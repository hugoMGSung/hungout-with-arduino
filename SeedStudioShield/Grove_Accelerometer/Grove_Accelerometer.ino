/*
  Grove - 3-Axis Digital Accelerometer (±16g) [ADXL345]
  - Base Shield I2C 포트 사용
  - X/Y/Z 가속도(g)와 간단한 Roll/Pitch 계산
*/

#include <Wire.h>

#define ADXL345_ADDR     0x53
#define REG_DEVID        0x00
#define REG_POWER_CTL    0x2D
#define REG_DATA_FORMAT  0x31
#define REG_BW_RATE      0x2C
#define REG_DATAX0       0x32

// 고정 오프셋(원하는 경우 테이블에 값을 넣어 보정)
float offsetX = 0.0f, offsetY = 0.0f, offsetZ = 0.0f;

void writeReg(uint8_t reg, uint8_t val) {
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}

uint8_t readReg(uint8_t reg) {
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);        // repeated start
  // Wire.requestFrom(ADXL345_ADDR, (uint8_t)1); // 오버로드 선택 문제
  Wire.requestFrom((uint8_t)ADXL345_ADDR, (uint8_t)1);  // <- 둘 다 uint8_t로
  return Wire.read();
}

void readXYZraw(int16_t &x, int16_t &y, int16_t &z) {
  Wire.beginTransmission(ADXL345_ADDR);
  Wire.write(REG_DATAX0);
  Wire.endTransmission(false);
  // Wire.requestFrom(ADXL345_ADDR, (uint8_t)6);
  Wire.requestFrom((uint8_t)ADXL345_ADDR, (uint8_t)6);  // <- 둘 다 uint8_t로
  x = (int16_t)(Wire.read() | (Wire.read() << 8));
  y = (int16_t)(Wire.read() | (Wire.read() << 8));
  z = (int16_t)(Wire.read() | (Wire.read() << 8));
}

void setup() {
  Serial.begin(115200);
  Wire.begin();

  // 장치 확인 (DEVID = 0xE5)
  uint8_t devid = readReg(REG_DEVID);
  Serial.print("ADXL345 DEVID = 0x");
  Serial.println(devid, HEX);

  // 샘플링 속도 100Hz (BW_RATE = 0x0A)
  writeReg(REG_BW_RATE, 0x0A);

  // DATA_FORMAT:
  //  FULL_RES(비트3)=1, 범위(비트1:0)=11 -> ±16g, full resolution (LSB≈3.9mg)
  writeReg(REG_DATA_FORMAT, 0b00001011);

  // 측정 시작 (POWER_CTL: Measure 비트3=1)
  writeReg(REG_POWER_CTL, 0b00001000);

  delay(10);

  // (선택) 간단한 오프셋 보정: 가만히 둔 상태에서 평균값을 빼기
  const int N = 100;
  long sx=0, sy=0, sz=0;
  for (int i=0; i<N; ++i) {
    int16_t rx, ry, rz;
    readXYZraw(rx, ry, rz);
    sx += rx; sy += ry; sz += rz;
    delay(5);
  }
  // full-res에서 1LSB ≈ 0.0039 g
  offsetX = (sx / (float)N) * 0.0039f;
  offsetY = (sy / (float)N) * 0.0039f;
  offsetZ = (sz / (float)N) * 0.0039f - 1.0f; // 정지 시 Z ≈ +1g 이므로 1g 보정

  Serial.println("Calibration done.");
}

void loop() {
  int16_t rx, ry, rz;
  readXYZraw(rx, ry, rz);

  // full-res 스케일: 약 3.9 mg/LSB
  float xg = rx * 0.0039f - offsetX;
  float yg = ry * 0.0039f - offsetY;
  float zg = rz * 0.0039f - offsetZ;

  // 간단한 기울기 계산 (라디안→도)
  float roll  = atan2(yg, zg) * 180.0f / PI;                 // x축 기준 좌우 기울기
  float pitch = atan2(-xg, sqrt(yg*yg + zg*zg)) * 180.0f / PI; // y축 기준 앞뒤 기울기

  Serial.print("X: "); Serial.print(xg, 3);
  Serial.print(" g, Y: "); Serial.print(yg, 3);
  Serial.print(" g, Z: "); Serial.print(zg, 3);
  Serial.print(" g | Roll: "); Serial.print(roll, 1);
  Serial.print(" deg, Pitch: "); Serial.print(pitch, 1);
  Serial.println(" deg");

  delay(50); // 약 20Hz 출력
}