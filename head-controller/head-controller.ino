#include "imu.h"
#include "serialout.h"

#define LOOP_DELAY 10

imu main_imu;

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
//  main_imu.setup(7, 8, LOOP_DELAY);
}

void loop() {
  main_imu.angles();

  serialout(520);//main_imu.angle_z);
  serialout(328);//main_imu.angle_y);
  delay(1000);

//  Serial.print(main_imu.angle_z);
//  Serial.print(", ");
//  Serial.println(main_imu.angle_y);
//  delay(LOOP_DELAY);

  // String s = c;
  // int f = s.toInt() + 200;
  // Serial.println(f);
  // delay(10000);
}
