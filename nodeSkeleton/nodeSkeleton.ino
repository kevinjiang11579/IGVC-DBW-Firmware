/***This is the skeleton for the individual nodes ***/
//Import libraries
//Declare macros, pins and variables

#include "Canbus.h"
#include "defaults.h"
#include "global.h"
#include "mcp2515.h"
#include "mcp2515_defs.h"

tCAN rxMessage;
tCAN txMessage;
void sendToCan(tCAN *message);
void readfromCan(tCAN message);

void setup() {
//Setup hardware interrupt from Digital Pin, connected to System Aggregator, need an interrupt handler
  //Also could send "I'm busy" signal through CAN when calling functions
  Serial.begin(9600); // For debug use
  delay(1000);
  if(Canbus.init(CANSPEED_500))  //Initialise MCP2515 CAN controller at the specified speed
    Serial.println("CAN Init ok");
  else
    Serial.println("Can't init CAN");
  delay(1000);
}

void loop() {
//Read from CAN
//Read from sensors
  //readSensor(), poll
//Send to CAN
tCAN message;
readfromCan(message);
}

void sendToCan(tCAN message) {
  mcp2515_bit_modify(CANCTRL, (1<<REQOP2)|(1<<REQOP1)|(1<<REQOP0), 0);
  mcp2515_send_message(&message);
}

void readfromCan(tCAN message){
  if (mcp2515_check_message()){
    if(mcp2515_get_message(&message)){
     //if(message.id == 0x620 && message.data[2] == 0xFF){  //uncomment when you want to filter
       Serial.print("ID: ");
       Serial.print(message.id,HEX);
       Serial.print(", ");
       Serial.print("Data: ");
       Serial.print(message.header.length,DEC);
       for(int i=0;i<message.header.length;i++) 
        { 
          Serial.print(message.data[i],HEX);
          Serial.print(" ");
        }
       Serial.println("");
      //}
    }
  }
}
