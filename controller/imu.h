#ifndef __IMU_H__
#define __IMU_H__

/**
 * imu.hpp
 * This header creates the imu class that wraps all future calls to the SparkFunLSM9DS1 API.
 * The IMU used for this project is the LSM9DS1 from sparkfun. Refer to their data sheet for more information.
 * While this is specifically built for use in this project, it can easily be scaled to work in other settings.
 * 
 * The IMU plugs the magnetometer and the accelerometer/gyroscope into the MISO pin on the Teensy.
 * It plugs into the MOSI pin on the Teensy, as well as the CLK pin.
 * Finally, it plugs the M_CS into a digital port and the AG_CS into another digital port.
 */

#include <Wire.h>
#include <SPI.h>
#include <SparkFunLSM9DS1.h>

class imu {
private:
    // The SparkFunLSM9DS1 API is in use.
    LSM9DS1 sensor;

    // Need a non-temporary storage container to hold the accumulated gyro values.
    float acc_gz;

    int dt;

public:
    float angle_y, angle_z;

    /**
     * Sets up the new imu object with the M_CS and AG_CS pins specified.
     */
    void setup(int _M_CS, int _AG_CS, int _dt);
    
    /**
     * Calculates heading (angle_y) using the gyroscope and a simple threshold filter.
     * Calculates tilt (angle_z) using both gyroscope and accelerometer data.
     */
    void angles();
};

#endif
