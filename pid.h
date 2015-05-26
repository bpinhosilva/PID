/*
  pid.h - Library for PID control
  Copyright (c) 2015 Bruno Sampaio Pinho da Silva.  All right reserved.
  E-mail address: bpinhosilva@gmail.com
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef PID_H
#define PID_H

#include "Arduino.h"

// controller type to use
enum controllerType {
  P,
  PI,
  PID
};

class PID {
private:
  enum  controllerType cType; // type of controller default PID
	
  float d;   // controller parameter from curve after unit step input applied
  float T;   // controller parameter from curve after unit step input applied

  float Kp;  // proportional gain  
  float Ti;  // integral time
  float Td;  // derivative time
  float T0;  // sampling time

  float q0;  // controler parameters calculated first
  float q1;
  float q2;

  float u[2]; // controlled value
  float e[3]; // error

  float ref = 0.0;  // reference or setpoint

  int minValue;
  int maxValue;

public:
  PID (float d, float T, float T0, float ref, enum controllerType cType);	
  void init();
  void setReference(float ref);
  float getReference();
  void setLimits(int min, int max);
  float control(float procOutput);
  float getOutputControl();
  float getMappedOutputControl(int fromLow, int fromHigh, int toLow, int toHigh);
};

#endif