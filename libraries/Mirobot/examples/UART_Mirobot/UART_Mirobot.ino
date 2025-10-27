/*
 * Use the Serial2 serial port to communicate with the robotic arm
 */
#include <Mirobot.h>  //include header file

UART_Mirobot myrobot; //Create the robotic arm object

void setup(){
  Serial.begin(9600); //Initialize the serial port, the baud rate is 9600
  myrobot.serialInit(2);  //Set Serial2 to communicate with the robotic arm, the baud rate is 115200;
  myrobot.setSerialMonitoring(ON);  //开Open serial monitor
  while(myrobot.getStatus() != Idle && myrobot.getStatus() != Alarm); //Determine whether the robotic arm can receive instructions
  myrobot.sendMsg("$H",OFF); //Robotic arm home
  while(myrobot.getStatus() != Idle); //Wait for the robotic arm to home and become idle
  myrobot.setMoveSpeed(3000); //Set the maximum movement speed of the robotic arm to 3000
  myrobot.moveJoints(-90,10,-90,60,10,10);  //Control the 1-6 axis movement of the robotic arm to the position (-90°, 10°, -90°, 60°, 10°, 10°)
  myrobot.zero(); //The arm moves to the initial position
  myrobot.movePose(198,0,230.05,0,-60,0); //Control the rapid movement of the end of the mechanical arm to xyz (198,0,230.05), RPY angle (0,-60,0) position
  myrobot.movePose(0,-100,-100,0,60,0,INC,MOVL);  //Control the relative position of the end of the manipulator in the coordinate mode, the linear interpolation motion
  myrobot.movePose(250,0,100,0,0,0);
  myrobot.moveArc(200,0,100,60,ABS,CCW);  //Control the manipulator to move along a circular arc (inferior arc) with a radius of 60mm, with the current coordinate point and the end point xyz (200,0,100) as the tangent point;
  myrobot.gripper(ON);  //Servo gripper open
  myrobot.timedPause(2.5);  //Pause and wait for 2.5s
  myrobot.gripper(OFF);
  myrobot.zero();
  myrobot.timedPause(0.5);
  myrobot.runFile("test");  //Run the Gcode file "test.gcode" stored in the controller
  myrobot.homing(2);
}
void loop(){
  
}
