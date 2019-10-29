#include "PID.h"
#include "MotorDriver.h"

bool firsttime = true;
MotorDriver cameraTilt;

void setup() {
  cameraTilt.setup(9, 10, (float) 0, (float) 0.0, (float) 0.0, 10);
}

void loop() {
//  if(firsttime = true){
//    firsttime = false;
//    cameraTilt.setPower(127);
//    delay(200);
//    cameraTilt.setPower(0);
//    delay(200);
//    cameraTilt.setPower(-127);
//    delay(200);
//    cameraTilt.setPower(0);
//    
//  }
  cameraTile.setPower(0);
  delay(1000);
}
