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
