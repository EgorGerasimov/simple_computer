#include "mySimpleComputer.h"

int
sc_commandValidate (int command)
{
  int flag = 0;
  if (command >= 0 && command <= 127)
    {
    }
  else
    flag = -1;
  return flag;
}