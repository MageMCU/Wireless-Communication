//
// Carpenter Software
// Processor: MCU-1
// src Folder: server - File: main.cpp
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

// Singleton instance of the radio driver
RH_NRF24 driver;
// RH_NRF24 driver(8, 7);   // For RFM73 on Anarduino Mini

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, RADIO_SERVER_ADDRESS);

// Carpenter Software - Jesse Carpenter
using namespace csjc;

// Source: Github - MageMCU - SJUL
Joystick<float> joystick;
LinearMap<float> ADCtoJoystickInputs;
LinearMap<float> joystickOutputsToMotors;
TypeConv typeConv;

Timer timerDebug;
Button buttonMotors;

// Max Data Size 28
uint8_t radioTX[COMM_MESSAGE_SIZE];
// Dont put this on the stack:
uint8_t radioRX[RH_NRF24_MAX_MESSAGE_LEN];

// Global data
Common data;

void setup()
{
// #ifdef DEBUG_CODE
    Serial.begin(9600);
    while (!Serial)
        ;
    Serial.println("RADIO SERVER - Serial 9600 baudrate");
// #endif
    //
    if (!manager.init())
#ifdef DEBUG_CODE
        Serial.println("init failed")
#endif
            ;
    // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
    // Default is 200ms
    manager.setTimeout(RADIO_TIMEOUT_mS);
    manager.setRetries(RADIO_TRIES);
    //
    joystick = Joystick<float>();
    ADCtoJoystickInputs = LinearMap<float>(0, 1023, -1.0, 1.0);
    joystickOutputsToMotors = LinearMap<float>(-1.0, 1.0, -255, 255);
    //
    timerDebug = Timer();
    //
    int buttonPin = 4;
    int ledPin = 2;
    buttonMotors = Button(buttonPin, ledPin);
    //
    typeConv = TypeConv();
}

// All debug statements occur here in the main.cpp file
// #ifdef DEBUG_CODE
template <typename T1, typename T2>
void Debug(String msg, T1 a, T2 b)
{
    Serial.print(msg);
    Serial.print(" a: ");
    Serial.print(a);
    Serial.print(" b: ");
    Serial.println(b);
}
// #endif

void checkTransmissions()
{
#ifdef DEBUG_CODE
    Serial.print("Server: TX-CNT: ");
    Serial.println(manager.retransmissions());
#endif
    // Total timeout for 3 retries is about 600ms
    if (manager.retransmissions() >= RADIO_TRIES)
        manager.resetRetransmissions();
}

void updateRadio()
{
    // Best practice is to use the same processors (and
    // radios) throughout your network. (RHReliableDatagram file)
    //
    // RHReliableDatagram is reliable in the sense
    // that messages are acknowledged by the recipient,
    // and unacknowledged messages are retransmitted until
    // acknowledged or the retries are exhausted.
    // * setTimeout - Defaults to 200ms.
    // * setRetries - Defaults to 3... [Number of tries starts at zero (0)? If tries stops at 2?] Question ------
    //
    // Wait for a message addressed to us from the client
    uint8_t len = sizeof(radioRX);
    uint8_t from;

    // Receive RX
    // When addressed messages are collected by the application (by recvfromAck()),
    // an acknowledgement is automatically sent to the sender.  (RHReliableDatagram file)
    if (manager.recvfromAck(radioRX, &len, &from))
    {
// #ifdef DEBUG_CODE
        Serial.print("RX-request from : 0x");
        Serial.print(from, HEX);
        Serial.print(": ");
        Serial.println((char *)radioRX);
// #endif
        // Transmit TX
        // When addressed messages are sent (by sendtoWait()), it will wait for an ack, and retransmit
        // after timeout until an ack is received or retries are exhausted.  (RHReliableDatagram file)
        if (!manager.sendtoWait(radioTX, sizeof(radioTX), from))
        {
            // Serial.println("sendtoWait failed");
            Serial.println("X");
        }
            
    }
}

