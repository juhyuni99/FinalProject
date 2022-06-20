# FinalProject  
## '스마트 홈'  


* 기획 의도 : 주택에 거주하는 1인 가구를 대상으로 보다 편리하고 안전하게 생활할 수 있도록 다양한 기능을 갖춘 스마트 홈을 제작함.


* 기능 : 미세먼지 알라미, 뮤직 셀렉터, 스마트 가로등, 침입자 감지 메시지, 홈 관리 시스템, 미니 IoT Controler


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

### 1)집 외부 가로등 구현

어두운 저녁 범죄율이 높아짐. 
범죄 예방을 위해 집 외부 벽에 조도센서와 네온픽셀 센서를 달아
밝기 감지에 따라 색이 변하는 스마트 가로등 구현
(인터넷이 끊켜도 상관없는 자동 제어를 위해 edge단 서버 사용!)


<img width="548" alt="image" src="https://user-images.githubusercontent.com/102004234/174609093-181ed9ab-9b06-41cb-88c6-4238e8ba73d2.png">


[image](https://user-images.githubusercontent.com/102004234/174600976-20296bc2-dade-4136-8930-76db37bc5d39.png)

[node-red]
<img width="785" alt="image" src="https://user-images.githubusercontent.com/102004234/174479882-1d2d93f9-9951-48b5-88fc-ac9e7a2f82ec.png">


![image](https://user-images.githubusercontent.com/102004234/174607098-72ff1578-0e62-4168-ba15-6bf5b2257ab5.png)

### 조도센서 Value 값에 따라 neopixel 색 지정
 * 어두울 때 : 쩅한 red+yellow
 * 약간 어두울 때 : sky
 * 밝을 때 : 색 없음
![image](https://user-images.githubusercontent.com/102004234/174607131-c4989f2c-0d63-4b63-a347-26e15e4b367f.png)
![image](https://user-images.githubusercontent.com/102004234/174607955-085de658-31ce-4237-9242-63f88ab1f255.png)
![image](https://user-images.githubusercontent.com/102004234/174607976-41ba478d-6400-463d-b42b-df230d5b62b9.png)


https://user-images.githubusercontent.com/102004234/174608405-8acd9e48-e88a-46ca-8f03-03997295095f.mp4



### 2) 뮤직 셀렉터

구글 어시스턴트, TTS를 이용하여 음성인식, 출력 음악 재생 스피커 구현
+인공지능 서비스 
<img width="550" alt="image" src="https://user-images.githubusercontent.com/102004234/174609293-fecb0f04-b8a9-4833-8aa5-4435ecd53a05.png">

<img width="519" alt="image" src="https://user-images.githubusercontent.com/102004234/174609438-aa74905f-1279-4454-8b05-80ab5f9d5167.png">


