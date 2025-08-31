# Wireless-Communication
- MakerFocus NRF24L01+ 2.4GHz Wireless RF Transceiver Module Compatible with Arduino and Raspberry Pi. (*This radio is inexpensive .*)
  - Makerfire 4pcs NRF24L01+ Breakout Adapter with on-board 3.3V Regulator for NRF24L01+ Wireless Module.
- XBee-PRO 900HP (S3 & S3B) DigiMesh, 900MHz, 250mW, Wire Antenna, 200Kbps (North America XBP9B-DMWT-002). 
  - The Digi XBee-PRO 900HP DigiMesh Kit (US/Canada XKB9-DMT-UHP) comes with three radios.

## Testing Platform
- The MCU chip **Atmega328P** is well known and the price is affordable as well as most of the robotic hardware that is described here. The Arduino Uno board comes with a removable MCU.
- **PlatformIO** is a cross-platform, cross-architecture, multiple framework, professional tool for embedded systems engineers and for software developers who write applications for embedded products. 
- **Visual Studio Code** is a streamlined code editor and it runs on macOS, Linux, and Windows. The best thing about VSCode, it is free.
  
## MakerFocus NRF24L01+ 2.4GHz Wireless Transceiver 
- Preliminary Test [Study nRF24L01+](https://drive.google.com/file/d/16c0QiXB1juv79E4-AEpoiPuyevjmZlZL)
  - Updated the study with the Motor Movement Checklist after updating the Joystick Uno L298N repository.
- ~~RadioHead version 1.22.1 by Mike McCauley~~ There is a new version. [Arduino Reference Libraries](https://www.arduino.cc/reference/en/libraries/radiohead/) New version not tested...
- FCC ID [2A63C-NRF24L01](https://fcc.report/FCC-ID/2A63C-NRF24L01) report (Shenzhen Danaotiankong Technology Co., Ltd) for MakerFocus NRF24L01+2.4GHz Wire Less RF Transceiver Module
- Note: Finished wiring the motor controller & motors
  - MCU-1: Radio Server - Joystick Input
  - MCU-2: Radio Client & I2C Master - Intermediary between MCU-1 & MCU-3
  - MCU-3: I2C Slave - Controller & Motors

## Digi XBee-PRO 900HP DigiMesh kit
- 20250826 actively testing radios. The Digi XCTU software was used to configure set-1 with 3 radios and all passed... While using the **Digi XCTU software** in the **configuration working mode** (Cog Wheel) under **Serial Interfacing**, the **AP (API Enable)** mode setting was set to **Transparent Mode [0]**.
- Shifting away from XBee transparent mode...

## In Development
- 20250829 - Testing XBee radios...
- 20240813 - The final push for nRF24L01+. The Joystick Uno L298N repository has to be updated in order to fix some motor movement issues. Those header files were moved here. Finished testing the code and worked out the Motor Movement Checklist (MMC). See the updated Study... Moving on to the next radio... Having fun.
  - The *#define RUN_WITH_DEBUG_CODE* in the Common.h file was the only debug used for 1 second intervals for testing and for data acquisiton for the MMC. Shorter time intervals is still pending when time permits.

## Disclaimer and Terms
- Must read from this repository
