/*
 * Tetriminos game header file
 *
 * @filename: game.h
 *
 * @version: 0.0.1
 *
 * @date: 2014-01-06
 *
 * @description: Tetriminos main screen header file
 *
 * @author: Alexander Skjolden
 *
 * @webpage: https://github.com/plastboks/Tetriminos
 *
 * This file is part of Tetriminos.
 *
 * Tetriminos is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Tetriminos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tetriminos.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <fcntl.h>
#include <time.h>
#include <math.h>

/* define game data */
typedef struct {
    char stack[20][10];
    char play_brick[4][4];
    char next_brick[4][4];
    int play_brick_pos[2];
    char play_type;
    char next_type;
    int level;
    int bricks;
    int lines;
} game_data;

/* globally defined game data... */
game_data gd;

/* helper functions */
void setup_gamedata(WINDOW **boxes, game_data **gd);
char get_new_brick(char brick[4][4]);
void reset_brick_pos(int play_brick_pos[]);
int level_up(int *lines);

/* game state handlers */
int game_play(WINDOW **boxes, game_data *gd, int new_game);
int game_pause(int x, int y, int game_state);
