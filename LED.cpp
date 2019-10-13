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
}
