/*
 * AngryBehaviour.h
 *
 *  Created on: 20.6.2016
 *      Author: kimmo
 */

#ifndef ANGRYBEHAVIOUR_H_
#define ANGRYBEHAVIOUR_H_

#include "Strategy.h"

class AngryBehaviour: public Strategy {
public:
	AngryBehaviour();
	virtual ~AngryBehaviour();

protected:
	virtual int getSequenceValue(int step, int index);

};

#endif /* ANGRYBEHAVIOUR_H_ */
