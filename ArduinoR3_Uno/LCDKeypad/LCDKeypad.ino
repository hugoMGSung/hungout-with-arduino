#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

#define BTN_RIGHT  0
#define BTN_UP     1
#define BTN_DOWN   2
#define BTN_LEFT   3

#define BTN_SELECT 4
#define BTN_NONE   5

int adc_key_in = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("LCD key Shield");

}

void loop()
{
  int lcd_key = read_LCD_buttons();
  display_LCD(lcd_key);
  delay(200);
}


int read_LCD_buttons()
{
  adc_key_in  = analogRead(0);

  if (adc_key_in > 1000) return BTN_NONE;
  if (adc_key_in < 50)   return BTN_RIGHT;   // 0
  if (adc_key_in < 195)  return BTN_UP;      // 99
  if (adc_key_in < 380)  return BTN_DOWN;    // 256
  if (adc_key_in < 555)  return BTN_LEFT;    // 409
  if (adc_key_in < 790)  return BTN_SELECT;  // 639

  return BTN_NONE;
}

void display_LCD(int lcd_key) {
  lcd.setCursor(0, 1);

  if (lcd_key == BTN_RIGHT) lcd.print("RIGHT ");
  else if (lcd_key == BTN_LEFT) lcd.print("LEFT   ");
  else if (lcd_key == BTN_UP) lcd.print("UP    ");
  else if (lcd_key == BTN_DOWN) lcd.print("DOWN  ");
  else if (lcd_key == BTN_SELECT) lcd.print("SELECT");
  else if (lcd_key == BTN_NONE) lcd.print("NONE  ");


  lcd.setCursor(10, 1);
  clearLCD();
  lcd.print(adc_key_in);
}

void clearLCD() {
  int i = 0;
  int digit = 0;

  if (adc_key_in > 999) digit = 4;
  else if (adc_key_in > 99) digit = 3;
  else if (adc_key_in > 9)  digit = 2;
  else digit = 1;

  for (i = 4; i > digit; i--) lcd.print(" ");
}