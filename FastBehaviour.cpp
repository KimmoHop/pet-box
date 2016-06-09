/*
 * fastBehaviour.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "FastBehaviour.h"

const int LID_SPEED = 20;
const int ARM_SPEED = 30;

FastBehaviour::FastBehaviour() {
	// TODO Auto-generated constructor stub

}

FastBehaviour::~FastBehaviour() {
	// TODO Auto-generated destructor stub
}

bool FastBehaviour::execute(bool abort) {
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
}
