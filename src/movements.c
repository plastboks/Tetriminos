/*
 * Tetriminos config source code file
 *
 * @filename: movements.c
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-15
 *
 * @description: Tetriminos brick movements source code file
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

#include "movements.h"

/**
 * Move brick left if no obstacles are in the way.
 *
 * @param int   play_brick_pos: x,y coordinates of play_brick.
 * @param char  play_brick: the current tetromino brick.
 * @param char  stack: play_board stack
 *
 * Returns negative if movement is not possible, modifies play_brick_pos.
 */
int move_brick_left(int play_brick_pos[2], char play_brick[4][4], char stack[][10])
{
    /* a = play brick horizontal leftmost a point */
    int a = 3;
    int sx, sy;

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (play_brick[y][x] > 0) {
                if (x < a)
                    a = x;
                sx = ((play_brick_pos[1]+1)/2)+x-1;
                sy = (20-play_brick_pos[0])-y;
                if (stack[sy][sx-1] > 0)
                    return -1;
            }
        }
    }

    /* move only if brick does not move outside board */
    if (play_brick_pos[1]+a > 1) {
        play_brick_pos[1]-=2;
        return 1;
    }

    return -1;
}

/**
 * Move brick right if no obstacles are in the way.
 *
 * @param int   play_brick_pos: x,y coordinates of play_brick.
 * @param char  play_brick: the current tetromino brick.
 * @param char  stack: play_board stack
 
 * Returns negative if movement is not possible, modifies play_brick_pos.
 */
int move_brick_right(int play_brick_pos[2], char play_brick[4][4], char stack[][10])
{
    /* b = play brick horizontal rightmost a point */
    int b = 0;
    int sx, sy;

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (play_brick[y][x] > 0) {
                if (x > b)
                    b = x;
                sx = ((play_brick_pos[1]+1)/2)+x-1;
                sy = (20-play_brick_pos[0])-y;
                if (stack[sy][sx+1] > 0)
                    return -1;
            }
        }
    }

    /* move only if brick does not move outside board */
    if (play_brick_pos[1]+b < BOARD_WIDTH-5) {
        play_brick_pos[1]+=2;
        return 1;
    }

    return -1;
}

/**
 * Rotate brick if no obstacles are in the way.
 *
 * @param int   play_brick_pos: x,y coordinates of play_brick.
 * @param char  play_brick: the current tetromino brick.
 * @param char  stack: play_board stack
 *
 * Returns negative if movement is not possible, modifies play_brick.
 */
int move_brick_rotate(int play_brick_pos[2], char play_brick[4][4], char stack[][10])
{
    int sx, sy;

    /* this is experimental at this stage */
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (play_brick[y][x] > 0) {
                sx = ((play_brick_pos[1]+1)/2)+x-1;
                sy = (20-play_brick_pos[0])-y;
                /* other bricks in the stack */
                if ((stack[sy][sx-1] > 0) || (stack[sy][sx+1] > 0))
                    return -1;
                /* the walls of the play board */
                if ((play_brick_pos[1] < 1) || (play_brick_pos[1] > BOARD_WIDTH-7))
                    return -1;
            }
        }
    }

    /* if the mess above has passed, we should be clear to rotate at this point... */
    brick_rotate(play_brick, true);
    return 1;
}

/**
 * Move brick down if no obstacles are in the way.
 *
 * @param int   play_brick_pos: x,y coordinates of play_brick.
 * @param char  play_brick: the current tetromino brick.
 * @param char  stack: play_board stack
 *
 * Returns negative if movement is not possible, modifies play_brick_pos.
 */
int move_brick_gravity(int play_brick_pos[2], char play_brick[4][4], char stack[][10])
{
    /* h = play brick vertical bottommost point */
    int h = 0;
    int sx, sy;

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (play_brick[y][x] > 0) {
                if (y > h)
                    h = y;
                sx = ((play_brick_pos[1]+1)/2)+x-1;
                sy = (20-play_brick_pos[0])-y;
                if (stack[sy-1][sx] > 0)
                    return -1;
            }
        }
    }

    if (play_brick_pos[0]+h < BOARD_HEIGHT-2) {
        play_brick_pos[0]++;
        return 1;
    }

    return -1;
}
