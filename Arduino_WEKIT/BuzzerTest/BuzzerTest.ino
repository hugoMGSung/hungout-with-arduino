// #include "Seeed_BME280.h"

#include <Grove_LED_Bar.h>

Grove_LED_Bar bar(1, 0, 0);  // Clock pin, Data pin, Orientation

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// #include <Wire.h>

// BME280 bme280;

int buzzer = 3;
int switch1 = 8;

U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);    //Software I2C

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  pinMode(switch1, INPUT);

  // if(!bme280.init()){
  //   Serial.println("Device error!");
  // }

  u8g2.begin();
  bar.begin();
}

void loop() {
  float pressure;

  // put your main code here, to run repeatedly:
  if (digitalRead(switch1) == LOW) {
    //Serial.println("OFF");
    digitalWrite(buzzer, LOW);  // 부저 끄기
  } else {
    //Serial.println("ON");
    // digitalWrite(buzzer, HIGH); // 부저 켜기
    //get and print temperatures
    //get and print temperatures
    // Serial.print("Temp: ");
    // Serial.print(bme280.getTemperature());
    // Serial.println("C");//The unit for  Celsius because original arduino don't support speical symbols

    // //get and print atmospheric pressure data
    // Serial.print("Pressure: ");
    // Serial.print(pressure = bme280.getPressure());
    // Serial.println("Pa");

    // //get and print altitude data
    // Serial.print("Altitude: ");
    // Serial.print(bme280.calcAltitude(pressure));
    // Serial.println("m");

    // //get and print humidity data
    // Serial.print("Humidity: ");
    // Serial.print(bme280.getHumidity());
    // Serial.println("%");

    // delay(1000);  
  }

  u8g2.clearBuffer();                   // clear the internal memory
  u8g2.setFont(u8g2_font_luBIS08_tf);   // choose a suitable font
  u8g2.drawStr(0,10,"Hello Seeed!");    // write something to the internal memory
  u8g2.drawStr(0,30,"Hello Studio!");    // write something to the internal memory
  u8g2.drawStr(0,50,"Hello Hugo!");    // write something to the internal memory
  u8g2.sendBuffer();                    // transfer internal memory to the display
  delay(100);  
}
