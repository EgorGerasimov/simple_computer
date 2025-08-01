#include "myBigChars.h"
#include "mySimpleComputer.h"
#include <string.h>

void
bc_drawBorders ()
{
  bc_box (1, 1, 61, 15, 7, 8, "Операвтивная память", 1, 8);
  bc_box (63, 1, 23, 3, 7, 8, "Аккумулятор", 1, 8);
  bc_box (63, 4, 23, 3, 7, 8, "Счётчик команд", 1, 8);
  bc_box (87, 1, 23, 3, 7, 8, "Регистр флагов", 1, 8);
  bc_box (87, 4, 23, 3, 7, 8, "Команда", 1, 8);
  bc_box (68, 19, 10, 7, 7, 8, "IN--OUT", 2, 7);
  bc_box (1, 16, 61, 3, 7, 8, "Редактируемая ячейка (формат)", 5, 7);
  bc_box (79, 19, 31, 7, 7, 8, "Клавиши", 2, 7);
  bc_box (63, 7, 47, 12, 7, 8, "Редактируемая ячейка (увеличено)", 5, 7);
  bc_box (1, 19, 66, 7, 7, 8, "Кеш процессора", 5, 7);
}

int
bc_box (int x1, int y1, int x2, int y2, enum Colors box_fg, enum Colors box_bg,
        char *header, enum Colors header_fg, enum Colors header_bg)
{
  int fd = -1;
  open_terminal (&fd);
  mt_setbgcolor (box_bg);
  mt_setfgcolor (box_fg);
  if (fd >= 0)
    {
      char str[128] = { 0 };
      for (int j = 0; j < y2; j++)
        {
          if (j == 0)
            {
              mt_gotoXY (x1, y1);
              str[0] = 'l';
              for (int i = 0; i < x2; i++)
                strcat (str, "q");
              str[x2] = 'k';
            }
          else if (j != 0 && j != y2 - 1)
            {
              mt_gotoXY (x1, y1 + j);

              for (int i = 0; i < x2; i++)
                {
                  if (i == 0)
                    str[0] = 'x';
                  else if (i != 0 && i != x2 - 1)
                    strcat (str, " ");
                  else
                    {
                      strcat (str, " ");
                      strcat (str, "x");
                    }
                }
            }
          else
            {
              mt_gotoXY (x1, y1 + y2 - 1);
              str[0] = 'm';
              for (int i = 0; i < x2; i++)
                strcat (str, "q");
              str[x2] = 'j';
            }
          write (fd, str, strlen (str));
          for (int i = 0; i < x2; i++)
            str[i] = 0;
        }
      str[0] = ' ';
      strcat (str, header);
      str[strlen (str)] = ' ';
      int len = strlen (header);
      if (str[1] == 'I')
        len = (len * 2);
      int head = x1 + (x2 - len / 2) / 2;
      mt_gotoXY (head, y1);
      mt_setfgcolor (header_fg);
      mt_setbgcolor (header_bg);
      write (fd, str, strlen (str) + 1);
      mt_setdefaultcolor ();
      close (fd);
    }
  return fd;
}

int
bc_getbigcharpos (int *big, int x, int y, int *value)
{
  if (x < 1 || x > 8 || y < 1 || y > 8 || value == NULL)
    return -1;

  int index = (y - 1) / 4;
  int bit = (8 * (4 - y % 4) + (8 - x));
  *value = (big[index] >> bit) & 1;

  return 0;
}

int
bc_setbigcharpos (int *big, int x, int y, int value)
{
  if (x < 1 || x > 8 || y < 1 || y > 8 || (value != 0 && value != 1))
    return -1;

  int index = (y - 1) / 4;
  int bit = (8 * (4 - y % 4) + (8 - x));
  if (value == 1)
    big[index] |= (1 << bit);
  else
    big[index] &= ~(1 << bit);

  return 0;
}

int
bc_printbigchar (int big[2], int x, int y, enum Colors fg, enum Colors bg)
{
  int fd = -1;
  int stat = open_terminal (&fd);
  if (fd >= 0 && !stat)
    {
      int val = 0;
      stat = mt_gotoXY (x, y);
      mt_exitAltMode ();
      mt_setbgcolor (bg);
      mt_setfgcolor (fg);
      mt_enterAltMode ();
      for (int i = 1; i <= 8 && !stat; i++)
        {
          for (int j = 1; j <= 8 && !stat; j++)
            {
              stat = bc_getbigcharpos (big, j, i, &val);
              if (val == 1)
                write (fd, "a", 2);
              else
                write (fd, " ", 2);
            }
          stat = mt_gotoXY (x, y + i);
        }
      mt_setdefaultcolor ();
      mt_exitAltMode ();
      close (fd);
    }
  else
    stat = -1;
  return stat;
}

int
bc_bigcharwrite (int fd, int big[18][2], int count)
{
  if (fd < 0 || count <= 0 || count > 18)
    return -1;

  for (int i = 0; i < count; i++)
    {
      for (int j = 0; j < 2; j++)
        write (fd, &(big[i][j]), sizeof (int));
    }
  return 0;
}

int
bc_bigcharread (int fd, int big[18][2], int need_count, int *count)
{
  if (fd < 0 || need_count < 0 || need_count > 18)
    return -1;
  *count = 0;
  for (int i = 0; i < need_count; i++, (*count)++)
    {
      for (int j = 0; j < 2; j++)
        read (fd, &(big[i][j]), sizeof (int));
    }
  return 0;
}

void
PrintBigCell (int cursor_pos, char *filename)
{
  int fd_font = open (filename, O_RDONLY), fd_term = 0;
  open_terminal (&fd_term);
  if (isatty (fd_term) && fd_font)
    {
      int font[18][2], count = 0;
      bc_bigcharread (fd_font, font, 18, &count);
      if (count == 18)
        {
          int value = 0, sign = 0, command = 0, operand = 0;
          sc_memoryGet (cursor_pos, &value);
          sc_commandDecode (value, &sign, &command, &operand);
          if (sign)
            bc_printbigchar (font[17], 65, 9, 7, 8);
          else
            bc_printbigchar (font[16], 65, 9, 7, 8);
          bc_printbigchar (font[(command >> 4) & 15], 74, 9, 7, 8);
          bc_printbigchar (font[(command & 15)], 83, 9, 7, 8);
          bc_printbigchar (font[(operand >> 4) & 15], 92, 9, 7, 8);
          bc_printbigchar (font[(operand & 15)], 101, 9, 7, 8);
          char str[64] = { 0 };
          mt_gotoXY (65, 17);
          sprintf (str, "Номер редактируемой ячейки: %03d", cursor_pos);
          mt_setfgcolor (4);
          write (fd_term, str, strlen (str));
          mt_setdefaultcolor ();
        }
      close (fd_term);
      close (fd_font);
    }
}