#include <Grove_LED_Bar.h>

#define BUTTON_PIN 2        // 버튼 (D2 포트)

// LED Bar는 D4 포트 사용: D4(노랑)=DATA, D5(흰색)=CLK
const int PIN_CLK = 5;      // 필요 시 4↔5 서로 바꿔보세요
const int PIN_DAT = 4;

Grove_LED_Bar bar(PIN_CLK, PIN_DAT, 0); // 0: 왼→오, 1: 반대

int level = 0;                       // 0~10
int btnPrev = HIGH;
unsigned long lastChange = 0;
const unsigned long debounceMs = 50;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  bar.begin();
  bar.setLevel(level);
  Serial.println(F("Press D2: +1 level, when Full next press resets to 0"));
}

void loop() {
  int b = digitalRead(BUTTON_PIN);

  // 디바운스 + 하강엣지(눌림) 검출
  if (b != btnPrev && (millis() - lastChange) > debounceMs) {
    lastChange = millis();
    btnPrev = b;

    if (b == LOW) {  // 버튼 눌림
      if (level < 10) {
        level++;
        bar.setLevel(level);
        Serial.print(F("Level: ")); Serial.println(level);
        if (level == 10) Serial.println(F("Full"));
      } else {
        // Full 상태에서 다음 누름 → 0으로 리셋
        level = 0;
        bar.setLevel(0);
        Serial.println(F("Reset to 0"));
      }
    }
  }
}
