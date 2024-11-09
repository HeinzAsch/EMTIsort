#ifndef STATE_MACHINE_ASSEMBLE_EMMAA_H
#define STATE_MACHINE_ASSEMBLE_EMMAA_H

#define DEPTH      40000000
#define SHIFT         10000


#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4
#define END_OF_SORT       5

#include "emmaa-format.h"
#include "midas-format.h"
#include "SFU-common.h"
#include "map.h"
#include "emmaalist-format.h"


extern int total_FRAGMENTS;

extern int analyze_list(int,int,eanode*);
int sort_list(ea_data_pointers *, eanode*);
int add_eanode(eanode*, ea_data_pointers *, eanode*);
void sort_and_assemble(char*,char*);
int unpack_emmaa_bank_for_assembly(int *, int , ea_data_pointers* , eanode*, gmap*);
int analyze_fragment_for_assembly(emmaa_event*, short*,ea_data_pointers*, eanode*, gmap*);
int get_fragments_for_assembly(ea_data_pointers*, eanode*, gmap*);


#endif
