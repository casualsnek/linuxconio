# Linux <conio.h>
## _"conio.h" implementation for Linux_

This is the implementation of "conio.h" from ms-dos based C compilers for linux/*nix systems

Why use "conio" on linux instead of "curses" or other libraries
- Because my college forces me to use "conio" library (which is not available on linux) and i have to make sure the code i write runs on my teacher's computer too.
- Yes, this is the only reason

### Features

- Does not use "curses" library.
- It works on linux with GCC and maybe BSD too


## Installation

Installation is done by copying "conio.h" file to location where compiler looks for header files Or keeping "conio.h" in same directory as your code and using ``` #include "conio.h"``` instead of ```#include <conio.h> ```

On most systems it can be installed by running following commands in terminal emulator

```sh
$ git clone https://github.com/casualsnek/linuxconio
$ cd linuxconio
$ sudo cp conio.h /usr/include/conio.h
```
Restart your IDE if you are using one and use it as you normally would

You can check if it is working properly after installing by compilling and running "testconio.c" using following commands:
```sh
$ gcc testconio.c -o testconio
$ ./testconio
```

### Implemented functions
May not be exact to windows "conio.h" but mostly seems to work in similar ways
- showcursor
- nocursor
- cagxy
- gotox
- gotoxy
- clrscr
- kbhit
- textbackground
- textcolor
- getch
- getche
- clreol
- delline
- cprintf
- cscanf
- cputs
- cgets
- wherex
- wherey
- getpass

You can help by adding support for missing functions or improving the already existing ones.
Please star this repository if you find ths useful
