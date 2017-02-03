#define module_evt_display_cxx

#include "module_evt_display.h"
#include <iostream>

#include <TROOT.h>
#include <TSystem.h>
#include <TTimer.h>

void module_evt_display::begin(){

	gROOT->SetBatch(false);

    c = new TCanvas("Waveform Display", "Waveform Display");
    c->Divide(2,2);
   
    waveform_0 = NULL;
    waveform_1 = NULL;

    charge_0 = NULL;
    charge_1 = NULL;
	

}

void module_evt_display::process( event * evt){
	
	waveform_0 = new TH1F( TString::Format("waveform_0_%i", evt->get_nevent() ), TString::Format("waveform_0_%i", evt->get_nevent() ), evt->get_nsamples(), 0, evt->get_nsamples() * evt->get_time_sample() );
	waveform_1 = new TH1F( TString::Format("waveform_1_%i", evt->get_nevent() ), TString::Format("waveform_1_%i", evt->get_nevent() ), evt->get_nsamples(), 0, evt->get_nsamples() * evt->get_time_sample() );

	waveform_0->SetStats(false);
	waveform_1->SetStats(false);

	charge_0 = new TH1F( TString::Format("charge_0_%i", evt->get_nevent() ), TString::Format("charge_0_%i", evt->get_nevent() ), 500, 0, 2500);
	charge_1 = new TH1F( TString::Format("charge_1_%i", evt->get_nevent() ), TString::Format("charge_1_%i", evt->get_nevent() ), 500, 0, 2500);
    
	charge_0->SetStats(false);
	charge_1->SetStats(false);
    
	for( int i = 0 ; i < evt->get_waveform(0)->size(); i++) {

		waveform_0 -> Fill( i * evt->get_time_sample(), evt->get_waveform(0)->at(i) );
		waveform_1 -> Fill( i * evt->get_time_sample(), evt->get_waveform(1)->at(i) );

		charge_0 -> Fill( evt->get_waveform(0)->at(i) );
		charge_1 -> Fill( evt->get_waveform(1)->at(i) );
		
	}
    			
	c->cd(1); waveform_0->Draw("HIST"); 
	c->cd(3); charge_0->Draw("HIST"); c->cd(3)->Modified(); c->cd(3)->Update();
	
	c->cd(2); waveform_1->Draw("HIST"); 
	c->cd(4); charge_1->Draw("HIST"); c->cd(4)->Modified(); c->cd(4)->Update();
    
	TTimer * timer = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);
	timer->TurnOn();
	timer->Reset();
    
    while (1) {
    
		c->Modified(); c->Update(); c->WaitPrimitive();
	    
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
	delete waveform_0;
	delete waveform_1;
	delete charge_0;
	delete charge_1;
			
}

void module_evt_display::terminate(){;}