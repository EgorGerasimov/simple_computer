#pragma once

#include "mySimpleComputer.h"
#include "myTerm.h"

void bc_drawBorders ();
int bc_box (int x1, int y1, int x2, int y2, enum Colors box_fg,
            enum Colors box_bg, char *header, enum Colors header_fg,
            enum Colors header_bg);
int bc_getbigcharpos (int *big, int x, int y, int *value);
int bc_setbigcharpos (int *big, int x, int y, int value);
int bc_printbigchar (int big[2], int x, int y, enum Colors fg, enum Colors bg);
int bc_bigcharwrite (int fd, int big[18][2], int count);
int bc_bigcharread (int fd, int big[18][2], int need_count, int *count);
void PrintBigCell (int cursor_pos, char *filename);