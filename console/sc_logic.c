#include "../include/console.h"
extern char io_data[5][10], filename[1][256];
extern int run_flag, add_flag, file_count;
extern enum Keys key;

void
moveCursor ()
{
  int ram_value = 0, run_reg = 1, icounter = 0, cursor_pos = 0;
  while (key != ESCAPE)
    {
      if (key == t)
        {
          sc_icounterSet (cursor_pos);
          run_reg = 0;
        }
      if (key == r)
        {
          sc_regInit ();
          sc_cacheInit ();
          for (int i = 0; i < CACHELINES_NUM; i++)
            printCacheline (i);
          sc_regSet (3, 0);
          run_flag = 0;
          run_reg = 0;
          icounter = 0;
          printFlags ();
          sc_icounterSet (0);
          printCell (cursor_pos, WHITE, DEFAULT);
          printCell (icounter, BLACK, WHITE);
        }
      while (!run_reg)
        {
          CU ();
          if (icounter < 128)
            printCell (icounter, WHITE, DEFAULT);
          sc_icounterGet (&icounter);
          sc_regGet (3, &run_reg);
          if (run_reg && key != t)
            icounter = cursor_pos;
          else if (run_reg && key == t && icounter < 128)
            cursor_pos = icounter;
          else if (key == t && icounter == 128)
            icounter = cursor_pos;
          printFlags ();
          if (icounter < 128)
            {
              if (icounter - 1 >= 0)
                printCell (icounter - 1, WHITE, DEFAULT);
              printCell (icounter, BLACK, WHITE);
            }
        }
      if (key == RIGHT)
        {
          if (cursor_pos + 1 == 128)
            {
              printCell (cursor_pos, WHITE, DEFAULT);
              cursor_pos = -1;
            }
          else
            printCell (cursor_pos, WHITE, DEFAULT);
          printCell (cursor_pos + 1, BLACK, WHITE);
          (cursor_pos)++;
        }
      if (key == LEFT)
        {
          if (cursor_pos - 1 == -1)
            {
              printCell (cursor_pos, WHITE, DEFAULT);
              cursor_pos = 128;
            }
          else
            printCell (cursor_pos, WHITE, DEFAULT);
          printCell (cursor_pos - 1, BLACK, WHITE);
          (cursor_pos)--;
        }
      if (key == UP)
        {
          if (cursor_pos - 10 < 0)
            {
              printCell (cursor_pos, WHITE, DEFAULT);
              if (cursor_pos == DEFAULT || cursor_pos == 9)
                cursor_pos -= 10;
              cursor_pos += 130;
            }
          else
            printCell (cursor_pos, WHITE, DEFAULT);
          printCell (cursor_pos - 10, BLACK, WHITE);
          (cursor_pos) -= 10;
        }
      if (key == DOWN)
        {
          if (cursor_pos + 10 > 127)
            {
              printCell (cursor_pos, WHITE, DEFAULT);
              if (cursor_pos == 118 || cursor_pos == 119)
                cursor_pos += 10;
              cursor_pos -= 130;
            }
          else
            printCell (cursor_pos, WHITE, DEFAULT);
          printCell (cursor_pos + 10, BLACK, WHITE);
          (cursor_pos) += 10;
        }
      if (key == l)
        {
          rk_mytermregime (1, 0, 1, 1, 0);
          rk_loadfile ();
          rk_mytermregime (1, 0, 1, 0, 0);
          printCell (cursor_pos, BLACK, WHITE);
        }
      if (key == s)
        {
          rk_mytermregime (1, 0, 1, 1, 0);
          rk_savefile ();
          rk_mytermregime (1, 0, 1, 0, 0);
        }
      if (key == i)
        {
          rk_mytermrestore ();
          main (file_count, (char **)filename);
          break;
        }
      if (key == F5)
        {
          mt_gotoXY (69, 2);
          int fd = 0, value = 0;
          open_terminal (&fd);
          write (fd, "     ", 6);
          rk_readvalue (&value, 10);
          sc_accumulatorSet (value);
          close (fd);
          printAccumulator ();
        }
      if (key == F6)
        {
          mt_gotoXY (79, 5);
          int fd = 0, value = 0;
          open_terminal (&fd);
          write (fd, "     ", 6);
          rk_readvalue (&value, 10);
          sc_icounterSet (value);
          close (fd);
          printCounters ();
        }
      sc_memoryGet (cursor_pos, &ram_value);
      if (key == ENTER)
        {
          int value = ram_value;
          printCell (cursor_pos, BLACK, DEFAULT);
          rk_readvalue (&value, 10);
          sc_memorySet (cursor_pos, value);
          printCell (cursor_pos, BLACK, WHITE);
          printDecodedCommand (value);
        }
      else
        printDecodedCommand (ram_value);
      PrintBigCell (cursor_pos, filename[0]);
      rk_readkey (&key);
    }
}

void
update_timer (int icounter, int *value)
{
  int tacts_for_vait = 0;
  if (sc_cacheGet (icounter, value))
    {
      tacts_for_vait = 10;
    }
  else
    tacts_for_vait = 1;
  if (key != t)
    {
      for (int i = tacts_for_vait; i >= 0; i--)
        {
          sc_clocksCountSet (i);
          printCounters ();
          pause ();
        }
    }
  for (int i = 0; i < CACHELINES_NUM; i++)
    printCacheline (i);
  printCounters ();
  printCommand ();
}

