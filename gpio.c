#include "gpio.h"
#include "lib.h"
#include <stdio.h>
#include <string.h>

static uint32_t mock_gpioa_odr = 0;
static uint32_t mock_gpioa_idr = 0;

static struct
{
  GPIOMode mode;
  GPIOConfig config;
  GPIOPull pull;
} pin_config[16];

#define GPIOA_ODR (&mock_gpioa_odr)
#define GPIOA_IDR (&mock_gpioa_idr)

void
gpio_init (void)
{
  memset (pin_config, 0, sizeof (pin_config));
  mock_gpioa_odr = 0;
  mock_gpioa_idr = 0;
  printf ("GPIO initialized!\n");
}

void
gpio_mode (uint8_t pin, GPIOMode mode, GPIOConfig config, GPIOPull pull)
{
  if (pin > 15)
    {
      printf ("Error: pin %d out of range\n", pin);
      return;
    }

  pin_config[pin].mode = mode;
  pin_config[pin].config = config;
  pin_config[pin].pull = pull;

  printf ("GPIO pin %d configured as ", pin);
  switch (mode)
    {
    case MODE_INPUT:
      printf ("INPUT");
      break;
    case MODE_OUTPUT_10MHZ:
      printf ("OUTPUT_10MHZ");
      break;
    case MODE_OUTPUT_2MHZ:
      printf ("OUTPUT_2MHZ");
      break;
    case MODE_OUTPUT_50MHZ:
      printf ("OUTPUT_50MHZ");
      break;
    }
  printf (" / ");
  switch (config)
    {
    case CNF_PUSH_PULL:
      printf ("PUSH_PULL");
      break;
    case CNF_FLOATING:
      printf ("FLOATING");
      break;
    }
  printf (" / ");
  switch (pull)
    {
    case PULL_NONE:
      printf ("PULL_NONE");
      break;
    case PULL_UP:
      printf ("PULL_UP");
      break;
    case PULL_DOWN:
      printf ("PULL_DOWN");
      break;
    }
}

void
gpio_emulate_input (uint8_t pin, uint8_t state)
{
  if (pin > 15)
    return;

  uint32_t old_val = *GPIOA_ODR;

  if (state)
    {
      *GPIOA_IDR |= (1 << pin);
    }
  else
    {
      *GPIOA_IDR &= ~(1 << pin);
    }

  printf ("GPIO emulate: pin %d input = %d\n", pin, state);
  printf ("IDR: 0x%08x -> 0x%08x\n", old_val, *GPIOA_IDR);
}

void
gpio_write (uint8_t pin, uint8_t state)
{
  if (pin > 15)
    {
      return;
    }
  if (pin_config[pin].mode == MODE_INPUT)
    {
      printf ("Warning: writing to input pin %d\n", pin);
      return;
    }

  uint32_t old_val = *GPIOA_ODR;

  if (state)
    {
      *GPIOA_ODR |= (1 << pin);
    }
  else
    {
      *GPIOA_ODR &= ~(1 << pin);
    }

  printf ("GPIO write: pin %d = %d\n", pin, state);
  printf ("ODR: 0x%08X -> 0x%08X\n", old_val, *GPIOA_ODR);
  print_bin (*GPIOA_ODR);
}

uint8_t
gpio_read (uint8_t pin)
{
  if (pin > 15)
    return 0;

  uint32_t reg
      = (pin_config[pin].mode == MODE_INPUT) ? *GPIOA_IDR : *GPIOA_ODR;
  uint32_t val = (reg >> pin) & 1;
  printf ("GPIO read: pin %d = %d (mode: %s)\n", pin, val,
          pin_config[pin].mode == MODE_INPUT ? "IN" : "OUT");
  return val;
}
