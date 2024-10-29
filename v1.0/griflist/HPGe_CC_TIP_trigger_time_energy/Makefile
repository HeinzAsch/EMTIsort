CC = g++
CFLAGS   = -O -Wall -fPIC $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)

INC = -I$(EMTIsort)/current/griflist-format\
      -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(ROOTINC)

BIN=$(EMTIsort)/bin/griflist

SORT= sort.o\
       $(EMTIsort)/current/griflist-format/griflist-format.a\
       $(EMTIsort)/current/midas/map/map.a

sort:$(SORT)
	$(CC) -o $(BIN)/griflist_HPGe_CC_TIP_trigger_time_energy $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
