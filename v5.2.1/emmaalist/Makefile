all:
	echo Making read.
	(cd read && make -is clean && make && make -is clean && cd ..)
	echo DONE: READ.

	echo Making emmatlist_tsns_offset.
	(cd emmatlist_tsns_offset && make -is clean && make && make -is clean && cd ..)
	echo DONE: EMMAT_LIST_TSNS_OFFSET.

	echo Making add_EMMAT_triggers.
	(cd add_EMMAT_triggers && make -is clean && make && make -is clean && cd ..)
	echo DONE: ADD_EMMAT_TRIGGERS.

clean:
	(cd read && make -is clean && cd ..)
	(cd emmatlist_tsns_offset  && make -is clean && cd ..)
	(cd add_EMMAT_triggers      && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making clean.
