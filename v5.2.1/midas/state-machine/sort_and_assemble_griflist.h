#ifndef STATE_MACHINE_ASSEMBLE_GRIF_H
#define STATE_MACHINE_ASSEMBLE_GRIF_H

#define DEPTH       40000000
#define SHIFT         10000


#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_SORT       3
#define ANALYZE_DATA      4

#include "grif-format.h"
#include "midas-format.h"
#include "SFU-common.h"
#include "map.h"
#include "griflist-format.h"

extern int prev_TSUP, min_TSUP, max_TSUP, minmax_DROPPED, pileup_DROPPED, cfd_DROPPED, map_DROPPED, zero_DROPPED, total_FRAGMENTS;

extern int analyze_list(int,int,node*);
int sort_list(data_pointers *, node*);
int add_node(node*, data_pointers *, node*);
void sort_and_assemble(char*,char*);
void sort_and_assemble_subruns(char*,char*);
int unpack_grif_bank_for_assembly(int *, int , data_pointers* , node*, gmap*);
int analyze_fragment_for_assembly(Grif_event*, short*,data_pointers*, node*, gmap*);
int get_fragments_for_assembly(data_pointers*, node*, gmap*);
int isonmap(node*, gmap*);

#endif
