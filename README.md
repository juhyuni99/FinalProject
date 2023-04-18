# FinalProject  
## 'IoT 스마트 홈'
> 🏡MQTT통신, Node-Red 환경을 이용한 IoT 스마트 홈 제작🏡
* 프로젝트 기간 : 2022.05 ~ 2022.06

* 기획 의도 : 주택에 거주하는 1인 가구를 대상으로 보다 편리하고 안전하게 생활할 수 있도록 다양한 기능을 갖춘 스마트 홈을 제작함. 자동제어, 관리 시스템, 편의 시스템에 초점을 맞춤.

## 📚얻은 역량
 * MQTT, Node-Red 활용 능력
 * AWS EC2 (Linux) 활용 능력
 * IBM Cloud 활용 능력
 * MPU(Raspberry pi) 활용 능력
 * Python virtual environment 활용 능력
 * Docker Container 활용
 * Google Assistant 활용
 * Cloud Server, Edge Server 에 대한 이해와 활용
 * 팀을 이끌어가는 능력
 * 팀원과의 소통을 통한 협업 능력

## 🔨사용 보드
 * Raspberry pi3
 * Esp8266

## ⚡사용 기술
 * Docker
 * Google Assistant
 * Bluetooth

## 사용언어
 * Python
 * C++

## 💡기능
* 기능 : 미세먼지 알라미, 뮤직 셀렉터, 스마트 가로등, 침입자 감지 메시지, 홈 관리 시스템, 미니 IoT Controler
<img width="416" alt="image" src="https://user-images.githubusercontent.com/102004234/232667637-f064386f-93fd-4854-a356-f93458b0af86.png">


* 기능 소개 

  * 뮤직 셀렉터: 구글어시스턴트를 이용하여 음성인식 음악 스피커 구현
  * 미니 IoT Controler : 구글어시스턴트 서비스에 mqtt통신을 추가시켜 edge와 cloud node-red에서 LED 제어(이 외에 센서 추가하여 간편하게 등록 가능 )
  * 스마트 가로등 : 주택 집 외부 벽=>Lux센서를 이용하여 가로등(NeoPixel) edge NodeRed로 제어 구현
  * 미세먼지 알라미: 기상청 정보와 날씨 api 크롤링하여 Node-Red UI에 시각화 
  * 홈 관리 시스템: Node-Red UI를 이용한 홈 관리 시스템
  * 침입자 감지 메시지: 초음파 센서를 통해 침입자 감지 후 이메일로 메시지 전송



 ### Could server
>>뮤직 셀렉터, 미세먼지 알라미, 침입자 감지 시스템, 미니 IoT Controler-LED 제어

 ### Edge server
>>미니 IoT Controler-google assistant mqtt publish, 스마트 가로등

## 1) 주택 집 외부 벽 가로등 구현

 * 어두운 저녁 범죄율이 높아짐. 
 * 범죄 예방을 위해 집 외부 벽에 조도센서와 네온픽셀 센서를 달아
밝기 감지에 따라 색이 변하는 스마트 가로등 구현
   (인터넷이 끊켜도 상관없는 자동 제어를 위해 edge단 서버 사용!)


