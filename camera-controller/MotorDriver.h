#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__

/**
 * MotorDriver.h
 * A wrapper to work with the DRV8871 Motor Driver.
 */

#include "PID.h"

class MotorDriver {
private:
    /**
     * The two leads that take input signal to power the motor.
     */
    int in1;
    int in2;
    PID pid;

public:
    /**
     * Sets up the digital out pins and the PID if specified.
     */
    void setup(int _in1, int _in2);
    void setup(int _in1, int _in2, float _kP, float _kI, float _kD, int _dt);

    /**
     * Power is taken in the range from -255 to 255 (dual 8-bit)
     */
    void setPower(int power);

    /**
     * Steps the internal PID and powers the motor.
     */
    void step(float error);
};

#endif
