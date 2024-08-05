# Wireless-Communication
- After six months of review, I have decided to start with these device(s). It is my hope to complete this project by the end of 2024. 

## Testing Platform
- This MCU chip **Atmega328P** is well known and the price is affordable as well as most of the robotic hardware that is described here. The Arduino Uno board comes with a removable MCU.
- **PlatformIO** is a cross-platform, cross-architecture, multiple framework, professional tool for embedded systems engineers and for software developers who write applications for embedded products. 
- **Visual Studio Code** is a streamlined code editor and it runs on macOS, Linux, and Windows. The best thing about VSCode, it is free.
  
## Nordic nRF24L01 - Radio Transceiver 
- Preliminary Test [Study](https://drive.google.com/file/d/1nfAlSv4Ejyql8hRYMXsEH_Gaa7wh_Z5n)
- RadioHead version 1.22.1 by Mike McCauley [Arduino Reference Libraries](https://www.arduino.cc/reference/en/libraries/radiohead/)
- FCC ID [2A63C-NRF24L01](https://fcc.report/FCC-ID/2A63C-NRF24L01)
- Note: Finished wiring the motor controller & motors
  - MCU-1: Radio Server - Joystick Input
  - MCU-2: Radio Client & I2C Master - Intermediary between MCU-1 & MCU-3
  - MCU-3: I2C Slave - Controller & Motors
- Timing Strategy is at Radios 100ms & I2C 50ms (this could be tweaked even further - maybe) The motors responded quite nicely.
- Could NOT get the amplified nRF24L01 radios to work... Could not find the FCC ID report for these either... I recommend the inexpensive radios with the FCC ID 2A63C-NRF24L01 report (Amazon) for now until the user can get their project up and running.

## Digi XBee-PRO 900HP DigiMesh Kit (US/Canada) XKB9-DMT-UHP
- Preliminary Test (private for now)
