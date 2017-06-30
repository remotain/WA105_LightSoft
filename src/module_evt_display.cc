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
#include <TTimeStamp.h>
#include <TImage.h>
#include <TVector3.h>

struct crtdet_t {

  // panel 1 is stairs side
  // panel 2 is wall side
  
  crtdet_t() {

    float strip_w = 112.;
    
    for(int is=0; is<NSTR; ++is) {

      float y = (7302.+100*2+20.*2)/2.;

      //float x1 = 1565 + (is*strip_w+strip_w/2);
      // centered to 0
      float x1 = -886.6 + (is*strip_w+strip_w/2);
      
      float z1 = 1930 + strip_w*NSTR - (is*strip_w+strip_w/2);

      //float x2 = 1545 + (is*strip_w+strip_w/2);
      // centered to 0
      float x2 = -906.6 + (is*strip_w+strip_w/2);
      
      float z2 = 1910 + strip_w*NSTR - (is*strip_w+strip_w/2);
      
      strip_pos1[is].SetXYZ(x1,-y,z1);
      strip_pos2[is].SetXYZ(x2,y,z2);

      strip_pos[0][is].SetXYZ(x1,-y,0);
      strip_pos[1][is].SetXYZ(0,-y,z1);
      strip_pos[2][is].SetXYZ(0,y,z2);
      strip_pos[3][is].SetXYZ(x2,y,0);
      
    }

    hStrip1.SetNameTitle("hStrip1","plane V1/H2; strip id; strip id");
    hStrip1.SetBins(NSTR,-0.5,NSTR-0.5,NSTR,-0.5,NSTR-0.5);
    hStrip2.SetNameTitle("hStrip2","plane V2/H2; strip id; strip id");
    hStrip2.SetBins(NSTR,-0.5,NSTR-0.5,NSTR,-0.5,NSTR-0.5);

    hStrip1.SetStats(0);
    hStrip2.SetStats(0);
    
    for(int i=1;i<=NSTR;++i) {
      hStrip1.GetXaxis()->SetBinLabel(i,Form("%i",NSTR-i));
      hStrip1.GetYaxis()->SetBinLabel(i,Form("%i",NSTR-i));

      hStrip2.GetXaxis()->SetBinLabel(i,Form("%i",NSTR-i));
      hStrip2.GetYaxis()->SetBinLabel(i,Form("%i",NSTR-i));
    }
    
    

  }//ctor

  static const int NSTR = 16;
  TVector3 strip_pos1[NSTR];
  TVector3 strip_pos2[NSTR];
  TVector3 strip_pos[4][NSTR];
  

  TH2F hStrip1;
  TH2F hStrip2;
  
  
};//crtdet_t




TVirtualPad * module_evt_display::go_to_pad( kCanvas k ){
	
	if( k == wCh0   ) return c_pmt->cd(1)->cd(1);
	else if( k == wCh1   ) return c_pmt->cd(1)->cd(2);
	else if( k == wCh2   ) return c_pmt->cd(1)->cd(3);
	else if( k == wCh3   ) return c_pmt->cd(1)->cd(4);
	else if( k == wCh4   ) return c_pmt->cd(1)->cd(5);
	else if( k == wAll   ) return 0; //c_pmt->cd(2)->cd(1);
	else if( k == crtT   ) return c_pmt->cd(2)->cd(1);
	else if( k == crtW   ) return c_pmt->cd(2)->cd(2);
	else if( k == crtXY1 ) return c_pmt->cd(2)->cd(3);
	else if( k == crtXY2 ) return c_pmt->cd(2)->cd(4);
	else if( k == viewYZ ) return c_pmt->cd(3)->cd(1);
	else if( k == viewXY ) return c_pmt->cd(3)->cd(2);
	
	return c_pmt->cd(0);
	
}

