# 스마트홈 키트 클로닝


## Day01
- 기본조립 및 스텝3 까지
	- 인체센서, LED, 
	- 터치센서, 사운드
	- 온습도센서 및 모터

<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/smarthome01.jpg" width="900" alt="스마트홈 진행중 1">

## Day02
- 스텝6까지
	- 근접센서 및 서보모터
	- 기패트 입력
	- 포터센서 및 7세그먼트
	
<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/smarthome02.jpg" width="900" alt="스마트홈 진행중 2">

## Day03
- 마무리
	- 수분센서
	- LCD패널
	- 불꽃센서(오류 및 소켓없음)
	
<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/smarthome03.jpg" width="900" alt="스마트홈 진행완료">

## Day04
- MQTT 통신
	- LCD패널 내용 변경

		<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/smarthome05.jpg" width="900" alt="스마트홈 통신">

	- LCD패널 텍스트가 USB연결 시만 동작, 파워연결 시에는 동작안함
		- 해결, 파워 W가 부족해서 생긴현상. 파워어댑터 변경
	- Wifi 실드연결
		- Wifi실드 및 Wifi기능이 탑재된 아두이노를 사용해도 GPIO와의 충돌로 사용불가
		- Wizfi250, Arduino R4 Wifi 등 모두 문제
		- 라즈베리파이와 연결로 해결함

<img src="https://raw.githubusercontent.com/hugoMGSung/study-smarthome/main/images/smarthome04.jpg" width="900" alt="스마트홈 통신">

## Day05
- MQTT 통신
	- 모니터링 프로그램 제작 및 연동
