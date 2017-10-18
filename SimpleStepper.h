/**
    @file SimpleStepper.h
    @author Evert Chin
    @brief Fast and Simple Stepper Driver
    
 * This file may be redistributed under the terms of the MIT license.
 * A copy of this license has been included with this distribution in the file LICENSE.
 */
#ifndef SIMPLE_STEPPER_BASE_H
#define SIMPLE_STEPPER_BASE_H
#include <Arduino.h>
#include "Pin.h"

/*
 * Simple Stepper class.
 */
class SimpleStepper {
public:
    volatile long ticksRemaining;   // remaining ticks, 2 ticks = 1 pulse = 1 microstep/step

protected:
    /* for some stupid reason the Pin class requires initialization */ 
    Pin dirPin = Pin(1000);
    Pin stepPin = dirPin;
    bool paused;
    
public:
    SimpleStepper(uint8_t dirpin, uint8_t steppin);
    void init();
    void setPulse(long pulse);
    bool step(long steps, uint8_t direction);
    bool step(long steps, uint8_t direction, long pulse);
    long stop();
    void pause();
    void resume();
    bool isStepping();
    bool isStopped();
    bool isPaused();
    static void ticking();
    
private:
    static SimpleStepper *firstInstance;
};
#endif // SIMPLE_STEPPER_BASE_H
