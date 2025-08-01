#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

enum Keys
{
  ENTER = 13,
  ESCAPE = 27,
  PLUS = 43,
  MINUS = 45,
  ZERO = 48,
  ONE,
  TWO,
  TREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  A = 65,
  B,
  C,
  D,
  E,
  F,
  G,
  H,
  I,
  J,
  K,
  L,
  M,
  N,
  O,
  P,
  Q,
  R,
  S,
  T,
  U,
  V,
  W,
  X,
  Y,
  Z,
  a = 97,
  b,
  c,
  d,
  e,
  f,
  g,
  h,
  i,
  j,
  k,
  l,
  m,
  n,
  o,
  p,
  q,
  r,
  s,
  t,
  u,
  v,
  w,
  x,
  y,
  z,
  UP = 4283163,
  DOWN = 4348699,
  LEFT = 4479771,
  RIGHT = 4414235,
  F5 = 5,
  F6 = 6
};

int rk_readkey (enum Keys *keys);
int rk_mytermregime (int regime, int vtime, int vmin, int echo, int sigint);
int rk_mytermsave (void);
int rk_mytermrestore (void);
int rk_readvalue (int *value, int timeout);
void rk_loadfile ();
void rk_savefile ();