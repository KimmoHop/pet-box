/*
 * SimpleBehaviour.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "SimpleBehaviour.h"

const int LID_SPEED = 10;
const int ARM_SPEED = 15;

SimpleBehaviour::SimpleBehaviour() {
}

SimpleBehaviour::~SimpleBehaviour() {
	// TODO Auto-generated destructor stub
}

bool SimpleBehaviour::execute(bool abort) {
	bool complete = false;

		switch (action) {
		case Action::hold:
			action = Action::open;
			break;

		case Action::open:
			if (lidPos < lid->getMaxValue()) {
				lidPos += LID_SPEED;
				lid->write(lidPos);
				//			lid.refresh();
			} else {
				action = Action::out;
			}
			break;

		case Action::out:
			if (armPos < arm->getMaxValue()) {
				armPos += ARM_SPEED;
				arm->write(armPos);
				//			arm.refresh();
			} else {
				action = Action::in;
			}
			break;

		case Action::in:
			if (armPos > arm->getMinValue()) {
				armPos -= ARM_SPEED;
				arm->write(armPos);
				//			arm.refresh();
			} else {
				action = Action::close;
			}
			break;

		case Action::close:
			if (lidPos > lid->getMinValue()) {
				lidPos -= LID_SPEED;
				lid->write(lidPos);
				//			lid.refresh();
			} else {
				action = Action::hold;
				complete = true;
			}
			break;
		}

		lid->refresh();
		arm->refresh();

		return complete;
//	bool complete = false;
//	unsigned long currentTime = millis();
//
//	if (step == 0) {
//		lidPos = sequence[step].lidAngle;
//		armPos = sequence[step].armAngle;
//		pwmPos = sequence[step].pwmValue;
//
//		writePwmPin(pwmPos);
//		lid->write(lidPos);
//		arm->write(armPos);
//
//		while (millis() < currentTime + sequence[step].delay) {
//			arm->refresh();
//			lid->refresh();
//			delay(20);
//		}
//		startTime = millis();
//	} else {
//		int phase = millis() - startTime;
//
//		if (phase < sequence[step].duration) {
//			int pwmValue = pwmPos + ((sequence[step].pwmValue - pwmPos) * phase) / sequence[step].duration;
//			int lidValue = lidPos + ((sequence[step].lidAngle - lidPos) * phase) / sequence[step].duration;
//			int armValue = armPos + ((sequence[step].armAngle - armPos) * phase) / sequence[step].duration;
//
//			writePwmPin(pwmValue);
//			lid->write(lidValue);
//			arm->write(armValue);
//			lid->refresh();
//			arm->refresh();
//
//		} else if (phase < (sequence[step].duration + sequence[step].delay)) {
//			writePwmPin(sequence[step].pwmValue);
//			lid->write(sequence[step].lidAngle);
//			arm->write(sequence[step].armAngle);
//			lid->refresh();
//			arm->refresh();
//		} else {
//			pwmPos = sequence[step].pwmValue;
//			lidPos = sequence[step].lidAngle;
//			armPos = sequence[step].armAngle;
//
//			step++;
//			if (step >= stepCount) {
//				step = 0;
//				complete = true;
//			}
//
//		}
//	}
//
//	return complete;
}

