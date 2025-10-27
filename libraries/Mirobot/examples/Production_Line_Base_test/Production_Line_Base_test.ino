#include <Wlkata_Mega_Sensor_Shield.h>
#include <Mirobot.h>
#include "RGB.h"

#define Start_btn  2  //start button pin
#define Stop_btn  3 //start button pin
#define A_btn  4  //start button pin
#define B_btn  5  //start button pin

int mirobotPause = 0;

RS485_Mirobot broadcast;   //broadcast
RS485_Mirobot mirobot_1;   //robotic arm 1

void setup() {
  Serial.begin(9600);
  rgbInit();
  shieldInit();
  
  broadcast.rs485Init(0);  //address 00
  mirobot_1.rs485Init(1);  //address 01
  mirobot_1.setSerialMonitoring(ON);
  
  for(int i=2;i<7;i++)  pinMode(i,INPUT_PULLUP);  //BUTTON

  buzzerAlarm(3,100);
  rgbSet(255, 255, 255);
  delay(2000);

  attachInterrupt(digitalPinToInterrupt(Stop_btn),STOP,FALLING);//STOP, key interrupt
}

void loop() {
  rgbAllWater(0, 0, 255, 50);//Light effect

  if(digitalRead(Start_btn) == 0) AUTO();
  if(digitalRead(A_btn) == 0) EVENT_A();
  if(digitalRead(B_btn) == 0) EVENT_B();
}

void AUTO(){
  Serial.println("START");
  rgbSet(0, 255, 0);
  while(mirobot_1.getStatus() != Alarm && mirobot_1.getStatus() != Idle);   //Confirm that robotic arm 1 is idle

  mirobot_1.sendMsg("$H",OFF);
  while(mirobot_1.getStatus() != Idle);   //Confirm that robotic arm 1 is idle

  mirobot_1.runFile("test");    //robotic arm 1 reset, and the verification of the returned information of the robotic arm is turned off
  delay(1000);
}

void STOP(){
  mirobotPause ++;
  if((mirobotPause % 2) == 1){
    Serial.println("---PAUSE---");
    broadcast.sendMsg("!",OFF);    //broadcast robot arm pause command
    rgbSet(255, 0, 0);
  }
  else{
    Serial.println("---PLAY---");
    broadcast.sendMsg("~",OFF);    //broadcast robotic arm continue command
    rgbSet(0, 255, 0);
  }
}

void EVENT_A(){
  mirobot_1.sendMsg("!",OFF);
  rgbSet(255, 255, 255);
  delay(500);
  rgbOff(); 
}

void EVENT_B(){
  mirobot_1.sendMsg("~",OFF);
  rgbSet(255, 255, 255);
  delay(500);
  rgbOff();
}
