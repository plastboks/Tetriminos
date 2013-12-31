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
#include "screens.h"
#include "logos.h"
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
WINDOW *screen_newwin(int box_size[], int coords[])
{
    WINDOW *local_win;

    erase();
    refresh();
    local_win = newwin(box_size[0], box_size[1], coords[1], coords[0]);
   
    /**
     * Set color and draw box.
     */
    wattron(local_win,COLOR_PAIR(BORDER_COLOR));
    box(local_win, 0, 0);
    wattroff(local_win,COLOR_PAIR(BORDER_COLOR));

    wrefresh(local_win);

    return local_win;
}


/***********************************
 * Some functions for controlling  *
 * the screen, setup, colors, end, *
 * destroy and such.               *
 ***********************************/

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

    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
}

/**
 * Update screen coords
 *
 * @cords       int array box coordinates.
 * 
 * Returns nothing.
 */
void screen_coord_update(int box_size[], int coords[], int old_coords[])
{
    coords[0] = (COLS - box_size[1]) / 2;
    coords[1] = (LINES - box_size[0]) / 2; 
    old_coords[0] = COLS;
    old_coords[1] = LINES;
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


/**********************************
 * Below follows functions which  *
 * purpose is to print to screen.  *
 **********************************/

/**
 * Welcome screen
 *
 * Returns nothing
 */
void screen_welcome(int coords[], bool effect)
{
    int main_color = 3;
    int effect_color = 2;
    int effect_sleep = 50000;

    mvprintw(coords[1]+10, coords[0]+2, "A Tetris clone by Alexander Skjolden");
    mvprintw(coords[1]+10 ,coords[0]+64, "Version: %s", VERSION);

    attron(COLOR_PAIR(main_color));
    for (int i = 1; i <=7; i++) {
        mvprintw(coords[1]+i, coords[0]+2, tetriminos_logo[i-1]);
    }
    attroff(COLOR_PAIR(main_color));
    refresh();

    
    /**
     * Do some fancy effect if true.
     */
    if (effect) {
        usleep(effect_sleep);
        /* Do the effect */
        for (int i = 1; i <=7; i++) {
            attron(COLOR_PAIR(effect_color));
            mvprintw(coords[1]+i, coords[0]+2, tetriminos_logo[i-1]);
            attroff(COLOR_PAIR(effect_color));
            /* sleep a bit, and refresh */
            usleep(effect_sleep);
            refresh();
        }
        /* Restore it to the original state */
        for (int i = 1; i <=7; i++) {
            attron(COLOR_PAIR(main_color));
            mvprintw(coords[1]+i, coords[0]+2, tetriminos_logo[i-1]);
            attroff(COLOR_PAIR(main_color));
            /* sleep a bit, and refresh */
            usleep(effect_sleep);
            refresh();
        }
    }
}

/**
 * Welcome screen
 *
 * Returns nothing
 */
void screen_menu(int coords[])
{
    mvprintw(coords[1]+2, coords[0]+2, "Menu be here.");
}
