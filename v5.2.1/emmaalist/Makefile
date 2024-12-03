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

	echo Making check_GRIF_gate.
	(cd check_GRIF_gate && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_GRIF_GATE.

	echo Making check_EMMAT_gate.
	(cd check_EMMAT_gate && make -is clean && make && make -is clean && cd ..)
	echo DONE: CHECK_EMMAT_GATE.

	echo Making combine.
	(cd combine && make -is clean && make && make -is clean && cd ..)
	echo DONE: COMBINE.

	echo Making project_IC.
	(cd project_IC && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT_IC.
clean:
	(cd read && make -is clean  && cd ..)
	(cd emmatlist_tsns_offset   && make -is clean && cd ..)
	(cd add_EMMAT_triggers      && make -is clean && cd ..)
	(cd check_GRIF_gate         && make -is clean && cd ..)
	(cd check_EMMAT_gate        && make -is clean && cd ..)
	(cd combine                 && make -is clean && cd ..)
	(cd project_IC              && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making clean.
