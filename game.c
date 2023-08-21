/**	@file game.c
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
	@brief Brings together the other modules to form the game
*/


#include <stdbool.h>
#include "system.h"
#include "pacer.h"
#include "snake.h"
#include "input.h"
#include "matrix.h"
#include "ir.h"
#include "pio.h"
#include "timer.h"


/* Define the loop rate in Hz of the play_round function */
#define ROUND_RATE 400


/* Define the loop rate in Hz of the display messages */
#define DISPLAY_RATE 1000


/* Define the scale factor used to keep messages on the screen for an amount of time */
#define SCALE_FACTOR 4


/* Define the ticks for when to execute a task inside a paced loop */
#define TICK_CAPTURE 4
#define TICK_COMMS 8
#define TICK_OFFSET 2
#define TICK_MOVE 400


/* Define the winning score */
#define WINNING_SCORE 3


static Snake_t snake_1;
static Snake_t snake_2;
static uint16_t ticker;
static bool round_complete;
static uint8_t player_score = 0;
static uint8_t opponent_score = 0;


/**	Execute all tasks required before the game starts */
void initialise (void) 
{
	system_init ();
	input_init();
	ir_init();
	
	snake_1 = snake_init(PLAYER_1);
	snake_2 = snake_init(PLAYER_2);
	
	matrix_init(ROUND_RATE);
	pacer_init(ROUND_RATE);
} 


/**	Repeatedly move the snakes around the board based on
	each player's inputs. Stop when at least one snake has collided
	with the other */
void play_round (void)
{
	/* Reset the game for another round */
	snake_reset(&snake_1);
	snake_reset(&snake_2);
	input_reset();
	ir_reset();
	ticker = 0;
	round_complete = false;

	matrix_display (snake_1, snake_2);
	
	while (!round_complete) {
		pacer_wait();
		matrix_update();
		
		/* Capture input from navswitch if not yet captured */
		if (ticker % TICK_CAPTURE == 0 && !input_defined()) {
			input_capture();
		}
		
		/* Attempt to send captured input */
		if (ticker % TICK_COMMS == 0 && input_defined()) {
			ir_send(input_get());
		}
		
		/* Attempt to receive opponent's sent input */
		if (ticker % TICK_COMMS == TICK_OFFSET) {
			ir_capture();
		}
		
		/* Move snakes according to both inputs */
		if ((ticker % TICK_MOVE == 0) && (ticker != 0)) {
			snake_move (&snake_1, input_get());
			snake_move (&snake_2, ir_get());
			matrix_display(snake_1, snake_2);
			round_complete = snake_collision(snake_1, snake_2) || snake_collision(snake_2, snake_1);
		}
		
		ticker++;
 	} 
}

/**	The main function for the game
 	@return Exit success */
int main (void)
{
	initialise();

	while (player_score < WINNING_SCORE && opponent_score < WINNING_SCORE) {
		
		play_round();
		
		/* Get the result from the most recent round */
		char result = snake_result(snake_1, snake_2);
		if (result == 'W') {
			player_score++;
		} else if (result == 'L') {
			opponent_score++;
		}
		
		/* Display the result */
		pacer_init(DISPLAY_RATE);
		matrix_score(result, player_score);
		for (uint16_t i = 0; i < DISPLAY_RATE * SCALE_FACTOR; i++) {
			matrix_update();
			pacer_wait();
		}
		
		/* Reset the matrix and pacer for the next round */
		matrix_init(ROUND_RATE);
		pacer_init(ROUND_RATE);
	}
	
	/* Display the final result of the game */
	pacer_init(DISPLAY_RATE);
	matrix_game(player_score == WINNING_SCORE);
	while (1) {
		matrix_update();
		pacer_wait();
	}

}