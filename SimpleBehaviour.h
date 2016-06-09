/*
 * SimpleBehaviour.h
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#ifndef SIMPLEBEHAVIOUR_H_
#define SIMPLEBEHAVIOUR_H_

#include "Strategy.h"

class SimpleBehaviour: public Strategy {
public:
	SimpleBehaviour();
	virtual ~SimpleBehaviour();

	virtual bool execute(bool abort);

protected:
	const Strategy::SequenceStep sequence[9] = {
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 0, 0}, // initial position
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
			{LID_MAX_VALUE, ARM_MAX_VALUE - 50, 150, 500, 500},
			{LID_MAX_VALUE, ARM_MAX_VALUE, 150, 200, 200},
			{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 500, 1000},
			{LID_MIN_VALUE + 30, ARM_MIN_VALUE, 50, 1000, 1000},
			{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 1000, 500}, // close position
			{LID_MIN_VALUE, ARM_MIN_VALUE, 0, 0, 0} // lights off
	};;
	const int stepCount = 9;
	int step;
	unsigned long startTime;
};

#endif /* SIMPLEBEHAVIOUR_H_ */
