/**
 * controller.ino
 * TARGET: Teensy 4.0
 * This is the main program to handle the funcitonality of YawYaw.
 */

#include "imu.h"
#include "MotorDriver.h"
#include <AccelStepper.h>
#define HALFSTEP 8

#define LOOP_DELAY 10

imu main_imu;

MotorDriver cameraTilt;
// MotorDriver cameraPan;
AccelStepper cameraPan(HALFSTEP, 5, 9, 6, 10);

#define cameraTiltPot A0
#define cameraPanPot  A1

#define resetButton 0
#define stepForward 3
#define stepBackward 4

void setup() {
  Serial.begin(115200);

  main_imu.setup(7, 8, LOOP_DELAY);

  cameraTilt.setup(1, 2, (float) 10.0, (float) 0.0, (float) 0.0, LOOP_DELAY);
  // cameraPan .setup(4, 3, (float) 10.0, (float) 0.0, (float) 0.0, LOOP_DELAY);
  cameraPan.setMaxSpeed(1800.0);
  cameraPan.setAcceleration(100000.0);
  cameraPan.setSpeed(1800.0);

  pinMode(resetButton, INPUT);
  pinMode(stepForward, INPUT);
  pinMode(stepBackward, INPUT);
}

void loop() {
  main_imu.angles();

  if(digitalRead(resetButton) == HIGH){
    main_imu.angle_y = 0;
    main_imu.angle_z = 0;
    cameraPan.moveTo(main_imu.angle_y * (1024.0 / 90.0));
    while(cameraPan.distanceToGo() != 0){
      cameraPan.run();
    }
  }

  int camTilt = analogRead(cameraTiltPot);
  int camPan = analogRead(cameraPanPot);

  cameraTilt.step( main_imu.angle_z - (270.0 / 1024.0) * (camTilt - 800) );
//  cameraPan .step( main_imu.angle_y - (270.0 / 1024.0) * (camPan - 512) );
  cameraPan.moveTo(main_imu.angle_y * (1024.0 / 90.0));

//  if(digitalRead(stepForward) == HIGH || digitalRead(stepBackward) == HIGH){
//    cameraPan.setSpeed(250.0);
//    while(1){
//      if(digitalRead(stepForward) == HIGH)
//        cameraPan.moveTo(cameraPan.currentPosition() + 50);
//      else if(digitalRead(stepBackward) == HIGH)
//        cameraPan.moveTo(cameraPan.currentPosition() - 50);
//      delay(LOOP_DELAY);
//    }
//  }
  for(int i = 0; i < LOOP_DELAY; i++){
    cameraPan.run();
    delay(1);
  }
}
