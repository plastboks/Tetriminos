Tetriminos
==========
Tetriminos is a small C and ncurses implementation of the Tetris game.


About
=====
This small game gets a lot of inspiration from the Ctris game at http://www.hackl.dhs.org/ctris/.
Tetriminos will try to stay as true to the original game as possible (meaning Alexey Pajitnovs 1984 Tetris).


Features
========
Part of this applications purpose is to teach the author some best practices in writing a C ncurses app. Therefor this app might have some unnecessary features just for the heck of it.
A short list of features follows:
  * Fully configurable trough config files.
  * High scores (saved in a SQL database (SQLite)).
  * Pause and stop game, continue upon start.


Game play
=========
Small list of game play features follows:
  * Level increment as score increments.
  * Gravity with chain reactions (see section four one the wiki page).
  * Configurable start level (easy, medium, hard).
  * Small box indicating next block.


Compiling
=========
Compiling this program is simply done by: `make`.


Install
==========
No global install routines have been made at this point. After the `make` run, a binary 'mousing' is created in the root folder of this project. Move binary to wanted destination.
In the finishing stages of this app it might be possible that a `make install` routine will be made.
Make sure you have the necessary dependencies as listed below.


Dependencies
============
  * ncurses
  * SQLite ? (or save data in a simple text file)
  * libconfig ? (or make a custom parser)


Branches
========
In the beginning of the project things were so little and experimental, so there was no need for multiple branches.
The develop branch (default), will be a feature and develop branch pushing this project forward. The develop branch might be in a none-compiling state at times.
I will strive to make sure the master branch will be stable at all times.


Sources and inspiration
=======================
  * [Wikipage](https://en.wikipedia.org/wiki/Tetris)
  * [ncurses tutorial](http://www.tldp.org/HOWTO/NCURSES-Programming-HOWTO/windows.html)
  * [ctris](http://www.hackl.dhs.org/ctris/)
  * [vitetris](http://www.victornils.net/tetris)
