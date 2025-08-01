#include "mySimpleComputer.h"
#include <limits.h>

extern int accumulator, commands_count, flags_registry, clocks_count;

int
sc_regInit (void)
{
  flags_registry = 1 << 3;
  return flags_registry;
}

int
sc_regSet (int registry, int value)
{
  int flag = 0;
  if (registry >= 0 && registry <= 4 && (value == 0 || value == 1))
    {
      if (value == 1)
        flags_registry |= (1 << registry);
      else
        flags_registry &= ~(1 << registry);
    }
  else
    flag = -1;
  return flag;
}

int
sc_regGet (int registry, int *value)
{
  int flag = 0;
  if (registry >= 0 && registry <= 31 && (value != NULL))
    {
      *value = (flags_registry >> registry) & 1;
    }
  else
    flag = -1;
  return flag;
}

int
sc_accumulatorInit (void)
{
  accumulator = 0;
  return accumulator;
}

int
sc_accumulatorSet (int value)
{
  int flag = -1;
  if (value <= 0x7fff)
    {
      flag = 0;
      // printf ("%d\n %015b", value, value);
      accumulator = value;
    }
  return flag;
}

int
sc_accumulatorGet (int *value)
{
  int flag = 0;
  if (value != NULL)
    *value = accumulator;
  else
    flag = -1;
  return flag;
}

int
sc_icounterInit (void)
{
  commands_count = 0;
  return commands_count;
}

int
sc_icounterSet (int value)
{
  int flag = -1;
  if (value <= 0x7fff)
    {
      flag = 0;
      commands_count = value;
    }
  return flag;
}

int
sc_icounterGet (int *value)
{
  int flag = 0;
  if (value != NULL)
    *value = commands_count;
  else
    flag = -1;
  return flag;
}

int
sc_clocksCountSet (int value)
{
  int flag = -1;
  if (value <= 0x7fff)
    {
      flag = 0;
      clocks_count = value;
    }
  return flag;
}

int
sc_clocksCountGet (int *value)
{
  int flag = 0;
  if (value != NULL)
    *value = clocks_count;
  else
    flag = -1;
  return flag;
}