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
}

void myServo::testScan()
{
	for (int i = 0; i < 60; i++)
	{
		myservo.write(myservo.read() + 3);
		delay(10);
	}
	for (int i = 0; i < 60; i++)
	{
		myservo.write(myservo.read() - 3);
		delay(10);
			
	}
}

Servo myServo::getservo()
{
	return myservo;
}
