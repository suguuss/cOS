/**
 * @file pong.c
 * @author Jonas STIRNEMANN
 * @brief Pong game implementation
 * @version 0.1
 * @date 13-02-2022
 */

#include "pong.h"

#include "../drivers/screen/print/print.h"
#include "../drivers/timer/timer.h"


/**
 * @brief Set a pong game
 *
 * @param game - Pointer to an empty pong game
 */
void pong_set_game(pong_game_t* game)
{
	// BALL
	ball_t b1;
	pong_set_ball(&b1, (coord_t){ MAX_COLS / 2, MAX_ROWS / 2 }, (coord_t){ -1, 0 });

	// PADDLES
	paddle_t p1;
	paddle_t p2;
	pong_set_paddles(&p1, &p2);

	// GAME
	game->ball		   = b1;
	game->paddle_left  = p1;
	game->paddle_right = p2;
	game->score_left   = 0;
	game->score_right  = 0;
}

/**
 * @brief Set the ball
 *
 * @param ball
 * @param pos
 * @param vel
 */
void pong_set_ball(ball_t* ball, coord_t pos, coord_t vel)
{
	ball->pos.x	 = pos.x;
	ball->pos.y	 = pos.y;
	ball->vel.x	 = vel.x;
	ball->vel.y	 = vel.y;
	ball->color	 = GET_FONT_COLOR(FB_RED, FB_WHITE); // HARD CODED FOR NOW
	ball->symbol = '#';								 // HARD CODED FOR NOW
}

/**
 * @brief Set the paddles
 *
 * @param p1 - Pointer to Paddle 1
 * @param p2 - Pointer to Paddle 2
 */
void pong_set_paddles(paddle_t* p1, paddle_t* p2)
{
	p1->width = MAX_ROWS / 4;
	p1->pos.x = 1;								   // SHIFT IT BY ONE COL
	p1->pos.y = (MAX_ROWS / 2) - (p1->width / 2);  // CENTER IT
	p1->color = GET_FONT_COLOR(FB_BLUE, FB_WHITE); // HARD CODED FOR NOW

	p2->width = MAX_ROWS / 4;
	p2->pos.x = MAX_COLS - 2;						// SHIFT IT BY ONE COL FROM THE RIGHT
	p2->pos.y = (MAX_ROWS / 2) - (p2->width / 2);	// CENTER IT
	p2->color = GET_FONT_COLOR(FB_GREEN, FB_WHITE); // HARD CODED FOR NOW
}

/**
 * @brief Show a ball
 *
 * @param b - Ball to show
 */
void pong_show_ball(ball_t b)
{
	set_font_color(get_foreground_color(b.color), get_background_color(b.color));

	// CLEAR PREVIOUS BALL
	k_put_char_at(' ', b.pos.x - b.vel.x, b.pos.y - b.vel.y);
	k_put_char_at(b.symbol, b.pos.x, b.pos.y);
}


/**
 * @brief Show the paddles
 *
 * @param p1
 * @param p2
 */
void pong_show_paddles(paddle_t p1, paddle_t p2)
{
	// PADDLE 1
	set_font_color(get_foreground_color(p1.color), get_background_color(p1.color));
	for (int i = 0; i < p1.width; i++)
	{
		k_put_char_at('|', p1.pos.x, p1.pos.y + i);
	}

	// PADDLE 2
	set_font_color(get_foreground_color(p2.color), get_background_color(p2.color));
	for (int i = 0; i < p2.width; i++)
	{
		k_put_char_at('|', p2.pos.x, p2.pos.y + i);
	}
}

void draw_game(pong_game_t g)
{
	pong_show_ball(g.ball);
	pong_show_paddles(g.paddle_left, g.paddle_right);
}

/**
 * @brief Move the ball
 *
 * @param b
 */
void pong_move_ball(pong_game_t* g)
{
	// TOP / BOT
	if (g->ball.pos.y + g->ball.vel.y < 0 || g->ball.pos.y + g->ball.vel.y > MAX_ROWS - 1)
	{
		g->ball.vel.y *= -1;
	}
	// RIGHT LEFT WALLS
	if (g->ball.pos.x + g->ball.vel.x < 0 || g->ball.pos.x + g->ball.vel.x > MAX_COLS - 1)
	{
		// Check collision with left wall
		if (g->ball.pos.x + g->ball.vel.x < 0)
		{
			// Increase score of right player
			g->score_right++;
			// Reset ball
			pong_set_ball(&g->ball, (coord_t){ MAX_COLS / 2, MAX_ROWS / 2 }, (coord_t){ 1, 1 });
		}
		// Check collision with right wall
		else
		{
			// Increase score of left player
			g->score_left++;

			// clear the ball
			set_font_color(get_foreground_color(g->ball.color), get_background_color(g->ball.color));
			k_put_char_at(' ', g->ball.pos.x, g->ball.pos.y);

			// Reset ball
			pong_set_ball(&g->ball, (coord_t){ MAX_COLS / 2, MAX_ROWS / 2 }, (coord_t){ 1, 0 });
		}
	}

	// LEFT PADDLE COLLISION
	if (g->ball.pos.x + g->ball.vel.x == g->paddle_left.pos.x) // next x is in the paddle ?
	{
		// y is aligned with the paddle ?
		if (g->ball.pos.y >= g->paddle_left.pos.y && g->ball.pos.y <= g->paddle_left.pos.y + g->paddle_left.width)
		{
			g->ball.vel.x *= -1;
		}
	}
	// RIGHT PADDLE COLLISION
	if (g->ball.pos.x + g->ball.vel.x == g->paddle_right.pos.x) // next x is in the paddle ?
	{
		// y is aligned with the paddle ?
		if (g->ball.pos.y >= g->paddle_right.pos.y && g->ball.pos.y <= g->paddle_right.pos.y + g->paddle_right.width)
		{
			g->ball.vel.x *= -1;
		}
	}


	g->ball.pos.x += g->ball.vel.x;
	g->ball.pos.y += g->ball.vel.y;
}

void pong_run()
{
	pong_game_t game;
	pong_set_game(&game);
	while (1)
	{
		if (ticker_ticked())
		{
			reset_ticker();
			draw_game(game);
			pong_move_ball(&game);
		}
	}
}