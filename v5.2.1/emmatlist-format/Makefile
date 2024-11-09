CC = g++
CFLAGS   = -O3 -Wall -Wno-narrowing -fPIC

INC = -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(ROOTINC)

BIN = $(EMTIsort)/current/emmatlist-format

EMMATLIST-FORMAT=emmatlist-format.o

emmatlist-format:$(EMMATLIST-FORMAT)
	$ ar rcs $(BIN)/emmatlist-format.a $(EMMATLIST-FORMAT)

emmatlist-format.o:emmatlist-format.c emmatlist-format.h
	$(CC) -c -o emmatlist-format.o $(CFLAGS) emmatlist-format.c $(INC)

clean:
	rm -rf *.o

very-clean:
	rm -rf *.a *.o *.*~ *~ sort
