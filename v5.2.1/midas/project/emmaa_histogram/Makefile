CC = g++
CFLAGS   = -g0 -O -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(ROOTINC)\
      -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/state-machine
BIN=$(EMTIsort)/bin/midas
SORT= sort.o\
	$(EMTIsort)/current/midas/state-machine/sort_but_not_assemble.a\
	$(EMTIsort)/current/midas/decoder/decoder.a
sort:$(SORT)
	$(CC) -o $(BIN)/project_emmaa_histogram $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
