#include "UltrasonicSensor.h"//ok
#include "myLCD.h"
#include "Arduino.h"//basic h
#include <LiquidCrystal.h>//lcd basic
#include <Wire.h>//i2c basic
#include <DFRobot_Servo.h>//servo revised
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
#define vision_type VISION_COLOR_DETECT
//VISION_TRAFFIC_CARD_DETECT		VISION_COLOR_DETECT(ֻ��ʶ��һ����ɫ)  VISION_COLOR_RECOGNITION


//#define I2C_MODE
#define SERIAL_MODE
#define MU_ADDRESS    0x60

int right = 0;
int left = 180;
int forward = 90;
#pragma region ���������� 
Servo servo;
SoundSenor soundsenor(SoundSensorpin);
SuperSoundSenor sss(UltrasonicSensor);
myLCD lcd;
LED ledg(14);
LED ledb(15);
Infrared infrared(InfraredSensor);
Button btnWhite(41);
MuVisionSensor Mu(MU_ADDRESS);
#pragma endregion
int times = 0;
int btnCounter = 0;
int btnCounter2 = 0;
bool isBlocked;
bool ledgStat;
bool ledbStat;
enum color
{
	red,green,yellow,white,black,blue
};

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
#pragma region ��ʼ�����
	while (!servo.attached()) { servo.attach(Servopin); }
	Serial.println("Servo initialized");
#pragma endregion


	delay(100);
	//while (!= MU_OK) {delay(20);};
#pragma region ����MU
	while (Mu.SensorSetDefault() != MU_OK) { delay(20); };//�����趨
	while (Mu.CameraSetAwb(kAutoWhiteBalance) != MU_OK) { delay(20); };//�Զ���ƽ��
	while (Mu.LedSetColor(kLed1, kLedWhite, kLedWhite, 7) != MU_OK) { delay(20); };
	Mu.LedSetColor(kLed2, kLedBlue, kLedClose, 7);
	//��ͬģʽ
	switch (vision_type)
	{
	case VISION_COLOR_RECOGNITION:
		initColorReg();
		break;
	case VISION_COLOR_DETECT:
		initColorDetect(red);
		break;
	default:
		break;
	}
#pragma endregion

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
	colorDetect();
	Serial.print(++btnCounter);
	delay(100);
}
void initColorReg()
{
	Mu.VisionBegin(VISION_COLOR_RECOGNITION);
	Mu.write(VISION_COLOR_RECOGNITION, kXValue, 50);
	Mu.write(VISION_COLOR_RECOGNITION, kYValue, 50);
	Mu.write(VISION_COLOR_RECOGNITION, kWidthValue, 5);
	Mu.write(VISION_COLOR_RECOGNITION, kHeightValue, 5);
}
void initColorDetect(int color)
{	
	Mu.VisionBegin(VISION_COLOR_DETECT);
	int temp = 0;
	switch (color)
	{
	case blue:
		Mu.write(vision_type, kLabel, MU_COLOR_BLUE);
		break;
	case red:
		Mu.write(vision_type, kLabel, MU_COLOR_RED);
		break;
	case yellow:
		Mu.write(vision_type, kLabel, MU_COLOR_YELLOW);
		break;
	case green:
		Mu.write(vision_type, kLabel, MU_COLOR_GREEN);
		break;
	case white:
		Mu.write(vision_type, kLabel, MU_COLOR_WHITE);
		break;
	case black:
		Mu.write(vision_type, kLabel, MU_COLOR_BLACK);
		break;
	default:
		Serial.println("ColorParInputError!!");
		break;
	}
}
void waitForTarget()
{
	Serial.println("Waiting");
	while (!Mu.GetValue(vision_type, kStatus))
	{
	}
}
void colorRecongnize()
{
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
}
void colorDetect()
{
		Serial.print("ColorFind!!");
	
	Serial.println(++btnCounter);
}
void FindHuman()
{
	Mu.VisionBegin(VISION_BODY_DETECT);
	Mu.LedSetColor(kLed1, kLedRed, kLedWhite, 1);
	Mu.LedSetColor(kLed2, kLedRed, kLedWhite, 1);

}

//��һ����Χ�ڵ���ӳ�䵽��һ����Χ
int scaleTo(int original, int min1, int max1, int min2, int max2)
{
	return (double)(original - min1) / (max1 - min1) * (max2 - min2) + min2;
}
int scale(int input,int min, int max)
{
	scaleTo(input,0, 1023, min,max);
}


