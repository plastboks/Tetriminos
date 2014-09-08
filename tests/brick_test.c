/**
 * Just a silly little test file for displaying the brick
 * matrix onto stdout and running the rotate functions.
 * 
 */

#include "brick_test.h"
#include "bricks.h"

int getch(void)
{
    int ch;
    struct termios origterm, tmpterm;

    tcgetattr(STDIN_FILENO, &origterm);
    tmpterm = origterm;
    tmpterm.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &tmpterm);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &origterm);

    return ch;
}

void brick_printer(char brick[][4])
{
    int x,y;
    for (y=0; y<=3; y++) {
        printf("{");
        for (x=0; x<=3; x++) {
            printf("%d, ", brick[y][x]);
        }
        printf("}\n");
    }
    printf("\n");
}

void label_printer()
{
    printf("\n##################################");
    printf("\n#                                #");
    printf("\n#    BRICK TESTER                #");
    printf("\n#                                #");
    printf("\n# Commands:                      #");
    printf("\n# 'r' - rotate clockwise         #");
    printf("\n# 'c' - rotate counter clockwise #");
    printf("\n# 'n' - next brick               #");
    printf("\n# 'q' - exit                     #");
    printf("\n#                                #");
    printf("\n##################################\n\n");
}

int main(int argc, char *argv[]) 
{
    char ch;
    int brick_type = 0;

    label_printer();

    /* pick a brick */
    char cur_brick[4][4];
    memcpy(cur_brick, brick_digit[brick_type], sizeof(char)*4*4);
    brick_printer(cur_brick);

    do {
        ch = getch();
        switch(ch) {
            case 'r':
                printf("Rotate Clockwise\n");
                brick_rotate(cur_brick, true);
                brick_printer(cur_brick);
                break;
            case 'c':
                printf("Rotate Counter clockwise\n");
                brick_rotate(cur_brick, false);
                brick_printer(cur_brick);
                break;
            case 'n':
                printf("New brick\n");
                memcpy(cur_brick, brick_digit[++brick_type % 6], sizeof(char)*4*4);
                brick_printer(cur_brick);
                break;
        }
    } while(ch != 'q');

    printf("Bye\n");
    return(0);
}
