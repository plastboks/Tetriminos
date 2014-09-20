/*
 * Tetriminos main source file.
 *
 * @filename: tetriminos.c
 *
 * @version: 0.0.1
 *
 * @date: 2013-12-26
 *
 * @description: Tetriminos main program file
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

#include "config.h"
#include "colors.h"
#include "structs.h"
#include "game.h"
#include "screens.h"

int main(int argc, char *argv[]) 
{
    WINDOW *base_win;
    int life = 1;
    int coords[2];
    int old_coords[2];
    int screen = -1;

    /* run config */
    config_setup();

    /* setup screen and colors */
    screen_setup();
    setup_colors();

    if (SPLASH) {
        screen_coord_update(c.splash_box_size, coords, old_coords);
        base_win = screen_newwin(c.splash_box_size, coords);
        screen_welcome(coords, true);
        sleep(1);
    }

    do {
        switch(screen) {
            case 0: /* new game */
                screen_coord_update(c.game_box_size, coords, old_coords);
                screen = game_pause(coords, 1);
                break;
            case 1: /* continue game */
                screen_coord_update(c.game_box_size, coords, old_coords);
                screen = game_pause(coords, -1);
                break;
            case -1:
            case 2: /* high scores */
                screen_coord_update(c.menu_box_size, coords, old_coords);
                screen = screen_menu(c.menu_box_size, coords);
                break;
            case 3: /* about */
                screen_coord_update(c.about_box_size, coords, old_coords);
                screen = screen_about(c.about_box_size, coords, texts.about);
                break;
            case 4: /* quit */
                life = 0;
                break;
        }
        /**
         * Redraw window if resized.
         */
        /* This causes some problems as of now, leave it out for later.
        if ((old_coords[1] != LINES) || (old_coords[0] != COLS)) {
            screen_coord_update(c.box_size, coords, old_coords);
            screen_destroy(base_win);
            base_win = screen_newwin(c.box_size, coords);
        }
        */
    } while (life == 1);

    screen_destroy(base_win);
    screen_end();
    return 0;
}
