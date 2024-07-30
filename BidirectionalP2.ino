// Receiver

// Include Package 
#include <SoftwareSerial.h>

SoftwareSerial aSerials(10, 11); // RX, TX

// Size Sixteen
struct response{
  char magic[4];  // 4 Chars size 1 
  char success;   // 1 Char size 1 
  char pad[11];   // 11 Chars size 11 
};

struct cmd{
  char magic[4];  // 4 Chars size 4 
  uint8_t verb;  // Unsigned Integer size 2 
  char padding[10];   // 10 Chars size 1 
};

void setup() {
  // put your setup code here, to run once:

  // Start the Serial Communications 
  Serial.begin(9600);

  // Start the Software Serial 
  aSerials.begin(9600);

  // Start LED 
  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:

  // Receive Command
  struct cmd c;

  // Response Struct 
  struct response r; 

  // Create Buffer 
  char buffer[16];
  
  // Check if Available and Read into Struct 
  if(aSerials.available() >= 1){


    // Read Each Part Into Struct
    aSerials.readBytes(buffer, 16); 
    memcpy(&c, buffer, 16);

    // Check if it Says "MIRO"
    if(c.magic[0] == 'M' && c.magic[1] == 'I' && c.magic[2] == 'R' && c.magic[3] == 'O'){
      if(c.verb == 0){
        digitalWrite(LED_BUILTIN, LOW);
      }
      else{
        digitalWrite(LED_BUILTIN, HIGH);
      }
      r.success = 1;
    }
    else{
      r.success = 0;
    }

    // Send Back SLAV Message 
    r.magic[0] = 'S';
    r.magic[1] = 'L';
    r.magic[2] = 'A';
    r.magic[3] = 'V';

    char responseBuff[16];
    memcpy(responseBuff, &r, 16);
    for(int i = 0; i < 16; i++){
      aSerials.write(responseBuff[i]);
    }
  }


}
