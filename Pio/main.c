/*
 * main.c
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */

#include "src/gpio.h"
#include "src/ultrasonic.h"

int main (int argc, char **argv)
{
	gpio trig, echo;

	trig = 23;
	echo = 24;

	ultrasonic_setup(trig, echo);
	while(true) {
		printf("%f\n", ultrasonic_get_distance(trig, echo));
	}

	return 0;
}

