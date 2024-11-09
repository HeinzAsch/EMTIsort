CC = g++
CFLAGS   = -O -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(ROOTINC)\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/utils

BIN=$(EMTIsort)/bin/SFU

SORT= sort.o\
      $(EMTIsort)/current/SFU-format/SFU-format.a

sort:$(SORT)
	$(CC) -o $(BIN)/sfu_display_TIP $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c sort.h
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
