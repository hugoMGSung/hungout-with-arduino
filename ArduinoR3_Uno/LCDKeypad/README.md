# LCD Keypad Shield

## 기본코딩
```c
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

void setup()
{
  lcd.begin(16, 2);
}

void loop()
{
  lcd.setCursor(0, 0);
  lcd.print("LCDkeyShield");

  lcd.setCursor(0, 1);
  lcd.print("Hello,World!");
}
```

## 키패드 컨트롤

<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/lcdkeypadshield01.jpg" width="900" alt="키패드 실드">
