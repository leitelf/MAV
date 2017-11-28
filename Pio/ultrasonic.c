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

	return gpio_access (trig);

}
