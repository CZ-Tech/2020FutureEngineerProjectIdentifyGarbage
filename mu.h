// mu.h

#ifndef _MU_h
#define _MU_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class mu
{
public:
	void initialize();
	void work();
	MuVisionType type;
	mu(MuVisionType customtype);
private:
	uint8_t err;
	int x, y, width, height;
};