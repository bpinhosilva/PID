/*
  pid.cpp - Library for PID control
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

#include "Arduino.h"
#include "pid.h"

// PID constructor
PID::PID() {
  this->cType = _PID; // default is PID
}

PID::PID (float d, float T, float T0, float ref, enum controllerType cType) {
  this->d     = d;
  this->T     = T;
  this->T0    = T0;
  this->ref   = ref;
  this->cType = cType;
}

// initialize controller
void PID::init() {

  switch(this->cType) {
    case _P:
      Kp = T / d;
      Ti = INFINITY;
      Td = 0.0;
      break;
    case _PI:
      Kp = 0.9 * T / d;
      Ti = d / 0.3;
      Td = 0.0;
      break;
    case _PID:
    default:
      Kp = 1.2 * T / d;
      Ti = 2 * d;
      Td = 0.5 * d;
  }

  q0 =  Kp * (1 + (Td / T0));
  q1 = -Kp * (1 + 2 * (Td / T0) - (T0 / Ti));
  q2 =  Kp * Td / T0;

  u[0] = u[1] = e[0] = e[1] = e[2] = 0;
}

void PID::setDeadTime(float d) {
  this->d = d;
}

float PID::getDeadTime() {
  return this->d;
}

void PID::setResponseTime(float T) {
  this->T = T;
}

float PID::getResponseTime() {
  return this->T;
}

// update the setpoint or reference
void PID::setReference(float ref) {
  this->ref = ref;
}

float PID::getReference() {
  return this->ref;
}

// set the filter for min and max values
void PID::setLimits(int min, int max) {
  this->minValue = min;
  this->maxValue = max;
}

float PID::control(float procOutput) {

  // calculate initial error based on process output
  e[0] = ref - procOutput;
  
  // to do: implement another filter here if necessary
  //if (e[0] >= -1 && e[0] <= 1) e[0] = 0;  
   
  u[0] = u[1] + q0 * e[0] + q1 * e[1] + q2 * e[2];
  
  if (u[0] < minValue) u[0] = minValue;
  else if (u[0] > maxValue) u[0] = maxValue;
  
  // update values
  u[1] = u[0];
  e[2] = e[1];
  e[1] = e[0];

  return u[0];
}

// get the output control variable
float PID::getOutputControl() {
  return u[0];
}

// if the output needs to be converted before using
float PID::getMappedOutputControl(int fromLow, int fromHigh, int toLow, int toHigh) {
  return map(u[0], fromLow, fromHigh, toLow, toHigh);
}
