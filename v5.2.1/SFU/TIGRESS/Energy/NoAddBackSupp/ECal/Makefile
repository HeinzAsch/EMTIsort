CC = g++
CFLAGS   = -O -g -Wall -fPIC  $(shell $(ROOTSYS)/bin/root-config --cflags)
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(ROOTINC)\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/calibrator

BIN=/$(EMTIsort)/bin/SFU

SORT= sort.o\
      $(EMTIsort)/current/SFU-format/SFU-format.a\
      $(EMTIsort)/current/calibrator/calibrator.a\
      $(EMTIsort)/current/utils/utils.a

sort:$(SORT)
	$(CC) -o $(BIN)/sfu_TIGRESS_ECal $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c sort.h
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
