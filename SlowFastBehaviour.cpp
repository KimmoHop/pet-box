/*
 * SlowFastBehaviour.cpp
 *
 *  Created on: 20.6.2016
 *      Author: kimmo
 */

#include "SlowFastBehaviour.h"
#include "Flash.h"

FLASH_TABLE(int, slowFastSequence, 5,
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 0, 0}, // initial position
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 1500, 0},
			{LID_MAX_VALUE, ARM_MAX_VALUE - 30, 150, 1500, 1500},
			{LID_MAX_VALUE, ARM_MAX_VALUE, 150, 100, 200},
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 200, 0},
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 200, 500}, // close position
			{LID_MIN_VALUE, ARM_MIN_VALUE, 0, 0, 0}, // lights off
			{SEQ_END, SEQ_END, 0, 0, 0}
	);

int SlowFastBehaviour::getSequenceValue(int step, int index) {
	return slowFastSequence[step][index];
};

SlowFastBehaviour::SlowFastBehaviour() {
	// TODO Auto-generated constructor stub

}

SlowFastBehaviour::~SlowFastBehaviour() {
	// TODO Auto-generated destructor stub
}

