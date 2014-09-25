/*
 * Tetriminos screen header file
 *
 * @filename: screens.h
 *
 * @version: 0.0.1
 *
 * @date: 2013-12-26
 *
 * @description: Tetriminos main screen header file
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Tetriminos.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <fcntl.h>

struct point {
    int x;
    int y;
};

struct size {
    int height;
    int width;
};

typedef struct {
    struct size splash;
    struct size menu;
    struct size about;
    struct size game;
    struct size highscores;
    struct size gameover;
} sizes;

typedef struct {
    struct point cur;
    struct point old;
} coords;

WINDOW *screen_newwin(coords c, struct size s);
WINDOW **draw_main_menu(coords c);

void screen_init_sizes(sizes *s);
void screen_setup();
void screen_coord_update(coords *c, struct size s);
void screen_destroy(WINDOW *local_win);
void screen_end();

int scroll_main_menu(WINDOW **items, int count);
int screen_menu(coords c, struct size s);
int screen_highscores(coords c, struct size s);
int screen_about(coords c, struct size s, char text[][50]);
int screen_gameover(coords c, struct size s);
int screen_welcome(coords c, bool effect);
