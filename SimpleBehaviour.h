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
};

#endif /* SIMPLEBEHAVIOUR_H_ */
