/*
 * Tetriminos config source code file
 *
 * @filename: drawers.c
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-19
 *
 * @description: Tetriminos brick drawer source file
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

#include "drawers.h"

/**
 * Draw the game window and boxes
 *
 * int coords defines the center of the screens, set by the
 * applications init functions.
 *
 * Returns WINDOW
 */
WINDOW **draw_game_boxes(int x, int y)
{
    WINDOW **items;

    w.main_window = 0;
    w.game_board = 1;
    w.next_brick = 2;
    w.score_board = 3;

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
    mvprintw(y-1, x+9, "- Tetriminos -");
    items[w.main_window] = newwin(mw_size[0], mw_size[1], y, x);
    box(items[w.main_window], ACS_VLINE, ACS_HLINE);

    /* game window */
    items[w.game_board]=subwin(items[w.main_window],
                               gb_size[0], gb_size[1],
                               y+1, x+1);
    box(items[w.game_board], ACS_VLINE, ACS_HLINE);

    /* next brick */
    mvprintw(y+2, x + BOARD_WIDTH + 2, "Next brick");
    items[w.next_brick]=subwin(items[w.main_window],
                               nb_size[0], nb_size[1],
                               y+3, x + BOARD_WIDTH + 2);
    box(items[w.next_brick], ACS_VLINE, ACS_HLINE);

    /* scores */
    mvprintw(y+10, x + BOARD_WIDTH + 2, "Score");
    items[w.score_board]=subwin(items[w.main_window],
                                      hs_size[0], hs_size[1],
                                      y+11, x + BOARD_WIDTH + 2);
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
    wrefresh(w);
}

/**
 * Clean game board, but not stack
 */
void empty_but_stack(WINDOW *w, char stack[][10])
{
    for (int y=0; y<20; y++) {
        for (int x=0; x<10; x++) {
            if (stack[y][x] == 0) {
                mvwprintw(w, 20-y, (x*2)+1, "%s", "  ");
            }
        }
    }

    wrefresh(w);
}

/**
 * Add new brick to board, and redraw.
 */
void add_new_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4])
{
    int color = get_brick_color(brick_type);

    /* empty game board */
    empty_window(w, BOARD_WIDTH-2, BOARD_HEIGHT-2);

    wattron(w, COLOR_PAIR(color));

    for (int y=0; y<3; y++) {
        for (int x=0; x<4; x++) {
            if (brick[y][x] > 0) {
                mvwprintw(w, y+play_brick_pos[0], (x*2)+play_brick_pos[1], "%s", "  ");
            }
        }
    }

    wattroff(w, COLOR_PAIR(color));
    wrefresh(w);
}

/**
 * Refresh brick
 */
void refresh_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4])
{
    int color = get_brick_color(brick_type);

    wattron(w, COLOR_PAIR(color));

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (brick[y][x] > 0) {
                mvwprintw(w, y+play_brick_pos[0], (x*2)+play_brick_pos[1], "%s", "  ");
            }
        }
    }

    wattroff(w, COLOR_PAIR(color));
    wrefresh(w);
}

/**
 * Update and redraw next brick window
 */
void update_next_brick(WINDOW *w, char brick_type, char brick[4][4])
{
    int color = get_brick_color(brick_type);

    empty_window(w, 8, 3);
    wattron(w, COLOR_PAIR(color));

    for (int y=0; y<3; y++) {
        for (int x=0; x<4; x++) {
            if (brick[y][x] > 0) {
                mvwprintw(w, y+1, (x*2)+1, "%s", "  ");
            }
        }
    }

    wattroff(w, COLOR_PAIR(color));
    wrefresh(w);
}

/**
 * Update and redraw score board
 */
void update_score_board(WINDOW *w, int *lines, int *bricks, int *level)
{
    empty_window(w, 8, 3);

    wattron(w, COLOR_PAIR(COLOR_BLACK_BG));
    mvwprintw(w, 1, 1, "br: %d", *bricks);
    mvwprintw(w, 2, 1, "ln: %d", *lines);
    mvwprintw(w, 3, 1, "lv: %d", *level);
    wattroff(w, COLOR_PAIR(COLOR_BLACK_BG));

    wrefresh(w);
}

/**
 * Draw stack on game board
 */
void draw_stack(WINDOW *w, char stack[][10])
{
    for (int y=0; y<20; y++) {
        for (int x=0; x<10; x++) {
            if (stack[y][x] > 0) {
                int color = get_brick_color(stack[y][x]);
                wattron(w, COLOR_PAIR(color));
                mvwprintw(w, 20-y, (x*2)+1, "%s", "  ");
                wattroff(w, COLOR_PAIR(color));
            }
        }
    }

    wrefresh(w);
}
