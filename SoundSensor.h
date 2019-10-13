// SoundSensor.h

#ifndef _SOUNDSENSOR_h
#define _SOUNDSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class SoundSenor
{
public:
	SoundSenor(int i);
	int volume;
	int getvolume();
private:
	int pin;
};