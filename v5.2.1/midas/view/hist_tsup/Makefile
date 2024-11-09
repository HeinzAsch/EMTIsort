CC = g++
CFLAGS   = -g0 -O -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)

INC = -I$(ROOTINC)\
      -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/utils\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/midas/state-machine

BIN=$(EMTIsort)/bin/midas
SORT= sort.o\
	$(EMTIsort)/current/midas/state-machine/sort_but_not_assemble.a\
        $(EMTIsort)/current/utils/utils.a\
       $(EMTIsort)/current/midas/map/map.a\
	$(EMTIsort)/current/midas/decoder/decoder.a
sort:$(SORT)
	$(CC) -o $(BIN)/midas_view_hist_tsup $(SORT) $(CFLAGS) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
