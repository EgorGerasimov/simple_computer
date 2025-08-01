#pragma once

#include "myTerm.h"

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RAM_SIZE 128
#define CACHELINES_NUM 5

typedef struct
{
  int start_address;
  int cacheline[10];
  int livetime;
  int is_changed;
} Cache;

int sc_memoryInit (void);
int sc_memorySet (int address, int value);
int sc_memoryGet (int address, int *value);
int sc_memorySave (char *filename);
int sc_memoryLoad (char *filename);
int sc_regInit (void);
int sc_regSet (int registry, int value);
int sc_regGet (int registry, int *value);
int sc_accumulatorInit (void);
int sc_accumulatorSet (int value);
int sc_accumulatorGet (int *value);
int sc_icounterInit (void);
int sc_icounterSet (int value);
int sc_icounterGet (int *value);
int sc_clocksCountSet (int value);
int sc_clocksCountGet (int *value);

int sc_cacheInit (void);
void sc_load_cache_to_memory ();
void sc_cachelineSet (int address);
int sc_cacheGet (int address, int *value);
int sc_cacheSet (int address, int value);
int sc_startCachelineGet (int address);
int sc_cacheValueGet (int address);
void sc_updateLivetime ();

void update_cache (int address);

void printCounters (void);
void printAccumulator (void);
void printFlags (void);
void printCell (int address, enum Colors fg, enum Colors bg);
void printCacheline (int cacheline_address);
void printDecodedCommand (int value);
void printCommand (void);
void printTerm ();
void printButtons ();

int sc_commandEncode (int sign, int command, int operand, int *value);
int sc_commandDecode (int value, int *sign, int *command, int *operand);

void convert_to_binary (unsigned a, int level);
void to_binary (unsigned a);