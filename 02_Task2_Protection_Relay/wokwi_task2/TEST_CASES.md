# Task 2 test cases

| Test ID | Action | Expected output |
|---|---|---|
| T2.1 | Start simulation | Startup banner and JSON-style serial output at 115200 |
| T2.2 | Adjust Pot1–Pot4 | Pack voltage and cell spread respond |
| T2.3 | Press GPIO16 fault button | Frozen ADC fault toggles; FAILSAFE and relay safe output should be logged |
| T2.4 | Press GPIO17 fault button | Jump fault toggles; state transition is logged |
| T2.5 | Press GPIO18 fault button | Out-of-range fault toggles; state transition is logged |
| T2.6 | Clear active button fault and wait | Verification period runs before recovery |
| T2.7 | Wait 5 seconds | LCD pages rotate (Task 3+) and critical fault overrides them |
| T2.8 | Inspect serial JSON | Timestamp, previous/new state, fault ID or telemetry fields are visible |
| T2.9 | Repeated fault toggles | Simulation continues without delay-based blocking |

For Task 5, network queue and Blynk behavior must be validated after implementing actual Wi-Fi/Blynk transport. The current sketch does not pretend that Serial telemetry is cloud connectivity.
