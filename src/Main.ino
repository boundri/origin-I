#include "Adafruit_VL53L0X.h"
#include "Adafruit_DRV2605.h"
#ifdef __AVR__
#include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS1.h>
#include <Adafruit_Sensor.h>  // not used in this demo but required!
//#include <SensorFusion.h>
#include "Arduino.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN     6
#define LED_COUNT  60
#define BRIGHTNESS 50

#define LSM9DS1_SCK A5
#define LSM9DS1_MISO 12
#define LSM9DS1_MOSI A4
#define LSM9DS1_XGCS 6
#define LSM9DS1_MCS 5

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);
Adafruit_LSM9DS1 lsm = Adafruit_LSM9DS1();

Adafruit_DRV2605 drv;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();

long previousMillis = 0;
long interval = 350;

float ax;
float ay;
float az;
float gx;
float gy;
float gz;
float mx;
float my;
float mz;

//float pitch;
//float roll;
//float yaw;
//SF fusion;

void setup() {
  Serial.begin(115200);
  strip.clear();
  strip.begin();

  drv.begin();
  drv.selectLibrary(1);
  drv.setMode(DRV2605_MODE_INTTRIG);

  startanimation(strip.Color(50,   0,   0)     , 15);
  startanimation(strip.Color(0,   50,   0)     , 15);
  startanimation(strip.Color(0,   0,   50)     , 15);
  startanimation(strip.Color(0,   0,   0)     , 15);


  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
  }

  if (!lsm.begin()) {
    Serial.println("Failed to boot LSM9DS1");
    while (1);
  }
  setupSensor();
}

void loop() {
  hfeed ();
  gestures();
  //orientation();
}
