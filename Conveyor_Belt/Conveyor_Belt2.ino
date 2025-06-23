int IN1 = 2;
int IN2 = 3;
int ENA = 10;

void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
}

void loop() {
  // 정방향 회전
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 100);  // 속도 (0~255)
  delay(10000);

  // 정지
  analogWrite(ENA, 0);
  delay(2000);
}