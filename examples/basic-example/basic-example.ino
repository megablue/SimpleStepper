/**
  @example basic-example.ino
  @file basic-example.ino
  @author Evert Chin
  @brief Fast and Simple Stepper Driver
  
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
*/

//example of driving a nema 17 stepper motor with A4988
#include "SimpleStepper.h"

#define PIN_STEP 9             // stepper step pin
#define PIN_DIR 10             // stepper dir pin
#define MOTORSTEPS 3200        // 360/1.8 = 200 full steps * 16 microsteps = number of steps per revolution 
#define CLOCKWISE 1            // Rotation of the stepper motor, reverse if it is swapped
#define ANTICW 0               // Rotation of the stepper motor, reverse if it is swapped

SimpleStepper stepper(PIN_DIR, PIN_STEP);
uint8_t counter = 0;

void setup() {
  //initialize the object
  stepper.init();
}

void loop() {
  
  //once the stepper finished stepping to remaining ticks/steps
  if(stepper.isStopped()){

    //conter is even number
    if(counter % 2 == 0){
      //do a full rotation clockwise at 20rpm
      stepper.step(MOTORSTEPS, CLOCKWISE, rpmToTickInterval(20));
    } else {
      //do a full rotation clockwise at 10rpm
      stepper.step(MOTORSTEPS, ANTICW, rpmToTickInterval(10));
    }

    ++counter;
  }

  if(counter == 100){
    //stop whatever the stepper is doing
    stepper.stop();
  }
}

//rpm to stepper tick in micro seconds
long rpmToTickInterval(long targetRPM){
    // rotation per sec = targetRPM/60
    float stepsPerSecond = (float) targetRPM/60 * MOTORSTEPS;
    long pulseInMicroseconds = (long) (1000000L/stepsPerSecond) / 2;

    return pulseInMicroseconds;
}
