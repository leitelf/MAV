/*
 * pwm.h
 *
 *  Created on: 28 de nov de 2017
 *      Author: luiz
 *
 * - PWM is only enabled for pin 12 (GPIO18);
 * - To setup pwm add "dtoverlay=pwm,pin=18,func=2" in /boot/config.txt and
 * reboot;
 * - Execute with root (sudo su) to work.
 *
 */

#ifndef SRC_PWM_H_
#define SRC_PWM_H_

#include "gpio.h"
#include <stdlib.h>
#include <stdio.h>

#define SYS_PWM "/sys/class/pwm/pwmchip0/"
#define SYS_PWM_EXPORT "/sys/class/pwm/pwmchip0/export"
#define SYS_PWM_UNEXPORT "/sys/class/pwm/pwmchip0/unexport"

#define SYS_PWM0 "/sys/class/pwm/pwmchip0/pwm0/"
#define SYS_PWM0_PERIOD "/sys/class/pwm/pwmchip0/pwm0/period"
#define SYS_PWM0_DUTY_CYCLE "/sys/class/pwm/pwmchip0/pwm0/duty_cycle"
#define SYS_PWM0_ENABLE "/sys/class/pwm/pwmchip0/pwm0/enable"


bool pwm_access ()
{
	if (access(SYS_PWM0_PERIOD, F_OK) != -1) {
		return false;
	} else {
		return true;
	}
}


bool pwm_export ()
{
	int file = open(SYS_PWM_EXPORT, O_WRONLY);

	if (file == -1) {
		printf("ERROR:Failed to open export!\n");
		return false;
	}
	if (write(file, "0", 1) == -1) {
		printf("ERROR:Failed to write in export!\n");
		close(file);
		return false;
	}

	close(file);
	return true;

}

bool pwm_unexport ()
{
	int file = open(SYS_PWM_UNEXPORT, O_WRONLY);
	if (file == -1) {
		printf("ERROR:Failed to open unexport!\n");
		return false;
	}
	if (write(file, "0", 1) == -1) {
		printf("ERROR:Failed to write in unexport!\n");
		close(file);
		return false;
	}

	close(file);
	return true;
}

bool pwm_set_frequency (float frequency) {
  int period = (int) (1000000000.0/frequency);
  int file = open(SYS_PWM0_PERIOD, O_WRONLY);
  char value[35];
	sprintf(value, "%d", period);
  if (file == -1) {
    printf("ERROR: failed to open period!\n");
    return false;
  }
  if (write(file, value, 35) == -1) {
    printf ("ERROR: failed to write on period!\n");
    close (file);
    return false;
  }
  close(file);
  return true;
}

bool pwm_setup (float frequency)
{
	if (pwm_access()) {
		if (pwm_export()) {
			delay(1.2);
      if (pwm_set_frequency(frequency)) {
          return true;
      }
		}
	}

	printf("Can't setup GPIO\n");
	return false;
}

bool pwm_reset ()
{
	if (!pwm_access()) {
		if (pwm_unexport()) {
			return true;
		}
	}

	printf("Can't reset GPIO\n");
	return false;
}

int pwm_get_period ()
{
	char period[35];
	int file = open(SYS_PWM0_PERIOD, O_RDONLY);
	if (file == -1) {
		printf("ERROR: failed to open period!\n");
		return -1;
	}

	if (read (file, period, 35) == -1) {
		printf("ERROR: failed to read period!\n");
		close(file);
		return -1;
	}
	close (file);
	return atoi(period);
}

bool pwm_set_duty_cycle (float duty_cycle)
{
	int period = pwm_get_period();
	int duty_cycle_size = 0;
	char value[35];
	int file;
	if (period > 0) {
		duty_cycle_size = (int)((float)period)*(duty_cycle/100.0);
		file = open (SYS_PWM0_DUTY_CYCLE, O_WRONLY);
		sprintf(value, "%d", duty_cycle_size);
		if (file == -1) {
			printf("ERROR: failed to open duty_cycle!\n");
			return false;
		}

		if (write (file, value, 35) == -1) {
			printf("ERROR: failed to write in duty_cycle!\n");
			close(file);
			return false;
		}
		close (file);
		return true;
	}
	return false;
}

bool pwm_start ()
{
	int file = open (SYS_PWM0_ENABLE, O_WRONLY);
	if (file == -1) {
		printf("ERROR: failed to open enable!\n");
		return false;
	}
	if (write (file, "1", 2) == -1) {
		printf("ERROR: failed to write in enable!\n");
		close(file);
		return false;
	}
	close(file);
	return true;
}

bool pwm_stop ()
{
	int file = open (SYS_PWM0_ENABLE, O_WRONLY);
	if (file == -1) {
		printf("ERROR: failed to open enable!\n");
		return false;
	}
	if (write (file, "0", 2) == -1) {
		printf("ERROR: failed to write in enable!\n");
		close(file);
		return false;
	}
	close(file);
	return true;
}

#endif /* SRC_PWM_H_ */
