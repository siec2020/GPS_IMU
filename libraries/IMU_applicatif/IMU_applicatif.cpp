#include "IMU_applicatif.h"


LSM6DSLSensor *AccGyr;
LSM303AGR_ACC_Sensor *Acc2;
LSM303AGR_MAG_Sensor *Mag;

int32_t accelerometer[3];
float fl_accelerometer[3];
int32_t gyroscope[3];
float fl_gyroscope[3];

int32_t accelerometer2[3];
int32_t magnetometer[3];

void IMU_SETUP(void)
{	
	// Define built in led as an output for debug
	pinMode(LED_BUILTIN, OUTPUT);

	// Initialize I2C bus.
	DEV_I2C.begin();

	// Initlialize components.
	AccGyr = new LSM6DSLSensor(&DEV_I2C);
	AccGyr->Enable_X();
	AccGyr->Enable_G();
	Acc2 = new LSM303AGR_ACC_Sensor(&DEV_I2C);
	Acc2->Enable();
	Mag = new LSM303AGR_MAG_Sensor(&DEV_I2C);
	Mag->Enable();

	//PRINT SCALE SELECTED FOR LSM6DSLSensor
	float scaleLSM6;
	AccGyr->Get_X_FS(&scaleLSM6);
	Serial.print("scaleLSM6 : ");
	Serial.println(scaleLSM6);

	//PRINT SCALE SELECTED FOR LSM303AGR_ACC_Sensor
	float scaleLSM303;
	Acc2->GetSensitivity(&scaleLSM303);
	Serial.print("sensitivityLSM303 : ");
	Serial.println(scaleLSM303);
}

void IMU_Getdata(void)
{	
	// Led blinking.
	digitalWrite(LED_BUILTIN, HIGH);
	delay(100);
	digitalWrite(LED_BUILTIN, LOW);
	delay(100);
  
	// Read accelerometer and gyroscope.
	AccGyr->Get_X_Axes(accelerometer);
	AccGyr->Get_G_Axes(gyroscope);
  
	// Read accelerometer LSM303AGR.
	Acc2->GetAxes(accelerometer2);

	// Read magnetometer LSM303AGR.
	Mag->GetAxes(magnetometer);

 
  
}


void IMU_SendDataAccel(void){
	#if (SENDALL==0)
		IMU_Getdata();
	#endif

	CAN_FRAME_ACCELXY[0]=(uint8_t)(accelerometer[0]>> 24);
	CAN_FRAME_ACCELXY[1]=(uint8_t)(accelerometer[0]>> 16);
	CAN_FRAME_ACCELXY[2]=(uint8_t)(accelerometer[0]>> 8);
	CAN_FRAME_ACCELXY[3]=(uint8_t)(accelerometer[0]);
	CAN_FRAME_ACCELXY[4]=(uint8_t)(accelerometer[1]>> 24);
	CAN_FRAME_ACCELXY[5]=(uint8_t)(accelerometer[1]>> 16);
	CAN_FRAME_ACCELXY[6]=(uint8_t)(accelerometer[1]>> 8);
	CAN_FRAME_ACCELXY[7]=(uint8_t)(accelerometer[1]);

	CAN.sendPacket(CAN_FRAME_ACCELXY,CAN_ID_ACCELXY,8);
	#ifdef DEBUG_IMU_FRAME
		Serial.println("CAN_FRAME_ACCELXY");
	#endif

	CAN_FRAME_ACCELMAGNETOZ[0]=(uint8_t)(accelerometer[2]>> 24);
	CAN_FRAME_ACCELMAGNETOZ[1]=(uint8_t)(accelerometer[2]>> 16);
	CAN_FRAME_ACCELMAGNETOZ[2]=(uint8_t)(accelerometer[2]>> 8);
	CAN_FRAME_ACCELMAGNETOZ[3]=(uint8_t)(accelerometer[2]);
	
	#if !(SENDALL)
		CAN.sendPacket(CAN_FRAME_ACCELMAGNETOZ,CAN_ID_ACCELMAGNETOZ,8);
	#endif
}

void IMU_SendDataRotation(void){
	#if(SENDALL==0)
		IMU_Getdata();
	#endif

	CAN_FRAME_ROTATIONXY[0]=(uint8_t)(gyroscope[0]>> 24);
	CAN_FRAME_ROTATIONXY[1]=(uint8_t)(gyroscope[0]>> 16);
	CAN_FRAME_ROTATIONXY[2]=(uint8_t)(gyroscope[0]>> 8);
	CAN_FRAME_ROTATIONXY[3]=(uint8_t)(gyroscope[0]);
	CAN_FRAME_ROTATIONXY[4]=(uint8_t)(gyroscope[1]>> 24);
	CAN_FRAME_ROTATIONXY[5]=(uint8_t)(gyroscope[1]>> 16);
	CAN_FRAME_ROTATIONXY[6]=(uint8_t)(gyroscope[1]>> 8);
	CAN_FRAME_ROTATIONXY[7]=(uint8_t)(gyroscope[1]);

	CAN.sendPacket(CAN_FRAME_ROTATIONXY,CAN_ID_ROTATIONXY,8);
	#ifdef DEBUG_IMU_FRAME
		Serial.println("CAN_FRAME_ROTATIONXY");
	#endif

	CAN_FRAME_ROTATIONZ[0]=(uint8_t)(gyroscope[2]>> 24);
	CAN_FRAME_ROTATIONZ[1]=(uint8_t)(gyroscope[2]>> 16);
	CAN_FRAME_ROTATIONZ[2]=(uint8_t)(gyroscope[2]>> 8);
	CAN_FRAME_ROTATIONZ[3]=(uint8_t)(gyroscope[2]);
	

	CAN.sendPacket(CAN_FRAME_ROTATIONZ,CAN_ID_ROTATIONZ,8);
	#ifdef DEBUG_IMU_FRAME
		Serial.println("CAN_FRAME_ROTATIONZ \n");
	#endif
}

