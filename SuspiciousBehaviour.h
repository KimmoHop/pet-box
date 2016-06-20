/*
 * SuspiciousBehaviour.h
 *
 *  Created on: 20.6.2016
 *      Author: kimmo
 */

#ifndef SUSPICIOUSBEHAVIOUR_H_
#define SUSPICIOUSBEHAVIOUR_H_

#include "Strategy.h"

class SuspiciousBehaviour: public Strategy {
public:
	SuspiciousBehaviour();
	virtual ~SuspiciousBehaviour();

protected:
	virtual int getSequenceValue(int step, int index);

};

#endif /* SUSPICIOUSBEHAVIOUR_H_ */
