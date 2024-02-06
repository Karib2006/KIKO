#define IR_SENSOR_RIGHT 11
#define IR_SENSOR_LEFT 12
#define IR_SENSOR_LEFTMOST 3
#define IR_SENSOR_RIGHTMOST 4
#define MOTOR_SPEED 140
#define NormalTurn 155
#define BigTurn  230
#define OuterTurn 180
#define time 1400
#define smallTime 100

//Right motor
int enableRightMotor=6;
int rightMotorPin1=7;
int rightMotorPin2=8;

//Left motor
int enableLeftMotor=5;
int leftMotorPin1=9;
int leftMotorPin2=10;

void setup()
{
  //The problem with TT gear motors is that, at very low pwm value it does not even rotate.
  //If we increase the PWM value then it rotates faster and our robot is not controlled in that speed and goes out of line.
  //For that we need to increase the frequency of analogWrite.
  //Below line is important to change the frequency of PWM signal on pin D5 and D6
  //Because of this, motor runs in controlled manner (lower speed) at high PWM value.
  //This sets frequecny as 7812.5 hz.
  
  TCCR0B = TCCR0B & B11111000 | B00000010 ;
  
  // put your setup code here, to run once:
  pinMode(enableRightMotor, OUTPUT);
  pinMode(rightMotorPin1, OUTPUT);
  pinMode(rightMotorPin2, OUTPUT);
  
  pinMode(enableLeftMotor, OUTPUT);
  pinMode(leftMotorPin1, OUTPUT);
  pinMode(leftMotorPin2, OUTPUT);

  pinMode(IR_SENSOR_RIGHT, INPUT);
  pinMode(IR_SENSOR_LEFT, INPUT);
  rotateMotor(0,0);   
}


void loop()
{

  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);
  int rightMostIRSensorValue = digitalRead(IR_SENSOR_RIGHTMOST);
  int leftMostIRSensorValue = digitalRead(IR_SENSOR_LEFTMOST);

  //If both the sensors detect black line, then stop 
  if(rightIRSensorValue == HIGH && leftIRSensorValue == HIGH){
    rotateMotor(-100,-100);
  }
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == HIGH && rightMostIRSensorValue == HIGH && leftMostIRSensorValue == HIGH){
     rotateMotor(0,0);
  }
    // If LeftMost and left sensor active then max turn 
  else if (leftMostIRSensorValue == HIGH && leftIRSensorValue == HIGH ){
    rotateMotor(BigTurn, -BigTurn);
    delay(time);
  }

  //If RightMost and Right sensor active then max turn
  else if (rightMostIRSensorValue == HIGH && rightIRSensorValue == HIGH){
    rotateMotor(-BigTurn, BigTurn);
    delay(time);
  }
  // IF LeftMost Sensor active
  else if(leftMostIRSensorValue == HIGH && rightIRSensorValue == LOW && leftIRSensorValue == LOW && rightMostIRSensorValue == LOW){
    rotateMotor(OuterTurn, -OuterTurn);
    delay(time);
  }

  // IF RightMost Sensor active
  else if(rightMostIRSensorValue == HIGH && rightIRSensorValue == LOW && leftIRSensorValue == LOW && leftMostIRSensorValue == LOW){
   rotateMotor(-OuterTurn, OuterTurn);
   delay(time);
  }
  //If none of the sensors detects black line, then go straight
  else if (rightIRSensorValue == LOW && leftIRSensorValue == LOW)
  {
    rotateMotor(MOTOR_SPEED, (MOTOR_SPEED+30));
  }
  //If right sensor detects black line, then turn right
  else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW )
  {
      rotateMotor(-NormalTurn, NormalTurn); 
      delay(smallTime);
  }
  //If left sensor detects black line, then turn left  
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH )
  {
      rotateMotor(NormalTurn, -NormalTurn); 
      delay(smallTime);
  } 

  //Exceptions
  else if(leftMostIRSensorValue == HIGH && rightIRSensorValue == LOW && leftIRSensorValue == HIGH && rightMostIRSensorValue == LOW){
     rotateMotor(OuterTurn, -OuterTurn);
     delay(time);
   }

   // IF RightMost Sensor active
   else if(rightMostIRSensorValue == HIGH && rightIRSensorValue == LOW && leftIRSensorValue == HIGH && leftMostIRSensorValue == LOW){
     rotateMotor(-OuterTurn, OuterTurn);
     delay(time);
   }
}


void rotateMotor(int rightMotorSpeed, int leftMotorSpeed)
{
  
  if (rightMotorSpeed < 0)
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,HIGH);    
  }
  else if (rightMotorSpeed > 0)
  {
    digitalWrite(rightMotorPin1,HIGH);
    digitalWrite(rightMotorPin2,LOW);      
  }
  else
  {
    digitalWrite(rightMotorPin1,LOW);
    digitalWrite(rightMotorPin2,LOW);      
  }

  if (leftMotorSpeed < 0)
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,HIGH);    
  }
  else if (leftMotorSpeed > 0)
  {
    digitalWrite(leftMotorPin1,HIGH);
    digitalWrite(leftMotorPin2,LOW);      
  }
  else 
  {
    digitalWrite(leftMotorPin1,LOW);
    digitalWrite(leftMotorPin2,LOW);      
  }
  analogWrite(enableRightMotor, abs(rightMotorSpeed));
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    
}

// Sensor Check
// const int leftMostSensorPin = 3;
// const int middleLeftSensorPin = 12;
// const int rightMostSensorPin = 4;
// const int middleRightSensorPin = 11;

// void setup() {
//   Serial.begin(9600);
//   pinMode(leftMostSensorPin, INPUT);
//   pinMode(middleLeftSensorPin, INPUT);
//   pinMode(rightMostSensorPin, INPUT);
//   pinMode(middleRightSensorPin, INPUT);
// }

// void loop() {
//   int leftMostValue = digitalRead(leftMostSensorPin);
//   int middleLeftValue = digitalRead(middleLeftSensorPin);
//   int rightMostValue = digitalRead(rightMostSensorPin);
//   int middleRightValue = digitalRead(middleRightSensorPin);

//   Serial.print("Left Most Sensor: ");
//   Serial.print(leftMostValue);
  
//   Serial.print("\t Middle Left Sensor: ");
//   Serial.print(middleLeftValue);

//   Serial.print("\t Right Most Sensor: ");
//   Serial.print(rightMostValue);

//   Serial.print("\t Middle Right Sensor: ");
//   Serial.println(middleRightValue);

//   delay(500); // Adjust the delay as needed
// }
