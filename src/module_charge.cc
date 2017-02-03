/*
	
	modulecharge.cc
	Purpose: Base class for charge calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: Calculate the charge for each active channel. 

	The algorithm proceed as follow:

	1 - A pulse in the waveform is defined as peak with amplitude bigger than 5 
		standad deviation of the pedestal.

	2 - The pulse start time is defined as the adc sample with 20 % of the pulse
	 	amplitude.

	3 - The pulse charge is calculated by integrating the waveform from the pulse
	 	start time till the end of the waveform.

	User might reimplement the algorithm inheriting from this class.

	
*/

#define module_charge_cxx

#include "module_charge.h"
#include <iostream>
#include <algorithm>
#include <numeric> 

void module_charge::begin(){
	
};

void module_charge::process( event * evt){
	
	for (int i = 0; i < evt->get_nchannels(); i++){
		
		// Define the position of the puslse maximum as the highest adc count in the waveform.
		std::vector<int>::iterator it_pulse_max = std::min_element(evt->get_waveform(i)->begin(),evt->get_waveform(i)->end());
	
		// Calculate the pulse maximum amplitude w.r.t. the pedestal.
		double pulse_max = evt->get_reco_pedestal(i) - *it_pulse_max;
	
		// If the pulse max is smaller than 5 pedestal standard deviation the charge is not calculated.
		if ( pulse_max <= 5 * evt->get_reco_pedestal_std(i) ) continue;
	
		// Find the time position of the pulse peak.
		double t_peak = evt->get_time_sample() * std::distance(evt->get_waveform(i)->begin(), it_pulse_max);
		
		// Define the pulse start as the first adc count with amplitude >= 20 % of the pulse maximum amplitude.
		std::vector<int>::iterator it_pulse_start = std::find_if (evt->get_waveform(i)->begin(),it_pulse_max, bind2nd(std::less<double>(), evt->get_reco_pedestal(i) - 0.2 * pulse_max ));
		
		// Find the time position of the pulse start.
		double t_start = evt->get_time_sample() * std::distance(evt->get_waveform(i)->begin(), it_pulse_start);

		// Find the time position of the pulse stop.
		double t_stop = -1;
	
		// Calculate the charge by integrating the waveform from t_start till the end of the waveform
		double charge = evt->get_reco_pedestal(i) * std::distance(it_pulse_start, evt->get_waveform(i)->end()) - std::accumulate(it_pulse_start, evt->get_waveform(i)->end(), 0);					
		
		// Set the values of the charge through the event interface.
		evt->set_reco_charge(i, charge);
					
	}
	
};

void module_charge::terminate(){
	
};

