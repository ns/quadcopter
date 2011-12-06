#include "Engines.h"

Engines::Engines() {  
  // Setup engines
  engines[LEFT_FRONT_MOTOR] = LEFT_FRONT_MOTOR_PIN;
  engines[RIGHT_FRONT_MOTOR] = RIGHT_FRONT_MOTOR_PIN;
  engines[LEFT_REAR_MOTOR] = LEFT_REAR_MOTOR_PIN;
  engines[RIGHT_REAR_MOTOR] = RIGHT_REAR_MOTOR_PIN;
}

void Engines::init() {
  //allStop();
}

void Engines::allStop() {
  throttle = 0;
  setAllSpeed(0);
}

void Engines::setEngineSpeed(int engine, int speed) {
  speed = constrain(speed, MIN_MOTOR_SPEED, MAX_MOTOR_SPEED);
  
  // Analog write supports commands from 0-255 => 0 - 100% duty cycle
  // Using 125-250 for motor setting 1000-2000
  analogWrite(engines[engine], speed / 8);
  
//  Serial.println(speed, DEC);
  
  //Serial.println(engines[engine], DEC);
  //Serial.println(" -> " + speed);
  
  
  engine_speeds[engine] = speed;
}

int Engines::getEngineSpeed(int engine) {
  return engine_speeds[engine];
}

void Engines::setAllSpeed(int speed) {
  for (int engine = 0; engine < 4; engine++) {
    setEngineSpeed(engine, speed);
  }
}

void Engines::setThrottle(int new_throttle) {
  throttle = new_throttle;
}

int Engines::getThrottle() {
  return throttle;
}

void Engines::arm(int method) {
  if (_armed) return;
  
  Serial.println("arming");
  
  switch (method){
    case 1:
      setAllSpeed(MAX_MOTOR_SPEED);
      break;
    default:
      setAllSpeed(MIN_MOTOR_SPEED);
  }

  _armed = true;
}

void Engines::disarm() {
  if (!_armed) return;
  
  Serial.println("disarming");
  
  setThrottle(0);
  allStop();
  
  _armed = false;
}

boolean Engines::isArmed() {
  return _armed;
}
