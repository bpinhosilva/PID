/*
  pid.cpp - Library for PID control.
  Created by Bruno Pinho, February 21, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "pid.h"

// PID constructor
PID::PID() {
	
}

PID::PID(float kp, float ki, float kd) {
	
}

void PID::setParams(float kp, float ki, float kd) {
	this->kp = kp;
	this->ki = ki;
	this->kd = kd;
}

void PID::control () {
	error       = setpoint - sensorData;
	integral    = integral + error*dt;
	derivative  = (error - error_prev)/dt;
	output      = kp * error + ki * integral + kd * derivative;
	error_prev  = error;
	//delay(dt); 
}