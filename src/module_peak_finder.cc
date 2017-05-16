/*
	
	module_peak_finder.cc
	Purpose: Base class for peak_finder calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: 
	
*/

#define module_peak_finder_cxx

#include "module_peak_finder.h"
#include "plotter.h"

#include <TMath.h>

#include <iostream>
#include <algorithm>
#include <numeric> 


void module_peak_finder::begin(){

	_treshold = 5; // # of sigma wrt pedestal
	
};

bool module_peak_finder::process( event * evt){	
	
	for (int ch = 0; ch < evt->get_nchannels(); ch++){
	
		int min_adc_count = TMath::MinElement( evt->get_waveform(ch)->size() , &evt->get_waveform(ch)->at(0) );
		int min_adc_count_loc = TMath::LocMin( evt->get_waveform(ch)->size() , &evt->get_waveform(ch)->at(0) );
		
		if( min_adc_count < evt->get_reco_pedestal(ch) - _treshold * evt->get_reco_pedestal_std(ch) ) {
			
			evt->set_reco_min_adc(ch, min_adc_count);
			evt->set_reco_min_adc_time(ch, min_adc_count_loc * evt->get_time_sample());
			
		}
			
	}
	
	return true;
	
};

void module_peak_finder::terminate(){
	
};

