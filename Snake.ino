#include "Wire.h" 
#include "LedControl.h"
#include "binary.h"
byte bf[8] = { B00000000, B01100110, B01100110, B00000000, B00000000, B01000010, B00111100, B00000000};
byte cf[8] = { B00000000, B01100110, B01100110, B00000000, B00000000, B01000010, B01000010, B00111100};
byte df[8] = { B00000000, B01100110, B01100110, B00000000, B00000000, B00000000, B01111110, B00000000};
byte af[8] = { B00000000, B01100110, B01100110, B00000000, B00000000, B00111100, B01000010, B01000010};
boolean play = true;
int points = 0;
int xVar = 4;
int yVar = 4;
int x[8] = { 3, -1, -1, -1, -1, -1};
int y[8] = { 3, -1, -1, -1, -1, -1};
int xApple = random(0, 7);
int yApple = random(0, 7);
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
LedControl lc = LedControl(16, 4, 5, 1);
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
void setup() {
  lc.shutdown(0, false);
  lc.setIntensity(0, 8); //initiallize the display 
  lc.clearDisplay(0);
  Serial.begin(9600);
  Wire.begin(0, 2);
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
}
void newX(int xVar) {
  x[4] = x[3];
  x[3] = x[2];
  x[2] = x[1];
  x[1] = x[0];
  x[0] = xVar;
}
// new x position 
void newY(int yVar) {
  y[4] = y[3];
  y[3] = y[2];
  y[2] = y[1];
  y[1] = y[0];
  y[0] = yVar;
}
// new y position 
void Reset() {
  points = 0;
  xVar = 4;
  yVar = 4;
  y[4] = -1;
  y[3] = -1;
  y[2] = -1;
  y[1] = -1;
  y[0] = -1;
  x[4] = -1;
  x[3] = -1;
  x[2] = -1;
  x[1] = -1;
  x[0] = -1;
}
// reset variables 
void win() {
  lc.setRow(0, 0, bf[0]);
  lc.setRow(0, 1, bf[1]);
  lc.setRow(0, 2, bf[2]);
  lc.setRow(0, 3, bf[3]);
  lc.setRow(0, 4, bf[4]);
  lc.setRow(0, 5, bf[5]);
  lc.setRow(0, 6, bf[6]);
  lc.setRow(0, 7, bf[7]);
  delay(500);
  lc.setRow(0, 0, af[0]);
  lc.setRow(0, 1, cf[1]);
  lc.setRow(0, 2, cf[2]);
  lc.setRow(0, 3, cf[3]);
  lc.setRow(0, 4, cf[4]);
  lc.setRow(0, 5, cf[5]);
  lc.setRow(0, 6, cf[6]);
  lc.setRow(0, 7, cf[7]);
  delay(500);
  lc.setRow(0, 0, bf[0]);
  lc.setRow(0, 1, bf[1]);
  lc.setRow(0, 2, bf[2]);
  lc.setRow(0, 3, bf[3]);
  lc.setRow(0, 4, bf[4]);
  lc.setRow(0, 5, bf[5]);
  lc.setRow(0, 6, bf[6]);
  lc.setRow(0, 7, bf[7]);
  delay(500);
  lc.setRow(0, 0, af[0]);
  lc.setRow(0, 1, cf[1]);
  lc.setRow(0, 2, cf[2]);
  lc.setRow(0, 3, cf[3]);
  lc.setRow(0, 4, cf[4]);
  lc.setRow(0, 5, cf[5]);
  lc.setRow(0, 6, cf[6]);
  lc.setRow(0, 7, cf[7]);
  delay(500);
}
// happy face animation 
void lose() {
  lc.setRow(0, 0, af[0]);
  lc.setRow(0, 1, af[1]);
  lc.setRow(0, 2, af[2]);
  lc.setRow(0, 3, af[3]);
  lc.setRow(0, 4, af[4]);
  lc.setRow(0, 5, af[5]);
  lc.setRow(0, 6, af[6]);
  lc.setRow(0, 7, af[7]);
  delay(500);
  lc.setRow(0, 0, df[0]);
  lc.setRow(0, 1, df[1]);
  lc.setRow(0, 2, df[2]);
  lc.setRow(0, 3, df[3]);
  lc.setRow(0, 4, df[4]);
  lc.setRow(0, 5, df[5]);
  lc.setRow(0, 6, df[6]);
  lc.setRow(0, 7, df[7]);
  delay(500);
  lc.setRow(0, 0, af[0]);
  lc.setRow(0, 1, af[1]);
  lc.setRow(0, 2, af[2]);
  lc.setRow(0, 3, af[3]);
  lc.setRow(0, 4, af[4]);
  lc.setRow(0, 5, af[5]);
  lc.setRow(0, 6, af[6]);
  lc.setRow(0, 7, af[7]);
  delay(500);
  lc.setRow(0, 0, df[0]);
  lc.setRow(0, 1, df[1]);
  lc.setRow(0, 2, df[2]);
  lc.setRow(0, 3, df[3]);
  lc.setRow(0, 4, df[4]);
  lc.setRow(0, 5, df[5]);
  lc.setRow(0, 6, df[6]);
  lc.setRow(0, 7, df[7]);
  delay(500);
}
// happy face animation
void check() {
  for (int t = 1; t <= points; t++) {
    if ((xVar == x[t]) && (yVar == y[t])) {
      lc.clearDisplay(0);
      Reset();
      lose();
    }
  }
}
// check for collision 
void loop() {
  lc.clearDisplay(0);
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  temperature = Wire.read() << 8 | Wire.read(); // reading registers: 0x41 (TEMP_OUT_H) and 0x42 (TEMP_OUT_L)
  gyro_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x43 (GYRO_XOUT_H) and 0x44 (GYRO_XOUT_L)
  gyro_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x45 (GYRO_YOUT_H) and 0x46 (GYRO_YOUT_L)
  gyro_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x47 (GYRO_ZOUT_H) and 0x48 (GYRO_ZOUT_L)

  if ((xVar <= 6) && (accelerometer_x <= -4300)) {
    xVar++;
    newX(xVar);
    newY(yVar);
    check();
  }
  else if  ((xVar >= 1) && (accelerometer_x >= 4300))  {
    xVar--;
    newX(xVar);
    newY(yVar);
    check();
  }
  else if ((yVar <= 6) && (accelerometer_y <= -4300)) {
    yVar++;
    newX(xVar);
    newY(yVar);
    check();
  }
  else if  ((yVar >= 1) && (accelerometer_y >= 4300))  {
    yVar--;
    newX(xVar);
    newY(yVar);
    check();
  }

  if ((xVar == xApple) && (yVar == yApple)) {
    if (points == 5) {
      lc.clearDisplay(0);
      Reset();
      win();
    }
    else  {
      xApple = random(0, 7);
      yApple = random(0, 7);
      points++;
    }
  }

  for (int i = 0; i <= points; i++) {
    lc.setLed(0, x[i], y[i], true);
  }
  lc.setLed(0, xApple, yApple, true);
  delay(300);
}
