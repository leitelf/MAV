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


bool access_gpio (int pin);
bool export_gpio (int pin);
bool direction_gpio (int pin, direction io_direction);
int value_in_gpio (int pin);
bool value_out_gpio (int pin, int value);
bool unexport_gpio (int pin);
// In seconds
void delay (float time);
bool setup_gpio (int pin, direction io_direction);


#endif /* SOURCES_GPIO_H_ */
