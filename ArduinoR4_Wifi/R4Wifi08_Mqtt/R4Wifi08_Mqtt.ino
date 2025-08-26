#include <WiFiS3.h>
#include <ArduinoMqttClient.h>

/////// 비밀 탭/arduino_secrets.h에 민감한 데이터 입력
char ssid[] = "AP-107-1304";        // 네트워크 SSID(이름)
char pass[] = "6244?e81";    // 네트워크 비밀번호(WPA에 사용하거나 WEP에 대한 키로 사용)
int status = WL_IDLE_STATUS;     // WiFi 라디오 상태

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "172.16.11.223";
int        port     = 1883;
const char topic[]  = "ToDevice/TopicForClient";
const char hostTopic[] = "ToHost/TopicForClient";

const long interval = 5000;
unsigned long previousMillis = 0;

void setup() {
  // 직렬을 초기화하고 포트가 열릴 때까지 대기
  Serial.begin(9600);

  while (!Serial) {
    ; // 직렬 포트가 연결될 때까지 대기. 기본 USB 포트에만 필요
  }

  // WiFi 모듈을 확인 요
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("WiFi 모듈과의 통신 실패!");
    // 계속하지 마셈
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("펌웨어 업그레이드 필요");
  }

  // WiFi 네트워크에 연결을 시도
  while (status != WL_CONNECTED) {
    Serial.print("WPA SSID 연결 시도중: ");
    Serial.println(ssid);
    // WPA/WPA2 네트워크 연결:
    status = WiFi.begin(ssid);

    // 인터벌 동안 대기:
    delay(interval);
  }

  // 연결되고 내용 출력:
  Serial.print("네트워크 연결 성공");
  printCurrentNet();
  printWifiData();

  // 고유한 클라이언트 ID 제공 가능. 미설정 시 라이브러리는 Arduino-millis()를 사용.
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");

  // 인증을 위해 사용자 이름과 비밀번호를 제공 가능
  // mqttClient.setUsernamePassword("username", "password");

  Serial.print("MQTT 브로커 연결 시도 중: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT 연결 실패! 에러 코드 = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("MQTT 브로커 연결!");
  Serial.println();

  // 메시지 수신 콜백 설정
  mqttClient.onMessage(onMqttMessage);

  Serial.print("주제 구독 중: ");
  Serial.println(topic);
  Serial.println();

  // 주제 구독
  mqttClient.subscribe(topic);

  // 아래 함수로 주제 구독 취소:
  // mqttClient.unsubscribe(topic);

  Serial.print("주제 메시지 대기중: ");
  Serial.println(topic);
  Serial.println();

}

void loop() {
  // 라이브러리가 MQTT 메시지를 수신할 수 있도록 정기적으로 poll()을 호출
  // 브로커에 의한 연결 끊김을 방지하는 MQTT 연결 유지를 전송.
  mqttClient.poll();

  // 지속적인 핑을 방지하려면 지연을 추가
  delay(5000);
}

void printWifiData() {
  // 보드의 IP 주소를 인쇄:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP 주소: ");
  
  Serial.println(ip);

  // print your MAC address:
  byte mac[6];
  WiFi.macAddress(mac);
  Serial.print("MAC 주소: ");
  printMacAddress(mac);
}

void printCurrentNet() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print the MAC address of the router you're attached to:
  byte bssid[6];
  WiFi.BSSID(bssid);
  Serial.print("BSSID: ");
  printMacAddress(bssid);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("신호 강도 (RSSI):");
  Serial.println(rssi);

  // print the encryption type:
  byte encryption = WiFi.encryptionType();
  Serial.print("암호화 타입:");
  Serial.println(encryption, HEX);
  Serial.println();
}

void printMacAddress(byte mac[]) {
  for (int i = 5; i >= 0; i--) {
    if (mac[i] < 16) {
      Serial.print("0");
    }
    Serial.print(mac[i], HEX);
    if (i > 0) {
      Serial.print(":");
    }
  }
  Serial.println();
}


void onMqttMessage(int messageSize) {
  // 메시지를 받았습니다. 주제와 내용을 인쇄
  Serial.print("주제가 포함된 메시지 수신 '");
  Serial.print(mqttClient.messageTopic());
  Serial.println("'");
  Serial.print("메시지 길이: ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  // 메시지 내용을 문자열로 읽어
  String message = mqttClient.readString();

  // 수신된 메시지와 비교 문자열을 소문자로 변환
  message.toLowerCase();

  // 해결 또는 재설정에 대한 메시지 내용이 일치하는지 확인
  if(message == "whatYouWantToSee") {
    onCustom();
    Serial.println("디버깅을 위한 사용자 정의 메시지");
  } else if (message == "whatYouWantToSee2") {
    onCustom2();
    Serial.println("디버깅을 위한 사용자 정의 메시지2");
  } else {
    // If it doesn't match either of the key words, print the message contents for debugging
  Serial.print("내 ESP32에 보내는 메시지");
  Serial.println(message);
  }
  Serial.println();

}

void onCustom(){
  //Code you want to run when message 1 gets here
}

void onCustom2(){
  //Code you want to run when message 1 gets here
}