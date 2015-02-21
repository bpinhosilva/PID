/*
  pid.h - Library for PID control.
  Created by Bruno Pinho, February 21, 2015.
  Released into the public domain.
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