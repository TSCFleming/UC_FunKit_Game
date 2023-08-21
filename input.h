/**	@file input.h
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
	@brief Capture the player's input on the navswitch
*/


#ifndef INPUT_H
#define INPUT_H


#include "snake.h"


/**	Block program until player has pressed the navswitch down */
void input_init (void);


/**	Reset the previous (and default) direction */
void input_reset (void);


/** Check if captured direction is defined
	@return true if defined */
bool input_defined (void);


/**	Capture and store the direction based on the input from the navswitch*/
void input_capture (void);


/**	Get the captured direction, then reset the direction. 
	Use previous direction if current direction is undefined
	@return direction that was captured */
Direction_t input_get (void);


#endif //INPUT_H