#include "CAN_applicatif.h"

uint8_t Trame_CAN_DEBUG[NBR_OCTET_TRAME_CAN]={0};
uint8_t CAN_FRAME_LAT_LON[NBR_OCTET_TRAME_CAN]={0}; //id 201 latitude 0..3 bytes longitude 4..7 bytes

uint8_t CAN_FRAME_ACCELXY[NBR_OCTET_TRAME_CAN]={0}; //id 202 accel x 0..3 bytes accel y 4..7 bytes
uint8_t CAN_FRAME_ACCELMAGNETOZ[NBR_OCTET_TRAME_CAN]={0}; //id 205 accel z 0..3 bytes magneto z 4..7 bytes
uint8_t CAN_FRAME_MAGNETOXY[NBR_OCTET_TRAME_CAN]={0}; //id 203 magneto x 0..3 bytes magneto y 4..7 bytes
uint8_t CAN_FRAME_ROTATIONXY[NBR_OCTET_TRAME_CAN]={0}; //id 204 rotation x 0..3 bytes rotation y 4..7 bytes
uint8_t CAN_FRAME_ROTATIONZ[NBR_OCTET_TRAME_CAN]={0}; //id 206 rotation z 0..3 bytes 

void onReceive(int){
	int p_Dlc;
	long p_Id;
	bool p_Extended;
	uint8_t p_RXframe[NBR_OCTET_TRAME_CAN];
	CAN.readFrame(&p_Id,&p_Extended,&p_Dlc,p_RXframe);

	#ifdef DEBUG_CAN
		for (int i=0;i<p_Dlc;i++){
			Serial.print(p_RXframe[i],HEX);
			Serial.print(" ");
		}
		Serial.println();
		Serial.println(p_Id,HEX);
		Serial.println(p_Dlc);
		Serial.print("Extended :");
		Serial.println(int(p_Extended));
		Serial.println();
	#endif
}
void CAN_SETUP(){
	if (!CAN.begin(CANSPEED))
	{
		#ifdef DEBUG_CAN
			Serial.println("Starting CAN failed!");
		#endif
	}
	CAN.onReceive(onReceive);
	//CAN.filterExtended();
}
