// Transmitter

// Include Package 
#include <SoftwareSerial.h>

SoftwareSerial bSerials(10, 11); // RX, TX

// Size Sixteen
struct cmd{
  char magic[4];
  uint8_t verb;  // Unsigned Integer size 2 
  char padding[10];   // 10 Chars size 1 
};

// Size Sixteen
struct response{
  char magic[4];  // 4 Chars size 1 
  char success;   // 1 Char size 1 
  char pad[11];   // 11 Chars size 11 
};

void setup() {
  // put your setup code here, to run once:

  // Start the Serial Communications 
  Serial.begin(9600);

  // Start the Software Serial 
  bSerials.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  // Command Struct for Turning LEDON
  struct cmd ledon;
  ledon.magic[0] = 'M';
  ledon.magic[1] = 'I';
  ledon.magic[2] = 'R';
  ledon.magic[3] = 'O';
  ledon.verb = 1;

  // Write Each Part of Struct
  char byteBuff1[16];
  memcpy(byteBuff1, &ledon, 16);
  for(int i = 0; i < 16; i++){
    bSerials.write(byteBuff1[i]);
  }

  // Check if Available and Read into Struct 
  char buffer1[16];
  struct response r1; 
  if(bSerials.available() >= 16){

    // Read Each Part Into Struct
    bSerials.readBytes(buffer1, 16); 
    memcpy(&r1, buffer1, 16);

    // Checking the Success of the Password 
    if(r1.success == 1){
      Serial.println("Success!");
    }
    else{
      Serial.println("Failure!");
    }
  }

  delay(1000);

  

  // Command for Turning LEDOFF
  struct cmd ledoff;
  ledoff.magic[0] = 'M'; 
  ledoff.magic[1] = 'I';
  ledoff.magic[2] = 'R';
  ledoff.magic[3] = 'O';
  ledoff.verb = 0;

  // Write Each Part of Struct
  char byteBuff2[16];
  memcpy(byteBuff2, &ledoff, 16);
  for(int i = 0; i < 16; i++){
    bSerials.write(byteBuff2[i]);
  }

  // Check if Available and Read into Struct 
  char buffer2[16];
  struct response r2; 
  if(bSerials.available() >= 16){

    // Read Each Part Into Struct
    bSerials.readBytes(buffer2, 16); 
    memcpy(&r2, buffer2, 16);

    // Checking the Success of the Password 
    if(r2.success == 1){
      Serial.println("Success!");
    }
    else{
      Serial.println("Failure!");
    }
  }

  delay(1000);

  
  

  

  // Incorrect Magic Word - this should not turn the LED back on
  struct cmd wrongmagic;
  wrongmagic.magic[0] = 'S'; 
  wrongmagic.magic[1] = 'L';
  wrongmagic.magic[2] = 'A';
  wrongmagic.magic[3] = 'V';
  wrongmagic.verb = 1;

  // Write Each Part of Struct
  char byteBuff3[16];
  memcpy(byteBuff3, &wrongmagic, 16);
  for(int i = 0; i < 16; i++){
    bSerials.write(byteBuff3[i]);
  }

  // Check if Available and Read into Struct 
  byte buffer3[16];
  struct response r3; 
  if(bSerials.available() >= 16){

    // Read Each Part Into Struct
    bSerials.readBytes(buffer3, 16); 
    memcpy(&r3, buffer3, 16);
    // Checking the Success of the Password 
    if(r3.success == 1){
      Serial.println("Success!");
    }
    else{
      Serial.println("Failure!");
    }
  }

  delay(1000);
  
}
