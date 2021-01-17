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

Plug the Arduino Due board to your computer with a micro USB cable with the programming port.

Go to Tools/Board and select "Arduino Due (programming port)".

Select the active COM port in Tools/Port (next to the one active it should be written "programming port").

Then, press ```Ctrl+U``` or click on the "Upload" button (right arrow next to the check logo).
