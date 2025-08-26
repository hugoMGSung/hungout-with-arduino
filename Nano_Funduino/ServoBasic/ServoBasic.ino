#include <Servo.h>
Servo s;

void setup() {
  s.attach(9);          // 서보 신호: D9
}

void loop() {
  for (int p=0; p<=180; p+=2) { s.write(p); delay(10); }
  for (int p=180; p>=0; p-=2) { s.write(p); delay(10); }
}