/**	@file input.c
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
	@brief Capture the player's input on the navswitch
*/


#include <stdbool.h>
#include "navswitch.h"
#include "snake.h"
#include "input.h"


/* Define the variables for the captured direction to be stored into */
static Direction_t direction = UNDEFINED;
static Direction_t prev_direction = WEST;


/**	Block program until player has pressed the navswitch down */
void input_init (void)
{
	navswitch_update();
	while (!navswitch_push_event_p(NAVSWITCH_PUSH)) {
		navswitch_update();
	}
}


/**	Reset the previous (and default) direction */
void input_reset (void)
{
	direction = UNDEFINED;
	prev_direction = WEST;
}


/** Check if captured direction is defined
	@return true if defined */
bool input_defined (void)
{
	return direction != UNDEFINED;
}


/**	Capture and store the direction based on the input from the navswitch*/
void input_capture (void)
{
	navswitch_update();
	
	/* Check the four navswitch inputs to determine the direction */
	if (navswitch_push_event_p(NAVSWITCH_NORTH)) {
		direction = NORTH;
	} else if (navswitch_push_event_p(NAVSWITCH_EAST)) {
		direction = EAST;
	} else if (navswitch_push_event_p(NAVSWITCH_SOUTH)) {
		direction = SOUTH;
	} else if (navswitch_push_event_p(NAVSWITCH_WEST)) {
		direction = WEST;
	}
}


/**	Get the captured direction, then reset the direction. 
	Use previous direction if current direction is undefined
	@return direction that was captured */
Direction_t input_get (void)
 {
	/* If the current direction is undefined, set to the previous direction */
	if (!input_defined()) {
		direction = prev_direction;
	}
	
	/* Return and reset the captured direction */
	prev_direction = direction;
	direction = UNDEFINED;
	return prev_direction;
}
