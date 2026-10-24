# Task 1 Test Procedure and Evidence Checklist

## Test 1 - Normal balanced pack
Set all four cell potentiometers close to the same position.
Expected:
- Weakest and strongest cells may be different.
- Voltage imbalance is small.
- Trend is STABLE after a few samples.
- Imbalance Status is NORMAL.

## Test 2 - Weakest-cell detection
Lower Cell 1 while keeping the other cells higher.
Expected:
- `Weakest Cell : Cell 1`
- Weakest voltage decreases.
- Voltage imbalance increases.

## Test 3 - Strongest-cell detection
Raise Cell 4 above the other cells.
Expected:
- `Strongest Cell : Cell 4`
- Strongest voltage increases.

## Test 4 - Increasing imbalance
Start with similar cell voltages. Gradually lower one cell.
Expected:
- Voltage imbalance increases.
- `Trend : INCREASING`.

## Test 5 - Decreasing imbalance
After Test 4, raise the weak cell toward the other cells.
Expected:
- Voltage imbalance decreases.
- `Trend : DECREASING`.

## Test 6 - Adaptive threshold
Move the SoC and discharge-rate potentiometers.
Expected:
- `Adaptive Threshold` changes according to SoC/discharge rate.

## Test 7 - Warning
Create a large difference between the weakest and strongest cells.
Expected:
- `Imbalance Status : WARNING`.

## Screenshots to capture for the report
1. Complete Wokwi circuit.
2. Serial Monitor showing all cell voltages.
3. Weakest/strongest cell identification.
4. Increasing trend.
5. Decreasing trend.
6. Adaptive threshold with one SoC/discharge condition.
7. Adaptive threshold under a different SoC/discharge condition.
8. Warning condition.

## Evidence rule
Do not rely only on one screenshot. Capture at least one screenshot for each major requirement.
