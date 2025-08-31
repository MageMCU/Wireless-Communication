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
    - Digi - [Do more with API mode: XBee libraries](https://docs.digi.com//resources/documentation/digidocs/90001496/concepts/c_xbee_libraries_api_mode.htm?TocPath=XBee%20API%20mode%7C_____6)
        -  While using the Arduino SPI.h library is possible for low-level communication, there is no official or widely-supported Arduino library specifically for the XBee 900HP (S3/S3B) using SPI. The popular xbee-arduino library only supports API mode over a UART (serial) connection, not SPI. 
            - Sent support request to Digi on this issue otherwise there seems to be a lot of develpment ahead...
    - Andrew Rapp github [xbee-arduino](https://github.com/andrewrapp/xbee-arduino)

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

- Use the Arduino SPI library to set up the Uno as the master and send and receive API frames to and from the XBee. The following is a basci structure for communication. (source: *Google AI*) The code is a work in progress.

```c++
// CODE HAS YET TO BE TESTED - CHECK SYNTAX

#include <SPI.h>

// Define Xbee SPI pins fro Arduino Uno
const int XBEE_SS_PIN = 10;
const int XBEE_nATTN_PIN = 9;

void setup() {
    Serial.begins(9600);
    SPI.begin();
    // Set the Slave Select (SS) pin as an output and set it high
    // to deselect the XBee initially.
    pinMode(XBEE_SS_PIN, OUTPUT);
    digitalWrite(XBEE_SS_PIN, HIGH);

    // Configure the SPI settings for the XBee 900HP
    // The XBee uses uses SPI mode 0 (CPOL=0, CPHA=0) and MSB first.
    SPI.beginTransaction(SPISettings(5000000, MSFIRST, SPI_MODE0));

    // Optional: Listen for the ATTN pin for incoming data
    pinMode(XBEE_nATTN_PIN, INPUT);
}

void loop() {
    // Example: Send an API frame
    if (Serial.available()) {
        char receivedChar = Serial.read();
        if (receivedChar == 's' {
            sendXBeeApiFrame();
        }
    }

    // Example: Check for incoming data from XBee
    if (digitalRead(XBEE_nATTN_PIN) == LOW) {
        readXBeeApiFrame();
    }
}

void sendXBeeApiFrame() {
    // Example API frame payload (e.g. AT command frame)
    byte frame[] = {0x7E, 0x00, 0x04, 0x08, 0x01, 0x4E, 0x49, 0x6E);

    // Selcet the XBee
    digitalWrite(XBEE_SS_PIN, LOW);

    for (int i = 0; i < sizeof(frame); i++) {
        SPI.transfer(frame[i]);
    }

    // Deselect the XBee
    digitalWrite(XBEE_SS_PIN, HIGH);

    Serial.println("API frame sent");
}

void readXBeeApiFrame() {
    // Read incoming data when the attention pin is low
    // Select the XBee
    digitalWrite(XBEE_SS_PIN, LOW);

    // The XBee documentation is key to correctly interpreting the API frame...
    // The frame begins with the start delimiter (0x7E) and has the length feild...
    // The SPI.transfer() function perfoems a simultaneous reand and write.
    bytr receivedByte = SPI.transfer(0xFF);

    // Read the rest of the fram based on the length field
    // ...

    // Deselect the XBee
    digitalWrite(XBEE_SS_PIN, HIGH);
}

// Working on other versions that are similar to this code...
```
- The key consideration are (1) the Logic Level Shifter, (2) the API Frame format, (3) the SPI_nATTN Pin and (4) Dedicated SPI Libtrary.
    - The standard Arduino SPI.h library is functional but using a specialized XBee library (such as the one from Digi) can significantly simplify the process of constructing and parsing API frames. (Digi may not have an Arduino SPI library for these particular radios...)

### Alternate Code: Transmitting an API frame

```c++
// CODE HAS YET TO BE TESTED - CHECK SYNTAX

// Arduino library
#include <SPI.h>
// Github: Andrew Rapp - repository: xbee-arduino
// Used for packet handling - In API mode, the XBee 
// module encapsulates data in structured packets, 
// including information like sender address, API ID, 
// data length, and payload.
#include <XBee.h>

// Define the pin for the XBee SPI nATTN line
const int XBEE_ATTN = 2;

// Create an XBee object
XBee xbee = XBee();

// Setup the XBee API frame
Tx64Request tx = Tx64Request();
TxStatusResponse txStatus = TxStatusResponse();

void setup() {
    Serial.begin(9600);
    SPI.begin();

    // Setup the interrupt for the XBee ATTN pin
    pinMode(XBEE_ATTN, INPUT);
    attachInterrupt(digitalPinTpInterrupt(XBEE_ATTN), attn_interrupt, FALLING);

    // Initialize the XBee library with the SPI interface
    xbee.setSpi(SPI);
    Serial.println("XBee in SPI mode is ready to transmit");
}

void loop() {
    // Example: Transmit a message to the other XBee every 5 seconds
    if (millis() % 5000 == 0) {
        uint8_t payload[] = {'H', 'e', 'l', 'l', 'o'};
        // Send to broastcast address 0xFFFF
        tx = Tx64Request(0x0000000000000FFFF, payload, sizeof(payload));
        xbee.send(tx);

        // After sending, wait for the status response from the XBee
        if (xbee.readPacket(5000)) {
            if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
                xbee.getResponse().getTxStatusResponse(txStatus);
                if (txStatus.getStatus() == SUCCESS) {
                    Serial.println("Transission successful.");
                } else {
                    Serial.print("Transmission failed with error code: ");
                    Serial.println(txStatus.getStatus());
                }
            }
        }
    }
}

void attn_interrupt() {
    // Read and process incoming packets
    // This helps prevent SPI buffer overruns
    xbee.readPacket();
    // Handle the received packet here if needed
}

```

### Alternate Code: Receiving an API frame
```c++
#include <SPI.h>
#include <XBee.h>

// Define the pin for the XBee SPI_nATTN line
const int XBee_nATTN = 2;

// Create an XBee object
XBee xbee = XBee();

// Create a receive packet object
Rx64Response rx64 = Rx64Response();

void setup() {
    Serial.begin(9600);
    SPI.begin();

    // Setup the interrupt for the XBee ATTN pin
    pinMode(XBee_nATTN, INPUT);
    attachInterrupt(digitalPinTpInterrupt(XBee_nATTN), attn_interrupt, FALLING);

    // Initialize the XBee library with the SPI interface
    xbee.setSpi(SPI);
    Serial.println("XBee in SPI mode is ready to receive");
}

void loop() {
    // Check if packet is available
    

}


```

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
