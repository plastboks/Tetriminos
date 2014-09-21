/*
 * Tetriminos high score source file
 *
 * @filename: highscore.c
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-19
 *
 * @description: Tetriminos high score source file
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

#include "highscore.h"

void get_highscore_file_path(char file[512])
{
    char path[512];
    config_path(path);

    snprintf(file, 512, "%s/highscore.dat", path);
}

int read_highscores()
{
	FILE *highscore_file;
    char file_path[512];
    get_highscore_file_path(file_path);

	if((highscore_file = fopen(file_path, "r")) == NULL)
        return -1;

	fclose(highscore_file);
	return 0;
}

int write_highscore(struct highscore_stack *stack)
{
	FILE *highscore_file;
    char file_path[512];
    get_highscore_file_path(file_path);

	if((highscore_file = fopen(file_path, "w")) == NULL)
        // do nothing for now...

	fclose(highscore_file);
	return 0;
}
