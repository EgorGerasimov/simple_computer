#include "console.h"
extern enum Keys key;

void
CPUINFO ()
{
  int fd = -1;
  open_terminal (&fd);
  if (fd >= 0)
    {
      mt_gotoXY (0, 28);
      write (fd, "Герасимов Егор Олегович, ИВ-323", 55);
      mt_gotoXY (0, 29);
      write (fd, "Чудинов Константин Игоревич, ИВ-323", 63);
      mt_gotoXY (0, 30);
      write (fd, "Главатских Екатерина Александровна, ИВ-323", 77);
      close (fd);
    }
}

void
READ (int address, char io_data[5][10])
{
  int fd = -1;
  open_terminal (&fd);
  if (fd >= 0)
    {
      int value = 0, sign = 0, command = 0, operand = 0;
      char buff[10] = { 0 };
      strncpy (buff, io_data[4], 10);
      for (int i = 3; i >= 0; i--)
        strncpy (io_data[i + 1], io_data[i], 10);
      sprintf (io_data[0], "%02X<      ", address);
      for (int i = 0; i < 5; i++)
        {
          mt_gotoXY (69, 20 + i);
          write (fd, io_data[i], strlen (io_data[i]));
        }
      mt_gotoXY (73, 20);
      if (rk_readvalue (&value, 10))
        {
          for (int i = 0; i < 4; i++)
            {
              strncpy (io_data[i], io_data[i + 1], 10);
            }
          strncpy (io_data[4], buff, 10);
          for (int i = 0; i < 5; i++)
            {
              mt_gotoXY (69, 20 + i);
              write (fd, io_data[i], strlen (io_data[i]));
            }
        }
      else
        {
          sc_commandDecode (value, &sign, &command, &operand);
          if (sign)
            sprintf (io_data[0], "%02X< -%02X%02X", address, command, operand);
          else
            sprintf (io_data[0], "%02X< +%02X%02X", address, command, operand);
          int timer = 1;
          if (sc_cacheSet (address, value))
            timer = 10;
          if (key != t)
            {
              for (int i = timer; i >= 0; i--)
                {
                  sc_clocksCountSet (i);
                  printCounters ();
                  pause ();
                }
            }
          for (int i = 0; i < CACHELINES_NUM; i++)
            printCacheline (i);
          printCell (address, 7, 8);
        }
      printTerm (operand, 1);
      close (fd);
    }
}

void
WRITE (int address, char io_data[5][10])
{
  int fd = -1;
  open_terminal (&fd);
  if (fd >= 0)
    {
      int value = 0, sign = 0, command = 0, operand = 0;
      for (int i = 3; i >= 0; i--)
        strncpy (io_data[i + 1], io_data[i], 10);

      sc_cacheGet (address, &value);
      sc_commandDecode (value, &sign, &command, &operand);
      for (int i = 0; i < 5; i++)
        {
          mt_gotoXY (69, 20 + i);
          write (fd, io_data[i], strlen (io_data[i]));
        }
      if (sign)
        sprintf (io_data[0], "%02X> -%02X%02X", address, command, operand);
      else
        sprintf (io_data[0], "%02X> +%02X%02X", address, command, operand);
      printTerm ();
      close (fd);
    }
}

int
ADD (int operand)
{
  int ret = ZAEBOK, value = 0, mem_value = 0;
  int sign_v = 0, comm_v = 0, oper_v = 0;
  int sign_m = 0, comm_m = 0, oper_m = 0;
  int src_v = 0, src_m = 0;
  sc_accumulatorGet (&value);
  sc_cacheGet (operand, &mem_value);
  sc_commandDecode (value, &sign_v, &comm_v, &oper_v);
  sc_commandDecode (mem_value, &sign_m, &comm_m, &oper_m);
  if (sign_v == sign_m)
    {
      value += mem_value;
      if (value > 0x7fff && sign_v)
        ret = CALC_OWERFLOW;
      else if (value > 0x3fff && !sign_v)
        ret = CALC_OWERFLOW;
    }
  else
    {
      sc_commandEncode (0, comm_v, oper_v, &src_v);
      sc_commandEncode (0, comm_m, oper_m, &src_m);
      if (!sign_v)
        { // ПОЛ
          if (src_v >= src_m)
            {
              value = src_v - src_m;
              if (value > 0x3fff)
                ret = CALC_OWERFLOW;
            }
          else
            {
              value = (src_m - src_v) | 0x4000;
              if (value > 0x7fff)
                ret = CALC_OWERFLOW;
            }
        }
      else
        { // ОТР
          if (src_v > src_m)
            {
              value = (src_v - src_m) | 0x4000;
              if (value > 0x7fff)
                ret = CALC_OWERFLOW;
            }
          else
            {
              value = src_m - src_v;
              ;
              if (value > 0x3fff)
                ret = CALC_OWERFLOW;
            }
        }
    }
  sc_accumulatorSet ((value & 0x7fff));
  return ret;
}

