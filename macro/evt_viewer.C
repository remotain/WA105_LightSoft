evt_viewer(TString name = "", double adc_min = 0, double adc_max = 4100){
	
	TFile * f = new TFile(name, "READ");
	
	TIter next( f->GetListOfKeys() );
	
	TKey *k;
	
	TH1F * w[5];
	
	TH2F * crt[2];
	
	//gStyle->SetOptTitle(0);
	
	TString tmp_name; tmp_name = name;
	
	while( k = (TKey*) next() ){
		
		TString tmp; tmp.Form("%s", k->GetName());
		
		if      ( tmp.Contains("waveform_0_") ) { w[0]   = (TH1F*) k->ReadObj(); TCanvas * c_w_0 = new TCanvas();  w[0]->GetYaxis()->SetRangeUser(adc_min, adc_max); w[0]->GetXaxis()->SetTitle("[#mus]"); w[0]->Draw(); c_w_0->SaveAs( tmp_name.ReplaceAll(".root", "") + "_c_w_0.png" ); }
		else if ( tmp.Contains("waveform_1_") ) { w[1]   = (TH1F*) k->ReadObj(); TCanvas * c_w_1 = new TCanvas();  w[1]->GetYaxis()->SetRangeUser(adc_min, adc_max); w[1]->GetXaxis()->SetTitle("[#mus]"); w[1]->Draw(); c_w_1->SaveAs( tmp_name.ReplaceAll(".root", "") + "_c_w_1.png" ); }
		else if ( tmp.Contains("waveform_2_") ) { w[2]   = (TH1F*) k->ReadObj(); TCanvas * c_w_2 = new TCanvas();  w[2]->GetYaxis()->SetRangeUser(adc_min, adc_max); w[2]->GetXaxis()->SetTitle("[#mus]"); w[2]->Draw(); c_w_2->SaveAs( tmp_name.ReplaceAll(".root", "") + "_c_w_2.png" ); }
		else if ( tmp.Contains("waveform_3_") ) { w[3]   = (TH1F*) k->ReadObj(); TCanvas * c_w_3 = new TCanvas();  w[3]->GetYaxis()->SetRangeUser(adc_min, adc_max); w[3]->GetXaxis()->SetTitle("[#mus]"); w[3]->Draw(); c_w_3->SaveAs( tmp_name.ReplaceAll(".root", "") + "_c_w_3.png" ); }
		else if ( tmp.Contains("waveform_4_") ) { w[4]   = (TH1F*) k->ReadObj(); TCanvas * c_w_4 = new TCanvas();  w[4]->GetYaxis()->SetRangeUser(adc_min, adc_max); w[4]->GetXaxis()->SetTitle("[#mus]"); w[4]->Draw(); c_w_4->SaveAs( tmp_name.ReplaceAll(".root", "") + "_c_w_4.png" ); }
		else if ( tmp.Contains("crt_xy_0_")   ) { crt[0] = (TH2F*) k->ReadObj(); }		
		else if ( tmp.Contains("crt_xy_1_")   ) { crt[1] = (TH2F*) k->ReadObj(); }		
		
	}
	
	
	
}