void module_evt_display::begin(){

	gROOT->SetBatch(false);

	c_pmt->Divide(1,3);	

	c_pmt->cd(1)->Divide(5,1);
	c_pmt->cd(2)->Divide(4,1);
	c_pmt->cd(3)->Divide(2,1);	

	////////////////////////////////////////////////
	//
	// LOAD Detector view
	//	
	TFile * f_geo = new TFile("$WLS_PATH/macro/fdet.root", "READ");
    _view_yz = (TH2Poly*) f_geo->Get("hDet_YZ"); _view_yz->SetTitle("View YZ (Lateral)");
	_view_xy = (TH2Poly*) f_geo->Get("hDet_YX"); _view_xy->SetTitle("View XY (Top)");
	
	gStyle->SetOptStat(0);
	gStyle->SetPalette(53);

}

bool module_evt_display::process( event * evt){
	
	crtdet_t crt_t;
	
	TTimeStamp evt_t(evt->get_time_stamp());
	
	Info("process", "Event no.%i, Time Stamp %s", evt->get_nevent(), evt_t.AsString("l"));
	Info("process", "CRT Match %i, CRT Reco %i", evt->get_crt_daq_match(), evt->get_crt_reco());
	Info("process", "Track Z %.2f, tan(theta) %.2f", evt->get_crt_track_param()[0], evt->get_crt_track_param()[1] );		
	
	
	c_pmt->SetTitle( TString::Format("Evt %i, Time %s", evt->get_nevent(), evt_t.AsString("l")) );
	
	////////////////////////////////////////////////
	//
	// MAKE WAVEFORMS
	//	
	for( int ch = 0; ch < evt->get_n_channels_active(); ch++ ){	
		
		_waveform.push_back( new TH1F( TString::Format("waveform_%i", ch), TString::Format("PMT Channel %i;[#mus]; [ADC]", ch ), evt->get_waveform(ch)->size(), 0, evt->get_waveform(ch)->size() * evt->get_time_sample() ));
		_waveform[ch]->GetYaxis()->SetRangeUser(3800, 4010);
		
		for( int i = 0 ; i < _waveform[ch]->GetNbinsX(); i++) {
			_waveform[ch] -> Fill( i * evt->get_time_sample(), evt->get_waveform(ch)->at(i) );		
					
		}
	
	}

	_waveform[5]->SetTitle("CRT Trigger signal");

	////////////////////////////////////////////////
	//
	// Waveform 2D
	//
    //
	TH2F * w2d = new TH2F("h2", ";[ns]; Channel",_waveform[0]->GetNbinsX(), _waveform[0]->GetBinLowEdge(1), _waveform[0]->GetBinLowEdge(_waveform[0]->GetNbinsX()), 5, 0, 5);
	w2d->SetStats(kFALSE);
	
	//h2->GetYaxis()->SetLabelSize(0.1);
	//h2->GetXaxis()->SetLabelSize(0.1);
	
	for( int j = 0; j < 5; j++){
		for(int i = 0; i < _waveform[0]->GetNbinsX(); i++){
			w2d->SetBinContent(i+1, j+1, _waveform[j]->GetBinContent(i));	
		}	
	}
	
    w2d->SetContour(100);
	gStyle->SetPalette(52);
	w2d->GetYaxis()->SetNdivisions(105); 
	w2d->GetZaxis()->SetRangeUser(3900, 4100); 
	
	////////////////////////////////////////////////
	//
	// CRT Waveform, 1 canvas
	//
	TH1F * a_0 = new TH1F( TString::Format("crt_adc_%i", 0 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 0 ), 16, -0.5, 15+0.5 );
	TH1F * a_1 = new TH1F( TString::Format("crt_adc_%i", 1 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 1 ), 16, -0.5, 15+0.5 );	
	TH1F * a_2 = new TH1F( TString::Format("crt_adc_%i", 2 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 2 ), 16, -0.5, 15+0.5 );
	TH1F * a_3 = new TH1F( TString::Format("crt_adc_%i", 3 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 3 ), 16, -0.5, 15+0.5 );
	
	a_0->GetYaxis()->SetRangeUser(0, 4500);
	
	a_0->SetLineColor(kViolet);
	a_1->SetLineColor(kAzure);
	a_2->SetLineColor(kPink);
	a_3->SetLineColor(kOrange);
	
	for( int i = 0 ; i < 32; i++) {
	
		a_0->Fill(i/2, evt->get_crt_adc(0)[i]);
		a_1->Fill(i/2, evt->get_crt_adc(1)[i]);
		a_2->Fill(i/2, evt->get_crt_adc(2)[i]);
		a_3->Fill(i/2, evt->get_crt_adc(3)[i]);	
    
	}
		
	////////////////////////////////////////////////
	//
	// CRT Hit position
	//
	TH2F * crt_xy_1 = new TH2F( TString::Format("crt_xy_1" ), TString::Format("CRT XY Panel 1; [mm]; [mm]" ), 32, crt_t.strip_pos1[0].X() - 112/2. , crt_t.strip_pos1[15].X() + 112/2. , 32, crt_t.strip_pos1[15].Z() - 112/2., crt_t.strip_pos1[0].Z() + 112/2);
	TH2F * crt_xy_2 = new TH2F( TString::Format("crt_xy_2" ), TString::Format("CRT XY Panel 2; [mm]; [mm]" ), 32, crt_t.strip_pos2[0].X() - 112/2. , crt_t.strip_pos2[15].X() + 112/2. , 32, crt_t.strip_pos2[15].Z() - 112/2., crt_t.strip_pos2[0].Z() + 112/2);	
				
	for(int i = 0; i < crt_xy_1->GetNbinsX(); i++){
		
		for(int j = 0; j < crt_xy_1->GetNbinsY(); j++){
		
			crt_xy_1->SetBinContent( i+1, crt_xy_1->GetNbinsY()-j, crt_xy_1->GetBinContent( i+1, crt_xy_1->GetNbinsY()-j) + evt->get_crt_adc(0)[i]);
			crt_xy_1->SetBinContent( i+1, crt_xy_1->GetNbinsY()-j, crt_xy_1->GetBinContent( i+1, crt_xy_1->GetNbinsY()-j) + evt->get_crt_adc(1)[j]);
			
			crt_xy_2->SetBinContent( i+1, crt_xy_2->GetNbinsY()-j, crt_xy_2->GetBinContent( i+1, crt_xy_2->GetNbinsY()-j) + evt->get_crt_adc(3)[i]);
			crt_xy_2->SetBinContent( i+1, crt_xy_2->GetNbinsY()-j, crt_xy_2->GetBinContent( i+1, crt_xy_2->GetNbinsY()-j) + evt->get_crt_adc(2)[j]);

		}
	}
	
	crt_xy_1->RebinX(2); crt_xy_1->RebinY(2);
	crt_xy_2->RebinX(2); crt_xy_2->RebinY(2);
	
	int x1 = a_0->GetBinCenter(a_0->FindFirstBinAbove(1000));
	int z1 = a_1->GetBinCenter(a_1->FindFirstBinAbove(1000));
	int z2 = a_2->GetBinCenter(a_2->FindFirstBinAbove(1000));
	int x2 = a_3->GetBinCenter(a_3->FindFirstBinAbove(1000));
		
	std::cout << "Panel 1: X, Y, Z [0]" << crt_t.strip_pos1[ 0 ].X() << " " << crt_t.strip_pos1[ 0 ].Y() << " " << crt_t.strip_pos1[ 0 ].Z() << std::endl;
	std::cout << "Panel 1: X, Y, Z [15]" << crt_t.strip_pos1[ 15 ].X() << " " << crt_t.strip_pos1[ 15 ].Y() << " " << crt_t.strip_pos1[ 15 ].Z() << std::endl;
	std::cout << "Panel 2: X, Y, Z [0]" << crt_t.strip_pos2[ 0 ].X() << " " << crt_t.strip_pos2[ 0 ].Y() << " " << crt_t.strip_pos2[ 0 ].Z() << std::endl;
	std::cout << "Panel 2: X, Y, Z [15]" << crt_t.strip_pos2[ 15 ].X() << " " << crt_t.strip_pos2[ 15 ].Y() << " " << crt_t.strip_pos2[ 15 ].Z() << std::endl;
	
	
	std::cout << "x1 " << x1 << std::endl;
	std::cout << "z1 " << z1 << std::endl;
	std::cout << "z2 " << z2 << std::endl;
	std::cout << "x2 " << x2 << std::endl;
	
	std::cout << "Panel 1: X, Y, Z " << crt_t.strip_pos1[ x1 ].X()<< " " <<  crt_t.strip_pos1[ 0 ].Y() << " " <<  crt_t.strip_pos1[ z1 ].Z() << std::endl;
	std::cout << "Panel 2: X, Y, Z " << crt_t.strip_pos2[ x2 ].X() << " " << crt_t.strip_pos2[ 0 ].Y() << " " <<  crt_t.strip_pos2[ z2 ].Z()  << std::endl;

		
	////////////////////////////////////////////////
	//
	// Track views
	//	
		
	TLine * yz_line = new TLine( crt_t.strip_pos2[ 0 ].Y(), crt_t.strip_pos2[ z2 ].Z(), crt_t.strip_pos1[ 0 ].Y(), crt_t.strip_pos1[ z1 ].Z());
	yz_line->SetLineColor(kRed);	

	TLine * xy_line = new TLine( -crt_t.strip_pos2[ 0 ].Y(), crt_t.strip_pos2[ x2 ].X(), -crt_t.strip_pos1[ 0 ].Y(), crt_t.strip_pos1[ x1 ].X());
	xy_line->SetLineColor(kRed);
		
	// DRAW
	
	go_to_pad(wCh0); _waveform[0] -> Draw("HIST");
	go_to_pad(wCh1); _waveform[1] -> Draw("HIST");
	go_to_pad(wCh2); _waveform[2] -> Draw("HIST");
	go_to_pad(wCh3); _waveform[3] -> Draw("HIST");
	go_to_pad(wCh4); _waveform[4] -> Draw("HIST");
	//go_to_pad(wAll); w2d->Draw("COLZ");
	
	go_to_pad(crtT); _waveform[5] -> Draw("HIST");
	
	go_to_pad(crtW); 
	a_0->Draw("HIST");
	a_1->Draw("HIST,Same");
	a_2->Draw("HIST,Same");
	a_3->Draw("HIST,Same");
	go_to_pad(crtW)->BuildLegend();
	
	go_to_pad(crtXY1); crt_xy_1->Draw("COLZ");
	go_to_pad(crtXY2); crt_xy_2->Draw("COLZ");
	go_to_pad(viewYZ); _view_yz->Draw(); yz_line->Draw("");
	go_to_pad(viewXY); _view_xy->Draw(); xy_line->Draw("");	
				
	c_pmt->cd()->Modified(); c_pmt->cd()->Update();		
			    
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
			
			c_pmt->Update();
			c_pmt->Print( TString::Format("waveforms_evt_%i.png", evt->get_nevent()) );			
			TFile * tmp_f = new TFile(TString::Format("waveforms_evt_%i.root", evt->get_nevent()), "RECREATE" );
			
			for( int i = 0; i < evt->get_n_channels_active(); i++ ){	
				_waveform[i]->Write();
			}
				
			w2d->Write();	
												
			xy_line->Write();	
			yz_line->Write();

			_view_xy->Write();
			_view_yz->Write();
				
			a_0->Write();
			a_1->Write();
			a_2->Write();
			a_3->Write();
			
			crt_xy_1->Write();
			crt_xy_2->Write();
			
			tmp_f->Close();
			
		} else {
			break;
		}
				 
		  
      }
    
  	timer->TurnOff();
    
  	delete timer;
	_waveform.clear();

	delete w2d;

	delete xy_line;    
	delete yz_line;
    
	delete a_0;
	delete a_1;
	delete a_2;
	delete a_3;

	delete crt_xy_1;
	delete crt_xy_2;

	return true;

}

void module_evt_display::terminate(){


}