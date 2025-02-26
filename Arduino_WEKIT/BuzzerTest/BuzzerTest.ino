int buzzer = 3;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(buzzer, 523);
  delay(1000);
  tone(buzzer, 587);
  delay(1000);
}
