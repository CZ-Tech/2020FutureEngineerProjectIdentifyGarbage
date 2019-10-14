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
	Mu.VisionBegin(globalType);
	//while (Mu.VisionBegin(VISION_BODY_DETECT) != MU_OK) { delay(10); };
}

void mu::work()
{
	work(globalType);
}

void mu::work(MuVisionType customtype)
{
	long time_start = millis();

	if (Mu.GetValue(customtype, kStatus)) {                   // update vision result and get status, 0: undetected, other: detected
		Serial.println("human detected:");
		Serial.print("x = ");
		Serial.println(x = Mu.GetValue(customtype, kXValue));       // get vision result: x axes value
		Serial.print("y = ");
		Serial.println(y = Mu.GetValue(customtype, kYValue));       // get vision result: y axes value
		Serial.print("width = ");
		Serial.println(width = Mu.GetValue(customtype, kWidthValue));   // get vision result: width value
		Serial.print("height = ");
		Serial.println(height = Mu.GetValue(customtype, kHeightValue));  // get vision result: height value
	}
	Serial.print("fps = ");
	Serial.println(1000 / (millis() - time_start));
	Serial.println();
}

mu::mu(MuVisionType customtype)
{
	globalType = customtype;
}

