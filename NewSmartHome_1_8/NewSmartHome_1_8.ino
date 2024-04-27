// 2. Music door bell
#include "Buzzer.h"
#include "Sounds.h"
#include "PH20Port.h"
// 3. DHT
#include "DHT.h" // <DHT.h> 아님
DHT dhtA0(A0, 11);
DHT dhtA3(A3, 11);
const int condTemp = 29;
// 4. Servo
#include <Servo.h>
Servo servo_12;
// 5. Keypad - 미사용!!
#include "EM_TTP229.h"
EM_TTP229 mTTP229;
String item;
volatile int number;
//String password[]={"0", "0", "0"};
// 6. Light Control
#include <Wire.h>
#include "TM1650.h"

TM1650 tm_4display;
volatile int _light;
volatile int _rain; // 수분센서
// 7. 공기질 
#include "SoftI2CMaster.h"
#include "LiquidCrystal_SoftI2C.h" // LCD 표시용
#include "DHT.h"

// 0. Default setup
// 1. Human body recognition lamp 
int HUMAN_SENSOR = 4;
int LAMP_PIN = 3;
// 2. Music door bell
int TOUCH_PIN = 2;
int TEMP_PIN = 5;
int MOTOR_PIN = 6;
// 4. Servo
int GARAGE_PIN = 12;
// 5. Keypad and Window
int SCLPin = 9, SDOPin = 8;
int WINDOW_PIN = 7;
// 6. Light Control
int ROOMLIGHT_PIN = 10;

// 7. 공기질에 사용할 LCD 설정
LiquidCrystal_SoftI2C mylcd(0x27,16,2,7,A0);

// 3. DHT if it get high temp, turn on the fan
void setMotor8833(int speedpin,int dirpin, int speed) {
  if (speed == 0) {
    digitalWrite(dirpin, LOW);
    analogWrite(speedpin, 0);
  } else if (speed > 0) {
    digitalWrite(dirpin, LOW);
    analogWrite(speedpin, speed);
  } else {
    digitalWrite(dirpin, HIGH);
    analogWrite(speedpin, 255 + speed);
  }
}

// 5. Keypad
// 키패드 읽기함수
String Read_Key () {
 String key_name = mTTP229.GetKeyMap();
 char * result = (char *)key_name.c_str();
 return result;
}

PH20Port buzzerplay(P9);
Buzzer mBuzzer = Buzzer(buzzerplay.pin1());
Buzzer buzzer(buzzerplay.pin1());

void setup() {
  Serial.begin(115200); // 0.

  pinMode(HUMAN_SENSOR, INPUT); // 1. 
  pinMode(LAMP_PIN, OUTPUT); // 1.
  pinMode(TOUCH_PIN,INPUT); // 2.
  // 3. dht
  dhtA0.begin();
  dhtA3.begin();
  pinMode(TEMP_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
  digitalWrite(TEMP_PIN, LOW);
  digitalWrite(MOTOR_PIN, LOW);
  // 4. Servo
  servo_12.attach(GARAGE_PIN);
  // 5. Keypad and Window
  item = "";
  number = 0;
  mTTP229.initTTP229(SCLPin, SDOPin); // 키패드 초기화
  // 6. Light Control. 세그먼트 설정
  Wire.begin();
  tm_4display.init();
  _light = 0;
  _rain = 0; // 7. rain
  tm_4display.clear();
  pinMode(ROOMLIGHT_PIN, OUTPUT);
  // 7. 온습도 LCD 및 초기화
  mylcd.init();
  mylcd.backlight();
  dhtA0.begin();
  dhtA3.begin();
}

void loop() {
  //Serial.println("Welcome to SMARTHOME!"); // 0.
  //delay(500); // 0.
  // light and display
  _light = analogRead(A2);
  _rain = analogRead(A1); // 7. 수분센서 
  
  Serial.println(String("T:") + String(dhtA3.readTemperature())); // 3.
  tm_4display.displayString(_light); // 7. Light Control
  Serial.print(String(" light:") + String(_light));
  Serial.print(",");
  Serial.print(String("rain:") + String(_rain));  
  Serial.println(",");

  // 7. 온습도
  mylcd.setCursor(0, 0);
  // mylcd.print(String("T:") + String(dhtA3.readTemperature()));
  mylcd.print(String("Hugo's SmartHome"));
  mylcd.setCursor(0, 1);
  mylcd.print(String(dhtA3.readTemperature()) + String("'C") + String(" | ") + String(dhtA3.readHumidity()) + String("%"));

  if (dhtA3.readTemperature() > condTemp) {
    setMotor8833(TEMP_PIN, MOTOR_PIN, 100);
    Serial.println(String("T:Fan On!")); // 3.
  } else {
    setMotor8833(TEMP_PIN, MOTOR_PIN, 0);
  }

  if (digitalRead(HUMAN_SENSOR) == 1) { // 1. 
    digitalWrite(LAMP_PIN, HIGH);
    Serial.println("Someone entered!!");
  } else {
    digitalWrite(LAMP_PIN, LOW);
  }

  if (_light > 50) { 
    digitalWrite(ROOMLIGHT_PIN, HIGH);
  } else {
    digitalWrite(ROOMLIGHT_PIN, LOW); // 여기서 켜진다! 이상하다!!
    Serial.println("Light UP");
  }

  if (_rain < 350) { // 비가 오면
    mBuzzer.bendTones(2000, 2500, 1.05, 20, 8);
    Serial.println("야, 비온다!!!");
  }

  if (digitalRead(TOUCH_PIN)==HIGH) { // 2. 
    mBuzzer.bendTones(1500, 2500, 1.05, 20, 8);
    mBuzzer.bendTones(2499, 1500, 1.05, 25, 8); 
    // 4. Servo
    servo_12.write(90);
  } else {
    buzzer.noTone();
    servo_12.write(0);
  }

  // 5. Keypad and Window
  // 키패드 입력
//  item = Read_Key();
//  if (item == "1" && number == 0) {
//    Serial.println(item);
//    mBuzzer.tone(2500, 10); // 필요키를 누를때마다 소리가 나도록
//    password[(int)(0)] = item;
//    number = 1;
//    delay(100);
//
//  }
//  if (item == "2" && number == 1) {
//    Serial.println(item);
//    mBuzzer.tone(2500, 10); // 필요키를 누를때마다 소리가 나도록
//    password[(int)(1)] = item;
//    number = 2;
//    delay(100);
//
//  }
//  if (item == "3" && number == 2) {
//    Serial.println(item);
//    mBuzzer.tone(2500, 10); // 필요키를 누를때마다 소리가 나도록
//    password[(int)(2)] = item;
//    number = 3;
//    delay(100);
//
//  }
//  if (password[(int)(0)] == "1" && (password[(int)(1)] == "2" && password[(int)(2)] == "3")) {
//    Serial.println("hello");
//    mBuzzer.bendTones(2500, 1000, 1.05, 10, 1); // 들어오는 소리
//    servo_12.write(90); // 차고문을 연다
//    delay(2000);
//    password[(int)(0)] = "0";
//    password[(int)(1)] = "0";
//    password[(int)(2)] = "0";
//    number = 0;
//
//  } else {
//    buzzer.noTone();
//    servo_12.write(0);
//    delay(20);
//  }

  delay(100);
}
