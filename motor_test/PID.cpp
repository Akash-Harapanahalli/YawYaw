#ifndef __PID_CPP__
#define __PID_CPP__

/**
 * PID.cpp
 * PID's are used for converting error into usable power output.
 * P - Proportion --> adding power as a proportion of the error
 * I - Integral   --> adding power as a proportion of the integral of error, leveling off any error present over longer periods of time.
 * D - Derivative --> removing power as a proportion of the derivative of error, preventing possible overshoots and restricting too large changes in error.
 */

#include "PID.h"
#include <Arduino.h>

PID::PID(){}

PID::PID(float _kP, float _kI, float _kD, int _dt){
    this->kP = _kP;
    this->kI = _kI;
    this->kD = _kD;
    this->dt = _dt;
}

void PID::setConstants(float _kP, float _kI, float _kD, int _dt){
    this->kP = _kP;
    this->kI = _kI;
    this->kD = _kD;
    this->dt = _dt;
}

// The PID's output lies in a range between -255 to 255 (dual 8-bit)
#define max_power 255

int PID::step(float error){
    // Riemann Sum
    integral += error * dt;

    // Slope Formula
    derivative = (error - prev_error) / dt;
    prev_error = error;

    // Adding the three terms
    int power = error * this->kP + this->integral * this->kI + this->derivative * this->kD;

    // Capping the power at max_power
    power = (power >  max_power) ?  max_power : power;
    power = (power < -max_power) ? -max_power : power;
    Serial.println(power);
    return power;
} 

#endif
