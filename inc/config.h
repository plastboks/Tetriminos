/*
 * Tetriminos config header file
 *
 * @filename: config.h
 *
 * @version: 0.0.4
 *
 * @date: 2013-12-17
 *
 * @description: Tetriminos functions header file
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

#define VERSION 0.02
#define SPLASH true

/**
 * Board dimensions is defined as follow:
 * Two characters make a horizontal brick.
 * Therefor width is (10*2) plus 2 for padding (border).
 * Height is standard 20 char height plus 2 for padding (border).
 *
 * BOARD SIZE CANNOT BE CHANGED AT THE MOMENT.
 * THIS WILL CAUSE A STACK OVERFLOW.
 */
#define BOARD_WIDTH 22
#define BOARD_HEIGHT 22
#define BORDER_COLOR 2

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

void config_setup();
void config_path(char path[512]);
void config_create_dir(char path[512]);
