#ifndef __PID_H__
#define __PID_H__

/**
 * PID.h
 * PID's are used for converting error into usable power output.
 * P - Proportion --> adding power as a proportion of the error
 * I - Integral   --> adding power as a proportion of the integral of error, leveling off any error present over longer periods of time.
 * D - Derivative --> removing power as a proportion of the derivative of error, preventing possible overshoots and restricting too large changes in error.
 */

class PID {
private:
    float kP, kI, kD;
    int dt;
    float integral;
    float derivative, prev_error;

public:
    /**
     * The constructor defines the PID constants and tells the PID how long the loop is that it is called in.
     */
    PID();
    PID(float _kP, float _kI, float _kD, int _dt);

    void setConstants(float _kP, float _kI, float _kD, int _dt);

    /**
     * The step function is an instantaneous step that calculates and returns a new power value.
     * This needs to be called within a closed loop where the parameter error is constantly updated.
     * PID output is in the range from -255 to 255 (dual 8-bit).
     */
    int step(float error);
};



#endif
