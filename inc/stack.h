/*
 * Tetriminos bricks header file
 *
 * @filename: stack.h
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-11
 *
 * @description: Tetriminos stack header file
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

int push_brick(char play_type, int play_brick_pos[2], char brick[4][4], char stack[][10]);
int check_stack(char stack[][10]);
void shift_stack(int row, char stack[][10]);

void empty_stack(char stack[][10]);
