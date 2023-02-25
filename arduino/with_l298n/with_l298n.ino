//Include the motor driver library
#include <SoftwareSerial.h> // Include the SoftwareSerial library
#define RX A0
#define TX A1
SoftwareSerial BTSerial(RX, TX);   // RX, TX pins for Bluetooth module

// Motor Pins
#define LMEnable 9
#define LMForward 6
#define LMBackward 7
#define RMEnable 3
#define RMForward 5
#define RMBackward 4

//Set the speed of the motors
#define motorSpeed 120
int errorX = 0;
int errorY = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); // Initialize the Bluetooth module

  // Setting PinMode
  pinMode(LMEnable, OUTPUT);
  pinMode(LMForward, OUTPUT);
  pinMode(LMBackward, OUTPUT);
  pinMode(RMEnable, OUTPUT);
  pinMode(RMForward, OUTPUT);
  pinMode(RMBackward, OUTPUT);

  // Initialize
  digitalWrite(LMForward, LOW);
  digitalWrite(LMBackward, LOW);
  digitalWrite(RMForward, LOW);
  digitalWrite(RMBackward, LOW); 

  analogWrite(LMEnable, motorSpeed);
  analogWrite(RMEnable, motorSpeed);
}

void loop() {
  if (BTSerial.available()) {             
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

  // Fixing misleading values
  else{
    errorX = 0;
    errorY = 0;
    }
  if(errorY > 500 || errorX > 80 || errorX <-80) { 
    errorY = 0;
    errorX =0;
    }
  

  // Determine the motor speeds based on the error
  int leftMotorSpeed = motorSpeed;
  int rightMotorSpeed = motorSpeed;

  if (errorX > 20 && errorY>20) {
    // The robot is to the left of the desired position
     rightMotorSpeed = motorSpeed - (errorX-16);
     leftMotorSpeed = motorSpeed+(errorX-16);
  } else if (errorX < 10) {
    // The robot is to the right of the desired position
    leftMotorSpeed = motorSpeed - (16-errorX);
    rightMotorSpeed = motorSpeed+(16-errorX);
  }else if(errorY > 30) {
    // Motor should move forward
    leftMotorSpeed = motorSpeed + errorY/5;
    rightMotorSpeed = motorSpeed + errorY/5;
  }

  // Setting Speed
  analogWrite(LMEnable, leftMotorSpeed);
  analogWrite(RMEnable, rightMotorSpeed);
  
 if(errorY < 30 && errorX<7 && errorY >-7){
     Stop();
     Serial.println("stop");
     delay(50);
     
  }else {
     Run();
     Serial.println("Run");
     delay(50);
    
    }
}

void Run(){
   digitalWrite(LMBackward, HIGH);
   digitalWrite(RMBackward, HIGH);
  }

void Stop() {
   digitalWrite(LMBackward, LOW);
   digitalWrite(RMBackward, LOW);
}
