
#include "Debug_manager.h"
#include "CAN_applicatif.h"
#include "CAN.h"

void setup() {
  //DEBUG
  #if defined DEBUG_MODE
    Serial_SETUP();
  #endif
  
  //CAN
  setup_CAN();
  
  Trame_CAN_DEBUG[0]=12;
  Trame_CAN_DEBUG[1]=13;
  Trame_CAN_DEBUG[2]=14;
  Trame_CAN_DEBUG[3]=15;
  Trame_CAN_DEBUG[4]=16;
  Trame_CAN_DEBUG[5]=17;
}

void loop() {
  // put your main code here, to run repeatedly:
  CAN.sendPacket(Trame_CAN_DEBUG,0x201,6);
  Serial.println("aftersend");
  delay(50);
}
