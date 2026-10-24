# Task 1 — Modular Battery Management Engine

## About this folder
This is the clean Task 1 submission folder for the Modular Battery Management Engine.
It contains the ESP32/Wokwi source, circuit, report, evidence screenshots, and a demonstration evidence video.
Git/GitHub files have intentionally been removed from this delivery folder.

## Project
**Platform:** ESP32 + Wokwi  
**Task:** Modular Battery Management Engine Design  
**Cell configuration:** 4-cell demonstration  
**Scalable constant:** `NUM_CELLS`

## What Task 1 demonstrates
- Array-based battery-cell processing.
- Cell count controlled by one compile-time constant.
- Weakest-cell identification.
- Strongest-cell identification.
- Voltage-imbalance calculation.
- Imbalance trend tracking.
- Adaptive imbalance threshold based on SoC and discharge rate.
- Reusable `BMSData` interface.
- 4-to-16-cell scaling analysis.

## Direct Wokwi project
https://wokwi.com/projects/477019229045221377

## Evidence
The `evidence/screenshots` folder contains screenshots extracted from the existing Task 1 final report.
The `video` folder contains a short evidence slideshow made from those real screenshots. It is provided as a
submission/evidence video; it is not presented as a replacement for a live screen recording.

## Main files
- `project/sketch.ino` — ESP32 program.
- `project/diagram.json` — Wokwi circuit.
- `report/Task_1_Modular_BMS_Final_Report.pdf` — final report.
- `report/Task_1_Modular_BMS_Final_Report.docx` — editable report.
- `evidence/screenshots/` — project evidence.
- `video/Task1_Evidence_Video.mp4` — evidence video.
- `WOKWI_PROJECT_URL.txt` — direct Wokwi link.

## Important
The screenshots currently available document the circuit, code/diagram, cell-analysis output, and adaptive-threshold warning.
For a strict rubric requiring separate proof of **INCREASING** and **DECREASING** trend states, capture those two states from the Wokwi project and add them to `evidence/screenshots`.
