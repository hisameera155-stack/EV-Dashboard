#include <Arduino.h>
#include <math.h>

// ============================================================
// Task 1: Modular Battery Management Engine
// ESP32 + Wokwi
// ============================================================

// Change ONLY this value to scale the design.
// Example: 4, 8, 12, 16 cells.
#define NUM_CELLS 4

// ESP32 ADC pins used for the cell-voltage demonstration inputs.
// Wokwi potentiometers represent the measured cell voltages.
const uint8_t CELL_PINS[NUM_CELLS] = {32, 33, 34, 35};

// Additional analog inputs
#define SOC_PIN       36
#define DISCHARGE_PIN 39

// Sampling
const unsigned long SAMPLE_INTERVAL = 1000;

// Demonstration cell-voltage range
const float CELL_MIN_V = 3.00f;
const float CELL_MAX_V = 4.20f;

// Adaptive threshold limits
const float THRESHOLD_MIN = 0.08f;
const float THRESHOLD_MAX = 0.20f;

struct BMSData {
  float cellVoltage[NUM_CELLS];

  int weakestCell;
  int strongestCell;

  float weakestVoltage;
  float strongestVoltage;

  float voltageImbalance;
  float previousImbalance;

  float soc;
  float dischargeRate;

  float adaptiveThreshold;
  String trend;

  bool imbalanceWarning;
};

BMSData bms;

unsigned long lastSampleTime = 0;

// ------------------------------------------------------------
// Utility functions
// ------------------------------------------------------------

float mapFloat(float x, float inMin, float inMax,
               float outMin, float outMax) {
  return (x - inMin) * (outMax - outMin) /
         (inMax - inMin) + outMin;
}

float clampFloat(float value, float low, float high) {
  if (value < low) return low;
  if (value > high) return high;
  return value;
}

// ------------------------------------------------------------
// Sensor reading
// ------------------------------------------------------------

float readCellVoltage(uint8_t index) {
  int raw = analogRead(CELL_PINS[index]);

  // Wokwi demonstration mapping:
  // ADC 0..4095 -> 3.00..4.20 V
  return mapFloat((float)raw, 0.0f, 4095.0f,
                  CELL_MIN_V, CELL_MAX_V);
}

float readSOC() {
  int raw = analogRead(SOC_PIN);

  // ADC 0..4095 -> 0..100 %
  return clampFloat(
    mapFloat((float)raw, 0.0f, 4095.0f, 0.0f, 100.0f),
    0.0f, 100.0f
  );
}

float readDischargeRate() {
  int raw = analogRead(DISCHARGE_PIN);

  // Demonstration mapping:
  // ADC 0..4095 -> 0..20 A
  return clampFloat(
    mapFloat((float)raw, 0.0f, 4095.0f, 0.0f, 20.0f),
    0.0f, 20.0f
  );
}

// ------------------------------------------------------------
// Adaptive imbalance threshold
// Based on SoC and discharge rate.
// ------------------------------------------------------------

float calculateAdaptiveThreshold(float soc, float dischargeRate) {
  float threshold = 0.08f;

  // More conservative threshold at very low/high SoC.
  if (soc < 20.0f || soc > 90.0f) {
    threshold = 0.12f;
  } else if (soc < 40.0f || soc > 80.0f) {
    threshold = 0.10f;
  }

  // Allow a little more imbalance during higher discharge.
  threshold += 0.002f * dischargeRate;

  return clampFloat(threshold, THRESHOLD_MIN, THRESHOLD_MAX);
}

// ------------------------------------------------------------
// Core BMS analysis
// ------------------------------------------------------------

