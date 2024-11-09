#ifndef SORT_H
#define SORT_H

#include <time.h>
#include "griflist-format.h"

#define MAXWIN 16384

long long gate_low, gate_high;
long long dt;

int analyze_list(int,int,node*){return -1;};
int analyze_fragment(Grif_event*, short*){return -1;};
#endif
