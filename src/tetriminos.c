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
#include "game.h"
#include "screens.h"
#include "texts.h"

int main(int argc, char *argv[]) 
{
    WINDOW *base_win;
    int life = 1;
    int screen = -1;

    /* coordinates center of screen */
    coords c;

    /* various box sizes */
    sizes s;

    /* run config */
    config_setup();

    /* setup screen and colors */
    screen_setup();
    setup_colors();

    /* initialize box sizes */
    screen_init_sizes(&s);

    if (SPLASH) {
        screen_coord_update(&c, s.splash);
        base_win = screen_newwin(c, s.splash);
        screen_welcome(c, true);
        sleep(1);
    }

    do {
        switch(screen) {
            case 0: /* new game */
                screen_coord_update(&c, s.game);
                screen = game_pause(c.cur.x, c.cur.y, 1);
                break;
            case 1: /* continue game */
                screen_coord_update(&c, s.game);
                screen = game_pause(c.cur.x, c.cur.y, -1);
                break;
            case 2: /* high scores */
                screen_coord_update(&c, s.highscores);
                screen = screen_highscores(c, s.highscores);
                break;
            case 3: /* about */
                screen_coord_update(&c, s.about);
                screen = screen_about(c, s.about, texts.about);
                break;
            case 4: /* quit */
                life = 0;
                break;
            default: /* default */
                screen_coord_update(&c, s.menu);
                screen = screen_menu(c, s.menu);
                break;
        }
    } while (life == 1);

    screen_destroy(base_win);
    screen_end();
    return 0;
}
