# ESP13 Wifi Webserver Shield

## 설정 후 코딩

- 작업순서
	- 기본 아두이노 소스 코딩 (실드를 빼고 Arduino UNO로 설정 소스를 집어넣음) 
	- 서버측 파이썬 코딩
	
```console
기본소스를 업로드 한 뒤 와이파이 실드를 연결하고 설정된 대로 동작시킵니다.

> telnet 192.168.0.208 9090 

// 접속 후 아래와 같이 메시지 나옴
Hello PHPoC Shield for Arduino!!
Hello PHPoC Shield for Arduino!!
Hello PHPoC Shield for Arduino!!
Hello PHPoC Shield for Arduino!!
Hello PHPoC Shield for Arduino!!
...

```

- 파이썬에서 위의 값이 넘어옴

<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/esp8266_shield07.jpg" width="600" alt="컴파일 결과">

- 콘솔 Telnet 결과

<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/esp8266_shield08.jpg" width="800" alt="콘솔 Telnet">


