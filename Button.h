// Button.h

#ifndef _BUTTON_h
#define _BUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif
class Button
{
public:
	Button(int i);
	bool getStatus();
private:
	bool status;
	int pin;
};
