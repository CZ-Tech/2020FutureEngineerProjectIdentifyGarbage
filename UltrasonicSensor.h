// UltrasonicSensor.h

#ifndef _ULTRASONICSENSOR_h
#define _ULTRASONICSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SuperSoundSenor {
private:
	int distance;
	int pin;
	int scaleTo(int original, int min1, int max1, int min2, int max2)
	{
		return (double)(original - min1) / (max1 - min1) * (max2 - min2) + min2;
	}
public:
	SuperSoundSenor(int i);
	int sssdistance();
};
#endif

