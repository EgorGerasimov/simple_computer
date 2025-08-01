#include "console.h"

int
main (int argc, char *argv[])
{
  int rows = 0, cols = 0, fd = 0, fd_font = read_font (argc, argv);

  if (fd_font != -1)
    {
      if (!mt_getscreensize (&rows, &cols) && !open_terminal (&fd))
        {
          init_all ();
          impulse_generator ();
          print_all (fd);
          close (fd);
          main_loop ();
        }
      close (fd_font);
    }
  else
    printf ("Font not found!!!\n");
}