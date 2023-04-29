#include <Dynamixel2Arduino.h> //다이나믹셀 라이브러리를 추가합니다.
#include <SoftwareSerial.h>

SoftwareSerial soft_serial(7, 8);
SoftwareSerial myserial(3,4);

//다이나믹셀의 통신을 위해 변수를 선언합니다.
#define DXL_SERIAL Serial
#define DEBUG_SERIAL soft_serial
#define BLUETOOTH_SERIAL myserial


char value;
const int DXL_DIR_PIN = 2;//보드 종류에 맞는 DIR_PIN을 설정합니다. openrb-150은 별도로 필요하지 않기에 -1을 저장합니다.
int wheel_velocity = 0;
int acc_time= 100;
float ID_0_position = 0;
float ID_1_position = 0;
float ID_3_position = 0;
float ID_4_position = 0;
float ID_6_position = 0;
float ID_7_position = 0;
float ID_9_position = 0;
float ID_10_position = 0;



//각 모터의 번호를 변수를 선언해 저장합니다.
const uint8_t DXL_ID_0 = 0;
const uint8_t DXL_ID_1 = 1;
const uint8_t DXL_ID_2 = 2;
const uint8_t DXL_ID_3 = 3;
const uint8_t DXL_ID_4 = 4;
const uint8_t DXL_ID_5 = 5;
const uint8_t DXL_ID_6 = 6;
const uint8_t DXL_ID_7 = 7;
const uint8_t DXL_ID_8 = 8;
const uint8_t DXL_ID_9 = 9;
const uint8_t DXL_ID_10 = 10;
const uint8_t DXL_ID_11 = 11;


//다이나믹셀의 통신 버전을 저장합니다.
const float DXL_PROTOCOL_VERSION = 2.0;

Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);


//ControlTalbeItem을 사용하기 위해 네임스페이스를 사용합니다.
using namespace ControlTableItem;   

