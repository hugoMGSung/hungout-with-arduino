void setup() {
  pinMode(2, OUTPUT); // 내장 LED 핀 설정
}

void loop() {
  digitalWrite(2, HIGH);
  delay(500);
  digitalWrite(2, LOW);
  delay(500);
}