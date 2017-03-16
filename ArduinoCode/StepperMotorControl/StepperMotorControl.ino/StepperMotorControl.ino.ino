#include <Stepper.h>

enum Direction { STOP = 0, CLOCKWISE = 1, COUNTERCLOCKWISE = 2};
Direction requestedDirection = Direction::STOP;
constexpr int preset_num_steps = 200;

bool validDirection(Direction wantedDirection){
  return wantedDirection == Direction::STOP || wantedDirection == Direction::CLOCKWISE || wantedDirection == Direction::COUNTERCLOCKWISE;
}

Stepper motor(200,3,13,11,12);  

 
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
  motor.setSpeed(30);
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
  if (requestedDirection == CLOCKWISE){
    motor.step(preset_num_steps);
  }
  if (requestedDirection == COUNTERCLOCKWISE){
    motor.step(-preset_num_steps);
  }
}
