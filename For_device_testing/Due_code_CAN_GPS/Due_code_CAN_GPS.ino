#include "Debug_manager.h"
#include "CAN_applicatif.h"
#include "CAN.h"


#include "teseo_liv3f_class.h"
#include <Wire.h>

//#define DEBUG_GPS
#define NBRE_VARIABLE 3
double tab_variable_GPS[NBRE_VARIABLE];

      
TeseoLIV3F *gps;
int incomingByte;
GNSSParser_Data_t data;
char command[32] = {0};
char msg[256];
int cmdType = 0;
uint32_t t, s;
int tracked;
GPGGA_Info_t stored_positions[64];
int status = 0;
uint32_t stime = 0;
int waitType = 0;

#define MSG_SZ 256
#define waitForRequest 0
#define waitForAnswer 1

#if defined(ARDUINO_SAM_DUE)
#define DEV_I2C Wire1
#include <avr/dtostrf.h>
#elif defined(ARDUINO_ARCH_STM32L0)
#define DEV_I2C Wire
#include <avr/dtostrf.h>
#elif defined(ARDUINO_ARCH_STM32)
#define DEV_I2C Wire
#endif



void setup() {
  //DEBUG
  #if defined DEBUG_MODE
    Serial_SETUP();
  #endif
  Serial.println("Setup CAN begin");
  
  //CAN
  setup_CAN();

  Serial.println("Setup end");
  delay(2000);
  //GPS
  Serial.println("Setup GPS begin");
  //Initialize the i2c communication
  DEV_I2C.begin();
  
   //Create the device object passing to it the i2c interface
   gps = new TeseoLIV3F(&DEV_I2C, 7, 13);
   //Initialize the device
   gps->init();
  
  Serial.println("Setup end");
}

void loop() {
  // put your main code here, to run repeatedly:
  gps->update();
  printValidInfo();
  delay(50);
  CAN.sendPacket(Trame_CAN_DEBUG,0x201,3);
  //Serial.println("aftersend");
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


      
      tab_variable_GPS[0]=uint8_t(lat);
      tab_variable_GPS[1]=uint8_t(lon);
      tab_variable_GPS[2]=uint8_t(data.gpgga_data.xyz.alt);

      Trame_CAN_DEBUG[0]=tab_variable_GPS[0];
      Trame_CAN_DEBUG[1]=tab_variable_GPS[1];
      Trame_CAN_DEBUG[2]=tab_variable_GPS[2];
      
      Serial.println("Valeur tableau données GPS : LAT, LONG, ALT ");
      for (int i=0;i<NBRE_VARIABLE;i++)
      {
         Serial.println(tab_variable_GPS[i]);
      }
      
      #ifdef DEBUG_GPS
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
      #endif //debug_gps
   }
   else
   {
      Serial.print("Last position wasn't valid.\r\n\n");
   }
   Serial.print("\r\n\n");
}
