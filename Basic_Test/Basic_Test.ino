void setup() {
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13,HIGH);
  delay(5000); // 5초 동안 켜짐
  digitalWrite(13,LOW);
  delay(1000);
}