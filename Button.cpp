// 
// 
// 

#include "Button.h"

Button::Button(int i)
{
	pin = i;
	pinMode(i, INPUT);
}

bool Button::getStatus()
{
	return digitalRead(pin);
}

int Button::getTimes()
{
	return counter;
}

void Button::buttonCounterDown(int& counter)
{
	if (digitalRead(pin) != laststatus)
	{
		delay(50);//elimate the effect of unstable electronic level of bouncing switch ���˵���ʽ���صĵ�·����
		if (digitalRead(pin)==HIGH)
		{
			laststatus = HIGH;
			counter++;
		}
		if (digitalRead(pin) == LOW)
		{
			laststatus = LOW;
		}
	}
}

void Button::buttonCounterPress(int& counter)
{
	if (digitalRead(pin) != laststatus)
	{
		delay(50);//elimate the effect of unstable electronic level of bouncing switch ���˵���ʽ���صĵ�·����
		if (digitalRead(pin) == HIGH)
		{
			laststatus = HIGH;
		}
		if (digitalRead(pin) == LOW)
		{
			counter++;
			laststatus = LOW;
		}
	}
}
