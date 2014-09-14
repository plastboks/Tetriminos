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
#include "colors.h"
#include "bricks.h"
#include "stack.h"
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
    wrefresh(w);
}

/**
 * Get a new brick, picked random.
 */
char get_new_brick(char brick[4][4])
{
    int r = rand() % 7;
    memcpy(brick, brick_digit[r], sizeof(char)*4*4);
    return brick_type_char(r);
}

/**
 * Convert brick type integer to brick type char
 */
char brick_type_char(int brick_type)
{
    switch(brick_type) {
        case 0:
              return 'i';
        case 1:
              return 'j';
        case 2:
              return 'l';
        case 3:
              return 'o';
        case 4:
              return 's';
        case 5:
              return 't';
        default:
              return 'z';
    }
}

/**
 * Return brick color based on type
 */
int get_brick_color(char brick_type) {
    switch(brick_type) {
        case 'i': /* I */
            return COLOR_CYAN_BG;
        case 'j': /* J */
            return  COLOR_BLUE_BG;
        case 'l': /* L */
            return COLOR_WHITE_BG;
        case 'o': /* O */
            return COLOR_YELLOW_BG;
        case 's': /* S */
            return COLOR_GREEN_BG;
        case 't': /* T */
            return COLOR_MAGENTA_BG;
        default: /* Z */
            return COLOR_RED_BG;
    }
}

/**
 * Set initial brick position.
 */
void reset_brick_pos(int play_brick_pos[])
{
    play_brick_pos[0] = 1;
    play_brick_pos[1] = 7;
}


/*****************
 * BRICK DRAWERS *
 *****************/
void add_new_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4])
{
    int color = get_brick_color(brick_type);

    /* empty game board */
    empty_window(w, BOARD_WIDTH-2, BOARD_HEIGHT-2);

    wattron(w, COLOR_PAIR(color));

    for (int y=0; y<3; y++) {
        for (int x=0; x<4; x++) {
            if (brick[y][x] > 0) {
                /* args: window, column, row ...*/
                mvwprintw(w, y+play_brick_pos[0], (x*2)+play_brick_pos[1], "%s", "  ");
            }
        }
    }

    wattroff(w, COLOR_PAIR(color));
    wrefresh(w);
}

void refresh_brick(WINDOW *w, char brick_type, int play_brick_pos[2], char brick[4][4])
{
    int color = get_brick_color(brick_type);

    wattron(w, COLOR_PAIR(color));

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (brick[y][x] > 0) {
                /* args: window, column, row ...*/
                mvwprintw(w, y+play_brick_pos[0], (x*2)+play_brick_pos[1], "%s", "  ");
            }
        }
    }

    wattroff(w, COLOR_PAIR(color));
    wrefresh(w);
}

void draw_next_brick(WINDOW *w, char brick_type, char brick[4][4])
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


/****************
 * BRICK MOVERS *
 ****************/
int move_brick_left(int play_brick_pos[2], char play_brick[4][4], char stack[][10])
{
    /* a = play brick horizontal leftmost a point */
    int a = 3;
    int sx, sy;

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (play_brick[y][x] > 0) {
                if (x < a)
                    a = x;
                sx = ((play_brick_pos[1]+1)/2)+x-1;
                sy = (20-play_brick_pos[0])-y;
                if (stack[sy][sx-1] > 0)
                    return -1;
            }
        }
    }

    /* move only if brick does not move outside board */
    if (play_brick_pos[1]+a > 1) {
        play_brick_pos[1]-=2;
        return 1;
    }

    return -1;
}

int move_brick_right(int play_brick_pos[2], char play_brick[4][4], char stack[][10])
{
    /* b = play brick horizontal rightmost a point */
    int b = 0;
    int sx, sy;

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (play_brick[y][x] > 0) {
                if (x > b)
                    b = x;
                sx = ((play_brick_pos[1]+1)/2)+x-1;
                sy = (20-play_brick_pos[0])-y;
                if (stack[sy][sx+1] > 0)
                    return -1;
            }
        }
    }

    /* move only if brick does not move outside board */
    if (play_brick_pos[1]+b < BOARD_WIDTH-5) {
        play_brick_pos[1]+=2;
        return 1;
    }

    return -1;
}

