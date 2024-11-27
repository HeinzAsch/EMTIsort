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
  //EMMA TDC output
  //Chan 0-9 : Anode Top, Middle, Bottom, Cathode Right, Left, Top, Bottom, Trigger (Anode OR), RF
  unsigned fl[16]; //flag for leading edge
  unsigned ft[16]; //flag for trailing edge
  unsigned lf[16]; //leading edge, first
  unsigned tf[16]; //trailing edge, first
  unsigned ls[16]; //leading edge, second
  unsigned ts[16]; //trailing edge, second
  unsigned lt[16]; //leading edge, third
  unsigned tt[16]; //trailing edge, third
} emmat_event;


extern int analyze_emmat_fragment(emmat_event*);
int unpack_emmat_bank(int *, int);
int unpack_emmat_event(unsigned*, int, emmat_event*);

#endif
