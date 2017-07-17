#include<TFile.h>
#include<TChain.h>
#include<TBranch.h>
#include<TH1F.h>
#include<TGraph.h>
#include<TCanvas.h>
#include<TPad.h>
#include<TStyle.h>
#include<TMath.h>
#include<iostream>
#include<fstream>
#include<string>

void get_pvss_data( const char * fn, int ts_start, int ts_stop, TGraph & g, bool debug = false){
	
	//
	// Get PVSS Data
	//
	std::ifstream ifs;
	ifs.open(fn, std::ifstream::in);
	if( !ifs.is_open() ) Fatal("","PVSS Data not open!");

	// Get rid of the fist line
	string tmp;
	getline(ifs, tmp);


	int np = 0;
    int ts_raw;
	double vv_raw;
	   
	while (ifs.good()) {
       ifs >> ts_raw >> vv_raw;
	   
	   if(debug)
		   cout << ts_raw << " " << vv_raw << endl;

	   if( ts_raw >= ts_start && ts_raw < ts_stop ){
		   g.SetPoint(np, ts_raw, vv_raw);
	  	   np++;
		}
		
    }
	
}

void trigger_rate_hv_corr(){

	//
	// Create the TChain to Display
	//
	TChain * t = new TChain("midas_data");

	//
	// Add root file to Display
	//
	//t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1225) );
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1228) );
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1229) );	
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1234) );		
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1235) );		
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1236) );				
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1237) );				
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1238) );				
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 1239) );							

	int adc_value[6][300000];
	int ts; 
	
	t->SetBranchStatus("*",0); //disable all branches
	TBranch * _b_ts; t->SetBranchStatus("TimeStamp", 1); 
	t->SetBranchAddress("TimeStamp", &ts, &_b_ts);	

	//
	// Trigger rate	
	//
	int t_min = t->GetMinimum("TimeStamp");
	int t_max = t->GetMaximum("TimeStamp");
	double t_l = t_max-t_min;

	TH1F * h0 = new TH1F("h0", "h0", 500, t_min, t_max);

	for( int i = 0; i < t->GetEntries(); ++i ){
		
		t->GetEntry(i);
		
		h0->Fill(ts);
		
	}

	//TString s = Form("TimeStamp>>h0");
	//t->Draw(s,"", "goff");
	h0->Scale( h0->GetNbinsX()/t_l );
			
	//
	// Get PVSS Data
	//
	TGraph * g_grid = new TGraph();	
	g_grid->SetName("g_grid");
	get_pvss_data("/Users/alberto/Software/WA105/WA105_LightSoft/PVSS_data/grid_HV.txt", t_min, t_max, *g_grid);

	TGraph * g_lem = new TGraph();	
	g_lem->SetName("g_lem");
	get_pvss_data("/Users/alberto/Software/WA105/WA105_LightSoft/PVSS_data/lem06d_HV.txt", t_min, t_max, *g_lem);
	
	TCanvas * c = new TCanvas();
	
	c->Divide(1,3);
	
	c->cd(1)->SetRightMargin(0);
	c->cd(2)->SetRightMargin(0);
	c->cd(3)->SetRightMargin(0);	
	
    c->cd(1)->SetTickx() ;
    c->cd(2)->SetTickx() ;
    c->cd(3)->SetTickx() ;

    c->cd(1)->SetTicky() ;
    c->cd(2)->SetTicky() ;
    c->cd(3)->SetTicky() ;
	
	c->cd(1)->SetTopMargin(0);
	//c->cd(1)->SetBottomMargin(0);
	//c->cd(2)->SetTopMargin(0);
	//c->cd(2)->SetBottomMargin(0);
	//c->cd(3)->SetTopMargin(0);
		
	gStyle->SetOptStat(0);
		
	c->cd(1);
	
	h0->SetLineColor(kBlack);
	h0->Draw();
	h0->SetTitle("");
	h0->GetXaxis()->SetTickLength(0.05);
	h0->GetXaxis()->SetTitle("");
	h0->GetXaxis()->SetTimeDisplay(1);
	h0->GetXaxis()->SetTimeOffset(1*60*60);
	h0->GetXaxis()->SetTimeFormat("%H:%M");
	h0->GetYaxis()->SetTitle("Trigger rate [Hz]");
	h0->GetYaxis()->SetRangeUser(0,5);
	h0->GetYaxis()->SetTitleSize(0.10);
	h0->GetYaxis()->SetTitleOffset(0.50);
	h0->GetXaxis()->SetLabelSize(0.10);
	h0->GetYaxis()->SetLabelSize(0.10);
	h0->Fit("pol0","L0");
	
	c->cd(2);
	
	g_grid->Draw("ALP");
	g_grid->SetMarkerColor(kRed);
	g_grid->SetLineColor(kRed);	
	g_grid->GetXaxis()->SetTickLength(0.05);
	g_grid->GetYaxis()->SetTitleSize(0.10);
	g_grid->GetYaxis()->SetTitleOffset(0.50);
	g_grid->GetXaxis()->SetLabelSize(0.10);
	g_grid->GetYaxis()->SetLabelSize(0.10);
	g_grid->GetXaxis()->SetRangeUser(t_min,t_max);
	g_grid->GetXaxis()->SetTimeDisplay(1);
	g_grid->GetXaxis()->SetTimeOffset(1*60*60);
	g_grid->GetXaxis()->SetTimeFormat("%H:%M");
	g_grid->GetXaxis()->SetTitle("");
	g_grid->GetYaxis()->SetTitle("HV Grid [V]");

	c->cd(3);
	
	g_lem->Draw("ALP");
	g_lem->SetMarkerColor(kBlue);
	g_lem->SetLineColor(kBlue);
	g_lem->GetXaxis()->SetTickLength(0.05);
	g_lem->GetYaxis()->SetTitleSize(0.10);
	g_lem->GetYaxis()->SetTitleOffset(0.50);
	g_lem->GetXaxis()->SetLabelSize(0.10);
	g_lem->GetYaxis()->SetLabelSize(0.10);
	g_lem->GetXaxis()->SetRangeUser(t_min,t_max);
	g_lem->GetXaxis()->SetTimeDisplay(1);
	g_lem->GetXaxis()->SetTimeOffset(1*60*60);
	g_lem->GetXaxis()->SetTimeFormat("%H:%M");
	g_lem->GetXaxis()->SetTitle("");
	g_lem->GetYaxis()->SetTitle("HV LEM 6 Down [V]");
	
	c->Update();
		
	std::cout << "Noe: " << t->GetEntries() << " Run time [s]: " << t_l << std::endl;
	std::cout << "Rate [Hz]: " << t->GetEntries()/t_l   << " +/- " << sqrt(t->GetEntries())/t_l   << std::endl;
	
	TFile fout("trigger_rate_hv_corr.root", "RECREATE");
	h0->Write();
	g_grid->Write();
	g_lem->Write();	
	
	fout.Close();

}
