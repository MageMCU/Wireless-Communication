//
// Carpenter Software
// File: Class Common.h
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
// MIT LICENSE
//

#ifndef Common_h
#define Common_h

// Communications
// Radio NRF24L01 & I2C
#define RADIO_CLIENT_ADDRESS 1
#define RADIO_SERVER_ADDRESS 2
// Wire I2C - Radio Client - Master UNO 
#define I2C_MASTER_ADDR_0x14 0x14
// Wire I2C - Slave UNO----------------------------
#define I2C_SLAVE_ADDR_0x16 0x16
// MESSAGE SIZE FOR BOTH RADIO & I2C
#define COMM_MESSAGE_SIZE 7

// Comment-out "// #define RUN_WITH_DEBUG_CODE"s
// to remove Serial Debugging
#define RUN_WITH_DEBUG_CODE
// ------------------------------------------------------
// ------------------------------------------------------
// DO NOT TOUCH - USE #define above, not its condition.
// ------------------------------------------------------
// ------------------------------------------------------
#ifdef RUN_WITH_DEBUG_CODE
// ------------------------------------------------------
// #define DEBUG_SERVER
// #define DEBUG_CLIENT
// #define DEBUG_I2C
#define DEBUG_JOYSTICK
#define DEBUG_L298N
#define DEBUG_SERIAL
#define RADIO_DELAY_mS 1000
#define RADIO_TIMEOUT_mS 200
#define RADIO_TRIES 3
#define JOYSTICK_TIMER_mS 1000
#define I2C_TIMER_mS 1000
#else
// I played with the timing but
// it could have been tweeked 
// even more...
#define DEBUG_SERVER
#define DEBUG_CLIENT
#define DEBUG_I2C
#define DEBUG_JOYSTICK
#define DEBUG_L298N
#define DEBUG_SERIAL
//
#define RADIO_DELAY_mS 250
#define RADIO_TIMEOUT_mS 100
#define RADIO_TRIES 2
#define JOYSTICK_TIMER_mS 250
#define I2C_TIMER_mS 250
#endif // debug
// ------------------------------------------------------
// ------------------------------------------------------
// Time-Out in microseconds (default 25000)
// 50 ms
#define I2C_TIMEOUT_uS 50000
//
struct Common
{
    uint8_t i2cAddress;
    uint8_t buttonState;
    uint8_t fsmStates;
    int16_t dataX;
    int16_t dataY;
};

#endif // hearder