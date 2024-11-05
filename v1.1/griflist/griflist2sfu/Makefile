CC = g++
CFLAGS   = -g -O -Wall -fPIC
ROOT =  $(shell $(ROOTSYS)/bin/root-config --glibs)
INC = -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/griflist-format\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(ROOTINC)

BIN=$(EMTIsort)/bin/griflist
SORT= sort.o\
       $(EMTIsort)/current/midas/decoder/decoder.a\
       $(EMTIsort)/current/utils/utils.a\
       $(EMTIsort)/current/SFU-format/SFU-format.a\
       $(EMTIsort)/current/griflist-format/griflist-format.a\
       $(EMTIsort)/current/midas/map/map.a

sort:$(SORT)
	$(CC) -o $(BIN)/griflist2sfu $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
