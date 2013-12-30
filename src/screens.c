/*
 * Tetriminos screen source file.
 *
 * @filename: screens.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-12-26
 *
 * @description: Tetriminos screen source code file.
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
#include "screens.h"
#include "logos.h"


/**
 * Create ncurses window.
 *
 * @height      int height.
 * @width       int width.
 * @coords      int coords array
 *
 * Returns WINDOW.
 */
WINDOW *screen_newwin(int height, int width, int coords[])
{
    WINDOW *local_win;

    local_win = newwin(height, width, coords[1], coords[1]);
    box(local_win, 0, 0);
    wrefresh(local_win);

    return local_win;
}


/**
 * Setup function for ncurses.
 *
 * Returns nothing.
 */
void screen_setup()
{
    initscr();
    curs_set(0);
    cbreak();
    nodelay(stdscr, true);
}

/**
 * ncurses color setup.
 *
 * Returns nothing.
 */
void screen_colors()
{
    if (has_colors() == FALSE) {
        endwin();
        printf("Your terminal does not support colors\n");
        exit(1);
    }
    start_color();
}

/**
 * Update screen coords
 *
 * @cords       int array box coordinates.
 * 
 * Returns nothing.
 */
void coord_update(int coords[])
{
    coords[0] = (COLS) / 2;
    coords[1] = (LINES) / 2; 
}

/**
 * ncurses cleanup
 *
 * Returns nothing
 */
void screen_end()
{
    /* Clean up and end program, end routine */
    clear();
    curs_set(1);
    endwin();
}

/**
 * Destroy window.
 *
 * @local_win       pointer to WINDOW.
 *
 * Returns nothing.
 */
void screen_destroy(WINDOW *local_win)
{
    wborder(local_win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(local_win);
    delwin(local_win);
    endwin();
    refresh();
}


/**
 * Welcome screen
 *
 * Returns nothing
 */
void screen_welcome()
{
    for (int i = 0; i <=6; i++) {
        mvprintw(26+i, 57, tetriminos_logo[i]);
    }
}
