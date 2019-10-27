/**
 * controller.ino
 * TARGET: Teensy 4.0
 * This is the main program to handle the funcitonality of YawYaw.
 */

#include "imu.h"
#include "MotorDriver.h"

#define LOOP_DELAY 10

imu main_imu;

MotorDriver cameraTilt;
MotorDriver cameraPan;

#define cameraTiltPot A0
#define cameraPanPot  A1

#define resetButton 0

void setup() {
  Serial.begin(115200);

  main_imu.setup(7, 8, LOOP_DELAY);

  cameraTilt.setup(1, 2, (float) 10.0, (float) 0.0, (float) 0.0, LOOP_DELAY);
  cameraPan .setup(4, 3, (float) 10.0, (float) 0.0, (float) 0.0, LOOP_DELAY);

  pinMode(resetButton, INPUT);
}

void loop() {
  main_imu.angles();

  if(digitalRead(resetButton) == HIGH){
    main_imu.angle_y = 0;
    main_imu.angle_z = 0;
  }

  int camTilt = analogRead(cameraTiltPot);
  int camPan = analogRead(cameraPanPot);

  cameraTilt.step( main_imu.angle_z - (270.0 / 1024.0) * (camTilt - 800) );
  cameraPan .step( main_imu.angle_y - (270.0 / 1024.0) * (camPan - 512) );

  delay(LOOP_DELAY);
}
