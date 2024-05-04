/*
  Bluetooth
*/
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 4); // BT TX:3, RX:4

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  if (BTSerial.available()) 
    Serial.write(BTSerial.read());

  if (Serial.available()) 
    BTSerial.write(Serial.read());
}
