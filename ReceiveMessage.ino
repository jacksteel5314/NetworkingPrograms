Re// Include Packages and Define Pin 
#include <SoftwareSerial.h>
#define TX_PIN 11

// Create the SoftwareSerial
SoftwareSerial aSerials(10, TX_PIN); // RX, TX


void setup() {
  
  // Start the Serial Communications 
  Serial.begin(9600);

  // Start the Software Serial
  aSerials.begin(9600);

  // Comment Out Booted Serial.print("Booted\n");

  // Start LED
  pinMode(LED_BUILTIN, OUTPUT);

}

void loop() {
  // Array of Received Data 
  byte dataRec[16];
  int curr = 16;
  
  
  // Check to See If There is Available Input 
  if(aSerials.available() >= 16){ // NEED 16 BYTES 

    // Enter If Statement Serial.print("Beginning to Receive\n")

    // Place All of the Receives Bytes in our Bytes Array
    aSerials.readBytes(dataRec, 16);

    // Write the Buffer to Serial Serial.write(dataRec, 16);

    // Extra Line Serial.print("\n");

    // Iterate through All Inputs
    for(int i = 0; i < 16; i++){

      // If there is a Letter thats not A 
      if(dataRec[i] != 65){

        // Not All A
        curr = i;

        // Turn LED Off
        digitalWrite(LED_BUILTIN, LOW);

        // Leave this Loop, Start Again
        break;
        
      }
    }
  }

  // If All 16 Letters were 65 (A)
  if(curr == 16){

    // Turn LED On
    digitalWrite(LED_BUILTIN, HIGH);
    
  }
  Serial.write(dataRec, 16);
  delay(1000);

}
