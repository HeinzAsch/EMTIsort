all:
	echo Making display_RawEvent.
	(cd RawEvent r && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY_RawEvent.

	echo Making display_TIGRESS.
	(cd TIGRESS r && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY_TIGRESS.

	echo Making display_EMMA.
	(cd EMMA r && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY_EMMA.

	echo Making display_TIP.
	(cd TIP r && make -is clean && make && make -is clean && cd ..)
	echo DONE: DISPLAY_TIP.

clean:
	(cd RawEvent && make -is clean && cd ..)
	(cd TIGRESS  && make -is clean && cd ..)
	(cd TIP      && make -is clean && cd ..)
	(cd EMMA     && make -is clean && cd ..)
	rm -f *~

very-clean:
	(cd RawEvent && make -is clean && cd ..)
	(cd TIGRESS  && make -is clean && cd ..)
	(cd TIP      && make -is clean && cd ..)
	(cd EMMA     && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making very-clean.
