CC = g++
CFLAGS   = -g -O3 -Wall -fPIC 

ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(EMTIsort)/current/griflist-format\
      -I$(ROOTINC)
 
BIN=$(EMTIsort)/current/midas/state-machine

SORT_NOT_ASSEMBLE= sort_but_not_assemble.o
SORT_AND_ASSEMBLE_GRIFLIST= sort_and_assemble_griflist.o

all:  sort_but_not_assemble sort_and_assemble_griflist

sort_but_not_assemble:$(SORT_NOT_ASSEMBLE)
	$ ar rcs $(BIN)/sort_but_not_assemble.a $(SORT_NOT_ASSEMBLE)

sort_but_not_assemble.o:sort_but_not_assemble.c sort_but_not_assemble.h 
	$(CC) -c -o sort_but_not_assemble.o sort_but_not_assemble.c $(CFLAGS) $(INC)

sort_and_assemble_griflist:$(SORT_AND_ASSEMBLE_GRIFLIST)
	$ ar rcs $(BIN)/sort_and_assemble_griflist.a $(SORT_AND_ASSEMBLE_GRIFLIST)

sort_and_assemble_griflist.o:sort_and_assemble_griflist.c sort_and_assemble_griflist.h 
	$(CC) -c -o sort_and_assemble_griflist.o sort_and_assemble_griflist.c $(CFLAGS) $(INC)

clean:
	rm -rf *.o *~
very-clean:
	rm -rf *.a *.o *.*~ *~
