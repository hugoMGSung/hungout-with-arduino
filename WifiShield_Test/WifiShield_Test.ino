int num = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  Serial.print("NUM : ");
  Serial.println(num);
  num++;

  delay(500);
}
