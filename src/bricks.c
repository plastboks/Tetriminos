/*
 * Tetriminos bricks source file.
 *
 * @filename: bricks.c
 *
 * @version: 0.0.1
 *
 * @date: 2014-01-06
 *
 * @description: Tetriminos screen source code file.
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

#include "bricks.h"
#include "tetriminos.h"

/**
 * Brick definitions.
 * Borrowed from Ctris http://www.hackl.dhs.org/ctris/
 *
 * 1: identifies the normal bricks.
 * 2: identifies the gravity brick(s).
 */
char brick_digit[7][4][4] =
{
    {
        {0, 1, 0, 0}, /* I */
        {0, 2, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
    },
    {
        {0, 1, 1, 0}, /* J */
        {0, 2, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0}, /* L */
        {0, 2, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {2, 2, 0, 0}, /* O */
        {2, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {   
        {0, 1, 1, 0}, /* S */
        {1, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 0, 0}, /* T */
        {1, 2, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0}, /* Z */
        {0, 2, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    }
};

/**
 * Change direction for current brick
 *
 * @brick     char brick[4][4] - current brick
 * @dir       bool dir - direction
 *
 * Returns nothing
 */
void brick_rotate(char brick[4][4], bool dir) {

    unsigned char x,y;
    char tmp_brick[4][4];

    for (y=0; y<4; y++) {
        for (x=0; x<4; x++) {
            if (dir) {
                // clockwise
                tmp_brick[y][x] = brick[3 - x][y]; 
            } else { 
                // counter clockwise
                tmp_brick[y][x] = brick[x][3 - y]; 
            }
        }
    }

    /* get the old bricks gravity */
    char old_gravity[2];
    brick_gravity(brick, old_gravity);

    /* copy tmp_brick over to brick */
    memcpy(brick, tmp_brick, sizeof(char)*4*4);

    /**
     * This functions has now rotated the brick, but it has not
     * taken account to the gravity point so the brick is now 
     * displaced.
     */
    brick_shift_check(brick, old_gravity);
}

/**
 * Find gravity point of input brick. Place the coordinates in
 * the gravity_index array.
 *
 * @brick           int brick, pointer to the faulty brick.
 * @gravity_index   int, [x,y] array identifying gravity point.
 *
 * Returns nothing, modifies gravity_index;
 */
void brick_gravity(char brick[4][4], char gravity_index[2])
{
    unsigned char i,n;
    for(i = 0; i < 4; i++) {
        for(n = 0; n < 4 && brick[i][n] != 2; n++);
        if(n < 4) {
            gravity_index[0] = n;
            gravity_index[1] = i;
            return;
        }
    }
}

/**
 * Shift the brick to fix the rotation error.
 *
 * @brick           int brick, pointer to the faulty brick.
 * @old_gravity     int, [x,y] array identifying old gravity point.
 *
 * Returns nothing, modifies brick array.
 */
void brick_shift_check(char brick[4][4], char old_gravity[2]) {
    char new_gravity[2];
    brick_gravity(brick, new_gravity);

    if (old_gravity[0] != new_gravity[0]) {
        /* x axis */
        brick_shift_right(brick, new_gravity[0]-old_gravity[0]);
    } else if (old_gravity[1] != new_gravity[1]) {
        /* y axis */
        brick_shift_up(brick, new_gravity[1]-old_gravity[1]);
    }
}

/**
 * Shift the brick array matrix right count number of times on the
 * x axis
 *
 * @brick           int brick, pointer to the faulty brick.
 * @count           int count, number of shifts.
 *
 * Returns nothing, modifies brick array.
 */
void brick_shift_right(char brick[4][4], int count)
{
    /* number of iterations */
    for (int n=0; n<count; n++) {
        /* rows */
        for (int y=0; y<4; y++) {
            /* 3 replacements */
            for (int x=0; x<3; x++) {
                char tmp = brick[y][x];
                brick[y][x] = brick[y][x+1];
                brick[y][x+1] = tmp;
            }
        }
    }
}

/**
 * Shift the brick array matrix left count number of times on the
 * x axis
 *
 * @brick           int brick, pointer to the faulty brick.
 * @count           int count, number of shifts.
 *
 * Returns nothing, modifies brick array.
 */
void brick_shift_left(char brick[4][4], int count)
{
    /* number of iterations */
    for (int n=0; n<count; n++) {
        /* rows */
        for (int y=0; y<4; y++) {
            /* 3 replacements */
            for (int x=3; x<0; x--) {
                char tmp = brick[y][x];
                brick[y][x] = brick[y][x-1];
                brick[y][x-1] = tmp;
            }
        }
    }
}

/**
 * Shift the brick array matrix up count number of times on the
 * y axis.
 *
 * @brick           int brick, pointer to the faulty brick.
 * @count           int count, number of shifts.
 *
 * Returns nothing, modifies brick array.
 */
void brick_shift_up(char brick[4][4], int count)
{
    /* number of iterations */
    for (int n=0; n<count; n++) {
        /* columns */
        for (int x=0; x<4; x++) {
            /* 3 replacements */
            for (int y=0; y<3; y++) {
                char tmp = brick[y][x];
                brick[y][x] = brick[y+1][x];
                brick[y+1][x] = tmp;
            }
        }
    }
}
