
#include <SoftwareSerial.h> // Include the SoftwareSerial library
#define RX A0
#define TX A1

SoftwareSerial BTSerial(RX, TX);   // RX, TX pins for Bluetooth module
char incomingByte;                 // Variable to store incoming Bluetooth data

void setup() {
  Serial.begin(9600); // Initialize the Serial Monitor
  BTSerial.begin(9600); // Initialize the Bluetooth module
}

void loop() {
  if (BTSerial.available()) {             // Check if there is data available from Bluetooth module
    incomingByte = BTSerial.read();       // Read the incoming data
    String incomingString = String(incomingByte);
   
    Serial.print(incomingString);
//    float* coordinate = splitString(incomingString, ',', 2); // call splitString function to split the string and store the values
//    for(int i = 0; i < 2; i++) {
//        Serial.print(coordinate[i]);
//        Serial.print(" ");
//    }
//    Serial.print("\n"); 
  }
}
