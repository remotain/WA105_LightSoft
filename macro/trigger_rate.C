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

void trigger_rate(int run_number = 722){

	//
	// Create the TChain to Display
	//
	TChain * t = new TChain("midas_data");

	//
	// Add root file to Display
	//
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );

int t_min = t->GetMinimum("TimeStamp");
int t_max = t->GetMaximum("TimeStamp");
double t_l = t_max-t_min;

cout << t_min << " " << t_max << endl;

t->SetBranchStatus("*",0); //disable all branches

int ts; 
TBranch * _b_ts; t->SetBranchStatus("TimeStamp", 1);  
t->SetBranchAddress("TimeStamp", &ts, &_b_ts);	

unsigned int tt; 
TBranch * _b_tt; t->SetBranchStatus("TriggerTimeTag", 1);  
t->SetBranchAddress("TriggerTimeTag", &tt, &_b_tt);	

TH1F * h0 = new TH1F("h0", "h0", 1000, t_min, t_max);
TH1F * hdt = new TH1F("hdt", "Event #Deltat;#Deltat [s]; Entries", 1e6, 0, 0);

unsigned int prev_tt = 0;

for( int i = 0; i < t->GetEntries(); ++i ){
	
	t->GetEntry(i);
	
	h0->Fill(ts);
	
	//cout << i << " " << ts << " " << tt << " " << prev_tt << endl;
	
	if( prev_tt != 0 ) hdt->Fill( (tt - prev_tt)*8*1e-9 );
	
	prev_tt = tt;
	
}

h0->Scale( h0->GetNbinsX()/t_l );

TCanvas * c = new TCanvas();

gStyle->SetOptStat(0);

//c->SetLogy(true);

h0->SetLineColor(kBlack);
h0->Draw();

h0->SetTitle("Trigger rate");

h0->GetXaxis()->SetTitle("Run time");
h0->GetXaxis()->SetTimeDisplay(1);
h0->GetXaxis()->SetTimeOffset(3600);
h0->GetXaxis()->SetTimeFormat("%H:%M");


h0->GetYaxis()->SetTitle("Trigger rate [Hz]");
h0->GetYaxis()->SetRangeUser(0,5);

h0->Fit("pol0","L");

c->Update();

TCanvas * cdt = new TCanvas();

gStyle->SetOptStat(111110);

gPad->SetLogx(true);

hdt->Draw();

//TF1 * f1 = new TF1("f1","[0]*TMath::Power(([1]/[2]),(x/[2]))*(TMath::Exp(-([1]/[2])))/TMath::Gamma((x/[2])+1)",1e-5,0.5);
//f1->SetParameters( 0.1, 1., 1.);
//hdt->Fit("f1","R");

gStyle->SetOptFit(1);

cdt->Update();

std::cout << "Noe: " << t->GetEntries() << " Run time [s]: " << t_l << std::endl;
std::cout << "Rate [Hz]: " << t->GetEntries()/t_l   << " +/- " << sqrt(t->GetEntries())/t_l   << std::endl;

TFile fout(TString::Format("trigger_rate_%08d.root", run_number), "RECREATE");
h0->Write();
hdt->Write();
fout.Close();

}