#include "myReadKey.h"

extern struct termios t_save, t_now;

int
rk_readkey (enum Keys *keys)
{
  int buffer[5] = { 0 };
  int bytes_read;
  bytes_read = read (STDIN_FILENO, buffer, sizeof (buffer));
  *keys = 0;
  if (bytes_read == 5 && memcmp (buffer, "\x1B[15~", 5) == 0)
    *keys = 5;
  else if (bytes_read == 5 && memcmp (buffer, "\x1B[17~", 5) == 0)
    *keys = 6;
  else
    *keys = buffer[0];
  return 1;
}

int
rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint)
{
  if (regime == 1)
    {
      t_now.c_lflag &= ~ICANON;
      t_now.c_cc[VTIME] = vtime;
      t_now.c_cc[VMIN] = vmin;
    }
  else
    t_now.c_lflag |= ICANON;

  echo ? (t_now.c_lflag |= ECHO) : (t_now.c_lflag &= ~ECHO);
  sigint ? (t_now.c_lflag |= ISIG) : (t_now.c_lflag &= ~ISIG);

  if (tcsetattr (STDIN_FILENO, TCSANOW, &t_now) != 0)
    return -1;

  return 0;
}

int
rk_mytermsave (void)
{
  if (tcgetattr (STDIN_FILENO, &t_save) != 0)
    return -1;
  return 0;
}

int
rk_mytermrestore (void)
{
  if (tcsetattr (STDIN_FILENO, TCSANOW, &t_save) != 0)
    return -1;
  return 0;
}