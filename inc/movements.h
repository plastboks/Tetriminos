/*
 * Tetriminos config header file
 *
 * @filename: movements.h
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-14
 *
 * @description: Tetriminos brick movements header file.
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

#include "config.h"
#include "bricks.h"

/* brick movers */
int move_brick_left(int play_brick_pos[2], char play_brick[4][4], char stack[][10]);
int move_brick_right(int play_brick_pos[2], char play_brick[4][4], char stack[][10]);
int move_brick_rotate(int play_brick_pos[2], char play_brick[4][4], char stack[][10]);
int move_brick_gravity(int play_brick_pos[2], char play_brick[4][4], char stack[][10]);
