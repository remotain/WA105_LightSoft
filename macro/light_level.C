#include<TSystem.h>
#include <TChain.h>
#include <TBranch.h>
#include <TFile.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TStyle.h>

#include "WaveUtils.h"


TFile fout("pks.root","recreate");
TNtuple *ntp = new TNtuple("ntp","","ev:ch:t:w:a:q");
TNtuple *nt  = new TNtuple("nt" ,"","ev:ch:n:nsel:qsum");


void light_level(int run_number = 949){

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
	int _adc_value[5][300000];
	int _nsamples; 

	TBranch * _b_nsamples   ; t->SetBranchAddress("nsamples"      , &_nsamples         , &_b_nsamples      );	
	TBranch * _b_adc_value_0; t->SetBranchAddress("adc_value_0"   , _adc_value[0]      , &_b_adc_value_0   );
	TBranch * _b_adc_value_1; t->SetBranchAddress("adc_value_1"   , _adc_value[1]      , &_b_adc_value_1   );
	TBranch * _b_adc_value_2; t->SetBranchAddress("adc_value_2"   , _adc_value[2]      , &_b_adc_value_2   );
	TBranch * _b_adc_value_3; t->SetBranchAddress("adc_value_3"   , _adc_value[3]      , &_b_adc_value_3   );
	TBranch * _b_adc_value_4; t->SetBranchAddress("adc_value_4"   , _adc_value[4]      , &_b_adc_value_4   );

	WaveUtils wu;
	
    t->Draw("nsamples","","goff",1, 1);
    int NSAMPLES = t->GetV1()[0];
	
	TH1F h("h",";time sample [ns]; amplitude [ADC counts]",NSAMPLES,-0.5,NSAMPLES*4-0.5);

	//
	// Event loop
	//
	//for(int ev=0; ev < 1000 ; ++ev) {
	for(int ev=0; ev < t->GetEntries()-1 ; ++ev) {

		t->GetEntry(ev);
		
	    int frac = (int) round(100 * ev / t->GetEntriesFast());

		if ( ev % (int)round(1+(0.1*t->GetEntriesFast())) == 0 ){
			Info("Process", "%2i %% Entry (%i/%lli)" , frac, ev, t->GetEntriesFast());
		}
		
		//
		// Channel loop
		//
		for(int c = 0; c < 5; c++){
			
			//
			// Samples loop
			//
			for(int i = 0; i < _nsamples; i++){
				
				h.SetBinContent(i+1, _adc_value[c][i]);
				
			} // End samples loop
		
			//
			// Charge stuff
			//
		    wu.FindPeaks(h,-1,50,_nsamples);
		
		    int npeaks = wu.peak_list.size();
		    int nsel = 0; 
		    float totq = 0;
    
		    for(int i=0; i<npeaks; ++i) {

		      if( !wu.peak_list[i].isolated ) continue;
		      if( wu.peak_list[i].quality!=0 ) continue;
      
		      nsel++;
		      totq += wu.peak_list[i].integ*1.;

			  ntp->Fill(ev,
			  		c, 
			  		wu.peak_list[i].imax*4.,
					(wu.peak_list[i].ilast-wu.peak_list[i].ifirst+1)*1.,
					wu.peak_list[i].amp*1.,
					wu.peak_list[i].integ*1.);

		  	}			
			
			//Info("LightLevel", " Ch. %i, N %i, Nsel %i, Q %.2f", c, npeaks, nsel, totq);
			nt->Fill(ev, c, npeaks, nsel, totq);
			
		} // End channel loop
	
	} // End event loop
	
    fout.cd();
    nt->Write();
		
	TH1F* h0 = new TH1F("h0", "Channel 0; Charge [A.U.]; ", 270, -20, 250);
	TH1F* h1 = new TH1F("h1", "Channel 1; Charge [A.U.]; ", 270, -20, 250);
	TH1F* h2 = new TH1F("h2", "Channel 2; Charge [A.U.]; ", 270, -20, 250);
	TH1F* h3 = new TH1F("h3", "Channel 3; Charge [A.U.]; ", 270, -20, 250);
	TH1F* h4 = new TH1F("h4", "Channel 4; Charge [A.U.]; ", 270, -20, 250);	
		
	ntp->Draw("q>>h0", "ch==0","goff");
	ntp->Draw("q>>h1", "ch==1","goff");
	ntp->Draw("q>>h2", "ch==2","goff");	
	ntp->Draw("q>>h3", "ch==3","goff");		
	ntp->Draw("q>>h4", "ch==4","goff");
	
	h0->Scale(1/(double)h0->GetEntries()); //h0->SetMarkerColor(); //h0->SetLineColor();
	h1->Scale(1/(double)h1->GetEntries()); h1->SetMarkerColor(kRed);	 h1->SetLineColor(kRed);		
	h2->Scale(1/(double)h2->GetEntries()); h2->SetMarkerColor(kGreen+2); h2->SetLineColor(kGreen+2);	
	h3->Scale(1/(double)h3->GetEntries()); h3->SetMarkerColor(kMagenta); h3->SetLineColor(kMagenta);	
	h4->Scale(1/(double)h4->GetEntries()); h4->SetMarkerColor(kOrange);	 h4->SetLineColor(kOrange);	
	
	TCanvas * c = new TCanvas("light_level", "Light Level");
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(false);
	c->SetLogy(true);
	
	h0->Draw("hist");
	h1->Draw("hist,same");
	h2->Draw("hist,same");
	h3->Draw("hist,same");
	h4->Draw("hist,same");
	
	c->BuildLegend();
	
	Info("LightLevel (Pulse)", "Channel %i, Mean: %.2f, RMS: %.2f", 0, h0->GetMean(), h0->GetRMS());
	Info("LightLevel (Pulse)", "Channel %i, Mean: %.2f, RMS: %.2f", 1, h1->GetMean(), h1->GetRMS());
	Info("LightLevel (Pulse)", "Channel %i, Mean: %.2f, RMS: %.2f", 2, h2->GetMean(), h2->GetRMS());
	Info("LightLevel (Pulse)", "Channel %i, Mean: %.2f, RMS: %.2f", 3, h3->GetMean(), h3->GetRMS());
	Info("LightLevel (Pulse)", "Channel %i, Mean: %.2f, RMS: %.2f", 4, h4->GetMean(), h4->GetRMS());

	//
	// Total charge
	//


	TH1F* h0_tot = new TH1F("h0_tot", "Channel 0; Total Charge [A.U.]; ", 500, -50, 500);
	TH1F* h1_tot = new TH1F("h1_tot", "Channel 1; Total Charge [A.U.]; ", 500, -50, 500);
	TH1F* h2_tot = new TH1F("h2_tot", "Channel 2; Total Charge [A.U.]; ", 500, -50, 500);
	TH1F* h3_tot = new TH1F("h3_tot", "Channel 3; Total Charge [A.U.]; ", 500, -50, 500);
	TH1F* h4_tot = new TH1F("h4_tot", "Channel 4; Total Charge [A.U.]; ", 500, -50, 500);	
		
	nt->Draw("qsum>>h0_tot", "ch==0&&qsum!=0","goff");
	nt->Draw("qsum>>h1_tot", "ch==1&&qsum!=0","goff");
	nt->Draw("qsum>>h2_tot", "ch==2&&qsum!=0","goff");	
	nt->Draw("qsum>>h3_tot", "ch==3&&qsum!=0","goff");		
	nt->Draw("qsum>>h4_tot", "ch==4&&qsum!=0","goff");
	
	//h0_tot->Scale(1/(double)h0_tot->GetEntries()); 
	//h1_tot->Scale(1/(double)h1_tot->GetEntries()); 	
	//h2_tot->Scale(1/(double)h2_tot->GetEntries()); 	
	//h3_tot->Scale(1/(double)h3_tot->GetEntries()); 	
	//h4_tot->Scale(1/(double)h4_tot->GetEntries()); 
	
	//h0->SetMarkerColor(); //h0->SetLineColor();
	h1_tot->SetMarkerColor(kRed);	 h1_tot->SetLineColor(kRed);	
	h2_tot->SetMarkerColor(kGreen+2); h2_tot->SetLineColor(kGreen+2);
	h3_tot->SetMarkerColor(kMagenta); h3_tot->SetLineColor(kMagenta);
	h4_tot->SetMarkerColor(kOrange);	 h4_tot->SetLineColor(kOrange);	
	
	TCanvas * c_tot = new TCanvas("light_level_tot", "Light Level");
	gStyle->SetOptStat(0);
	gStyle->SetOptTitle(false);
	c_tot->SetLogy(true);
	
	h0_tot->Draw("hist");
	h1_tot->Draw("hist,same");
	h2_tot->Draw("hist,same");
	h3_tot->Draw("hist,same");
	h4_tot->Draw("hist,same");
	
	c_tot->BuildLegend();
	
	Info("LightLevel (Total)", "Channel %i, Mean: %.2f, RMS: %.2f", 0, h0_tot->GetMean(), h0_tot->GetRMS());
	Info("LightLevel (Total)", "Channel %i, Mean: %.2f, RMS: %.2f", 1, h1_tot->GetMean(), h1_tot->GetRMS());
	Info("LightLevel (Total)", "Channel %i, Mean: %.2f, RMS: %.2f", 2, h2_tot->GetMean(), h2_tot->GetRMS());
	Info("LightLevel (Total)", "Channel %i, Mean: %.2f, RMS: %.2f", 3, h3_tot->GetMean(), h3_tot->GetRMS());
	Info("LightLevel (Total)", "Channel %i, Mean: %.2f, RMS: %.2f", 4, h4_tot->GetMean(), h4_tot->GetRMS());


	
}