void IMU_SendDataMagneto(void){
	#if(SENDALL==0)
		IMU_Getdata();
	#endif

	CAN_FRAME_MAGNETOXY[0]=(uint8_t)(magnetometer[0]>> 24);
	CAN_FRAME_MAGNETOXY[1]=(uint8_t)(magnetometer[0]>> 16);
	CAN_FRAME_MAGNETOXY[2]=(uint8_t)(magnetometer[0]>> 8);
	CAN_FRAME_MAGNETOXY[3]=(uint8_t)(magnetometer[0]);
	CAN_FRAME_MAGNETOXY[4]=(uint8_t)(magnetometer[1]>> 24);
	CAN_FRAME_MAGNETOXY[5]=(uint8_t)(magnetometer[1]>> 16);
	CAN_FRAME_MAGNETOXY[6]=(uint8_t)(magnetometer[1]>> 8);
	CAN_FRAME_MAGNETOXY[7]=(uint8_t)(magnetometer[1]);

	CAN.sendPacket(CAN_FRAME_MAGNETOXY,CAN_ID_MAGNETOXY,8);
	#ifdef DEBUG_IMU_FRAME
		Serial.println("CAN_FRAME_MAGNETOXY");
	#endif

	CAN_FRAME_ACCELMAGNETOZ[4]=(uint8_t)(magnetometer[2]>> 24);
	CAN_FRAME_ACCELMAGNETOZ[5]=(uint8_t)(magnetometer[2]>> 16);
	CAN_FRAME_ACCELMAGNETOZ[6]=(uint8_t)(magnetometer[2]>> 8);
	CAN_FRAME_ACCELMAGNETOZ[7]=(uint8_t)(magnetometer[2]);
	
	#if !(SENDALL)
		CAN.sendPacket(CAN_FRAME_ACCELMAGNETOZ,CAN_ID_ACCELMAGNETOZ,8);
	#endif

}

void IMU_SendDataAll(void){

	IMU_Getdata();
	IMU_SendDataAccel();
	IMU_SendDataMagneto();
	CAN.sendPacket(CAN_FRAME_ACCELMAGNETOZ,CAN_ID_ACCELMAGNETOZ,8);
	#ifdef DEBUG_IMU_FRAME
		Serial.println("CAN_FRAME_ACCELMAGNETOZ");
	#endif
	IMU_SendDataRotation();

}






void printrawdata(void)
{
	// Output data.
    Serial.print("Acc[mg]: [");
    Serial.print(accelerometer[0]);
    Serial.print(" "); 
    Serial.print(accelerometer[1]);
    Serial.print(" ");
    Serial.print(accelerometer[2]);
    Serial.print("] ||||| Gyr[mdps]: [");
    Serial.print(gyroscope[0]);
    Serial.print(" ");
    Serial.print(gyroscope[1]);
    Serial.print(" ");
    Serial.print(gyroscope[2]);
    Serial.print("] ||||| Acc2[mg]: [");
    Serial.print(accelerometer2[0]);
    Serial.print(" ");
    Serial.print(accelerometer2[1]);
    Serial.print(" ");
    Serial.print(accelerometer2[2]);
    Serial.print("] ||||| Mag[mGauss]: [");
    Serial.print(magnetometer[0]);
    Serial.print(" ");
    Serial.print(magnetometer[1]);
    Serial.print(" ");
    Serial.print(magnetometer[2]);
    Serial.print("] \n\r");
    Serial.println(" ");
}

void printconvertdata(void)
{
	//ACCEL
    //CONVERSION : INT giving acceleration in mg (millig) 
	//							   to FLOAT giving acceleration in m/s²
    
    Serial.print("IMU_data : Acceleration (in m/s²) = [");
    for (int i=0;i<3;i++)
    {
		fl_accelerometer[i]=(float(accelerometer[i])/1000.0)*VALG;
		Serial.print(fl_accelerometer[i],3);
		Serial.print(" ");
    }
    Serial.println("]");
    
    //GYRO
    //CONVERTION : from INT giving orientation in mdps (milli degres per seconde) 
	//							   to FLOAT giving orientation in rad/sec
    
    Serial.print("IMU_data : Rotation (in rad/s) = [");
    for (int i=0;i<3;i++)
    {
		fl_gyroscope[i]=(float(gyroscope[i])/1000.0)*(VALPI/180);
		Serial.print(fl_gyroscope[i],3);
		Serial.print(" ");
    }
    Serial.println("] \n\r");
}