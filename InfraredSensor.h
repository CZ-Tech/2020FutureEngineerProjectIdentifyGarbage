// InfraredSensor.h

#ifndef _INFRAREDSENSOR_h
#define _INFRAREDSENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class Infrared
{
public:
	Infrared(int i);
	bool isBlocked();
private:
	int pin;
	bool IsBlocked;
};