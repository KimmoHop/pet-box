/*
 * Strategy.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "Strategy.h"

//int readIntFromFlash(const void *address) {
//	int value = pgm_read_word_near(address);
//	return value;
//}

Strategy::Strategy() :
		lid(NULL), arm(NULL), pwmPin(-1), lidPos(0), armPos(
				0), pwmPos(0), step(0) {
}

Strategy::~Strategy() {
}

void Strategy::writePwmPin(int value) {
	if (pwmPin >= 1) {
		analogWrite(pwmPin, value);
	}
}

bool Strategy::execute(bool abort) {
	bool complete = false;
	unsigned long currentTime = millis();


	if (step == 0) {
		Serial.print(F("Sequence begin < 0 "));

		lidStart = getSequenceValue(step, LIDANGLE);
		armStart = getSequenceValue(step, ARMANGLE);
		pwmStart = getSequenceValue(step, PWMVALUE);
		duration = getSequenceValue(step, DURATION);
		delayAfter = getSequenceValue(step, DELAYAFTER);

//		Serial.print("(delay: ");
//		Serial.print(delayAfter);
//		Serial.print(")");
		writePwmPin(pwmStart);
		lid->write(lidStart);
		arm->write(armStart);

		while (millis() < currentTime + delayAfter) {
			arm->refresh();
			lid->refresh();
			delay(20);
		}

		step++;

		lidPos = getSequenceValue(step, LIDANGLE);
		armPos = getSequenceValue(step, ARMANGLE);
		pwmPos = getSequenceValue(step, PWMVALUE);
		duration = getSequenceValue(step, DURATION);
		delayAfter = getSequenceValue(step, DELAYAFTER);
//		Serial.print("(lid: ");
//		Serial.print(lidStart);
//		Serial.print("->");
//		Serial.print(lidPos);
//		Serial.print(")");

		startTime = millis();

	} else {
		unsigned long phase = millis() - startTime;

		if (phase < duration) {
			int pwmValue = map(phase, 0, duration, pwmStart, pwmPos);
			int lidValue = map(phase, 0, duration, lidStart, lidPos);
			int armValue = map(phase, 0, duration, armStart, armPos);

			writePwmPin(pwmValue);
			lid->write(lidValue);
			arm->write(armValue);
			lid->refresh();
			arm->refresh();

		} else if (phase < (duration + delayAfter)) {
			writePwmPin(pwmPos);
			lid->write(lidPos);
			arm->write(armPos);
			lid->refresh();
			arm->refresh();
		} else {
			writePwmPin(pwmPos);
			lid->write(lidPos);
			arm->write(armPos);
			lid->refresh();
			arm->refresh();

			lidStart = lidPos;
			armStart = armPos;
			pwmStart = pwmPos;

			Serial.print(step);
			Serial.print(' ');

			startTime = millis();
			step++;

			if (getSequenceValue(step, LIDANGLE) == SEQ_END) {
				step = 0;
				complete = true;
				Serial.println('>');
			} else {
				lidPos = getSequenceValue(step, LIDANGLE);
				armPos = getSequenceValue(step, ARMANGLE);
				pwmPos = getSequenceValue(step, PWMVALUE);
				duration = getSequenceValue(step, DURATION);
				delayAfter = getSequenceValue(step, DELAYAFTER);
			}

		}
	}

	return complete;
}
//bool Strategy::execute(bool abort) {
//	bool complete = false;
//		unsigned long currentTime = millis();
//
//		if (step == 0) {
//			Serial.print("Fast begin < 0 ");
//
//			lidStart = sequence[step].lidAngle;
//			armStart = sequence[step].armAngle;
//			pwmStart = sequence[step].pwmValue;
//
//			writePwmPin(pwmStart);
//			lid->write(lidStart);
//			arm->write(armStart);
//
//			while (millis() < currentTime + sequence[step].delay) {
//				arm->refresh();
//				lid->refresh();
//				delay(20);
//			}
//
//			step++;
//
//			lidPos = sequence[step].lidAngle;
//			armPos = sequence[step].armAngle;
//			pwmPos = sequence[step].pwmValue;
//
//			startTime = millis();
//
//		} else {
//			unsigned long phase = millis() - startTime;
//			int duration = sequence[step].duration;
//
//			if (phase < sequence[step].duration) {
//				int pwmValue = map(phase, 0, duration, pwmStart, pwmPos);
//				int lidValue = map(phase, 0, duration, lidStart, lidPos);
//				int armValue = map(phase, 0, duration, armStart, armPos);
//
//				writePwmPin(pwmValue);
//				lid->write(lidValue);
//				arm->write(armValue);
//				lid->refresh();
//				arm->refresh();
//
//			} else if (phase < (sequence[step].duration + sequence[step].delay)) {
//				writePwmPin(pwmPos);
//				lid->write(lidPos);
//				arm->write(armPos);
//				lid->refresh();
//				arm->refresh();
//			} else {
//				writePwmPin(pwmPos);
//				lid->write(lidPos);
//				arm->write(armPos);
//				lid->refresh();
//				arm->refresh();
//
//				lidStart = sequence[step].lidAngle;
//				armStart = sequence[step].armAngle;
//				pwmStart = sequence[step].pwmValue;
//
//				Serial.print(step);
//				Serial.print(" ");
//
//				startTime = millis();
//				step++;
//				if (step >= stepCount) {
//					step = 0;
//					complete = true;
//					Serial.println(">");
//				} else {
//					pwmPos = sequence[step].pwmValue;
//					lidPos = sequence[step].lidAngle;
//					armPos = sequence[step].armAngle;
//
//				}
//
//			}
//		}
//
//		return complete;
//}
