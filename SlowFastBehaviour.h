/*
 * SlowFastBehaviour.h
 *
 *  Created on: 20.6.2016
 *      Author: kimmo
 */

#ifndef SLOWFASTBEHAVIOUR_H_
#define SLOWFASTBEHAVIOUR_H_

#include "Strategy.h"

class SlowFastBehaviour: public Strategy {
public:
	SlowFastBehaviour();
	virtual ~SlowFastBehaviour();

protected:
	virtual int getSequenceValue(int step, int index);

};

#endif /* SLOWFASTBEHAVIOUR_H_ */
