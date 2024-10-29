#ifndef STATE_MACHINE_NOT_ASSEMBLE_H
#define STATE_MACHINE_NOT_ASSEMBLE_H

#define NEXT_EVENT        0
#define GET_FRAGMENTS     1
#define END_OF_RECORD     2
#define END_OF_FILE       3
#define ANALYZE_DATA      4

#include "midas-format.h"
#include "grif-format.h"
#include "emmat-format.h"
#include "emmaa-format.h"


#include <stdlib.h>

extern int unpack_griff;
extern int unpack_emmat;
extern int unpack_emmaa;
void sort_but_not_assemble(char*);
int  get_fragments(long*);

#endif
