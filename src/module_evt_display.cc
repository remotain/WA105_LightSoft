/*
	
	module_evt_display.cc
	Purpose: Base class to display events
	
	@author Alberto Remoto
	@version 1.0 2017-02-03

	This module is currently not working properly.
	
*/

#define module_evt_display_cxx

#include "module_evt_display.h"
#include <iostream>

#include <TROOT.h>
#include <TSystem.h>
#include <TTimer.h>

void module_evt_display::begin(){

	gROOT->SetBatch(false);

    c = new TCanvas("Waveform Display", "Waveform Display");
    c->Divide(1,2);	

}

void module_evt_display::process( event * evt){
	
	for( int ch = 0; ch < evt->get_n_channels_active(); ch++ ){
		
		_waveform.push_back( new TH1F( TString::Format("waveform_%i_%i", ch , evt->get_nevent() ), TString::Format("waveform_%i_%i", ch , evt->get_nevent() ), evt->get_nsamples(), 0, evt->get_nsamples() * evt->get_time_sample() ));
		_waveform[ch]->SetStats(false); 
		
		for( int i = 0 ; i < evt->get_waveform(ch)->size(); i++) {
			_waveform[ch] -> Fill( i * evt->get_time_sample(), evt->get_waveform(ch)->at(i) );		
		}
		
		c->cd(ch+1); _waveform[ch] -> Draw("HIST");
		c->cd(ch+1)->Modified(); c->cd(ch+1)->Update();
	}
    		    
	TTimer * timer = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);
	timer->TurnOn();
	timer->Reset();
    
    while (1) {
    
		//c->Modified(); c->Update(); c->WaitPrimitive();
	    
		gSystem->ProcessEvents();
			
		char key;	
		std::cout<< " (return to next event, q to quit): "; 
		std::cin.get(key);
    
		if( key == 'q' || key == 'Q') 
			gSystem->Exit(0);
		else
			break;
				 
		  
      }
    
  	timer->TurnOff();
    
  	delete timer;
	_waveform.clear();

			
}

void module_evt_display::terminate(){


}