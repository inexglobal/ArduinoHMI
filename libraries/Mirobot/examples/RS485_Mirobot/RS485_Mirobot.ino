/*
 * RS485_Mirobot
 * ======================== Function Description =======================
 * Demonstrate how to use the Arduino development board to send data to two robotic arms through the RS485 bus
 * Control commands to command multiple robotic arms to operate in coordination
 *
 * ====================== Robotic Arm Settings ======================
 * Use WlkataStudio-V1.019.20 to update the latest firmware for the robotic arm and controller,
 * The "Port" of the multi-function controller is set to "RS485"
 * The controller addresses of the two robotic arms are set to "01" and "02:" respectively
 * For the setting method, please refer to "Multi-function Controller User Manual"
 *
 * ======================= Circuit Connection ======================
 * Mage Sensor Shield RS485 --- Multi-function controller "RS485" interface
 *
 * This sample program is for use with the Mirobot robot arm, and cannot be executed normally without connecting the robot arm
 * 
 */
#include <Mirobot.h>  //include header file

//Create the robotic arm object
RS485_Mirobot arm1;
RS485_Mirobot arm2;

void setup(){
  Serial.begin(9600); //Initialize the serial port, the baud rate is 9600
  arm1.rs485Init(); //Initial setting, default address 01
  arm2.rs485Init(2);  //Initialize settings, set the object address to 02
  arm1.setSerialMonitoring(ON); //Set to open the serial port monitor, and print information through the Arduino serial port monitor
  while(arm1.getStatus() != Alarm || arm2.getStatus() != Alarm);  //Wait for the two robotic arms to be powered on
  arm1.sendMsg("$H",OFF); //arm1 is reset (HOME), and the verification of the information returned by the robotic arm is turned off
  delay(500);
  arm2.sendMsg("$H",OFF);
  while(arm1.getStatus() != Idle || arm2.getStatus() != Idle);  //Wait for the robotic arm to home and become idle
  arm1.setMoveSpeed(3000); //Set the maximum movement speed of the robotic arm to 3000
  arm2.setMoveSpeed(3000); //Set the maximum movement speed of the robotic arm to 3000
  arm1.moveJoints(-90,10,-90,60,10,10);
  arm2.moveJoints(-90,10,-90,60,10,10);
  arm1.zero();
  arm2.zero();
  arm1.runFile("test"); //Run the "test.gcode" file stored in the controller
  arm2.runFile("test");
}
void loop(){
  
}
