/*
 * LimitedServo.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "LimitedServo.h"

LimitedServo::LimitedServo(Adafruit_SoftServo *servo_, int minValue_, int maxValue_) : servo(servo_), minValue(minValue_), maxValue(maxValue_) {
}

LimitedServo::~LimitedServo() {
}

void LimitedServo::attach(int pin) {
	servo->attach(pin);
}

void LimitedServo::write(int value) {
	if (value < minValue) value = minValue;
	if (value > maxValue) value = maxValue;
	servo->write(value);
}
	void LimitedServo::refresh() {
		servo->refresh();
	}
