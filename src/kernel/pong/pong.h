/**
 * @file pong.h
 * @author Jonas STIRNEMANN
 * @brief Pong game implementation
 * @version 0.1
 * @date 13-02-2022
 */

#ifndef __PONG_H__
#define __PONG_H__

#include "../drivers/screen/color/color.h"
#include "../drivers/screen/cursor/cursor.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct
{
	int8_t x;
	int8_t y;
} coord_t;

typedef struct
{
	coord_t	   pos;
	coord_t	   vel;
	fb_color_t color;
	char	   symbol;
} ball_t;

typedef struct
{
	coord_t	   pos;
	uint8_t	   width;
	fb_color_t color;
} paddle_t;

typedef struct
{
	ball_t	 ball;
	paddle_t paddle_left;
	paddle_t paddle_right;
	uint8_t	 score_left;
	uint8_t	 score_right;
} pong_game_t;


// PROTOTYPES
void pong_set_game(pong_game_t* game);
void pong_set_ball(ball_t* ball, coord_t pos, coord_t vel);
void pong_set_paddles(paddle_t* p1, paddle_t* p2);
void pong_show_ball(ball_t b);
void pong_show_paddles(paddle_t p1, paddle_t p2);
void draw_game(pong_game_t g);
void pong_move_ball(pong_game_t* g);
void pong_run();


#endif // __PONG_H__