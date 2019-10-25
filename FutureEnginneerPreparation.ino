#include <SoftwareSerial.h>
#include "UltrasonicSensor.h"//ok
#include "myLCD.h"
#include "Arduino.h"
#include <LiquidCrystal.h>
#include <Wire.h>
#include <DFRobot_Servo.h>
#include <mu_vision_sensor_uart_interface.h>
#include <mu_vision_sensor_uart_hw_interface.h>
#include <mu_vision_sensor_type.h>
#include <mu_vision_sensor_interface.h>
#include <mu_vision_sensor_i2c_interface.h>
#include <mu_vision_sensor_i2c_hw_interface.h>
#include <MuVisionSensor.h>
#include "SoundSensor.h"//ok
#include "InfraredSensor.h" //OK
#include "LED.h" //OK
#include "Button.h" //OK


#define LED_RED  5
#define LED_GREEN 4
#define BUTTON 3
#define Beeper 2 //������
#define UltrasonicSensor A7 //������
#define InfraredSensor 28 //������� ��ɫ�ź� ���ִ�����
#define Servopin 2		//��� (��PMW����Vcc����ɫ�ӵ�) �߳�ǰ
#define SoundSensorpin A6   //����������
#define VISION_TYPE VISION_COLOR_RECOGNITION//VISION_TRAFFIC_CARD_DETECT 
#define Findcolor
//#define I2C_MODE
#define SERIAL_MODE
#define MU_ADDRESS    0x60

int right = 0;
int left = 180;
int forward = 90;

Servo servo;
SoundSenor soundsenor(SoundSensorpin);
SuperSoundSenor sss(UltrasonicSensor);
myLCD lcd;
//mu mymu(VISION_COLOR_DETECT);
//int pos=0;
LED ledg(14);
LED ledb(15);
Infrared infrared(InfraredSensor);
Button btnWhite(41);
SoftwareSerial myserial(21, 20);
MuVisionSensor Mu(MU_ADDRESS);
int times = 0;
int btnCounter = 0;
int btnCounter2 = 0;
bool isBlocked;
bool ledgStat;
bool ledbStat;

void setup()
{
	Serial.begin(115200);
	Serial3.begin(9600);
#pragma region ��ʼ��MU�Ӿ�������
	IniMU :
	uint8_t err = MU_ERROR_FAIL;
#ifdef I2C_MODE
	Wire.begin();
	err = Mu.begin(&Wire);
	if (err == MU_OK) {
		Serial.println("MU initialized.");
	}
	else {
		Serial.println("MU initializing failed.");
		goto IniMU;
	}
#elif defined SERIAL_MODE
	//myserial.begin(9600);
	// initialized MU on the soft serial port
	err = Mu.begin(&Serial3);
#endif // I2c
	if (err == MU_OK) {
		Serial.println("MU initialized.");
	}
	else {
		Serial.println("MU initializing failed.");
		goto IniMU;
	}

#pragma endregion

	while (!servo.attached()) { servo.attach(Servopin); }
	Serial.println("Servo initialized");
	delay(100);
	//while (!= MU_OK) {delay(20);};
	while (Mu.SensorSetDefault() != MU_OK) { delay(20); };
	while (Mu.CameraSetAwb(kAutoWhiteBalance) != MU_OK) { delay(20); };

	Mu.VisionBegin(VISION_COLOR_RECOGNITION);
	while (Mu.LedSetColor(kLed1, kLedWhite, kLedWhite, 1) != MU_OK) { delay(20); };
	Mu.LedSetColor(kLed2, kLedBlue, kLedClose, 1);
	Mu.write(VISION_COLOR_RECOGNITION, kXValue, 50);                  // set detect region center x value(0~100)
	Mu.write(VISION_COLOR_RECOGNITION, kYValue, 50);                  // set detect region center y value(0~100)
	Mu.write(VISION_COLOR_RECOGNITION, kWidthValue, 5);               // set detect region center width value(0~100)
	Mu.write(VISION_COLOR_RECOGNITION, kHeightValue, 5);

}

void loop()
{
#pragma region ���´�������Ϣ																
	isBlocked = infrared.isBlocked();
	ledgStat = ledg.islight();
	ledbStat = ledb.islight();
	btnWhite.buttonCounterPress(btnCounter);
#pragma endregion
	//Serial.println(sss.sssdistance());
	/*waitForHuman();*/
	waitForTarget();
	switch (Mu.GetValue(VISION_COLOR_RECOGNITION, kLabel))
	{
	case MU_COLOR_BLACK:
		Serial.println("black");
		break;
	case MU_COLOR_CYAN:
	case MU_COLOR_BLUE:
		Serial.println("blue");
		break;
	case MU_COLOR_GREEN:
		Serial.println("green");
		break;
	case MU_COLOR_PURPLE:
		Serial.println("purple");
		break;
	case MU_COLOR_RED:
		Serial.println("red");
		break;
	case MU_COLOR_WHITE:
		Serial.println("white");
		break;
	case MU_COLOR_YELLOW:
		Serial.println("yellow");
		break;
	default:
		Serial.print("unknow color type: ");
		Serial.println(Mu.GetValue(VISION_COLOR_RECOGNITION, kLabel));
		break;
	}
	Serial.print(++btnCounter);
	delay(100);
}
void FindColor()
{
	Mu.LedSetColor(kLed1, kLedWhite, kLedWhite, 1);
	Mu.LedSetColor(kLed2, kLedBlue, kLedClose, 1);
	Mu.VisionBegin(VISION_COLOR_DETECT);
	Mu.write(VISION_COLOR_DETECT, kLabel, MU_COLOR_BLUE);
}
void waitForTarget()
{
	Serial.println("Waiting");
	while (!Mu.GetValue(VISION_TYPE, kStatus))
	{
	}
}
void FindHuman()
{
	Mu.VisionBegin(VISION_BODY_DETECT);
	Mu.LedSetColor(kLed1, kLedRed, kLedWhite, 1);
	Mu.LedSetColor(kLed2, kLedRed, kLedWhite, 1);

}
void waitForHuman()
{
	Serial.println("Waiting");
	while (!Mu.GetValue(VISION_BODY_DETECT, kStatus))
	{
	}
}
//��һ����Χ�ڵ���ӳ�䵽��һ����Χ
int scaleTo(int original, int min1, int max1, int min2, int max2)
{
	return (double)(original - min1) / (max1 - min1) * (max2 - min2) + min2;
}


