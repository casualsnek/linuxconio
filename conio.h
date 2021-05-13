#ifndef CONIO_H
#define CONIO_H

#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define cprintf printf
#define cscanf scanf
#define cgets gets

#define CLEAR "\x1b[2J"
#define SET11 "\x1b[1;1f"
#define CURSOR_UP "\x1b[1A"
#define ERASE_LINE "\x1b[2K"
#define BLINK_SLOW "\x1b[5m"
#define BLINK_RAPID "\x1b[6m"
#define CC_CLEAR "\x1b[0m"

#define BLACK "\x1b[30m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define WHITE "\x1b[37m"

#define IBLACK "\x1b[30;1m"
#define IRED "\x1b[31;1m"
#define IGREEN "\x1b[32;1m"
#define IYELLOW "\x1b[33;1m"
#define IBLUE "\x1b[34;1m"
#define IMAGENTA "\x1b[35;1m"
#define ICYAN "\x1b[36;1m"
#define IWHITE "\x1b[37;1m"

#define BGC_BLACK "\x1b[40m"
#define BGC_RED "\x1b[41m"
#define BGC_GREEN "\x1b[42m"
#define BGC_YELLOW "\x1b[43m"
#define BGC_BLUE "\x1b[44m"
#define BGC_MAGENTA "\x1b[45m"
#define BGC_CYAN "\x1b[46m"
#define BGC_WHITE "\x1b[47m"

#define BGC_IBLACK "\x1b[40;1m"
#define BGC_IRED "\x1b[41;1m"
#define BGC_IGREEN "\x1b[42;1m"
#define BGC_IYELLOW "\x1b[43;1m"
#define BGC_IBLUE "\x1b[44;1m"
#define BGC_IMAGENTA "\x1b[45;1m"
#define BGC_ICYAN "\x1b[46;1m"
#define BGC_IWHITE "\x1b[47;1m"

static struct termios oldterm, newterm;

void initTermios(int echo)
{
    tcgetattr(0, &oldterm);
    newterm = oldterm;
    newterm.c_lflag &= ~ICANON;
    newterm.c_lflag &= echo ? ECHO : ~ECHO;
    tcsetattr(0, TCSANOW, &newterm);
}
void resetTermios(void)
{
    tcsetattr(0, TCSANOW, &oldterm);
}

int getch_(int echo)
{
    int ch;
    initTermios(echo);
    ch = getchar();
    resetTermios();
    return ch;
}

void cagxy(unsigned int x, unsigned int y)
{
    printf("%s\x1b[%d;%df", CLEAR, y, x);
}

void clrscr()
{
    printf("%s%s",CLEAR, SET11);
}

int getch(void)
{
    return getch_(0);
}

int getche(void)
{
    return getch_(1);
}

void gotox(unsigned int x)
{
    printf("\x1b[%dG", x);
}

void gotoxy(unsigned int x, unsigned int y)
{
    printf("\x1b[%d;%df", y, x);
}

void nocursor()
{
    printf("\x1b[?25l");
}

void reset_video()
{
    printf("\x1b[0m");
}

void showcursor()
{
    printf("\x1b[?25h");
}

void textcolor(char *color)
{
    printf("%s",color);
}

void textbackground(char color[11])
{
    char col[11];
    strcpy(col,color);
    col[2]='4';
    printf("%s",col);
}

void delline()
{
    printf("%s%s", ERASE_LINE, CURSOR_UP);
}

void clreol()
{
    printf("%s",CLEAR);
}
int putch(const char c)
{
    printf("%c",c);
    return (int)c;
}

int cputs(const char*str)
{
    printf(str);
    return 0;
}


int wherexy(int *x, int *y)
{
    printf("\033[6n");
    if(getch() != '\x1B') return 0;
    if(getch() != '\x5B') return 0;
    int in;
    int ly = 0;
    while((in = getch()) != ';')
        ly = ly * 10 + in - '0';
    int lx = 0;
    while((in = getch()) != 'R')
        lx = lx * 10 + in - '0';
    *x = lx;
    *y = ly;
}
int wherex()
{
    int x=0,y=0;
    wherexy(&x, &y);
    return x;
}

int wherey()
{
    int x=0,y=0;
    wherexy(&x, &y);
    return y;
}

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
#endif

