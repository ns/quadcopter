#include <Wire.h>
#include "Engines.h"
#include "IMU.h"
#include "Gyro.h"
#include "Accel.h"

Gyro gyro;
Accel accel;
IMU imu;
Engines engines;

unsigned long previousTime = 0;
unsigned long currentTime = 0;
unsigned long deltaTime = 0;
//unsigned long serialTime = 0;
//unsigned long activityTime = 0;

boolean flightControlEnabled;

void setup() {
  Serial.begin(57600);
  
  previousTime = micros();
  flightControlEnabled = true;
  
  gyro.init();
  accel.init();
  engines.init();
}

void loop() {
  currentTime = micros();
  deltaTime = currentTime - previousTime;
  previousTime = currentTime;
  
  if (Serial.available()) {
    processSerialInput();
  }
  
  //Serial.println("test");
  
  gyro.updateAll();
  accel.updateAll();
  imu.update(deltaTime/1000, gyro.getRoll(), gyro.getPitch(), gyro.getYaw(), accel.getYAngle(), accel.getXAngle(), accel.getZAngle(), 0);
  
  if (flightControlEnabled) {
    processFlightControl();
  }
  
  delay(50);
}

void processSerialInput() {
  String cmd = readNextStringTerm();
  
  if (cmd == "throttle") {
    int speed = readNextIntTerm();
    engines.setThrottle(speed);
    Serial.println("ok");
  }
  else if (cmd == "e") {
    String engine = readNextStringTerm();
    int speed = readNextIntTerm() + MIN_MOTOR_SPEED;
    
    if (engine == "fl") {
      engines.setEngineSpeed(LEFT_FRONT_MOTOR, speed);
    }
    else if (engine == "fr") {
      engines.setEngineSpeed(RIGHT_FRONT_MOTOR, speed);
    }
    else if (engine == "bl") {
      engines.setEngineSpeed(LEFT_REAR_MOTOR, speed);
    }
    else if (engine == "br") {
      engines.setEngineSpeed(RIGHT_REAR_MOTOR, speed);
    }
    else {
      Serial.println("what engine? - " + engine);
    }
    
    Serial.println("ok");
  }
  else if (cmd == "calibhigh") { // Calibrate ESCS's by setting Throttle high on all channels
    engines.disarm();
    engines.arm(1);
    Serial.println("ok");
  }
  else if (cmd == "caliblow") { // Calibrate ESC's by setting Throttle low on all channels
    engines.disarm();
    engines.arm(2);
    Serial.println("ok");
  }
  else if (cmd == "testcalib") { // Test ESC calibration
    engines.disarm();
    //engines.setThrottle(constrain(readFloatSerial(), 1000, 1200));
  }
  else if (cmd == "escoff") { // Turn off ESC calibration
    engines.disarm();
  }
  else if (cmd == "fc") { // Turn off ESC calibration
    String state = readNextStringTerm();
    if (state == "on") {
      flightControlEnabled = true;
      Serial.println("flight control on");
    }
    else {
      flightControlEnabled = false;
      Serial.println("flight control off");
    }
  }
  else if (cmd == "status") {
    serialPrintValueComma(gyro.getRoll());
    serialPrintValueComma(gyro.getPitch());
    serialPrintValueComma(gyro.getYaw());
    
    serialPrintValueComma(accel.getRoll());
    serialPrintValueComma(accel.getPitch());
    serialPrintValueComma(accel.getYaw());
    
//    serialPrintValueComma(mag.getRaw(XAXIS));
//    serialPrintValueComma(mag.getRaw(YAXIS));
//    serialPrintValueComma(mag.getRaw(ZAXIS));
    
    serialPrintValueComma(imu.getRoll());
    serialPrintValueComma(imu.getPitch());
    Serial.println();
  }
  else {
    Serial.println("UNKNOWN cmd = " + cmd);
  }
}

String readNextStringTerm() {
  String term = String();
  while (int data = Serial.read()) {
    if (data == 10 || data == 32) { // new line, space
      return term;
    }
    else if (data != -1) {
      term += (char)data;
    }
    else {
      delay(10);
    }
  }
}

int readNextIntTerm() {
  String term = readNextStringTerm();
  char this_char[term.length() + 1];
  term.toCharArray(this_char, sizeof(this_char));
  return atoi(this_char);
}

void serialPrintValueComma(float val){
  Serial.print(val);
  serialComma();
}

void serialPrintValueComma(double val){
  Serial.print(val);
  serialComma();
}

void serialPrintValueComma(char val){
  Serial.print(val);
  serialComma();
}

void serialPrintValueComma(int val){
  Serial.print(val);
  serialComma();
}

void serialPrintValueComma(unsigned long val){
  Serial.print(val);
  serialComma();
}

void serialComma(){
  Serial.print(',');
}
