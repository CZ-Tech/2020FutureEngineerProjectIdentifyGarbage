// 
// 
// 

#include "myServo.h"

myServo::myServo(int i)
{
	pin = i;
	myservo.attach(i);
	
}

void myServo::rotateTo(int angle)
{
	//myservo.write()
	myservo.angle(angle);
}

void myServo::testScan()
{
	for (int i = 0; i < 60; i++)
	{
		pos += 3;
		myservo.angle(pos);
		delay(25);
	}
	for (int i = 0; i < 60; i++)
	{
		pos -= 3;
		myservo.angle(pos);
		delay(25);
	}
}

Servo myServo::getservo()
{
	return myservo;
}
