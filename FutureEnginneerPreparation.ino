#include "InfraredSensor.h"
#include "LED.h"
#include "Button.h"
#include <SoftwareSerial.h>
#include "testmodel.h"
#include "Servo.h"

#define LED_RED  5
#define LED_GREEN 4
#define BUTTON 3
#define Beeper 2 //蜂鸣器
#define UltrasonicSensor A0 //超声波
#define InfraredSensor A1 //红外避障

Console con;
Button btn(BUTTON);
LED redled(LED_RED);
LED greenled(LED_GREEN);
Infrared infrared(InfraredSensor);

void setup()
{
	//pinMode(53, INPUT);
	Serial.begin(115200);
	pinMode(Beeper,OUTPUT);
}

void loop()
{
	//Serial.println(scaleTo(analogRead(A0),0,1023,0,100));
	Serial.println(infrared.isBlocked());
}

void ipinMode2(int a, int b)
{
	pinMode(a, INPUT);
	pinMode(b, INPUT);
}
void ipinMode3(int a, int b,int c)
{
	pinMode(a, INPUT);
	pinMode(b, INPUT);
	pinMode(c, INPUT);
}
void ipinMode4(int a, int b, int c,int d)
{
	pinMode(a, INPUT);
	pinMode(b, INPUT);
	pinMode(c, INPUT);
	pinMode(d, INPUT);
}
//将一个范围内的数映射到另一个范围
int scaleTo(int original, int min1, int max1, int min2, int max2)
{
	return (double)(original - min1) / (max1 - min1) * (max2 - min2) + min2;
}