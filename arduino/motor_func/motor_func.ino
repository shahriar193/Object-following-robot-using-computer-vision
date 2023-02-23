//Include the motor driver library
#include <AFMotor.h>
#include <SoftwareSerial.h> // Include the SoftwareSerial library
#define RX A0
#define TX A1

SoftwareSerial BTSerial(RX, TX);   // RX, TX pins for Bluetooth module

//Set the speed of the motors
#define Speed 150
int x = 15;
int y = 120;

//Create objects for the motors
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600); // Initialize the Bluetooth module
  
  //Set the speed of the motors
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);
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
     x = xString.toInt();
     y = yString.toInt();
    
    // Print the (x, y) coordinate to the serial monitor
    Serial.print("Received coordinate: ");
    Serial.print(x);
    Serial.print(", ");
    Serial.println(y);

    
  }

  // Check the distance using the IF condition
  if ( y<40 & x<20 & x>-20) {
    Stop();
    //Serial.println("Stop");
    delay(500);
  }

  else if (x<-15) {
      shortLeft();
      Serial.println("Left");
      delay(500);
    } 
  else if(x>15){
      shortRight();
      Serial.println("Right");
      delay(500);
    }

  if(y>20){
      Serial.println("Forward");
      forward();
    } 
}










/*******************Motor functions**********************/
void forward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void shortLeft(){
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  }

void shortRight() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}

void left() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void right() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void Stop() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
