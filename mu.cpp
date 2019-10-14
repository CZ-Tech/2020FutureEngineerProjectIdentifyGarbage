// 
// 
// 
#include <Arduino.h>
#include <MuVisionSensor.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "mu.h"

#define I2C_MODE
#define MU_ADDRESS    0x60

MuVisionSensor Mu(MU_ADDRESS);

void mu::initialize()
{
	A:
	err = MU_ERROR_FAIL;
	Wire.begin();
	err = Mu.begin(&Wire);
	if (err == MU_OK) {
		Serial.println("MU initialized.");
	}
	else {
			Serial.println("fail to initialize MU! Please check protocol "
				"version or make sure MU is working on the "
				"correct port with correct mode.");
			delay(5000);
			goto A;
	}
	Mu.VisionBegin(type);
}

void mu::work()
{
	long time_start = millis();

	if (Mu.GetValue(VISION_BODY_DETECT,kStatus)) {                   // update vision result and get status, 0: undetected, other: detected
		Serial.println("human detected:");
		Serial.print("x = ");
		Serial.println(x=Mu.GetValue(VISION_BODY_DETECT, kXValue));       // get vision result: x axes value
		Serial.print("y = ");
		Serial.println(y=Mu.GetValue(VISION_BODY_DETECT, kYValue));       // get vision result: y axes value
		Serial.print("width = ");
		Serial.println(width=Mu.GetValue(VISION_BODY_DETECT, kWidthValue));   // get vision result: width value
		Serial.print("height = ");
		Serial.println(height=Mu.GetValue(VISION_BODY_DETECT, kHeightValue));  // get vision result: height value
	}
	//else {
	//	Serial.println("vision body undetected.");
	//}
	Serial.print("fps = ");
	Serial.println(1000 / (millis() - time_start));
	Serial.println();
}

mu::mu(MuVisionType customtype)
{
	type = customtype;
}
