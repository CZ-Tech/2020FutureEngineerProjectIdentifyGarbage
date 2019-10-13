// LED.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class LED
{
public:
	LED(int i);
	void light();
private:
	int pin;
};