/*
 * SuspiciousBehaviour.cpp
 *
 *  Created on: 20.6.2016
 *      Author: kimmo
 */

#include "SuspiciousBehaviour.h"
#include "Flash.h"

FLASH_TABLE(int, suspiciousSequence, 5,
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 0, 0}, // initial position
			{(2*LID_MIN_VALUE + LID_MAX_VALUE)/3, ARM_MIN_VALUE, 60, 500, 1000}, // peek
			{(LID_MIN_VALUE + 2*LID_MAX_VALUE)/3, ARM_MIN_VALUE, 120, 500, 1000}, // peek more
			{(LID_MIN_VALUE + 2*LID_MAX_VALUE)/3, ARM_MIN_VALUE + 50, 150, 500, 1000},// arm a bit
			{LID_MAX_VALUE, ARM_MAX_VALUE - 50, 150, 500, 500}, // open and arm almost
			{LID_MAX_VALUE - 50, ARM_MAX_VALUE - 50, 120, 500, 500}, // close a bit
			{LID_MAX_VALUE - 50, ARM_MAX_VALUE, 120, 500, 500}, // switch
			{LID_MAX_VALUE, ARM_MAX_VALUE, 150, 500, 500}, // open
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 500}, // arm back
			{LID_MIN_VALUE + 50, ARM_MIN_VALUE, 50, 1000, 1000}, // close almost
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 1000, 500}, // close position
			{LID_MIN_VALUE, ARM_MIN_VALUE, 0, 0, 0}, // lights off
			{SEQ_END, SEQ_END, 0, 0, 0}
	);

int SuspiciousBehaviour::getSequenceValue(int step, int index) {
	return suspiciousSequence[step][index];
};

SuspiciousBehaviour::SuspiciousBehaviour() {
	// TODO Auto-generated constructor stub

}

SuspiciousBehaviour::~SuspiciousBehaviour() {
	// TODO Auto-generated destructor stub
}

