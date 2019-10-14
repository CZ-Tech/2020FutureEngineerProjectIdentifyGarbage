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
	void work(MuVisionType customtype);
	MuVisionType globalType;
	mu(MuVisionType customtype);
	int FPS();
	//��ǰ����type���ʺϵ�һ����
	int x, y, width, height;
private:
	uint8_t err;
};