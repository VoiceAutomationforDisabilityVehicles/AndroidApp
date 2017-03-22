#include <Stepper.h>
#include <Servo.h>

enum SystemState { INVALID = 0, OPEN_IN = 1, CLOSE = 2, OPEN_OUT = 3};

static SystemState currSystemState;
static SystemState requestedSystemState;

constexpr double preset_num_steps = 200*5.25;
constexpr int zero_servo_pos = 70;
constexpr int preset_servo_pos = 140;

bool validSystemState(SystemState wantedState){
  return wantedState == SystemState::OPEN_IN || wantedState == SystemState::CLOSE || wantedState == SystemState::OPEN_OUT;
}

Stepper motor(200,3,13,11,12);  
Servo servo;

void setup()
{
  /**
     H-BRIDGE B:
     -: Gray
     +: Green
     H-BRIDGE A:
     -: Yellow:
     +: Red:
  */
  Serial.begin(9600); 
  servo.attach(6,0,255);
  motor.setSpeed(50);
  currSystemState = SystemState::CLOSE;
  requestedSystemState  = SystemState::INVALID;
}

int cnttest = 0;

void loop()
{
  if (Serial.available() > 0){
    requestedSystemState = static_cast<SystemState>(Serial.read() - 48);
    Serial.print("Wanted State: " + static_cast<String>(requestedSystemState));
    Serial.print("Current State: " + static_cast<String>(currSystemState));
    if (!validSystemState(requestedSystemState)){
      requestedSystemState = SystemState::INVALID;
    }
  }
  else requestedSystemState = SystemState::INVALID;

  if (requestedSystemState == SystemState::OPEN_IN){
    Serial.print("Requested OPEN_IN");
    if (currSystemState == SystemState::OPEN_IN){
      return;
    }
    if (currSystemState == SystemState::OPEN_OUT){
      closeArm();
    }
    if (currSystemState == SystemState::CLOSE){
      openPos();
      delay(1000);
      closeArm();
    }
    currSystemState = SystemState::OPEN_IN;
  }

  if (requestedSystemState == SystemState::OPEN_OUT){
    if (currSystemState == OPEN_OUT){
      return;
    }
    if (currSystemState == SystemState::OPEN_IN){
      openArm();
    }
    if (currSystemState == SystemState::CLOSE){
      openPos();
      delay(1000);
      openArm();
    }
    currSystemState = SystemState::OPEN_OUT;
  }
  
  if (requestedSystemState == SystemState::CLOSE){
    if (currSystemState == SystemState::CLOSE){
      return;
    }
    if (currSystemState == SystemState::OPEN_IN){
      closePos();
    }
    if (currSystemState == SystemState::OPEN_OUT){
      closeArm();
      delay(1000);
      closePos();
    }
    currSystemState = SystemState::CLOSE;
  }
  cnttest++;
}

void openArm(){
  servo.write(preset_servo_pos);
}

void closeArm(){
  servo.write(zero_servo_pos);
}

void openPos(){
  motor.step(preset_num_steps);
}

void closePos(){
  motor.step(-preset_num_steps);
}

