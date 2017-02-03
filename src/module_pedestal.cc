#define module_pedestal_cxx

#include "module_pedestal.h"
#include <iostream>
#include <TMath.h>

void module_pedestal::begin(){
	
	_nsample = 100;
	
};

void module_pedestal::process( event * evt){
	
	for (int i = 0; i < evt->get_nchannels(); i++){
		
		evt->set_reco_pedestal( i,  avg_ped_value( evt->get_waveform(i) ) );
		evt->set_reco_pedestal_std( i,  std_ped_value( evt->get_waveform(i) ) );		
			
	}
	
};

void module_pedestal::terminate(){
	
};

double module_pedestal::avg_ped_value( std::vector<int> * waveform){ 
	return TMath::Mean(waveform->begin(), waveform->begin() + _nsample);
};

double module_pedestal::std_ped_value( std::vector<int> * waveform){ 
	return TMath::StdDev(waveform->begin(), waveform->begin() + _nsample);
};
