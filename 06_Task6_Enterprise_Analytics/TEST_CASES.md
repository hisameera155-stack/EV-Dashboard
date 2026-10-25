# Task 6 test cases

| Test ID | Action | Expected output |
|---|---|---|
| T6.1 | Start simulation | Startup banner and JSON-style serial output at 115200 |
| T6.2 | Adjust Pot1–Pot4 | Pack voltage and cell spread respond |
| T6.3 | Press GPIO16 fault button | Frozen ADC fault toggles; FAILSAFE and relay safe output should be logged |
| T6.4 | Press GPIO17 fault button | Jump fault toggles; state transition is logged |
| T6.5 | Press GPIO18 fault button | Out-of-range fault toggles; state transition is logged |
| T6.6 | Clear active button fault and wait | Verification period runs before recovery |
| T6.7 | Wait 5 seconds | LCD pages rotate (Task 3+) and critical fault overrides them |
| T6.8 | Inspect serial JSON | Timestamp, previous/new state, fault ID or telemetry fields are visible |
| T6.9 | Repeated fault toggles | Simulation continues without delay-based blocking |

For Task 5, network queue and Blynk behavior must be validated after implementing actual Wi-Fi/Blynk transport. The current sketch does not pretend that Serial telemetry is cloud connectivity.
