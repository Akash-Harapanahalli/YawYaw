#ifndef __IMU_H__
#define __IMU_H__

/**
 * imu.hpp
 * This header creates the imu class to handle all calls to the 
 * The IMU used for this project is the LSM9DS1 from sparkfun. Refer to their data sheet for more information.
 */

#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

class imu {
private:
    // The SparkFunLSM9DS1 API is in use.
    LSM9DS1 sensor;

    // Need a non-temporary storage container to hold the accumulated gyro values.
    float acc_gy;

    int dt;

public:
    float angle_y, angle_z;

    /**
     * Sets up the new imu object with the M_CS and AG_CS pins specified.
     */
    void setup(int _M_CS, int _AG_CS, int _dt);
    
    /**
     * Calculates heading (angle_x) using the gyroscope and a simple threshold filter.
     * Calculates tilt (angle_y) using both gyroscope and accelerometer data.
     */
    void angles();
};

#endif
