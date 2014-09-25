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
#include "drawers.h"
#include "stack.h"
#include "config.h"


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
int game_play(WINDOW **boxes, game_data gd, int new_game)
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

int game_pause(int x, int y, int game_state)
{
    /* draw and get game boxes */
    WINDOW **boxes = draw_game_boxes(x, y);

    /* globally defined game data... */
    game_data gd;

    /* Info texts */
    mvwprintw(boxes[w.game_board], 10, 2, "%s", "Press p to play");
    wrefresh(boxes[w.game_board]);
    mvprintw(y + BOARD_HEIGHT + 2, x+1, "Press q to quit");

    while(1) {
        switch(wgetch(stdscr)) {
            case 'p':
                /* enter game play state */
                game_state = game_play(boxes, gd, game_state);

                /* user has quited the ongoing game, push to menu */
                if (game_state == -2) return -1;
                /* game has ended, do */
                if (game_state == 1) return -2;
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
