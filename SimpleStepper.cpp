/**
    @file SimpleStepper.cpp
    @author Evert Chin
    @brief Fast and Simple Stepper Driver
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

void SimpleStepper::setPulse(long pul){
    if(this->pulse != pul){
        this->pulse = pul;
        Timer1.setPeriod(pul);
    }
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

    this->dirPin.getState();

    if(this->dirPin != direction){
        halt = true;
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

//returns the remaining steps
long SimpleStepper::stop(){
    //each step = 2 ticks
    long stepsRemaining = ticksRemaining/2;

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
