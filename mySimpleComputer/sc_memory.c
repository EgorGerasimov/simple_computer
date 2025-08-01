#include "mySimpleComputer.h"

extern int RAM[RAM_SIZE];
extern int accumulator;

int
sc_memoryInit (void)
{
  for (int i = 0; i < RAM_SIZE; i++)
    RAM[i] = 0;
  return 0;
}

int
sc_memorySet (int address, int value)
{
  int flag = 0;
  if ((address >= 0 && address < 128) && value <= 0x7fff)
    RAM[address] = value;
  else
    flag = -1;
  return flag;
}

int
sc_memoryGet (int address, int *value)
{
  int flag = 0;
  if ((address >= 0 && address < 128) && value != NULL)
    *value = RAM[address];
  else
    flag = -1;
  return flag;
}

int
sc_memorySave (char *filename)
{
  int flag = 0;
  if (filename != NULL)
    {
      FILE *file = fopen (filename, "wb");
      if (file != NULL)
        {
          int counter_w = 0;
          counter_w = fwrite (RAM, sizeof (int), 128, file);
          if (counter_w != 128)
            flag = -1;
          fclose (file);
        }
      else
        flag = -1;
    }
  else
    flag = -1;
  return flag;
}

int
sc_memoryLoad (char *filename)
{
  int flag = 0;
  if (filename != NULL)
    {
      FILE *file = fopen (filename, "rb");
      if (file != NULL)
        {
          int counter_r = 0;
          int copy_RAM[RAM_SIZE] = { 0 };
          counter_r = fread (copy_RAM, sizeof (int), 128, file);
          if (counter_r != 128)
            flag = -1;
          else
            {
              for (int i = 0; i < RAM_SIZE; i++)
                sc_memorySet (i, copy_RAM[i]);
              for (int i = 0; i < 128; i++)
                printCell (i, WHITE, DEFAULT);
            }
          fclose (file);
        }
      else
        flag = -1;
    }
  else
    flag = -1;
  return flag;
}