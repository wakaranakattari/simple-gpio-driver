CFLAGS = -Wall -Wextra -std=11

all:
	gcc main.c lib.c gpio.c -o gpio && chmod +x gpio && ./gpio

clean:
	rm -f gpio
