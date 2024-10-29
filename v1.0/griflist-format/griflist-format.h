#ifndef GRIFLIST_H
#define GRIFLIST_H

#include "map.h"

typedef struct data_pointers
{
  unsigned long proc;
  int    last;
  int    trig;
  size_t son;
}data_pointers;

typedef struct node
{
  unsigned long long    tsns;
  int          chan;
  int          trig;
  int          tig_trig;
  int          csi_trig;
  int          emm_trig;
  unsigned long long    trig_tsns;
  channel      ch;
  ShapePar     wfit;
  double       t0;
}node;

int print_list(int, int, node*);
int store_list(int, node*, FILE*);
int sort_list(data_pointers *, node*);
int same_HPGe(node*, node*, gmap*);
int CC_channel(node*, gmap*);
int Seg_channel(node*, gmap*);
int Sup_channel(node*, gmap*);
int TIP_channel(node*, gmap*);
int EMMA_channel(node*, gmap*);
#endif
