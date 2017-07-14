void pedestals(int run_number = 722){

	//
	// Create the TChain to Display
	//
	TChain * t = new TChain("midas_data");

	//
	// Add root file to Display
	//
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );

	TH1F * h[5];
	TGraph * g[5];

	for(int c = 0; c < 5; c++){
		
		h[c] = new TH1F(TString::Format("ped%i",c), TString::Format("ped%i;[ADC]; Entries",c), 1000, 3096, 4096);
		g[c] = new TGraph();
		
		for(int i = 0; i < t->GetEntriesFast(); ++i){
		
			t->Draw(TString::Format("TimeStamp:adc_value_%i",c),"", "goff", 1, i);
			double *ts = t->GetV1();
			double *adc = t->GetV2();
			
			double ped = TMath::Mean(100, adc);
			
			h[c]->Fill(ped);
			//tmp.GetRMS();
				
			g[c]->SetPoint(i-1, ts[0], ped);
				
		}
		
		
	}
	
	TCanvas * c = new TCanvas();
	h[0]->Draw("PLC");
	h[1]->Draw("SAMES PLC");
	h[2]->Draw("SAMES PLC");
	h[3]->Draw("SAMES PLC");
	h[4]->Draw("SAMES PLC");				

	TCanvas * cg = new TCanvas();
	
	gStyle->SetPalette(kSolar);
	
	g[0]->SetTitle("Channel 0"); g[0]->Draw("APL");    
	g[1]->SetTitle("Channel 1"); g[1]->Draw("SAME PL");
	g[2]->SetTitle("Channel 2"); g[2]->Draw("SAME PL");
	g[3]->SetTitle("Channel 3"); g[3]->Draw("SAME PL");
	g[4]->SetTitle("Channel 4"); g[4]->Draw("SAME PL");
		
	 g[0]->SetFillColor(kWhite); g[0]->SetLineColor(kOrange+0); g[0]->SetMarkerColor(kOrange+0);	
	 g[1]->SetFillColor(kWhite); g[1]->SetLineColor(kOrange+1); g[1]->SetMarkerColor(kOrange+1);	
	 g[2]->SetFillColor(kWhite); g[2]->SetLineColor(kOrange+2); g[2]->SetMarkerColor(kOrange+2);	
	 g[3]->SetFillColor(kWhite); g[3]->SetLineColor(kOrange+3); g[3]->SetMarkerColor(kOrange+3);	
	 g[4]->SetFillColor(kWhite); g[4]->SetLineColor(kOrange+4); g[4]->SetMarkerColor(kOrange+4);	
		
		
	g[0]->GetXaxis()->SetTimeDisplay(1);
	g[0]->GetXaxis()->SetTimeOffset(1*60*60);
	g[0]->GetXaxis()->SetTimeFormat("%H:%M");
	g[0]->GetXaxis()->SetTitle("Time");
	g[0]->GetYaxis()->SetTitle("Mean pedestal [ADC]");

	cg->BuildLegend();	
		
		
}