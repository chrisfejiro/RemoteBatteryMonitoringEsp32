# ESP8266 IoT Battery Monitoring System

This project demonstrates how to use an **ESP8266 (NodeMCU)** to monitor its own **battery voltage** along with environmental data (temperature & humidity).  
The data is displayed on an **OLED screen** and simultaneously sent to the **Blynk IoT platform**, where users can track readings in real-time.  
It also sends a **low-battery alert** when the charge drops below 30%.

---

## 🚀 Features

- Reads **temperature** and **humidity** using a DHT22 sensor.  
- Monitors **battery voltage** using the ESP8266 analog pin (A0).  
- Converts analog values to percentage (0–100%).  
- Sends data to the **Blynk IoT dashboard** for remote monitoring:
  - V1 → Temperature  
  - V2 → Humidity  
  - V3 → Battery Voltage  
  - V4 → Battery Level %  
- Displays readings on an **SSD1306 OLED screen**.  
- Triggers a **Blynk notification event** (`battery_low`) when the battery level falls below 30%.  
- Prints debug information to the **Serial Monitor**.

---

## 🛠️ Hardware Requirements

- ESP8266 NodeMCU (or compatible board)  
- DHT22 temperature & humidity sensor  
- SSD1306 OLED display (128x64 I²C)  
- Li-ion battery or other DC source connected to the ESP8266  
- Supporting components (wires, breadboard, etc.)

---

## 📦 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software)  
- ESP8266 board package  
- Required libraries:
  - [BlynkEdgent](https://github.com/blynkkk) (for IoT connection)
  - [DHT Sensor Library](https://github.com/adafruit/DHT-sensor-library)
  - [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
  - [Adafruit SSD1306 Library](https://github.com/adafruit/Adafruit_SSD1306)

---

## ⚡ Circuit Connections

| Component       | ESP8266 Pin |
|-----------------|-------------|
| DHT22 Signal    | D4 (GPIO2)  |
| OLED SDA        | D2 (GPIO4)  |
| OLED SCL        | D1 (GPIO5)  |
| Battery Voltage | A0 (Analog) |

---

## 📋 How It Works

1. The ESP8266 reads the **raw analog value** from the battery on pin `A0`.  
2. Converts it into **voltage** with calibration (`voltageOffset`).  
3. Maps voltage (2.8V–4.2V) to a **battery percentage (0–100%)**.  
4. Reads **temperature** and **humidity** from the DHT22 sensor.  
5. Sends data to the **Blynk IoT dashboard**.  
6. Updates values on the **OLED display**.  
7. Sends **low battery alert** if charge ≤ 30%.

---

## 🖥️ Blynk Setup

1. Create a new device in the **Blynk IoT app**.  
2. Note your:
   - `BLYNK_TEMPLATE_ID`  
   - `BLYNK_DEVICE_NAME`  
3. Add the following datastreams:  
   - V1: Temperature  
   - V2: Humidity  
   - V3: Battery Voltage  
   - V4: Battery Level  
4. Create an **event** named `battery_low` for low-battery notifications.  

---

## 🔧 Code Highlights

- Replace template details:
  ```cpp
  #define BLYNK_TEMPLATE_ID "YourTemplateID"
  #define BLYNK_DEVICE_NAME "Smart IoT"
