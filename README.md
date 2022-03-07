# WavePWM

Calculates PWM values according to a sine wave, with the periodicity given as argument.

The pins output used for these must be PWM pins.

Please see https://idyl.io/arduino/quadratic-wave-led/ for complete tutorial on how this works.
  
This example code is licensed under CC BY 4.0.
Please see https://creativecommons.org/licenses/by/4.0/

Original code written 18 January 2017 by Tony Pottier

Modified 9 Mar 2021 by Markus Kalkbrenner:
- use the class to only calculate the values and let the LED be driven by the calling code
- merged modifications from 5 Mar 2020 by Brad Roy to alternatively change from a 'sine-esque' function
to an exponential one which *looks* more linear
