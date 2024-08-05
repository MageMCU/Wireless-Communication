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
L298N motorsL298N;
LinearMap<float> mapInput;
LinearMap<float> mapOutput;
TypeConv typeConv;
Timer timerDebug;

void setup()
{
    // #ifdef DEBUG_CODE
    Serial.begin(9600);
    while (!Serial)
        ;
    Serial.println("I2C - Serial 9600 baudrate");
    // #endif

    // Assign BusI2C Object
    busI2C = BusI2C();
    // Wire.BEGIN: Include Timeout
    busI2C.Begin(I2C_SLAVE_ADDR_0x16, I2C_TIMEOUT_uS, true);

    // Temp Variables
    int8_t ENA = 5;
    int8_t IN1 = 6;
    int8_t IN2 = 7;
    int8_t IN3 = 8;
    int8_t IN4 = 9;
    int8_t ENB = 10;
    int8_t LeftMotorPWM = ENB;
    // EASY METHOD (See article 1009 L298N Supplemental)
    // Can switch variable pairs IN1 & IN2
    // for either Left Motor A & B or Right Motor A & B
    // variables and also their order arrangement for
    // either A or B; and the same fore variable pairs
    // IN3 & IN4...
    // Finally try switching ENB & ENA (???)
    int8_t LeftMotorA = IN3;
    int8_t LeftMotorB = IN4;
    int8_t RightMotorA = IN1;
    int8_t RightMotorB = IN2;
    int8_t RightMotorPWM = ENA;

    // Assign L298N Object
    motorsL298N = L298N(LeftMotorPWM, LeftMotorA, LeftMotorB,
                        RightMotorA, RightMotorB, RightMotorPWM);
    motorsL298N.SetupPinsL298N();
    //
    typeConv = csjc::TypeConv();
}

// All debug statements occur here in the main.cpp file
// #ifdef DEBUG_CODE
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

        // #ifdef DEBUG_CODE
        Serial.print("I2C-MCU-3: 0x");
        Serial.print(data.i2cAddress, HEX);
        if (data.buttonState)
        {
            Serial.print(" But-ON");
            Debug("-Motors:", data.dataX, data.dataY, 0);
        }
        else
            Serial.println(" But-OFF");
        // #endif
    }
}

void loop()
{
    if (timerDebug.isTimer(BUTTON_TIMER_mS))
    {
        // I2C RECEIVE (Uses Interrupt call-back)
        Wire.onReceive(SlaveReceiveI2C);

        // SAFETY - MOTORS
        if (data.buttonState)
        {
            // L298N
            motorsL298N.updateL298N(data.dataX, data.dataY);
#ifdef DEBUG_CODE
            // Debug - State Motor ON
            Serial.print("But-ON: ");
#endif
        }
        else
        {
            motorsL298N.PowerDownL298N();
#ifdef DEBUG_CODE
            // Debug - State Motor ON
            Serial.print("But-OFF: ");
#endif
        }
        busI2C.ClearTimeout();
    }
}