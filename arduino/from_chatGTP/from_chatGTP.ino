// Define the pins for the motor driver
int leftMotorForwardPin = 9;
int leftMotorBackwardPin = 10;
int rightMotorForwardPin = 6;
int rightMotorBackwardPin = 5;

// Define the motor speed
int motorSpeed = 100;

// Define the desired x and y coordinates
int desiredX = 50;
int desiredY = 100;

void setup() {
  // Set the motor driver pins as output pins
  pinMode(leftMotorForwardPin, OUTPUT);
  pinMode(leftMotorBackwardPin, OUTPUT);
  pinMode(rightMotorForwardPin, OUTPUT);
  pinMode(rightMotorBackwardPin, OUTPUT);
}

void loop() {
  // Read the current x and y coordinates
  int currentX = analogRead(A0);
  int currentY = analogRead(A1);
  
  // Calculate the error in the x and y coordinates
  int errorX = desiredX - currentX;
  int errorY = desiredY - currentY;

  // Determine the motor speeds based on the error
  int leftMotorSpeed = motorSpeed;
  int rightMotorSpeed = motorSpeed;

  if (errorX > 0) {
    // The robot is to the left of the desired position
    leftMotorSpeed = motorSpeed - errorX;
  } else if (errorX < 0) {
    // The robot is to the right of the desired position
    rightMotorSpeed = motorSpeed + errorX;
  }

  if (errorY > 0) {
    // The robot is below the desired position
    leftMotorSpeed = motorSpeed + errorY;
  } else if (errorY < 0) {
    // The robot is above the desired position
    rightMotorSpeed = motorSpeed - errorY;
  }

  // Set the motor speeds
  analogWrite(leftMotorForwardPin, leftMotorSpeed);
  analogWrite(leftMotorBackwardPin, 0);
  analogWrite(rightMotorForwardPin, rightMotorSpeed);
  analogWrite(rightMotorBackwardPin, 0);
}
