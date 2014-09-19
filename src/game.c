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
#include "movements.h"
#include "stack.h"
#include "config.h"

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
 * Setup game data for a new game.
 */
void setup_gamedata(WINDOW **boxes, game_data *gd)
{
    /* empty stack */
    empty_stack(gd->stack);

    /* reset play brick position */
    reset_brick_pos(gd->play_brick_pos);

    /* generate next brick type, and draw it in the next brick box */
    gd->next_type = get_new_brick(gd->next_brick);
    update_next_brick(boxes[w.next_brick],
                      gd->next_type,
                      gd->next_brick);

    /* generate a play brick, and draw it to the game board */
    gd->play_type = get_new_brick(gd->play_brick);
    add_new_brick(boxes[w.game_board],
                  gd->play_type,
                  gd->play_brick_pos,
                  gd->play_brick);

    gd->bricks = 1;
    gd->lines = 0;
    gd->level = 1;
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
 * Get a new brick, picked random.
 */
char get_new_brick(char brick[4][4])
{
    int r = rand() % 7;
    memcpy(brick, brick_digit[r], sizeof(char)*4*4);
    return brick_type_char(r);
}

/**
 * Set initial brick position.
 */
void reset_brick_pos(int play_brick_pos[])
{
    play_brick_pos[0] = 1;
    play_brick_pos[1] = 7; /* must be an odd number */
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
                mvwprintw(w, y+play_brick_pos[0], (x*2)+play_brick_pos[1], "%s", "  ");
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

int level_up(int *lines)
{
    if (*lines < 20 && *lines > 0) return 1;        /* 1 -> 19 */
    if (*lines < 60 && *lines >= 20) return 2;      /* 20 -> 59 */
    if (*lines < 120 && *lines >= 60) return 3;     /* 60 -> 119 */
    if (*lines < 200 && *lines >= 120) return 4;    /* 120 -> 199 */
    if (*lines < 250 && *lines >= 200) return 5;    /* 200 -> 249 */
    if (*lines < 300 && *lines >= 250) return 6;    /* 250 -> 299 */
    if (*lines < 350 && *lines >= 300) return 7;    /* 300 -> 349 */
    if (*lines < 400 && *lines >= 350) return 8;    /* 350 -> 399 */
    if (*lines > 400) return 9;                     /* 400 -> ... */

    return 1;
}


/***********************
 * GAME STATE HANDLERS *
 ***********************/
int game_play(WINDOW **boxes, int new_game)
{
    /* setup game data */
    if (new_game > 0) {
        setup_gamedata(boxes, &gd);
    }

    /* game data */
    int interval = 0;
    short skip_beat = 0;
    short gravity_moves = 0;

    /* update score board */
    update_score_board(boxes[w.score_board], &gd.lines, &gd.bricks, &gd.level);

    while(1) {
        /* switch getch(), supports vim mode, wasd mode and arrow keys */
        switch(wgetch(stdscr)) {
            case 'w':
            case 'k':
            case KEY_UP:
                move_brick_rotate(gd.play_brick_pos, gd.play_brick, gd.stack);
                empty_but_stack(boxes[w.game_board], gd.stack);
                refresh_brick(boxes[w.game_board],
                              gd.play_type,
                              gd.play_brick_pos,
                              gd.play_brick);
                break;
            case 's':
            case 'j':
            case KEY_DOWN:
                skip_beat = 1;
                break;
            case 'a':
            case 'h':
            case KEY_LEFT:
                move_brick_left(gd.play_brick_pos, gd.play_brick, gd.stack);
                empty_but_stack(boxes[w.game_board], gd.stack);
                refresh_brick(boxes[w.game_board],
                              gd.play_type,
                              gd.play_brick_pos,
                              gd.play_brick);
                break;
            case 'd':
            case 'l':
            case KEY_RIGHT:
                move_brick_right(gd.play_brick_pos, gd.play_brick, gd.stack);
                empty_but_stack(boxes[w.game_board], gd.stack);
                refresh_brick(boxes[w.game_board],
                              gd.play_type,
                              gd.play_brick_pos,
                              gd.play_brick);
                break;
            case 'q':
                return -2;
            case 'p':
                /* pause game, return */
                return -1;
        }

        /* do gravity until brick hits something */
        interval++;
        if ((interval > 100-(gd.level*gd.level)) || (skip_beat > 0)) {
            interval = skip_beat = 0;

            /* check if possible to move, else setup new brick */
            if (move_brick_gravity(gd.play_brick_pos, gd.play_brick, gd.stack) > 0) {
                gravity_moves++;
                empty_but_stack(boxes[w.game_board], gd.stack);
                refresh_brick(boxes[w.game_board],
                              gd.play_type,
                              gd.play_brick_pos,
                              gd.play_brick);
            } else {
                /* if brick cannot move anymore */
                if (gravity_moves == 0) return 1;

                /* commit play brick */
                push_brick(gd.play_type, gd.play_brick_pos, gd.play_brick, gd.stack);
                reset_brick_pos(gd.play_brick_pos);

                /* copy 'next brick' to 'play brick' */
                memcpy(gd.play_brick, gd.next_brick, sizeof(char)*4*4);
                gd.play_type = gd.next_type;
                add_new_brick(boxes[w.game_board],
                              gd.play_type,
                              gd.play_brick_pos,
                              gd.play_brick);

                /* get new next brick */
                gd.bricks++;
                gd.next_type = get_new_brick(gd.next_brick);
                update_next_brick(boxes[w.next_brick], gd.next_type, gd.next_brick);

                /* redraw stack */
                gd.lines += check_stack(gd.stack);
                draw_stack(boxes[w.game_board], gd.stack);

                /* level up */
                gd.level = level_up(&gd.lines);

                /* update score board */
                update_score_board(boxes[w.score_board], &gd.lines, &gd.bricks, &gd.level);

                /* reset brick gravity_moves */
                gravity_moves = 0;
            }
        }

        /* let the CPU rest some, before next iteration */
        usleep(5000);
    }

    /* Break out of this function returns to game play state. */
    return -1;
}

int game_pause(int coords[], int game_state)
{
    /* draw and get game boxes */
    WINDOW **boxes = draw_game_boxes(coords);

    /* Info texts */
    mvwprintw(boxes[w.game_board], 10, 2, "%s", "Press p to play");
    wrefresh(boxes[w.game_board]);
    mvprintw(coords[1] + BOARD_HEIGHT + 2, coords[0]+1, "Press q to quit");

    while(1) {
        switch(wgetch(stdscr)) {
            case 'p':
                /* enter game play state */
                game_state = game_play(boxes, game_state);

                /* user has quited the ongoing game, push to menu */
                if (game_state == -2) return -1;
                /* game has ended, do high score routine */
                if (game_state == 1) return -1;
                /* return from play state, aka pause mode */
                mvwprintw(boxes[w.game_board], 10, 6, "%s", "- PAUSE -");
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
