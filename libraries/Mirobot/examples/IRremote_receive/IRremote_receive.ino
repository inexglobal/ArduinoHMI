#include <IRremote.h>
 
IRrecv irrecv(RECV_PIN);
 
decode_results results;
 
void setup()
{
  Serial.begin(9600);
  //If there is a problem in the startup process, notify the start failure
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");
}
 
void loop() {
  if (irrecv.decode(&results)) { //Check whether the infrared remote control signal is received
    Serial.println(results.value, HEX); //output command information
    irrecv.resume();                    //receive next command
  }
  delay(100);
}