int
SUB (int operand)
{
  int ret = ZAEBOK, value = 0, mem_value = 0;
  int sign_v = 0, comm_v = 0, oper_v = 0;
  int sign_m = 0, comm_m = 0, oper_m = 0;
  int src_v = 0, src_m = 0;
  sc_accumulatorGet (&value);
  sc_cacheGet (operand, &mem_value);
  sc_commandDecode (value, &sign_v, &comm_v, &oper_v);
  sc_commandDecode (mem_value, &sign_m, &comm_m, &oper_m);
  sc_commandEncode (0, comm_v, oper_v, &src_v);
  sc_commandEncode (0, comm_m, oper_m, &src_m);
  if (!sign_v && !sign_m)
    {
      if (src_v > src_m)
        value -= mem_value;
      else
        value = src_m - src_v;
      if (src_m > src_v)
        value |= 0x4000;
    }
  else if (!sign_v && sign_m)
    {
      value = src_v + src_m;
      if (value > 0x3fff)
        ret = CALC_OWERFLOW;
    }
  else if (sign_v && !sign_m)
    {
      value = src_v + src_m;
      if (value > 0x3fff)
        ret = CALC_OWERFLOW;
      value |= 0x4000;
    }
  else if (sign_v && sign_m)
    {
      value -= mem_value;
      if (src_v > src_m)
        value |= 0x4000;
    }
  sc_accumulatorSet ((value & 0x7fff));
  return ret;
}

int
MUL (int operand)
{
  int ret = ZAEBOK, value = 0, mem_value = 0;
  int sign_v = 0, comm_v = 0, oper_v = 0;
  int sign_m = 0, comm_m = 0, oper_m = 0;
  int src_v = 0, src_m = 0;
  sc_accumulatorGet (&value);
  sc_cacheGet (operand, &mem_value);
  sc_commandDecode (value, &sign_v, &comm_v, &oper_v);
  sc_commandDecode (mem_value, &sign_m, &comm_m, &oper_m);

  sc_commandEncode (0, comm_v, oper_v, &src_v);
  sc_commandEncode (0, comm_m, oper_m, &src_m);

  value = src_v * src_m;
  if (value > 0x3fff)
    {
      value &= 0x3fff;
      ret = CALC_OWERFLOW;
    }
  if (sign_v != sign_m)
    value |= 0x4000;

  sc_accumulatorSet (value);
  return ret;
}

int
DIV (int operand)
{
  int ret = ZAEBOK, value = 0, mem_value = 0;
  int sign_v = 0, comm_v = 0, oper_v = 0;
  int sign_m = 0, comm_m = 0, oper_m = 0;
  int src_v = 0, src_m = 0;
  sc_accumulatorGet (&value);
  sc_cacheGet (operand, &mem_value);
  sc_commandDecode (value, &sign_v, &comm_v, &oper_v);
  sc_commandDecode (mem_value, &sign_m, &comm_m, &oper_m);

  sc_commandEncode (0, comm_v, oper_v, &src_v);
  sc_commandEncode (0, comm_m, oper_m, &src_m);

  if (src_m != 0)
    value = src_v / src_m;
  else
    ret = DIV_ZERO;
  if (value > 0x3fff)
    {
      value &= 0x3fff;
      ret = CALC_OWERFLOW;
    }
  if (sign_v != sign_m)
    value |= 0x4000;

  sc_accumulatorSet (value);
  return ret;
}