void setup() {
  
  BLUETOOTH_SERIAL.begin(9600);
  DEBUG_SERIAL.begin(9600);


  dxl.begin(57600);//다이나믹셀의 기본 통신속도인 57600bps로 통신속도를 설정합니다.
  dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);//다이나믹셀과 일치하는 프로토콜 버전을 설정합니다.

  

  //다이나믹셀로 부터 정보를 수신합니다.
  dxl.ping(DXL_ID_0);
  dxl.ping(DXL_ID_1);
  dxl.ping(DXL_ID_2);
  dxl.ping(DXL_ID_3);
  dxl.ping(DXL_ID_4);
  dxl.ping(DXL_ID_5);
  dxl.ping(DXL_ID_6);
  dxl.ping(DXL_ID_7);
  dxl.ping(DXL_ID_8);
  dxl.ping(DXL_ID_9);
  dxl.ping(DXL_ID_10);
  dxl.ping(DXL_ID_11);

  
  //다이나믹셀에 부착된 LED를 켭니다.
  dxl.ledOn(DXL_ID_0);
  dxl.ledOn(DXL_ID_1);
  dxl.ledOn(DXL_ID_2);
  dxl.ledOn(DXL_ID_3);
  dxl.ledOn(DXL_ID_4);
  dxl.ledOn(DXL_ID_5);
  dxl.ledOn(DXL_ID_6);
  dxl.ledOn(DXL_ID_7);
  dxl.ledOn(DXL_ID_8);
  dxl.ledOn(DXL_ID_9);
  dxl.ledOn(DXL_ID_10);
  dxl.ledOn(DXL_ID_11);
  delay(500);
  
  //다이나믹셀에 부착된 LED를 끕니다.
  dxl.ledOff(DXL_ID_0);
  dxl.ledOff(DXL_ID_1);
  dxl.ledOff(DXL_ID_2);
  dxl.ledOff(DXL_ID_3);
  dxl.ledOff(DXL_ID_4);
  dxl.ledOff(DXL_ID_5);
  dxl.ledOff(DXL_ID_6);
  dxl.ledOff(DXL_ID_7);
  dxl.ledOff(DXL_ID_8);
  dxl.ledOff(DXL_ID_9);
  dxl.ledOff(DXL_ID_10);
  dxl.ledOff(DXL_ID_11);
  delay(500);

  //EEPROM 영역을 수정할때 다이나믹셀의 토크를 끕니다.
  dxl.torqueOff(DXL_ID_0);
  dxl.torqueOff(DXL_ID_1);
  dxl.torqueOff(DXL_ID_2);
  dxl.torqueOff(DXL_ID_3);
  dxl.torqueOff(DXL_ID_4);
  dxl.torqueOff(DXL_ID_5);
  dxl.torqueOff(DXL_ID_6);
  dxl.torqueOff(DXL_ID_7);
  dxl.torqueOff(DXL_ID_8);
  dxl.torqueOff(DXL_ID_9);
  dxl.torqueOff(DXL_ID_10);
  dxl.torqueOff(DXL_ID_11);
  

  //다이나믹셀을 실행 모드로 설정합니다.
  dxl.setOperatingMode(DXL_ID_0, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_1, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_2, OP_VELOCITY);
  dxl.setOperatingMode(DXL_ID_3, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_4, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_5, OP_VELOCITY);
  dxl.setOperatingMode(DXL_ID_6, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_7, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_8, OP_VELOCITY);
  dxl.setOperatingMode(DXL_ID_9, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_10, OP_POSITION);
  dxl.setOperatingMode(DXL_ID_11, OP_VELOCITY);
  dxl.setOperatingMode(DXL_ID_11, OP_VELOCITY);
  
  //EEPROM 영역 수정 후 다이나믹셀의 토크를 킵니다.
  dxl.torqueOn(DXL_ID_0);
  dxl.torqueOn(DXL_ID_1);
  dxl.torqueOn(DXL_ID_2);
  dxl.torqueOn(DXL_ID_3);
  dxl.torqueOn(DXL_ID_4);
  dxl.torqueOn(DXL_ID_5);
  dxl.torqueOn(DXL_ID_6);
  dxl.torqueOn(DXL_ID_7);
  dxl.torqueOn(DXL_ID_8);
  dxl.torqueOn(DXL_ID_9);
  dxl.torqueOn(DXL_ID_10);
  dxl.torqueOn(DXL_ID_11);
}

void loop(){
  BLUETOOTH_SERIAL.listen();
  while(BLUETOOTH_SERIAL.available ())
  {
    value= BLUETOOTH_SERIAL.read();
    DEBUG_SERIAL.println(value);
  
    
    if(value =='a'){
    //DEBUG_SERIAL.println("speed_up");
    up();
  
    }else if(value =='b'){
    //DEBUG_SERIAL.println("stop");
    stop();
  
    }else if(value == 'c'){
    //DEBUG_SERIAL.println("speed_down");
    down();
    
    }else if(value == 'd'){
   // DEBUG_SERIAL.println("ID_0_clockwise");
    ID_0_clock();

    }else if(value == 'e'){
    //DEBUG_SERIAL.println("ID_0_counterclockwise");
    ID_0_counterclock();
    
    }else if(value == 'f'){
    //DEBUG_SERIAL.println("ID_1_clockwise");
    ID_1_clock();

    }else if(value == 'g'){
    //DEBUG_SERIAL.println("ID_1_counterclockwise");
    ID_1_counterclock();

    }else if(value == 'h'){
    //DEBUG_SERIAL.println("ID_3_clockwise");
    ID_3_clock();

    }else if(value == 'i'){
    //DEBUG_SERIAL.println("ID_3_counterclockwise");
    ID_3_counterclock();

    }else if(value == 'j'){
    //DEBUG_SERIAL.println("ID_4_clockwise");
    ID_4_clock();

    }else if(value == 'k'){
    //DEBUG_SERIAL.println("ID_4_counterclockwise");
    ID_4_counterclock();

    }else if(value == 'l'){
    //DEBUG_SERIAL.println("ID_6_clockwise");
    ID_6_clock();

    }else if(value == 'm'){
    //DEBUG_SERIAL.println("ID_6_counterclockwise");
    ID_6_counterclock();
    
    }else if(value == 'n'){
    //DEBUG_SERIAL.println("ID_7_clockwise");
    ID_7_clock();
    }else if(value == 'o'){
    //DEBUG_SERIAL.println("ID_7_counterclockwise");
    ID_7_counterclock();

    }else if(value == 'p'){
    //DEBUG_SERIAL.println("ID_9_clockwise");
    ID_9_clock();

    }else if(value == 'q'){
    //DEBUG_SERIAL.println("ID_9_counterclockwise");
    ID_9_counterclock();

    }else if(value == 'r'){
    //DEBUG_SERIAL.println("ID_10_clockwise");
    ID_10_clock();

    }else if(value == 's'){
    //DEBUG_SERIAL.println("ID_10_counterclockwise");
    ID_10_counterclock();
    }

  }
}

