all:
	rm -rf ../bin
	echo Setting up directories.
	(mkdir ../bin && mkdir ../bin/midas && mkdir ../bin/SFU && mkdir ../bin/griflist && mkdir ../bin/emmatlist && mkdir ../bin/emmaalist)

	echo Making utils.
	(cd utils && make -is very-clean && make && make -is clean && cd ..)
	echo DONE: UTILS.

	echo Making SFU-format.
	(cd SFU-format && make -is very-clean && make && make -is clean && cd ..)
	echo DONE: SFU-FORMAT.

	echo Making griflist-format.
	(cd griflist-format && make -is clean && make && make -is clean && cd ..)
	echo DONE: GRIFLIST-FORMAT.

	echo Making emmatlist-format.
	(cd emmatlist-format && make -is clean && make && make -is clean && cd ..)
	echo DONE: EMMATLIST-FORMAT.

	echo Making emmaalist-format.
	(cd emmaalist-format && make -is clean && make && make -is clean && cd ..)
	echo DONE: EMMAALIST-FORMAT.

	echo Making midas.
	(cd midas && make -is clean && make && make -is clean && cd ..)
	echo DONE: MIDAS.

	echo Making griflist.
	(cd griflist && make -is clean && make && make -is clean && cd ..)
	echo DONE: GRIFLIST.

	echo Making emmatlist.
	(cd emmatlist && make -is clean && make && make -is clean && cd ..)
	echo DONE: EMMATLIST.

	echo Making emmaalist.
	(cd emmaalist && make -is clean && make && make -is clean && cd ..)
	echo DONE: EMMAALIST.

	echo Making SFU.
	(cd SFU && make -is clean && make && make -is clean && cd ..)
	echo DONE: SFU.

clean:
	echo Making clean all directories and bin.
	rm -rf ../bin/*
	rmdir ../bin
	(cd utils      && make -is clean && cd ..)
	(cd SFU-format && make -is clean && cd ..)
	(cd midas      && make -is clean && cd ..)
	(cd griflist   && make -is clean && cd ..)
	(cd griflist-format && make -is clean && cd ..)
	(cd emmaalist-format && make -is clean && cd ..)
	(cd emmatlist-format && make -is clean && cd ..)
	(cd SFU        && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making clean.

very-clean:
	echo Making very-clean all directories and bin.
	(cd midas      && make -is very-clean && cd ..)
	(cd utils      && make -is very-clean && cd ..)
	(cd SFU-format && make -is very-clean && cd ..)
	(cd griflist-format && make -is very-clean && cd ..)
	(cd emmatlist-format && make -is very-clean && cd ..)
	(cd emmaalist-format && make -is very-clean && cd ..)
	(cd griflist   && make -is very-clean && cd ..)
	(cd SFU        && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making very-clean.
