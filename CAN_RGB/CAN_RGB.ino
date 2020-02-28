#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication

struct can_frame canMsg; 
MCP2515 HS_CAN(10);                 // SPI CS Pin 10 
MCP2515 MS_CAN(9);                  // SPI CS Pin 9

#include "FastLED.h"
#define NUM_LEDS 50
#define DATA_PIN A0
CRGB leds[NUM_LEDS];

void setup() {
  
  SPI.begin();                       //Begins SPI communication
  
  Serial.begin(38400);                //Begins Serial Communication at 38400 baudrate 
  Serial.println("CAN Read - Testing receival of CAN Bus message");  
  
  HS_CAN.reset();                          
  HS_CAN.setBitrate(CAN_500KBPS,MCP_8MHZ); //Sets CAN at speed 500KBPS and Clock 8MHz 
  HS_CAN.setNormalMode();                  //Sets CAN at normal mode

  MS_CAN.reset();                          
  MS_CAN.setBitrate(CAN_125KBPS,MCP_8MHZ); //Sets CAN at speed 125KBPS and Clock 8MHz 
  MS_CAN.setListenOnlyMode();              //Sets CAN at normal mode
  Serial.println(" Running ");


  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  if (HS_CAN.readMessage(&canMsg) == MCP2515::ERROR_OK){ // To receive data (Poll Read)
    printMsg(canMsg);   
    if (canMsg.can_id == 1689){
      switch (canMsg.data[0]){
        case 0x02:
          break;
        case 0x03:
          break; 
        case 0x04:
          break; 
        case 0x05:
          break; 
      }
    }
  }
  
  if (MS_CAN.readMessage(&canMsg) == MCP2515::ERROR_OK){ // To receive data (Poll Read)    
    
  }
}


for (int i = 0; i < NUM_LEDS; i++){
          leds[i] = CRGB(canMsg.data[1],canMsg.data[2],canMsg.data[3]);
        }
        FastLED.show();

void printMsg(struct can_frame *frame){
  Serial.print("<");
  Serial.print(frame.can_id);
  Serial.print(";");
  for(int i=0;i<frame.can_dlc-1;i++) {  
    Serial.print(frame.data[i]);
    Serial.print(",");
  }                 
  Serial.print(frame.data[frame.can_dlc-1]);             
  Serial.println(">");
}
