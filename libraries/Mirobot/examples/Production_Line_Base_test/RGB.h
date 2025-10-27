#ifndef __RGB_H__
#define __RGB_H__

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    8  // Digital pins for RGB strip connections
#define PIXEL_COUNT 47  // Number of LED lights

void rgbInit();
void rgbSet(uint8_t r,uint8_t g, uint8_t b);
void rgbOff();
void rgbAllWater(uint8_t r,uint8_t g,uint8_t b, int wait);

#endif
