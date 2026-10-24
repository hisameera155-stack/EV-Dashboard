# Modular Battery Management System (BMS) — Project Report

## 1. Objective
Design a modular BMS demonstration with scalable cell analysis, non-blocking protection logic, LCD page management, structured fault recovery, event-driven telemetry, and an analytics dashboard.

## 2. Architecture
The project is split into reusable layers:
1. **Cell analysis:** reads an array of cell voltages and calculates pack voltage, weakest/strongest cell, spread, and trend.
2. **Protection manager:** evaluates thresholds and anomaly flags without blocking delays.
3. **State machine:** maintains NORMAL, DEGRADED, FAILSAFE, and SHUTDOWN states.
4. **Display manager:** rotates information pages on a timer and prioritizes fault display.
5. **Telemetry queue:** fixed-size FIFO for offline events; events are sent in sequence after connectivity returns.
6. **Dashboard:** visualizes measurements, injected faults, network state, queue depth, transition history, and a heuristic risk score.

## 3. Task mapping
### Task 1 — Modular Battery Engine
- Cell count is configured by `NUM_CELLS` in firmware.
- Analysis scans the array to compute pack voltage and min/max cell values.
- Imbalance is `maxCellVoltage - minCellVoltage`.
- Trend is estimated by comparing the current spread with the previous sample.
- The example adaptive threshold changes with SoC and discharge rate. These values are demonstration parameters and must be tuned to the chemistry, cell manufacturer, and sensing accuracy.

### Task 2 — Non-blocking Protection
- Firmware uses `millis()` timing and does not use `delay()` in its main control loop.
- Fault flags cover cell imbalance, frozen ADC, unrealistic jumps, range checks, relay feedback mismatch, and communication loss.
- A production implementation should use calibrated sensor limits, debounce, a moving window/median filter, and separate load-transient detection.
- Relay switching in this template is an educational logical output; add a properly rated driver, flyback protection where applicable, and independent hardware interlocks.

### Task 3 — Flicker-free LCD Engine
- Website preview rotates among Battery, System State, and Telemetry pages.
- The display layer should compare new text against prior text and update only changed character positions. The included firmware starter outputs status to Serial; add the correct LCD library and I²C address for your physical display before enabling hardware LCD writes.
- Five seconds is a reasonable demo page interval; fast safety updates should not wait for page rotation.

### Task 4 — Fault State Machine
States:
- `NORMAL`: measurements and relay feedback are acceptable.
- `DEGRADED`: warning threshold exceeded, but critical safety checks pass.
- `FAILSAFE`: critical sensor/relay/communication fault; relay command moves to safe state.
- `SHUTDOWN`: latched terminal state requiring explicit operator/service reset.

Recovery should verify fault-clear status continuously for a defined interval before restoring normal operation. Every transition should log timestamp, previous state, new state, fault ID, and source.

| Current state | Condition | Next state |
|---|---|---|
| NORMAL | Warning-level imbalance | DEGRADED |
| NORMAL/DEGRADED | Critical fault | FAILSAFE |
| DEGRADED | Measurements stable and warning cleared | NORMAL |
| FAILSAFE | Fault cleared and verification timer passes | NORMAL or DEGRADED |
| Any non-SHUTDOWN state | Explicit shutdown request | SHUTDOWN |
| SHUTDOWN | Service reset / explicit reset | NORMAL only after checks |

### Task 5 — Event-driven telemetry
- Telemetry is emitted on state transitions, faults, connectivity changes, or significant measurement changes.
- A fixed-size FIFO queue stores events while offline and flushes in FIFO order after reconnect.
- The template's serial transport is not a real Wi-Fi/Blynk implementation. Use the Blynk setup guide to connect device credentials and map datastreams.

### Task 6 — Analytics dashboard
- The website computes a demonstration risk score from voltage spread, SoC, and fault history.
- The risk score and operator recommendations are heuristic examples, not validated battery-health diagnostics.
- Blynk charts and historical analytics require real datastreams and cloud-side configuration.

## 4. Scaling from 4 to 16 cells
Let `N` be the cell count.
- Cell storage is `O(N)`: one `float` per cell, approximately 4N bytes for raw voltages (16 bytes at N=4, 64 bytes at N=16), excluding metadata and alignment.
- Min/max, sum, and spread can be calculated in one pass: `O(N)` time per sample.
- Increasing from 4 to 16 cells makes the scan approximately 4× longer, but 16 comparisons/additions per sample are still small for an ESP32 at typical sampling rates.
- A fixed queue of `Q` events consumes `O(Q)` memory, independent of cell count. Event payload size should be bounded in firmware.
- ADC input count and safe voltage measurement are hardware constraints. A real multi-cell pack requires appropriate isolated/stacked sensing or a battery-monitor IC; never connect a high-voltage cell stack directly to ESP32 ADC pins.

## 5. Test procedure
See `../tests/TEST_PLAN.md`. Record actual serial output, dashboard states, and screenshots from your own run. Do not claim hardware/Blynk integration based only on the local website simulation.

## 6. Limitations and next steps
1. Calibrate cell voltage readings and verify sensor wiring.
2. Implement a robust ADC noise window and frozen-reading timer with realistic sensor resolution.
3. Add actual relay driver/feedback wiring and fail-safe hardware.
4. Configure Blynk template, datastreams, dashboard widgets, and device credentials.
5. Run sustained fault-injection tests and verify queue overflow policy.
6. Validate all limits for the selected cell chemistry and pack configuration.
