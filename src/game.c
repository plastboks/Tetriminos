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
 * Draw the game window
 *
 * @coords      int array coordinates.
 *
 * Returns WINDOW
 */
WINDOW **draw_game_boxes(int coords[])
{
    WINDOW **items;

    /* main window size */
    int mw_size[2] = {20, 34};
    /* game board size */
    int gb_size[2] = {18, 20};
    /* next brick size */
    int nb_size[2] = {5, 10};
    /* high score size */
    int hs_size[2] = {5, 10};

    items = (WINDOW **)malloc(9 * sizeof(WINDOW *));
    erase();
    refresh();

    items[w.main_window] = newwin(mw_size[0], mw_size[1], coords[1], coords[0]);
    box(items[w.main_window], ACS_VLINE, ACS_HLINE);

    /* game window */
    items[w.game_board]=subwin(items[w.main_window], gb_size[0], gb_size[1], coords[1]+1, coords[0]+1);
    box(items[w.game_board], ACS_VLINE, ACS_HLINE);

    /* next brick */
    items[w.next_brick]=subwin(items[w.main_window], nb_size[0], nb_size[1], coords[1]+2, coords[0]+22);
    box(items[w.next_brick], ACS_VLINE, ACS_HLINE);

    /* scores */
    items[w.score_board]=subwin(items[w.main_window], hs_size[0], hs_size[1], coords[1]+11, coords[0]+22);
    box(items[w.score_board], ACS_VLINE, ACS_HLINE);

    /* colors */
    wbkgd(items[w.main_window], COLOR_PAIR(BORDER_COLOR));
    wbkgd(items[w.game_board], COLOR_PAIR(4));
    wbkgd(items[w.next_brick], COLOR_PAIR(5));
    wbkgd(items[w.score_board], COLOR_PAIR(6));

    /* static texts */
    mvprintw(coords[1]-1, coords[0]+9, "- Tetriminos -");
    mvprintw(coords[1]+1, coords[0]+22, "Next brick");
    mvprintw(coords[1]+10, coords[0]+22, "Score");

    /* do one last refresh */
    wrefresh(items[w.main_window]);

    return items;
}

/**
 * Welcome screen
 *
 * @coords          int array of coordinates.
 *
 * Returns int
 */
int game_switch(int box_size[], int coords[])
{

    WINDOW **boxes = draw_game_boxes(coords);

    mvwprintw(boxes[w.game_board], 8, 2, "%s", "Press p to play");
    wrefresh(boxes[w.game_board]);

    mvprintw(coords[1]+20, coords[0]+1, "Press q to go back");

    while(1) {
        switch(wgetch(stdscr)) {
            case 'p':
                // play / pause
                break;
            case 'q':
                return -1;
        }
        usleep(5000);
    }

    return -1;
}
