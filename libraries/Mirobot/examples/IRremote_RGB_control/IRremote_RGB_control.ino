/*
 * IRremote_RGB_control
 * ======================== Function Description =======================
 * Demonstrate the use of infrared remote control to control the color of RGB lights on the expansion board, use the remote control to check
 * Battery power, when the power is low, the signal is weak and difficult to be received.
 * "1" key------red
 * "2" key------green
 * "3" key------blue
 * "OK" key ----- off
 *
 * This sample program is for use with Wlkata Mega Sensor Shield supporting remote control,
 * For other infrared remote controllers, please use the sample program "IRremote_receive" to obtain the corresponding key values
 * 
 */
#include "Wlkata_Mega_Sensor_Shield.h"
#include <IRremote.h>
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;

void setup() {
  shieldInit();
  Serial.begin(9600);

  // If there is a problem in the startup process, notify start failure
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}

void loop() {
  if(irrecv.decode(&results)){ //Check whether the infrared remote control signal is received
    Serial.println(results.value, HEX);
      
    if(results.value == 0xFFA25D){ //Press the "1" key          
      shieldRgb(RED); 
    } 
    
    if(results.value == 0xFF629D){ //Press the "2" key          
      shieldRgb(GREEN); 
    }

    if(results.value == 0xFFE21D){ //Press the "3" key         
      shieldRgb(BLUE); 
    }

    if(results.value == 0xFF38C7){ //Press the "OK" key         
      shieldRgb(OFF); 
    }
    irrecv.resume(); //receive next command
  }
  delay(100);
}