void updateRadioData(int xAnalog, int yAnalog)
{
    // Continued from updateMotors()

    // Transmit Joystick-Motors Data
    // data - Button state
    radioTX[0] = (uint8_t)0x0; // Used for I2C
    radioTX[1] = data.buttonState;
    radioTX[2] = (uint8_t)0x0; // AI States (Not Used)
    // Input-X
    typeConv.WordTo2Bytes(xAnalog);
    radioTX[3] = typeConv.GetHiByte();
    radioTX[4] = typeConv.GetLoByte();
    // Input-Y
    typeConv.WordTo2Bytes(yAnalog);
    radioTX[5] = typeConv.GetHiByte();
    radioTX[6] = typeConv.GetLoByte();
}

void updateMotors(float inputX, float inputY)
{
    // Continued from updateJoystick()

    // (3)
    // Joystick Algorithm
    joystick.UpdateInputs(inputX, inputY);
    // Joystick Outputs
    float outputX = joystick.OutLeft();
    float outputY = joystick.OutRight();

#ifdef DEBUG_CODE
    Debug<float>("JS-Out: ", outputX, outputY);
#endif

    // (4)
    // Map Joystick Outputs to Motor Inputs
    // See setup() for Map arguments
    // Easier to transmit integers
    int motorLeft = (int)joystickOutputsToMotors.Map(outputX);
    int motorRight = (int)joystickOutputsToMotors.Map(outputY);

// #ifdef DEBUG_CODE
    // Use integers for radio data (easier)
    Debug<int>("motors: ", motorLeft, motorRight);
// #endif
    // (5) Update Radio Data
    updateRadioData(motorLeft, motorRight);
}

bool updateButton()
{
    bool flag = buttonMotors.isButtonOn();

// #ifdef DEBUG_CODE
    String str = "";
// #endif

    if (flag)
    {
// #ifdef DEBUG_CODE
        str = "But-ON";
// #endif
        data.buttonState = (uint8_t)1;
    }
    else
    {
// #ifdef DEBUG_CODE
        str = "But-OFF";
// #endif
        data.buttonState = (uint8_t)0;
    }

// #ifdef DEBUG_CODE
    Debug("Button: ", str, data.buttonState);
// #endif

    return flag;
}

void updateJoystick()
{
    if (updateButton())
    {
        // (1)
        // Analog to Digital (10-bit) Conversion
        // Digital Values from 0 to 1023
        // Read Article 1009 L298N Supplemental
        int xDigital = 1023 - analogRead(A1);
        int yDigital = 1023 - analogRead(A0);

#ifdef DEBUG_CODE
        Debug<int>("Analog: ", xDigital, yDigital);
        //
        int sizeInt = sizeof(int);
        Debug("bytes: ", sizeInt, (int)INT16_MAX);
#endif
        // (2)
        // Map Analogs to Joystick Inputs
        // Output range from -1 to 1
        // See setup() for Map arguments
        float inputX = ADCtoJoystickInputs.Map((float)xDigital);
        float inputY = ADCtoJoystickInputs.Map((float)yDigital);
        // Offset joystick center sensitivity
        // Experiment sensitivity starting with zero (0)
        float OFFSET = 0.05;
        // Joystick X-Input with sensitivity
        if (ABS_REAL<float>(inputX) < OFFSET)
            inputX = (float)0;
        // Joystick Y-Input with sensitivity
        if (ABS_REAL<float>(inputY) < OFFSET)
            inputY = (float)0;
#ifdef DEBUG_CODE
        Debug<float>("JS-In: ", inputX, inputY);
#endif
        // Notice: motors safety        ***
        updateMotors(inputX, inputY);
    }
    else
    {
        // Motor OFF: x=0, y=0
        // Notice: motors safety        ***
        updateMotors((float)0, (float)0);
    }
}

void loop()
{
    buttonMotors.updateButton();
    // (1) Joystick Update Process
    if (timerDebug.isTimer(BUTTON_TIMER_mS))
    {
        updateJoystick();
    }
    // R(2) H_NRF24 Radio Update
    if (manager.available())
    {
        checkTransmissions();
        updateRadio();
    }
}
