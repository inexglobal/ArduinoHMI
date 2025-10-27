/*
 * SD_readGcode
 * ======================== Function Description =======================
 * Demonstrate how to use the Arduino development board to read the "test.gcode" file in the TF card,
 * And send the read G code command to the robot arm through the serial port for execution.
 *
 * ====================== Robotic Arm Settings ======================
 * Use WlkataStudio-V1.019.20 to update the latest firmware for the robotic arm and controller,
 * Multi-function controller "Port" is set to "UART".
 *
 * ======================= Circuit Connection ======================
 * Mage Sensor Shield UART2 --- Multi-function controller "SERIAL INTERFACER" interface
 *
 * ======================TF card file =====================
 * The TF card stores the "test.gcode" file by default, confirm that the file is stored in the root directory
 *
 * This sample program is for use with the Mirobot robot arm, and cannot be executed normally without connecting the robot arm
 * 
 */
#include <SPI.h>
#include <SdFat.h>
#include <Mirobot.h>  
#include <Wlkata_Mega_Sensor_Shield.h>

#define SD_CS_PIN SS

UART_Mirobot myrobot; //Create the robotic arm object
SdFat SD;
File myFile;

void setup() {
  Serial.begin(9600);
  shieldInit();
  while (!Serial) {}  //Wait for the serial port to open
  Serial.print("Initializing SD card...");
  
  if (!SD.begin(SD_CS_PIN)) {  //SD类进行初始化
    Serial.println("initialization failed!");
    return;
  }
  
  Serial.println("initialization done.");
  myFile = SD.open("test.gcode");//open a file. Note that only one file can be open at a time
  
  if (myFile) {  //If the file is open, read the contents
    Serial.println("test.gcode:");
    while (myFile.available()) {  //Read data from the file and print to the serial port until the reading is complete
      Serial.write(myFile.read());
    }
    myFile.close(); // close file open
  } 
  else {  //If the file is not open, output file open error to the serial port
    Serial.println("error opening test.txt");
  }

  myrobot.serialInit(2);  //Set Serial2 to communicate with the robotic arm, the baud rate is 115200;
  myrobot.setSerialMonitoring(ON);  //Open serial monitor
  
  while(!shieldKeyValue(SW1) == HIGH);  //Press the SW1 key, the mechanical arm starts to move
  buzzerAlarm(3,200);
  myrobot.homing(); //Robotic arm returns to zero quickly
  myrobot.setCmdTimeout(1000000);
}

void loop() {
  SD_runFile("test.gcode"); //Send the G code command in the "test.gcode" file through the serial port of the robot arm communication
  buzzerAlarm(3,200);  //The buzzer beeps three times with an interval of 200ms
  delay(2000);
}


void SD_runFile(String filename){
  while(myrobot.getStatus() != Idle); //Wait for the robotic arm to home and become idle
  myFile = SD.open(filename);

  if(myFile){  //If the file is open, read the contents
    Serial.println("File Gcode:");
    
    while(myFile.available()){
      String _str="\0";
      char _data='\0';
      
      while(1){ //read single instruction
        if(_data=='\n') break;
        else if(myFile.available()==0){
          if(_str=="\0") break;
          _str+="\r\n";
          break;
        }
        _data = myFile.read();
        _str += _data;
      }
      myrobot.sendMsg(_str);
    }
    myFile.close(); // close file open
    Serial.println("File run completed");
    while(myrobot.getStatus() != Idle); //Wait for the robotic arm to home and become idle
  }
  else {  //If the file is not open, output file open error to the serial port
    Serial.println("error opening file");
  }
}
