/*
 * Strategy.h
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "Adafruit_SoftServo.h"

#define ARM_MIN_VALUE  30
#define ARM_MAX_VALUE  150
#define LID_MIN_VALUE  30
#define LID_MAX_VALUE  150

class Strategy {
public:



	/**
	 * Sequence of positions and pwm at the end of period
	 */
	struct SequenceStep {
		int lidAngle; /// lid servo angle after duration
		int armAngle; /// arm servo angle after duration
		int pwmValue; /// backlight brightness after duration
		int duration; /// time to move to end values
		int delay; /// time after move before next step
	};

	enum Action {
		hold = 0, open, out, in, close, end
	};

	Strategy();
	virtual ~Strategy();

	/**
	 * Set servos to the strategy
	 */
	void setServos(Adafruit_SoftServo *lid_, Adafruit_SoftServo *arm_) {lid=lid_; arm=arm_;};

	/**
	 * Set pwm pin for backlight
	 */
	void setPwmPin(int pin) {pwmPin = pin;};

	/**
	 * execute behaviour
	 *
	 * abort true if switch set while running
	 * return true when complete
	 */
	virtual bool execute(bool abort) = 0;

protected:

	/**
	 * Set pwm value
	 */
	void writePwmPin(int value);

	Adafruit_SoftServo *lid;
	Adafruit_SoftServo *arm;

	int pwmPin;


	Action action;

	int lidPos;
	int armPos;
	int pwmPos;

};

#endif /* STRATEGY_H_ */
