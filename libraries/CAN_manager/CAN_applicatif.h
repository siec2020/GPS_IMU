#ifndef CAN_APPLICATIF_H
#define CAN_APPLICATIF_H
#include "CAN.h"
#include "Debug_and_config_manager.h"
#include "Arduino.h"


#define NBR_OCTET_TRAME_CAN 8
#define CANSPEED 400E3

#define CAN_ID_LATLONG 0x201
#define CAN_ID_ACCELXY 0x202
#define CAN_ID_MAGNETOXY 0x203
#define CAN_ID_ROTATIONXY 0x204
#define CAN_ID_ACCELMAGNETOZ 0x205
#define CAN_ID_ROTATIONZ 0x206


extern uint8_t Trame_CAN_DEBUG[NBR_OCTET_TRAME_CAN];
extern uint8_t CAN_FRAME_LAT_LON[NBR_OCTET_TRAME_CAN]; //id 201

extern uint8_t CAN_FRAME_ACCELXY[NBR_OCTET_TRAME_CAN]; //id 202
extern uint8_t CAN_FRAME_MAGNETOXY[NBR_OCTET_TRAME_CAN]; //id 203 0..7 octet
extern uint8_t CAN_FRAME_ROTATIONXY[NBR_OCTET_TRAME_CAN]; //id 204 0..7 octet
extern uint8_t CAN_FRAME_ACCELMAGNETOZ[NBR_OCTET_TRAME_CAN]; //id 205 accel z 0..3 octet magneto z 4..7 octet
extern uint8_t CAN_FRAME_ROTATIONZ[NBR_OCTET_TRAME_CAN]; //id 206 0..3 octet

extern "C" {
void onReceive(int);
void CAN_SETUP();
} //externC
#endif
