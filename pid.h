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

class PID {
private:
	float kp;
	float ki;
	float kd;

	float setpoint;
	float sensorData;

	float error;
	float error_prev;

	float integral;
	float derivative;

	float output;

	float dt;

public:
	PID ();
	PID (float kp, float ki, float kd);
	void setParams(float kp, float ki, float kd);

	void control ();

};

#endif