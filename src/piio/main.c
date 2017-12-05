/*
 * main.c
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */

#include "src/gpio.h"
#include "src/ultrasonic.h"
#include "src/servo.h"

int main (int argc, char **argv)
{

	gpio trig1 = 23;
	gpio echo1 = 24;

	gpio trig2 = 27;
	gpio echo2 = 22;

	float distance1, distance2;
	ultrasonic_stop (trig1, echo1);
	ultrasonic_stop (trig2, echo2);

	servo_reset ();

	printf("Setting up ultrasonic...\n");
	ultrasonic_setup (trig1, echo1);
	ultrasonic_setup (trig2, echo2);

	printf("Setting up servo...\n");
	servo_setup ();

	printf("System started!\n");
	while (1) {
		distance1 = ultrasonic_get_distance (trig1, echo1);
		distance2 = ultrasonic_get_distance (trig2, echo2);
		//printf("%.2f, %.2f\n", distance1, distance2);
		if ((distance1 < 16.0) && (distance2 < 16.0)) {
			printf("%s\n", "Opening the gate...");
			servo_set_angle(90);
			delay(3);
			printf("%s\n", "Closing the gate...");
			servo_set_angle(0);
		}
	}
	return 0;
}
