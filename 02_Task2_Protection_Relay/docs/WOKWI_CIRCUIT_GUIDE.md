# Wokwi Circuit Guide (matching your screenshot)

The `wokwi_task1` folder has a simple six-pot cell/SoC/discharge circuit. `wokwi_task2` through `wokwi_task6` include an expanded illustrative circuit with:
- ESP32 DevKit
- Six potentiometers (four simulated cells + SoC + discharge)
- 16x2 I²C LCD
- Relay module
- Buzzer
- Green/red LEDs
- Three fault-injection buttons

## Important pin notes
- Pot signals: 32, 33, 34, 35, 36, 39.
- LCD I²C: SDA 21, SCL 22.
- Relay input: 23.
- Buzzer: 14.
- Green LED: 26; red LED: 27.
- Fault buttons: 16, 17, 18.

If Wokwi rejects a component field or pin name, add the component from the Wokwi parts panel and use its generated `diagram.json` schema; part schemas can vary. Do not assume the simulator circuit is evidence of a physical battery-safe circuit.
