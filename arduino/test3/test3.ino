//Include the motor driver library
#include <AFMotor.h>
#include <SoftwareSerial.h> // Include the SoftwareSerial library
#define RX A0
#define TX A1

SoftwareSerial BTSerial(RX, TX);   // RX, TX pins for Bluetooth module

//Set the speed of the motors
#define motorSpeed 100
int errorX = 0;
int errorY = 0;

//Create objects for the motors
AF_DCMotor leftMotor1(1);
AF_DCMotor leftMotor2(2);
AF_DCMotor rightMotor2(3);
AF_DCMotor rightMotor1(4);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); // Initialize the Bluetooth module
}

void loop() {
  if (BTSerial.available()) {             // Check if there is data available from Bluetooth module
    // Read the serial data as a string
    String data = BTSerial.readStringUntil('\n');
    
    // Split the string into two parts (x and y)
    int commaIndex = data.indexOf(',');
    String xString = data.substring(0, commaIndex);
    String yString = data.substring(commaIndex + 1);
    
    // Convert the string values to integers
    errorX = xString.toInt();
    errorY = yString.toInt();
    
    // Print the (x, y) coordinate to the serial monitor
    Serial.print("Received coordinate: ");
    Serial.print(errorX);
    Serial.print(", ");
    Serial.println(errorY);
  }

  // Determine the motor speeds based on the error
  int leftMotorSpeed = motorSpeed;
  int rightMotorSpeed = motorSpeed;

    if (errorX > 7) {
    // The robot is to the left of the desired position
     rightMotorSpeed = motorSpeed - errorX;
  } else if (errorX < -7) {
    // The robot is to the right of the desired position
    leftMotorSpeed = motorSpeed + errorX;
  }

  if (errorY > 30) {
    // The robot is below the desired position
    leftMotorSpeed = motorSpeed + errorY/5;
    rightMotorSpeed = motorSpeed + errorY/5;
  }

  // Setting Speed
  leftMotor1.setSpeed(leftMotorSpeed );
  leftMotor2.setSpeed(leftMotorSpeed );
  rightMotor1.setSpeed(rightMotorSpeed );
  rightMotor2.setSpeed(rightMotorSpeed );

   if(errorY < 20 && errorX<7 && errorY >-7){
     Stop();
     Serial.println("stop");
     delay(500);
  }else {
     Run();
     Serial.println("Run");
     delay(500);
    
    }
}

void Run(){
  leftMotor1.run(FORWARD);
  leftMotor2.run(FORWARD);
  rightMotor1.run(FORWARD);
  rightMotor2.run(FORWARD);
  }

void Stop() {
  leftMotor1.run(RELEASE);
  leftMotor2.run(RELEASE);
  rightMotor1.run(RELEASE);
  rightMotor2.run(RELEASE);
}
