/*
 * Tetriminos color definition file
 *
 * @filename: colors.h
 *
 * @version: 0.0.1
 *
 * @date: 2013-12-26
 *
 * @description: Tetriminos color header file
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

#pragma once

#define COLOR_BLACK_FG 1
#define COLOR_GREEN_FG 2
#define COLOR_WHITE_FG 3
#define COLOR_RED_FG 4 
#define COLOR_CYAN_FG 5
#define COLOR_MAGENTA_FG 6
#define COLOR_BLUE_FG 7
#define COLOR_YELLOW_FG 8

#define COLOR_BLACK_BG 9
#define COLOR_GREEN_BG 10
#define COLOR_WHITE_BG 11
#define COLOR_RED_BG 12 
#define COLOR_CYAN_BG 13
#define COLOR_MAGENTA_BG 14
#define COLOR_BLUE_BG 15
#define COLOR_YELLOW_BG 16

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void setup_colors();
char brick_type_char(int brick_type);
int get_brick_color(char brick_type);
