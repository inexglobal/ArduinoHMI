#include "RGB.h"

uint8_t ri = 0;
int8_t rj, rk;
uint8_t rgbMode = 0;
uint32_t previousMillis = 0;   //Stores the last time RGB was updated
uint32_t currentMillis;  //number of milliseconds elapsed since the microcontroller was running

Adafruit_NeoPixel rgb(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void rgbInit(){
  rgb.begin();
  rgb.clear();
  rgb.show();
}

void rgbSet(uint8_t r,uint8_t g, uint8_t b){
  for(int i=0;i<PIXEL_COUNT;i++){
    rgb.setPixelColor(i, rgb.Color(r, g, b)); 
  }
  rgb.show();
}

void rgbOff(){
  rgb.clear();
  rgb.show(); 
}

void rgbAllWater(uint8_t r,uint8_t g,uint8_t b, int wait){
  currentMillis = millis();
  rj = ri - 1;
  rk = ri - 2;
  if(ri > PIXEL_COUNT) ri = 0;
  if(rj == -1){
    rj = PIXEL_COUNT;
    rk = PIXEL_COUNT - 1;
  }
  if(currentMillis - previousMillis >= wait){
  previousMillis = currentMillis;
  rgb.clear();
  rgb.setPixelColor(ri,r,g,b);
  rgb.setPixelColor(rj,r/5,g/5,b/5);
  rgb.setPixelColor(rk,r/10,g/10,b/10);
  rgb.show();
  ri ++;
  }
}
