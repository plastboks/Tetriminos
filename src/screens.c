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
#include "game.h"

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

/**
 * Draw the main menu.
 *
 * @coords      int array coordinates.
 *
 * Returns WINDOW
 */
WINDOW **draw_main_menu(int coords[])
{
    WINDOW **items;
    items = (WINDOW **)malloc(9 * sizeof(WINDOW *));

    mvprintw(coords[1]+5, coords[0]+7, "-Main menu-");

    items[0] = newwin(7, 21, coords[1]+6, coords[0]+2);
    wbkgd(items[0], COLOR_PAIR(1));
    box(items[0], ACS_VLINE, ACS_HLINE);

    /* first item */
    items[1]=subwin(items[0], 1, 15, coords[1]+7, coords[0]+3);
    wprintw(items[1], "New game", 1);

    /* second item */
    items[2]=subwin(items[0], 1, 15, coords[1]+8, coords[0]+3);
    wprintw(items[2], "Continue game", 1);

    /* third item */
    items[3]=subwin(items[0], 1, 15, coords[1]+9, coords[0]+3);
    wprintw(items[3], "Highscores", 1);

    /* fourth item */
    items[4]=subwin(items[0], 1, 15, coords[1]+10, coords[0]+3);
    wprintw(items[4], "About", 1);

    /* fifth item */
    items[5]=subwin(items[0], 1, 15, coords[1]+11, coords[0]+3);
    wprintw(items[5], "Quit", 1);

    wbkgd(items[1],COLOR_PAIR(0));
    wrefresh(items[0]);

    return items;
}

/**
 * Scroll main menu function. Returns chosen menu.
 *
 * @items           WINDOW items
 * @count           int for using as modulus.
 *
 * Returns selected.
 */
int scroll_main_menu(WINDOW **items, int count)
{
    int selected = 0;

    while (1) {
        switch(wgetch(stdscr)) {
            case KEY_DOWN:
            case 'j':
                selected = (selected +1) % count;
                wbkgd(items[selected], COLOR_PAIR(1));
                wnoutrefresh(items[selected]);
                wbkgd(items[selected +1], COLOR_PAIR(0));
                wnoutrefresh(items[selected +1]);
                doupdate();
                break;
            case KEY_UP:
            case 'k':
                wbkgd(items[selected+1], COLOR_PAIR(1));
                wnoutrefresh(items[selected+1]);
                selected = (selected + count -1) % count;
                wbkgd(items[selected +1],COLOR_PAIR(0));
                wnoutrefresh(items[selected +1]);
                doupdate();
                break;
            case KEY_ENTER:
            case ' ':
            case '\n':
                return selected;
        }
        usleep(5000);
    }
}

/**
 * Welcome screen
 *
 * @coords          int array of coordinates.
 *
 * Returns nothing
 */
int screen_menu(int box_size[], int coords[])
{
    WINDOW **menu;
    int selected_item;

    screen_newwin(box_size, coords);

    attron(COLOR_PAIR(3));
    for (int i = 1; i <=3; i++) {
        mvprintw(coords[1]+i, coords[0]+2, tetriminos_logo_tiny[i-1]);
    }
    attroff(COLOR_PAIR(3));
    refresh();

    menu = draw_main_menu(coords);
    selected_item = scroll_main_menu(menu, 5);

    return selected_item;
}

/**
 * About screen
 *
 * @box_size        int box size array.
 * @coords          int box placement coords.
 * @text            char text for about box.
 *
 * Returns -1 for main menu.
 */
int screen_about(int box_size[], int coords[], char text[][50])
{
    screen_newwin(box_size, coords);

    for (int i = 1; i <= sizeof(text); i++) {
        mvprintw(coords[1]+i, coords[0]+2, text[i-1]);
    }

    mvprintw(coords[1]+20, coords[0]+1, "Press 'q' to go back");
    do {
        usleep(5000);
    } while (getch() != 'q');

    return -1;
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
    noecho();
    nodelay(stdscr, true);
    keypad(stdscr, true);
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

    /*
	init_pair(COLOR_BLACK_FG, COLOR_BLACK, COLOR_BLACK);
	init_pair(COLOR_GREEN_FG, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_WHITE_FG, COLOR_WHITE, COLOR_BLACK);
	init_pair(COLOR_RED_FG, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_CYAN_FG, COLOR_CYAN, COLOR_BLACK);
	init_pair(COLOR_MAGENTA_FG, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_BLUE_FG, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_YELLOW_FG, COLOR_YELLOW, COLOR_BLACK);
    */
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

    mvprintw(coords[1]+9, coords[0]+2, "A Tetris clone by Alexander Skjolden");
    mvprintw(coords[1]-1 ,coords[0]+41, "Version: %s", VERSION);

    attron(COLOR_PAIR(main_color));
    for (int i = 1; i <=7; i++) {
        mvprintw(coords[1]+i, coords[0]+2, tetriminos_logo_small[i-1]);
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
            mvprintw(coords[1]+i, coords[0]+2, tetriminos_logo_small[i-1]);
            attroff(COLOR_PAIR(effect_color));
            /* sleep a bit, and refresh */
            usleep(effect_sleep);
            refresh();
        }
        /* Restore it to the original state */
        for (int i = 1; i <=7; i++) {
            attron(COLOR_PAIR(main_color));
            mvprintw(coords[1]+i, coords[0]+2, tetriminos_logo_small[i-1]);
            attroff(COLOR_PAIR(main_color));
            /* sleep a bit, and refresh */
            usleep(effect_sleep);
            refresh();
        }
    }
}
