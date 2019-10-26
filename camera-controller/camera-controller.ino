#include "PID.h"
#include "MotorDriver.h"

MotorDriver cameraTilt;

void setup() {
  cameraTilt.setup(1, 2, (float) 0, (float) 0.0, (float) 0.0, 10);
}

void loop() {
  // READ SENSOR VALUES HERE AND PASS THEM INTO THE STEP FUNCTION.

  cameraTilt.setPower(255);
  delay(10);
}
