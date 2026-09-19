// =============================================================
// =============================================================
//        SMART IRRIGATION SYSTEM - AI DECISION TREE
//    CAPACITIVE SOIL SENSOR, DHT22 & WATER FLOW SENSOR
//         WITH GOOGLE SHEETS TELEMETRY (1-HOUR LOG)
// =============================================================
// =============================================================

#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "time.h"
#include "model_ai_irigasi.h" // Import Transpiled AI Decision Tree Model

// -------------------------------------------------------------
// WIFI & GOOGLE APPS SCRIPT CONFIGURATION
// -------------------------------------------------------------
const char* WIFI_SSID     = "YOUR_WIFI_SSID";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
const String GOOGLE_SCRIPT_URL = "https://script.google.com/macros/s/YOUR_SCRIPT_ID/exec";

// Data transmission interval to Google Sheets (3600000 ms = 1 Hour)
const unsigned long LOG_INTERVAL_MS = 3600000; 
unsigned long lastLogTime = 0;

// NTP Time Configuration (GMT+7)
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 7 * 3600;  
const int daylightOffset_sec = 0;

// -------------------------------------------------------------
// ESP32-S3 PINOUT CONFIGURATION
// -------------------------------------------------------------
#define HMI_TX_PIN      15  // Connected to TJC/Nextion Display RX
#define HMI_RX_PIN      16  // Connected to TJC/Nextion Display TX
#define FLOW_PIN        5   // YF-S401 Water Flow Sensor Pin
#define SOIL_ADC_PIN    3   // Capacitive Soil Moisture Sensor (Analog ADC1)
#define DHT_PIN         18  // DHT Pin (Air Temperature & Humidity)
#define RELAY_PUMP_PIN  20  // Water Pump Relay Module
#define SOIL_POWER_PIN  46  // VCC Power Switching Pin for Soil Sensor
#define DHTTYPE         DHT22 

// -------------------------------------------------------------
// DOSING & COOLDOWN CALIBRATION PARAMETERS
// -------------------------------------------------------------
const float TARGET_BATCH_ML     = 100.0; // Target irrigation batch volume (mL)
const float EARLY_CUTOFF_ML     = 5.0;   // Inertia offset threshold
const float FLOW_CALIB_FACTOR   = 88.2;  // YF-S401 Calibration Factor (pulses/L)
const unsigned long SOAKING_TIME_MS = 30000; // Infiltration cooldown delay (30 seconds)

// -------------------------------------------------------------
// OBJECT INITIALIZATION & GLOBAL VARIABLES
// -------------------------------------------------------------
DHT dht(DHT_PIN, DHTTYPE);

// Water Flow & Accumulation Variables
volatile unsigned long pulseCount = 0;
float flowRateMls = 0.0;          // Water flow rate (mL/s)
float batchWaterMl = 0.0;         // Water volume in active dosing session (mL)
float hourlyCompletedBatchMl = 0.0;// Accumulated water volume delivered per hour (mL)
float totalWaterMl = 0.0;         // Total lifetime accumulated water volume (mL)

// Trigger Source Latching Flags (Captured within the 1-hour interval)
bool flagAiTriggered     = false;
bool flagManualTriggered = false;
bool isManualAction      = false; // Differentiates active trigger source (AI vs Manual HMI)

// Control Status, AI & Cooldown Timers
bool isPumpOn = false;
int aiDecisionResult = 0;
unsigned long lastPumpOffTime = 0; // Timestamp when pump was turned off
int rawSoilADCForCloud = 0;         // Raw ADC value stored for Google Sheets telemetry

// Soil Sensor ADC Calibration Limits
const int SOIL_DRY_ADC = 3200; 
const int SOIL_WET_ADC = 1500; 

// Interrupt Service Routine (ISR) for Water Flow Sensor
void IRAM_ATTR pulseCounterISR() {
  pulseCount++;
}

// Helper to send Nextion/TJC HMI termination command
void endCommand() {
  Serial1.write(0xFF);
  Serial1.write(0xFF);
  Serial1.write(0xFF);
}

// Function to get NTP Date & Time String (YYYY-MM-DD HH:MM)
String getDateTimeNTP() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "----/--/-- --:--";
  }
  char timeBuff[20];
  strftime(timeBuff, sizeof(timeBuff), "%Y-%m-%d %H:%M", &timeinfo);
  return String(timeBuff);
}

// Function to read capacitive soil moisture percentage
float readSoilMoisture() {
  digitalWrite(SOIL_POWER_PIN, HIGH);
  delay(20);
  rawSoilADCForCloud = analogRead(SOIL_ADC_PIN);
  digitalWrite(SOIL_POWER_PIN, LOW);
  
  float percentage = map(rawSoilADCForCloud, SOIL_DRY_ADC, SOIL_WET_ADC, 0, 100);
  return constrain(percentage, 0.0, 100.0);
}

