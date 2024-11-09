CC = g++
CFLAGS   = -O3 -Wall -Wno-narrowing -fPIC

INC = -I$(EMTIsort)/current/midas/decoder\
      -I$(EMTIsort)/current/midas/map\
      -I$(EMTIsort)/current/SFU-format\
      -I$(EMTIsort)/current/utils\
      -I$(ROOTINC)

BIN = $(EMTIsort)/current/emmaalist-format

EMMAALIST-FORMAT=emmaalist-format.o

emmaalist-format:$(EMMAALIST-FORMAT)
	$ ar rcs $(BIN)/emmaalist-format.a $(EMMAALIST-FORMAT)

emmaalist-format.o:emmaalist-format.c emmaalist-format.h
	$(CC) -c -o emmaalist-format.o $(CFLAGS) emmaalist-format.c $(INC)

clean:
	rm -rf *.o

very-clean:
	rm -rf *.a *.o *.*~ *~ sort
