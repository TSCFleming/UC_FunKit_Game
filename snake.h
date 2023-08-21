/**	@file snake.h
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
	@brief Module that creates and moves a snake on a 7x5 matrix
*/


#ifndef SNAKE_H
#define SNAKE_H


/* Define the maximum values of the matrix */
#define X_BORDER 4
#define Y_BORDER 6


/* Define the possible players of the game */
typedef enum {
	PLAYER_1,
	PLAYER_2
} Player_t;


/* Define the directions that a snake can move */
typedef enum {
	NORTH,
	EAST,
	SOUTH,
	WEST,
	UNDEFINED
} Direction_t;


/* Define the position a single part of the snake occupies */
typedef struct {
	int8_t x;
	int8_t y;
} Position_t;


/**	Define a snake, including the player that controls it, each position 
	the snake occupies on the matrix, and the size of the snake */	
typedef struct {
	Player_t player;
	Position_t body[35];
	uint8_t size;
} Snake_t;


/**	Create a snake
	@param new_player the controller of the snake
	@return snake */
Snake_t snake_init (Player_t new_player);


/** Reset the position of the snake
	@param snake */
void snake_reset (Snake_t* snake);


/**	Get the position of the head of a snake 
	@param snake
	@return head */
Position_t snake_head (Snake_t snake);


/**	Grow the snake in a specified direction.
	@param snake
	@param direction */
void snake_move (Snake_t* snake, Direction_t direction);


/**	Check if a snake has collided with itself or another snake.
	This DOES NOT check if the other snake has collided with itself 
	@param snake_1 
	@param snake_2
	@return true if collision */
bool snake_collision (Snake_t snake_1, Snake_t snake_2);


/**	Using both snakes positions on the board, determine the result of the round 
	@return char containing result */
char snake_result (Snake_t snake_1, Snake_t snake_2);


#endif //SNAKE_H