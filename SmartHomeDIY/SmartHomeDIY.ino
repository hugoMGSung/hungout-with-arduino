// 필요 헤더 추가
#include "Buzzer.h"
#include "Sounds.h"
#include "PH20Port.h"

PH20Port buzzerplay(P9);

#include "Buzzer.h" // 왜??

#include "SoftI2CMaster.h"
#include "LiquidCrystal_SoftI2C.h" // LCD 표시용
#include "DHT.h"

#include <Servo.h>
Servo servoGarage;

#include "EM_TTP229.h"
EM_TTP229 mTTP229;
// 7 세그먼트
#include <Wire.h>
#include "TM1650.h"

TM1650 tm_4display;
volatile int _light;
volatile int _rain; // 수분센서
volatile int _fire; // 불꽃센서
int fireSensorPin = 7;

int SCLPin = 9, SDOPin = 8;

int humanSensorPin = 4;

// 교통신호등 LED 핀번호 맞추기 힘듦
int trafficGreenPin = 3;
int trafficYelloPin = 5;
int trafficRedPin = 6;

// 서보모터 설정
int servoPin = 12;
// 근접센서
// int sensorPin = 13;
// 창문서보모터 // 창문은 계속 열림 특히 현재 것에 문제가 있어서 사용 불가
// int winServoPin = 13;
// Servo servoWindow;


// 터치센서 
int touch_PIN2 = 2;
Buzzer mBuzzer = Buzzer(buzzerplay.pin1());
Buzzer buzzer(buzzerplay.pin1());

// LCD 설정
LiquidCrystal_SoftI2C mylcd(0x27,16,2,7,A0);

// 온습도 센서
DHT dhtA0(A0, 11);
DHT dhtA3(A3, 11);
const int condTemp = 29;

String item;
volatile int number;
String password[]={"0", "0", "0"};

// 키패드 읽기함수
String Read_Key () {
 String key_name = mTTP229.GetKeyMap();
 char * result = (char *)key_name.c_str();
 return result;
}

// 모터용 함수
void setMotor8833(int speedpin,int dirpin, int speed)
{
  if (speed == 0)
  {
    digitalWrite(dirpin, LOW);
    analogWrite(speedpin, 0);
  }
  else if (speed > 0)
  {
    digitalWrite(dirpin, LOW);
    analogWrite(speedpin, speed);
  }
  else
  {
    digitalWrite(dirpin, HIGH);
    analogWrite(speedpin, 255 + speed);
  }
}

void setup() {
  item = "";
  number = 0;
  mTTP229.initTTP229(SCLPin, SDOPin); // 키패드 초기화
  Serial.begin(9600);

  pinMode(humanSensorPin, INPUT); // 휴먼센서 
  // 교통신호등 LED 설정
  pinMode(trafficGreenPin, OUTPUT);
  pinMode(trafficYelloPin, OUTPUT);
  pinMode(trafficRedPin, OUTPUT);
  // 최초에는 교통신호등 다 꺼놓기
  digitalWrite(trafficGreenPin, LOW);
  digitalWrite(trafficYelloPin, LOW);
  digitalWrite(trafficRedPin, LOW);
  // 터치센서 
  pinMode(touch_PIN2, INPUT);

  // LCD 초기화
  mylcd.init();
  mylcd.backlight();
  // 온습도 및 모터 설정
  dhtA0.begin();
  dhtA3.begin();
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);

  // 근접센서 설정
  // pinMode(sensorPin, INPUT);
  servoGarage.attach(servoPin);

  // 7 세그먼트 설정
  Wire.begin();
  tm_4display.init();
  _light = 0;
  _rain = 0;
  tm_4display.clear();
  //servoWindow.attach(winServoPin); // 창문서보 불가!!
  _fire = 0;
}

void loop() {
  /// Serial.println("스마트홈 시스템!");
  Serial.println(String("T:") + String(dhtA3.readTemperature()));

  // light and display
  _light = analogRead(A2);
  _rain = analogRead(A1); // 수분센서
  //_fire = digitalRead(fireSensorPin);
  tm_4display.displayString(_light);
  mylcd.setCursor(0, 0);
  mylcd.print(String("T:") + String(dhtA3.readTemperature()));
  mylcd.setCursor(0, 1);
  mylcd.print(String("H:") + String(dhtA3.readHumidity()));
  
  Serial.print(String(" light:") + String(_light));
  Serial.print(",");
  Serial.print(String("rain:") + String(_rain));
  Serial.print(",");
  Serial.println(String("fire:") + String(_fire));

  if (_light < 100) {
    mBuzzer.bendTones(1500, 2500, 1.05, 20, 8);
  }
  if (_rain < 350) {
    mBuzzer.bendTones(2000, 2500, 1.05, 20, 8);
  }
  // if (_light > 100) {
  //   servoWindow.write(0);
  // }
  // else {
  //   servoWindow.write(90);
  // }

  // 키패드 입력
  item = Read_Key();
  if (item == "1" && number == 0) {
    Serial.println(item);
    mBuzzer.tone(2500, 10); // 필요키를 누를때마다 소리가 나도록
    password[(int)(0)] = item;
    number = 1;
    delay(100);

  }
  if (item == "2" && number == 1) {
    Serial.println(item);
    mBuzzer.tone(2500, 10); // 필요키를 누를때마다 소리가 나도록
    password[(int)(1)] = item;
    number = 2;
    delay(100);

  }
  if (item == "3" && number == 2) {
    Serial.println(item);
    mBuzzer.tone(2500, 10); // 필요키를 누를때마다 소리가 나도록
    password[(int)(2)] = item;
    number = 3;
    delay(100);

  }
  if (password[(int)(0)] == "1" && (password[(int)(1)] == "2" && password[(int)(2)] == "3")) {
    Serial.println("hello");
    mBuzzer.bendTones(2500, 1000, 1.05, 10, 1); // 들어오는 소리
    servoGarage.write(90); // 차고문을 연다
    delay(2000);
    password[(int)(0)] = "0";
    password[(int)(1)] = "0";
    password[(int)(2)] = "0";
    number = 0;

  } else {
    buzzer.noTone();
    servoGarage.write(0);
    delay(20);
  }

  if (digitalRead(humanSensorPin) == 1) { // 휴먼센서 인식되면
    digitalWrite(trafficRedPin, HIGH);
    Serial.println("인체 감지");
  } else {
    digitalWrite(trafficRedPin, LOW);
  }

  if (digitalRead(touch_PIN2) == HIGH) {
    mBuzzer.bendTones(1500, 2500, 1.05, 20, 8);
    mBuzzer.bendTones(2499, 1500, 1.05, 25, 8);
  } else {
    buzzer.noTone();
  }

  if (dhtA3.readTemperature() > condTemp) { //온도가 28도는 넘어서면
    setMotor8833(5, 6, 100); // 모터를 돌린다. 이부분 손볼것
  } else {
    setMotor8833(5, 6, 0);
  }

  // if (digitalRead(sensorPin) == 1) { // 1 감지 | 0 노감지
  //   Serial.println("주차장 접근!");
  //   servoGarage.write(90);
  // }
  // else {
  //   servoGarage.write(0);
  // }

  

  delay(500); // 0.5초
}