void
CU (void)
{
  int icount = 0, value = 0, sign = 0, command = 0, operand = 0, flag = 0;
  sc_icounterGet (&icount);
  if (icount < 128)
    {
      update_timer (icount++, &value);
      sc_updateLivetime ();
      sc_icounterSet (icount);
      sc_commandDecode (value, &sign, &command, &operand);
      flag = ALU (command, operand);

      if (flag == FAILURE_COMMAND)
        {
          sc_regSet (4, 1);
          sc_regSet (3, 1);
        }
      else if (flag == CALC_OWERFLOW)
        sc_regSet (0, 1);
      else if (flag == DIV_ZERO)
        sc_regSet (1, 1);
    }
  else
    {
      sc_regSet (2, 1);
      sc_regSet (3, 1);
      sc_load_cache_to_memory ();
    }
}

int
ALU (int command, int operand)
{
  int ret = ZAEBOK, value = 0, mem_value = 0, sign = 0, comm = 0, oper = 0;
  switch (command)
    {
    case 0x0: // NOP
      break;
    case 0x1: // CPUINFO
      CPUINFO ();
      break;
    case 0xA: // READ
      READ (operand, io_data);
      break;
    case 0xB: // WRITE
      WRITE (operand, io_data);
      break;
    case 0x14: // LOAD
      sc_cacheGet (operand, &value);
      sc_accumulatorSet (value);
      printAccumulator ();
      break;
    case 0x15: // STORE
      sc_accumulatorGet (&value);
      sc_cacheSet (operand, value);
      printCell (operand, WHITE, DEFAULT);
      break;
    case 0x1E: // ADD
      ret = ADD (operand);
      add_flag = ret;
      printAccumulator ();
      break;
    case 0x1F: // SUB
      ret = SUB (operand);
      printAccumulator ();
      break;
    case 0x20: // DIVIDE
      ret = DIV (operand);
      printAccumulator ();
      break;
    case 0x21: // MUL
      ret = MUL (operand);
      printAccumulator ();
      break;
    case 0x28: // JUMP
      sc_icounterSet (operand);
      break;
    case 0x29: // JNEG
      sc_accumulatorGet (&value);
      sc_commandDecode (value, &sign, &comm, &oper);
      if (sign)
        sc_icounterSet (operand);
      break;
    case 0x2A: // JZ
      sc_accumulatorGet (&value);
      sc_commandDecode (value, &sign, &comm, &oper);
      if (!comm && !oper)
        sc_icounterSet (operand);
      break;
    case 0x2B: // HALT
      sc_regSet (3, 1);
      sc_load_cache_to_memory ();
      break;
    case 0x33: // NOT
      sc_accumulatorGet (&value);
      sc_cacheSet (operand, ~value);
      printCell (operand, WHITE, DEFAULT);
      break;
    case 0x34: // AND
      sc_accumulatorGet (&value);
      sc_cacheGet (operand, &mem_value);
      sc_accumulatorSet (value && mem_value);
      printAccumulator ();
      break;
    case 0x37: // JNS
      sc_accumulatorGet (&value);
      sc_commandDecode (value, &sign, &comm, &oper);
      if (!sign)
        sc_icounterSet (operand);
      break;
    case 0x38: // JC
      if (add_flag == 2)
        sc_icounterSet (operand);
      break;
    default:
      ret = FAILURE_COMMAND;
      break;
    }
  return ret;
}

void
init_all ()
{
  mt_clrscr ();
  sc_memoryInit ();
  sc_icounterInit ();
  sc_regInit ();
  sc_accumulatorInit ();
  sc_cacheInit ();
  for (int i = 0; i < 5; i++)
    sprintf (io_data[i], "         ");
}

void
impulse_generator ()
{
  struct itimerval nval, oval;
  signal (SIGALRM, IRC);
  signal (SIGUSR1, IRC);

  nval.it_interval.tv_sec = 0;
  nval.it_interval.tv_usec = 100000;
  nval.it_value.tv_sec = 1;
  nval.it_value.tv_usec = 0;

  setitimer (ITIMER_REAL, &nval, &oval);
}

void
print_all (int fd)
{
  mt_enterAltMode ();
  bc_drawBorders ();
  for (int i = 0; i < 128; i++)
    printCell (i, WHITE, DEFAULT);
  printCell (0, BLACK, WHITE);
  for (int i = 0; i < CACHELINES_NUM; i++)
    printCacheline (i);
  PrintBigCell (0, filename[0]);
  mt_exitAltMode ();
  mt_setbgcolor (DEFAULT);
  mt_setfgcolor (WHITE);
  printFlags ();
  printCounters ();
  printCommand ();
  printAccumulator ();
  printButtons ();
  mt_exitAltMode ();
  mt_gotoXY (1, 26);
  char *str = "Введите имя файла для загрузки: ";
  write (fd, str, strlen (str));
}

void
main_loop ()
{
  rk_mytermsave ();
  rk_mytermregime (1, 0, 1, 0, 0);
  moveCursor ();
  rk_mytermrestore ();
  mt_gotoXY (1, 31);
}

int
read_font (int argc, char *argv[])
{
  int fd_font = 0;
  if (argc >= 2)
    {
      fd_font = open (argv[1], O_RDONLY);
      file_count = 2;
      strncpy (filename[0], argv[1], strlen (argv[1]));
    }
  else
    {
      fd_font = open ("console/font.bin", O_RDONLY);
      file_count = 1;
      strncpy (filename[0], "console/font.bin", 17);
    }

  return fd_font;
}