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
#define _BSD_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <fcntl.h>
#include <time.h>

WINDOW **draw_game_boxes(int coords[]);

/* helper functions */
char get_new_brick(char brick[4][4]);
char brick_type_char(int brick_type);
int get_brick_color(char brick_type);
void empty_window(WINDOW *w, int x, int y);
void reset_brick_pos(int play_brick_pos[]);

/* brick drawers */
void draw_next_brick(WINDOW *w, char brick_type, char brick[4][4]);
void add_new_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4]);
void refresh_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4]);
void draw_stack(WINDOW *w, char stack[][10]);
void empty_but_stack(WINDOW *w, char stack[][10]);

/* game state handlers */
int game_play(WINDOW **boxes, int play_pause);
int game_pause(int coords[]);

/* brick movers */
void move_brick_left(int play_brick_pos[2], char play_brick[4][4]);
void move_brick_right(int play_brick_pos[2], char play_brick[4][4]);
int move_brick_gravity(int play_brick_pos[2], char play_brick[4][4]);
