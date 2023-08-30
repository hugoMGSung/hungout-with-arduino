int Relaypin = 3;
int Switch = 9;
 
void setup()
{
  pinMode(Relaypin,OUTPUT);         // 릴레이를 출력으로 설정
  pinMode(Switch,INPUT_PULLUP);     // 스위치를 입력으로 설정
}
 
void loop()
{
  if(digitalRead(Switch)==LOW)       // 스위치를 누르면
  {
    digitalWrite(Relaypin,HIGH);     // 1채널 릴레이 ON
    delay(100);
  }
  else                               // 스위치를 누르지 않으면 
  {
    digitalWrite(Relaypin,LOW);      // 1채널 릴레이 OFF
    delay(100);
  }
}