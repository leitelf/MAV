/*
 * gpio.h
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

typedef enum {input=0, output=1} io;
typedef enum {low=0, high=1} output_level;

#define PATH_SIZE 35
#define BUFFER_SIZE 3

bool gpio_access (int pin)
{
	char path[PATH_SIZE];
	snprintf(path, PATH_SIZE, "/sys/class/gpio/gpio%d/direction", pin);
	if (access(path, 0) == -1) {
		return true;
	} else {
		return false;
	}
}

bool gpio_export (int pin)
{
	char buffer[BUFFER_SIZE];
	int file = open ("/sys/class/gpio/export", O_WRONLY);
	if (-1 == file) {
		return false;
	}
	snprintf(buffer, BUFFER_SIZE, "%d", pin);
	if (write(file, buffer, BUFFER_SIZE) == -1) {
		close (file);
		return false;
	}
	close (file);
	return true;
}

bool gpio_unexport(int pin)
{
	char buffer[BUFFER_SIZE];
	int file = open ("/sys/class/gpio/unexport", O_WRONLY);
	if (file == -1)	{
		return false;
	}
	if(write(file, buffer, BUFFER_SIZE) == -1)
	{
		close(file);
		return false;
	}
	return true;
}

bool gpio_direction (int pin, io direction)
{
	int file=0;
	char path[PATH_SIZE];
	char buffer[BUFFER_SIZE];
	snprintf(path, PATH_SIZE, "/sys/class/gpio/gpio%d/direction", pin);
	file = open (path, O_WRONLY);
	if (file==-1) {
		return false;
	}
	snprintf(buffer, BUFFER_SIZE, "%d", pin);
	if (write( file, ((direction == input)?"in":"out"), BUFFER_SIZE )==-1) {
		close(file);
		return false;
	}
	close(file);
	return true;
}

bool gpio_setup (int pin, io direction)
{
	if (gpio_access(pin)) {
		if (gpio_export(pin)) {
			if (gpio_direction(pin, direction)) {
				return true;
			}
		}
	}

	return false;
}

bool gpio_reset (int pin)
{
	return gpio_unexport(pin);
}
#endif /* SRC_GPIO_H_ */
