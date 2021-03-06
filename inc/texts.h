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

struct {
    char about[10][50];
} texts = {
    { /*about text */
        {"Tetriminos is a Tetris clone made by"},
        {"Plastboks."},
        {"Tetriminos source code can be viewed"},
        {"https://github.com/plastboks/Tetriminos"},
        {""},
        {"Tetriminos is licensed under GPL 2."}
    }
};
