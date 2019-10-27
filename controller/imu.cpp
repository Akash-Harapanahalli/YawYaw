#ifndef __IMU_CPP__
#define __IMU_CPP__

#include "imu.h"

/**
 * imu.cpp
 * SEE: imu.h
 */

/**
 * Sets up the new imu object with the M_CS and AG_CS pins specified.
 */

void imu::setup(int M_CS, int AG_CS, int _dt){
    // Sets up communications with the sensor over the SPI protocol.
    this->sensor.settings.device.commInterface = IMU_MODE_SPI;
    // NOTE: No need to setup MISO, MOSI, or SCK (clock) as they are default pins on the Teensy 4.0.

    // The M_CS pin selects SPI as the protocol to communicate over with the Magnetometer.
    this->sensor.settings.device.mAddress = M_CS;
    // The AG_CS pin selects SPI as the protocol to communicate over with the Accelerometer and Gyroscopes.
    this->sensor.settings.device.agAddress = AG_CS;

    // Setup the angles for accumulating later on.
    this->angle_y = this->angle_z = this->acc_gz = 0;

    this->dt = _dt;

    if(!this->sensor.begin()){
        Serial.print("The IMU is not connected properly!\nPlease check your connections.");
        while(1) delay(10);
    }
}

/**
   * Calculates heading (angle_y) using the gyroscope and a simple threshold filter.
   * Calculates tilt (angle_z) using both gyroscope and accelerometer data.
 */

void imu::angles(){
    // Updating the current sensor values for the gyroscopes and the accelerometers.
    this->sensor.readGyro();
    this->sensor.readAccel();

    // Read and adjusted to deg/s
    float calc_gy = this->sensor.calcGyro(this->sensor.gy);
    float calc_gz = this->sensor.calcGyro(this->sensor.gz);

    // Calculating the pitch using the accelerometers and a little bit of Linear Algebra :)
    // https://cache.freescale.com/files/sensors/doc/app_note/AN3461.pdf
    // In a nutshell, it compares the gravity vector (0, 0, 1) to the accelerometer vector.
    // It uses rotation matrices to find the relationship and the angles that would cause the change.
    // While this is not reliable in the short term, when added with the gyro's value, it can act as a filter and makes the long term value more precise.
    float pitch = atan2(-this->sensor.ax, sqrt(this->sensor.az * this->sensor.az + this->sensor.ay * this->sensor.ay));

    // Simple accumulation
    this->acc_gz += 1 * ((abs(calc_gz) > 10 ? calc_gz : 0) * this->dt / 1000);

    // Adding the accumulated angle with the pitch in the ratio indicated, acting as a filter for the gyroscope's angle (which is subject to drift over time).
    this->angle_z = 0.95 * acc_gz + 0.05 * pitch;

    // Unfortunately, no gravity filtering process is available for the heading, because its axis is completely orthogonal to the gravity vector.
    // Therefore a simple integrating process must be used, and any values less than the value indicated are filtered out manually (drift).
    this->angle_y += 1 * ((abs(calc_gy) > 10 ? calc_gy : 0) * this->dt / 1000);
}

#endif
