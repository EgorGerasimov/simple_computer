#include "mySimpleComputer.h"

int RAM[RAM_SIZE];
int accumulator = 1, commands_count = 0, flags_registry = 0, clocks_count = 0,
    sets_counter = 0;
char io_data[5][10];
Cache cache[5] = { 0 };
