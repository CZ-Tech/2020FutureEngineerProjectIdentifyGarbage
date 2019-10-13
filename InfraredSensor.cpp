// 
// 
// 

#include "InfraredSensor.h"

Infrared::Infrared(int i)
{
	pin = i;
	pinMode(i, INPUT);
}

bool Infrared::isBlocked()
{
	return IsBlocked=!digitalRead(pin);
}
