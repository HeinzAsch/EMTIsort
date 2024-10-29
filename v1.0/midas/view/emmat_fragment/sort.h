#ifndef SORT_H
#define SORT_H

#include "sort_but_not_assemble.h"

int wrap;
unsigned last;
long long counter;

int unpack_griff=0;
int unpack_emmat=1;
int unpack_emmaa=0;

/*================================================================*/
int analyze_grif_fragment(Grif_event* ptr, short* waveform)
{
  return -1;
}

/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  return -1;
}


#endif