void analyzeBattery() {
  bms.soc = readSOC();
  bms.dischargeRate = readDischargeRate();

  bms.weakestCell = 0;
  bms.strongestCell = 0;

  for (int i = 0; i < NUM_CELLS; i++) {
    bms.cellVoltage[i] = readCellVoltage(i);
  }

  // Find weakest and strongest cells.
  for (int i = 1; i < NUM_CELLS; i++) {
    if (bms.cellVoltage[i] < bms.cellVoltage[bms.weakestCell]) {
      bms.weakestCell = i;
    }

    if (bms.cellVoltage[i] > bms.cellVoltage[bms.strongestCell]) {
      bms.strongestCell = i;
    }
  }

  bms.weakestVoltage = bms.cellVoltage[bms.weakestCell];
  bms.strongestVoltage = bms.cellVoltage[bms.strongestCell];

  // Imbalance = strongest - weakest
  bms.previousImbalance = bms.voltageImbalance;
  bms.voltageImbalance =
      bms.strongestVoltage - bms.weakestVoltage;

  // Adaptive threshold
  bms.adaptiveThreshold =
      calculateAdaptiveThreshold(bms.soc, bms.dischargeRate);

  // Trend
  const float TREND_EPSILON = 0.005f;

  if (bms.voltageImbalance >
      bms.previousImbalance + TREND_EPSILON) {
    bms.trend = "INCREASING";
  } else if (bms.voltageImbalance <
             bms.previousImbalance - TREND_EPSILON) {
    bms.trend = "DECREASING";
  } else {
    bms.trend = "STABLE";
  }

  bms.imbalanceWarning =
      (bms.voltageImbalance > bms.adaptiveThreshold);
}

// ------------------------------------------------------------
// Output
// ------------------------------------------------------------

void printBMSData() {
  Serial.println();
  Serial.println("========================================");
  Serial.println("       MODULAR BMS ENGINE - TASK 1");
  Serial.println("========================================");

  Serial.print("Number of Cells : ");
  Serial.println(NUM_CELLS);

  Serial.println();
  Serial.println("CELL VOLTAGES:");

  for (int i = 0; i < NUM_CELLS; i++) {
    Serial.print("Cell ");
    Serial.print(i + 1);
    Serial.print(" : ");
    Serial.print(bms.cellVoltage[i], 3);
    Serial.println(" V");
  }

  Serial.println();
  Serial.print("Weakest Cell      : Cell ");
  Serial.println(bms.weakestCell + 1);

  Serial.print("Weakest Voltage   : ");
  Serial.print(bms.weakestVoltage, 3);
  Serial.println(" V");

  Serial.print("Strongest Cell    : Cell ");
  Serial.println(bms.strongestCell + 1);

  Serial.print("Strongest Voltage : ");
  Serial.print(bms.strongestVoltage, 3);
  Serial.println(" V");

  Serial.print("Voltage Imbalance : ");
  Serial.print(bms.voltageImbalance, 3);
  Serial.println(" V");

  Serial.print("Previous Imbalance: ");
  Serial.print(bms.previousImbalance, 3);
  Serial.println(" V");

  Serial.print("Trend             : ");
  Serial.println(bms.trend);

  Serial.print("State of Charge   : ");
  Serial.print(bms.soc, 1);
  Serial.println(" %");

  Serial.print("Discharge Rate    : ");
  Serial.print(bms.dischargeRate, 2);
  Serial.println(" A");

  Serial.print("Adaptive Threshold: ");
  Serial.print(bms.adaptiveThreshold, 3);
  Serial.println(" V");

  Serial.print("Imbalance Status  : ");
  Serial.println(bms.imbalanceWarning ? "WARNING" : "NORMAL");

  Serial.println("========================================");
}

void setup() {
  Serial.begin(115200);
  delay(500);

  for (int i = 0; i < NUM_CELLS; i++) {
    pinMode(CELL_PINS[i], INPUT);
  }

  pinMode(SOC_PIN, INPUT);
  pinMode(DISCHARGE_PIN, INPUT);

  // Initialize previous values cleanly.
  bms.voltageImbalance = 0.0f;
  bms.previousImbalance = 0.0f;
  bms.trend = "STABLE";

  Serial.println("Task 1 Modular BMS Engine started.");
  Serial.println("Open Serial Monitor at 115200 baud.");
}

void loop() {
  unsigned long now = millis();

  if (now - lastSampleTime >= SAMPLE_INTERVAL) {
    lastSampleTime = now;

    analyzeBattery();
    printBMSData();
  }
}
