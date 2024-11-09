CC = g++
CFLAGS   = -O -Wall -fPIC
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(EMTIsort)/current/griflist-format\
      -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/state-machine\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(ROOTINC)

BIN=$(EMTIsort)/bin/midas

SORT= sort.o\
       $(EMTIsort)/current/midas/state-machine/sort_and_assemble_griflist.a\
       $(EMTIsort)/current/griflist-format/griflist-format.a\
       $(EMTIsort)/current/midas/decoder/decoder.a\
       $(EMTIsort)/current/utils/utils.a\
       $(EMTIsort)/current/midas/map/map.a

sort:$(SORT)
	$(CC) -o $(BIN)/grif2list $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
