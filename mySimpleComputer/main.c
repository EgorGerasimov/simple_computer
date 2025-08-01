#include "mySimpleComputer.h"
// extern int accumulator, commands_count, RAM[RAM_SIZE];

int
main ()
{
  sc_cacheInit ();
  printf ("kcjbdkj");
  // sc_memoryInit ();
  // sc_accumulatorInit ();
  // sc_icounterInit ();
  // sc_regInit ();
  // for (int i = 0; i < 127; i += 3)
  //   sc_commandEncode (1, i, i, &(RAM[i]));
  // for (int i = 0, sign = 0, command = 0, operand = 0; i < 127; i++)
  //   {
  //     sc_commandDecode (RAM[i], &sign, &command, &operand);
  //     printf ("0x%-4x ", RAM[i]);
  //     if (!(i % 10) && i != 0)
  //       printf ("\n");
  //   }
  // putchar ('\n');
  // printf ("wrong encode RAM: %d\n",
  //         sc_commandEncode (1, 0xfffffff, 0, &(RAM[0])));
  // sc_regSet (0, 1);
  // sc_regSet (2, 1);
  // printf ("wrong reg: %d\n", sc_regSet (0, 999));
  // printFlags ();
  // sc_accumulatorSet (54);
  // printAccumulator ();
  // printf ("wrong acc: %d\n", sc_accumulatorSet (0xfffffff));
  // printAccumulator ();
  // sc_icounterSet (123);
  // printCounters ();
  // printf ("wrong counter: %d\n", sc_icounterSet (0xfffffff));
  // printCounters ();
  // int sign = 0, command = 0, operand = 0;
  // sc_commandDecode (RAM[123], &sign, &command, &operand);
  // printf ("sign: %d\ncommand: %d\noperand: %d\nRAM[123]: 0x%x\n", sign,
  //         command, operand, RAM[123]);
  // sc_commandDecode (accumulator, &sign, &command, &operand);
  // printf ("sign: %d\ncommand: %d\noperand: %d\naccumulator: 0x%x\n", sign,
  //         command, operand, accumulator);
  // sc_commandEncode (1, sign, command, &(RAM[123]));
  // printf ("RAM[123]: %d %x %o\n", RAM[123], RAM[123], RAM[123]);
  // ALU (10, 0);
  // int sign = 0, com = 0, oper = 0;
  // sc_commandDecode(val, &sign, &com, &oper);
  // printf("%d %d %d\n", sign, com, oper);
}