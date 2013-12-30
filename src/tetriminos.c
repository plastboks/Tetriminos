/*
 * Tetriminos main source file.
 *
 * @filename: tetriminos.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-12-26
 *
 * @description: Tetriminos main program file
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

#include "config.h"
#include "screens.h"

int main(int argc, char *argv[]) 
{
    WINDOW *base_win;
    char ch;
    int life = 1;
    int coords[2];
    int box_size[2] = {10, 78};

    /* run config */
    config_setup();

    /* setup screen and colors */
    screen_setup();
    screen_colors();

    refresh();
    screen_coord_update(box_size, coords);
    base_win = screen_newwin(box_size, coords);

    screen_welcome(coords);

    do {

        ch = getch();
        switch(ch) {
            case 'q':
                life = 0;
                break;
        }

    } while (life == 1);

    screen_destroy(base_win);
    screen_end();
    return 0;
}
