# GPS_IMU
Arduino libraries and application files for the GPS and IMU data acquisition and sending it through CAN bus. 

## How to use the Arduino Due board
### Install the Arduino IDE
* On Windows: [tutorial link](https://www.arduino.cc/en/guide/windows#)
* On Linux: [tutorial link](https://www.arduino.cc/en/guide/linux#)

### Installing the Arduino Sam Boards core

* Go to Tools / Board / Boards Manager and type "due".
* Install the "Arduino SAM Boards (32-bits ARM Cortex-M3)" (the version used for the project is the 1.6.12).

*If your computer does not recognize the COM port, please follow the instructions of this [Arduino tutorial](https://www.arduino.cc/en/Guide/ArduinoDue).*

### Programming the Arduino Due Board
Once your program is ready to be upload to the Arduino Due, setup the connection :
* Plug the Arduino Due board to your computer with a micro USB cable with the programming port.
* Go to Tools/Board and select "Arduino Due (programming port)".
* Select the active COM port in Tools/Port (next to the one active it should be written "programming port").

Then, press ```Ctrl+U``` or click on the "Upload" button (right arrow next to the check logo).

## Launch the program on the hardware
All you need is to copy-paste all the directories from the "libraries" directory to your Arduino Library folder. On Windows, this folder can be found on ```Documents/Arduino/libraries```, on Linux it should be at ```~/Arduino/libraries```.

Then, you just have to open the ```Due_code_CAN_GPS_IMU.ino``` file and upload it to the Due board.

NB: You need, of course, to plug all the needed shield on the Due board.

Here is the list:
* The CAN shield ([CAN-BUS shield V2.0 by Seed Studio](https://wiki.seeedstudio.com/CAN-BUS_Shield_V2.0/))
* The GPS shield ([X-NUCLEO-GNSS1A1](https://www.st.com/en/ecosystems/x-nucleo-gnss1a1.html))
* The IMU shield ([X-NUCLEO-IKS01A2](https://www.st.com/en/ecosystems/x-nucleo-iks01a2.html))

## IDs of the CAN Messages

|Name                                                      |ID    |
|----------------------------------------------------------|:----:|
|                                                          |11bits|
|GPS (latitude and longitude)                              |0x201 |
|IMU_ACCELXY (x and y acceleration)                        |0x202 |
|IMU_MAGNETOXY (x and y magnetic fields)                   |0x203 |
|IMU_ROTATIONXY (x and y rotation)                         |0x204 |
|IMU_ACCELMAGNETOZ (z acceleration and z magnetic field)   |0x205 |
|IMU_ROTATIONZ (z rotation)                                |0x206 |

## Description of the CAN Messages
### GPS (latitude and longitude)

* **From:** Arduino Due
* **To:** Raspberry Pi
* **Lenght (Bytes):** 8
* **Data field:**

|Bytes 0-3 |Bytes 4-7|
|:------------|:------------|
|latitude | longitude |

* **latitude**
	* Hexadecimal value of the latitude. The value is an integer, if you want the decimal degree value you need to divide it by 10^7.
* **longitude**	
	* Hexadecimal value of the longitude. As for the latitude, the longitude value is an integer, if you want the decimal degree value you need to divide it by 10^7.
  
### IMU_ACCELXY (x and y acceleration)
* **From:** Arduino Due
* **To:** Raspberry Pi
* **Lenght (Bytes):** 8
* **Data field:**

|Bytes 0-3 |Bytes 4-7|
|:------------|:------------|
| x_acceleration | y_acceleration |

* **x_acceleration**
	* Hexadecimal value of acceleration on the x axis. The current unit is mg (millig). In order to convert it to m/s² you will have to divide it by 1000 and then multiply it with g = 9.807.
* **y_acceleration**	
	* Hexadecimal value of acceleration on the y axis. The current unit is mg (millig). In order to convert it to m/s² you will have to divide it by 1000 and then multiply it with g = 9.807.
	
### IMU_MAGNETOXY (x and y magnetic fields)
* **From:** Arduino Due
* **To:** Raspberry Pi
* **Lenght (Bytes):** 8
* **Data field:**

|Bytes 0-3 |Bytes 4-7|
|:------------|:------------|
|x_magneto | y_magneto |

* **x_magneto**
	* Hexadecimal value of the magnetic field on the x axis. The current unit is mGauss (milliGauss). In order to convert it to Tesla you will have to divide it by 10^7.
* **y_magneto**	
	* Hexadecimal value of the magnetic field on the y axis. The current unit is mGauss (milliGauss). In order to convert it to Tesla you will have to divide it by 10^7. 
	
### IMU_ROTATIONXY (x and y rotation)
* **From:** Arduino Due
* **To:** Raspberry Pi
* **Lenght (Bytes):** 8
* **Data field:**

|Bytes 0-3 |Bytes 4-7|
|:------------|:------------|
|x_rotation | y_rotation |

* **x_rotation**
	* Hexadecimal value of the rotation on the x axis. The current unit is mdps (milli degres per seconde). In order to convert it to rad/s you will have to divide it by 1000 and then multiply it with (pi/180).
* **x_rotation**	
	* Hexadecimal value of the rotation on the y axis. The current unit is mdps (milli degres per seconde). In order to convert it to rad/s you will have to divide it by 1000 and then multiply it with (pi/180).
	
### IMU_ACCELMAGNETOZ (z acceleration and z magnetic field)
* **From:** Arduino Due
* **To:** Raspberry Pi
* **Lenght (Bytes):** 8
* **Data field:**

|Bytes 0-3 |Bytes 4-7|
|:------------|:------------|
|z_acceleration | z_magneto |

* **z_acceleration**
	* Hexadecimal value of acceleration on the z axis. The current unit is mg (millig). In order to convert it to m/s² you will have to divide it by 1000 and then multiply it with g = 9.807.
* **z_magneto**	
	* Hexadecimal value of the magnetic field on the z axis. The current unit is mGauss (milliGauss). In order to convert it to Tesla you will have to divide it by 10^7.
	
### IMU_ROTATIONZ (z rotation)
* **From:** Arduino Due
* **To:** Raspberry Pi
* **Lenght (Bytes):** 4
* **Data field:**

|Bytes 0-3 |
|:------------|
|z_rotation |

* **z_rotation**
	* Hexadecimal value of the rotation on the z axis. The current unit is mdps (milli degres per seconde). In order to convert it to rad/s you will have to divide it by 1000 and then multiply it with (pi/180).
