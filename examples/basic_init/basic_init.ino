/*
  basic_init.ino - A simple example of how to use the PID library
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

#include "pid.h"

// set the controller parameters:
// d, T, T0, reference and type (_P, _PI or _PID)
// d and T come from the chart after setting unit step as input to process
// T0 means the sampling time, the reference is the desired setpoint
PID mypid (10E-3, 18E-3, 30E-3, 380, _PID);

void setup() {
  mypid.setLimits(0, 1023);  // set limits for controller
  mypid.init();              // initialize controller variables
  Serial.begin(9600);        // configure serial port communication
}

void loop() {
  // send the process variable as input to controller
  float output = mypid.control(analogRead(0));
  Serial.println(output);
  delay(30);
}
