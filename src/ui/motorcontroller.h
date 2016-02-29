 /*
 ****************************************************************************
 *
 * simulavr - A simulator for the Atmel AVR family of microcontrollers.
 * Copyright (C) 2001, 2002, 2003   Klaus Rudolph
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 ****************************************************************************
 *
 *  $Id$
 */

#ifndef MOTOR_CONTROLLER_H_INCLUDED
#define MOTOR_CONTROLLER_H_INCLUDED


#include <fstream>
#include <string>

#include "systemclocktypes.h"
#include "simulationmember.h"
//#include "hardware.h"
#include "ui.h"
#include "pin.h"


/** Simulates a HD44780 character-LCD controller with a 4 bit interface.
 * This HD-controller is boring slow :-) like some original.
 */
class MotorController : public HasPinNotifyFunction {
    protected:
        UserInterface *ui;
        std::string name;
        std::map<std::string, Pin*> allPins;

        Pin enable;
        Pin direction;
        Pin step;

	Pin endStopL;
	Pin endStopR;

	int minPosition;
	int maxPosition;
        int position;

	int lastStepPinValue;

        virtual void PinStateHasChanged(Pin* p);

	void MoveStep(void);

    public:
        //MotorController(UserInterface *ui, const string &name, const string &baseWindow);
        MotorController(UserInterface *ui, const char *name, const char *baseWindow);
        virtual ~MotorController();

        Pin *GetPin(const char *name);
};

#endif
