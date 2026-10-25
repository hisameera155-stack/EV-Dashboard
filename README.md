# Modular BMS — Six-Task Structured Project

This folder organizes the supplied Modular Battery Management System project materials into six task-specific sections.

## Folder map

1. `01_Task1_Modular_Battery_Engine/` — modular cell array, weakest/strongest cells, imbalance, adaptive thresholds, scalability notes, report and evidence.
2. `02_Task2_Protection_Relay/` — non-blocking relay/protection code, circuit, README and test cases.
3. `03_Task3_Flicker_Free_LCD/` — LCD engine code/circuit, report and supplied demo video.
4. `04_Task4_Fault_State_Machine/` — state-machine submission, transition/recovery test evidence, report, demo video, and Wokwi task code.
5. `05_Task5_Event_Driven_Telemetry/` — event-driven telemetry, offline queue/reconnection documentation, Blynk setup, tests, sample telemetry and supplied demo video.
6. `06_Task6_Enterprise_Analytics/` — analytics dashboard code/circuit, setup notes and test cases.

## Recommended workflow

- Open each task's README before running its sketch.
- Use the `diagram.json` and `sketch.ino` from the same task folder together.
- Configure your own Blynk Template ID, Template Name, and Auth Token where required. Do not publish credentials in screenshots or reports.
- Run the task test cases and capture your own current screenshots/video. Supplied evidence is preserved as provided; it is not a guarantee that every test currently passes.
- Keep the task-specific circuit/code pairs separate unless you deliberately integrate and re-test them. The six tasks may use different sketch versions and virtual-pin mappings.

## Important verification notes

This is a structured combination of the uploaded task archives, not a claim that every sketch has been independently compiled or every hardware/dashboard test has passed. Check each task's `TEST_CASES.md`/test procedure, verify libraries and pins, and test Blynk connectivity and offline queue behavior before final submission.

## Evidence and deliverables

Task-specific reports, screenshots, test files and demo videos included in the uploaded archives are retained in their respective task folders. If a file was not present in the supplied archive, this package does not fabricate it.
