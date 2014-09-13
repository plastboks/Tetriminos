/*
 * Tetriminos bricks source file.
 *
 * @filename: stack.c
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-11
 *
 * @description: Tetriminos stack source file
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.    See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tetriminos.    If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "stack.h"


/**
 * Function to completely empty stacks with zeros.
 */
void empty_stack(char stack[][10])
{
    for (int y=0; y<BOARD_HEIGHT-2; y++) {
        for (int x=0; x<BOARD_WIDTH-2; x++) {
            stack[y][x] = 0;
        }
    }
}

/**
 * Push brick to stack
 */
int push_brick(char play_type, int play_brick_pos[2], char brick[4][4], char stack[][10])
{
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (brick[y][x] > 0) {
                //int sx = play_brick_pos[0];
                //int sy = play_brick_pos[1];
                //stack[sy][sx] = play_type;
            }
        }
    }
    return 1;
}

/**
 * Shift stack
 */
int shift_stack(int lines)
{
    return 1;
}
