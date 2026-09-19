# Smart Irrigation System with On-Device TinyML (ESP32-S3)

An edge-AI precision irrigation system built around the ESP32-S3 microcontroller. The system features local, offline inference using a transpiled Decision Tree (CART) model to automatically control irrigation based on real-time environmental data, complete with a manual HMI touchscreen override, closed-loop water dosing, and automated cloud telemetry.

---

## 📁 Repository Structure
.
├── smart_irrigation_tinyml_esp32s3/
│   ├── smart_irrigation_tinyml_esp32s3.ino   # Main Arduino application firmware
│   └── model_ai_irigasi.h                   # Transpiled C++ Decision Tree model
└── README.md                                 # Project documentation

---

## 🛠️ Hardware & Requirements

### Hardware Components
* Microcontroller: ESP32-S3 Development Board
* Sensors:
* DHT22 (Air Temperature & Air Humidity)
* Capacitive Soil Moisture Sensor v1.2 (Analog ADC)
* YF-S401 Water Flow Sensor (Pulse-based)
* Actuator & Interface:
* 12V DC Water Pump with Relay Module
* Nextion / TJC HMI Touchscreen Display

### Software & Libraries
* Arduino IDE (v2.x recommended)
* ESP32 Board Support Package (v2.0.x or higher)
* Required Arduino Libraries:
* DHT sensor library by Adafruit
* Adafruit Unified Sensor
* WiFi & HTTPClient (Built-in ESP32 core)

---

## 📊 Dataset & Model Training
The decision tree classifier in model_ai_irigasi.h was trained offline using a publicly available Kaggle IoT sensor dataset:

Dataset Source: Raspberry Pi IoT Irrigation Sensor Data (Kaggle)

Features Used: Air Temperature, Air Humidity, and Soil Moisture.

Target Output: Binary Irrigation Decision (1 = Irrigate / Pump ON, 0 = Do Not Irrigate / Pump OFF).
Transpilation Process: The trained Scikit-Learn decision tree model was transpiled into pure C++ nested if-else logic using a custom Python script, enabling lightweight and zero-dependency execution on the ESP32-S3.

---

## 🚀 Getting Started & Deployment Guide
Follow these step-by-step instructions to compile and upload the firmware to your ESP32-S3.

### Step 1: Directory Setup
Arduino IDE requires the main folder name to match the main .ino file name exactly:
1. Create a folder named smart_irrigation_tinyml_esp32s3.
2. Place smart_irrigation_tinyml_esp32s3.ino and model_ai_irigasi.h inside this single folder.

### Step 2: Configure Credentials & Endpoints
Open smart_irrigation_tinyml_esp32s3.ino in Arduino IDE and update the network and API configuration block:

// Update with your local WiFi credentials
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

// Update with your deployed Google Apps Script Web App URL
const String GOOGLE_SCRIPT_URL = "[https://script.google.com/macros/s/YOUR_SCRIPT_ID/exec](https://www.google.com/search?q=https://script.google.com/macros/s/YOUR_SCRIPT_ID/exec&utm_source=gemini)";

### Step 3: Verify Model Header Inclusion
Ensure that model_ai_irigasi.h is present in the same directory as the .ino file. The C++ transpiled Decision Tree function is included via:

#include "model_ai_irigasi.h"

Note: The prediksi_penyiraman(soil_moisture, temperature, humidity) function inside model_ai_irigasi.h accepts live sensor inputs and outputs 1 (irrigate) or 0 (do not irrigate).

### Step 4: Board Configuration in Arduino IDE
1. Connect your ESP32-S3 board via USB.
2. Go to Tools > Board and select ESP32S3 Dev Module.
3. Set the following board settings:
* USB CDC On Boot: Enabled (if monitoring Serial output via native USB)
* Flash Size: 8MB or 16MB (depending on your board module)
* Port: Select the COM port corresponding to your ESP32-S3.



### Step 5: Compile & Upload
1. Click the Verify button (check mark icon) to compile the firmware and ensure there are no missing libraries or header references.
2. Click the Upload button (arrow icon) to flash the code onto the ESP32-S3.
3. Open the Serial Monitor set to 115200 baud to view boot logs, Wi-Fi status, and AI inference outputs.

---

## ⚡ How It Works
1. Autonomous AI Inference (1 Hz): Every second, the system reads air temperature, air humidity, and capacitive soil moisture. It feeds these values into the lightweight C++ function in model_ai_irigasi.h to execute offline decision-making without cloud reliance.
2. Precision Closed-Loop Dosing: When irrigation is triggered, the pump activates and the YF-S401 flow sensor tracks water delivery pulse-by-pulse until the 100 mL target threshold (adjusted with inertia offset) is reached.
3. Infiltration Cooldown Delay: After dosing completes, a 30-second soaking delay is enforced to allow water absorption before reading the soil sensor again, preventing false re-triggers.
4. Cloud Telemetry: At configurable intervals, the system transmits aggregated telemetry logs (temperature, humidity, soil moisture, raw ADC, trigger source, and batch volume) to Google Sheets via HTTP GET requests.
