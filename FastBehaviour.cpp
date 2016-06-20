/*
 * fastBehaviour.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "FastBehaviour.h"
#include "Flash.h"

	FLASH_TABLE(int, fastSequence, 5 ,
				{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 0, 0}, // initial position
				{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
				{LID_MAX_VALUE, ARM_MAX_VALUE, 150, 500, 500},
				{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
				{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 1000, 500}, // close position
				{LID_MIN_VALUE, ARM_MIN_VALUE, 0, 0, 0}, // lights off
				{SEQ_END, SEQ_END, 0, 0, 0}
		);

int FastBehaviour::getSequenceValue(int step, int index) {
	return fastSequence[step][index];
}

FastBehaviour::FastBehaviour() {
	// TODO Auto-generated constructor stub

}

FastBehaviour::~FastBehaviour() {
	// TODO Auto-generated destructor stub
}
