/**	@file ir.c
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
    @brief Contains functions that exchange directions with an opponent using ir
*/


#include <stdbool.h>
#include "ir_uart.h"
#include "pio.h"
#include "pacer.h"
#include "snake.h"
#include "ir.h"


/* Define the variables for the captured direction to be stored into */
static Direction_t direction = UNDEFINED;
static Direction_t prev_direction = EAST;


/**	Block the program until the microcontroller has sent a char.
	In the case that button 1 is pressed, it will instead wait
	to receive a char */
void ir_init (void)
{
    ir_uart_init();
	pacer_init(IR_INIT_RATE);
	
	/* Wait to receive a char if the button is pressed */
	if (pio_input_get(PD7_PIO)) {
		pio_output_high(LED1_PIO);
		ir_uart_getc();
		pio_output_low(LED1_PIO);
	} 
	
	/* Otherwise wait until a char has been transmitted */
	else {
		ir_uart_putc('A');
		while (!ir_uart_write_finished_p()) {
			pacer_wait();
		}
	}

}


/**	Reset the previous (and default) direction */
void ir_reset (void) 
{
	direction = UNDEFINED;
	prev_direction = EAST;
}


/** Check if captured direction is defined
	@return true if defined */
bool ir_defined (void)
{
	return direction != UNDEFINED;
}


/**	Convert the given direction into a character and send to the other microcontroller 
	@param direction to convert to char */
void ir_send (Direction_t direction)
{
	char c = 'U';
	
	/* Convert from direction to char */
	if (direction == NORTH) {
		c = 'N';
	} else if (direction == EAST) {
		c = 'E';
	} else if (direction == SOUTH) {
		c = 'S';
	} else if (direction == WEST) {
		c = 'W';
	}

	if (ir_uart_write_ready_p()) {	
		ir_uart_putc(c); 
	}
}


/**	Receive a char from the other microcontroller and store as a direction */
void ir_capture (void)
{
	char c = 'U';
	
	if (ir_uart_read_ready_p()) {
		c = ir_uart_getc();
	}
	
	/* Convert from char to direction and store value */	
	if (c == 'N') {
		direction = SOUTH;
	} else if (c == 'E') {
		direction = WEST;
	} else if (c == 'S') {
		direction = NORTH;
	} else if (c == 'W') {
		direction = EAST;
	}
}


/**	Get the captured direction, then reset the direction. 
	Use previous direction if current direction is undefined
	@return direction that was captured */
Direction_t ir_get (void) 
{
	/* If the current direction is undefined, set to the previous direction */
	if (!ir_defined()) {
		direction = prev_direction;
	}
	
	/* Return and reset the captured direction */
	prev_direction = direction;
	direction = UNDEFINED;
	return prev_direction;
}