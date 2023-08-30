int num = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(3, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int a = digitalRead(3);

  if (a == HIGH) {
    Serial.print("NUM : ");
    Serial.println(num);
    num++;

    delay(500);
  }
}
