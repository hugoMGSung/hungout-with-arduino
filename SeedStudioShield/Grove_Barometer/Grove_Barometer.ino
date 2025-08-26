#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define BUTTON_PIN 2
#define SEALEVELPRESSURE_HPA 1013.25 // 지역 기압으로 보정하면 고도 정확도 ↑

Adafruit_BME280 bme;

bool btnPrev = HIGH;
unsigned long lastChange = 0;
const unsigned long debounceMs = 50;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Grove Button: 누르면 LOW

  Wire.begin();

  // BME280 I2C 주소 시도 (기본 0x76 → 실패 시 0x77)
  bool ok = bme.begin(0x76);
  if (!ok) ok = bme.begin(0x77);

  if (!ok) {
    Serial.println(F("BME280 not found! Check I2C wiring or address(0x76/0x77)."));
    while (1) delay(1000);
  }

  Serial.println(F("Ready. Press the button on D2 to read BME280."));
}

void loop() {
  int btn = digitalRead(BUTTON_PIN);
  unsigned long now = millis();

  // 디바운스 + 하강엣지(눌림) 검출
  if (btn != btnPrev && (now - lastChange) > debounceMs) {
    lastChange = now;
    btnPrev = btn;

    if (btn == LOW) { // 버튼 눌림
      float t  = bme.readTemperature();          // °C
      float h  = bme.readHumidity();             // %RH
      float p  = bme.readPressure() / 100.0F;    // hPa
      float alt = bme.readAltitude(SEALEVELPRESSURE_HPA); // m (선택)

      Serial.print(F("T: "));   Serial.print(t, 1);  Serial.print(F(" °C, "));
      Serial.print(F("H: "));   Serial.print(h, 1);  Serial.print(F(" %RH, "));
      Serial.print(F("P: "));   Serial.print(p, 1);  Serial.print(F(" hPa, "));
      Serial.print(F("Alt: ")); Serial.print(alt, 1);Serial.println(F(" m"));
    }
  }
}
