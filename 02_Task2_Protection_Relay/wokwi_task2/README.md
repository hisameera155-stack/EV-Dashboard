# Task 2 — Wokwi project

## Purpose
Non-blocking protection relay: button toggles inject frozen/jump/range faults; debounce and timer logic; relay safe-state output.

## Circuit
This folder's `diagram.json` is an illustrative ESP32 circuit matching the general layout in the supplied screenshot: six potentiometers, ESP32, I2C LCD, relay module, buzzer, LEDs, and three fault buttons.

## Wiring summary
- Pot1–Pot4 SIG → GPIO32, 33, 34, 35; Pot5 SIG → GPIO36 (SoC); Pot6 SIG → GPIO39 (discharge).
- All potentiometer VCC → 3V3 and GND → ESP32 GND.
- LCD SDA → GPIO21, SCL → GPIO22, VCC → 3V3, GND → GND.
- Relay IN → GPIO23; relay VCC → 5V, GND → GND.
- Green LED anode → GPIO26; red LED anode → GPIO27; cathodes → GND.
- Buzzer + → GPIO14, − → GND.
- Fault buttons GPIO16/17/18 → one side; other side → GND. Firmware uses INPUT_PULLUP.

## Run
1. Create/open a Wokwi ESP32 project.
2. Paste this folder's `diagram.json` into diagram.json and `sketch.ino` into sketch.ino.
3. Add `LiquidCrystal_I2C` library if Wokwi does not resolve it automatically.
4. Start simulation and set Serial Monitor to 115200.
5. Follow `TEST_CASES.md`.

## Notes
This is a simulation starter, not validated battery-protection firmware. Check the component pin names in Wokwi's current editor; if a part schema differs, add that part using the Wokwi editor and rewire it there. Blynk cloud is not connected until credentials and real Wi-Fi integration are configured.
