#ifndef GPS_APPLICATIF_H
#define GPS_APPLICATIF_H

#include "Debug_and_config_manager.h"
#include "CAN.h"
#include "CAN_applicatif.h"
#include "teseo_liv3f_class.h"
#include <avr/dtostrf.h>

extern "C" {
	void GPS_SETUP(void);
	void GPS_printAllValidInfo(void);
	void GPS_printCoords(void);
	void GPS_sendCoords(void);
}



#endif //ifndef
