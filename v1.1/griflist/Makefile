all:
	echo Making sorting.
	(cd sorting && make -is clean && make && make -is clean && cd ..)
	echo DONE: SORTING.

	echo Making diagnostics.
	(cd diagnostics && make -is clean && make && make -is clean && cd ..)
	echo DONE: DIAGNOSTICS.

	echo Making griflist2sfu.
	(cd griflist2sfu && make -is clean && make && make -is clean && cd ..)
	echo DONE: GRIFLIST2SFU.

clean:
	(cd sorting      && make -is clean && cd ..)
	(cd diagnostics  && make -is clean && cd ..)
	(cd griflist2sfu && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making clean.
