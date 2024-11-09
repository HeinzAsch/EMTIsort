all:
	echo making Energy_NoAddBackSupp Programs.
	(cd NoAddBackSupp r && make -is clean && make && make -is clean && cd ..)
	echo DONE: NOADDBACKSUPP.

	echo making Energy_AddBackSupp Programs.
	(cd AddBackSupp r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ADDBACKSUPP.


clean:
	(cd NoAddBackSupp   && make -is clean && cd ..)
	(cd AddBackSupp     && make -is clean && cd ..)
	rm -f *~
