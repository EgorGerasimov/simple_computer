#include <mySimpleComputer.h>

#define COMMANDS                                                              \
  ((char const *[]){                                                          \
      "NOP",    "00", "CPUINFO", "01", "READ", "0A", "WRITE", "0B",           \
      "LOAD",   "14", "STORE",   "15", "ADD",  "1E", "SUB",   "1F",           \
      "DEVIDE", "20", "MUL",     "21", "JUMP", "28", "JNEG",  "29",           \
      "JZ",     "2A", "HALT",    "2B", "NOT",  "33", "AND",   "34",           \
      "JNS",    "37", "JC",      "38", "=" })

int
main (int argc, char *argv[])
{
  char *line = malloc (sizeof (char) * 256);
  size_t read_flag = 0, buffer_size = 256;
  if (argc == 3)
    {
      FILE *file = fopen (argv[1], "rb");
      if (file)
        {
          int index = 0;
          while ((read_flag = getline (&line, &buffer_size, file))
                 != (size_t)-1)
            {
              char *mal = strtok (line, " ");
              index = strtol (mal, NULL, 10);
              if ((index >= 1 && index <= 127)
                  || (index == 0 && mal[0] == '0'))
                {
                  mal = strtok (NULL, " ");
                  int flag = -1, i = 0, command = 0;
                  for (; i < 37 && flag; i += 2)
                    flag = strcmp (mal, COMMANDS[i]);
                  if (!flag)
                    {
                      mal = strtok (NULL, " ");
                      int operand = strtol (mal, NULL, 10);
                      if (i - 2 != 36)
                        {
                          command = strtol (COMMANDS[i - 1], NULL, 16);
                          if ((operand >= 1 && operand <= 127)
                              || (operand == 0 && mal[0] == '0'))
                            sc_memorySet (index, (command << 7) | operand);
                          else
                            {
                              flag = -1;
                              printf ("Incorrect data\n");
                            }
                        }
                      else
                        {
                          if ((operand >= 1 && operand <= 16383)
                              || (operand == 0 && mal[0] == '0'))
                            sc_memorySet (index, operand);
                          else if ((operand < 0 && operand >= -16383))
                            sc_memorySet (index, (1 << 14) | (operand * -1));
                          else
                            {
                              flag = -1;
                              printf ("Incorrect data\n");
                            }
                        }
                      if (!flag)
                        {
                          char filename[256] = { 0 };
                          sprintf (filename, "../console/%s", argv[2]);
                          sc_memorySave (filename);
                        }
                    }
                  else
                    printf ("Incorrect data1\n");
                }
              else
                printf ("Incorrect data2\n");
            }
          fclose (file);
        }
      else
        printf ("File not found3\n");
    }
  else
    printf (
        "Not enough arguments\nExample: ./simpleassembler файл.sa файл.o\n");
}