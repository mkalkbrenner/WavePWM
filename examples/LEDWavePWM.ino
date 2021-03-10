/*
  LEDWavePWM.ino

  Pulses a LED according to a sine wave, with the periodicity given as argument.

  The pins output used for these must be PWM pins.

  Please see https://idyl.io for complete tutorial on how this works.

  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  Original code written and modified 20 January 2017 by Tony Pottier

  Modified 9 Mar 2021 by Markus Kalkbrenner
    - use the class to only calculate the values and let the LED by driven by the calling code
    - merged modifications from 5 Mar 2020 by Brad Roy to alternatively change from a 'sine-esque' function
   	  to an exponential one which *looks* more linear
*/

#include "WavePWM.h"

WavePWM wavePWM;
const int LED_PIN = 11;     //11 is a PWM pin on the Arduino Uno. Change to whichever pin you wish to use.
const unsigned long WAVE_LEN = 2000UL;  //in milliseconds. This wave will last 2 seconds.

unsigned long milli = 0UL;

void setup() {
    pinMode(LED_PIN, OUTPUT);
    wavePWM.setup(WAVE_LEN);
}

void loop() {
    milli = millis();
    //write to LED
    analogWrite(LED_PIN, wavePWM.getQuadraticValue(milli);
}
