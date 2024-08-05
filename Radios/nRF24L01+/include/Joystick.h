//
// Carpenter Software
// File: Class Joystick.h
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

#include <Arduino.h>
#include "MiscMath.h"

#ifndef DDMR_Joystick_Algorithm_h
#define DDMR_Joystick_Algorithm_h

// Carpenter Software - Jesse Carpenter
namespace csjc
{
    // Joystick Class (Simplified for upcoming projects...)
    template <typename real>
    class Joystick
    {
    private:
        // PROPERTIES
        real j_ZERO;
        // INPUT
        real j_inputX;
        real j_inputY;
        // OUTPUT
        real j_outputLeft;
        real j_outputRight;
        // METHODS
        void j_joystick();

    public:
        // Constructor
        Joystick();
        ~Joystick() = default;
        // METHODS
        void UpdateInputs(real inputX, real inputY);
        real OutLeft();
        real OutRight();
    };

    // Constructor
    template <typename real>
    Joystick<real>::Joystick()
    {
        j_ZERO = (real)0;
    }

    // Method update
    template <typename real>
    void Joystick<real>::UpdateInputs(real inputX, real inputY)
    {
        // Input values -1 <= X <= 1
        if (inputX >= -1 && inputX <= 1)
            j_inputX = inputX;
        // Input values -1 <= Y <= 1
        if (inputY >= -1 && inputY <= 1)
            j_inputY = inputY;

        // Private
        j_joystick();
    }

    // Method output
    template <typename real>
    real Joystick<real>::OutLeft()
    {
        return j_outputLeft;
    }

    // Method output
    template <typename real>
    real Joystick<real>::OutRight()
    {
        return j_outputRight;
    }

    // Private Method
    template <typename real>
    void Joystick<real>::j_joystick()
    {
        // Assume Noisy Analogs
        real const _tol = 0.04;

        // Input Values
        real const _inputX = j_inputX;
        real const _inputY = j_inputY;

        // Initialize x & y
        real _x = 0;
        real _y = 0;

        // Delta Equation
        real delta = ABS_REAL<float>(ABS_REAL<float>(_inputX) - ABS_REAL<float>(_inputY));

        // Consitionals
        if (ABS_REAL<float>(_inputX) > _tol && ABS_REAL<float>(_inputY) > _tol)
        {
            // Y-Dominator
            if (ABS_REAL<float>(_inputX) <= ABS_REAL<float>(_inputY))
            {
                if (_inputX > j_ZERO && _inputY > j_ZERO)
                {
                    _x = _inputY;
                    _y = delta;
                }
                else if (_inputX > j_ZERO && _inputY < j_ZERO)
                {
                    _x = -delta;
                    _y = _inputY;
                }
                else if (_inputX < j_ZERO && _inputY > j_ZERO)
                {
                    _x = delta;
                    _y = _inputY;
                }
                else if (_inputX < j_ZERO && _inputY < j_ZERO)
                {
                    _x = _inputY;
                    _y = -delta;
                }
            } // X-Dominator
            else if (ABS_REAL<float>(_inputX) > ABS_REAL<float>(_inputY))
            {
                if (_inputX > j_ZERO && _inputY > j_ZERO)
                {
                    _x = _inputX;
                    _y = -delta;
                }
                else if (_inputX > j_ZERO && _inputY < j_ZERO)
                {
                    _x = delta;
                    _y = -_inputX;
                }
                else if (_inputX < j_ZERO && _inputY > j_ZERO)
                {
                    _x = -delta;
                    _y = -_inputX;
                }
                else if (_inputX < j_ZERO && _inputY < j_ZERO)
                {
                    _x = _inputX;
                    _y = delta;
                }
            }
        }
        else if (ABS_REAL<float>(_inputX) > _tol && ABS_REAL<float>(_inputY) < _tol)
        {
            // Left & Right Turns
            _x = _inputX;
            _y = -_inputX;
        }
        else if (ABS_REAL<float>(_inputX) < _tol && ABS_REAL<float>(_inputY) > _tol)
        {
            // Forward & Backward
            _x = _inputY;
            _y = _inputY;
        }
        else if (ABS_REAL<float>(_inputX) < _tol && ABS_REAL<float>(_inputY) < _tol)
        {
            // Stop
            _x = 0;
            _y = 0;
        }

        j_outputLeft = _x;
        j_outputRight = _y;
    }
}

#endif
