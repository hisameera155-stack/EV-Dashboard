# Blynk Cloud Integration Guide

The included website is a local simulation and does not log in to Blynk. To connect real hardware:

1. Create a Blynk account and a new Template for ESP32.
2. Create datastreams (suggested virtual pins):
   - V0: Pack Voltage (Double, V)
   - V1: SoC (Integer, %)
   - V2: Voltage Imbalance (Double, V)
   - V3: Weakest Cell Index (Integer)
   - V4: Strongest Cell Index (Integer)
   - V5: Relay Status (Integer/Enum)
   - V6: State (String or Enum)
   - V7: Wi-Fi RSSI (Integer, dBm)
   - V8: Offline Queue Depth (Integer)
   - V9: Risk Score (Integer, 0–100)
   - V10: Fault/Event Log (String; keep payload bounded)
   - V11–V26: Cell 1–16 Voltage (Double, V)
3. Add matching widgets to the Blynk Web Dashboard: value displays, charts, LEDs/labels, and event log.
4. Copy the Template ID, Device Name, and Auth Token from Blynk into your local firmware configuration. Never publish the token to GitHub.
5. Install the Blynk library through Arduino IDE Library Manager and use the current Blynk ESP32 examples as the connection baseline.
6. Ensure connection handling is non-blocking; do not wait in a `while(WiFi.status()!=WL_CONNECTED)` loop.
7. Test cloud disconnect/reconnect and verify that queued event sequence numbers arrive in order.

Do not paste credentials into screenshots or commit them to source control. Cloud API details can change; follow the current Blynk documentation for the exact library/API version.
