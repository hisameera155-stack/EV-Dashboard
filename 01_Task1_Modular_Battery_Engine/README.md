# Task 1 — Modular Battery Management Engine

Clean submission package — ESP32 + Wokwi.

## Direct project
**Wokwi:** https://wokwi.com/projects/477019229045221377

## Folder structure
```text
Task1_Modular_BMS_Clean/
├── ABOUT_TASK_1.md
├── README.md
├── WOKWI_PROJECT_URL.txt
├── TEST_PROCEDURE.md
├── SCALABILITY.md
├── WOKWI_STRUCTURE.md
├── SUBMISSION_CHECKLIST.md
├── project/
│   ├── sketch.ino
│   └── diagram.json
├── evidence/
│   └── screenshots/
│       ├── 01_architecture.png
│       ├── 02_wokwi_circuit_and_code.png
│       ├── 03_cell_analysis_output.png
│       └── 04_adaptive_threshold_warning.png
├── video/
│   └── Task1_Evidence_Video.mp4
└── report/
    ├── Task_1_Modular_BMS_Final_Report.pdf
    └── Task_1_Modular_BMS_Final_Report.docx
```

## About the implementation
The project uses `#define NUM_CELLS 4` and array-based processing so the same analysis engine can be scaled to other cell counts. It identifies the weakest and strongest cells, calculates voltage imbalance, tracks trend, and calculates an adaptive threshold from SoC and discharge rate.

## Wokwi circuit pins
| Input | ESP32 GPIO |
|---|---:|
| Cell 1 | 32 |
| Cell 2 | 33 |
| Cell 3 | 34 |
| Cell 4 | 35 |
| SoC | 36 |
| Discharge rate | 39 |

## Evidence video
`video/Task1_Evidence_Video.mp4` is a short evidence slideshow built from the real Task 1 screenshots stored in the package. It should be described as an evidence video/slideshow, not as a live screen recording.

## Note on trend evidence
The package contains the available real screenshots from the existing Task 1 report. If the assessment specifically requires separate screenshots showing `INCREASING` and `DECREASING`, capture those two states from the linked Wokwi project and place them in `evidence/screenshots/` before final submission.

## No Git files
Git/GitHub setup instructions and Git-related files are intentionally excluded from this clean Task 1 delivery folder.
