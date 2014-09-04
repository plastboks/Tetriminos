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
    int main_window = 0;
    int game_board = 1;
    int next_brick = 2;
    int high_score = 3;

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

    items[main_window] = newwin(mw_size[0], mw_size[1], coords[1], coords[0]);
    box(items[main_window], ACS_VLINE, ACS_HLINE);

    /* game window */
    items[game_board]=subwin(items[main_window], gb_size[0], gb_size[1], coords[1]+1, coords[0]+1);
    box(items[game_board], ACS_VLINE, ACS_HLINE);

    /* next brick */
    items[next_brick]=subwin(items[main_window], nb_size[0], nb_size[1], coords[1]+2, coords[0]+22);
    box(items[next_brick], ACS_VLINE, ACS_HLINE);

    /* scores */
    items[high_score]=subwin(items[main_window], hs_size[0], hs_size[1], coords[1]+11, coords[0]+22);
    box(items[high_score], ACS_VLINE, ACS_HLINE);

    /* colors */
    wbkgd(items[main_window], COLOR_PAIR(BORDER_COLOR));
    wbkgd(items[game_board], COLOR_PAIR(4));
    wbkgd(items[next_brick], COLOR_PAIR(5));
    wbkgd(items[high_score], COLOR_PAIR(6));

    /* static texts */
    mvprintw(coords[1]-1, coords[0]+9, "- Tetriminos -");
    mvprintw(coords[1]+1, coords[0]+22, "Next brick");
    mvprintw(coords[1]+10, coords[0]+22, "Score");

    /* do one last refresh */
    wrefresh(items[main_window]);

    return items;
}

/**
 * Welcome screen
 *
 * @coords          int array of coordinates.
 *
 * Returns int
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
