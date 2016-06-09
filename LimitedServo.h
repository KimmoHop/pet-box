/*
 * LimitedServo.h
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#ifndef LIMITEDSERVO_H_
#define LIMITEDSERVO_H_

#include <Adafruit_SoftServo.h>

class LimitedServo {
public:
	LimitedServo(Adafruit_SoftServo *servo_, int minValue_, int maxValue_);
	virtual ~LimitedServo();

	void attach(int pin);
	void write(int value);
	void refresh();

	int getMinValue() {return minValue;}
	int getMaxValue() {return maxValue;}

private:
	Adafruit_SoftServo *servo;
	int minValue;
	int maxValue;
};

#endif /* LIMITEDSERVO_H_ */
