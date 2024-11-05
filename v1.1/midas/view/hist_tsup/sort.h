#ifndef SORT_H
#define SORT_H

#include "SFU-common.h"
#include "sort_but_not_assemble.h"

int h[S32K];
int h2[S32K];
int counter;

int unpack_griff=1;
int unpack_emmat=0;
int unpack_emmaa=0;

/*================================================================*/
int analyze_emmat_fragment(emmat_event* ptr)
{
  return -1;
}
/*================================================================*/
int analyze_emmaa_fragment(emmaa_event* ptr)
{
  return -1;
}

#endif