// Function to stop the water pump
void stopPump() {
  isPumpOn = false;
  digitalWrite(RELAY_PUMP_PIN, LOW);
  
  // Accumulate dosing volume to hourly total
  hourlyCompletedBatchMl += batchWaterMl; 
  batchWaterMl = 0.0;
  
  lastPumpOffTime = millis(); // Record timestamp for infiltration delay
  Serial1.print("b0.txt=\"MANUAL\"");
  endCommand();
}

// Function to start the water pump
void startPump(bool isManual) {
  isPumpOn = true;
  isManualAction = isManual;
  
  // Latch trigger status flags
  if (isManual) {
    flagManualTriggered = true;
  } else {
    flagAiTriggered = true;
  }

  batchWaterMl = 0.0;
  digitalWrite(RELAY_PUMP_PIN, HIGH);
  Serial1.print("b0.txt=\"STOP\"");
  endCommand();
}

// Function to transmit telemetry data to Google Sheets
void sendTelemetryToGoogle(float temp, float humid, float soil, int rawAdc, String triggerSource, float batchMl, float totalMl) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    String url = GOOGLE_SCRIPT_URL + "?temp=" + String(temp, 1) +
                 "&humid=" + String(humid, 1) +
                 "&soil=" + String(soil, 1) +
                 "&soil_adc=" + String(rawAdc) +
                 "&trigger=" + triggerSource +
                 "&batch_ml=" + String(batchMl, 1) +
                 "&total_ml=" + String(totalMl, 1);

    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.printf("[CLOUD LOG] Telemetry Sent! Code: %d | Trigger: %s | Batch: %.1f mL\n", 
                    httpCode, triggerSource.c_str(), batchMl);
    } else {
      Serial.printf("[CLOUD ERROR] Transmission Failed: %s\n", http.errorToString(httpCode).c_str());
    }
    http.end();
  } else {
    Serial.println("[WIFI WARN] Offline, Skipping Cloud Sync...");
  }
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600, SERIAL_8N1, HMI_RX_PIN, HMI_TX_PIN);

  pinMode(RELAY_PUMP_PIN, OUTPUT);
  pinMode(SOIL_POWER_PIN, OUTPUT);
  digitalWrite(RELAY_PUMP_PIN, LOW);
  digitalWrite(SOIL_POWER_PIN, LOW);

  pinMode(FLOW_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(FLOW_PIN), pulseCounterISR, RISING);

  dht.begin();
  delay(1000);

  Serial.print("Connecting to WiFi: ");
  Serial.println(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int wifiTimeout = 0;
  while (WiFi.status() != WL_CONNECTED && wifiTimeout < 20) {
    delay(500);
    Serial.print(".");
    wifiTimeout++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WIFI] Connected Successfully!");
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    sendTelemetryToGoogle(dht.readTemperature(), dht.readHumidity(), readSoilMoisture(), rawSoilADCForCloud, "OFF", 0.0, totalWaterMl);
  } 
  else {
    Serial.println("\n[WIFI] Connection Timeout! Running in Offline Mode.");
  }
  
  Serial1.print("b0.txt=\"MANUAL\"");
  endCommand();
  Serial.println("System Ready! AI Decision Engine Active.");
}

