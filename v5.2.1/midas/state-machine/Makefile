CC = g++
CFLAGS   = -g -O3 -Wall -fPIC 

ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(EMTIsort)/current/griflist-format\
      -I$(EMTIsort)/current/emmatlist-format\
      -I$(EMTIsort)/current/emmaalist-format\
      -I$(ROOTINC)

BIN=$(EMTIsort)/current/midas/state-machine

SORT_NOT_ASSEMBLE= sort_but_not_assemble.o
SORT_AND_ASSEMBLE_GRIFLIST= sort_and_assemble_griflist.o
SORT_AND_ASSEMBLE_EMMATLIST= sort_and_assemble_emmatlist.o
SORT_AND_ASSEMBLE_EMMAALIST= sort_and_assemble_emmaalist.o

all:  sort_but_not_assemble sort_and_assemble_griflist sort_and_assemble_emmatlist sort_and_assemble_emmaalist

sort_but_not_assemble:$(SORT_NOT_ASSEMBLE)
	$ ar rcs $(BIN)/sort_but_not_assemble.a $(SORT_NOT_ASSEMBLE)

sort_but_not_assemble.o:sort_but_not_assemble.c sort_but_not_assemble.h 
	$(CC) -c -o sort_but_not_assemble.o sort_but_not_assemble.c $(CFLAGS) $(INC)

sort_and_assemble_griflist:$(SORT_AND_ASSEMBLE_GRIFLIST)
	$ ar rcs $(BIN)/sort_and_assemble_griflist.a $(SORT_AND_ASSEMBLE_GRIFLIST)

sort_and_assemble_griflist.o:sort_and_assemble_griflist.c sort_and_assemble_griflist.h 
	$(CC) -c -o sort_and_assemble_griflist.o sort_and_assemble_griflist.c $(CFLAGS) $(INC)

sort_and_assemble_emmatlist:$(SORT_AND_ASSEMBLE_EMMATLIST)
	$ ar rcs $(BIN)/sort_and_assemble_emmatlist.a $(SORT_AND_ASSEMBLE_EMMATLIST)

sort_and_assemble_emmatlist.o:sort_and_assemble_emmatlist.c sort_and_assemble_emmatlist.h 
	$(CC) -c -o sort_and_assemble_emmatlist.o sort_and_assemble_emmatlist.c $(CFLAGS) $(INC)

sort_and_assemble_emmaalist:$(SORT_AND_ASSEMBLE_EMMAALIST)
	$ ar rcs $(BIN)/sort_and_assemble_emmaalist.a $(SORT_AND_ASSEMBLE_EMMAALIST)

sort_and_assemble_emmaalist.o:sort_and_assemble_emmaalist.c sort_and_assemble_emmaalist.h 
	$(CC) -c -o sort_and_assemble_emmaalist.o sort_and_assemble_emmaalist.c $(CFLAGS) $(INC)

clean:
	rm -rf *.o *~
very-clean:
	rm -rf *.a *.o *.*~ *~
