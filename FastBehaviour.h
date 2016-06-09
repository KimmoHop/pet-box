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

	virtual bool execute(bool abort);

};

#endif /* FASTBEHAVIOUR_H_ */
