# GPS-Tracking-System
This project is divided into a variety of functions on which each member has worked separately and then the entirety of it has been reviewed and revised collectively.
## Functions
1- GPIO\
  This function sets up the settings of each pin required for the project (LEDs, Switches, and hardware connections).\
2- GPS\
  This function is responsible for intaking the data from the GPS module and processing it, which helps figure out current position and displacement between us and target location.\
3- LED\
  This function controls which color the LED should be lit based on the displacement between the current location and that of the target.\
4- SevenSegment\
  This function shows the total distance walked since starting the program on 3 Seven Segment displays to a maximum of 999 meters.\
5- UART\
  This function controls the baudrate to match it between both the GPS module and the TIVA C M4 microprocessor.\
6- Hardware Components\
Tiva-c Ublox NEO-6m GPS tested Module.\
