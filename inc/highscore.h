/*
 * Tetriminos high score header file
 *
 * @filename: highscore.h
 *
 * @version: 0.0.1
 *
 * @date: 2014-09-19
 *
 * @description: Tetriminos high score header file.
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

#include "config.h"

struct stack_entry {
    char name[3]; /* YES!, only three char old style high score names */
    unsigned int score;
};

struct highscore_stack {
    struct stack_entry entry[10]; /* only 10 last entries */
};

int read_highscores();
int init_highscores(struct highscore_stack *stack);
int load_highscore(struct highscore_stack *stack);
int write_highscore(/*struct highscore_stack *stack*/);
