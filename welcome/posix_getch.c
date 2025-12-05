#include "posix_getch.h"
#ifndef _WIN32
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

int posix_getch(void) {
    struct termios oldt, newt;
    int ch;

    if (tcgetattr(STDIN_FILENO, &oldt) == -1) {
        return EOF;
    }
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    newt.c_cc[VMIN] = 1;
    newt.c_cc[VTIME] = 0;

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) == -1) {
        return EOF;
    }

    ch = getchar();

    /* restore terminal */
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}
#endif