void loop() {

  // =============================================================
  // 1. MANUAL OVERRIDE CONTROL VIA HMI TOUCHSCREEN
  // =============================================================
  if (Serial1.available() >= 7) {
    byte header = Serial1.read();

    if (header == 0x65) { 
      byte pageID      = Serial1.read();
      byte componentID = Serial1.read(); 
      byte eventType   = Serial1.read(); 

      Serial1.read(); Serial1.read(); Serial1.read();

      if (componentID == 0x07 && eventType == 0x01) {
        if (!isPumpOn) {
          startPump(true); // Manual Trigger
          Serial.println("[USER] Manual Override: Starting Dosing Routine...");
        } else {
          stopPump();
          Serial.println("[USER] Manual Override: Emergency Stop Initiated!");
        }
      }
    }
  }

  // =============================================================
  // 2. ROUTINE SENSOR READING & AI INFERENCE (EVERY 1 SECOND)
  // =============================================================
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    // ---------------------------------------------------------
    // A. WATER FLOW CALCULATION & INERTIA COMPENSATION
    // ---------------------------------------------------------
    detachInterrupt(digitalPinToInterrupt(FLOW_PIN));
    
    flowRateMls = ((float)pulseCount / FLOW_CALIB_FACTOR) * (1000.0 / 60.0);
    
    if (isPumpOn) {
      batchWaterMl += flowRateMls;
      totalWaterMl += flowRateMls;

      // AUTO STOP WITH INERTIA COMPENSATION OFFSET
      if (batchWaterMl >= (TARGET_BATCH_ML - EARLY_CUTOFF_ML)) {
        stopPump();
        Serial.printf("[AUTO STOP] Reached Target with Inertia Offset! Pump turned OFF.\n");
      }
    }
    
    pulseCount = 0; 
    attachInterrupt(digitalPinToInterrupt(FLOW_PIN), pulseCounterISR, RISING);

    // ---------------------------------------------------------
    // B. ENVIRONMENTAL SENSOR READINGS
    // ---------------------------------------------------------
    float airHum   = dht.readHumidity();
    float airTemp  = dht.readTemperature();
    float soilMois = readSoilMoisture();
    bool dhtError  = isnan(airHum) || isnan(airTemp);

    // ---------------------------------------------------------
    // C. AI DECISION ENGINE INFERENCE
    // ---------------------------------------------------------
    bool isSoaking = (millis() - lastPumpOffTime < SOAKING_TIME_MS) && (lastPumpOffTime > 0);
    if (!dhtError) {
      aiDecisionResult = prediksi_penyiraman(soilMois, airTemp, airHum); 

      if (aiDecisionResult == 1 && !isPumpOn && !isSoaking) { 
        startPump(false); // Autonomous AI Trigger
        Serial.println("[AI AUTO TRIGGER] Irrigation Conditions Met -> Executing Dosing Cycle.");
      }
    }

    // ---------------------------------------------------------
    // D. UPDATE HMI TOUCHSCREEN DISPLAY
    // ---------------------------------------------------------
    if (WiFi.status() == WL_CONNECTED) {
      Serial1.print("t1.txt=\"Status Wifi: Connected\""); endCommand();
    } else {
      Serial1.print("t1.txt=\"Status Wifi: Disconnected\""); endCommand();
      WiFi.begin(WIFI_SSID, WIFI_PASSWORD); 
    }

    Serial1.print("t2.txt=\"" + getDateTimeNTP() + "\""); endCommand();

    if (dhtError) {
      Serial1.print("t4.txt=\" Air Humidity   : --.- %\""); endCommand();
      Serial1.print("t5.txt=\" Air Temperature: --.- C\""); endCommand();
    } else {
      Serial1.print("t4.txt=\" Air Humidity   : " + String(airHum, 1) + " %\""); endCommand();
      Serial1.print("t5.txt=\" Air Temperature: " + String(airTemp, 1) + " C\""); endCommand();
    }

    Serial1.print("t6.txt=\" Soil Moisture  : " + String(soilMois, 1) + " %\""); endCommand();
    Serial1.print("t7.txt=\" Soil pH        : -\""); endCommand();
    Serial1.print("t8.txt=\" Rain Intensity : - %\""); endCommand();

    // ---------------------------------------------------------
    // E. UPDATE SYSTEM STATUS & AI DECISION UI
    // ---------------------------------------------------------
    Serial1.print("t10.txt=\" Operation Mode : AUTO (AI)\""); endCommand();
    
    String aiString;
    if (isSoaking && aiDecisionResult == 1) { 
      unsigned long remainSec = (SOAKING_TIME_MS - (millis() - lastPumpOffTime)) / 1000;
      aiString = "WAIT SOAKING (" + String(remainSec) + "s)";
    } else {
      aiString = (aiDecisionResult == 1) ? "PUMP ON" : "PUMP OFF";
    }
    
    Serial1.print("t11.txt=\" AI Decision    : " + aiString + "\""); endCommand();
    Serial1.print("t12.txt=\" Pump Status    : " + String(isPumpOn ? "ON" : "OFF") + "\""); endCommand();

    // ---------------------------------------------------------
    // F. UPDATE STATUS BAR
    // ---------------------------------------------------------
    static bool hbState = false;
    hbState = !hbState;
    String hbSymbol = hbState ? "[]" : "]["; 
    String statusText = "t14.txt=\"Irrig Status: Flow: " + String(flowRateMls, 1) 
                        + " mL/s | Batch: " + String(batchWaterMl, 0) + "/100 mL | Total: " 
                        + String(totalWaterMl, 0) + " mL | " + hbSymbol + "\"";
    
    Serial1.print(statusText);
    endCommand();

    // Debug Console Log
    Serial.printf("[SYSTEM] AI Decision: %s | Flow: %.1f mL/s | Batch: %.0f/100mL | Pump: %s\n",
                  aiString.c_str(), flowRateMls, batchWaterMl, isPumpOn ? "ON" : "OFF");

    // ---------------------------------------------------------
    // G. TELEMETRY DATA TRANSMISSION TO GOOGLE SHEETS
    // ---------------------------------------------------------
    if (millis() - lastLogTime >= LOG_INTERVAL_MS) {
      lastLogTime = millis();
      if (!dhtError) {
        
        // Determine Trigger Source based on Latch Flags
        String triggerSource = "OFF";
        if (flagAiTriggered && flagManualTriggered) {
          triggerSource = "HYBRID";
        } else if (flagAiTriggered) {
          triggerSource = "AI";
        } else if (flagManualTriggered) {
          triggerSource = "MANUAL";
        }
        
        // Transmit Accumulated Data to Cloud
        sendTelemetryToGoogle(airTemp, airHum, soilMois, rawSoilADCForCloud, triggerSource, hourlyCompletedBatchMl, totalWaterMl);
        
        // RESET LATCH FLAGS & ACCUMULATORS FOR THE NEXT INTERVAL
        hourlyCompletedBatchMl = 0.0; 
        flagAiTriggered        = false;
        flagManualTriggered    = false;
      }
    }
  }
}