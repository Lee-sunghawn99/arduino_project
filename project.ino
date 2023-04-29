// 타이머를 이용해 현재시간을 계산합니다.
// 광,습도,압력센서를 입력으로 설정합니다.
// 서보모터를 출력으로 설정합니다.
// 07:00시가 되면 입력을 받습니다.
// 비오는 조건을 만족하면 서보모터를 작동해 조명을 켭니다.

#include "Arduino_SensorKit.h" //센서키트에 존재하는 센서를 사용하기위해 라이브러리를 불러옵니다.
#include <Servo.h> //서보모터를 사용하기위해 라이브러리를 불러옵니다.

Servo myservo; //서보모터를 제어하기 위해 서보 변수를 선언합니다.
int light_sensor = A3; // 광센서의 핀번호를 변수에 할당합니다.
int pos = 0; //서보모터의 각도를 할당할 변수를 선언합니다.
extern volatile unsigned long timer0_millis; //타이머변수를 선언합니다.
unsigned long timeVal; //이전타이머시간
unsigned long readTime; //현재타이머시간
int hour, min, sec; //시,분,초 
boolean state=false;

void setup() {
  Serial.begin(9600); // 시리얼 통신을 시작합니다.
  Pressure.begin(); // 압력센서를 구동합니다.
  Environment.begin(); //온,습도 센서를 구동합니다.
  myservo.attach(2); //서보모터를 연결한 핀을 제공합니다.
  Oled.begin(); //디스플레이를 활성화합니다.
  Oled.setFont(u8x8_font_artosserif8_r); // 디스플레이 폰트를 설정합니다.
  
  
}

void loop() {
  //시리얼 통신을 통해 "12:00:00"과 같이 시간이 입력되면 시,분,초를 분리해 변수해 저장합니다.
  //분리할때 ":"를 기준값으로 사용합니다.
  if(Serial.available()){ // 시리얼 통신을 이용해 아두이노에게 현재시간을 입력합니다.
    String inString = Serial.readStringUntil('\n'); //엔터 값을 만날때 까지의 입력값을 읽습니다.   
    int index1 = inString.indexOf(':'); //":"가 문자열에서 존재하는 위치를 저장하는 변수를 선언합니다.
    int index2 = inString.indexOf(':',index1+1);  // 두번째":" 가 존재하는 위치를 저장하는 변수를 선언합니다.
    int index3 = inString.length(); // 입력된 문자열의 길이를 저장하는 변수를 선언합니다.
    
    hour = inString.substring(0, index1).toInt(); // 처음부터 ":"가 존재하는 위치까지의 문자열을 정수로 반환해 시로 저장합니다.
    min = inString.substring(index1+1,index2).toInt();// 첫번째":" 다음 문자부터 두번째":"까지의 문자열을 정수로 반환해 분으로 저장합니다.
    sec = inString.substring(index2+1,index3).toInt();// 두번째":" 다음 문자부터 문자열 끝까지의 문자열을 정수로 반환해 초로 저장합니다.
  
    
    timer0_millis = ((long)hour*3600+min*60+sec)*1000; // 입력된 현재시간의 ms단위로 반환해 저장합니다.
    state=true;
    timeVal=millis(); //입력된 시간을 기준이후로 흐른 ms시간을 출력합니다.
  }
  if(state==true){ //시리얼모니털 출력 시작
    
    if(millis()-timeVal>=1000){ //매1초마다 코드를 작동합니다.
     readTime = millis()/1000; // ms를 s로 변환합니다.
      
     if(millis()>=86400000){ // 24시간이 지나면 타이머를 초기화 합니다.
       timer0_millis=0;
     }
     timeVal = millis(); 
   
     sec = readTime%60; 
     min = (readTime/60)%60;
     hour = (readTime/(60*60))%24;       
     Oled.setCursor(0,3);
     Oled.setFlipMode(true); // 디스플레이의 방향을 맞게 설정합니다.
    
    //시간을 디스플레이에 출력합니다.
     Oled.print(hour);
     Oled.print(" : ");
     Oled.print(min);
     Oled.print(" : ");
     Oled.println(sec);      
    }
  }
  if (hour== 17 & min ==28 & sec ==00){ // 지정한 시간이 되면 외부 환경을 센싱합니다.
    sensing_weather();
  }


}

float average(float prevAvg, float newNumber, float listLength){ // 평균필터 알고리즘을 사용한 평균을 구합니다.
  float oldWeight = (listLength-1)/ listLength; // 현재평균의 가중치를 n/n-1로 설정합니다.
  float newWeight = 1/ listLength; // 새로운 값의 가중치를 1/n으로 설정합니다.
  float newAvg = (prevAvg * oldWeight) + (newNumber * newWeight); // 가중치와 현재평균을 이용해 새로운 평균을 계산합니다.
  return newAvg; // 새로운 평균을 반환합니다.

}

void sensing_weather(){ 
  float pressure_Avg; //압력평균을 저장할 변수를 생성합니다.
  float light_Avg;  // 광도평균을 저장할 변수를 생성합니다.
  float Humidity_Avg; //습도평균을 저장할 변수를 생성합니다.

  
  for (int i=1; i<=11; i++){ // 루프를 돌면서 10번의 계측결과를 평균필터 방식으로 평균을 구합니다.
    pressure_Avg = average(pressure_Avg,Pressure.readPressure(),i); 
    light_Avg = average(light_Avg,analogRead(light_sensor),i);
    Humidity_Avg = average(Humidity_Avg,Environment.readHumidity(),i);
    delay(15); // 각 관측값 사이에 15ms의 간격을 둡니다.
  }

  
  if (pressure_Avg <= 99400 & light_Avg <= 150 & Humidity_Avg >=55) // 어두운 조건에 맞았을떄 조명을 켜줍니다. 
  {
    light_up(); //조명을 켜는 함수를 호출합니다.
  }
  
}


void light_up() { // 전등을 켜주는 함수를 선언합니다.
  for (pos = 0; pos <= 60; pos += 1) { // 0~60도를 한스텝이 1도 씩 증가시킵니다.
    myservo.write(pos);                // pos변수로 서보모터의 각도를 결정합니다.
    delay(15);                        // 서보모터가 설정 각도에 도달 한 후 15ms를 기다립니다.
  }
  for (pos = 60; pos >= 0; pos -= 1) { // 60~0도를 한스텝이 1도 씩 감소시킵니다.
    myservo.write(pos);              // pos변수로 서보모터의 각도를 결정합니다.
    delay(15);                       // 서보모터가 설정 각도에 도달 한 후 15ms를 기다립니다.
  }
}
