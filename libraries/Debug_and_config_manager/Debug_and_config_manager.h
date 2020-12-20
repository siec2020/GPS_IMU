#ifndef DEBUG_AND_CONFIG_MANAGER_H
#define DEBUG_AND_CONFIG_MANAGER_H

#include <Arduino.h>
#include <Wire.h>

#define DEBUG_MODE

#define DEBUG_CAN

#define DEBUG_GPS 0 //if equal to 1, all the possible data received will be printed
#define DEBUG_LAT_LON 0 //if equal to 1, latitude and longigitude and altitude will be printed (respectively in DD and meter form) to the monitor

//#define DEBUG_IMU_RAW
#define DEBUG_IMU_CONVERT
//#define DEBUG_IMU_FRAME

#define DEV_I2C Wire1

extern "C" {
	void Serial_SETUP(void);
}


#endif //ifndef
