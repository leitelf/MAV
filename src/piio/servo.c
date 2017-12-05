#include "src/pwm.h"
#include "src/gpio.h"
#include "src/pwm.h"
#include "src/servo.h"
#include "string.h"

void helperFunc ()
{
  printf("Format: servo <option> [angle]\n");
  printf("option: setup, rotate or reset;\n");
  printf("angle: angle to rotate(float);\n");
}

int main (int argc, char **argv)
{
  float angle;

  if (!((argc == 3) || (argc == 2))) {
    helperFunc ();
    return -1;
  }

  if (strcmp("setup", argv[1]) == 0) {
    return servo_setup ();
  }

  if (strcmp("rotate", argv[1]) == 0) {
    if(argc != 3) {
      helperFunc ();
      return -1;
    }
    angle = atof(argv[2]);
    servo_set_angle (angle);
    return 0;
  }

  if (strcmp("reset", argv[1]) == 0) {
    return servo_reset ();
  }

  return -1;
}
