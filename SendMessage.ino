// Include Packages and Define Pin 
#include <SoftwareSerial.h>
#define TX_PIN 11

// Create the SoftwareSerial
SoftwareSerial aSerials(10, TX_PIN); // RX, TX

// Set Up Function - ONLY RUNS ONCE
void setup() {

  // Start Serial Communication
  Serial.begin(9600);
  
  // Start the Software Serial From Above 
  aSerials.begin(9600);

}

// Loop Function – CONTINUOUSLY RUNS
void loop() {

  // Create and Write 16 'As' (or 65) to the Software Serial (which is sent out of pin)
  for (int i = 0; i < 16; i++) {

    // Write 65, or A, to SoftwareSerial
    aSerials.write(65); 
  }
  delay(1000);
  
}
