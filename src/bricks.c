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

/**
 * Brick definitions.
 * Borrowed from Ctris http://www.hackl.dhs.org/ctris/
 */
char brick_digit[7][4][4] =
{
    {
        {0, 1, 0, 0},
        {0, 2, 0, 0},
        {0, 1, 0, 0},
        {0, 1, 0, 0},
    },
    {
        {2, 2, 0, 0},
        {2, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0},
        {0, 2, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 1, 0},
        {0, 2, 0, 0},
        {0, 1, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {1, 1, 0, 0},
        {0, 2, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {   
        {0, 1, 1, 0},
        {1, 2, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    },
    {
        {0, 1, 0, 0},
        {1, 2, 1, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
    }
};

