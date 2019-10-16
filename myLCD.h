// myLCD.h

#ifndef _MYLCD_h
#define _MYLCD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#include <LiquidCrystal.h>
#else
	#include "WProgram.h"
#endif

class myLCD
{
public:
	myLCD();
	void show(int i);
	void clear();
private:
	int currentNum;
};
#endif

