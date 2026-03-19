#ifndef GPIO_H
#define GPIO_H 1

#include <stdint.h>

typedef enum
{
  MODE_INPUT,
  MODE_OUTPUT_10MHZ,
  MODE_OUTPUT_2MHZ,
  MODE_OUTPUT_50MHZ
} GPIOMode;

typedef enum
{
  CNF_PUSH_PULL,
  CNF_FLOATING
} GPIOConfig;

typedef enum
{
  PULL_NONE,
  PULL_UP,
  PULL_DOWN
} GPIOPull;

void gpio_init (void);
void gpio_mode (uint8_t pin, GPIOMode mode, GPIOConfig config, GPIOPull pull);
void gpio_write (uint8_t pin, uint8_t state);
uint8_t gpio_read (uint8_t pin);
void gpio_emulate_input (uint8_t pin, uint8_t state);

#endif /* GPIO_H */
