// myServo.h
#include "Servo.h"
#ifndef _MYSERVO_h
#define _MYSERVO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


#endif

class myServo:Servo
{
public:
	myServo(int i);
	void rotateTo(int angle);
	void testScan();
	Servo myservo;
	Servo getservo();
private:
	int pin;

};