// 
// 
// 

#include "LED.h"

LED::LED(int i)
{
	pinMode(i, OUTPUT);
	pin = i;
}

void LED::light()
{
	digitalWrite(pin, HIGH);
	Islight = true;
}

void LED::off()
{
	digitalWrite(pin, LOW);
	Islight = false;
}

bool LED::islight()
{
	return Islight;
}
