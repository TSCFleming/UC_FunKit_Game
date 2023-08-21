# File:   Makefile
# Author: tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
# Date:   18 Oct 2022
# Brief:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c ../../drivers/avr/system.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@
	
pacer.o: ../../utils/pacer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/pacer.h
	$(CC) -c $(CFLAGS) $< -o $@
	
timer.o: ../../drivers/avr/timer.c ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/system.h ../../drivers/avr/pio.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/pio.h ../../drivers/navswitch.h 
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h 
	$(CC) -c $(CFLAGS) $< -o $@
	
display.o: ../../drivers/display.c ../../drivers/display.h
	$(CC) -c $(CFLAGS) $< -o $@
	
ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/system.h ../../drivers/avr/pio.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../utils/font.h 
	$(CC) -c $(CFLAGS) $< -o $@
	
ir_uart.o: ../../drivers/avr/ir_uart.c ../../drivers/avr/system.h ../../drivers/avr/ir_uart.h ../../drivers/avr/usart1.h ../../drivers/avr/timer0.h ../../drivers/avr/pio.h ../../drivers/avr/delay.h 
	$(CC) -c $(CFLAGS) $< -o $@
	
usart1.o: ../../drivers/avr/usart1.c ../../drivers/avr/system.h ../../drivers/avr/usart1.h
	$(CC) -c $(CFLAGS) $< -o $@

timer0.o: ../../drivers/avr/timer0.c ../../drivers/avr/system.h ../../drivers/avr/timer0.h ../../drivers/avr/bits.h ../../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

prescale.o: ../../drivers/avr/prescale.c ../../drivers/avr/system.h ../../drivers/avr/prescale.h
	$(CC) -c $(CFLAGS) $< -o $@

snake.o: snake.c snake.h
	$(CC) -c $(CFLAGS) $< -o $@
	
input.o: input.c ../../drivers/navswitch.h snake.h input.h
	$(CC) -c $(CFLAGS) $< -o $@

matrix.o: matrix.c ../../utils/tinygl.h ../../fonts/font5x7_1.h snake.h matrix.h
	$(CC) -c $(CFLAGS) $< -o $@
	
ir.o: ir.c ../../drivers/avr/ir_uart.h ../../drivers/avr/pio.h ../../utils/pacer.h snake.h input.h ir.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
game.out: game.o system.o pacer.o timer.o pio.o navswitch.o tinygl.o display.o ledmat.o font.o ir_uart.o usart1.o timer0.o prescale.o snake.o input.o matrix.o ir.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start