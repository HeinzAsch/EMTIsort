#ifndef EMMAALIST_H
#define EMMAALIST_H

#include "map.h"

typedef struct ea_data_pointers
{
  unsigned long proc;
  int    last;
  int    trig;
  size_t son;
}ea_data_pointers;

typedef struct eanode
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
  unsigned SSB; //channel 3
  unsigned IC[4]; //channels 16-19
}eanode;

int ea_print_list(int, int, eanode*);
int ea_store_list(int, eanode*, FILE*);

#endif
