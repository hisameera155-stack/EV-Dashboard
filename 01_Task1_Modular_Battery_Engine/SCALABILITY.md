# Task 1 Scalability: 4 to 16 Cells

The design is controlled by:
```cpp
#define NUM_CELLS 4
```

## Data structure scaling
The main variable-size storage is:
```cpp
float cellVoltage[NUM_CELLS];
```

Approximate storage:
| Cells | Cell array |
|---:|---:|
| 4 | 16 bytes |
| 8 | 32 bytes |
| 12 | 48 bytes |
| 16 | 64 bytes |

Other fixed fields in `BMSData` do not grow with the number of cells.

## Execution time
The weakest/strongest search is O(N), where N is the number of cells. Doubling the number of cells approximately doubles the loop work for that operation.

## Data structure
An array is used instead of separate variables such as `cell1`, `cell2`, etc. This is what makes the analysis reusable and scalable.

## Hardware consideration
For a real 16-cell pack, the ESP32 cannot simply connect 16 floating cell voltages directly to ordinary GPIO ADC pins. A real design needs a proper battery-monitoring front end, cell tap circuitry, isolation/measurement strategy, and protection. Wokwi here demonstrates the software architecture only.
