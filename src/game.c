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

struct {
    int main_window;
    int game_board;
    int next_brick;
    int score_board;
} w = {
    0, 1, 2, 3
};

/**
 * Draw the game window and boxes
 *
 * int coords defines the center of the screens, set by the
 * applications init functions.
 *
 * Returns WINDOW
 */
WINDOW **draw_game_boxes(int coords[])
{
    WINDOW **items;

    /* main window size */
    int mw_size[2] = {BOARD_HEIGHT + 2, BOARD_WIDTH + 14};
    /* game board size */
    int gb_size[2] = {BOARD_HEIGHT, BOARD_WIDTH};
    /* next brick size */
    int nb_size[2] = {5, 10};
    /* high score size */
    int hs_size[2] = {5, 10};

    items = (WINDOW **)malloc(9 * sizeof(WINDOW *));
    erase();
    refresh();

    /* main window */
    mvprintw(coords[1]-1, coords[0]+9, "- Tetriminos -");
    items[w.main_window] = newwin(mw_size[0], mw_size[1], coords[1], coords[0]);
    box(items[w.main_window], ACS_VLINE, ACS_HLINE);

    /* game window */
    items[w.game_board]=subwin(items[w.main_window],
                               gb_size[0], gb_size[1],
                               coords[1]+1, coords[0]+1);
    box(items[w.game_board], ACS_VLINE, ACS_HLINE);

    /* next brick */
    mvprintw(coords[1]+2, coords[0] + BOARD_WIDTH + 2, "Next brick");
    items[w.next_brick]=subwin(items[w.main_window],
                               nb_size[0], nb_size[1],
                               coords[1]+3, coords[0] + BOARD_WIDTH + 2);
    box(items[w.next_brick], ACS_VLINE, ACS_HLINE);

    /* scores */
    mvprintw(coords[1]+10, coords[0] + BOARD_WIDTH + 2, "Score");
    items[w.score_board]=subwin(items[w.main_window],
                                      hs_size[0], hs_size[1],
                                      coords[1]+11, coords[0] + BOARD_WIDTH + 2);
    box(items[w.score_board], ACS_VLINE, ACS_HLINE);

    /* colors */
    wbkgd(items[w.main_window], COLOR_PAIR(BORDER_COLOR));
    wbkgd(items[w.game_board], COLOR_PAIR(4));
    wbkgd(items[w.next_brick], COLOR_PAIR(5));
    wbkgd(items[w.score_board], COLOR_PAIR(6));

    /* do one last refresh */
    wrefresh(items[w.main_window]);

    return items;
}

/**
 * Empty game board with empty chars.
 */
void empty_window(WINDOW *w, int x, int y)
{
    for (int r=1; r<=y; r++) {
        for (int c=1; c<=x; c++) {
            mvwprintw(w, r, c, "%s", " ");
        }
    }
}

/**
 * Game play state.
 *
 * Break out of this function returns to game play state.
 */
int game_play(WINDOW *w, int play_pause)
{
    /* empty game board and reset border */
    empty_window(w, BOARD_WIDTH-2, BOARD_HEIGHT-2);

    mvwprintw(w, 10, 2, "%s", "Running");
    wrefresh(w);

    while(1) {
        switch(wgetch(stdscr)) {
            case 'h':
                /* move brick left */
                break;
            case 'l':
                /* move brick right */
                break;
            case 'j':
                /* rotate brick downwards / clockwise */
                break;
            case 'k':
                /* rotate brick upwards / counter clockwise */
                break;
            case 'p':
                /* pause game, return */
                return -1;
        }
        usleep(5000);
    }
    return -1;
}

/**
 * Game paused state
 *
 * Break out of this function returns to menu.
 *
 * Returns int
 */
int game_pause(int coords[])
{
    /* draw and get game boxes */
    WINDOW **boxes = draw_game_boxes(coords);

    /* Info texts */
    mvwprintw(boxes[w.game_board], 10, 2, "%s", "Press p to play");
    wrefresh(boxes[w.game_board]);
    mvprintw(coords[1] + BOARD_HEIGHT + 2, coords[0]+1, "Press h for help");

    while(1) {
        switch(wgetch(stdscr)) {
            case 'p':
                /* enter game play state */
                game_play(boxes[w.game_board], 1);
                /* return from play state */
                mvwprintw(boxes[w.game_board], 10, 2, "%s", "Press p to play");
                wrefresh(boxes[w.game_board]);
                break;
            case 'q':
                return -1;
        }
        usleep(5000);
    }
    return -1;
}
