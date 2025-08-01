#include "myReadKey.h"

int
main ()
{
  //   for (int i = 65; i < 130; i++)
  //     printf ("%c,", i);
  // unsigned long long int ch = 0;
  enum Keys keys = ENTER;
  // for(int i = 0; i < 10; i++, keys++)
  //     printf("%d\n", keys);
  // rk_readkey (&keys);
  rk_mytermsave ();
  rk_mytermregime (1, 0, 1, 0, 0);
  while (keys != ESCAPE)
    {
      rk_readkey (&keys);
      printf ("%d\n", keys);
    }
  rk_mytermrestore ();
}