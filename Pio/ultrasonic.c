/*
 * ultrasonic.c
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */


#include "../includes/gpio.h"

void stop ();

int main(int argc, char **argv)
{

	signal(SIGINT, stop);

	int trig = GPIO23;
	int echo = GPIO24;

	clock_t begin;
	clock_t end;
	double duration;
	double distance;
	setup_gpio(echo, INPUT);

	setup_gpio(trig, OUTPUT);
	value_out_gpio(trig, LOW);

	while (true) {
		value_out_gpio(trig, HIGH);
		delay(0.00001);
		value_out_gpio(trig, LOW);

		while (value_in_gpio(echo) == LOW) {
			begin = clock();
		}

		while (value_in_gpio(echo) == HIGH) {
			end = clock();
		}

		duration = (double)(end-begin)*1000/CLOCKS_PER_SEC;

		distance = duration * 17150;
		printf("%.2f", distance);
	}

}

void stop() {
	unexport_gpio(GPIO23);
	unexport_gpio(GPIO24);
}
