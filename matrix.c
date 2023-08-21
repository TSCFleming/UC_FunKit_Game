/**	@file matrix.c
	@author tfl33 (Thomas Fleming) & cfi29 (Caleb Fitzgerald) 
	@date 18 Oct 2022
	@brief Module that sets a LED matrix display in a pattern determined by a bitmap or given snakes
*/


#include "tinygl.h"
#include "../fonts/font5x7_1.h"
#include "snake.h"
#include "matrix.h"


/**	Initialize the matrix */
void matrix_init (uint16_t rate)
{
	tinygl_init(rate);
}


/** Update the matrix */
void matrix_update (void)
{
	tinygl_update();
}


/**	Display bitmap pattern on LED Matrix
	@param bitmap*/
static void matrix_set (uint8_t bitmap[])
{
    uint8_t i;
	uint8_t j;
    /* Set LEDs in LED Matrix to values given by bitmap */
    for (i = 0; i < X_BORDER + 1; i++) {
        for (j = 0; j < Y_BORDER + 1; j++) {
            /* Set LED to value */
            tinygl_draw_point(tinygl_point(i, j), bitmap[i] & (1 << j));
        }
    }
}


/**	Display given snakes on LED Matrix
	@param snake_1
	@param snake_2 */
void matrix_display (Snake_t snake_1, Snake_t snake_2)
{
    uint8_t bitmap[X_BORDER + 1] = {0};
    uint8_t i;
    /* Add body positions of the snake for Player 1 */
    for (i = 0; i < snake_1.size; i++) {
        bitmap[snake_1.body[i].x] |= (1 << snake_1.body[i].y);
    }
    /* Add body positions of the snake for Player 2 */
    for (i = 0; i < snake_2.size; i++) {
        bitmap[snake_2.body[i].x] |= (1 << snake_2.body[i].y);
    }
    matrix_set(bitmap);
}


/** Display the outcome of the most recent round and the current score 
	@param result of the last round
	@param score of the game */
void matrix_score (char result, uint8_t score) 
{
    tinygl_font_set(&font5x7_1);
    tinygl_text_speed_set(2);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_STEP);
	
	char string[3] = {result, score + '0', '\0'};
	tinygl_text(string);
}


/** Display the outcome of the game
	@param true if won */
void matrix_game (bool won) 
{
    tinygl_text_speed_set(8);
	tinygl_text_mode_set(TINYGL_TEXT_MODE_SCROLL);
	
	if (won) {
		tinygl_text("Victory");
	} else {
		tinygl_text("Defeat");
	}
}