<img width="548" alt="image" src="https://user-images.githubusercontent.com/102004234/174609093-181ed9ab-9b06-41cb-88c6-4238e8ba73d2.png">


 >> #### node-red
 > 
 > <img width="785" alt="image" src="https://user-images.githubusercontent.com/102004234/174479882-1d2d93f9-9951-48b5-88fc-ac9e7a2f82ec.png">


 >> #### code
 > ![image](https://user-images.githubusercontent.com/102004234/174607098-72ff1578-0e62-4168-ba15-6bf5b2257ab5.png)

### ✔️조도센서 Value 값에 따라 neopixel 색 지정
 * 어두울 때 : 쩅한 red+yellow
 * 약간 어두울 때 : sky
 * 밝을 때 : 색 없음

 >> #### code
 >
 ><img width="337" alt="image" src="https://user-images.githubusercontent.com/102004234/218678534-4937ff69-842e-4562-b032-162a6265892e.png">

![image](https://user-images.githubusercontent.com/102004234/174607955-085de658-31ce-4237-9242-63f88ab1f255.png)
![image](https://user-images.githubusercontent.com/102004234/174607976-41ba478d-6400-463d-b42b-df230d5b62b9.png)


 >> #### 동작영상


https://user-images.githubusercontent.com/102004234/174608405-8acd9e48-e88a-46ca-8f03-03997295095f.mp4



## 2) 뮤직 셀렉터

 * 구글 어시스턴트, TTS를 이용하여 음성인식, 출력 음악 재생 스피커 구현 + 인공지능 서비스 

<img width="550" alt="image" src="https://user-images.githubusercontent.com/102004234/174609293-fecb0f04-b8a9-4833-8aa5-4435ecd53a05.png">

<img width="519" alt="image" src="https://user-images.githubusercontent.com/102004234/174609438-aa74905f-1279-4454-8b05-80ab5f9d5167.png">


>> #### 동작영상
https://user-images.githubusercontent.com/102004234/218676085-64d86061-394a-4205-a512-f578d0ac6036.mp4



## 3) 미니 IoT Controler
 * 구글어시스턴트 서비스에 mqtt통신을 추가시켜 edge와 cloud node-red에서 LED 제어(이 외에 센서 추가하여 간편하게 등록 가능 )
 * Edge, cloud server 나누어 구현

<img width="577" alt="image" src="https://user-images.githubusercontent.com/102004234/174610150-90b854b8-3ac3-4487-a677-a22fbd3d1e2d.png">

 >> #### 동작영상1('불켜' => LED ON)

https://user-images.githubusercontent.com/102004234/218676322-d710aa09-0c2e-4a6e-ae83-c2a05d1a65d9.mp4



 >> #### 동작영상2('불꺼' => LED OFF)

https://user-images.githubusercontent.com/102004234/218676344-73eb76a4-0a48-4863-b13e-b2fdcf36da6c.mp4

## 4) 미세먼지 알라미
 * 공공데이터 API + 기상청 API를 가져와 보고싶은 정보만 추출
 * 날씨 데이터 -> 맑음, 흐림 등을 구분에 따라 다른 이미지 파일을 넣어 Node-Red UI로 깔끔한 화면 구성
<img width="415" alt="image" src="https://user-images.githubusercontent.com/102004234/232667870-315e6e21-c92a-42cc-a859-457b7c1db8d2.png">
Node-Red
<img width="418" alt="image" src="https://user-images.githubusercontent.com/102004234/232667891-7e1987ad-2385-4a60-a1b1-c3f7c6b1a789.png">

## 5) 침입자 감지 메시지
 * 일상모드, 감지모드
 * 감지모드 : 초음파 센서 가까이 인식되면 사전에 등록된 이메일로 알림 전송
 * 알림 기능을 통해 집을 비웠을 때 발생하는 상황에 대해 빠르게 대처 가능
<img width="416" alt="image" src="https://user-images.githubusercontent.com/102004234/232667937-73defbdf-3793-43b8-98e0-b4856ace9b38.png">
<img width="416" alt="image" src="https://user-images.githubusercontent.com/102004234/232667975-2afacf35-a5c0-4d63-b1c5-5b896ed8909b.png">

## 6) 홈 관리 시스템
 * 하나의 페이지에서 여러 센서 제어 가능 + 데이터 시각화
<img width="418" alt="image" src="https://user-images.githubusercontent.com/102004234/232668007-7cb8e7f7-2b33-4929-805c-4e529b655d1a.png">

## 후기
* 어러웠던 점 : 접속 불안정, 구글 어시스턴트 설치 오류
* 프로젝트 후기 : 기능과 구성을 좀 더 보완시켜 여름방학 때 개인적으로 새로운 작품을 만드는 것이 목표. 
교수님께서 피드백 해주신대로 iot컨트롤러 기능을 특정 단어로만 센서를 제어하지 말고 " 불 켜 " , " 전등 켜 " 다 인식 가능하도록 구현하기
