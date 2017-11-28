/*
 * gpio.h
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

typedef unsigned int gpio;
typedef enum {INPUT, OUTPUT} direction;
typedef enum {LOW, HIGH} gpio_level;

#define SYS_EXPORT "/sys/class/gpio/export"
#define SYS_UNEXPORT "/sys/class/gpio/unexport"
#define SYS_GPIO "/sys/class/gpio/gpio"
#define DIRECTIONS "/direction"
#define VALUES "/value"
#define IN "in"
#define OUT "out"

void delay (int seconds)
{
	struct timespec t;
	int seg;
	seg = seconds;
	t.tv_sec = seg;
	t.tv_nsec = (seconds-seg)*1e9;
	nanosleep(&t, NULL);
}


bool gpio_access (gpio pin)
{
	char path[35];
	sprintf(path, "%s%d%s", SYS_GPIO, pin, DIRECTIONS);
	if (access(path, F_OK) != -1) {
		return false;
	} else {
		return true;
	}
}


bool gpio_export (gpio pin)
{
	int file = open(SYS_EXPORT, O_WRONLY);
	char pintext [3];
	if (file == -1) {
		printf("ERROR:Failed to open export!\n");
		return false;
	}
	sprintf(pintext, "%d", pin);
	if (write(file, pintext, 3) == -1) {
		printf("ERROR:Failed to write in export!\n");
		close(file);
		return false;
	}

	close(file);
	return true;

}

bool gpio_unexport (gpio pin)
{
	int file = open(SYS_UNEXPORT, O_WRONLY);
	char pintext [3];
	if (file == -1) {
		printf("ERROR:Failed to open unexport!\n");
		return false;
	}
	sprintf(pintext, "%d", pin);
	if (write(file, pintext, 3) == -1) {
		printf("ERROR:Failed to write in unexport!\n");
		close(file);
		return false;
	}

	close(file);
	return true;
}

bool gpio_direction (gpio pin, direction io)
{
	char path[35];
	int file;
	char directiontext [4];

	sprintf(path, "%s%d%s", SYS_GPIO, pin, DIRECTIONS);
	file = open(path, O_WRONLY);

	if (file == -1) {
		printf("ERROR:Failed to open direction!\n");
		return false;
	}
	sprintf(directiontext, "%s", ((io==INPUT)?"in":"out"));
	if (write(file, directiontext, 4) == -1) {
		printf("ERROR:Failed to write in directions!\n");
		close(file);
		return false;
	}

	close(file);
	return true;
}

bool gpio_setup (gpio pin, direction io)
{
	if (gpio_access(pin)) {
		if (gpio_export(pin)) {
			delay(0.5);
			if (gpio_direction(pin, io)) {
				return true;
			}
		}
	}

	printf("Can't setup GPIO%d", pin);
	return false;
}

bool gpio_reset (gpio pin)
{
	if (!gpio_access(pin)) {
		if (gpio_unexport(pin)) {
			return true;
		}
	}

	printf("Can't reset GPIO%d", pin);
	return false;
}


int gpio_get_val (gpio pin)
{
	char path[35];
	int file;
	char value[4];
	char directiontext [4];

	sprintf(path, "%s%d%s", SYS_GPIO, pin, VALUES);
	file = open(path, O_WRONLY);

	if (file == -1) {
		printf("ERROR:Failed to open value!\n");
		return false;
	}
	if (read(file, value, 4) == -1) {
		printf("ERROR:Failed to read in value!\n");
		close(file);
		return false;
	}

	close(file);
	return atoi(value);
}


bool gpio_set_val (gpio pin, gpio_level value)
{
	char path[35];
	int file;
	char directiontext [4];

	sprintf(path, "%s%d%s", SYS_GPIO, pin, VALUES);
	file = open(path, O_WRONLY);

	if (file == -1) {
		printf("ERROR:Failed to open value!\n");
		return false;
	}
	if (write(file, ((value == HIGH)?"1":"0"), 1) == -1) {
		printf("ERROR:Failed to write in value!\n");
		close(file);
		return false;
	}

	close(file);
	return true;
}

#endif /* SRC_GPIO_H_ */
