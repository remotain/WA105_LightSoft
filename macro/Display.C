#include<iostream>

#include<TSystem.h>
#include<TChain.h>
#include<TBranch.h>
#include<TCanvas.h>
#include<TH1.h>
#include<TH2.h>
#include<TLine.h>
#include<TString.h>
#include<TStyle.h>
#include<TTimeStamp.h>

#include "WaveUtils.h"
#include "THDet.C"

using namespace std;

struct tot_peak_t {
  int n;
  int n_sel;
  int q;
};

//bool _find_peaks = false;
//bool _match = true;
//bool _reco = true;

bool _find_peaks = false;
bool _match = false;
bool _reco = false;


void Display(int run_number = 722){

	//
	// Create the TChain to Display
	//
	TChain * t = new TChain("midas_data");

	//
	// Add root file to Display
	//
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );

	//
	// Branches
	//
	TBranch * _b_time_stamp   ; int    _time_stamp          ; t->SetBranchAddress("TimeStamp"     , &_time_stamp      , &_b_time_stamp    );
	TBranch * _b_nsamples     ; int    _nsamples            ; t->SetBranchAddress("nsamples"      , &_nsamples        , &_b_nsamples      );
	TBranch * _b_crt_daq_match; int    _crt_daq_match       ; t->SetBranchAddress("crt_daq_match" , &_crt_daq_match   , &_b_crt_daq_match );
	TBranch * _b_crt_reco     ; int    _crt_reco            ; t->SetBranchAddress("crt_reco"      , &_crt_reco		  , &_b_crt_reco      );
	TBranch * _b_crt_tof      ; double _crt_tof             ; t->SetBranchAddress("crt_ToF"       , &_crt_tof		  , &_b_crt_tof       );		
	TBranch * _b_crt_adc      ; int    _crt_adc[4][32]      ; t->SetBranchAddress("crt_adc"       , _crt_adc          , &_b_crt_adc       );
	TBranch * _b_adc_value_0  ; int    _adc_value_0[300000] ; t->SetBranchAddress("adc_value_0"   , _adc_value_0      , &_b_adc_value_0   );
	TBranch * _b_adc_value_1  ; int    _adc_value_1[300000] ; t->SetBranchAddress("adc_value_1"   , _adc_value_1      , &_b_adc_value_1   );
	TBranch * _b_adc_value_2  ; int    _adc_value_2[300000] ; t->SetBranchAddress("adc_value_2"   , _adc_value_2      , &_b_adc_value_2   );
	TBranch * _b_adc_value_3  ; int    _adc_value_3[300000] ; t->SetBranchAddress("adc_value_3"   , _adc_value_3      , &_b_adc_value_3   );
	TBranch * _b_adc_value_4  ; int    _adc_value_4[300000] ; t->SetBranchAddress("adc_value_4"   , _adc_value_4      , &_b_adc_value_4   );
	TBranch * _b_adc_value_5  ; int    _adc_value_5[300000] ; t->SetBranchAddress("adc_value_5"   , _adc_value_5      , &_b_adc_value_5   );

	//
	// Canvas
	//
	TCanvas * c = new TCanvas("PMT Display", "PMT Display", 5000, 5000);
		
	c->Divide(1,3);	
	c->cd(1)->Divide(5,1);
	c->cd(2)->Divide(4,1);
	c->cd(3)->Divide(2,1);	
	
	//
	// Global Style option
	//
	gStyle->SetOptStat(0);
	gStyle->SetPalette(53);	
		
	//
	// LOAD Detector view
	//	
	TFile * f_geo = new TFile("$WLS_PATH/macro/fdet.root", "READ");
	
	if( f_geo->IsZombie() ) {
		
		Fatal("f_geo","Geometry file does not exist");
		
	}
	
    TH2Poly * crt_view_yz = (TH2Poly*) f_geo->Get("hDet_YZ"); crt_view_yz->SetTitle("View YZ (Lateral)");
	TH2Poly * crt_view_xy = (TH2Poly*) f_geo->Get("hDet_YX"); crt_view_xy->SetTitle("View XY (Top)");	
		
	//
	// Event loop
	//
	for(int ev=0; ev < t->GetEntries()-1 ; ++ev) {

		t->GetEntry(ev);

		if( _match && _crt_daq_match != 1 ) continue;
		if( _reco && _crt_reco != 1 ) continue;

		//
		// ADC Waveforms
		//
		TH1F * h0 = new TH1F( "h0","PMT Channel 0;[#mus]; [ADC]", _nsamples, 0, _nsamples*4 );
		TH1F * h1 = new TH1F( "h1","PMT Channel 1;[#mus]; [ADC]", _nsamples, 0, _nsamples*4 );
		TH1F * h2 = new TH1F( "h2","PMT Channel 2;[#mus]; [ADC]", _nsamples, 0, _nsamples*4 );
		TH1F * h3 = new TH1F( "h3","PMT Channel 3;[#mus]; [ADC]", _nsamples, 0, _nsamples*4 );	
		TH1F * h4 = new TH1F( "h4","PMT Channel 4;[#mus]; [ADC]", _nsamples, 0, _nsamples*4 );
		TH1F * h5 = new TH1F( "h5","CRT trigger;[#mus]; [ADC]"  , _nsamples, 0, _nsamples*4 );
					
		for(int i=0; i<_nsamples; ++i) {
      	      h0->SetBinContent(i+1,_adc_value_0[i]);
      	      h1->SetBinContent(i+1,_adc_value_1[i]);
      	      h2->SetBinContent(i+1,_adc_value_2[i]);
      	      h3->SetBinContent(i+1,_adc_value_3[i]);
      	      h4->SetBinContent(i+1,_adc_value_4[i]);			  			  			  	   
			  h5->SetBinContent(i+1,_adc_value_5[i]);			  			  			  	   
		}
						
		//
		// Charge calculation
		//
		
		tot_peak_t q[5];	
		
		if( _find_peaks ) {
		
			WaveUtils wu;	
			TH1F * w[5];
						
			w[0] = h0;
			w[1] = h1;
			w[2] = h2;
			w[3] = h3;		
			w[4] = h4;
		
			for( int ch = 0; ch < 5; ch++){
				
				wu.FindPeaks(*w[ch],-1,50,_nsamples);
				
				int npeaks = wu.peak_list.size();
			    int nsel = 0;
			    float totq = 0;
			
			    for(int i=0; i<npeaks; ++i) {
        	
			      if( !wu.peak_list[i].isolated ) continue;
			      if( wu.peak_list[i].quality!=0 ) continue;
        	
        	
			      nsel++;
			      totq += wu.peak_list[i].integ*1.;
			  	}
			
				q[ch].n = npeaks;
				q[ch].n_sel = nsel;
				q[ch].q = totq;
				
			}
		} // if( _find_peaks )
		
		//
		// CRT Waveforms
		//
		TH1F * a_0 = new TH1F( TString::Format("crt_adc_%i", 0 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 0 ), 16, -0.5, 15+0.5 );
		TH1F * a_1 = new TH1F( TString::Format("crt_adc_%i", 1 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 1 ), 16, -0.5, 15+0.5 );	
		TH1F * a_2 = new TH1F( TString::Format("crt_adc_%i", 2 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 2 ), 16, -0.5, 15+0.5 );
		TH1F * a_3 = new TH1F( TString::Format("crt_adc_%i", 3 ), TString::Format("CRT ADC %i; [channel]; [ADC]", 3 ), 16, -0.5, 15+0.5 );
	
		a_0->GetYaxis()->SetRangeUser(0, 4500); a_0->SetLineColor(kViolet);
		a_1->GetYaxis()->SetRangeUser(0, 4500); a_1->SetLineColor(kAzure);
		a_2->GetYaxis()->SetRangeUser(0, 4500); a_2->SetLineColor(kPink);
		a_3->GetYaxis()->SetRangeUser(0, 4500); a_3->SetLineColor(kOrange);
	
		for( int i = 0 ; i < 32; i++) {
	
			a_0->Fill(i/2, _crt_adc[0][i]); 
			a_1->Fill(i/2, _crt_adc[1][i]); 
			a_2->Fill(i/2, _crt_adc[2][i]); 
			a_3->Fill(i/2, _crt_adc[3][i]); 	
    
		}
	
		//
		// CRT Hit position
		//
		crtdet_t crt_t;
		
		TH2F * crt_xy_1 = new TH2F( TString::Format("crt_xy_1" ), TString::Format("CRT XY Panel 1; [mm]; [mm]" ), 32, crt_t.strip_pos1[0].X() - 112/2. , crt_t.strip_pos1[15].X() + 112/2. , 32, crt_t.strip_pos1[15].Z() - 112/2., crt_t.strip_pos1[0].Z() + 112/2);
		TH2F * crt_xy_2 = new TH2F( TString::Format("crt_xy_2" ), TString::Format("CRT XY Panel 2; [mm]; [mm]" ), 32, crt_t.strip_pos2[0].X() - 112/2. , crt_t.strip_pos2[15].X() + 112/2. , 32, crt_t.strip_pos2[15].Z() - 112/2., crt_t.strip_pos2[0].Z() + 112/2);	
				
		for(int i = 0; i < crt_xy_1->GetNbinsX(); i++){
		
			for(int j = 0; j < crt_xy_1->GetNbinsY(); j++){
		
				crt_xy_1->SetBinContent( i+1, crt_xy_1->GetNbinsY()-j, crt_xy_1->GetBinContent( i+1, crt_xy_1->GetNbinsY()-j) + _crt_adc[0][i]);
				crt_xy_1->SetBinContent( i+1, crt_xy_1->GetNbinsY()-j, crt_xy_1->GetBinContent( i+1, crt_xy_1->GetNbinsY()-j) + _crt_adc[1][j]);
			
				crt_xy_2->SetBinContent( i+1, crt_xy_2->GetNbinsY()-j, crt_xy_2->GetBinContent( i+1, crt_xy_2->GetNbinsY()-j) + _crt_adc[3][i]);
				crt_xy_2->SetBinContent( i+1, crt_xy_2->GetNbinsY()-j, crt_xy_2->GetBinContent( i+1, crt_xy_2->GetNbinsY()-j) + _crt_adc[2][j]);

			}
		}
	
		crt_xy_1->RebinX(2); crt_xy_1->RebinY(2);
		crt_xy_2->RebinX(2); crt_xy_2->RebinY(2);
	
		//
		// CRT Hit position
		//
		int x1 = a_0->GetBinCenter(a_0->FindFirstBinAbove(1000));
		int z1 = a_1->GetBinCenter(a_1->FindFirstBinAbove(1000));
		int z2 = a_2->GetBinCenter(a_2->FindFirstBinAbove(1000));
		int x2 = a_3->GetBinCenter(a_3->FindFirstBinAbove(1000));
		
		//std::cout << "Panel 1: X, Y, Z [0]" << crt_t.strip_pos1[ 0 ].X() << " " << crt_t.strip_pos1[ 0 ].Y() << " " << crt_t.strip_pos1[ 0 ].Z() << std::endl;
		//std::cout << "Panel 1: X, Y, Z [15]" << crt_t.strip_pos1[ 15 ].X() << " " << crt_t.strip_pos1[ 15 ].Y() << " " << crt_t.strip_pos1[ 15 ].Z() << std::endl;
		//std::cout << "Panel 2: X, Y, Z [0]" << crt_t.strip_pos2[ 0 ].X() << " " << crt_t.strip_pos2[ 0 ].Y() << " " << crt_t.strip_pos2[ 0 ].Z() << std::endl;
		//std::cout << "Panel 2: X, Y, Z [15]" << crt_t.strip_pos2[ 15 ].X() << " " << crt_t.strip_pos2[ 15 ].Y() << " " << crt_t.strip_pos2[ 15 ].Z() << std::endl;
	
		//std::cout << "x1 " << x1 << std::endl;
		//std::cout << "z1 " << z1 << std::endl;
		//std::cout << "z2 " << z2 << std::endl;
		//std::cout << "x2 " << x2 << std::endl;
	
		//std::cout << "Panel 1: X, Y, Z " << crt_t.strip_pos1[ x1 ].X()<< " " <<  crt_t.strip_pos1[ 0 ].Y() << " " <<  crt_t.strip_pos1[ z1 ].Z() << std::endl;
		//std::cout << "Panel 2: X, Y, Z " << crt_t.strip_pos2[ x2 ].X() << " " << crt_t.strip_pos2[ 0 ].Y() << " " <<  crt_t.strip_pos2[ z2 ].Z()  << std::endl;

		TLine * yz_line = new TLine( crt_t.strip_pos2[ 0 ].Y(), crt_t.strip_pos2[ z2 ].Z(), crt_t.strip_pos1[ 0 ].Y(), crt_t.strip_pos1[ z1 ].Z());
		yz_line->SetLineColor(kRed);	

		TLine * xy_line = new TLine( -crt_t.strip_pos2[ 0 ].Y(), crt_t.strip_pos2[ x2 ].X(), -crt_t.strip_pos1[ 0 ].Y(), crt_t.strip_pos1[ x1 ].X());
		xy_line->SetLineColor(kRed);
		
		//
		// Print on screen
		//
		TTimeStamp evt_t(_time_stamp);
		cout<<endl;
		Info("Display", "Event no.%i, Time Stamp %s", ev, evt_t.AsString("l"));
		Info("Display", " CRT Match %i, CRT Reco %i", _crt_daq_match, _crt_reco);
		Info("Display", " CRT Panel 1 (%.1f, %.1f, %.1f)", crt_t.strip_pos1[ x1 ].X(), crt_t.strip_pos1[ 0 ].Y(), crt_t.strip_pos1[ z1 ].Z() );
		Info("Display", " CRT Panel 2 (%.1f, %.1f, %.1f)", crt_t.strip_pos2[ x2 ].X(), crt_t.strip_pos2[ 0 ].Y(), crt_t.strip_pos2[ z2 ].Z() );
		
		if( _find_peaks ) {
			for( int ch = 0; ch < 5; ch++){
				Info("Display", " PeakFinder %i: N = %i, N_sel = %i, Q = %.2d", ch, q[ch].n, q[ch].n_sel, q[ch].q);		
			}
		}
		
		//
		// Draw
		//
		c->cd(1)->cd(1); h0->Draw();
		c->cd(1)->cd(2); h1->Draw();
		c->cd(1)->cd(3); h2->Draw();		
		c->cd(1)->cd(4); h3->Draw();		
		c->cd(1)->cd(5); h4->Draw();		
		c->cd(2)->cd(1); h5->Draw();		
		
		c->cd(2)->cd(2);		
		a_0->Draw("HIST");
		a_1->Draw("HIST,Same");
		a_2->Draw("HIST,Same");
		a_3->Draw("HIST,Same");
		c->cd(2)->cd(2)->BuildLegend();
		c->cd(2)->cd(3); crt_xy_1->Draw("COLZ");
		c->cd(2)->cd(4); crt_xy_2->Draw("COLZ");
		
		c->cd(3)->cd(1); crt_view_yz->Draw(); yz_line->Draw("");
		c->cd(3)->cd(2); crt_view_xy->Draw(); xy_line->Draw("");	
						
		c->cd()->Modified(); 
		
		c->cd()->Update();		
	
		//
		// Display
		//
			    
		TTimer * timer = new TTimer("gSystem->ProcessEvents();", 50, kFALSE);

		timer->TurnOn();

		timer->Reset();
	
	    while (1) {
	    
			gSystem->ProcessEvents();
			
			char key;	

			std::cout<< " (return to next, p to prev, s to save, q to quit): "; 

			std::cin.get(key);
			if( key == 'q' || key == 'Q') {
				gSystem->Exit(0);
			} if( key == 's' || key == 'S') {
				c->Update();
				
				c->Print( TString::Format("display_evt_%i.png", ev) );			
				TFile * tmp_f = new TFile(TString::Format("display_evt_%i.root", ev), "RECREATE" );
				
				h0->Write();
				h1->Write();
				h2->Write();
				h3->Write();
				h4->Write();
				h5->Write();
				
				a_0->Write();
				a_1->Write();
				a_2->Write();
				a_3->Write();
				
				crt_xy_1->Write();
		        crt_xy_2->Write();
				
				crt_view_yz->Write(); 
				crt_view_xy->Write(); 
				
				yz_line->Write();
				xy_line->Write();
				
			} else {
				break;
			}
				 
		  
	      }
    
	  	timer->TurnOff();
    	
		delete h0;
		delete h1;
		delete h2;
		delete h3;
		delete h4;
		delete h5;
		
		delete a_0;
		delete a_1;
		delete a_2;
		delete a_3;
		  
	}
	
	delete c;

}