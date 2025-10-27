#include "Mirobot.h"
#include "Wlkata_Shield.h"

void setup() {
  shieldInit();
  Serial.begin(9600); //monitor serial port
  Serial1.begin(115200);
  Serial.println("TEST");
}

void loop() {
  String testCode = "";
  if(Serial.available()>0){
    testCode = Serial.readString();
    Serial1.println(testCode);
    while(Serial.read() >= 0){};
  }
  String RS485back = "";
  if(Serial1.available()>0){
    testCode = Serial1.readString();
    Serial.println(RS485back);
    while(Serial1.read() >= 0){};
  }
}
