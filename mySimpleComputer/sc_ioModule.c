#include "console.h"
#include <string.h>

extern int flags_registry, commands_count, accumulator, RAM[RAM_SIZE],
    clocks_count;
extern char io_data[5][10];

void
printCell (int address, enum Colors fg, enum Colors bg)
{
  int operand = 0, sign = 0, command = 0;
  sc_commandDecode (RAM[address], &sign, &command, &operand);
  int flag = 0, fd = 0;
  flag = open_terminal (&fd);
  int x = 2 + (address % 10) * 6;
  int y = 2 + (address / 10);
  if (!flag)
    {
      mt_gotoXY (x, y);
      mt_setfgcolor (fg);
      mt_setbgcolor (bg);
      char str[30] = { 0 };
      if (sign)
        sprintf (str, "-%02X%02X", command, operand);
      else
        sprintf (str, "+%02X%02X", command, operand);
      write (fd, str, 7);
      mt_setdefaultcolor ();
      write (fd, " ", 2);
      mt_gotoXY (x, y);
      close (fd);
    }
  else
    printf ("Ошибка открытия терминала");
}

void
printCacheline (int cacheline_address)
{
  int operand = 0, sign = 0, command = 0, fd = 0,
      cache_index = sc_startCachelineGet (cacheline_address);
  int x = 2;
  int y = 20 + cacheline_address;
  if (!open_terminal (&fd))
    {
      mt_gotoXY (x, y);
      mt_setfgcolor (WHITE);
      mt_setbgcolor (DEFAULT);
      if (cache_index == -1)
        {
          char fake_line[80] = { 0 };
          sprintf (fake_line, "000: +0000 +0000 +0000 +0000 +0000 +0000 +0000 "
                              "+0000 +0000 +0000 ");
          write (fd, fake_line, 80);
        }
      else
        {
          char str_line[6] = { 0 };
          sprintf (str_line, "%03d: ", cache_index);
          write (fd, str_line, 6);
        }
      for (int i = 0;
           i < 10 && cache_index > -1 && (cache_index + i) < RAM_SIZE; i++)
        {
          char str[30] = { 0 };
          sc_commandDecode (sc_cacheValueGet (cache_index + i), &sign,
                            &command, &operand);
          if (sign)
            sprintf (str, "-%02X%02X ", command, operand);
          else
            sprintf (str, "+%02X%02X ", command, operand);
          write (fd, str, 8);
        }
      mt_gotoXY (x, y);
      close (fd);
    }
  else
    printf ("Ошибка открытия терминала");
}

void
printFlags (void)
{
  int fd = -1;
  open_terminal (&fd);
  if (fd >= 0)
    {
      mt_gotoXY (94, 2);
      write (fd, (flags_registry & 1) ? "P " : "_ ", 3);
      write (fd, (flags_registry & 1 << 1) ? "0 " : "_ ", 3);
      write (fd, (flags_registry & 1 << 2) ? "M " : "_ ", 3);
      write (fd, (flags_registry & 1 << 3) ? "T " : "_ ", 3);
      write (fd, (flags_registry & 1 << 4) ? "E " : "_\n", 3);

      close (fd);
    }
}

void
printDecodedCommand (int value)
{
  int fd = -1;
  open_terminal (&fd);
  if (fd >= 0)
    {
      char str[100] = { 0 };
      mt_gotoXY (2, 17);
      sprintf (str, "dec: %05d | oct: %05o | hex: %04X    bin: %015b", value,
               value, value, value);
      write (fd, str, strlen (str));
      close (fd);
    }
}

void
printAccumulator (void)
{
  int fd = -1, operand = 0, sign = 0, command = 0;
  open_terminal (&fd);
  if (fd >= 0)
    {
      mt_gotoXY (65, 2);
      char str[100] = { 0 };
      sc_commandDecode (accumulator, &sign, &command, &operand);
      if (sign)
        sprintf (str, "sc: -%02X%02X  hex: %04X", command, operand,
                 accumulator);
      else
        sprintf (str, "sc: +%02X%02X  hex: %04X", command, operand,
                 accumulator);
      write (fd, str, strlen (str));
      close (fd);
    }
}

void
printCounters (void)
{
  int fd = -1, operand = 0, sign = 0, command = 0;
  open_terminal (&fd);
  if (fd >= 0)
    {
      mt_gotoXY (65, 5);
      char str[100] = { 0 };
      sc_commandDecode (commands_count, &sign, &command, &operand);
      if (sign)
        sprintf (str, "T: %02d     IC: -%02X%02X", clocks_count, command,
                 operand);
      else
        sprintf (str, "T: %02d     IC: +%02X%02X", clocks_count, command,
                 operand);
      write (fd, str, strlen (str));
      close (fd);
    }
}

void
printCommand (void)
{
  int fd = -1, operand = 0, sign = 0, command = 0;
  open_terminal (&fd);
  if (fd >= 0)
    {
      mt_gotoXY (94, 5);
      char str[100] = { 0 };
      sc_commandDecode (RAM[commands_count], &sign, &command, &operand);
      if (command >= 0 && command <= 127)
        {
          if (sign)
            sprintf (str, "- %02X : %02X", command, operand);
          else
            sprintf (str, "+ %02X : %02X", command, operand);
        }
      else
        {
          sprintf (str, "!   + FF : FF");
        }
      write (fd, str, strlen (str));
      close (fd);
    }
}

void
printTerm ()
{
  int fd = -1;
  static int j = 0;
  open_terminal (&fd);
  if (fd >= 0)
    {
      if (j < 5)
        j++;
      for (int i = 0; i < j; i++)
        {
          mt_gotoXY (69, 20 + i);
          write (fd, io_data[i], strlen (io_data[i]));
        }
      close (fd);
    }
}

void
printButtons ()
{
  int fd = -1;
  open_terminal (&fd);
  if (fd >= 0)
    {
      mt_gotoXY (80, 20);
      char str[100] = { 0 };
      sprintf (str, "%s", "l - load  s - save  i - reset");
      write (fd, str, strlen (str));
      mt_gotoXY (80, 21);
      sprintf (str, "%s", "r - run   t - step");
      write (fd, str, strlen (str));
      mt_gotoXY (80, 22);
      sprintf (str, "%s", "ESC - выход");
      write (fd, str, strlen (str));
      mt_gotoXY (80, 23);
      sprintf (str, "%s", "F5 - accumulator");
      write (fd, str, strlen (str));
      mt_gotoXY (80, 24);
      sprintf (str, "%s", "F6 - instructor counter");
      write (fd, str, strlen (str));

      close (fd);
    }
}