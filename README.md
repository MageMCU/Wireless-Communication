# Wireless-Communication
- After six months of review, I have decided to start with these device(s). It is my hope to complete this project by the end of 2024. There were other radios under review but decided against using them because the IDE and code was beyond a beginners capability... Maybe later...
- I reviewed several radios but I have been having bad luck with the amplified NRF24L01, and the ESP32. Many of these radios have been returned back for one reason or another.
- Thanks to both Digikey and Digi for their support and best of all, recieved a replacement for the XBee 900 radio. 

## Testing Platform
- The MCU chip **Atmega328P** is well known and the price is affordable as well as most of the robotic hardware that is described here. The Arduino Uno board comes with a removable MCU.
- **PlatformIO** is a cross-platform, cross-architecture, multiple framework, professional tool for embedded systems engineers and for software developers who write applications for embedded products. 
- **Visual Studio Code** is a streamlined code editor and it runs on macOS, Linux, and Windows. The best thing about VSCode, it is free.
  
## MakerFocus NRF24L01+ 2.4GHz Wireless Transceiver 
- Preliminary Test [Study nRF24L01+](https://drive.google.com/file/d/16c0QiXB1juv79E4-AEpoiPuyevjmZlZL)
  - Updated the study with the Motor Movement Checklist after updating the Joystick Uno L298N repository.
- RadioHead version 1.22.1 by Mike McCauley [Arduino Reference Libraries](https://www.arduino.cc/reference/en/libraries/radiohead/)
- FCC ID [2A63C-NRF24L01](https://fcc.report/FCC-ID/2A63C-NRF24L01) report (Shenzhen Danaotiankong Technology Co., Ltd) for MakerFocus NRF24L01+2.4GHz Wire Less RF Transceiver Module
- Note: Finished wiring the motor controller & motors
  - MCU-1: Radio Server - Joystick Input
  - MCU-2: Radio Client & I2C Master - Intermediary between MCU-1 & MCU-3
  - MCU-3: I2C Slave - Controller & Motors

## Digi XBee-PRO 900HP DigiMesh kit
- 20250826 actively testing radios. The Digi XCTU software was used to re-configure set-1 with 3 radios and all passed the simple AT mode communications. When initially recieved the radio after purchase, it was assumed their configuration were identical. The assumption was wrong.
- The AT mode is the simple communication between two radios.
- 20250826 - Will use both the Arduino Uno and Raspberry Pi 3 where each will have a radio attached. Resullts pending []

## In Development
- 20240804 - First push for nRF24L01+
- 20240813 - The final push for nRF24L01+. The Joystick Uno L298N repository has to be updated in order to fix some motor movement issues. Those header files were moved here. Finished testing the code and worked out the Motor Movement Checklist (MMC). See the updated Study... Moving on to the next radio... Having fun.
  - The *#define RUN_WITH_DEBUG_CODE* in the Common.h file was the only debug used for 1 second intervals for testing and for data acquisiton for the MMC. Shorter time intervals is still pending when time permits.

## Disclaimer and Terms
- Must read from this repository
