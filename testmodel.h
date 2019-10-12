// testmodel.h

#ifndef _TESTMODEL_h
#define _TESTMODEL_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class Console
{
public:
	Console();
	void show();
};