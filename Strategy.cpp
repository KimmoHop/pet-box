/*
 * Strategy.cpp
 *
 *  Created on: 9.6.2016
 *      Author: kimmo.toivanen
 */

#include "Strategy.h"

Strategy::Strategy()
: lid(NULL), arm(NULL), action(Action::hold),
  lidPos(0), armPos(0) {
}

Strategy::~Strategy() {
}
