#include "Arduino.h"
#include <Wire.h>
#include "Servo.h"
#include <SoftwareSerial.h>
#include <mu_vision_sensor_uart_interface.h>
#include <mu_vision_sensor_uart_hw_interface.h>
#include <mu_vision_sensor_type.h>
#include <mu_vision_sensor_interface.h>
#include <mu_vision_sensor_i2c_interface.h>
#include <mu_vision_sensor_i2c_hw_interface.h>
#include <MuVisionSensor.h>
#include "mu.h"
#include "SoundSensor.h"
#include "myServo.h"
#include "InfraredSensor.h"
#include "LED.h"
#include "Button.h"
#include "testmodel.h"


#define LED_RED  5
#define LED_GREEN 4
#define BUTTON 3
#define Beeper 2 //蜂鸣器
#define UltrasonicSensor A0 //超声波
#define InfraredSensor A1 //红外避障
#define Servopin 7		//舵机 (黄PMW，红Vcc，棕色接地)
#define SoundSensorpin A2

Console con;
Button btn(BUTTON);
LED redled(LED_RED);
LED greenled(LED_GREEN);
Infrared infrared(InfraredSensor);
myServo myservo(Servopin);
Servo mservo;
SoundSenor soundsenor(SoundSensorpin);
mu mymu(VISION_BODY_DETECT);
int angle=0;
int buttoncounter = 0;

void setup()
{
	//pinMode(53, INPUT);
	//Serial3.begin(9600);
	//pinMode(Beeper,OUTPUT);
	//mservo.attach(6);
	Serial.begin(115200);
	mymu.initialize();
}

void loop()
{

	mymu.work();
	//btn.buttonCounterDown(buttoncounter);
	//Serial.println(buttoncounter);
	//Serial.println(soundsenor.getvolume());
	//if(Serial3.available())
	//Serial3.println("Hello");
	//Serial.println(scaleTo(analogRead(A0),0,1023,0,100));
	//Serial.println(infrared.isBlocked());
	//myservo.testScan();
	//myservo.getservo().write(90);
	//for (int i = 0; i < 60; i++)
	//{
	//	myservo.getservo().write(myservo.getservo().read() + 3);
	//	delay(10);
	//}
	//for (int i = 0; i < 60; i++)
	//{
	//	myservo.getservo().write(myservo.getservo().read() - 3);
	//	delay(10);

	//}
	//for (int i = 0; i < 60; i++)
	//{
	//	mservo.write(angle=angle + 3);
	//	delay(10);
	//}
	//for (int i = 0; i < 60; i++)
	//{
	//	mservo.write(angle=angle - 3);
	//	delay(10);

	//}
	//mservo.write(180);
	//delay(1000);
	//mservo.write(90);
	//delay(1000);
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