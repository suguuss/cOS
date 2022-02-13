/**
 * @file pong.c
 * @author Jonas STIRNEMANN
 * @brief Pong game implementation
 * @version 0.1
 * @date 13-02-2022
 */

#include "pong.h"

#include "../drivers/keyboard/keyboard.h"
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
	pong_set_ball(&b1, DEFAULT_BALL_POS, DEFAULT_BALL_VEL);

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
	ball->color	 = GET_FONT_COLOR(BALL_COLOR, BACK_COLOR); // HARD CODED FOR NOW
	ball->symbol = BALL_SYMBOL;							   // HARD CODED FOR NOW
}

/**
 * @brief Set the paddles
 *
 * @param p1 - Pointer to Paddle 1
 * @param p2 - Pointer to Paddle 2
 */
void pong_set_paddles(paddle_t* p1, paddle_t* p2)
{
	p1->width = PADDLE_SIZE;
	p1->pos.x = 1;										   // SHIFT IT BY ONE COL
	p1->pos.y = (MAX_ROWS / 2) - (p1->width / 2);		   // CENTER IT
	p1->color = GET_FONT_COLOR(LPADDLE_COLOR, BACK_COLOR); // HARD CODED FOR NOW

	p2->width = PADDLE_SIZE;
	p2->pos.x = MAX_COLS - 2;							   // SHIFT IT BY ONE COL FROM THE RIGHT
	p2->pos.y = (MAX_ROWS / 2) - (p2->width / 2);		   // CENTER IT
	p2->color = GET_FONT_COLOR(RPADDLE_COLOR, BACK_COLOR); // HARD CODED FOR NOW
}

/**
 * @brief Show a ball
 *
 * @param b - Ball to show
 */
void pong_show_ball(ball_t b)
{
	set_font_color_whole(b.color);

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
	// CLEAR PREVIOUS PADDLES
	for (int i = 0; i < MAX_ROWS; i++)
	{
		k_put_char_at(' ', p1.pos.x, i);
		k_put_char_at(' ', p2.pos.x, i);
	}

	// PADDLE 1
	set_font_color_whole(p1.color);
	for (int i = 0; i < p1.width; i++)
	{
		k_put_char_at(PADDLE_SYMBOL, p1.pos.x, p1.pos.y + i);
	}

	// PADDLE 2
	set_font_color_whole(p2.color);
	for (int i = 0; i < p2.width; i++)
	{
		k_put_char_at(PADDLE_SYMBOL, p2.pos.x, p2.pos.y + i);
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

			// clear the ball
			set_font_color_whole(g->ball.color);
			k_put_char_at(' ', g->ball.pos.x, g->ball.pos.y);

			// Reset ball
			pong_set_ball(&g->ball, DEFAULT_BALL_POS, DEFAULT_BALL_VEL);
		}
		// Check collision with right wall
		else
		{
			// Increase score of left player
			g->score_left++;

			// clear the ball
			set_font_color_whole(g->ball.color);
			k_put_char_at(' ', g->ball.pos.x, g->ball.pos.y);

			// Reset ball
			pong_set_ball(&g->ball, DEFAULT_BALL_POS, DEFAULT_BALL_VEL);
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

/**
 * @brief Move the paddle up by one
 *
 * @param p
 */
void pong_paddle_move_up(paddle_t* p)
{
	if (p->pos.y > 0)
	{
		p->pos.y--;
	}
}

/**
 * @brief Move the paddle down by 1
 *
 * @param p
 */
void pong_paddle_move_down(paddle_t* p)
{
	if (p->pos.y < MAX_ROWS - 1)
	{
		p->pos.y++;
	}
}

void pong_run()
{
	pong_game_t game;
	pong_set_game(&game);
	k_cclear(BACK_COLOR);
	while (1)
	{
		if (ticker_ticked())
		{
			reset_ticker();

			pong_move_ball(&game);
			if (is_key_pressed(KEY_W))
			{
				pong_paddle_move_up(&game.paddle_left);
			}
			if (is_key_pressed(KEY_S))
			{
				pong_paddle_move_down(&game.paddle_left);
			}

			draw_game(game);
		}
	}
}