
void gestures() {
  bool jerkx = false;
  bool jerky = false;
  bool jerkz = false;
  static int shake = 0;
  static int dshake = 0;
  bool debug = false;

  unsigned long currentMillis = millis();

  lsm.read();
  sensors_event_t a, m, g, temp;
  lsm.getEvent(&a, &m, &g, &temp);

  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;
  float gx = g.gyro.x;
  float gy = g.gyro.y;
  float gz = g.gyro.z;
  float mx = m.magnetic.x;
  float my = m.magnetic.y;
  float mz = m.magnetic.z;

  if (currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    dshake = 0;
  }

  if ((ax < 25 && ax > 15) || (ax < -15 && ax > -20)) {
    jerkx = true;
  }

  if ((ay < 25 && ay > 15) || (ay < -15 && ay > -20)) {
    jerky = true;
  }

  if ((az < 25 && az > 15) || (az < -15 && az > -20)) {
    jerkz = true;
  }

  if (jerkx == true && jerky == true || jerkx == true && jerkz == true || jerky == true && jerkz == true) {
    shake = shake + 1;
  }

  if (jerkx == true && jerky == true || jerkx == true && jerkz == true || jerky == true && jerkz == true) {
    dshake = dshake + 1;
  }

  if (shake == 1) {
    fillanimation(strip.Color(0,   0,   0, 255)     , 15); //
  }

  if (shake >= 2) {
    fillanimation(strip.Color(0,   0,   0)     , 15);
    shake = shake - 2;
  }

  if (dshake >= 2) {
    fillanimation(strip.Color(50,   0,   0)     , 15);
  }

  if (shake >= 2 && dshake >= 2) {
    fillanimation(strip.Color(0,   0,   50)     , 15);
  }

  if (debug == true) {
    Serial.print (jerkx);
    Serial.print (jerky);
    Serial.print (jerkz);
    Serial.print (shake);
    Serial.print(dshake);
    Serial.print(ax);
    Serial.print("          ");
  }
}

void setupSensor() {
  lsm.setupAccel(lsm.LSM9DS1_ACCELRANGE_2G);
  lsm.setupMag(lsm.LSM9DS1_MAGGAIN_4GAUSS);
  lsm.setupGyro(lsm.LSM9DS1_GYROSCALE_245DPS);
}
