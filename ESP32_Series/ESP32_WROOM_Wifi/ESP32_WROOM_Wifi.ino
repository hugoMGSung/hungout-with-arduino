// CP210x_Universal_Windows_Driver.zip
#include <WiFi.h>

const char* ssid = "PKNU_54";       // 여기에 SSID 입력
const char* password = "Pknu5234*!";     // 여기에 암호 입력

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\nWiFi 접속 시도중...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi 접속 성공!");
  Serial.print("할당된 IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // 계속 접속된 상태로 대기
}
