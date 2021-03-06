/*
 * Tetriminos bricks header file
 *
 * @filename: bricks.h
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

#include <stdbool.h>
#include <stdlib.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#ifndef _PRESSURE
#define _PRESSURE
typedef struct {
    int x;
    int y;
} pressure; 
#endif

char brick_digit[7][4][4];
void find_brick_pressure(pressure *p, char brick[4][4]);

void brick_rotate(char brick[4][4], bool dir);

void brick_shift_check(pressure old_pressure, char brick[4][4]);
void brick_shift_up(char brick[4][4], int count);
void brick_shift_right(char brick[4][4], int count);
void brick_check_and_shift_sz(pressure p, char brick[4][4]);
void brick_shift_sz(char brick[4][4]);

