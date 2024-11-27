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
  unsigned anodeTop; //channel 0
  unsigned anodeMiddle; //channel 1
  unsigned anodeBottom; //channel 2
  unsigned cathodeRight; //channel 3
  unsigned cathodeLeft; //channel 4
  unsigned cathodeTop; //channel 5
  unsigned cathodeBottom; //channel 6
  unsigned anodeTrigger; //channel 7, OR of Anodes
  unsigned RF; //channel 8, ISAC RF
}etnode;

int et_print_list(int, int, etnode*);
int et_store_list(int, etnode*, FILE*);

#endif
