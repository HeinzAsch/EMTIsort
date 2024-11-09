#ifndef EMMAA_FORMAT_H
#define EMMAA_FORMAT_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "midas-format.h"


typedef struct emmaa_fragment_struct {
  unsigned tslow;
  unsigned tshigh;
  unsigned adc[32];
  unsigned adcf[32];
  unsigned adchitpattern;
  unsigned adcfold;
} emmaa_event;


extern int analyze_emmaa_fragment(emmaa_event*);
int unpack_emmaa_bank(int *, int);
int unpack_emmaa_event(unsigned*, int, emmaa_event*);

#endif
