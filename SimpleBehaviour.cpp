/*
 * SimpleBehaviour.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "SimpleBehaviour.h"
#include "Flash.h"

FLASH_TABLE(int, simpleSequence, 10,
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 0, 0}, // initial position
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
			{LID_MAX_VALUE, ARM_MAX_VALUE - 50, 150, 500, 500},
			{LID_MAX_VALUE, ARM_MAX_VALUE, 150, 200, 200},
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 500, 1000},
			{LID_MIN_VALUE + 30, ARM_MIN_VALUE, 50, 1000, 1000},
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 1000, 500}, // close position
			{LID_MIN_VALUE, ARM_MIN_VALUE, 0, 0, 0}, // lights off
			{SEQ_END, SEQ_END, 0, 0, 0}
	);

int SimpleBehaviour::getSequenceValue(int step, int index) {
	return simpleSequence[step][index];
};

SimpleBehaviour::SimpleBehaviour() {
}

SimpleBehaviour::~SimpleBehaviour() {
	// TODO Auto-generated destructor stub
}

//bool SimpleBehaviour::execute(bool abort) {
//
//	bool complete = false;
//	unsigned long currentTime = millis();
//
//	if (step == 0) {
//		Serial.print("Fast begin < 0 ");
//
//		lidStart = sequence[step].lidAngle;
//		armStart = sequence[step].armAngle;
//		pwmStart = sequence[step].pwmValue;
//
//		writePwmPin(pwmStart);
//		lid->write(lidStart);
//		arm->write(armStart);
//
//		while (millis() < currentTime + sequence[step].delay) {
//			arm->refresh();
//			lid->refresh();
//			delay(20);
//		}
//
//		step++;
//
//		lidPos = sequence[step].lidAngle;
//		armPos = sequence[step].armAngle;
//		pwmPos = sequence[step].pwmValue;
//
//		startTime = millis();
//
//	} else {
//		unsigned long phase = millis() - startTime;
//		int duration = sequence[step].duration;
//
//		if (phase < sequence[step].duration) {
//			int pwmValue = map(phase, 0, duration, pwmStart, pwmPos);
//			int lidValue = map(phase, 0, duration, lidStart, lidPos);
//			int armValue = map(phase, 0, duration, armStart, armPos);
//
//			writePwmPin(pwmValue);
//			lid->write(lidValue);
//			arm->write(armValue);
//			lid->refresh();
//			arm->refresh();
//
//		} else if (phase < (sequence[step].duration + sequence[step].delay)) {
//			writePwmPin(pwmPos);
//			lid->write(lidPos);
//			arm->write(armPos);
//			lid->refresh();
//			arm->refresh();
//		} else {
//			writePwmPin(pwmPos);
//			lid->write(lidPos);
//			arm->write(armPos);
//			lid->refresh();
//			arm->refresh();
//
//			lidStart = sequence[step].lidAngle;
//			armStart = sequence[step].armAngle;
//			pwmStart = sequence[step].pwmValue;
//
//			Serial.print(step);
//			Serial.print(" ");
//
//			startTime = millis();
//			step++;
//			if (step >= stepCount) {
//				step = 0;
//				complete = true;
//				Serial.println(">");
//			} else {
//				pwmPos = sequence[step].pwmValue;
//				lidPos = sequence[step].lidAngle;
//				armPos = sequence[step].armAngle;
//
//			}
//
//		}
//	}
//
//	return complete;
//}

