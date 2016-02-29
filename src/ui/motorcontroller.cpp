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

#include <iostream>
#include <fstream>

#include "motorcontroller.h"
#include "pinatport.h"

using namespace std;

void MotorController::MoveStep() {
   if (enable) {
      if (!direction) {
	 position++;
      } else {
	 position--;
      }

      if (position <= minPosition) {
	 position = minPosition;
	 endStopL= 'H';
      } else {
	 endStopL= 'L';
      }

      if (position >= maxPosition) {
	 position = maxPosition;
	 endStopR= 'H';
      } else {
	 endStopR= 'L';
      }

      ostringstream os;
      os << name << " ChangeValue " << position <<  endl;
      ui->Write(os.str());
   }
}

MotorController::MotorController(UserInterface *_ui, const char *_name, const char *baseWindow):
   ui(_ui), name(_name)
{
   lastStepPinValue = 0;

   allPins["ENA"]=&enable;
   allPins["DIR"]=&direction;
   allPins["PUL"]=&step;

   allPins["ESL"]=&endStopL;
   allPins["ESR"]=&endStopR;

   step.RegisterCallback(this);

   minPosition = 0;
   maxPosition = 1000;
   position = 500;

   endStopL= 'L';
   endStopR= 'L';

   //setup the corrosponding ui in tcl from here
   ostringstream os;
   os << "create MotorController " << name  << " " << baseWindow << " " << " " << minPosition << " " << maxPosition << " " << position << endl;
   ui->Write(os.str());
}

void MotorController::PinStateHasChanged(Pin* p){
   if (p == &step) {
      if (!*p) { //Low
         lastStepPinValue = 0;
      } else { // not Low
	 if (lastStepPinValue == 0) {
	    // Step on rising edge
	    MoveStep();
	 }
         lastStepPinValue = 1;
      }
   }
}

MotorController::~MotorController() { }

Pin *MotorController::GetPin(const char *name) {
   return allPins[name];
}
