# EMTIsort

This code base is intended to facilitate analysis of data derived from the combination (or a subset of) the TIGRESS, TIP, and EMMA detector systems collected by a GRIFFIN-style DAQ. Codes below will be discussed in order of appearance in the bin folder and starting top-down. Broadly speaking, data formats flow from MIDAS to LIST (with subcategories for data streams) to SFU. Each step refines the analysis with a primary focus on employing the time coincidence method to compile trigger-less time-stamped fragments into events.

##BIN Folder

Populated primarily by tools that are not specific to MIDAS, LIST or SFU. Typically these affect derived, visualized data store in SPN or ROOT formats.

###addspn

###chisqspn

##MIDAS

###grif2list
###midas_block_dump
###midas_block_id
###midas_project_channelHP
###midas_project_grif_channel
###midas_sclr_raw
###midas_sclr_sum
###project_emma_adc_channel
###project_emma_adc_hits
###project_emma_adc_HP
###view_emmaa_fragment
###view_emmaa_timing
###view_emmat_fragment
###view_emmat_timing
###view_griff_address
###view_griff_channel
###view_griff_dtype
###view_griff_fragment
###view_griff_timing
###wfit_amplitude
###wfit_amplitude_all
###wfit_create_PID
###wfit_fit_fast_component
###wfit_fit_slow_component
###wfit_fit_two_component
###wfit_RC
###wfit_show_bad_baseline
###wfit_show_bad_CsIExclusionZone
###wfit_show_bad_tmax
###wfit_show_CsIBaseline
###wfit_show_CsIExclusionZone
###wfit_show_CsIExclusionZoneAndFits
###wfit_show_CsIFits
###wfit_show_CsIFit_t0
###wfit_show_CsIFit_type
###wfit_show_CsITF
###wfit_show_lin_two_components
###wfit_test_CsIBaseline
###wfit_test_CsIExclusionZone
###wfit_test_CsIFits_chisq
###wfit_test_CsIFits_chisq_all
###wfit_test_lin_two_components_chisq

##GRIFLIST

###griflist_add_trigger_to_Seg
###griflist_add_trigger_to_Sup
###griflist_apply_TIG_TIP_trigger
###griflist_channelHP_tsup
###griflist_check_order
###griflist_clear_trigger
###griflist_combine
###griflist_EMMA_trigger
###griflist_HPGe_CC_EMMA_time_difference
###griflist_HPGe_CC_energy
###griflist_HPGe_CC_energy_crystal
###griflist_HPGe_CC_Seg_time_difference
###griflist_HPGe_CC_Seg_time_energy
###griflist_HPGe_CC_Sup_time_difference
###griflist_HPGe_CC_Sup_time_energy
###griflist_HPGe_CC_time_difference
###griflist_HPGe_CC_time_difference_EE
###griflist_HPGe_CC_time_energy
###griflist_HPGe_CC_TIP_time_difference
###griflist_HPGe_CC_TIP_trigger_time_energy
###griflist_HPGe_CC_TIP_trigger_tsdiff
###griflist_HPGe_CC_trigger
###griflist_HPGe_CC_trigger_tsdiff
###griflist_HPGe_CC_Trigger_tsns
###griflist_read
###griflist_reset
###griflist_TIG_trigger_tsdiff
###griflist_time_difference
###griflist_TIP_fold
###griflist_TIP_t0
###griflist_TIP_time_difference
###griflist_TIP_trigger
###griflist_TIP_trigger_tsdiff
###griflist_TIP_Trigger_tsns

##SFU