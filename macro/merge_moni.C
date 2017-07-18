#include<vector>

#include<TStyle.h>
#include<TFile.h>
#include<TH1.h>
#include<TCanvas.h>

TString file_path = "$WLS_PATH/moni/";

void trigger_rate( vector<int> run_list ){
	
	TCanvas * c = new TCanvas("TriggerRate", "Trigger Rate");
	
	c->DivideSquare( run_list.size() );
	
	TFile * f_tmp = 0;
	TH1F * h_tmp = 0;
	
	gStyle->SetOptTitle(kFALSE);
	gStyle->SetOptStat(kFALSE);
	
	for(size_t i = 0; i<run_list.size(); i++ ){
		
		f_tmp = new TFile( TString::Format("%s/output%08d.root", file_path.Data(), run_list[i]), "READ" );
		
		if( f_tmp->IsZombie() ) continue;
		
		f_tmp->Print();
		
		c->cd(i+1);
		
		h_tmp = (TH1F*) f_tmp->Get("trigger_rate");

		if( !h_tmp ) continue; 
		
		h_tmp->SetName( TString::Format("trigger_rate_%i", run_list[i]) );		
		
		h_tmp->GetXaxis()->SetTimeDisplay(0);
		h_tmp->Rebin(60);
		h_tmp->Scale(1/60.);
		h_tmp->GetXaxis()->SetTimeDisplay(1);
		h_tmp->GetYaxis()->SetRangeUser(0, 10);
		h_tmp->GetYaxis()->SetTitle("");
		h_tmp->GetXaxis()->SetTitle("");
		h_tmp->GetYaxis()->SetTitleSize(0.10);
		h_tmp->GetYaxis()->SetTitleOffset(0.50);
		h_tmp->GetXaxis()->SetLabelSize(0.05);
		h_tmp->GetYaxis()->SetLabelSize(0.05);

		h_tmp->Print();	

		h_tmp->Draw();	
			
		gPad->Update();
			
	}
	
	c->Update();
	
}

void pedestal( vector<int> run_list, int channel = 0 ){
	
	TCanvas * c = new TCanvas( TString::Format("Pedestal_%i", channel), TString::Format("Pedestal %i", channel));
	
	c->DivideSquare( run_list.size() );
	
	TFile * f_tmp = 0;
	TH1F * h_tmp = 0;
	
	gStyle->SetOptTitle(kFALSE);
	gStyle->SetOptStat(kFALSE);
	
	for(size_t i = 0; i<run_list.size(); i++ ){
		
		f_tmp = new TFile( TString::Format("%s/output%08d.root", file_path.Data(), run_list[i]), "READ" );
		
		if( f_tmp->IsZombie() ) continue;
		
		f_tmp->Print();
		
		c->cd(i+1);
		
		h_tmp = (TH1F*) f_tmp->Get( TString::Format("V1720_pedestal_prof_%i", channel) );

		if( !h_tmp ) continue; 
		
		h_tmp->SetName( TString::Format("V1720_pedestal_prof_%i_%i", channel, run_list[i]) );		
		
		h_tmp->GetXaxis()->SetTimeDisplay(0);
		h_tmp->GetXaxis()->SetTimeDisplay(1);
		h_tmp->GetYaxis()->SetRangeUser(3980, 4030);
		h_tmp->GetYaxis()->SetTitle("");
		h_tmp->GetXaxis()->SetTitle("");
		h_tmp->GetYaxis()->SetTitleSize(0.10);
		h_tmp->GetYaxis()->SetTitleOffset(0.50);
		h_tmp->GetXaxis()->SetLabelSize(0.05);
		h_tmp->GetYaxis()->SetLabelSize(0.05);

		h_tmp->Print();	

		h_tmp->Draw();	
			
		gPad->Update();
			
	}
	
	c->Update();
	
}



void merge_moni(){
	
	vector<int> run_list;

	//
	// Set run list
	//

	run_list.push_back(1222);
	run_list.push_back(1225);	
	
	for(int i = 1228; i<=1253; i++)
		run_list.push_back(i);	
	
	for(int i = 1288; i<=1289; i++)
		run_list.push_back(i);	
	
	run_list.push_back(1253);	
	
	trigger_rate( run_list );
	
	pedestal( run_list, 0 );	

	pedestal( run_list, 1 );	

	pedestal( run_list, 2 );	

	pedestal( run_list, 3 );	

	pedestal( run_list, 4 );	
	
}
