//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <AFMotor.h>
#include <Servo.h>

Servo servo1;
Servo servo2;

int servoPos = 0;

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
  servo1.attach(4);
  servo2.attach(5);
  
  lcd.init(); // initialize the lcd
  // Print a message to the LCD.
  lcd.backlight();
//  lcd.setCursor(0,0);
//  lcd.print("Hello, world!");
//  lcd.setCursor(0,1);
//  lcd.print("Ywrobot Arduino!");
}


void loop()
{
  for (servoPos >= 0; servoPos <= 180; servoPos++) {
    servo1.write(servoPos);
    servo2.write(servoPos);
    lcd.setCursor(0,0);
    lcd.print("Servo Position");
    lcd.setCursor(0,1);
    lcd.print(servoPos);
    delay(20);
  }

  for (servoPos <= 0; servoPos >= 0; servoPos--) {
    servo1.write(servoPos);
    servo2.write(servoPos);
    lcd.setCursor(0,0);
    lcd.print("Servo Position");
    lcd.setCursor(0,1);
    lcd.print(servoPos);
    delay(20);
  }
}
