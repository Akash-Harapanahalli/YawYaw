#include "imu.h"

#define LOOP_DELAY 10

imu main_imu;

void setup() {
  Serial.begin(115200);
  main_imu.setup(7, 8, LOOP_DELAY);
}

void loop() {
  main_imu.angles();
  Serial.print(main_imu.angle_z);
  Serial.print(", ");
  Serial.println(main_imu.angle_y);
  delay(LOOP_DELAY);
}
