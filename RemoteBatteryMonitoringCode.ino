// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID "TMPxxx-xxx-xxx"
#define BLYNK_DEVICE_NAME "Smart IoT"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_SPARKFUN_BLYNK_BOARD
#define USE_NODE_MCU_BOARD
//#define USE_WITTY_CLOUD_BOARD
//#define USE_WEMOS_D1_MINI

#include "BlynkEdgent.h"
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET_PIN -1   // Reset pin # (or -1 if sharing Arduino reset pin)

#define DHT_SENSOR_TYPE DHT22   // DHT 22
#define DHT_SENSOR_PIN D4       // DHT22 Pin D4(GPIO 2)


DHT climateSensor(DHT_SENSOR_PIN, DHT_SENSOR_TYPE);
Adafruit_SSD1306 oledDisplay(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET_PIN);

float batteryVoltage;
int batteryLevel;
int batteryAnalogPin = A0;    // Analog input pin
int rawAnalogValue;
float voltageOffset = 0.40;   // Check Battery voltage using multimeter & add/subtract the value



void setup()
{
  Serial.begin(115200);
  delay(100);

  BlynkEdgent.begin();

  climateSensor.begin();
  oledDisplay.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  oledDisplay.clearDisplay();
  oledDisplay.setTextColor(WHITE);

  delay(100);
}

void loop() {
  BlynkEdgent.run();
  float temperature = climateSensor.readTemperature();
  float humidity = climateSensor.readHumidity();

  rawAnalogValue = analogRead(batteryAnalogPin);
  batteryVoltage = (((rawAnalogValue * 3.3) / 1024) * 2 + voltageOffset); 

  batteryLevel = mapfloat(batteryVoltage, 2.8, 4.2, 0, 100);

  if (batteryLevel >= 100)
  {
    batteryLevel = 100;
  }
  if (batteryLevel <= 0)
  {
    batteryLevel = 1;
  }
  
  //send data to blynk
  Blynk.virtualWrite(V1, temperature);
  Blynk.virtualWrite(V2, humidity);
  Blynk.virtualWrite(V3, batteryVoltage);
  Blynk.virtualWrite(V4, batteryLevel);
  
  //Print data on serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Analog Value = ");
  Serial.println(rawAnalogValue);
  Serial.print("Output Voltage = ");
  Serial.println(batteryVoltage);
  Serial.print("Battery Percentage = ");
  Serial.println(batteryLevel);

  Serial.println();
  Serial.println("****************************");
  Serial.println();
  delay(1000);
 
  if (batteryLevel <= 30)
  {
    Serial.println("Battery level below 30%, Charge battery on time");
    Blynk.logEvent("battery_low", "Battery is getting low.... Plugin to charge") ;
    delay(500);
  }

  // display temperature on OLED
  oledDisplay.clearDisplay();
  oledDisplay.setTextColor(WHITE);
  oledDisplay.setTextSize(1);
  oledDisplay.setCursor(0, 0);
  oledDisplay.print("Temperature: ");
  oledDisplay.setTextSize(2);
  oledDisplay.setCursor(0, 10);
  oledDisplay.print(temperature);
  oledDisplay.print(" ");
  oledDisplay.setTextSize(1);
  oledDisplay.cp437(true);
  oledDisplay.write(167);
  oledDisplay.setTextSize(2);
  oledDisplay.print("C");

  // display humidity on OLED
  oledDisplay.setTextSize(1);
  oledDisplay.setCursor(0, 35);
  oledDisplay.print("Humidity: ");
  oledDisplay.setTextSize(2);
  oledDisplay.setCursor(0, 45);
  oledDisplay.print(humidity);
  oledDisplay.print(" %");

  oledDisplay.display();
  delay(1500);
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
