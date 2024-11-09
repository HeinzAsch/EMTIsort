all:
	echo making ECalABSupp.
	(cd ECalABSupp r && make -is clean && make && make -is clean && cd ..)
	echo DONE: ECALABSUPP

clean:
	(cd ECalABSupp            && make -is clean && cd ..)
	rm -f *~
