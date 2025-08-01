#include "mySimpleComputer.h"

void
convert_to_binary (unsigned a, int level)
{
  if (level != 16)
    convert_to_binary (a / 2, level + 1);
  printf ("%d", a % 2);
}

void
to_binary (unsigned a)
{
  convert_to_binary (a, 0);
  putchar ('\n');
}

int
sc_commandEncode (int sign, int command, int operand, int *value)
{
  int flag = 0;
  if ((sign == 0 || sign == 1) && (command >= 0 && command <= 127)
      && (operand >= 0 && operand <= 127) && value != NULL)
    {
      *value = 0;
      *value |= (sign << 14) | (command << 7) | operand;
    }
  else
    flag = -1;
  return flag;
}