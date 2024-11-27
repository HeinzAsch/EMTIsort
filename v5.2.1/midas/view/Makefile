all:
	echo Making view_griff_channel.
	(cd griff_channel r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_GRIFF_CHANNEL.

	echo Making view_griff_fragment.
	(cd griff_fragment r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_GRIFF_FRAGMENT.

	echo Making view_griff_address.
	(cd griff_address r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_GRIFF_ADDRESS.

	echo Making view_griff_dtype.
	(cd griff_dtype r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_GRIFF_DTYPE.

	echo Making view_griff_timing.
	(cd griff_timing r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_GRIFF_TIMING.

	echo Making view_emmat_timing.
	(cd emmat_timing r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_EMMAT_TIMING.

	echo Making view_emmat_fragment.
	(cd emmat_fragment r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_EMMAT_FRAGMENT.

	echo Making view_emmaa_timing.
	(cd emmaa_timing r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_EMMAA_TIMING.

	echo Making view_emmaa_fragment.
	(cd emmaa_fragment r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_EMMAA_FRAGMENT.

	echo Making view_hist_tsup.
	(cd hist_tsup r && make -is clean && make && make -is clean && cd ..)
	echo DONE: VIEW_HIST_TSUP.

clean:
	(cd griff_channel        && make -is clean && cd ..)
	(cd griff_fragment       && make -is clean && cd ..)
	(cd griff_timing         && make -is clean && cd ..)
	(cd emmat_timing         && make -is clean && cd ..)
	(cd emmat_fragment       && make -is clean && cd ..)
	(cd emmaa_timing         && make -is clean && cd ..)
	(cd emmaa_fragment       && make -is clean && cd ..)
	(cd hist_tsup            && make -is clean && cd ..)

	rm -f *~
