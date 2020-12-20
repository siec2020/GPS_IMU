#include "Debug_and_config_manager.h"

void Serial_SETUP(void){
	#ifdef DEBUG_MODE
		Serial.begin(115200);
	#endif
}