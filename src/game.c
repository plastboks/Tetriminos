/*
 * Tetriminos game source file.
 *
 * @filename: game.c
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

#include "game.h"
#include "config.h"

/**
 * Create ncurses window.
 *
 * @height      int height.
 * @width       int width.
 * @coords      int coords array
 *
 * Returns WINDOW.
 */
WINDOW *game_newwin(int box_size[], int coords[])
{
    WINDOW *local_win;

    erase();
    refresh();
    local_win = newwin(box_size[0], box_size[1], coords[1], coords[0]);
   
    wrefresh(local_win);

    return local_win;
}

/**
 * Draw the main menu.
 *
 * @coords      int array coordinates.
 *
 * Returns WINDOW
 */
WINDOW **draw_game_boxes(int coords[])
{
    WINDOW **items;
    items = (WINDOW **)malloc(9 * sizeof(WINDOW *));

    erase();
    refresh();

    items[0] = newwin(20, 34, coords[1], coords[0]);
    wbkgd(items[0], COLOR_PAIR(1));

    /* game window */
    items[1]=subwin(items[0], 19, 20, coords[1]+1, coords[0]+1);
    box(items[1], ACS_VLINE, ACS_HLINE);

    /* next brick */
    items[2]=subwin(items[0], 5, 10, coords[1]+1, coords[0]+22);
    box(items[2], ACS_VLINE, ACS_HLINE);

    /* scores */
    items[3]=subwin(items[0], 5, 10, coords[1]+10, coords[0]+22);
    box(items[3], ACS_VLINE, ACS_HLINE);

    wbkgd(items[1],COLOR_PAIR(0));
    wrefresh(items[0]);

    return items;
}

/**
 * Welcome screen
 *
 * @coords          int array of coordinates.
 *
 * Returns nothing
 */
int game_play(int box_size[], int coords[])
{
    //WINDOW **game_boxes;

    //game_newwin(box_size, coords);

    draw_game_boxes(coords);

    mvprintw(coords[1]+20, coords[0]+1, "Press 'q' to go back");
    do {
        usleep(5000);
    } while (getch() != 'q');

    return -1;
}
