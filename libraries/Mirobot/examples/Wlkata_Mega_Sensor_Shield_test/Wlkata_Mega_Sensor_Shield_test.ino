#include "Wlkata_Mega_Sensor_Shield.h"

void setup() {
  shieldInit();
  Serial.begin(9600);
  Serial1.begin(38400);
  for(int i=0;i<3;i++){
    shieldBuzzer(ON);
    delay(500);
    shieldBuzzer(OFF);
    delay(500);
  }
  shieldRgb(RED);
  delay(1000);
  shieldRgb(GREEN);
  delay(1000);
  shieldRgb(BLUE);
  delay(1000);
  shieldRgb(OFF);
  delay(1000);
}

void loop() {
  Serial.print("SW1: ");
  Serial.print(shieldKeyValue(SW1));
  Serial.print(" SW2: ");
  Serial.println(shieldKeyValue(SW2));
  Serial1.println("Serial1 OK");
  delay(500);
}
