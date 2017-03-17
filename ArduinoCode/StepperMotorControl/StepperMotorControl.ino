#include <Stepper.h>
#include <Servo.h>

enum Direction { STOP = 0, OPEN = 1, CLOSE = 2};
Direction requestedDirection = Direction::STOP;
constexpr int preset_num_steps = 200*4;

bool validDirection(Direction wantedDirection){
  return wantedDirection == Direction::STOP || wantedDirection == Direction::OPEN || wantedDirection == Direction::CLOSE;
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
  servo.attach(9,0,255);
  servo.write(90);
  motor.setSpeed(50);
}

void loop()
{
  if (Serial.available() > 0){
    requestedDirection = static_cast<Direction>(Serial.read() - 48);
    Serial.print("Wanted State: " + static_cast<String>(requestedDirection));
    if (!validDirection(requestedDirection)){
      requestedDirection = Direction::STOP;
    }
  }
  else requestedDirection = Direction::STOP;
  if (requestedDirection == OPEN){
    motor.step(preset_num_steps);
  }
  if (requestedDirection == CLOSE){
    motor.step(-preset_num_steps);
  }
}
