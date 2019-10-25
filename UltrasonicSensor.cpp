#include "UltrasonicSensor.h"

SuperSoundSenor::SuperSoundSenor(int i)
{
	pin = i;
}

int SuperSoundSenor::sssdistance()
{
	return scaleTo(analogRead(pin), 0, 1023, 0, 100);
}
