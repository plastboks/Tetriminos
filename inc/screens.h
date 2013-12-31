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
#define _BSD_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <fcntl.h>

WINDOW *screen_newwin(int box_size[], int coords[]);
void screen_destroy(WINDOW *local_win);
void screen_setup();
void screen_colors();
void screen_coord_update(int box_size[], int coords[], int old_coords[]);
void screen_end();

void screen_welcome(int coords[], bool effect);
void screen_menu(int coords[]);
