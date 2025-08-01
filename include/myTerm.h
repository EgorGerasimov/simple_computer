#pragma once

enum Colors
{
  BLACK,
  RED,
  GREEN,
  YELLOW,
  BLUE,
  MAGENTA,
  CYAN,
  WHITE,
  DEFAULT
};

#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

int open_terminal (int *fd);
int mt_clrscr (void);
int mt_gotoXY (int x, int y);
int mt_getscreensize (int *rows, int *cols);
int mt_setfgcolor (enum Colors c);
int mt_setbgcolor (enum Colors c);
int mt_setdefaultcolor (void);
int mt_setcursorvisible (int value);
int mt_delline (void);
int mt_enterAltMode ();
int mt_exitAltMode ();