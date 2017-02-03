#define module_charge_cxx

#include "module_charge.h"
#include <iostream>
#include <algorithm>
#include <numeric> 

void module_charge::begin(){
	
};

void module_charge::process( event * evt){
	
	for (int i = 0; i < evt->get_nchannels(); i++){
		
		std::vector<int>::iterator it_pulse_max = std::min_element(evt->get_waveform(i)->begin(),evt->get_waveform(i)->end());
	
		double pulse_max = evt->get_reco_pedestal(i) - *it_pulse_max;
	
		double t_peak = evt->get_time_sample() * std::distance(evt->get_waveform(i)->begin(), it_pulse_max);
		
		std::vector<int>::iterator it_pulse_start = std::find_if (evt->get_waveform(i)->begin(),it_pulse_max, bind2nd(std::less<double>(), evt->get_reco_pedestal(i) - 0.2 * pulse_max ));
		
		double t_start = evt->get_time_sample() * std::distance(evt->get_waveform(i)->begin(), it_pulse_start);

		double t_stop = -1;
	
		double charge = evt->get_reco_pedestal(i) * std::distance(it_pulse_start, evt->get_waveform(i)->end()) - std::accumulate(it_pulse_start, evt->get_waveform(i)->end(), 0);					
		
		evt->set_reco_charge(i, charge);
					
	}
	
};

void module_charge::terminate(){
	
};

