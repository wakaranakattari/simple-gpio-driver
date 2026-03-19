#include "gpio.h"
#include <stdio.h>

int
main ()
{
  gpio_init ();

  printf ("\n1. Configuring pins:\n");
  gpio_mode (13, MODE_OUTPUT_50MHZ, CNF_PUSH_PULL, PULL_DOWN);
  gpio_mode (5, MODE_INPUT, CNF_FLOATING, PULL_UP);

  printf ("\n2. Controlling LED:\n");
  gpio_write (13, 1);
  gpio_read (13);

  printf ("\n3. Turning LED off:\n");
  gpio_write (13, 0);
  gpio_read (13);

  printf ("\n4. Button press simulation:\n");
  gpio_emulate_input (5, 1);
  gpio_read (5);

  printf ("\n5. Button release:\n");
  gpio_emulate_input (5, 0);
  gpio_read (5);

  printf ("\n6. Writing to input pin (should warn):\n");
  gpio_write (5, 1);
}