void up() {
  wheel_velocity = wheel_velocity + 50;
  dxl.setGoalVelocity(DXL_ID_2, -wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_5, wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_8, -wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_11, wheel_velocity); 
}

void stop() {
  wheel_velocity = 0;
  dxl.setGoalVelocity(DXL_ID_2, wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_5, wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_8, wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_11, wheel_velocity); 
}

void down() {
  wheel_velocity = wheel_velocity - 50;
  dxl.setGoalVelocity(DXL_ID_2, -wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_5, wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_8, -wheel_velocity);
  dxl.setGoalVelocity(DXL_ID_11, wheel_velocity);
}

void ID_0_clock() {
  ID_0_position = ID_0_position + 274;
  dxl.setGoalPosition(DXL_ID_0, ID_0_position);
}

void ID_0_counterclock() {
  ID_0_position = ID_0_position - 274;
  dxl.setGoalPosition(DXL_ID_0, ID_0_position);
}

void ID_1_clock() {
  ID_1_position = ID_1_position + 274;
  dxl.setGoalPosition(DXL_ID_1, ID_1_position);
}

void ID_1_counterclock() {
  ID_1_position = ID_1_position - 274;
  dxl.setGoalPosition(DXL_ID_1, ID_1_position);
}

void ID_3_clock() {
  ID_3_position = ID_3_position + 274;
  dxl.setGoalPosition(DXL_ID_3, ID_3_position);
}

void ID_3_counterclock() {
  ID_3_position = ID_3_position - 274;
  dxl.setGoalPosition(DXL_ID_3, ID_3_position);
}


void ID_4_clock() {
  ID_4_position = ID_4_position + 274;
  dxl.setGoalPosition(DXL_ID_4, ID_4_position);
}

void ID_4_counterclock() {
  ID_4_position = ID_4_position - 274;
  dxl.setGoalPosition(DXL_ID_4, ID_4_position);
}

void ID_6_clock() {
  ID_6_position = ID_6_position + 274;
  dxl.setGoalPosition(DXL_ID_6, ID_6_position);
}

void ID_6_counterclock() {
  ID_6_position = ID_6_position - 274;
  dxl.setGoalPosition(DXL_ID_6, ID_6_position);
}

void ID_7_clock() {
  ID_7_position = ID_7_position + 274;
  dxl.setGoalPosition(DXL_ID_7, ID_7_position);
}

void ID_7_counterclock() {
  ID_7_position = ID_7_position - 274;
  dxl.setGoalPosition(DXL_ID_7, ID_7_position);
}

void ID_9_clock() {
  ID_9_position = ID_9_position + 274;
  dxl.setGoalPosition(DXL_ID_9, ID_9_position);
}

void ID_9_counterclock() {
  ID_9_position = ID_9_position - 274;
  dxl.setGoalPosition(DXL_ID_9, ID_9_position);
}

void ID_10_clock() {
  ID_10_position = ID_10_position + 274;
  dxl.setGoalPosition(DXL_ID_10, ID_10_position);
}

void ID_10_counterclock() {
  ID_10_position = ID_10_position - 274;
 dxl.setGoalPosition(DXL_ID_10, ID_10_position);
}


