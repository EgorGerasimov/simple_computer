#include "mySimpleComputer.h"

extern Cache cache[CACHELINES_NUM];
extern int sets_counter;

int
sc_cacheInit (void)
{
  for (int i = 0; i < CACHELINES_NUM; i++)
    {
      for (int j = 0; j < 10; j++)
        cache[i].cacheline[j] = 0;
      cache[i].start_address = -1;
      cache[i].livetime = 0;
      cache[i].is_changed = 0;
    }
  sets_counter = 0;
  return 0;
}

int
get_max_livetime ()
{
  int max_livetime = cache[0].livetime, max_livetime_index = 0;
  for (int i = 1; i < CACHELINES_NUM; i++)
    {
      if (cache[i].livetime > max_livetime)
        {
          max_livetime = cache[i].livetime;
          max_livetime_index = i;
        }
    }
  return max_livetime_index;
}

void
sc_updateLivetime ()
{
  for (int i = 0; i < CACHELINES_NUM; i++)
    (cache[i].livetime)++;
}

void
sc_load_cache_to_memory ()
{
  for (int cacheline_index = 0; cacheline_index < CACHELINES_NUM;
       cacheline_index++)
    {
      for (int row_num = 0; row_num < 13; row_num++)
        {
          if (cache[cacheline_index].start_address == row_num * 10)
            {
              if (cache[cacheline_index].is_changed)
                {
                  for (int i = 10; i >= 0; i--)
                    {
                      sc_clocksCountSet (i);
                      printCounters ();
                      pause ();
                    }
                  for (int i = row_num * 10;
                       i < row_num * 10 + 10 && i < RAM_SIZE; i++)
                    {
                      sc_memorySet (i,
                                    cache[cacheline_index].cacheline[i % 10]);
                      printCell (i, WHITE, DEFAULT);
                    }
                }
            }
        }
    }
}

void
sc_cachelineSet (int address)
{
  int row_num = address / 10, cacheline_index = get_max_livetime ();
  if (sets_counter > 4)
    {
      for (int i = cache[cacheline_index].start_address;
           i < cache[cacheline_index].start_address + 10 && i < RAM_SIZE; i++)
        {
          sc_memorySet (i, cache[cacheline_index].cacheline[i % 10]);
          printCell (i, WHITE, DEFAULT);
        }
    }
  for (int i = row_num * 10, mem_value = 0; i < row_num * 10 + 10; i++)
    {
      sc_memoryGet (i, &mem_value);
      cache[cacheline_index].cacheline[i % 10] = mem_value;
    }
  cache[cacheline_index].livetime = 0;
  cache[cacheline_index].start_address = row_num * 10;
  sets_counter++;
}

int
sc_cacheSet (int address, int value)
{
  int row_num = address / 10, cache_miss = 1;

  for (int i = 0; i < CACHELINES_NUM; i++)
    {
      if (cache[i].start_address == row_num * 10)
        {
          cache[i].cacheline[address - row_num * 10] = value;
          cache[i].livetime = 0;
          cache[i].is_changed = 1;
          cache_miss = 0;
        }
    }
  if (cache_miss)
    {
      sc_cachelineSet (address);
      sc_cacheSet (address, value);
    }
  return cache_miss;
}

int
sc_cacheGet (int address, int *value)
{
  int row_num = address / 10, cache_miss = 1;
  for (int i = 0; i < CACHELINES_NUM; i++)
    {
      if (cache[i].start_address == row_num * 10)
        {
          *value = cache[i].cacheline[address - row_num * 10];
          cache[i].livetime = 0;
          cache_miss = 0;
        }
    }
  if (cache_miss)
    {
      sc_cachelineSet (address);
      sc_cacheGet (address, value);
    }
  return cache_miss;
}

void
update_cache (int address)
{
  int row_num = address / 10;
  for (int i = 0; i < CACHELINES_NUM; i++)
    {
      if (cache[i].start_address == row_num * 10)
        {
          for (int j = row_num * 10, mem_value = 0; j < row_num * 10 + 10; j++)
            {
              sc_memoryGet (j, &mem_value);
              cache[i].cacheline[j % 10] = mem_value;
            }
          cache[i].livetime = 0;
          cache[i].start_address = row_num * 10;
        }
    }
  for (int i = 0; i < CACHELINES_NUM; i++)
    printCacheline (i);
}

int
sc_cacheValueGet (int address)
{
  int row_num = address / 10, value = 0;
  for (int i = 0; i < CACHELINES_NUM; i++)
    {
      if (cache[i].start_address == row_num * 10)
        value = cache[i].cacheline[address - row_num * 10];
    }
  return value;
}

int
sc_startCachelineGet (int address)
{
  return cache[address].start_address;
}