//
// Carpenter Software
// Processor: MCU-3
// src Folder: I2C - File: main.cpp
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
#include <SPI.h>

#include "Common.h"
#include "Headers.h"

// Arduino Uno as Master communicates with another Arduino as Slave.
// ----------------------------------------------------
// CAUTION: platformio.ini ---------------------------- BEWARE
// MASTER MCU: Change to MasterUno folder
//             Upload to Master-MCU
// SLAVE MCU: Change to SlaveUno folder
//             Upload to Slave-MCU
// ----------------------------------------------------
// ----------------------------------------------------
// Note that some Wire call functions reside in both
// BusI2C.h and main.cpp...
// ----------------------------------------------------

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Global Declartions
BusI2C busI2C;
Common data;
uint8_t i2cRX[COMM_MESSAGE_SIZE];
//
L298N motors;
LinearMap<float> mapInput;
LinearMap<float> mapOutput;
TypeConv typeConv;
Timer timerDebug;

void setup()
{
#ifdef DEBUG_SERIAL
    Serial.begin(9600);
    while (!Serial)
        ;
    Serial.println("I2C - Serial 9600 baudrate");
#endif

    // Assign BusI2C Object
    busI2C = BusI2C();
    // Wire.BEGIN: Include Timeout
    busI2C.Begin(I2C_SLAVE_ADDR_0x16, I2C_TIMEOUT_uS, true);

    // Arduino PINS
    int8_t ENA = 5;
    int8_t IN1 = 6;
    int8_t IN2 = 7;
    int8_t IN3 = 8;
    int8_t IN4 = 9;
    int8_t ENB = 10;
    // L298N PINS
    int8_t LeftEN = ENA;
    int8_t LeftA = IN1;
    int8_t LeftB = IN2;
    int8_t RightA = IN3;
    int8_t RightB = IN4;
    int8_t RightEN = ENB;

    // L298N Constructor
    motors = L298N(LeftEN, LeftA, LeftB,
                   RightA, RightB, RightEN);
    // Initiate L298N Pins
    motors.PinsL298N();
    // See Joystick-Uno-L298N in how to use....
    motors.Bits(BitsL298N::bits_1111);
    //
    typeConv = csjc::TypeConv();
}

// Callback
void SlaveReceiveI2C(int numberBytes)
{
    uint8_t message[numberBytes];
    busI2C.ReceiveMessage(message, numberBytes);

    // Build the data back to its original values....
    if (message[0] == I2C_SLAVE_ADDR_0x16)
    {
        data.i2cAddress = message[0];
        data.buttonState = message[1];
        data.fsmStates = message[2];
        data.dataX = typeConv.BytesToWord(message[3], message[4]);
        data.dataY = typeConv.BytesToWord(message[5], message[6]);

#ifdef DEBUG_I2C
        Serial.print("I2C-MCU-3: 0x");
        Serial.println(data.i2cAddress, HEX);
        if (data.buttonState)
        {
            Debug("-Motors:", data.dataX, data.dataY);
        }
#endif

    }
}

void loop()
{
    if (timerDebug.isTimer(I2C_TIMER_mS))
    {
        // I2C RECEIVE (Uses Interrupt call-back)
        Wire.onReceive(SlaveReceiveI2C);

        // SAFETY - MOTORS
        if (data.buttonState)
        {
            // L298N
            motors.UpdateL298N(data.dataX, data.dataY, true);
#ifdef DEBUG_I2C
            // Debug - State Motor ON
            Serial.println("But-ON: ");
#endif
        }
        else
        {
            motors.PowerDownL298N();
#ifdef DEBUG_I2C
            // Debug - State Motor ON
            Serial.println("But-OFF: ");
#endif
        }
        busI2C.ClearTimeout();
    }
}