# Wokwi Circuit Structure

## Main controller
ESP32 DevKit.

## Inputs
Six potentiometers are used:
- Potentiometer 1 -> Cell 1 -> GPIO 32
- Potentiometer 2 -> Cell 2 -> GPIO 33
- Potentiometer 3 -> Cell 3 -> GPIO 34
- Potentiometer 4 -> Cell 4 -> GPIO 35
- Potentiometer 5 -> SoC -> GPIO 36
- Potentiometer 6 -> Discharge rate -> GPIO 39

Every potentiometer:
- VCC -> ESP32 3V3
- GND -> ESP32 GND
- SIG -> the assigned ADC pin

## Block diagram

```text
 Cell 1 POT ---- GPIO32 --+
 Cell 2 POT ---- GPIO33 --+
 Cell 3 POT ---- GPIO34 --+--> ESP32 --> Modular BMS Engine
 Cell 4 POT ---- GPIO35 --+                  |
 SoC POT ------- GPIO36 ---------------------+--> BMSData
 Discharge POT - GPIO39 ---------------------+--> Serial Monitor
```
