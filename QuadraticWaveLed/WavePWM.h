/*
  WavePWM.h

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

#include <stdint.h>
#include <Arduino.h>

typedef int16_t f7p9;
typedef uint32_t uf16p16;

//signed 7 bit integer / 9 bit decimal
#define inttof7p9(n)          ((n) << 9)
#define f7p9toint(n)          ((n) >> 9)
#define floattof7p9(n)        ((int16_t)((n) * (1 << 9))) 
#define f7p9tofloat(n)        (((float)(n)) / (float)(1<<9))

//signed 23 bit integer / 9 bit decimal
#define floattof23p9(n)     ((int32_t)((n) * ((int32_t)1 << 9))) 
#define f23p9tofloat(n)     (((float)(n)) / (float)(1<<9))

//unsigned 16 bit integer / 16 bit decimal
#define floattouf16p16(n)        ((uf16p16)((n) * ((uf16p16)1 << 16))) 
#define inttouf16p16(n)          (((uf16p16)n) << 16)
#define uf16p16tofloat(n)        (((float)(n)) / (float)((uf16p16)1<<16))


//return a f7p9 of a multiplication of two f16p16. If the number doesn't fit it will be truncated
static inline f7p9 muluf16p16(uf16p16 a, uf16p16 b) {
	return  (f7p9)(((uf16p16)a * (uf16p16)b) >> (16+7));
}

//Simple multiplication of two f7p9 terms. Operation is done on 32 bits to avoid overflow.
static inline f7p9 mulf7p9(f7p9 a, f7p9 b){
	return  (f7p9)  (  (( (int32_t)a * (int32_t)b) >> 9) );
}

class WavePWM{
	private:
	f7p9 quadraticWavef7p9(f7p9 x);
    f7p9 exponentialWavef7p9(f7p9 x);
	unsigned long waveLen;
	uf16p16 inverseWaveLen;
	
	public:
	void setup(const unsigned long waveDuration);
    uint8_t getQuadraticValue(const unsigned long milli);
    uint8_t getExponentialValue(const unsigned long milli);
};

