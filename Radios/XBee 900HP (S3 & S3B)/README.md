## Radio - XBee-PRO 900HP - 900 MHz RF Module
### Work in Progress (There is some redundency)
- Digi International - XBee-PRO 900HP (S3B) DigiMesh, 900MHz, 250mW, Wire Antenna, 200Kbps (North America XBP9B-DMWT-002). The Digi XBee-PRO 900HP DigiMesh Kit (US/Canada XKB9-DMT-UHP) comes with three radios.
    - **Recommended Digi User Guides**
        - Digi XBee-PRO 900HP DigiMesh Kit - Radio Frequency (RF) Module - User Guide
            - Supplemental: Digi - XBee-PRO 900HP/XSC RF Modules - S3 and S3B - User Guide (This guide has more information.)
        - Digi - XCTU - Configuration and Test Utility Software
        - Digi - XBee Grove Development Board - User Guide
- Digi XCTU - Configuration and Test Utility Software.
    - Radio module operating mode
        - AT operating mode
        - API operating mode (SPI communication requires this operating mode.)
        - API escaped operating mode
- Addional Information - Arduino Uno
    - [Digi International Inc. **Github**](https://github.com/digidotcom)
        - [digidotcom/xbee_ansic_library **Github**](https://github.com/digidotcom/xbee_ansic_library)
            - [Overview of Digi International's ANSI C XBee(R) Host Library **Github**](https://digidotcom.github.io/xbee_ansic_library/)
    - Furthermore, Digi makes reference to [Felix Galindo - **Github**](https://github.com/felixgalindo)
        - [XBee C Library](https://github.com/felixgalindo/xbee_c_library)
            - [XBeeArduino](https://github.com/felixgalindo/XBeeArduino)
- SPI implementation for the XBee-PRO 900HP (S3B) (source: *XBee®-PRO 900HP/XSC RF Modules S3 and S3B - User Guide*)
    - **The XBee-PRO 900HP RF Module operates as a SPI slave only.** This means an **external master** like Arduino Uno provides the clock and decides when to send data. The XBee-PRO 900HP RF Module supports an external clock rate of up to 3.5 Mb/s.
    - The device transmits and receives data with the **most significant bit first using SPI mode 0**. This means the CPOL and CPHA are both 0. We chose Mode 0 because it is the typical default for most microcontrollers and simplifies configuring the master.
    - The specification for SPI includes the four signals: **SPI_MISO**, **SPI_MOSI**, **SPI_CLK**, and **SPI_SSEL**. Using only these four signals, the master cannot know when the slave needs to send and the SPI slave cannot transmit unless enabled by the master. For this reason, the **SPI_ATTN** signal is available. This allows the device to alert the SPI master that it has data to send. In turn, the SPI master asserts SPI_SSEL and starts SPI_CLK unless these signals are already asserted and active respectively. This allows the XBee-PRO 900HP RF Module to send data to the master.
    - Full duplex operation
        - SPI on the XBee-PRO 900HP RF Module requires that you use **API mode (without escaping)** to packetize data. By design, SPI is a full duplex protocol even when data is only available in one direction. This means that when a device receives data, it also transmits and that data is normally invalid. Likewise, when the device transmits data, invalid data is probably received. To determine whether or not received data is invalid, we packetize the data with API packets.
        - SPI allows for valid data from the slave to begin before, at the same time, or after valid data begins from the master. When the master is sending data to the slave and the slave has valid data to send in the middle of receiving data from the master, this allows a true full duplex operation where data is valid in both directions for a period of time. Not only must the master and the slave both be able to keep up with the full duplex operation, but both sides must honor the protocol as specified.
- API mode and API frame format
    - As an alternative to Transparent operating mode, you can use API operating mode. API mode provides a structured interface where data is communicated through the serial interface in organized packets and in a determined order. This enables you to establish complex communication between devices without having to define your own protocol. The API specifies how commands, command responses and device status messages are sent and received from the device using the serial interface or the SPI interface.
        - API operation (AP parameter = 1)

| Frame fields | Byte | Description |
| ----- | ----- | ----- |
|Start delimiter | 1 | 0x7E |
| Length | 2 - 3 | Most Significant Byte, Least Significant Byte |
| Frame data | 4-n | API-specific structure |
| Checksum | n+1 | 1 byte |


## Digi XBee-PRO 900HP RF (S3 & S3B) Module
### Pin signals (Pin connections)

| Pin No. | Name | Direction | Default state | Description |
| ----- | ----- | ----- | ----- | ----- |
| 1 | VCC | | | Power Supply |
| 2 | DOUT/DIO13 | Both | Output | GPIO/UART data out |
| 3 | DIN/<span style="text-decoration:overline">CONFIG</span>/DIO14 | Both | Input | GPIO/UART data in |
| 4 | DIO12/**SPI_MISO** | Both | Output | GPIO/SPI slave out |
| 5 | <span style="text-decoration:overline">RESET</span> | Input | | Device reset. Drive low to reset the device. This is also an output with an open drain configuration with an internal 20 kΩ pull-up (never drive to logic high, as the device may be driving it low). The minimum pulse width is 1 mS. |
| 6 | DIO10/PWM0 | Both | | GPIO/RX signal strength indiactor. |
| 7 | DIO11/PWM1 | Both | | GPIO/pulse width modulator |
| 8 | Reserved | | Disabled | Do not connect |
| 9 | <span style="text-decoration:overline">DTR</span>/SLEEP_RQ/DIO8 | Both | Input | GPIO/pin sleep control line (DTR on the development board) |
| 10 | GND | | | Ground |
| 11 | DIO4/**SPI_MOSI** | Both | | GPIO/SPI Slave in |
| 12 | <span style="text-decoration:overline">CTS</span>/DIO7 | Both | Output | GPIO/clear-to-send flow control |
| 13 | ON_SLEEP/DIO9 | Output | Output | GPIO/module status indicator |
| 14 | VREF | Input | | Internally used for the programmable secondary processor. For compatibility with other XBee devices, we recommend connecting this pin to the voltage reference if you desire analog sampling. Otherwise, connect to GND. |
| 15 | Associate/DIO5 | Both | Output | GPIO/associate indicator |
| 16 | <span style="text-decoration:overline">RTS</span>/DIO6 | Both | Input | GPIO/request-to-send flow control |
| 17 | AD3/DIO3/ <span style="text-decoration:overline"><b>SPI_SSEL</b></span> | Both | | GPIO/analog input/SPI slave selesct |
| 18 | AD2/DIO2/**SPI_CLK** | Both | | GPIO/analog input/ SPI clock |
| 19 | AD1/DIO1/**SPI_ATTN** | Both | | GPIO/analog input/SPI attention |
| 20 | AD0/DIO0 | Both | | GPIO/analog input |

### UART pin assignments

| UART pins | Device pin Number |
| ----- | ----- |
| DOUT | 2 |
| DIN/<span style="text-decoration:overline">CONFIG</span> | 3 |
| <span style="text-decoration:overline">CTS</span>/DIO7 | 12 |
| <span style="text-decoration:overline">RTS</span>/DIO6 | 16 |

### SPI pin assignments

| SPI pins | Device pin number |
| ----- | ----- |
| **SPI_SCLK**/DIO18 | 18 |
| <span style="text-decoration:overline"><b>SPI+SSEL</b></span>/DIO17 | 17 |
| **SPI_MOSI**/DIO16 | 11 |
| **SPI_MISO**/DIO15 | 4 |
| <span style="text-decoration:overline"><b>SPI_ATTN</b></span>/DIO1 | 19 |

## Experimental Approach (For author's purposes ONLY - DO NOT TRY)
- Using an Arduino Uno with an XBee 900HP in **SPI mode** similarly with the radio nRF24L01+ requires three primary steps: hardware connection, configuring the XBee for SPI and API modes, and writing the Arduino code. (*The Raspberry Pi 3 will be tested once the Arduino Uno test is completed.*) Since the Arduino Uno uses 5V logic and the XBee 900HP uses 3.3V logic, its important a **logic level shifter** is used for safety.

### (1) Hardware connection

| Arduino Uno  (Master) | Logic Level Shifter | XBee 900HP (Slave) | Connection Detail                 |
| ---- | ---- | ---- | ---- |
| **SS** (Pin 10) | Low Voltage (LV) | **SPI_nSSel** (Pin 17) | **Chip select line** for controlling the XBee. |
| **MOSI** (Pin 11) | LV | **SPI_MOSI** (Pin 11) | **Master-Out Slave-In** for transmitting data. |
| **MISO** (Pin 12) | High Voltage (HV) | **SPI_MISO** (Pin 4) | **Master-In Slave-Out** for receiving data. |
| **SCK** (Pin 13) | LV | **SPI_Clk** (Pin 18) | SPI Clock generated by Arduino. |
| **GND** | GND | **GND** | Common Ground Connection |
| **5V** | HV | - | Powers the high-voltage side of the shifter. |
| - | LV | **VCC** (Pin 1) | The 3.3V supply for the XBee. |
| - | LV | **SPI_nATTN** (Pin 19) | An optional pin for the XBee to alert the Arduino that data is ready. |

### (2) Configure the XBee

- The **Digi XCTU software** is used to change the XBee settings from the default UART mode to SPI and API mode. This requires connecting the XBee to the computer using a USB connection. (*The Digi Xbee-PRO 900HP DigiMesh Kit comes with development boards which has this USB cababilties.*)
    1. **Read your current settings:** Open XCTU and select the XBee.
    2. **Enable SPI:** Go to the I/O Settings section and configure the following pins:
            * **P1(SPI_nATTN):** Set to 3 (SPI_nATTN)
            * **P2(SPI_MISO):** Set to 4 (SPI_MISO)
            * **P3(SPI_MOSI):** Set to 3 (SPI_MOSI)
            * **P4(SPI_CLK):** Set to 2 (SPI_CLK)
            * **P8(SPI_nSSel):** Set to 1 (SPI_nSSel)
    3. **Enable API mode:** Serial port flow control is not possible when using the SPI port. The SPI only operates in API mode 1. The SPI does not support Transparent mode or API mode 2 (with escaped characters). This means that the AP configuration only applies to the UART interface and is ignored while using the SPI. (source: *Digi XBee®-PRO 900HP/XSC RF Modules - User Guide*) S3 and S3B.
    4. **Save settings:** Write the changes to the module.

### (3) Arduino Uno sketch (Experimental)
    - SCRATCH
### Alternate Code: Transmitting an API frame
    - SCRATCH
### Alternate Code: Receiving an API frame
    - SCRATCH

### ***include folder***

### ***src folder***

### ***root folder***

### Notes
- Under review and testing

### How to use this repository
- Open PlatformIO with a new project...
- Copy and Paste contents from here into your project...
- Install RadioHead Lib from PlatformIO.
    - Understand how to use the platformio.ini file with multiple src folders - see file for details.
