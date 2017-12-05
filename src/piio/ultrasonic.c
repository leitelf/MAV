#include "src/ultrasonic.h"
#include "src/gpio.h"
#include "string.h"

void helperFunc ()
{
  printf("Format: ultrasonic <option> <trig> <echo>\n");
  printf("option: setup, read or reset;\n");
  printf("trig: GPIO number (int);\n");
  printf("echo: GPIO number (int);\n");
}

int main (int argc, char **argv)
{

  gpio trig;
  gpio echo;

  if (argc != 4) {
    helperFunc ();
    return -1;
  }

  trig = atoi (argv[2]);
  echo = atoi (argv[3]);

  if (strcmp("setup", argv[1]) == 0) {
    return ultrasonic_setup (trig, echo);
  }

  if (strcmp("read", argv[1]) == 0) {
    return  ultrasonic_get_distance (trig, echo);
  }

  if (strcmp("reset", argv[1]) == 0) {
    return ultrasonic_stop (trig, echo);
  }

  return -1;
}
