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
#define Beeper 27 //蜂鸣器
#define UltrasonicSensor A7 //超声波
#define InfraredSensor 28 //红外避障 黑色信号 数字传感器
#define Servopin 2		//舵机 (黄PMW，红Vcc，棕色接地) 线朝前
#define SoundSensorpin A6   //音量传感器
#define vision_type VISION_COLOR_RECOGNITION
//VISION_TRAFFIC_CARD_DETECT		VISION_COLOR_DETECT(只能识别一种颜色)  VISION_COLOR_RECOGNITION


//#define I2C_MODE
#define SERIAL_MODE
#define MU_ADDRESS    0x60

#pragma region 舵机角度预定义区
int right = 0;
int left = 180;
int forward = 90;
#pragma endregion
#pragma region 对象声明区 
Servo servo;
SoundSenor soundsenor(SoundSensorpin);
SuperSoundSenor sss(UltrasonicSensor);
myLCD lcd;
LED ledg(14);
LED ledb(15);
Infrared infrared(InfraredSensor);
Button btnone(40);
Button btntwo(39);
Button btnthree(38);
Button btnconfirm(37);

MuVisionSensor Mu(MU_ADDRESS);
#pragma endregion
int times = 0;
int btnCounter1 = 0;
int btnCounter2 = 0;
int btnCounter3 = 0;
int lastBtn1 = 0;
int lastBtn2 = 0;
int lastBtn3 = 0;


bool isBlocked;
bool ledgStat;
bool ledbStat;
bool oneflag = false;
bool threeflag = false;
bool twoflag = false;
bool isConfirmed = false;
int que[10] = { 0,0,0,0,0,0,0,0,0,0 };
int quee = 0;

enum color
{
	red, green, yellow, white, black, blue
};

void setup()
{
	Serial.begin(115200);
	Serial3.begin(9600);
	pinMode(Beeper, OUTPUT);
#pragma region 初始化MU视觉传感器
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
#pragma region 初始化舵机
	while (!servo.attached()) { servo.attach(Servopin); }
	Serial.println("Servo initialized");
#pragma endregion

	delay(100);
	rotateToRight(servo);

	//while (!= MU_OK) {delay(20);};
#pragma region 配置MU
	while (Mu.SensorSetDefault() != MU_OK) { delay(20); };//重置设定
	while (Mu.CameraSetAwb(kAutoWhiteBalance) != MU_OK) { delay(20); };//自动白平衡
	while (Mu.LedSetColor(kLed1, kLedWhite, kLedWhite, 7) != MU_OK) { delay(20); };
	Mu.LedSetColor(kLed2, kLedBlue, kLedClose, 7);
	//不同模式
	switch (vision_type)
	{
	case VISION_COLOR_RECOGNITION:
		initColorReg();
		break;
	case VISION_COLOR_DETECT:
		initColorDetect(red);
		break;
	case VISION_BALL_DETECT:
		initBall();
		break;
	default:
		break;
	}
#pragma endregion
}

void loop()
{
#pragma region 更新传感器信息																
	isBlocked = infrared.isBlocked();
	ledgStat = ledg.islight();
	ledbStat = ledb.islight();

	//lastBtn1 = btnCounter1;
	//lastBtn2 = btnCounter2;
	//lastBtn3 = btnCounter3;

	//btnone.buttonCounterPress(btnCounter1);
	//btntwo.buttonCounterPress(btnCounter2);
	//btnthree.buttonCounterPress(btnCounter3);

#pragma endregion
//#pragma region 任意调用
//	if (btnconfirm.getStatus()) { isConfirmed = true; }
//
//	if (lastBtn1 != btnCounter1)
//	{
//		que[quee] = 1;
//		quee++;
//		lcd.show(1);
//	}
//	if (lastBtn2 != btnCounter1) {
//		que[quee] = 2;
//		quee++;
//		lcd.show(2);
//
//	}
//	if (lastBtn3 != btnCounter1) {
//		que[quee] = 3;
//		lcd.show(3);
//
//		quee++;
//	}
//
//	if (!isConfirmed)goto end;
//	for (int i = 0; i < 10; i++)
//	{
//		switch (que[i])
//		{
//		case 1:
//			goto Task1;
//			break;
//		case 2:
//			//goto Task2;
//			break;
//		case 3:
//			goto Task3;
//			break;
//		default:
//			break;
//		}
//	}
//
//	return;
//#pragma endregion


#pragma region 第一个任务
	Task1 :
	if (oneflag == false)Serial.println(infrared.isBlocked());
	if (infrared.isBlocked() && oneflag == false)
	{
		oneflag = true;
		rotateToanlge(servo, forward, 135);
		delay(1000);
		digitalWrite(Beeper, HIGH);
		delay(1000);
		digitalWrite(Beeper, LOW);
		delay(2000);
		rotateToRight(servo);
	}
#pragma endregion
#pragma region  第二个任务
	//Task2 :
	if (soundsenor.getvolume() >= 200&& oneflag == true)
	{
		lcd.show(2);
		rotateToanlge(servo, forward, 135);
		delay(2000);
		rotateToRight(servo);
	}
#pragma endregion

#pragma region 第三个任务
	Task3 :
	if (threeflag == false && oneflag == true&&twoflag==true)
	{
		Serial.println("Task 3");
		waitForTarget();
		colorRecongnize();
	}

#pragma endregion

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
void initBall()
{
	Mu.VisionBegin(VISION_BALL_DETECT);
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
		threeflag = true;
		lcd.show(1);
		rotateToanlge(servo, right, 135);
		delay(3000);
		rotateToanlge(servo, 135, 0);
		lcd.clear();
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

}
void ballDetect()
{
	switch (Mu.GetValue(vision_type, kLabel))
	{
	case MU_BALL_TABLE_TENNIS:
		Serial.println("table tennis");
		break;
	case MU_BALL_TENNIS:
		Serial.println("tennis");
		break;
	default:
		Serial.println("unknow ball type");
		break;
	}
}
void FindHuman()
{
	Mu.VisionBegin(VISION_BODY_DETECT);
	Mu.LedSetColor(kLed1, kLedRed, kLedWhite, 1);
	Mu.LedSetColor(kLed2, kLedRed, kLedWhite, 1);

}


//将一个范围内的数映射到另一个范围
int scaleTo(int original, int min1, int max1, int min2, int max2)
{
	return (double)(original - min1) / (max1 - min1) * (max2 - min2) + min2;
}
int scale(int input, int min, int max)
{
	scaleTo(input, 0, 1023, min, max);
}

void rotateToForward(Servo& inservo)
{
	inservo.angle(forward);
}
void rotateToLeft(Servo& inservo)
{
	inservo.angle(left);
}
void rotateToRight(Servo& inservo)
{
	inservo.angle(right);
}
void rotateToanlge(Servo& inservo, int current, int target)
{
	int angle = current;
	int k = current <= target ? 1 : -1;
	for (int i = 0; i < abs(current - target); i++)
	{
		delay(10);
		angle = angle + k;
		inservo.angle(angle);
	}
}

