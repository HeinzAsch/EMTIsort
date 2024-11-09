all:
	echo Making display.
	(cd  display && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY.

	echo Making check.
	(cd  check && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK.

	echo Making TIGRESS.
	(cd  TIGRESS && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS.


clean:
	(cd display         && make -is clean && cd ..)
	(cd check           && make -is clean && cd ..)
	(cd TIGRESS         && make -is clean && cd ..)
	rm -f *~

very-clean:
	(cd display         && make -is very-clean && cd ..)
	(cd check           && make -is very-clean && cd ..)
	(cd TIGRESS         && make -is very-clean && cd ..)
	rm -f *~
