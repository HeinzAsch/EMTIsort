all:
	echo Making project_emma_adc_channel.
	(cd emma_adc_channel r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_EMMA_ADC_CHANNEL.

	echo Making project_emma_adc_hits.
	(cd emma_adc_hits r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_EMMA_ADC_HITS.

	echo Making project_emma_adc_HP.
	(cd emma_adc_HP r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_EMMA_ADC_HP.

	echo Making project_grif_channel.
	(cd grif_channel r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_GRIF_CHANNEL.

	echo Making project_channelHP.
	(cd channelHP r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_CHANNELHP.

	echo Making project_emmaa_histogram.
	(cd emmaa_histogram r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_EMMAA_HISTOGRAM.

	echo Making project_emmat_timing_histogram.
	(cd emmat_timing_histogram r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_EMMAT_TIMING_HISTOGRAM.

	echo Making project_emmat_PGAC.
	(cd emmat_PGAC r && make -is clean && make  && make -is clean && cd ..)
	echo DONE: PROJECT_EMMAT_PGAC.

clean:
	(cd emma_adc_channel          && make -is clean && cd ..)
	(cd emma_adc_hits             && make -is clean && cd ..)
	(cd emma_adc_HP               && make -is clean && cd ..)
	(cd grif_channel              && make -is clean && cd ..)
	(cd channelHP                 && make -is clean && cd ..)
	(cd emmaa_histogram           && make -is clean && cd ..)
	(cd emmat_timing_histogram    && make -is clean && cd ..)
	rm -f *~
