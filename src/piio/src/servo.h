/*
 * servo.h
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */

#ifndef SRC_SERVO_H_
#define SRC_SERVO_H_


#include "gpio.h"
#include "pwm.h"
#include <time.h>
#include <unistd.h>

bool servo_setup ()
{
	return pwm_setup(50.0);
}

void servo_set_angle (float angle)
{
  float duty_cycle = (angle / 18 +2);
  pwm_set_duty_cycle (duty_cycle);
	pwm_start();
	delay(1);
	pwm_stop();
	pwm_set_duty_cycle (0.0);
}


bool servo_reset ()
{
	return pwm_reset();
}
#endif /* SRC_SERVO_H_ */
