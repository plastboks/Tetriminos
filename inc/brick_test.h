/**
 * Just a silly little test file for displaying the brick
 * matrix onto stdout and running the rotate functions.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int getch(void);
void brick_printer(char brick[][4]);
int main(int argc, char *argv[]);
