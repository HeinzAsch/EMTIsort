all:
	echo Making read.
	(cd read && make -is clean && make && make -is clean && cd ..)
	echo DONE: READ.

	echo Making griflist_tsns_offset.
	(cd griflist_tsns_offset && make -is clean && make && make -is clean && cd ..)
	echo DONE: GRIF_LIST_TSNS_OFFSET.

	echo Making add_GRIF_triggers.
	(cd add_GRIF_triggers && make -is clean && make && make -is clean && cd ..)
	echo DONE: ADD_GRIF_TRIGGERS.

clean:
	(cd read && make -is clean && cd ..)
	(cd griflist_tsns_offset   && make -is clean && cd ..)
	(cd add_GRIF_triggers      && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making clean.
