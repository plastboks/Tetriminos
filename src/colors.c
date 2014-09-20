/*
 * Tetriminos bricks source file.
 *
 * @filename: colors.c
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-14
 *
 * @description: Tetriminos color function file
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

#include "colors.h"

/**
 * Convert brick type integer to brick type char
 */
char brick_type_char(int brick_type)
{
    switch(brick_type) {
        case 0:
              return 'i';
        case 1:
              return 'j';
        case 2:
              return 'l';
        case 3:
              return 'o';
        case 4:
              return 's';
        case 5:
              return 't';
        default:
              return 'z';
    }
}

/**
 * Return brick color based on type
 */
int get_brick_color(char brick_type) {
    switch(brick_type) {
        case 'i': /* I */
            return COLOR_CYAN_BG;
        case 'j': /* J */
            return  COLOR_BLUE_BG;
        case 'l': /* L */
            return COLOR_WHITE_BG;
        case 'o': /* O */
            return COLOR_YELLOW_BG;
        case 's': /* S */
            return COLOR_GREEN_BG;
        case 't': /* T */
            return COLOR_MAGENTA_BG;
        default: /* Z */
            return COLOR_RED_BG;
    }
}

/**
 * ncurses color setup.
 *
 * Returns nothing.
 */
void setup_colors()
{
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support colors\n");
        exit(1);
    }
    start_color();

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);
    init_pair(15, COLOR_WHITE, COLOR_BLACK);
    init_pair(16, COLOR_BLACK, COLOR_BLACK);

    init_pair(COLOR_BLACK_BG, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_GREEN_BG, COLOR_WHITE, COLOR_GREEN);
    init_pair(COLOR_WHITE_BG, COLOR_WHITE, COLOR_WHITE);
    init_pair(COLOR_RED_BG, COLOR_WHITE, COLOR_RED);
    init_pair(COLOR_CYAN_BG, COLOR_WHITE, COLOR_CYAN);
    init_pair(COLOR_MAGENTA_BG, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(COLOR_BLUE_BG, COLOR_WHITE, COLOR_BLUE);
    init_pair(COLOR_YELLOW_BG, COLOR_WHITE, COLOR_YELLOW);
}
