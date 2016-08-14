/*
 * AngryBehaviour.cpp
 *
 *  Created on: 20.6.2016
 *      Author: kimmo
 */

#include "AngryBehaviour.h"
#include "Flash.h"

FLASH_TABLE(int, angrySequence, 5,
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 0, 0}, // initial position
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 100, 200}, // fast open, wait a bit
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 100, 500}, // slam shut, wait a bit
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 100, 1000}, // fast open, wait a bit longer
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 100, 500}, // slam shut, wait a bit
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 100, 0}, // fast open
			{LID_MAX_VALUE, ARM_MAX_VALUE, 150, 100, 500}, // fast switch off
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 100, 200}, // hand back in
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 100, 500}, // slam shut
			{LID_MIN_VALUE, ARM_MIN_VALUE, 0, 0, 0}, // lights off
			{SEQ_END, SEQ_END, 0, 0, 0}
	);

int AngryBehaviour::getSequenceValue(int step, int index) {
	return angrySequence[step][index];
};

AngryBehaviour::AngryBehaviour() {
	// TODO Auto-generated constructor stub

}

AngryBehaviour::~AngryBehaviour() {
	// TODO Auto-generated destructor stub
}

