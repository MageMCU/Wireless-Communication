# Wireless-Communication
- After six months of review, I have decided to start with these device(s). It is my hope to complete this project by the end of 2024. There were other radios under review but decided against using them because the IDE and code was beyond a beginners capability... Maybe later...
- I reviewed several radios but I have been having bad luck with the amplified NRF24L01, the ESP32 and the XBee 900. Many of these radios have been returned back for one reason or another. This repository is now on hold for the year 2024. It will continue again around the middle 2025.

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
- Timing Strategy is at Radios 100ms & I2C 50ms (this could be tweaked even further - maybe) The motors responded quite nicely.
- Could NOT get the amplified nRF24L01 radios to work... Could not find the FCC ID report for these either...
- It's recommended that the inexpensive radios *about $1 each from Amazon* having the FCC ID 2A63C-NRF24L01 report at least for now until the user can get their project up and running.

## In Development
- 20240804 - First push for nRF24L01+
- 20240813 - The final push for nRF24L01+. The Joystick Uno L298N repository has to be updated in order to fix some motor movement issues. Those header files were moved here. Finished testing the code and worked out the Motor Movement Checklist (MMC). See the updated Study... Moving on to the next radio... Having fun.
  - The *#define RUN_WITH_DEBUG_CODE* in the Common.h file was the only debug used for 1 second intervals for testing and for data acquisiton for the MMC. Shorter time intervals is still pending when time permits.

## Disclaimer and Terms
- Please read
