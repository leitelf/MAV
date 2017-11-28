/*
 * ultrasonic.h
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */

#ifndef SRC_ULTRASONIC_H_
#define SRC_ULTRASONIC_H_


#include "gpio.h"
#include "time.h"

bool ultrasonic_setup (gpio trig, gpio echo)
{
	if (gpio_setup(trig, OUTPUT)) {
		if (gpio_setup(echo, INPUT)) {
			return true;
		}
	}

	gpio_reset(trig);
	gpio_reset(echo);

	return false;
}

double ultrasonic_get_distance (gpio trig, gpio echo)
{

	clock_t pulse_start, pulse_end;
	double distance;

	gpio_set_val(trig, HIGH);
	delay(0.00001);
	gpio_set_val(trig, LOW);

	while (gpio_get_val(echo) == LOW) {
		pulse_start = clock();
	}

	while (gpio_get_val(echo) == HIGH) {
		pulse_end = clock();
	}


	return ((double) (pulse_end-pulse_start)*17150/CLOCKS_PER_SEC);
}


#endif /* SRC_ULTRASONIC_H_ */
