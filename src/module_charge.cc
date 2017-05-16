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

#include <TSystem.h>
#include <TTimer.h>
#include <TCanvas.h>

void module_charge::begin(){
	
	plotter::get_me().add( new TH1F ("charge_distribution", "Charge distribution; Integrated ADC Counts", 100000, -1000000, 10000) ); 
	plotter::get_me().add( new TH1F ("total_charge_distribution", "Total charge distribution; Integrated ADC Counts", 100000, -1000000, 10000) ); 
	plotter::get_me().add( new TH2F ("charge_map", "Charge vs channel distribution; Channel; Integrated ADC Counts", 5, 0, 5, 5500, -50000, 5000) ); 
	plotter::get_me().add( new TProfile ("charge_profile", "Charge vs channel distribution; Channel; Integrated ADC Counts", 5, 0, 5, "S" ) ); 

	plotter::get_me().add( new TH1F ("charge_ch0", "Charge distribution ch 0; Integrated ADC Counts", 100000, -1000000, 10000) ); 
	plotter::get_me().add( new TH1F ("charge_ch1", "Charge distribution ch 1; Integrated ADC Counts", 100000, -1000000, 10000) ); 
	plotter::get_me().add( new TH1F ("charge_ch2", "Charge distribution ch 2; Integrated ADC Counts", 100000, -1000000, 10000) ); 
	plotter::get_me().add( new TH1F ("charge_ch3", "Charge distribution ch 3; Integrated ADC Counts", 100000, -1000000, 10000) ); 
	plotter::get_me().add( new TH1F ("charge_ch4", "Charge distribution ch 4; Integrated ADC Counts", 100000, -1000000, 10000) ); 			
	
	
	
	
	
};

bool module_charge::process( event * evt){
	
	double total_charge = 0;		
				
	for (int ch = 0; ch < evt->get_n_channels_active(); ch++){
	
		if ( (_window_start + _window_length) > evt->get_waveform(ch)->size() ){
			Fatal("process", "The integration window is longer than the current waveform: %i, %i, %lu", _window_start, _window_length, evt->get_waveform(ch)->size());
		}
				
		double charge = 0;

		//TH1F * h = new TH1F("h", "h", _window_length, 0, _window_length);	

		// integrate only if the peak is > 20 and < 60 ADC counts
		// int result = *std::min_element(&evt->get_waveform(ch)->at(_window_start), &evt->get_waveform(ch)->at(_window_start + _window_length));

		//std::cout << result << " " << result - evt->get_reco_pedestal(ch) << std::endl;

		// if( TMath::Abs(result - evt->get_reco_pedestal(ch)) > 60 ) continue;

		for(int j = _window_start ; j < _window_start + _window_length; j++){
			
			charge += evt->get_waveform(ch)->at(j) - evt->get_reco_pedestal(ch);
			
			//h->SetBinContent( j-_window_start, - (evt->get_waveform(ch)->at(j) - evt->get_reco_pedestal(ch)) );
			
		}
		
		// Sum the charge of the PMT only
		if( ch < 5 ){
			total_charge += charge;	
			plotter::get_me().find("charge_distribution")->Fill( charge ) ;
		}
								
		// Set the values of the charge through the event interface.
		evt->set_reco_charge(ch, charge);
		
		plotter::get_me().find2d("charge_map")->Fill( ch, charge ) ;
		plotter::get_me().find2d("charge_profile")->Fill( ch, charge ) ;
		
		if( plotter::get_me().find( TString::Format("charge_ch%i", ch) ) ){
		
			plotter::get_me().find( TString::Format("charge_ch%i", ch) )->Fill( charge ) ;
		
		}
					
	}
	
	evt->set_reco_total_charge( total_charge );
	
	plotter::get_me().find("total_charge_distribution")->Fill( total_charge ) ;
	
	return true;
	
};

void module_charge::terminate(){
	
};

