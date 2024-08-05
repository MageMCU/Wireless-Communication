//
// Carpenter Software
// Processor: MCU-2
// src Folder: client - File: main.cpp
// Github: MageMCU
// Repository: Wireless Communication
// Folder: nRF24L01
//
// By Jesse Carpenter (carpentersoftware.com)
//
// Testing Platform:
//  * MCU:Atmega328P
//  * IDE:PlatformIO
//  * Editor: VSCode
//
// MCU-1 Radio Server : Joystick Input
// MCU-2 Radio Client & I2C Master : intermediary
// MCU-3 I2C Slave : Controller & Motors Output
//
// MIT LICENSE
//

#include <Arduino.h>
#include <RHReliableDatagram.h>
#include <RH_NRF24.h>
#include <SPI.h>

#include "Common.h"

using namespace csjc;

// Singleton instance of the radio driver
RH_NRF24 driver;
// RH_NRF24 driver(8, 7);   // For RFM73 on Anarduino Mini
// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, RADIO_CLIENT_ADDRESS);
// Radio Stream Buffers
uint8_t radioTX[COMM_MESSAGE_SIZE] = "Hello";
// Dont put this on the stack:
uint8_t radioRX[RH_NRF24_MAX_MESSAGE_LEN];
//
BusI2C busI2C;
uint8_t i2cTX[COMM_MESSAGE_SIZE];
//
Timer timerRadio;
TypeConv typeConv;

void setup()
{
    Serial.begin(9600);
    while (!Serial)
        ;
    Serial.println("RADIO CLIENT & I2C - Serial 9600 baudrate");

    if (!manager.init())
        Serial.println("init failed");
    // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
    // Default is 200ms
    manager.setTimeout(RADIO_TIMEOUT_mS);
    manager.setRetries(RADIO_TRIES);
    // Assign BusI2C Object
    busI2C = BusI2C();
    // Wire.BEGIN: Include Timeout
    busI2C.Begin(I2C_MASTER_ADDR_0x14, I2C_TIMEOUT_uS, true);
    //
    timerRadio = Timer();
    //
    typeConv = TypeConv();
}

// #ifdef DEBUG_CODE
// All debug statements occur here in the main.cpp file
template <typename T1, typename T2, typename T3>
void Debug(String msg, T1 a, T2 b, T3 c, bool cFlag = false)
{
    Serial.print(msg);
    Serial.print(" a: ");
    Serial.print(a);
    Serial.print(" b: ");

    if (cFlag)
    {
        Serial.print(b);
        Serial.print(" c: ");
        Serial.println(c);
    }
    else
    {
        Serial.println(b);
    }
}
// #endif

void i2cToSlaveTransmitRadioRX()
{
    // TRANSMIT
    busI2C.TransmitMessage(I2C_SLAVE_ADDR_0x16, i2cTX, COMM_MESSAGE_SIZE);
    // Print all errors...
    Serial.println(busI2C.ErrorMsg());
}

void RadioRXData()
{
    //
    i2cTX[0] = (uint8_t)I2C_SLAVE_ADDR_0x16;
    i2cTX[1] = radioRX[1];
    i2cTX[2] = radioRX[2];
    i2cTX[3] = radioRX[3];
    i2cTX[4] = radioRX[4];
    i2cTX[5] = radioRX[5];
    i2cTX[6] = radioRX[6];
    // Debug
    int16_t X = (int16_t)typeConv.BytesToWord(radioRX[3], radioRX[4]);
    int16_t Y = (int16_t)typeConv.BytesToWord(radioRX[5], radioRX[6]);

    // #ifdef DEBUG_CODE
    Serial.print("I2C-MCU-2: 0x");
    Serial.print(i2cTX[0], HEX);
    if (i2cTX[1])
    {
        Serial.print(" But-ON");
        Debug("-Motors:", X, Y, 0);
    }
    else
        Serial.println(" But-OFF");
    // #endif
}

void checkTransmissions()
{
#ifdef DEBUG_CODE
    Serial.print("Client: TX-CNT: ");
    Serial.println(manager.retransmissions());
#endif
    if (manager.retransmissions() >= RADIO_TRIES)
    {
        manager.resetRetransmissions();
    }
}

bool updateRadio()
{
    bool flag = false;
    // Serial.println("updateRadio()");

    // Send a message to manager_server
    if (manager.sendtoWait(radioTX, sizeof(radioTX), RADIO_SERVER_ADDRESS))
    {
        // Serial.println("Sending to nrf24_reliable_datagram_server");
        //
        checkTransmissions();

        // Now wait for a reply from the server
        uint8_t len = sizeof(radioRX);
        uint8_t from;
        if (manager.recvfromAckTimeout(radioRX, &len, 2000, &from))
        {
            Serial.print("RX-reply from : 0x");
            Serial.print(from, HEX);

            Serial.print(":len: ");
            Serial.println(len);

            RadioRXData();

            flag = true;
        }

        else
        {
            // Serial.println("No reply, is nrf24_reliable_datagram_server running?");
        }
    }
    // else
        // Serial.println("sendtoWait failed");

        // Best to use a timer if OTHER functions need processing
        delay(RADIO_DELAY_mS);
        // See Loop()

        return flag;
}

void loop()
{
    if (timerRadio.isTimer(RADIO_DELAY_mS))
    {
        if (updateRadio())
        {
            i2cToSlaveTransmitRadioRX();
            busI2C.ClearTimeout();
        }
    }
}
