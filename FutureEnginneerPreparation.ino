#include "myLCD.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include <Wire.h>
//#include "Servo.h"
#include <DFRobot_Servo.h>
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
//#include "myServo.h"
#include "InfraredSensor.h"
#include "LED.h"
#include "Button.h"


#define LED_RED  5
#define LED_GREEN 4
#define BUTTON 3
#define Beeper 2 //������
#define UltrasonicSensor A0 //������
#define InfraredSensor A1 //�������
#define Servopin 9		//��� (��PMW����Vcc����ɫ�ӵ�)
#define SoundSensorpin A2
#define VISION_TYPE VISION_BODY_DETECT;//VISION_TRAFFIC_CARD_DETECT 

Button btn(BUTTON);
LED redled(LED_RED);
LED greenled(LED_GREEN);
Infrared infrared(InfraredSensor);
//myServo myservo(Servopin);
Servo myservo;
SoundSenor soundsenor(SoundSensorpin);
myLCD mylcd;
//mu mymu(VISION_BODY_DETECT);
int pos=0;
int buttoncounter = 0;

void setup()
{
	//pinMode(53, INPUT);
	//Serial3.begin(9600);
	//pinMode(Beeper,OUTPUT);
	//mservo.attach(6);
	Serial.begin(115200);
	myservo.attach(Servopin);
	//mymu.initialize();
	mylcd.show(1);
	delay(1000);
	mylcd.clear();
	mylcd.show(2);
}

void loop()
{
	/*rotatoServoTo(180);
	rotatoServoTo(0);*/
	for (int i = 0; i < 60; i++)
	{
		pos += 3;
		myservo.angle(pos);
		delay(35);
	}	for (int i = 0; i < 60; i++)
	{
		pos -= 3;
		myservo.angle(pos);
		delay(25);
	}
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

//��һ����Χ�ڵ���ӳ�䵽��һ����Χ
int scaleTo(int original, int min1, int max1, int min2, int max2)
{
	return (double)(original - min1) / (max1 - min1) * (max2 - min2) + min2;
}
//void rotatoServoTo(Servo& mservo,int angle)
//{
//	int position=angle;
//	for (int i = 0; i < angle/3; i++)
//	{
//		position += 3;
//		mservo.angle(position);
//		delay(25);
//	}
//}