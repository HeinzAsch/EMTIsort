#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "midas-format.h"
#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4
#include <vector>


struct bid
{
  char name[5];
  long cts;
}bid;

struct bid *blocks;
int    nbid;

#endif
