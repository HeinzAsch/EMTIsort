CC = g++
CFLAGS   = -O3 -Wall -Wno-narrowing -fPIC

INC = -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(EMTIsort)/current/griflist/griflist-format\
      -I$(ROOTINC)

BIN = $(EMTIsort)/current/griflist-format

GRIFLIST-FORMAT=griflist-format.o

griflist-format:$(GRIFLIST-FORMAT)
	$ ar rcs $(BIN)/griflist-format.a $(GRIFLIST-FORMAT)

griflist-format.o:griflist-format.c griflist-format.h
	$(CC) -c -o griflist-format.o $(CFLAGS) griflist-format.c $(INC)

clean:
	rm -rf *.o

very-clean:
	rm -rf *.a *.o *.*~ *~ sort
