#include "myBigChars.h"

int font[18][2];

void
font_s ()
{
  for (int i = 1; i <= 8; i++)
    {
      for (int j = 1; j <= 2; j++)
        bc_setbigcharpos (font[0], j, i, 1);
      for (int j = 3; j <= 7 && (i == 1 || i == 8); j++)
        bc_setbigcharpos (font[0], j, i, 1);
      for (int j = 6; j <= 7; j++)
        bc_setbigcharpos (font[0], j, i, 1);

      for (int j = 4; j <= 7; j++)
        bc_setbigcharpos (font[1], j, i, 1);
      if (i > 1 && i < 4)
        {
          for (int j = 5 - i; j < 4; j++)
            bc_setbigcharpos (font[1], j, i, 1);
        }

      for (int j = 1; j <= 7 && i == 8; j++)
        bc_setbigcharpos (font[2], j, i, 1);
      for (int j = 1; j <= 2 && (i == 2 || i == 7); j++)
        bc_setbigcharpos (font[2], j, i, 1);
      for (int j = 3; j <= 4 && (i == 1 || i == 6); j++)
        bc_setbigcharpos (font[2], j, i, 1);
      for (int j = 5; j <= 6 && (i == 2 || i == 5); j++)
        bc_setbigcharpos (font[2], j, i, 1);
      for (int j = 6; j <= 7 && (i == 3 || i == 4); j++)
        bc_setbigcharpos (font[2], j, i, 1);

      for (int j = 1; j <= 2 && (i == 2 || i == 7); j++)
        bc_setbigcharpos (font[3], j, i, 1);
      for (int j = 2; j <= 7 && (i == 1 || i == 8); j++)
        bc_setbigcharpos (font[3], j, i, 1);
      for (int j = 4; j <= 5 && (i == 4 || i == 5); j++)
        bc_setbigcharpos (font[3], j, i, 1);
      for (int j = 6; j <= 7; j++)
        bc_setbigcharpos (font[3], j, i, 1);

      for (int j = 6; j <= 7; j++)
        bc_setbigcharpos (font[4], j, i, 1);
      for (int j = 3; j <= 5 && i == 5; j++)
        bc_setbigcharpos (font[4], j, i, 1);
      for (int j = 1; j <= 2 && i <= 5; j++)
        bc_setbigcharpos (font[4], j, i, 1);

      for (int j = 1; (j <= 7 && i == 1) || ((i == 4 || i == 8) && j <= 5);
           j++)
        bc_setbigcharpos (font[5], j, i, 1);
      for (int j = 1; j <= 2 && i < 4; j++)
        bc_setbigcharpos (font[5], j, i, 1);
      for (int j = 6; j <= 7 && i > 4 && i < 8; j++)
        bc_setbigcharpos (font[5], j, i, 1);

      for (int j = 1; j <= 2; j++)
        bc_setbigcharpos (font[6], j, i, 1);
      for (int j = 3; j <= 7 && (i == 1 || i == 5 || i == 8); j++)
        bc_setbigcharpos (font[6], j, i, 1);
      for (int j = 6; j <= 7 && i >= 5; j++)
        bc_setbigcharpos (font[6], j, i, 1);

      for (int j = 1; j <= 7 && i == 1; j++)
        bc_setbigcharpos (font[7], j, i, 1);
      for (int j = 0; j <= 1 && i > 1; j++)
        bc_setbigcharpos (font[7], 8 - i + j, i, 1);

      for (int j = 1; j <= 2; j++)
        bc_setbigcharpos (font[8], j, i, 1);
      for (int j = 3; j <= 7 && (i == 1 || i == 4 || i == 5 || i == 8); j++)
        bc_setbigcharpos (font[8], j, i, 1);
      for (int j = 6; j <= 7; j++)
        bc_setbigcharpos (font[8], j, i, 1);

      for (int j = 6; j <= 7; j++)
        bc_setbigcharpos (font[9], j, i, 1);
      for (int j = 1; j <= 7 && (i == 1 || i == 5 || i == 8); j++)
        bc_setbigcharpos (font[9], j, i, 1);
      for (int j = 1; j <= 2 && i < 5; j++)
        bc_setbigcharpos (font[9], j, i, 1);

      bc_setbigcharpos (font[10], (4 - (int)(i / 2.1)), i, 1);
      bc_setbigcharpos (font[10], (4 + (int)(i / 2.1)), i, 1);
      for (int j = 3; j <= 5 && i == 6; j++)
        bc_setbigcharpos (font[10], j, i, 1);

      for (int j = 1;
           j <= 2 || ((i == 4 || i == 5 || i == 1 || i == 8) && j <= 5); j++)
        bc_setbigcharpos (font[11], j, i, 1);
      for (int j = 6; j <= 7 && ((i == 2 || i == 3 || i == 6 || i == 7)); j++)
        bc_setbigcharpos (font[11], j, i, 1);

      for (int j = 1; (j <= 2 && (i != 1 && i != 8)); j++)
        bc_setbigcharpos (font[12], j, i, 1);
      for (int j = 3; (j <= 5 && (i == 1 || i == 8)); j++)
        bc_setbigcharpos (font[12], j, i, 1);
      for (int j = 6; (j <= 7 && (i == 2 || i == 7)); j++)
        bc_setbigcharpos (font[12], j, i, 1);

      for (int j = 1; j <= 2 || ((i == 1 || i == 8) && j <= 3); j++)
        bc_setbigcharpos (font[13], j, i, 1);
      if (i <= 4)
        {
          bc_setbigcharpos (font[13], i + 3, i, 1);
          bc_setbigcharpos (font[13], i + 3, 9 - i, 1);
        }

      for (int j = 1; j <= 2; j++)
        bc_setbigcharpos (font[14], j, i, 1);
      for (int j = 3; j <= 7 && (i == 1 || i == 4 || i == 5 || i == 8); j++)
        bc_setbigcharpos (font[14], j, i, 1);

      for (int j = 1; j <= 2; j++)
        bc_setbigcharpos (font[15], j, i, 1);
      for (int j = 1; (j <= 7 && i == 1) || (j <= 6 && i == 4); j++)
        bc_setbigcharpos (font[15], j, i, 1);
    }

  for (int i = 2; i <= 7; i++)
    {
      if (i >= 4 && i <= 5)
        {
          for (int j = 2; j <= 7; j++)
            bc_setbigcharpos (font[16], j, i, 1);
        }
      else
        {
          for (int j = 4; j <= 5; j++)
            bc_setbigcharpos (font[16], j, i, 1);
        }
    }

  for (int j = 1; j <= 7; j++)
    {
      bc_setbigcharpos (font[17], j, 4, 1);
      bc_setbigcharpos (font[17], j, 5, 1);
    }
}

int
main ()
{
  int fd = open ("console/font.bin", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  if (fd)
    {
      font_s ();
      bc_bigcharwrite (fd, font, 18);
      close (fd);
    }
}