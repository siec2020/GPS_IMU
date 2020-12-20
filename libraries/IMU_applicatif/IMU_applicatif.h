#ifndef IMU_APPLICATIF_H
#define IMU_APPLICATIF_H

#include "Debug_and_config_manager.h"
#include "CAN.h"
#include "CAN_applicatif.h"
#include <Arduino.h>
#include <LSM303AGR_ACC_Sensor.h>
#include <LSM6DSLSensor.h>
#include <LSM303AGR_MAG_Sensor.h>
//#include <HTS221Sensor.h>
//#include <LPS22HBSensor.h>

#define VALG 9.807
#define VALPI 3.142
#define SENDALL 1 //if you want to use IMU_SendDataAll(void) function put 1  
				  //it has to be 0 if you want to use other send functions
extern "C" {
	void IMU_SETUP(void);
	void IMU_Getdata(void);
	void IMU_SendDataAccel(void);
	void IMU_SendDataRotation(void);
	void IMU_SendDataMagneto(void);
	void IMU_SendDataAll(void);
	void printrawdata(void);
	void printconvertdata(void);
}



#endif //ifndef
