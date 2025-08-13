// === Pins ===
const int IR_LEFT  = A0;   // LOW = 감지
const int IR_RIGHT = A1;   // LOW = 감지
const int MOTOR_PWM = 10;
const int MOTOR_DIR = 12;

const int RUN_SPEED = 90;

enum { IDLE, RUNNING } state = IDLE;

// 필요하면 풀업으로 더 안정화
// pinMode(IR_LEFT,  INPUT_PULLUP);
// pinMode(IR_RIGHT, INPUT_PULLUP);

void startConveyor() {
  digitalWrite(MOTOR_DIR, HIGH);
  analogWrite(MOTOR_PWM, RUN_SPEED);
  Serial.println("START");
}

void stopConveyor() {
  analogWrite(MOTOR_PWM, 0);   // 코스팅 정지
  Serial.println("STOP");
}

bool prevL=false, prevR=false;

void setup() {
  Serial.begin(9600);
  pinMode(IR_LEFT,  INPUT);
  pinMode(IR_RIGHT, INPUT);
  pinMode(MOTOR_DIR, OUTPUT);
  stopConveyor();
}

void loop() {
  bool L = (digitalRead(IR_LEFT)  == LOW);
  bool R = (digitalRead(IR_RIGHT) == LOW);

  bool L_edge = L && !prevL;
  // bool R_edge = R && !prevR;   // 필요하면 디버깅용

  if (state == IDLE) {
    if (L_edge) {               // 왼쪽 '들어올 때' 시작
      startConveyor();
      state = RUNNING;
    }
  } else { // RUNNING
    // 🔴 레벨 트리거: 오른쪽이 LOW인 '현재'면 즉시 정지
    if (R) {
      stopConveyor();
      state = IDLE;
    }
  }

  prevL = L; prevR = R;
  delay(2); // 아주 짧게
}