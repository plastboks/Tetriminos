Tetriminos
==========
Tetriminos is a small C and ncurses implementation of the Tetris game.
![main_screenshot](screenshots/gameplay.2014-09-16.png)

About
=====
This small game gets a lot of inspiration from the Ctris game at http://www.hackl.dhs.org/ctris/.
Tetriminos will try to stay as true to the original game as possible (meaning Alexey Pajitnovs 1984 Tetris).

Docker
======
Now with a docker automated build. See [the registry](https://registry.hub.docker.com/u/plastboks/tetriminos/) for details.
* change directory into `./docker`
* run: `build` (need superuser)
* run: `run` (need superuser)

Features
========
Part of this applications purpose is to teach the author some best practices in writing a C ncurses app. Therefor this app might have some unnecessary features just for the heck of it.
A short list of features follows:
  * Fully configurable trough config files.
  * High scores.
  * Pause and stop game, continue upon start.


Game play
=========
Small list of game play features follows:
  * Level increment as score increments.
  * Gravity with chain reactions.
  * Configurable start level (easy, medium, hard).
  * Small box indicating next block.


Compiling and running
=====================
Compiling this program is simply done by: 
  * `make`
  * `./tetriminos`


Testing / Debugging
===================
Tetriminos does not fully integrate a test framework like [Check](http://check.sourceforge.net/) or [CuTest](http://cutest.sourceforge.net/). Hopefully this will get done in the future.
For now some small ad hoc programs have been created for this purpose. They can be found in the Makefile file.
  * `make brick_test` and run `brick_test`


Install
==========
No global install routines have been made at this point. After the `make` run, a binary 'mousing' is created in the root folder of this project. Move binary to wanted destination.
In the finishing stages of this app it might be possible that a `make install` routine will be made.
Make sure you have the necessary dependencies as listed below.


Dependencies
============
  * ncurses


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
  * [libini](http://sourceforge.net/projects/libini/)
  * [SO question regarding parsers](http://stackoverflow.com/questions/1417765/parse-config-file-in-c-c)
