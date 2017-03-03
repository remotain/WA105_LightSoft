/*
	
	module_charge.cc
	Purpose: Base class for charge calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: Calculate the pedestal subtracted total charge for each active 
	channel. 

	User might reimplement the algorithm inheriting from this class.

	
*/

#define module_charge_cxx

#include "module_charge.h"
#include "plotter.h"

#include <iostream>
#include <algorithm>
#include <numeric> 

void module_charge::begin(){
	
	plotter::get_me().add( new TH1F ("charge_distribution", "Charge distribution; Integrated ADC Counts", 100, 0, 0) ); 
	plotter::get_me().add( new TH2F ("charge_map", "Charge vs channel distribution; Channel; Integrated ADC Counts", 5, 0, 5, 100, 0, 0) ); 
	plotter::get_me().add( new TProfile ("charge_profile", "Charge vs channel distribution; Channel; Integrated ADC Counts", 5, 0, 5 ) ); 

	
};

void module_charge::process( event * evt){
	
	for (int i = 0; i < evt->get_nchannels(); i++){
		
		//// Define the position of the puslse maximum as the highest adc count in the waveform.
		//std::vector<int>::iterator it_pulse_max = std::min_element(evt->get_waveform(i)->begin(),evt->get_waveform(i)->end());
	    //
		//// Calculate the pulse maximum amplitude w.r.t. the pedestal.
		//double pulse_max = evt->get_reco_pedestal(i) - *it_pulse_max;
	    //
		//// If the pulse max is smaller than "_pulse_max_tolerance" pedestal standard deviation the charge is not calculated.
		//if ( pulse_max <= _pulse_max_tolerance * evt->get_reco_pedestal_std(i) ) continue;
	    //
		//// Find the time position of the pulse peak.
		//double t_peak = evt->get_time_sample() * std::distance(evt->get_waveform(i)->begin(), it_pulse_max);
		//
		//// Define the pulse start as the first adc count with amplitude >= "_pulse_start_amplitude" of the pulse maximum amplitude.
		//std::vector<int>::iterator it_pulse_start = std::find_if (evt->get_waveform(i)->begin(),it_pulse_max, bind2nd(std::less<double>(), evt->get_reco_pedestal(i) - _pulse_start_amplitude * pulse_max ));
		//
		//// Find the time position of the pulse start.
		//double t_start = evt->get_time_sample() * std::distance(evt->get_waveform(i)->begin(), it_pulse_start);
        //
		//// Find the time position of the pulse stop.
		//double t_stop = -1;
	    //
		//// Calculate the charge by integrating the waveform from t_start till the end of the waveform
		//double charge = evt->get_reco_pedestal(i) * std::distance(it_pulse_start, evt->get_waveform(i)->end()) - std::accumulate(it_pulse_start, evt->get_waveform(i)->end(), 0);					
		
		double charge = 0;
        
		for(int j = 0; j < evt->get_waveform(i)->size(); j++){
			
			charge += evt->get_waveform(i)->at(j) - evt->get_reco_pedestal(i);
			
		}
				
		//std::cout << charge << std::endl;
				
		// Set the values of the charge through the event interface.
		evt->set_reco_charge(i, charge);
		
		plotter::get_me().find("charge_distribution")->Fill( charge ) ;
		plotter::get_me().find("charge_map")->Fill( i, charge ) ;
		plotter::get_me().find("charge_profile")->Fill( i, charge ) ;
					
	}
	
};

void module_charge::terminate(){
	
};

