#include "console.h"

int
rk_readvalue (int *value, int timeout)
{
  int str[5] = { 0 }, ret = 0;
  enum Keys key = 0;
  rk_mytermregime (1, timeout, 1, 1, 0);

  for (int i = -1; i < 4;)
    {
      i += rk_readkey (&key);
      if (i == 0)
        {
          if (key == PLUS)
            str[i] = 0;
          else if (key == MINUS)
            str[i] = 1;
          else
            ret = -1;
        }
      else if (i > 0 && i < 5)
        {
          if ((i == 1 || i == 3) && (key > SEVEN || key < ZERO))
            ret = -1;
          if (key >= a && key <= f)
            str[i] = (key - a) + 10;
          else if (key >= A && key <= F)
            str[i] = (key - A) + 10;
          else if (key >= ZERO && key <= NINE)
            str[i] = (key - ZERO);
          else
            ret = -1;
        }
      if (ret == -1)
        break;
    }
  if (ret == 0)
    ret = sc_commandEncode (str[0], (str[1] << 4) | str[2],
                            (str[3] << 4) | str[4], value);
  rk_mytermregime (1, 0, 1, 0, 0);

  return ret;
}

void
rk_loadfile ()
{
  int i = 8;
  enum Keys key = 0;
  char filename[256] = "console/";
  mt_gotoXY (33, 26);
  while (key != ENTER && i != 255)
    {
      rk_readkey (&key);
      if (key != ENTER)
        filename[i] = key;
      i++;
    }
  mt_gotoXY (33, 26);
  int fd = 0;
  if (!open_terminal (&fd))
    {
      for (int i = 0; i < 256; i++)
        write (fd, " ", sizeof (char));
      close (fd);
    }
  sc_memoryLoad (filename);
}

void
rk_savefile ()
{
  int i = 8;
  enum Keys key = 0;
  char filename[256] = "console/";
  mt_gotoXY (33, 26);
  while (key != ENTER && i != 255)
    {
      rk_readkey (&key);
      if (key != ENTER)
        filename[i] = key;
      i++;
    }
  mt_gotoXY (33, 26);
  int fd = 0;
  if (!open_terminal (&fd))
    {
      for (int i = 0; i < 256; i++)
        write (fd, " ", sizeof (char));
      close (fd);
    }
  sc_memorySave (filename);
}
