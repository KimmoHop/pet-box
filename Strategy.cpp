/*
 * Strategy.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "Strategy.h"

Strategy::Strategy()
: lid(NULL), arm(NULL), pwmPin(-1), action(Action::hold),
  lidPos(0), armPos(0), pwmPos(0) {
}

Strategy::~Strategy() {
}

void Strategy::writePwmPin(int value) {
	if (pwmPin >= 1) {
		analogWrite(pwmPin, value);
	}
}
