#include "PID.h"

// For tuning, see: http://en.wikipedia.org/wiki/PID_controller#Manual_tuning
PID levelRollPID = PID(6.1, 0.0, 0.9);
PID levelPitchPID = PID(6.1, 0.0, 0.9);
PID headingHoldPID = PID(6.0, 0, 0.0);


float currentRoll = 0.0;
float currentPitch = 0.0;
float currentHeading = 0.0;

// Level flight assumed
float targetRoll = 0.0;
float targetPitch = 0.0;
float targetHeading = 0.0;

void processFlightControl(){
  
  currentRoll = imu.getRoll();
  currentPitch = imu.getPitch();
  currentHeading = imu.getHeading();
  
  //
  // Don't adjust pitch/roll if we are not armed!
  //
  
  if (engines.isArmed()){
     
    //
    // Panic!
    //
    
    if (currentRoll > 90 || currentRoll < -90 || currentPitch > 90 || currentPitch < -90){
      engines.disarm();
    }
    
    float G_Dt = deltaTime / 1000000.0; // Delta time in seconds

    // What does the receiver say?
    // TODO: Pull these from FlightCommand so that autopilot can adjust them
    targetRoll = 0;//receiver.getAngle(ROLL_CHANNEL);
    targetPitch = 0;//receiver.getAngle(PITCH_CHANNEL);
    targetHeading = 0;//receiver.getAngle(YAW_CHANNEL);
    
    // Negative values mean the right side is up
    // Constrain to 45 degrees, because beyond that, we're fucked anyway
    float rollAdjust = levelRollPID.updatePID(targetRoll, constrain(currentRoll, -50, 50), G_Dt);
    
    // Positive values mean the frontend is up
    // Constrain to 45 degrees, because beyond that, we're fucked anyway
    float pitchAdjust = levelPitchPID.updatePID(targetPitch, constrain(currentPitch, -50, 50), G_Dt);
    
    // Positive values are to the right
    float headingAdjust = headingHoldPID.updatePID(targetHeading, currentHeading, G_Dt);
    
    // Apply offsets to all motors evenly to ensure we pivot on the center
    int throttle = engines.getThrottle() + MIN_MOTOR_SPEED;
    if (throttle > MIN_MOTOR_SPEED){
      engines.setEngineSpeed(LEFT_FRONT_MOTOR, throttle - rollAdjust - pitchAdjust + headingAdjust);
      engines.setEngineSpeed(RIGHT_FRONT_MOTOR, throttle + rollAdjust - pitchAdjust - headingAdjust);
      engines.setEngineSpeed(LEFT_REAR_MOTOR, throttle - rollAdjust + pitchAdjust - headingAdjust);
      engines.setEngineSpeed(RIGHT_REAR_MOTOR, throttle + rollAdjust + pitchAdjust + headingAdjust);
    }
    else{
      engines.setAllSpeed(50);
    }
    
    /*Serial.print(targetPitch);
    Serial.print(" | ");
    Serial.print(currentPitch);
    Serial.print(" | ");
    Serial.println(pitchAdjust);*/
    //delay(100);
  }
  else{
    // Reset state
    levelRollPID.resetError();
    levelPitchPID.resetError();
    headingHoldPID.resetError();
  }
}
