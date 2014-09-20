/*
 * Tetriminos config header file
 *
 * @filename: drawers.h
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-19
 *
 * @description: Tetriminos brick drawer header file.
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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "colors.h"
#include "config.h"

struct {
    int main_window;
    int game_board;
    int next_brick;
    int score_board;
} w;

/* setup game board and info boxes */
WINDOW **draw_game_boxes(int x, int y);

/* window cleaners */
void empty_window(WINDOW *w, int x, int y);
void empty_but_stack(WINDOW *w, char stack[][10]);

/* brick drawers */
void add_new_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4]);
void refresh_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4]);

/* info box drawers */
void update_next_brick(WINDOW *w, char brick_type, char brick[4][4]);
void update_score_board(WINDOW *w, int *lines, int *bricks, int *level);

/* stack drawer */
void draw_stack(WINDOW *w, char stack[][10]);
