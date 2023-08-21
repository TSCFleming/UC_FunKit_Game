/**	@file snake.c
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
	@brief Module that creates and moves a snake on a 7x5 matrix
*/


#include <stdint.h>
#include <stdbool.h>
#include "snake.h"


/**	Create a snake
	@param new_player the controller of the snake
	@return snake */
Snake_t snake_init (Player_t new_player)
{
	Position_t head = {X_BORDER, Y_BORDER};
	
	/* Change the start position of the snake for Player 2 */
	if (new_player == PLAYER_2) {
		head.x = 0;
		head.y = 0;
	}
	
	Snake_t snake = {.player = new_player, .body[0] = head, .size = 1};
	return snake;
}


/** Reset the position of the snake
	@param snake */
void snake_reset (Snake_t* snake)
{
	Position_t head = {X_BORDER, Y_BORDER};
	
	/* Reset to the starting position for Player 2 */
	if (snake->player == PLAYER_2) {
		head.x = 0;
		head.y = 0;
	}
	snake->body[0] = head;
	snake->size = 1;
}


/**	Get the position of the head of a snake 
	@param snake
	@return head */
Position_t snake_head (Snake_t snake)
{
	return snake.body[snake.size - 1];
}


/**	Grow the snake in a specified direction.
	@param snake
	@param direction */
void snake_move (Snake_t* snake, Direction_t direction)
{	
	Position_t next_head;
	
	/* Set the position of the next head of the snake */
	switch (direction) {
		case NORTH:
			next_head.x = snake_head(*snake).x; 
			next_head.y = snake_head(*snake).y - 1;
			break;
		case EAST:
			next_head.x = snake_head(*snake).x + 1; 
			next_head.y = snake_head(*snake).y;
			break;
		case SOUTH:
			next_head.x = snake_head(*snake).x;
			next_head.y = snake_head(*snake).y + 1;
			break;
		case WEST:
			next_head.x = snake_head(*snake).x - 1; 
			next_head.y = snake_head(*snake).y;
			break;
		default:
			next_head.x = snake_head(*snake).x; 
			next_head.y = snake_head(*snake).y;
	}
	
	/* Check if the snake head has moved off the edge of the matrix.
	   If so, move it to the opposite side */
	if (next_head.x > X_BORDER) {
		next_head.x = 0;
	}
	if (next_head.x < 0) {
		next_head.x = X_BORDER;
	}
	if (next_head.y > Y_BORDER) {
		next_head.y = 0;
	}
	if (next_head.y < 0) {
		next_head.y = Y_BORDER;
	}
	snake->body[snake->size++] = next_head;
}


/**	Check if a snake has collided with itself or another snake.
	This DOES NOT check if the other snake has collided with itself 
	@param snake_1 
	@param snake_2
	@return true if collision */
bool snake_collision (Snake_t snake_1, Snake_t snake_2)
{
	Position_t head = snake_head (snake_1);
	
	/* Check for collision with self */
	for (uint8_t i = 0; i < snake_1.size - 1; i++) {
		if (head.x == snake_1.body[i].x && head.y == snake_1.body[i].y) {
				return true;
			}
	}
	
	/* Check for collision with other snake */
	for (uint8_t i = 0; i < snake_1.size; i++) {
		if (head.x == snake_2.body[i].x && head.y == snake_2.body[i].y) {
				return true;
			}
	}
	
	return false;
}


/**	Using both snakes positions on the board, determine the result of the round 
	@return char containing result */
char snake_result (Snake_t snake_1, Snake_t snake_2)
{
	if (snake_collision(snake_2, snake_1) && !snake_collision(snake_1, snake_2)) {
		return 'W';
	}
	
	if (snake_collision(snake_1, snake_2) && !snake_collision(snake_2, snake_1)) {
		return 'L';
	}
	
	return 'D';
}