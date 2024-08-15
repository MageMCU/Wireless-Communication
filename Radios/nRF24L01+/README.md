# Radios - nRF24L01+
- namespace ***csjc***
- Note: The header files listed here are updated from the other older namespace header files.

### ***include folder***
- **Bitwise.h** 
- **BusI2C.h** (see source folder for implementation)
- **Button.h**
- **Common.h**
- **Headers.h**
- **Joystick.h**   
- **L298N.h** 
- **LinearMap.h**    
- **MiscMath.h** 
- **Switch.h**
- **Timer.h**   
- **TypeConv.h**  
- **Vector3.h**  
- Note: Not all header files were used...,  but will work on later,

### ***lib folder***
-  *Used PlatformIO to install RadioHead Lib.* - Please read **Study nRF24L01+** for more details...

### ***src folder***
- client folder
    - main.cpp
- DEP folder
    - BusI2C.cpp
- I2C folder
    - main.cpp
- server folder
    - main.cpp

### ***root folder***
- platformio.ini
    - Read contents of this file because src folder uses multiple files which cannot be used at the same time when compiling...

### Notes
- The final testing was to decrease the timing down to 50ms for the MCU-1 (server with the joystick), the MCU-2 (client) and the MCU-3 (I2C with the motor diver) which went quite well. Next the debug defintions were commented out except for the SERIAL DEBUG. Strangely enough, it caused the client not to work. The code here at Github does not have this test but anyone can try to duplicate it as a project. Good luck.
- The project is considered complete and is now closed until further notice.

### How to use this repository
- Open PlatformIO with a new project...
- Copy and Paste contents from here into your project...
- Install RadioHead Lib from PlatformIO.
    - Understand how to use the platformio.ini file with multiple src folders - see file for details.