/*
 * SimpleBehaviour.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "SimpleBehaviour.h"
#include "Flash.h"

FLASH_TABLE(int, simpleSequence, 5,
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

