# GPIO Driver Emulation (STM32-style)

A simple GPIO driver written in C, emulated on x86 for learning purposes.  
It mimics STM32 registers (ODR, IDR) and supports:

- Pin modes: INPUT, OUTPUT_10MHZ, OUTPUT_2MHZ, OUTPUT_50MHZ
- Config: PUSH_PULL, FLOATING
- Pull: PULL_UP, PULL_DOWN, PULL_NONE
- Safety: prevents writing to input pins
- Emulation: `gpio_emulate_input()` to simulate external signals

## Build & Run

```bash
make
```

## Example output
```
GPIO pin 13 configured as OUTPUT_50MHZ / PUSH_PULL / PULL_DOWN
GPIO write: pin 13 = 1
ODR: 0x00000000 -> 0x00002000
```
