// 2. Music door bell
#include "Buzzer.h"
#include "Sounds.h"
#include "PH20Port.h"

PH20Port buzzerplay(P9);

#include "Buzzer.h" // 왜??

int touch_PIN2 = 2;
Buzzer mBuzzer = Buzzer(buzzerplay.pin1());
Buzzer buzzer(buzzerplay.pin1());


// 0. Default setup
// 1. Human body recognition lamp
int humanSensor = 4;
int lampPin = 3;
// 2. Music door bell

void setup() {
  Serial.begin(9600); // 0.

  pinMode(humanSensor, INPUT); // 1. 
  pinMode(lampPin, OUTPUT); // 1.
  pinMode(touch_PIN2,INPUT); // 2.
}

void loop() {
  //Serial.println("Welcome to SMARTHOME!"); // 0.
  //delay(500); // 0.

  if (digitalRead(humanSensor) == 1) { // 1. 
    digitalWrite(lampPin, HIGH);
    Serial.println("Someone entered!!");
  } else {
    digitalWrite(lampPin, LOW);
  }

  if (digitalRead(touch_PIN2)==HIGH) { // 2. 
    mBuzzer.bendTones(1500, 2500, 1.05, 20, 8);
    mBuzzer.bendTones(2499, 1500, 1.05, 25, 8);
  } else {
    buzzer.noTone();
  }
}
