#ifndef EMMATLIST_H
#define EMMATLIST_H

#include "map.h"

typedef struct et_data_pointers
{
  unsigned long proc;
  int    last;
  int    trig;
  size_t son;
}et_data_pointers;

typedef struct etnode
{
  unsigned long long    tsns;
  int                   trignum;
  unsigned              tsup;
  unsigned              ts;
  int                   trig;
  unsigned long long    trig_tsns;
}etnode;

int et_print_list(int, int, etnode*);
int et_store_list(int, etnode*, FILE*);

#endif
