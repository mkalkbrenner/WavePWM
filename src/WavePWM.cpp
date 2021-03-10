/*
  WavePWM.cpp

  Calculate a sine wave, with the periodicity given as argument.

  Please see https://idyl.io for complete tutorial on how this works.

  This example code is licensed under CC BY 4.0.
  Please see https://creativecommons.org/licenses/by/4.0/

  Original code written 18 January 2017 by Tony Pottier

  Modified 9 Mar 2021 by Markus Kalkbrenner
    - use the class to only calculate the values and let the LED by driven by the calling code
    - merged modifications from 5 Mar 2020 by Brad Roy to alternatively change from a 'sine-esque' function
   	  to an exponential one which *looks* more linear
*/

#include "WavePWM.h"


//Apply the following function:
// f(x) = x^2 if x <= 1
// f(x) = -(x-2)^2 + 2 if 1 < x <= 3
// f(x) = (x-4)^2 otherwise
// this function is almost a perfect sine wave on the [0;4] range.
f7p9 WavePWM::quadraticWavef7p9(f7p9 x) {
  if (x <= inttof7p9(1)) {
    return mulf7p9(x, x);
  }
  else if (x <= inttof7p9(3)) {
    x -= inttof7p9(2);
    x = mulf7p9(x, x);
    x = inttof7p9(0) - x + inttof7p9(2);
    return x;
  }
  else {
    x -= inttof7p9(4);
    return mulf7p9(x, x);
  }
}

//Apply the following function:
// f(x) = x^2 if x <= 1
// f(x) = (x-4)^2 otherwise
// this function has a period of '2,' and returns a value from 0 to 1.
f7p9 WavePWM::exponentialWavef7p9(f7p9 x) {
  if (x <= inttof7p9(1)) {
	return mulf7p9(x, x);
  }
  else {
    x -= inttof7p9(2);
    return mulf7p9(x, x);
  }
}

void WavePWM::setup(const unsigned long waveDuration){
	this->waveLen = waveDuration;
	this->inverseWaveLen = floattouf16p16(1.0f / waveDuration);
}

uint8_t WavePWM::getQuadraticValue(const unsigned long milli){
	unsigned long mod = milli % this->waveLen;

	//transform to 0--1 range
    f7p9 value = muluf16p16(inttouf16p16(mod), this->inverseWaveLen);

	//convert to 0--4 range: multiply by 4 by shifting left twice
	value = value << 2;

	//apply wave
	value = quadraticWavef7p9(value);

	//convert to 0-255 range
	return (uint8_t) (((int32_t)value * floattof23p9(127.5f)) >> 18);
}

uint8_t WavePWM::getExponentialValue(const unsigned long milli){
	unsigned long mod = milli % this->waveLen;

	//transform to 0--1 range
    f7p9 value = muluf16p16(inttouf16p16(mod), this->inverseWaveLen);

	//convert to 0--4 range: multiply by 4 by shifting left twice
	value = value << 1;

	//apply wave
	value = exponentialWavef7p9(value);

	//convert to 0-255 range
    return (uint8_t) ((((int32_t)value * floattof23p9(249.0f)) >> 18)+6);
}
