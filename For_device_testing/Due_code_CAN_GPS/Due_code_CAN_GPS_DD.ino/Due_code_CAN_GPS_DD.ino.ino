/**
 ******************************************************************************
 * @file    Due_code_CAN_GPS_DD.ino
 * @author  Thibault Gouin et Loriane Blanc
 * @version V1.0.0
 * @date    December 2020
 * @brief   Arduino application for the STMicrolectronics X-NUCLEO-GNSS1A1
 *          GNSS (Global Navigation Satellite System) module expansion board 
 *          based on TeseoLIV3F.
 *          This application allows the user to get the GPS frame with a 
 *          frequency of 20 times per second. And send it through a CAN bus.
 *          Two CAN frames are send: 
 *          One for the latitude and one for the longitude.
 ******************************************************************************
 */

//include librairies
#include "Debug_manager.h"
#include "CAN_applicatif.h"
#include "CAN.h"
#include "teseo_liv3f_class.h"
#include <Wire.h>

#define DEBUG_GPS 0 //if equal to 1, all the possible data received will be printed
#define DEBUG_LAT_LON 0 //if equal to 1, latitude and longigitude and altitude will be printed (respectively in DD and meter form) to the monitor
#define SEND_TO_CAN 1 //if equal to 1, latitude and longitude will be send directly to the CAN bus
#define MSG_SZ 256 //size of a message printed on printValidInfo() function
#define GPS_COORDS_SZ 3 //size of the array storing the GPS coordinates
#define waitForRequest 0
#define waitForAnswer 1

      
TeseoLIV3F *gps;
GNSSParser_Data_t data;
Coords_t Coords;
char msg[MSG_SZ];
float64_t tab_variable_GPS[GPS_COORDS_SZ];
uint8_t CAN_FRAME_LAT_LON[8];

#if defined(ARDUINO_SAM_DUE) //automatically detected when connected to the board
#define DEV_I2C Wire1
#include <avr/dtostrf.h>
#elif defined(ARDUINO_ARCH_STM32L0)
#define DEV_I2C Wire
#include <avr/dtostrf.h>
#elif defined(ARDUINO_ARCH_STM32)
#define DEV_I2C Wire
#endif

void setup()
{
   //Initialize serial port for user communication
   Serial.begin(115200);
   Serial.println("Setup GPS begin");
   //Initialize the i2c communication
   DEV_I2C.begin();
   //Create the device object passing to it the i2c interface
   gps = new TeseoLIV3F(&DEV_I2C, 7, 13);
   //Initialize the device
   gps->init();
   Serial.println("Setup GPS end");
   delay(1000);
   Serial.println("Setup CAN begin");
   setup_CAN();
   Serial.println("Setup CAN end");
   delay(1000);
   Serial.println("System ready!");
}

void loop()
{
   //recieve data form the i2c port
   //Note: this function shoud be called AT LEAST 20 times per second
   //      your code should not have any blocking function in order to prevent data loss
   gps->update();
   #if(DEBUG_GPS)
   printValidInfo(); //print all the received information on a readable format
   #elif(DEBUG_LAT_LON)
   printCoordsToMonitor(); //print the latitude and longitude data on the monitor (uncomment on the function the "get altitude" section for altitude data)
   #elif(SEND_TO_CAN)
   sendCoordsToCAN(); //send directly the latitude and the longitude to the CAN bus
   #endif

}

void printCoordsToMonitor()
{
  //declaration of local variables
  float64_t lat_dd; //latitude in decimal degrees
  float64_t lon_dd; //longitude in decimal degrees
  float64_t lat_raw; //latitude raw value from gps
  float64_t lon_raw; //longitude raw value from gps
  int lat_deg; //degree value of the latitude
  int lon_deg; //degree value of the longitude
  float64_t alt; //altitude in meter
  
  //get the coordinates and store them in Coords_t struct called Coords
  Coords = gps->getCoords();
  if (Coords.lat != 0.0 && Coords.lon != 0.0){ //Verify that the GPS is not giving wrong values 
    
    //get raw values
    lat_raw = gps->getCoords().lat;
    lon_raw = gps->getCoords().lon;
    alt = gps->getCoords().alt;

    /*//tests values
    lat_raw=4334.79899;
    lon_raw=128.31965;
    alt=120.81;
    */

    //conversion from raw data to decimal degrees
    lat_deg = (int)(lat_raw/100.0);
    lon_deg = (int)(lon_raw/100.0);
    lat_dd = lat_deg + ((lat_raw-(lat_deg*100))/60);
    lon_dd = lon_deg + ((lon_raw-(lon_deg*100))/60);
    
    tab_variable_GPS[0]=lat_dd;
    tab_variable_GPS[1]=lon_dd;
    tab_variable_GPS[2]=alt;
  
    Serial.println("GPS coordinates values : LAT, LONG, ALT ");
    for (int i=0;i<GPS_COORDS_SZ;i++)
      {
         Serial.println(tab_variable_GPS[i],7);
      }
  }
  else 
  {
  Serial.print("Last position wasn't valid.\r\n\n");
  }
  Serial.print("\r\n\n");
}


