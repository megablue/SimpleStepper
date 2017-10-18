**Simple Stepper Library for Arduino**
--------------------------------------------------------------------------------

  A bare minimum but really fast and simple stepper library. It relies on Timer1 interrupts and direct port manipulations via Pin library to produce extremely smooth stepping signal. It supports changing the tick rate of the stepper signals to drive the motor faster or slower. It doesn't support acceleration or deceleration control. The usage is very straight forward, basically you just need to provide the STEP and DIR pin numbers, steps, direction and tick rate. The rest of the "API" is pretty much self-explanatory. Base on the author tests on an Arduino Nano 3.0, it is able to drive a 1.8 degree Nema 17 motor with 1/128 microsteps with reasonable speed with still have processing power left for the rest of your code. 

**Installation**
--------------------------------------------------------------------------------

  To install this library, just place this entire folder as a subfolder in your
Arduino/lib/targets/libraries folder.

