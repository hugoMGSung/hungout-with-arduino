int buzzer = 3;
int switch1 = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);
  pinMode(switch1, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(switch1) == LOW) {
    Serial.println("ON");
    // tone(buzzer, 523);
    // delay(1000);
    // tone(buzzer, 587);
    // delay(1000);
  } else {
    Serial.println("OFF");
    // tone(buzzer, 0);
  }

}
