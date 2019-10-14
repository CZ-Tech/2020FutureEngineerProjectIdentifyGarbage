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
	int getTimes();
	void buttonCounterDown(int& counter);
	void buttonCounterPress(int& counter);
private:
	bool status;
	int pin;
	int counter=0;
	int laststatus=LOW;
	int nowstatus;	
};
