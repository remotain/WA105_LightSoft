/**
	
	module_pedestal.cc
	Purpose: Base class for pedestal calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: Calculate the pedestal for each active channel. In this simple
	implementation the pedestal is obtained by averaging the first"_nsample" of 
	the waveform. The pedestal standard deviation is obtained in a similar way.
	User might reimplement the algorithm inheriting from this class.
	
**/

#define module_pedestal_cxx

#include "module_pedestal.h"
#include <iostream>
#include <TMath.h>

#include "plotter.h"

void module_pedestal::begin(){
	
	// The function set the number of sample used to calculate the pedestal is not
	// already set by the user.
	if( _nsample == -1 ) set_nsample( 100 );
	
	plotter::get_me().add( new TH1F ("pedestal_avg_distributions", "Pedestal average distribution", 100, 2100, 2200) ); 
	plotter::get_me().add( new TH1F ("pedestal_std_distributions", "Pedestal standard deviation distribution", 100, 0, 10) ); 
	
};

void module_pedestal::process( event * evt){
	
	// For each active channel, calculate the pedestal average and the standard 
	// deviation and set the values through the event interface.
	for (int i = 0; i < evt->get_nchannels(); i++){
		
		evt->set_reco_pedestal( i,  calculate_pedestal_average( evt->get_waveform(i) ) );
		evt->set_reco_pedestal_std( i,  calculate_pedestal_standard_deviation( evt->get_waveform(i) ) );		
		
		plotter::get_me().find("pedestal_avg_distributions")->Fill( evt->get_reco_pedestal(i) ) ;
		plotter::get_me().find("pedestal_std_distributions")->Fill( evt->get_reco_pedestal_std(i) ) ;	
			
	}
	
};

void module_pedestal::terminate(){
	
};

double module_pedestal::calculate_pedestal_average( std::vector<int> * waveform){ 

	// Calculate the average of the pedestal using the firts _nsample of the 
	//waveform.
	return TMath::Mean(waveform->begin(), waveform->begin() + _nsample);

};

double module_pedestal::calculate_pedestal_standard_deviation( std::vector<int> * waveform){ 

	// Calculate the standard deviation of the pedestal using the firts _nsample
	// of the waveform.
	return TMath::StdDev(waveform->begin(), waveform->begin() + _nsample);

};
