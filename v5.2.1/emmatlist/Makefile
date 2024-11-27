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

	echo Making check_GRIF_gate.
	(cd check_GRIF_gate && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_GRIF_GATE.

	echo Making project_PGAC.
	(cd project_PGAC && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_PGAC.
clean:
	(cd read && make -is clean && cd ..)
	(cd griflist_tsns_offset   && make -is clean && cd ..)
	(cd add_GRIF_triggers      && make -is clean && cd ..)
	(cd check_GRIF_gate        && make -is clean && cd ..)
	(cd project_PGAC	   && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making clean.
