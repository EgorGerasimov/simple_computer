
#pragma once

#include "myBigChars.h"
#include "myReadKey.h"
#include "mySimpleComputer.h"
#include "myTerm.h"

#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

enum ERRORS
{
  ZAEBOK,
  FAILURE_COMMAND,
  CALC_OWERFLOW,
  DIV_ZERO
};

int main (int argc, char *argv[]);
void moveCursor ();
void init_all ();
void impulse_generator ();
void print_all (int fd);
void main_loop ();
int read_font (int argc, char *argv[]);

void IRC (int signum);
void CU (void);
int ALU (int command, int operand);
void CPUINFO ();
void READ (int address, char io_data[5][10]);
void WRITE (int address, char io_data[5][10]);
int ADD (int operand);
int SUB (int operand);
int MUL (int operand);
int DIV (int operand);