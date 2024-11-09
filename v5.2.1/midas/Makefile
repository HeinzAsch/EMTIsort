all:
	echo Making decoder.
	(cd decoder && make -is very-clean && make && make -is clean && cd ..)
	echo DONE: DECODER.
	echo Making map.
	(cd map && make -is very-clean && make  && make -is clean && cd ..)
	echo DONE: MAP.
	echo Making state-machine.
	(cd state-machine && make -is very-clean && make  && make -is clean && cd ..)
	echo DONE: STATE-MACHINE.
	echo Making view.
	(cd view && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW.
	echo Making wfit.
	(cd wfit && make -is clean && make && make -is clean && cd ..)
	echo DONE: WFIT.
	echo Making project.
	(cd project && make -is clean && make && make -is clean && cd ..)
	echo DONE: PROJECT.	
	echo Making grif2list.
	(cd grif2list && make -is clean && make && make -is clean && cd ..)
	echo DONE: GRIF2LIST.
	echo Making emmat2list.
	(cd emmat2list && make -is clean && make && make -is clean && cd ..)
	echo DONE: EMMAT2LIST.
	echo Making emmaa2list.
	(cd emmaa2list && make -is clean && make && make -is clean && cd ..)
	echo DONE: EMMAA2LIST.
	echo Making block_id.
	(cd block_id && make -is clean && make && make -is clean && cd ..)
	echo DONE: block_id.
	echo Making block_dump.
	(cd block_dump && make -is clean && make && make -is clean && cd ..)
	echo DONE: block_dump.
	echo Making sclr_sum.
	(cd sclr_sum && make -is clean && make && make -is clean && cd ..)
	echo DONE: sclr_sum.
	echo Making sclr_raw.
	(cd sclr_raw && make -is clean && make && make -is clean && cd ..)
	echo DONE: sclr_raw.
clean:
	(cd decoder       && make -is clean && cd ..)
	(cd map           && make -is clean && cd ..)
	(cd state-machine && make -is clean && cd ..)
	(cd view          && make -is clean && cd ..)
	(cd wfit          && make -is clean && cd ..)
	(cd project       && make -is clean && cd ..)
	(cd grif2list     && make -is clean && cd ..)
	(cd emmat2list    && make -is clean && cd ..)
	(cd emmaa2list	  && make -is clean && cd ..)
	(cd block_id      && make -is clean && cd ..)
	(cd block_dump    && make -is clean && cd ..)
	(cd sclr_sum      && make -is clean && cd ..)
	(cd sclr_raw      && make -is clean && cd ..)
	rm -f *~

very-clean:
	echo Making very-clean all directories and bin.
	(cd decoder && make -is very-clean && cd ..)
	(cd map           && make -is very-clean && cd ..)
	(cd state-machine && make -is very-clean && cd ..)
	(cd view          && make -is clean && cd ..)
	(cd wfit          && make -is clean && cd ..)
	(cd project       && make -is clean && cd ..)
	(cd grif2list     && make -is clean && cd ..)
	(cd emmat2list    && make -is clean && cd ..)
	(cd emmaa2list	  && make -is clean && cd ..)
	(cd block_id      && make -is clean && cd ..)
	(cd block_dump    && make -is clean && cd ..)
	(cd sclr_sum      && make -is clean && cd ..)
	(cd sclr_raw      && make -is clean && cd ..)
	rm -f *~
	echo DONE: Making very-clean.

