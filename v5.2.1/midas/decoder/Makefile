CC = g++
CFLAGS   = -O3 -Wall -fPIC

BIN = $(EMTIsort)/current/midas/decoder

DECODER=midas-format.o grif-format.o emmat-format.o emmaa-format.o

decoder:$(DECODER)
	$ ar rcs $(BIN)/decoder.a $(DECODER)

emmaa-format.o:emmaa-format.c emmaa-format.h
	$(CC) -c -o emmaa-format.o $(CFLAGS) emmaa-format.c

emmat-format.o:emmat-format.c emmat-format.h
	$(CC) -c -o emmat-format.o $(CFLAGS) emmat-format.c

grif-format.o:grif-format.c grif-format.h
	$(CC) -c -o grif-format.o $(CFLAGS) grif-format.c

midas-format.o:midas-format.c midas-format.h
	$(CC) -c -o midas-format.o $(CFLAGS) midas-format.c

clean:
	rm -rf *.o

very-clean:
	rm -rf *.a *.o *.*~ *~ sort
