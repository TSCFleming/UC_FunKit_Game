/**	@file matrix.h
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
	@brief Module that sets a LED matrix display in a pattern determined by a bitmap or given snakes
*/


#ifndef MATRIX_H
#define MATRIX_H


#include "snake.h"


/* Define the speeds to display each message type at */
#define STEP_SPEED 2
#define SCROLL_SPEED 8


/**	Initialize the matrix */
void matrix_init (uint16_t rate);


/** Update the matrix */
void matrix_update (void);


/**	Display given snakes on LED Matrix
	@param snake_1
	@param snake_2 */
void matrix_display (Snake_t snake_1, Snake_t snake_2);


/** Display the outcome of the most recent round and the current score 
	@param result of the last round
	@param score of the game */
void matrix_score (char result, uint8_t score);


/** Display the outcome of the game
	@param true if won */
void matrix_game (bool won);


#endif //MATRIX_H
