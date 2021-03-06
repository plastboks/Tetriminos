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
 * 2: identifies the bricks pressure point.
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

    /* get the old bricks pressure point */
    pressure old_pressure;
    find_brick_pressure(&old_pressure, brick);

    /* copy tmp_brick over to brick */
    memcpy(brick, tmp_brick, sizeof(char)*4*4);

    /**
     * This functions has now rotated the brick, but it has not
     * taken account to the pressure point so the brick is now 
     * displaced.
     */
    brick_shift_check(old_pressure, brick);
}

/**
 * Find pressure point of input brick. Place the coordinates in
 * the y_index array.
 *
 * @pressure        struct pressure x,y
 * @brick           int brick, pointer to the faulty brick.
 *
 * Returns nothing, modifies pressure struct.
 */
void find_brick_pressure(pressure *p, char brick[4][4])
{
    unsigned char i,n;
    for(i = 0; i < 4; i++) {
        for(n = 0; n < 4 && brick[i][n] != 2; n++);
        if(n < 4) {
            p->x = n;
            p->y = i;
            return;
        }
    }
}

/**
 * Shift the brick to fix the rotation error.
 *
 * @pressure        struct pressure x,y
 * @brick           int brick, pointer to the faulty brick.
 *
 * Returns nothing, modifies brick array.
 */
void brick_shift_check(pressure old_pressure, char brick[4][4])
{
    pressure new_pressure;
    find_brick_pressure(&new_pressure, brick);

    if (old_pressure.x != new_pressure.x) {
        brick_shift_right(brick, new_pressure.x - old_pressure.x);  /* x axis shift  */
        brick_check_and_shift_sz(old_pressure, brick);              /* s and z brick */
    } else if (old_pressure.y != new_pressure.y) {
        brick_shift_up(brick, new_pressure.y - old_pressure.y);     /* y axis shift  */
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
 * x axis. This also shifts the pressure point '2', so this needs
 * to be corrected. The purpose of this function is to handle the
 * 'Z' and 'S' bricks.
 *
 * @brick           int brick, pointer to the faulty brick.
 * @count           int count, number of shifts.
 *
 * Returns nothing, runs second function (side effect).
 */
void brick_check_and_shift_sz(pressure p, char brick[4][4])
{
    /* above and right */
    if ((brick[p.y-1][p.x] == 0) && (brick[p.y][p.x+1] == 0))
        brick_shift_sz(brick);
    /* above and left and above-and-right */
    if ((brick[p.y-1][p.x] == 0)
        && (brick[p.y][p.x-1] == 0)
        && (brick[p.y-1][p.x+1] == 0))
        brick_shift_sz(brick);
}

/**
 * Shift the 's' and 'z' back into place.
 *
 * @brick           int brick, pointer to the faulty brick.
 * Returns nothing, modifies brick array.
 */
void brick_shift_sz(char brick[4][4])
{
    pressure p;

    brick_shift_up(brick, 1);
    find_brick_pressure(&p, brick);

    brick[p.y+1][p.x] = brick[p.y][p.x];
    brick[p.y][p.x] = 1;
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
