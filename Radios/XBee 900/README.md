## Radio - XBee-PRO 900HP - 900 MHz RF Module
- Digi International - XBee-PRO 900HP embedded modules provide best-in-class range wireless connectivity to devices. They take advantage of the DigiMesh networking protocol, featuring dense network operation and support for sleeping routers, and are also available in a proprietary point-to-multipoint configuration. Supporting RF line-of-sight ranges up to **28 miles** (*with high-gain antennas*), and data rates of up to 200 Kbps, these modules are ideal for extended-range applications requiring increased data throughput. The XBee-PRO 900HP requires no programming and can be configured easily using Digi’s free **X-CTU** software or via a simplified AT command set. (datasheet)
- **Serial Communication**
    - An XBee module can operate as a stand-alone device or it can be attached to an intelligent device. For example, you can place several battery-powered XBee modules in remote locations to gather data such as temperature, humidity, light, or liquid level.
        - When operating as a stand-alone device, an XBee module simply sends sensor data to a central node.
        - When an XBee module is connected to an intelligent device (such as a computer, **Arduino**, or **Raspberry Pi**), it uses serial communication:
            - The intelligent device sends data through the serial interface to the XBee module to be transmitted to other devices over the air.
            - The XBee module receives wireless data from other devices, and then sends the data through the serial interface to the intelligent device.
    - The XBee modules **interface to a host device such as a microcontroller or computer through a logic-level asynchronous serial port**. They use a **UART** for serial communication with those devices.
    - For additional information about serial communication, go to the **XBee-PRO 900HP and XSC RF Modules User Guide**.
    - Microcontrollers attached to an XBee module can process the information received by the module and thus monitor or even control remote devices by sending messages through their local XBee module.
    - For prototyping, you can use external microcontrollers such as **Arduino** or **Raspberry Pi**, **sockets**, and **breadboards**.
    - *XBee-PRO 900HP DigiMesh Kit - Radio Frequency (RF) Module - User Guide*
- namespace ***csjc***

## Experimental Approach
- Using an Arduino Uno with an XBee 900HP in **SPI mode** similarly with the radio nRF24L01+ requires three primary steps: hardware connection, configuring the XBee for SPI and API modes, and writing the Arduino code. (*The Raspberry Pi 3 will be tested once the Arduino Uno test is completed.*) Since the Arduino Uno uses 5V logic and the XBee 900HP uses 3.3V logic, its important a **logic level shifter** is used for safety.
- **(1) Hardware connection**

| Arduino Uno  (Master) | Logic Level Shifter | XBee 900HP (Slave) | Connection Detail                 |
| ---- | ---- | ---- | ---- |
| **SS** (Pin 10) | Low Voltage (LV) | **SPI_nSSel** (Pin 17) | **Chip select line** for controlling the XBee. |
| **MOSI** (Pin 11) | LV | **SPI_MOSI** (Pin 11) | **Master-Out Slave-In** for transmitting data. |
| **MISO** (Pin 12) | High Voltage (HV) | **SPI_MISO** (Pin 4) | **Master-In Slave-Out** for receiving data. |

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
