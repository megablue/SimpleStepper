/**
    @file SimpleStepper.cpp
    @author Evert Chin
    @brief Fast and Simple Stepper Driver

   * This file may be redistributed under the terms of the MIT license.
   * A copy of this license has been included with this distribution in the file LICENSE.
   */

#include "SimpleStepper.h"
#include "TimerOne.h"

SimpleStepper *SimpleStepper::firstInstance;

SimpleStepper::SimpleStepper(uint8_t dirpin, uint8_t steppin){
    if(!firstInstance){
      firstInstance = this;
    }

    this->dirPin = Pin(dirpin);
    this->stepPin = Pin(steppin);
}

void SimpleStepper::init(){
    dirPin.setOutput();
    stepPin.setOutput();
    Timer1.initialize();
    Timer1.attachInterrupt(SimpleStepper::ticking); 
    Timer1.stop();
    this->pause();
}

void SimpleStepper::setPulse(long pulse){
    Timer1.setPeriod(pulse);
}

bool SimpleStepper::step(long steps, uint8_t direction){
    if(this->isStepping()){
        return false;
    }

    this->ticksRemaining = steps * 2; //converting steps to ticks
    
    if(direction == HIGH){
      this->dirPin.setHigh();
    } else {
       this->dirPin.setLow();
    }

    return true;
}

bool SimpleStepper::step(long steps, uint8_t direction, long pulse){
    if(this->isStepping()){
        return false;
    }

    this->resume();
    this->setPulse(pulse);
 
    return  this->step(steps, direction);
}

long SimpleStepper::getRemainingSteps(){
    return ticksRemaining/2;
}

//returns the remaining steps
long SimpleStepper::stop(){
    //each step = 2 ticks
    long stepsRemaining = this->getRemainingSteps();

    Timer1.stop();

    if(ticksRemaining & 1){
        ticksRemaining = 1;
    } else{
        ticksRemaining = 0;
    }

    Timer1.start();

    return stepsRemaining;
}

void SimpleStepper::pause(){
  paused = true;
  Timer1.stop();
}

void SimpleStepper::resume(){
  if(paused){
    Timer1.start();
    paused = false;
  }
}

bool SimpleStepper::isStepping(){
    return (ticksRemaining > 0);
}

bool SimpleStepper::isStopped(){
    return (ticksRemaining <= 0);
}

bool SimpleStepper::isPaused(){
  return paused;
}

void SimpleStepper::ticking(){
    if(firstInstance->ticksRemaining > 0){
        //generate high/low signal for the stepper driver
        firstInstance->stepPin.toggleState();
        --firstInstance->ticksRemaining;
    }
}
