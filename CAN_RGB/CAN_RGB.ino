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

  // need to make sure not Interrupting each other
  attachInterrupt(digitalPinToInterrupt(2), HS_CAN_MSG,FALLING);
  //attachInterrupt(digitalPinToInterrupt(3), MS_CAN_MSG,FALLING);
}

void loop() {
  for (int i = 0; i < NUM_LEDS; i++){
    
  }
  FastLED.show();
}

void HS_CAN_MSG(){
  if (HS_CAN.readMessage(&canMsg) == MCP2515::ERROR_OK){ // To receive data (Poll Read)
      printMsg(&canMsg);
      switch (canMsg.can_id){
        case 1689:
          decode_CAN_CTRL(&canMsg);
          break;
        default:
          break;
      }   
  }
}

void MS_CAN_MSG(){
  if (MS_CAN.readMessage(&canMsg) == MCP2515::ERROR_OK){ // To receive data (Poll Read)
      printMsg(&canMsg);   
    }  
}

void decode_CAN_CTRL(struct can_frame *frame){
  switch (frame->data[0]){
    case 0x02:  // Static
      break;
    case 0x03:  // Breath
      break; 
    case 0x04:  // Rainbow
      break; 
    case 0x05:  // Wave
      break; 
    default:
      break;
  }
}

void printMsg(struct can_frame *frame){
  Serial.print("<");
  Serial.print(frame->can_id);
  Serial.print(";");
  for(int i=0;i<frame->can_dlc-1;i++) {  
    Serial.print(frame->data[i]);
    Serial.print(",");
  }                 
  Serial.print(frame->data[frame->can_dlc-1]);             
  Serial.println(">");
}
