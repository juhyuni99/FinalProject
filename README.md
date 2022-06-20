### FinalProject  
## '스마트 홈'  


* 기획 의도 : 주택에 거주하는 1인 가구를 대상으로 보다 편리하고 안전하게 생활할 수 있도록 다양한 기능을 갖춘 스마트 홈을 제작함.


* 기능 : 미세먼지 알라미, 뮤직 셀렉터, 스마트 가로등, 침입자 감지 메시지, 홈 관리 시스템, 미니 IoT Controler


*** 기능 소개

뮤직 셀렉터: 구글어시스턴트를 이용하여 음성인식 음악 스피커 구현
미니 IoT Controler : 구글어시스턴트 서비스에 mqtt통신을 추가시켜 edge와 cloud node-red에서 LED 제어(이 외에 센서 추가하여 간편하게 등록 가능 )
스마트 가로등 : 주택 집 외부 벽=>Lux센서를 이용하여 가로등(NeoPixel) edge NodeRed로 제어 구현
미세먼지 알라미: 기상청 정보와 날씨 api 크롤링하여 Node-Red UI에 시각화 
홈 관리 시스템: Node-Red UI를 이용한 홈 관리 시스템
침입자 감지 메시지: 초음파 센서를 통해 침입자 감지 후 이메일로 메시지 전송





### 1)집 외부 가로등 구현

어두운 저녁 범죄율이 높아짐. 
범죄 예방을 위해 집 외부 벽에 조도센서와 네온픽셀 센서를 달아
밝기 감지에 따라 색이 변하는 스마트 가로등 구현
(인터넷이 끊켜도 상관없는 자동 제어를 위해 edge단 서버 사용!)

[image](https://user-images.githubusercontent.com/102004234/174600976-20296bc2-dade-4136-8930-76db37bc5d39.png)

[node-red]
<img width="785" alt="image" src="https://user-images.githubusercontent.com/102004234/174479882-1d2d93f9-9951-48b5-88fc-ac9e7a2f82ec.png">
