#include "PID.h"
#include "MotorDriver.h"

MotorDriver cameraTilt;

void setup() {
  cameraTilt.setup(9, 10, (float) 0.3, (float) 0.0, (float) 0.0, 10);
}

void loop() {
  // READ SENSOR VALUES HERE AND PASS THEM INTO THE STEP FUNCTION.

  cameraTilt.setPower(127);

  delay(10);
}
