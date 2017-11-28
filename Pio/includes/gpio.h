/*
 * gpio.h
 *
 *  Created on: 27 de nov de 2017
 *      Author: luiz
 */

#ifndef SOURCES_GPIO_H_
#define SOURCES_GPIO_H_

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <signal.h>

#define GPIO2 2
#define GPIO3 3
#define GPIO4 4
#define GPIO17 17
#define GPIO27 27
#define GPIO22 22
#define GPIO10 10
#define GPIO9 9
#define GPIO11 11
#define GPIO5 5
#define GPIO6 6
#define GPIO13 13
#define GPIO19 19
#define GPIO26 26
#define GPIO18 18
#define GPIO23 23
#define GPIO24 24
#define GPIO25 25
#define GPIO8 8
#define GPIO7 7
#define GPIO12 12
#define GPIO16 16
#define GPIO20 20
#define GPIO21 21

#define LOW 0
#define HIGH 1
typedef enum {INPUT=0, OUTPUT=1} direction;


#define BB_SIZE 35
#define SB_SIZE 3

bool access_gpio (int pin)
{
	char path[BB_SIZE];
	snprintf(path, BB_SIZE, "/sys/class/gpio/gpio%d/direction", pin);
	if (access(path, 0) == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool export_gpio (int pin)
{
	// Open for Writing ONLY
	char buffer[SB_SIZE];
	int file = open ("/sys/class/gpio/export", O_WRONLY);
	if (file == -1) {
		printf("Failed to open file! [export_gpio()]\n");
		return false;
	}

	sprintf(buffer, SB_SIZE, "%d", pin);
	if (write(file, buffer, SB_SIZE) == -1) {
		close(file);
		return false;
	}
	close(file);
	return true;
}

bool direction_gpio (int pin, direction io_direction)
{
	int file = 0;
	char path[BB_SIZE];
	char buffer[SB_SIZE];
	snprintf(path, BB_SIZE, "/sys/class/gpio/gpio%d/direction", pin);
	file = open (path, O_WRONLY);
	if (file==-1) {
		return false;
	}
	sprintf(buffer, SB_SIZE, "%d", pin);
	if (write(file, ((io_direction == INPUT)?"in":"out"), SB_SIZE)==-1) {
		close(file);
		return false;
	}
	close(file);
	return true;
}

int value_in_gpio (int pin)
{
	int file = 0;
	char output[SB_SIZE];
	char path[BB_SIZE];
	snprintf(path, BB_SIZE, "/sys/class/gpio/gpio%d/value", pin);
	file = open(path, O_RDONLY);
	//printf("Descritor do arquivo: %d \n", arquive);
	if (file == -1)
	{
		return false;
	}
	if (read(file, output, SB_SIZE) == -1)
	{
		close(file);
		return false;
	}
	close(file);
	printf("Valor do pino: %c \n", output[0]);

	return atoi(output);
}

bool value_out_gpio (int pin, int value)
{
	int file=0;
	char path[BB_SIZE];
	snprintf(path, BB_SIZE, "/sys/class/gpio/gpio%d/value", pin);
	file = open(path, O_WRONLY);
	if (file == -1)	{
		return false;
	}
	if (write (file, ((value == HIGH)?"1":"0"), 1) == -1) {
		close(file);
		return false;
	}
	close(file);
	return true;
}

bool unexport_gpio (int pin)
{
	int file = open ("/sys/class/gpio/unexport", O_WRONLY);
	char buffer[SB_SIZE];
	if (file==-1) {
		printf("Arquivo abriu incorretamente\n");
		return false;
	}
	if(write(file, buffer, SB_SIZE) == -1)	{
		close(file);
		return false;
	}
	return true;
}

//in seconds
void delay (float time)
{
	struct timespec t;
	int seg;
	seg = time;
	t.tv_sec = seg;
	t.tv_nsec = (time-seg)*1e9;
	nanosleep(&t, NULL);
}

bool setup_gpio (int pin, direction io_direction) {
	if (access_gpio(pin)) {
		if (export_gpio(pin)) {
			if (direction_gpio(pin, io_direction)) {
				return true;
			}
		}
	}

	return false;
}


#endif /* SOURCES_GPIO_H_ */
