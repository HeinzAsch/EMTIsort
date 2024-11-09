#ifndef STATE_MACHINE_ASSEMBLE_EMMAT_H
#define STATE_MACHINE_ASSEMBLE_EMMAT_H

#define DEPTH      40000000
#define SHIFT         10000


#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4
#define END_OF_SORT       5

#include "emmat-format.h"
#include "midas-format.h"
#include "SFU-common.h"
#include "map.h"
#include "emmatlist-format.h"

extern int wrap;
extern unsigned tslast;

extern int total_FRAGMENTS;

extern int analyze_list(int,int,etnode*);
int sort_list(et_data_pointers *, etnode*);
int add_etnode(etnode*, et_data_pointers *, etnode*);
void sort_and_assemble(char*,char*);
void sort_and_assemble_subruns(char*,char*);
int unpack_emmat_bank_for_assembly(int *, int , et_data_pointers* , etnode*, gmap*);
int analyze_fragment_for_assembly(emmat_event*, short*,et_data_pointers*, etnode*, gmap*);
int get_fragments_for_assembly(et_data_pointers*, etnode*, gmap*);


#endif
