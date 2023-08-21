/**	@file ir.h
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
    @brief Contains functions that exchange directions with an opponent using ir
*/


#ifndef IR_H
#define IR_H


#include "snake.h"


#define IR_INIT_RATE 10


/**	Block the program until the microcontroller has sent a char.
	In the case that button 1 is pressed, it will instead wait
	to receive a char */
void ir_init (void);


/**	Reset the previous (and default) direction */
void ir_reset (void);


/** Check if captured direction is defined
	@return true if defined */
bool ir_defined (void);


/**	Convert the given direction into a character and send to the other microcontroller 
	@param direction to convert to char */
void ir_send (Direction_t direction);


/**	Receive a char from the other microcontroller and store as a direction */
void ir_capture (void);


/**	Get the captured direction, then reset the direction. 
	Use previous direction if current direction is undefined
	@return direction that was captured */
Direction_t ir_get (void);


#endif //IR_H
