/**
 ******************************************************************************
 * @file    Due_code_CAN_GPS_IMU.ino
 * @author  Thibault Gouin et Loriane Blanc
 * @version V2.0.1
 * @date    December 2020
 * @brief   Arduino application for the STMicrolectronics X-NUCLEO-GNSS1A1
 *          GNSS (Global Navigation Satellite System) module expansion board 
 *          based on TeseoLIV3F.
 *          This application allows the user to get the GPS frame with a 
 *          frequency of 20 times per second maximum. And send it through 
 *          a CAN bus in one unique frame.
 *          
 *          Also included in this sketch:
 *          Arduino application for the STMicrolectronics X-NUCLEO-IKS01A2
 *          MEMS Inertial and Environmental sensor expansion board.
 *          This application allows the user to get accelerometry and rotation
 *          data got from the IMU shield, and send it through CAN bus.
 *          
 *          Please refer to the readme file for any explanation on the CAN
 *          frames and the data they transmit.
 *          
 ******************************************************************************
 */



//include librairies and application files
#include "GPS_applicatif.h"
#include "IMU_applicatif.h"
#include "CAN_applicatif.h"
#include "Debug_and_config_manager.h"

void setup()
{
   //Initialize serial port for user communication
   Serial_SETUP();
   #ifdef DEBUG_MODE
    Serial.println("Setup begin");
   #endif
   GPS_SETUP();
   IMU_SETUP();
   CAN_SETUP();
   #ifdef DEBUG_MODE
    Serial.println("Ready!");
   #endif
}

void loop()
{
   /**********GPS***********/
   #if(DEBUG_GPS)
   GPS_printAllValidInfo(); //print all the received information on a readable format
   #elif(DEBUG_LAT_LON)
   GPS_printCoords(); //print the latitude longitude, and altitude data on the monitor
   #else
   GPS_sendCoords(); //send directly the latitude and the longitude to the CAN bus
   #endif
   
   /**********IMU***********/
   IMU_SendDataAll();
   #ifdef DEBUG_IMU_RAW
     printrawdata(); //print data in its raw format, as received from sensors
   #endif
   #ifdef DEBUG_IMU_CONVERT
     printconvertdata(); //print data after conversion (accel data in m/s² and gyro data in rad/sec)
   #endif
}
