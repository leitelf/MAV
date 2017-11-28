/*
 * ultrasonic.c
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */


#include "./src/gpio.h"

int main(int argc, char **argv)
{


	int trig = 23;
	int echo = 24;

	clock_t begin;
	clock_t end;
	double duration;
	double distance;

	if (gpio_setup(23, output)) {
		printf("Set!");
	}

	if (gpio_reset(23)) {
		printf("Reset!");
	}

	return 0;
}
