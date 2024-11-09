all:
	echo Making TIGRESS_Energy.
	(cd Energy r && make -is clean && make && make -is clean && cd ..)
	echo DONE: TIGRESS_ENERGY.

clean:
	(cd Energy        && make -is clean && cd ..)
	rm -f *~
