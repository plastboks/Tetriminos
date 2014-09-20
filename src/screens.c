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

#include "screens.h"
#include "colors.h"
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
WINDOW *screen_newwin(coords c, struct size s)
{
    WINDOW *local_win;

    erase();
    refresh();
    local_win = newwin(s.height, s.width, c.cur.y, c.cur.x);
   
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
WINDOW **draw_main_menu(coords c)
{
    WINDOW **items;
    items = (WINDOW **)malloc(9 * sizeof(WINDOW *));

    mvprintw(c.cur.y+5, c.cur.x+7, "-Main menu-");

    items[0] = newwin(7, 21, c.cur.y+6, c.cur.x+2);
    wbkgd(items[0], COLOR_PAIR(1));
    box(items[0], ACS_VLINE, ACS_HLINE);

    /* first item */
    items[1]=subwin(items[0], 1, 15, c.cur.y+7, c.cur.x+3);
    wprintw(items[1], "New game", 1);

    /* second item */
    items[2]=subwin(items[0], 1, 15, c.cur.y+8, c.cur.x+3);
    wprintw(items[2], "Continue game", 1);

    /* third item */
    items[3]=subwin(items[0], 1, 15, c.cur.y+9, c.cur.x+3);
    wprintw(items[3], "Highscores", 1);

    /* fourth item */
    items[4]=subwin(items[0], 1, 15, c.cur.y+10, c.cur.x+3);
    wprintw(items[4], "About", 1);

    /* fifth item */
    items[5]=subwin(items[0], 1, 15, c.cur.y+11, c.cur.x+3);
    wprintw(items[5], "Quit", 1);

    wbkgd(items[1],COLOR_PAIR(0));
    wrefresh(items[0]);

    return items;
}

/**
 * Init box sizes
 */
void screen_init_sizes(sizes *s)
{
    /* splash box size */
    s->splash.height = 9;
    s->splash.width = 54;
    /* menu box size */
    s->menu.height = 14;
    s->menu.width = 25;
    /* about box size */
    s->about.height = 20;
    s->about.width = 44;
    /* game box size */
    s->game.height = 20;
    s->game.width = 44;
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
 * Update screen coords
 *
 * @cords       int array box coordinates.
 * 
 * Returns nothing.
 */
void screen_coord_update(coords *c, struct size s)
{
    c->cur.x = (COLS - s.width) / 2;
    c->cur.y = (LINES - s.height) / 2; 
    c->old.x = COLS;
    c->old.y = LINES;
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
int screen_welcome(coords c, bool effect)
{
    int main_color = 3;
    int effect_color = 2;
    int effect_sleep = 50000;

    mvprintw(c.cur.y+9, c.cur.x+2, "A Tetris clone by Alexander Skjolden");
    mvprintw(c.cur.y-1 ,c.cur.x+41, "Version: %s", VERSION);

    attron(COLOR_PAIR(main_color));
    for (int i = 1; i <=7; i++) {
        mvprintw(c.cur.y+i, c.cur.x+2, tetriminos_logo_small[i-1]);
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
            mvprintw(c.cur.y+i, c.cur.x+2, tetriminos_logo_small[i-1]);
            attroff(COLOR_PAIR(effect_color));
            /* sleep a bit, and refresh */
            usleep(effect_sleep);
            refresh();
        }
        /* Restore it to the original state */
        for (int i = 1; i <=7; i++) {
            attron(COLOR_PAIR(main_color));
            mvprintw(c.cur.y+i, c.cur.x+2, tetriminos_logo_small[i-1]);
            attroff(COLOR_PAIR(main_color));
            /* sleep a bit, and refresh */
            usleep(effect_sleep);
            refresh();
        }
    }
    return -1;
}

/**
 * Welcome screen
 *
 * @coords          int array of coordinates.
 *
 * Returns nothing
 */
int screen_menu(coords c, struct size s)
{
    WINDOW **menu;
    int selected_item;

    screen_newwin(c, s);

    attron(COLOR_PAIR(3));
    for (int i = 1; i <=3; i++) {
        mvprintw(c.cur.y+i, c.cur.x+2, tetriminos_logo_tiny[i-1]);
    }
    attroff(COLOR_PAIR(3));
    refresh();

    menu = draw_main_menu(c);
    selected_item = scroll_main_menu(menu, 5);

    return selected_item;
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
 * About screen
 *
 * @coords          int box placement coords.
 * @text            char text for about box.
 *
 * Returns -1 for main menu.
 */
int screen_about(coords c, struct size s, char text[][50])
{
    screen_newwin(c, s);

    for (int i = 1; i <= sizeof(text); i++) {
        mvprintw(c.cur.y+i, c.cur.x+2, text[i-1]);
    }

    mvprintw(c.cur.y+20, c.cur.x+1, "Press 'q' to go back");
    do {
        usleep(5000);
    } while (getch() != 'q');

    return -1;
}
