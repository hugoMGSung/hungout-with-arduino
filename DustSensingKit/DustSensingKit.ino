#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <SoftwareSerial.h>  

// 블루투스 통신 초기화
SoftwareSerial BTSerial(3, 4); // BT TX:3, RX:4

#include <Wire.h>                     // i2C 통신을 위한 라이브러리
#include <LiquidCrystal_I2C.h>        // LCD 2004 I2C용 라이브러리
LiquidCrystal_I2C lcd(0x27,16,2);  

#define DHTPIN 7
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT11     // DHT 22 (AM2302)
//#define DHTTYPE    DHT21     // DHT 21 (AM2301)

#define REDPIN 10
#define GREENPIN 9
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

int DUST = 0;
float dustval = 0.0f;
float voltage = 0.0f;
float dustug = 0.0f;
float dus = 0.0f;
int deltaTime = 40;

void setup() {
  Serial.begin(115200);
  BTSerial.begin(115200); // 블루투스는 바꿔보자.
  
  dht.begin();  // Initialize device.
  //Serial.println(F("DHT11 Unified Sensor Example"));
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;

  // LED
  pinMode(REDPIN, OUTPUT);
  pinMode(GREENPIN, OUTPUT);
  digitalWrite(GREENPIN, HIGH); // 일단 파란불
  digitalWrite(REDPIN, LOW);

  lcd.init();                      // LCD 초기화
  lcd.backlight();                // 백라이트 켜기
  
}

void loop() {
  delay(delayMS);
  sensors_event_t event;
  float temp = 0.0f;
  float humd = 0.0f;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  } else {
    temp = event.temperature;
    Serial.print(F(" Temp: "));
    Serial.print(temp);
    Serial.println(F("°C"));
  }
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  } else {
    humd = event.relative_humidity;
    Serial.print(F("Humidity: "));
    Serial.print(humd);
    Serial.println(F("%"));
  }

  dustval = analogRead(DUST);
  delayMicroseconds(deltaTime);
  voltage = dustval * (5.0 / 1024.0);
  dustug = 0.17 * voltage;
  dus = dustug * 1000;
  Serial.print("Dust Sensor Voltage: ");
  Serial.print(voltage);
  Serial.println("V");
  Serial.print("Dust Value: ");
  Serial.print(dus); // unit: mg/m3
  Serial.println("ug");

  if (dus > 0) {
    digitalWrite(GREENPIN, LOW);
    digitalWrite(REDPIN, HIGH);
  } else {
    digitalWrite(GREENPIN, HIGH);
    digitalWrite(REDPIN, LOW);
  }

  // LCD에 온습도 출력하기
  lcd.setCursor(0,0);             // 첫 번째 column열 , 첫 번째 row 행부터 시작
  lcd.print("FineDust SENSKit");
  lcd.setCursor(0,1);             // 첫 번째 column 열, 첫 번째 row 행부터 시작
  lcd.print(temp + String("'C | ") + humd + String("%"));

  if(Serial.available()) {             // 시리얼 통신으로 문자가 들어오면
    BTSerial.write(Serial.read());      // 블루투스시리얼 통신으로 발송
  } 

  if(BTSerial.available()) {               // 블루투스 시리얼 통신으로 문자가 들어오면
    Serial.write(BTSerial.read());       // 시리얼 창에 표시(시리얼 통신으로 출력)
  }
}
