#include "lib.h"
#include <stdint.h>
#include <stdio.h>

void
print_bin (uint8_t byte)
{
  for (int i = 7; i >= 0; --i)
    {
      printf ("%d", (byte >> i) & 1);
      if (i == 4)
        printf (" ");
    }
  printf ("\n");
}

void
print_hex (uint8_t byte)
{
  printf ("Hex: 0x%02X\n", byte);
}

void
print_all (uint8_t byte)
{
  print_bin (byte);
  print_hex (byte);
  printf ("\n");
}
