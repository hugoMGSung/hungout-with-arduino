#include <Wire.h>
#include <U8g2lib.h>

#define BUTTON_PIN 2

// 대부분의 Grove 128x64 I2C OLED는 SSD1306/SSD1315 계열(주소 0x3C).
// 화면이 안 뜨면 아래 두 줄 중 다른 생성자를 시험하거나 회전값을 바꿔 보세요.
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
// 예) SH1107 계열일 경우: U8G2_SH1107_64X128_F_HW_I2C u8g2(U8G2_R2);

int page = 0;
int btnPrev = HIGH;
unsigned long lastChange = 0;
const unsigned long debounceMs = 60;

// 페이지3(바운싱 볼) 상태
float bx = 20,  by = 20;
float vx = 1.8, vy = 1.2;
const int  r  = 6;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Wire.begin();
  u8g2.begin();
  // 필요시 회전: u8g2.setDisplayRotation(U8G2_R0/R1/R2/R3);
  // 필요시 I2C 주소(7-bit 0x3C)를 8-bit로 설정: u8g2.setI2CAddress(0x3C*2);

  u8g2.enableUTF8Print(); // 한글 출력 시 폰트 교체 필요. 여기선 영문 숫자 사용.
}

void drawPage1() {
  // 대시보드
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(2, 12, "Grove OLED Demo");
  u8g2.drawHLine(0, 14, 128);

  // 진행바(시간에 따라 변화)
  uint8_t w1 = (millis()/10) % 128;
  uint8_t w2 = (millis()/6)  % 128;

  u8g2.drawStr(2, 28, "Progress A");
  u8g2.drawFrame(2, 32, 124, 8);
  u8g2.drawBox(4, 34, w1, 4);

  u8g2.drawStr(2, 48, "Progress B");
  u8g2.drawFrame(2, 52, 124, 8);
  u8g2.drawBox(4, 54, w2, 4);

  // 아이콘 느낌 도형
  u8g2.drawCircle(112, 10, 7);
  u8g2.drawTriangle(110, 24, 124, 24, 117, 34);
}

void drawPage2() {
  // 아날로그 시계 (초침만)
  const int cx = 64, cy = 32;
  u8g2.drawCircle(cx, cy, 30);

  // 12개 틱
  for (int i=0; i<12; ++i) {
    float ang = i * (2*PI/12);
    int x1 = cx + (int)(cos(ang)*26);
    int y1 = cy + (int)(sin(ang)*26);
    int x2 = cx + (int)(cos(ang)*30);
    int y2 = cy + (int)(sin(ang)*30);
    u8g2.drawLine(x1, y1, x2, y2);
  }

  // 초침
  int sec = (millis()/1000) % 60;
  float a = (sec / 60.0f) * 2*PI;   // 0~2π
  int xs = cx + (int)(cos(a - PI/2) * 24); // 12시가 0초
  int ys = cy + (int)(sin(a - PI/2) * 24);
  u8g2.drawLine(cx, cy, xs, ys);

  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.setCursor(44, 60);
  u8g2.print("SEC ");
  u8g2.print(sec);
}

void drawPage3() {
  // 바운싱 볼
  bx += vx; by += vy;
  if (bx - r <= 0 || bx + r >= 127) vx = -vx;
  if (by - r <= 0 || by + r >= 63)  vy = -vy;
  u8g2.drawDisc((int)bx, (int)by, r);

  // 바닥에 그림자 느낌
  u8g2.drawHLine(0, 63, 128);
}

void loop() {
  // 버튼 디바운스 + 하강엣지 검출
  int b = digitalRead(BUTTON_PIN);
  if (b != btnPrev && (millis() - lastChange) > debounceMs) {
    lastChange = millis();
    btnPrev = b;
    if (b == LOW) {           // 눌림
      page = (page + 1) % 3;  // 0->1->2->0...
    }
  }

  u8g2.clearBuffer();
  switch (page) {
    case 0: drawPage1(); break;
    case 1: drawPage2(); break;
    case 2: drawPage3(); break;
  }
  u8g2.sendBuffer();

  // 프레임레이트(과도한 깜빡임 방지)
  delay(25);
}
