#include <SoftwareSerial.h>
#include "testmodel.h"
#include "Servo.h"
Console con;
void setup()
{
	Serial.begin(115200);
	pinMode(53, INPUT);
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
	
	//con.show();
	Serial.println(digitalRead(53));
	if (digitalRead(53))
	{
		digitalWrite(LED_BUILTIN, HIGH);
	}
	else {
		digitalWrite(LED_BUILTIN, LOW);
	}
}
