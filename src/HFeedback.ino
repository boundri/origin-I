#include "Adafruit_VL53L0X.h"
#include "Adafruit_DRV2605.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Adafruit_DRV2605 drv;

void setup() {
  
  // Opens serial connection 
  Serial.begin(115200);

  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  // Tests distance sensor 
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }

  // Activates distance sensor 
  drv.begin();

  // Set Real-Time Playback mode
  drv.setMode(DRV2605_MODE_REALTIME);

}

long range = 0;
uint16_t force = 0;

void loop() {

  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    
    if (measure.RangeMilliMeter < 750) {
      range = 75 - round(measure.RangeMilliMeter * 100 / 750) + 25;
      drv.setRealtimeValue(range);
      Serial.println(range);
      Serial.println(measure.RangeMilliMeter);
    }

  } else {
    Serial.println(" out of range ");
    drv.setRealtimeValue(0);
  }

}