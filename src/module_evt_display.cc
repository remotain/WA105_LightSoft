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
#include <TH2F.h>
#include <TLine.h>
#include <TStyle.h>
#include <TFile.h>

void module_evt_display::begin(){

	gROOT->SetBatch(false);

    c_pmt = new TCanvas("PMT Display", "PMT Display");
    c_pmt->Divide(5,3);	

    //c_crt = new TCanvas("CRT Display", "CRT Display");
    //c_crt->Divide(3,2);	

	for( int ch = 0; ch < 5; ch++ ){	
		_waveform_avg.push_back( new TProfile( TString::Format("waveform_avg_%i", ch ), TString::Format("waveform_avg_%i", ch ), 1000, 0, 4000 ));
		_waveform_avg[ch]->GetYaxis()->SetRangeUser(0, 4500);
	}

	gStyle->SetOptStat(0);

}

bool module_evt_display::process( event * evt){
	
	Info("process", "Event no.%i, CRT Match %i, CRT Reco %i", evt->get_nevent(), evt->get_crt_daq_match(), evt->get_crt_reco());
	
	for( int ch = 0; ch < evt->get_n_channels_active(); ch++ ){	
		
		_waveform.push_back( new TH1F( TString::Format("waveform_%i_%i", ch , evt->get_nevent() ), TString::Format("waveform_%i_%i", ch , evt->get_nevent() ), evt->get_waveform(ch)->size(), 0, evt->get_waveform(ch)->size() * evt->get_time_sample() ));
		_waveform[ch]->GetYaxis()->SetRangeUser(0, 4500);
		
		for( int i = 0 ; i < evt->get_waveform(ch)->size(); i++) {
			_waveform[ch] -> Fill( i * evt->get_time_sample(), evt->get_waveform(ch)->at(i) );		
			
			if( ch < 5 ) 
				_waveform_avg[ch] -> Fill( i * evt->get_time_sample(), evt->get_waveform(ch)->at(i) );		
		
		}

		if( ch < 5 ) {
			c_pmt->cd(ch+1); _waveform[ch] -> Draw("HIST");
			c_pmt->cd(ch+1)->Modified(); c_pmt->cd(ch+1)->Update();

			c_pmt->cd(ch+1+5); _waveform_avg[ch] -> Draw("");
			c_pmt->cd(ch+1+5)->Modified(); c_pmt->cd(ch+1+5)->Update();
		}
	
		//std::vector<int> * waveform = evt->get_waveform(ch);
		//std::vector<int>::iterator result = std::min_element(waveform->begin(), waveform->end());
		//std::cout << "Peak at " << std::distance(waveform->begin(), result) * evt->get_time_sample() << std::endl;
	
	
	}
	
	// Trigger waveforms
	
	_waveform[5]->SetTitle("CRT Trigger signal");
	c_pmt->cd(11); _waveform[5] -> Draw("HIST");
	c_pmt->cd(11)->Modified(); c_pmt->cd(11)->Update();
	
	// CRT Waveform
	
	TH1F * a_0 = new TH1F( TString::Format("crt_adc_%i_%i", 0 , evt->get_nevent() ), TString::Format("crt_adc_%i_%i", 0 , evt->get_nevent() ), 32, 0, 32 );
	TH1F * a_1 = new TH1F( TString::Format("crt_adc_%i_%i", 1 , evt->get_nevent() ), TString::Format("crt_adc_%i_%i", 1 , evt->get_nevent() ), 32, 0, 32 );	
	TH1F * a_2 = new TH1F( TString::Format("crt_adc_%i_%i", 2 , evt->get_nevent() ), TString::Format("crt_adc_%i_%i", 2 , evt->get_nevent() ), 32, 0, 32 );
	TH1F * a_3 = new TH1F( TString::Format("crt_adc_%i_%i", 3 , evt->get_nevent() ), TString::Format("crt_adc_%i_%i", 3 , evt->get_nevent() ), 32, 0, 32 );
	
	a_0->GetYaxis()->SetRangeUser(0, 4500);
	
	a_0->SetLineColor(kViolet);
	a_1->SetLineColor(kAzure);
	a_2->SetLineColor(kPink);
	a_3->SetLineColor(kOrange);
	
	
	for( int i = 0 ; i < 31; i++) {
	
		a_0->Fill(i, evt->get_crt_adc(0)[i]);
		a_1->Fill(i, evt->get_crt_adc(1)[i]);
		a_2->Fill(i, evt->get_crt_adc(2)[i]);
		a_3->Fill(i, evt->get_crt_adc(3)[i]);	
    
	}
	
	c_pmt->cd(12);
    
	a_0->Draw("HIST");
	a_1->Draw("HIST,Same");
	a_2->Draw("HIST,Same");
	a_3->Draw("HIST,Same");
	
	c_pmt->cd(12)->BuildLegend();
	c_pmt->cd(12)->Modified(); c_pmt->cd(12)->Update();
	
	// XY view
	
	TH2F * xy_tmp = new TH2F("xy_view", "XY view; Y [mm]; X [mm]", 100, -4000, +4000, 100, -1000, +1000);
		
	TLine * xy_line = new TLine( evt->get_crt_track_pos0()[1], evt->get_crt_track_pos0()[0], evt->get_crt_track_pos1()[1], evt->get_crt_track_pos1()[0] );
	
	//xy_line->Print();
	
	c_pmt->cd(13);
	xy_tmp->Draw();
	xy_line->Draw("");
	c_pmt->cd(13)->Modified(); c_pmt->cd(13)->Update();		
    
	// YZ view
	
	TH2F * yz_tmp = new TH2F("yz_view", "YZ view; Y [mm]; Z [mm]", 100, -4000, +4000, 100, -1000, +1000);
		
	//TLine * yz_line = new TLine( - evt->get_crt_track_pos0()[1], evt->get_crt_track_param()[0] + evt->get_crt_track_pos0()[1] *  evt->get_crt_track_param()[1], evt->get_crt_track_pos1()[1], evt->get_crt_track_param()[0] - evt->get_crt_track_pos1()[1] *  evt->get_crt_track_param()[1]);
	
	TLine * yz_line = new TLine( evt->get_crt_track_pos0()[1], evt->get_crt_track_pos0()[2], evt->get_crt_track_pos1()[1], evt->get_crt_track_pos1()[2]);
	
	//yz_line->Print();
	
	c_pmt->cd(14);	
	yz_tmp->Draw();
	yz_line->Draw("");			
	c_pmt->cd(14)->Modified(); c_pmt->cd(14)->Update();		

			    
	TTimer * timer = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);
	timer->TurnOn();
	timer->Reset();
	
    while (1) {
    
		//c->Modified(); c->Update(); c->WaitPrimitive();
	    
		gSystem->ProcessEvents();
			
		char key;	
		std::cout<< " (return to next event, s to save, q to quit): "; 
		std::cin.get(key);
    
		if( key == 'q' || key == 'Q') {
			gSystem->Exit(0);
		} if( key == 's' || key == 'S') {
			
			c_pmt->Print( TString::Format("waveforms_evt_%i.pdf", evt->get_nevent()) );
			
			TFile * tmp_f = new TFile(TString::Format("waveforms_evt_%i.root", evt->get_nevent()), "RECREATE" );
			
			for( int i = 0; i < evt->get_n_channels_active(); i++ ){	
				_waveform[i]->Write();
			}
												
			xy_line->Write();
			yz_line->Write();
			
			a_0->Write();
			a_1->Write();
			a_2->Write();
			a_3->Write();
			
			tmp_f->Close();
			
		} else {
			break;
		}
				 
		  
      }
    
  	timer->TurnOff();
    
  	delete timer;
	_waveform.clear();

	delete xy_tmp;
	delete xy_line;
    
	delete yz_tmp;
	delete yz_line;
    
	delete a_0;
	delete a_1;
	delete a_2;
	delete a_3;

	return true;

}

void module_evt_display::terminate(){


}