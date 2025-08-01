#include "../include/myTerm.h"

int
open_terminal (int *fd)
{
  *fd = open ("/dev/tty", O_WRONLY);
  if (*fd == -1)
    {
      fprintf (stderr, "Ошибка открытия терминала.\n");
      return (-1);
    }
  return 0;
}

int
mt_clrscr (void)
{
  int fd = 0, ret = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      write (fd, "\033[H\033[J", 7);
      close (fd);
    }
  return ret;
}

int
mt_gotoXY (int x, int y)
{
  int ret = 0, rows = 0, cols = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      if (!mt_getscreensize (&rows, &cols) && x <= cols && y <= rows && x >= 0
          && y >= 0)
        {
          char str[25] = { 0 };
          sprintf (str, "\033[%d;%dH", y, x);
          write (fd, str, 11);
        }
      else
        ret = -1;
      close (fd);
    }
  return ret;
}

int
mt_getscreensize (int *rows, int *cols)
{
  struct winsize ws;
  int ret = 0;
  if (!ioctl (1, TIOCGWINSZ, &ws))
    {
      *rows = ws.ws_row;
      *cols = ws.ws_col;
      // printf ("%d\n\n%d\n\n", *rows, *cols);
      if (*cols < 112 || *rows < 32)
        {
          int fd = 0;
          open_terminal (&fd);
          write (fd, "Small screen!\n", 15);
          close (fd);
          ret = -1;
        }
    }
  else
    {
      ret = -1;
    }
  return ret;
}

int
mt_setfgcolor (enum Colors c)
{
  int ret = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      char str[6] = { 0 };
      sprintf (str, "\033[3%dm", c);
      write (fd, str, 6);
      close (fd);
    }
  return ret;
}

int
mt_setbgcolor (enum Colors c)
{
  int ret = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret && isatty (fd))
    {
      char str[6] = { 0 };
      sprintf (str, "\033[4%dm", c);
      write (fd, str, 6);
      close (fd);
    }
  return ret;
}

int
mt_setdefaultcolor (void)
{
  int ret = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      write (fd, "\033[0m", 5);
      close (fd);
    }
  return ret;
}

int
mt_setcursorvisible (int must_visible)
{
  int ret = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      if (must_visible)
        write (fd, "\033[?25h\033[?8c", 12);
      else
        write (fd, "\033[?25h\033[?1c", 12);
      close (fd);
    }
  return ret;
}

int
mt_delline (void)
{
  int ret = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      write (fd, "\033[M", 4);
      close (fd);
    }
  return ret;
}

int
mt_enterAltMode ()
{
  int ret = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      write (fd, "\033(0", 3);
      close (fd);
    }
  return ret;
}

int
mt_exitAltMode ()
{
  int ret = 0, fd = 0;
  ret = open_terminal (&fd);
  if (!ret)
    {
      write (fd, "\033(B", 3);
      close (fd);
    }
  return ret;
}