#include "mySimpleComputer.h"

int
sc_commandDecode (int value, int *sign, int *command, int *operand)
{
  int flag = 0;
  if (value <= 0b111111111111111)
    {
      *sign = 0, *command = 0, *operand = 0;
      *sign = (value >> 14);
      *command = (value >> 7) & 0b01111111;
      *operand = value & 0b1111111;
    }
  else
    flag = -1;
  return flag;
}