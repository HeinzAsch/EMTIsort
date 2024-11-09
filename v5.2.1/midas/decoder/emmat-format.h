#ifndef EMMAT_FORMAT_H
#define EMMAT_FORMAT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "midas-format.h"


typedef struct emmat_fragment_struct {
  unsigned trignum;
  unsigned tslow;
  unsigned tshigh;
  unsigned geo;
  unsigned chanid;
  unsigned pcktid;
  //  unsigned eflag;
  unsigned fl[16];
  unsigned ft[16];
  unsigned lf[16];
  unsigned tf[16];
  unsigned ls[16];
  unsigned ts[16];
  unsigned lt[16];
  unsigned tt[16];
} emmat_event;


extern int analyze_emmat_fragment(emmat_event*);
int unpack_emmat_bank(int *, int);
int unpack_emmat_event(unsigned*, int, emmat_event*);

#endif
