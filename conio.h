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

enum COLORS
{
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHTGRAY = 7,
  DARKGRAY = 8,
  LIGHTBLUE = 9,
  LIGHTGREEN = 10,
  LIGHTCYAN = 11,
  LIGHTRED = 12,
  LIGHTMAGENTA = 13,
  YELLOW = 14,
  WHITE = 15,
  BLINK = 128
};

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

// added the fflush function, it might seem like it does nothing, but it helps on some glitches when using gotoxy
void gotoxy(unsigned int x, unsigned int y)
{
    printf("\x1b[%d;%df", y, x);
    fflush(stdout);
}

void nocursor()
{
    printf("\x1b[?25l");
}

void normvideo()
{
    printf("\x1b[0m");
}

void showcursor()
{
    printf("\x1b[?25h");
}

void textcolor(int newcolor)
{
  //https://en.wikipedia.org/wiki/ANSI_escape_code

  const char * s = "\x1b[30m";

  switch (newcolor)
  {
  case BLACK:
    s = "\x1b[30m";
    break;

  case BLUE:
    s = "\x1b[34m";
    break;

  case GREEN:
    s = "\x1b[32m";
    break;

  case CYAN:
    s = "\x1b[36m";
    break;

  case RED:
    s = "\x1b[31;1m";
    break;

  case MAGENTA:
    s = "\x1b[35m";
    break;

  case BROWN:
    s = "\x1b[31m";
    break;

  case LIGHTGRAY:
    s = "\x1b[30;1m";
    break;

  case DARKGRAY:
    s = "\x1b[30m";
    break;

  case LIGHTBLUE:
    s = "\x1b[34;1m";
    break;

  case LIGHTGREEN:
    s = "\x1b[32,1m";;
    break;

  case LIGHTCYAN:
    s = "\x1b[36;1m";
    break;

  case LIGHTRED:
    s = "\x1b[31;1m";
    break;

  case LIGHTMAGENTA:
    s = "\x1b[35;1m";
    break;

  case YELLOW:
    s = "\x1b[33;1m";
    break;

  case WHITE:
    s = "\x1b[37;1m";
    break;

  case BLINK:
    s = "\x1b[30m";
    break;
  };

  printf("%s", s);
}

void textbackground(int newcolor)
{
  //https://en.wikipedia.org/wiki/ANSI_escape_code

  const char * s = "\x1b[40m";

  switch (newcolor)
  {
  case BLACK:
    s = "\x1b[40m";
    break;

  case BLUE:
    s = "\x1b[44m";
    break;

  case GREEN:
    s = "\x1b[42m";
    break;

  case CYAN:
    s = "\x1b[46m";
    break;

  case RED:
    s = "\x1b[41;1m";
    break;

  case MAGENTA:
    s = "\x1b[45m";
    break;

  case BROWN:
    s = "\x1b[41m";
    break;

  case LIGHTGRAY:
    s = "\x1b[40;1m";
    break;

  case DARKGRAY:
    s = "\x1b[40m";
    break;

  case LIGHTBLUE:
    s = "\x1b[44;1m";
    break;

  case LIGHTGREEN:
    s = "\x1b[42,1m";;
    break;

  case LIGHTCYAN:
    s = "\x1b[46;1m";
    break;

  case LIGHTRED:
    s = "\x1b[41;1m";
    break;

  case LIGHTMAGENTA:
    s = "\x1b[45;1m";
    break;

  case YELLOW:
    s = "\x1b[43;1m";
    break;

  case WHITE:
    s = "\x1b[47;1m";
    break;

  case BLINK:
    s = "\x1b[40m";
    break;
  };

  printf("%s", s);
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

