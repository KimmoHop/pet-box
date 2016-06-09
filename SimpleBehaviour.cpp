/*
 * SimpleBehaviour.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "SimpleBehaviour.h"


SimpleBehaviour::SimpleBehaviour() : step(0), startTime(0) {
}

SimpleBehaviour::~SimpleBehaviour() {
	// TODO Auto-generated destructor stub
}

bool SimpleBehaviour::execute(bool abort) {

	bool complete = false;
	unsigned long currentTime = millis();

	if (step == 0) {
		Serial.print("Simple begin < ");
		lidPos = sequence[step].lidAngle;
		armPos = sequence[step].armAngle;
		pwmPos = sequence[step].pwmValue;

		writePwmPin(pwmPos);
		lid->write(lidPos);
		arm->write(armPos);

		while (millis() < currentTime + sequence[step].delay) {
			arm->refresh();
			lid->refresh();
			delay(20);
		}
		startTime = millis();
		step++;
	} else {
		unsigned long phase = millis() - startTime;

		if (phase < sequence[step].duration) {
			int pwmValue = pwmPos + ((sequence[step].pwmValue - pwmPos) * phase) / sequence[step].duration;
			int lidValue = lidPos + ((sequence[step].lidAngle - lidPos) * phase) / sequence[step].duration;
			int armValue = armPos + ((sequence[step].armAngle - armPos) * phase) / sequence[step].duration;

			writePwmPin(pwmValue);
			lid->write(lidValue);
			arm->write(armValue);
			lid->refresh();
			arm->refresh();

		} else if (phase < (sequence[step].duration + sequence[step].delay)) {
			writePwmPin(sequence[step].pwmValue);
			lid->write(sequence[step].lidAngle);
			arm->write(sequence[step].armAngle);
			lid->refresh();
			arm->refresh();
		} else {
			pwmPos = sequence[step].pwmValue;
			lidPos = sequence[step].lidAngle;
			armPos = sequence[step].armAngle;

			step++;
			if (step >= stepCount) {
				step = 0;
				complete = true;
				Serial.println(">");
			} else {
				Serial.print(step);
				Serial.print(" ");
			}

		}
	}

	return complete;
}

