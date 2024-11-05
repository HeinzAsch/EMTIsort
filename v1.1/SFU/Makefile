all:
	echo Making display.
	(cd  display && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY.

	echo Making check.
	(cd  check && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK.


clean:
	(cd display         && make -is clean && cd ..)
	(cd check           && make -is clean && cd ..)
	rm -f *~
