CC = g++
CFLAGS   = -O -Wall -fPIC 

INC = -I$(EMTIsort)/current/midas/decoder

BIN=$(EMTIsort)/bin/midas

SORT= sort.o\
       $(EMTIsort)/current/midas/decoder/decoder.a

sort:$(SORT)
	$(CC) -o $(BIN)/midas_block_dump $(SORT) $(CFLAGS) $(ROOT) -lm -ldl

sort.o:sort.c 
	$(CC) -c -o sort.o sort.c $(CFLAGS) $(INC)

clean:
	rm -rf sort *.o *~
