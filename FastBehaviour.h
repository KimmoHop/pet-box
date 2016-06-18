/*
 * fastBehaviour.h
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#ifndef FASTBEHAVIOUR_H_
#define FASTBEHAVIOUR_H_

#include "Strategy.h"

class FastBehaviour: public Strategy {
public:
	FastBehaviour();
	virtual ~FastBehaviour();

//	virtual bool execute(bool abort);

protected:
	virtual const void * getSequenceAddress() {return &sequence[0];};
	virtual int getStepCount() {return 6;};

	const Strategy::SequenceStep sequence[7] = {
				{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 0, 0}, // initial position
				{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
				{LID_MAX_VALUE, ARM_MAX_VALUE, 150, 500, 500},
				{LID_MAX_VALUE, ARM_MIN_VALUE, 150, 500, 0},
				{LID_MIN_VALUE, ARM_MIN_VALUE, 20, 1000, 500}, // close position
				{LID_MIN_VALUE, ARM_MIN_VALUE, 0, 0, 0}, // lights off
				{SEQ_END, SEQ_END, 0, 0, 0}
		};
		const int stepCount = 6;
		int step;
		unsigned long startTime;
};

#endif /* FASTBEHAVIOUR_H_ */