void sendCoordsToCAN()
{
    //declaration of local variables
  float64_t lat_dd; //latitude in decimal degrees
  float64_t lon_dd; //longitude in decimal degrees
  float64_t lat_raw; //latitude raw value from gps
  float64_t lon_raw; //longitude raw value from gps
  int lat_deg; //degree value of the latitude
  int lon_deg; //degree value of the longitude
  
  //get the coordinates and store them in Coords_t struct called Coords
  Coords = gps->getCoords();
  if (Coords.lat != 0.0 && Coords.lon != 0.0){ //Verify that the GPS is not giving wrong values 
    
    //get raw values
    lat_raw = gps->getCoords().lat;
    lon_raw = gps->getCoords().lon;

    /*//tests values for conversion
    lat_raw=4334.79899;
    lon_raw=128.31965;*/
    

    //conversion from raw data to decimal degrees
    lat_deg = (int)(lat_raw/100.0);
    lon_deg = (int)(lon_raw/100.0);
    lat_dd = lat_deg + ((lat_raw-(lat_deg*100))/60);
    lon_dd = lon_deg + ((lon_raw-(lon_deg*100))/60);
    int lat_dd_int= (int)(lat_dd*10000000);
    int lon_dd_int= (int)(lon_dd*10000000);
    
    CAN_FRAME_LAT_LON[0]=(uint8_t)(lat_dd_int >> 24);
    CAN_FRAME_LAT_LON[1]=(uint8_t)(lat_dd_int >> 16);
    CAN_FRAME_LAT_LON[2]=(uint8_t)(lat_dd_int >> 8);
    CAN_FRAME_LAT_LON[3]=(uint8_t)(lat_dd_int);
    CAN_FRAME_LAT_LON[4]=(uint8_t)(lon_dd_int >> 24);
    CAN_FRAME_LAT_LON[5]=(uint8_t)(lon_dd_int >> 16);
    CAN_FRAME_LAT_LON[6]=(uint8_t)(lon_dd_int >> 8);
    CAN_FRAME_LAT_LON[7]=(uint8_t)(lon_dd_int);

    Serial.println("\nGPS coordinates values : LAT, LONG");
    Serial.println(lat_dd_int);
    Serial.println(lon_dd_int);
    /*for (int i=0;i<8;i++)
      {
         Serial.print(CAN_FRAME_LAT_LON[i],HEX);
      }*/

    CAN.sendPacket(CAN_FRAME_LAT_LON,0x201,8);

  }
  else 
  {
    Serial.println("\nno data available");
  }
}


void printValidInfo()
{
   data = gps->getData();
   if (data.gpgga_data.valid == 1)
   {
      int lat = (int) (data.gpgga_data.xyz.lat/100.0);
      int lat_mod = (int) (data.gpgga_data.xyz.lat) - (lat * 100);
     
      int lon = (int) (data.gpgga_data.xyz.lon/100.0);
      int lon_mod = (int) (data.gpgga_data.xyz.lon) - (lon * 100);

      char alt[7];
      char acc[5];
      dtostrf (data.gpgga_data.xyz.alt, 3, 2, alt);
      dtostrf (data.gpgga_data.acc, 4, 1, acc);

      snprintf(msg, MSG_SZ, "UTC:\t\t\t[ %02ld:%02ld:%02ld ]\r\n",
               data.gpgga_data.utc.hh,
               data.gpgga_data.utc.mm,
               data.gpgga_data.utc.ss);
      Serial.print(msg);

      snprintf(msg, MSG_SZ, "Latitude:\t\t[ %.02d' %.02d'' %c ]\r\n",
               lat,
               lat_mod,
               data.gpgga_data.xyz.ns);
      Serial.print(msg);

      snprintf(msg, MSG_SZ, "Longitude:\t\t[ %.02d' %.02d'' %c ]\r\n",
               lon,
               lon_mod,
               data.gpgga_data.xyz.ew);
      Serial.print(msg);

      snprintf(msg, MSG_SZ, "Satellites locked:\t[ %ld ]\r\n",
               data.gpgga_data.sats);
      Serial.print(msg);

      snprintf(msg, MSG_SZ, "Position accuracy:\t[ %s ]\r\n",
               acc);
      Serial.print(msg);

      snprintf(msg, MSG_SZ, "Altitude:\t\t[ %s%c ]\r\n",
               alt,
               (data.gpgga_data.xyz.mis + 32U));
      Serial.print(msg);

      snprintf(msg, MSG_SZ, "Geoid infos:\t\t[ %ld%c ]\r\n",
               data.gpgga_data.geoid.height,
               data.gpgga_data.geoid.mis);
      Serial.print(msg);

      snprintf(msg, MSG_SZ, "Diff update:\t\t[ %ld ]\r\n",
               data.gpgga_data.update);
      Serial.print(msg);
   }
   else
   {
      Serial.print("Last position wasn't valid.\r\n\n");
   }
   Serial.print("\r\n\n");
}


