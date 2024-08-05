# Radios

## nRF24L01+

- namespace ***csjc***
- Note: The header files listed here are updated from the other older namespace header files.

### ***include folder***
- **Bitwise.h** 
- **BusI2C.h** (see source folder for implementation)
- **Button.h**
- **Common.h**
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

### How to use this repository
- Open PlatformIO with a new project...
- Copy and Paste contents from here into your project...
- Install RadioHead Lib from PlatformIO.
    - Understand how to use the platformio.ini file with multiple src folders - see file for details.