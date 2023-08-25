// 필요 헤더 추가
#include "Buzzer.h"
#include "Sounds.h"
#include "PH20Port.h"

PH20Port buzzerplay(P9);

#include "Buzzer.h" // 왜??

#include "DHT.h"

int humanSensorPin = 4;

// 교통신호등 LED 핀번호 맞추기 힘듦
int trafficGreenPin = 3;
int trafficYelloPin = 5;
int trafficRedPin = 6;

// 터치센서 
int touch_PIN2 = 2;
Buzzer mBuzzer = Buzzer(buzzerplay.pin1());
Buzzer buzzer(buzzerplay.pin1());

// 온습도 센서
DHT dhtA0(A0, 11);
DHT dhtA3(A3, 11);

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
  // 온습도 및 모터 설정

  dhtA0.begin();
  dhtA3.begin();
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void loop() {
  /// Serial.println("스마트홈 시스템!");
  Serial.println(String("T:") + String(dhtA3.readTemperature()));

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

  if (dhtA3.readTemperature() > 28) {
    setMotor8833(5, 6, 100);
  } else {
    setMotor8833(5, 6, 0);
  }

  delay(500); // 0.5초
}
