// 
// 
// 

#include "Button.h"

Button::Button(int i)
{
	pin = i;
	pinMode(i, INPUT);
}

bool Button::getStatus()
{
	return digitalRead(pin);
}