int move_brick_gravity(int play_brick_pos[2], char play_brick[4][4], char stack[][10])
{
    /* h = play brick vertical bottommost point */
    int h = 0;
    int sx, sy;

    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (play_brick[y][x] > 0) {
                if (y > h)
                    h = y;
                sx = ((play_brick_pos[1]+1)/2)+x-1;
                sy = (20-play_brick_pos[0])-y;
                if (stack[sy-1][sx] > 0)
                    return -1;
            }
        }
    }

    if (play_brick_pos[0]+h < BOARD_HEIGHT-2) {
        play_brick_pos[0]++;
        return 1;
    }

    return -1;
}


/***********************
 * GAME STATE HANDLERS *
 ***********************/
int game_play(WINDOW **boxes, int play_pause)
{
    /* stack, static for now */
    char stack[20][10];

    /* bricks */
    char play_brick[4][4];
    char next_brick[4][4];
    int play_brick_pos[2];
    char play_type;
    char next_type;

    /* game data */
    int level = 1;
    int interval = 0;
    int skip_beat = 0;

    /* empty stack if new game */
    empty_stack(stack);

    /* set brick pos */
    reset_brick_pos(play_brick_pos);

    /* generate next brick type, and draw it in the next brick box */
    next_type = get_new_brick(next_brick);
    draw_next_brick(boxes[w.next_brick], next_type, next_brick);

    /* generate a play brick, and draw it to the game board */
    play_type = get_new_brick(play_brick);
    add_new_brick(boxes[w.game_board], play_type, play_brick_pos, play_brick);

    while(1) {
        /* switch getch(), supports vim mode, wasd mode and arrow keys */
        switch(wgetch(stdscr)) {
            case 'w':
            case 'k':
            case KEY_UP:
                /* rotate brick upwards / clockwise */
                brick_rotate(play_brick, true);
                empty_but_stack(boxes[w.game_board], stack);
                refresh_brick(boxes[w.game_board], play_type, play_brick_pos, play_brick);
                break;
            case 's':
            case 'j':
            case KEY_DOWN:
                skip_beat = 1;
                break;
            case 'a':
            case 'h':
            case KEY_LEFT:
                move_brick_left(play_brick_pos, play_brick, stack);
                empty_but_stack(boxes[w.game_board], stack);
                refresh_brick(boxes[w.game_board], play_type, play_brick_pos, play_brick);
                break;
            case 'd':
            case 'l':
            case KEY_RIGHT:
                move_brick_right(play_brick_pos, play_brick, stack);
                empty_but_stack(boxes[w.game_board], stack);
                refresh_brick(boxes[w.game_board], play_type, play_brick_pos, play_brick);
                break;
            case 'q':
            case 'p':
                /* pause game, return */
                return -1;
        }

        /* do gravity until brick hits something */
        interval++;
        if ((interval > 100-(level*level)) || (skip_beat > 0)) {
            interval = skip_beat = 0;

            /* check if possible to move, else setup new brick */
            if (move_brick_gravity(play_brick_pos, play_brick, stack) > 0) {
                empty_but_stack(boxes[w.game_board], stack);
                refresh_brick(boxes[w.game_board], play_type, play_brick_pos, play_brick);
            } else {
                push_brick(play_type, play_brick_pos, play_brick, stack);
                reset_brick_pos(play_brick_pos);
                memcpy(play_brick, next_brick, sizeof(char)*4*4);
                play_type = next_type;
                add_new_brick(boxes[w.game_board], play_type, play_brick_pos, play_brick);

                /* get new next brick */
                next_type = get_new_brick(next_brick);
                draw_next_brick(boxes[w.next_brick], next_type, next_brick);

                /* redraw stack */
                draw_stack(boxes[w.game_board], stack);
            }
        }

        /* let the CPU rest some, before next iteration */
        usleep(5000);
    }

    /* Break out of this function returns to game play state. */
    return -1;
}

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
                game_play(boxes, 1);
                /* return from play state */
                mvwprintw(boxes[w.game_board], 10, 2, "%s", "Press p to play");
                wrefresh(boxes[w.game_board]);
                break;
            case 'q':
                return -1;
        }
        usleep(5000);
    }
    /* Break out of this function returns to menu. */
    return -1;
}
