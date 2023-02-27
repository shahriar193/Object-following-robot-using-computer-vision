//Include the motor driver library
#include <SoftwareSerial.h> // Include the SoftwareSerial library
#define RX A0
#define TX A1
SoftwareSerial BTSerial(RX, TX);   // RX, TX pins for Bluetooth module

// Motor Pins
#define LMEnable 9
#define LMBackward 6
#define LMForward 7
#define RMEnable 3
#define RMBackward 5
#define RMForward 4

//Set the speed of the motors
#define motorSpeed 130

int Ythres = 30;
int Xthres = 10;

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
    errorY = yString.toInt();
    errorX = xString.toInt();
    
    // Print the (x, y) coordinate to the serial monitor
    Serial.print("Received coordinate: ");
    Serial.print(errorX);
    Serial.print(", ");
    Serial.println(errorY);
  } else{
      errorX = 0;
      errorY = 0;
    }
    // Fixing misleading values
  if(errorY > 800 || errorX > 200 || errorX <-200) { 
    errorY = 0;
    errorX =0;
    }
  
  // Determine the motor speeds based on the error
  int leftMotorSpeed = motorSpeed;
  int rightMotorSpeed = motorSpeed;

  // Speed error correction while turning
  int delta = 0;
  if(abs(errorY) > 400){
     delta = abs(errorX)*0.5;
   }else if(abs(errorY)>300){
    delta = abs(errorX)*0.8;
    }else if(abs(errorY)>200){
    delta = abs(errorX)*1.6;
    }else if(abs(errorY)>100){
    delta = abs(errorX)*2;
    }else if(abs(errorY)<100 && abs(errorY)> Ythres){
    delta = abs(errorX)*3.2;
    }
  
  if (errorX > 10) {
    // The robot is to the left of the desired position
    leftMotorSpeed = motorSpeed + delta;
    rightMotorSpeed = motorSpeed -delta;
    
  } else if (errorX < -10) {
    // The robot is to the right of the desired position
    leftMotorSpeed = motorSpeed - delta;
    rightMotorSpeed = motorSpeed +delta;
    
  }else if(errorY > Ythres) {
    // Motor should move forward
    leftMotorSpeed = motorSpeed + errorY/5;
    rightMotorSpeed = motorSpeed + errorY/5;
  }

  if(leftMotorSpeed>250 && rightMotorSpeed > 250){
    // Fixing Overspeed issue
        leftMotorSpeed = 250;
        rightMotorSpeed = 250;
      }

  // Setting Speed to the Enable pins
  analogWrite(LMEnable, leftMotorSpeed);
  analogWrite(RMEnable, rightMotorSpeed);

 // Run and stop robot according to the conditions 
 if(errorY>Ythres){
     Run();
     Serial.println("Run");
     delay(25);
    
  } else if(errorY < Ythres && errorX<10 && errorX >-10){
     Stop();
     Serial.println("stop");
     delay(5);
     
    } else {
     Run();
     Serial.println("Run");
     delay(25);
    
    }
}

void Run(){
  // Function for running the motors
   digitalWrite(LMForward, HIGH);
   digitalWrite(RMForward, HIGH);
  }

void Stop() {
  // Function for stopping the motors
   digitalWrite(LMForward, LOW);
   digitalWrite(RMForward, LOW);
}
