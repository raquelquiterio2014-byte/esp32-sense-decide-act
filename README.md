# ESP32 Sense, Decide & Act — Temperature Monitoring Lab

Educational IoT project using an ESP32 and DHT22 sensor to demonstrate a simple embedded decision cycle:

**Sense → Validate → Decide → Act → Wait → Repeat**

## Project objective

The project monitors temperature and humidity with a DHT22 sensor. The ESP32 validates each sensor reading before applying a temperature rule. A red LED represents the output command or alert.

## Hardware

- ESP32 DevKit C V4
- DHT22 temperature and humidity sensor
- Red LED
- 330 Ω resistor

## Pin configuration

| Component | ESP32 pin |
| --- | --- |
| DHT22 data | GPIO 4 |
| LED | GPIO 26 |

## Decision rule

The temperature threshold is **30 °C**.

- **Temperature > 30 °C** → `ALERT` → LED ON
- **Temperature ≤ 30 °C** → `NORMAL` → LED OFF
- **Invalid DHT22 reading** → `ERROR` → LED OFF

The acquisition cycle repeats every **2 seconds**.

## Validation tests

| Test | Expected / observed behavior |
| --- | --- |
| 28.8 °C (~29 °C) | NORMAL — LED OFF |
| 30.0 °C | NORMAL — LED OFF |
| 31.0 °C | ALERT — LED ON |
| Invalid sensor reading | ERROR — LED OFF |
| Recovery after reconnecting sensor | Valid readings resume and the decision cycle continues |

The 30 °C boundary test confirms that the implementation uses a strict comparison: the alert is triggered only when the measured temperature is **greater than** 30 °C.

## Failure and recovery test

Sensor failure was simulated by temporarily disconnecting the DHT22 data signal from GPIO 4. The program detected the invalid reading, printed `ERROR: Failed to read DHT22.` and kept the LED OFF.

After reconnecting the signal, valid readings resumed and the system returned to the normal Sense → Validate → Decide → Act cycle.

## Technologies

- ESP32
- DHT22
- Arduino / C++
- Adafruit DHT Sensor Library
- Wokwi
- Serial Monitor

## Project files

- `sketch.ino` — ESP32 application code
- `diagram.json` — Wokwi circuit definition
- `libraries.txt` — Wokwi library dependency
- `wokwi-project.txt` — Wokwi project reference

## Run the simulation

[Open the final project in Wokwi](https://wokwi.com/projects/479505405813167105)

## Learning outcomes

This lab focuses not only on obtaining sensor data, but also on validating input, testing decision boundaries, defining deterministic output behavior, handling invalid readings, and confirming recovery after a simulated sensor failure.

---

Developed by **Raquel Cruz** as an educational IoT and embedded-systems study.
