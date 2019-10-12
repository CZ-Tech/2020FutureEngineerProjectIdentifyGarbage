// 
// 
// 

#include "testmodel.h"
#include "Arduino.h"

Console::Console()
{
}


void Console::show()
{
	for (size_t i = 0; i < 11; i++)
	{
		Serial.print(i);
		delay(1000);
	}
}

