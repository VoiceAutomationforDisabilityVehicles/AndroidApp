class StepperMotor{
  public:
    enum Direction{ CLOCKWISE, COUNTERCLOCKWISE };
    StepperMotor(int brake_a, int brake_b, int dir_a, int dir_b, int pwm_a, int pwm_b);
    void initialize();
    void update_test_run(Direction d);
  private:
    int brake_a, brake_b, dir_a, dir_b, pwm_a, pwm_b;
    constexpr int delay_time = 5;
};

StepperMotor::StepperMotor(int brake_a, int brake_b, int dir_a, int dir_b, int pwm_a, int pwm_b){
  this->brake_a = brake_a;
  this->brake_b = brake_b;
  this->dir_a = dir_a;
  this->dir_b = dir_b;
  this->pwm_a = pwm_a;
  this->pwm_b = pwm_b;
}

void StepperMotor::initialize(){
  pinMode(brake_a, OUTPUT);
  pinMode(brake_b, OUTPUT);
  pinMode(dir_a, OUTPUT);
  pinMode(dir_b, OUTPUT);
}

void StepperMotor::update_test_run(StepperMotor::Direction wantedDirection){
    //Power first coil
  digitalWrite(brake_a, LOW);  
  digitalWrite(brake_b, HIGH); 
  digitalWrite(dir_a, HIGH); 
  analogWrite(pwm_a, 255);  
  delay(delay_time);
  //Power second coil with reverse polarity
  digitalWrite(brake_a, HIGH); 
  digitalWrite(brake_b, LOW);
  digitalWrite(dir_b, wantedDirection == CLOCKWISE ? LOW : HIGH);
  analogWrite(pwm_b, 255); 
  delay(delay_time);
  //Power first coil with reverse polarity
  digitalWrite(brake_a, LOW); 
  digitalWrite(brake_b, HIGH); 
  digitalWrite(dir_a, LOW); 
  analogWrite(pwm_a, 255);  
  delay(delay_time);
  //Power second coil
  digitalWrite(brake_a, HIGH);  
  digitalWrite(brake_b, LOW); 
  digitalWrite(dir_b, wantedDirection == CLOCKWISE ? HIGH : LOW); 
  analogWrite(pwm_b, 255); 
  delay(delay_time);
}

constexpr int ENABLE_A_PIN = 9;
constexpr int ENABLE_B_PIN = 8;
constexpr int DIRECTION_A_PIN = 12;
constexpr int DIRECTION_B_PIN = 13;
constexpr int PWM_A_PIN = 3;
constexpr int PWM_B_PIN = 11;



StepperMotor stepper(ENABLE_A_PIN, ENABLE_B_PIN, DIRECTION_A_PIN, DIRECTION_B_PIN, PWM_A_PIN, PWM_B_PIN);
void setup() {
  /**
   * H-BRIDGE B:
   * -: Gray
   * +: Green
   * H-BRIDGE A:
   * -: Yellow:
   * +: Red:
    */
    stepper.initialize();  
}

void loop(){
    stepper.update_test_run(StepperMotor::Direction::COUNTERCLOCKWISE);
}


