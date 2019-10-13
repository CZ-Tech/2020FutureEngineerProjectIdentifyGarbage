// 
// 
// 

#include "SoundSensor.h"

SoundSenor::SoundSenor(int i)
{
	pin = i;
	
}

int SoundSenor::getvolume()
{
	return volume=analogRead(pin);
}
