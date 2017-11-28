/*
 * ultrasonic.c
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */


#include "./src/gpio.h"

void stop ();

int main(int argc, char **argv)
{

	signal(SIGINT, stop);

	int trig = 23;
	int echo = 24;

	clock_t begin;
	clock_t end;
	double duration;
	double distance;

	if (gpio_access(trig)) {
		if (gpio_export(trig)) {
			if (gpio_unexport(trig))
				printf("Success!");
		}
	}

	return 0;
}
