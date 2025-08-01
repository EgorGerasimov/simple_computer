#include "console.h"

extern int run_flag;

void
IRC (int signum)
{
  int T_reg = 0;
  sc_regGet (3, &T_reg);
  if (signum == SIGUSR1)
    run_flag = 1;
  if (signum == SIGALRM && !T_reg)
    run_flag = 0;
}