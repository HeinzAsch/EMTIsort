#ifndef SORT_H
#define SORT_H

#include <time.h>

#include "sort_and_assemble_griflist.h"
#include "map.h"

FILE* out;

int prev_TSUP, min_TSUP, max_TSUP, minmax_DROPPED, pileup_DROPPED, cfd_DROPPED, map_DROPPED, zero_DROPPED, total_FRAGMENTS;
int analyze_grif_fragment(Grif_event*, short*){return -1;};
#endif
