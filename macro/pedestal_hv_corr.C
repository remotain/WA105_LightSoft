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

void pedestal_hv_corr(){

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

	int adc_value[6][300000];
	int ts; 
	
	t->SetBranchStatus("*",0); //disable all branches
	
	TBranch * _b_ts         ; t->SetBranchStatus("TimeStamp"   , 1); t->SetBranchAddress("TimeStamp"   , &ts          , &_b_ts            );	
	TBranch * _b_adc_value_0; t->SetBranchStatus("adc_value_0" , 1); t->SetBranchAddress("adc_value_0" , adc_value[0] , &_b_adc_value_0   );
	TBranch * _b_adc_value_1; t->SetBranchStatus("adc_value_1" , 1); t->SetBranchAddress("adc_value_1" , adc_value[1] , &_b_adc_value_1   );
	TBranch * _b_adc_value_2; t->SetBranchStatus("adc_value_2" , 1); t->SetBranchAddress("adc_value_2" , adc_value[2] , &_b_adc_value_2   );
	TBranch * _b_adc_value_3; t->SetBranchStatus("adc_value_3" , 1); t->SetBranchAddress("adc_value_3" , adc_value[3] , &_b_adc_value_3   );
	TBranch * _b_adc_value_4; t->SetBranchStatus("adc_value_4" , 1); t->SetBranchAddress("adc_value_4" , adc_value[4] , &_b_adc_value_4   );
	TBranch * _b_adc_value_5; t->SetBranchStatus("adc_value_5" , 1); t->SetBranchAddress("adc_value_5" , adc_value[5] , &_b_adc_value_5   );

	//
	// Trigger rate	
	//
	int t_min = t->GetMinimum("TimeStamp");
	int t_max = t->GetMaximum("TimeStamp");
	double t_l = t_max-t_min;

	//
	// Pedestals
	//

	TGraph * gped[5];
	TGraph * grms[5];
	int nevt[5];
	double ped[5];
	double rms[5];
	for(int c = 0; c < 5; c++){
		gped[c] = new TGraph();
		grms[c] = new TGraph();
		nevt[c] = 0;
		ped[c] = 0;
		rms[c] = 0;		
	}	
	
	int t_prev = 0;
	int npt = 0;
	
	for(int i = 0; i < t->GetEntriesFast(); ++i){
		
		t->GetEntry(i);
			
		//cout << i << " " << ts << " " << t_prev << " punto" << endl;	
			
		if( t_prev == 0 ) t_prev = ts;
			
		for(int c = 0; c < 5; c++){
					    	
			ped[c] += TMath::Mean(100, adc_value[c]);
			rms[c] += TMath::RMS(100, adc_value[c]);
			nevt[c]++;
						    	
		}
		
		// smoothing 1s
		if( ts -  t_prev >= 1 ){
		
			for(int c = 0; c < 5; c++){
				gped[c]->SetPoint(npt, ts, ped[c]/nevt[c]);
				grms[c]->SetPoint(npt, ts, rms[c]/nevt[c]);
				ped[c]=0;
				rms[c]=0;
				nevt[c]=0;
			}	
				
			npt++;	
			t_prev = ts;
			
		}
		
	}
		
	//
	// Get PVSS Data
	//
	std::ifstream ifs;
	ifs.open("/Users/alberto/Software/WA105/WA105_LightSoft/PVSS_data/grid_HV_0711_0712.txt", std::ifstream::in);

	TGraph * gv = new TGraph();	
	int np = 0;
    int ts_raw;
	double vv_raw;
	
	while (ifs.good()) {
       ifs >> ts_raw >> vv_raw;
	   //cout << ts_raw << " " << vv_raw << endl;
	   if( ts_raw >= t_min && ts_raw < t_max ){
		   gv->SetPoint(np, ts_raw, vv_raw);
	  	   np++;
		}
		
    }
	
TCanvas * c_ped = new TCanvas();

gStyle->SetOptTitle(0);

c_ped->Divide(1,3);

c_ped->cd(1);

gped[0]->SetTitle("Channel 0"); gped[0]->Draw("APL");    
gped[1]->SetTitle("Channel 1"); gped[1]->Draw("SAME PL");
gped[2]->SetTitle("Channel 2"); gped[2]->Draw("SAME PL");
gped[3]->SetTitle("Channel 3"); gped[3]->Draw("SAME PL");
gped[4]->SetTitle("Channel 4"); gped[4]->Draw("SAME PL");
	
gped[0]->SetFillColor(kWhite); gped[0]->SetLineColor(kOrange+4); gped[0]->SetMarkerColor(kOrange+4);	
gped[1]->SetFillColor(kWhite); gped[1]->SetLineColor(kOrange+3); gped[1]->SetMarkerColor(kOrange+3);	
gped[2]->SetFillColor(kWhite); gped[2]->SetLineColor(kOrange+2); gped[2]->SetMarkerColor(kOrange+2);	
gped[3]->SetFillColor(kWhite); gped[3]->SetLineColor(kOrange+1); gped[3]->SetMarkerColor(kOrange+1);	
gped[4]->SetFillColor(kWhite); gped[4]->SetLineColor(kOrange+0); gped[4]->SetMarkerColor(kOrange+0);	

gped[0]->GetYaxis()->SetTitleSize(0.10);
gped[0]->GetYaxis()->SetTitleOffset(0.50);
gped[0]->GetYaxis()->SetLabelSize(0.10);
gped[0]->GetXaxis()->SetLabelSize(0.10);
gped[0]->GetYaxis()->SetRangeUser(3980,4030);
gped[0]->GetXaxis()->SetRangeUser(t_min,t_max);
gped[0]->GetXaxis()->SetTimeDisplay(1);
gped[0]->GetXaxis()->SetTimeOffset(1*60*60);
gped[0]->GetXaxis()->SetTimeFormat("%H:%M");
gped[0]->GetXaxis()->SetTitle("");
gped[0]->GetYaxis()->SetTitle("Mean pedestal [ADC]");

gPad->BuildLegend();	

c_ped->cd(2);

grms[0]->SetTitle("Channel 0"); grms[0]->Draw("APL");    
grms[1]->SetTitle("Channel 1"); grms[1]->Draw("SAME PL");
grms[2]->SetTitle("Channel 2"); grms[2]->Draw("SAME PL");
grms[3]->SetTitle("Channel 3"); grms[3]->Draw("SAME PL");
grms[4]->SetTitle("Channel 4"); grms[4]->Draw("SAME PL");
	
grms[0]->SetFillColor(kWhite); grms[0]->SetLineColor(kOrange+4); grms[0]->SetMarkerColor(kOrange+4);	
grms[1]->SetFillColor(kWhite); grms[1]->SetLineColor(kOrange+3); grms[1]->SetMarkerColor(kOrange+3);	
grms[2]->SetFillColor(kWhite); grms[2]->SetLineColor(kOrange+2); grms[2]->SetMarkerColor(kOrange+2);	
grms[3]->SetFillColor(kWhite); grms[3]->SetLineColor(kOrange+1); grms[3]->SetMarkerColor(kOrange+1);	
grms[4]->SetFillColor(kWhite); grms[4]->SetLineColor(kOrange+0); grms[4]->SetMarkerColor(kOrange+0);	

grms[0]->GetYaxis()->SetTitleSize(0.10);
grms[0]->GetYaxis()->SetTitleOffset(0.50);
grms[0]->GetYaxis()->SetLabelSize(0.10);
grms[0]->GetXaxis()->SetLabelSize(0.10);
grms[0]->GetYaxis()->SetRangeUser(0,10);
grms[0]->GetXaxis()->SetRangeUser(t_min,t_max);
grms[0]->GetXaxis()->SetTimeDisplay(1);
grms[0]->GetXaxis()->SetTimeOffset(1*60*60);
grms[0]->GetXaxis()->SetTimeFormat("%H:%M");
grms[0]->GetXaxis()->SetTitle("");
grms[0]->GetYaxis()->SetTitle("RMS pedestal [ADC]");

//gPad->BuildLegend();

c_ped->cd(3);

gv->DrawClone("ALP");

c_ped->Update();

std::cout << "Noe: " << t->GetEntries() << " Run time [s]: " << t_l << std::endl;
std::cout << "Rate [Hz]: " << t->GetEntries()/t_l   << " +/- " << sqrt(t->GetEntries())/t_l   << std::endl;

TFile fout("pedestal_hv_corr.root", "RECREATE");

for(int c = 0; c < 5; c++){
	gped[c]->Write();
	grms[c]->Write();
}

fout.Close();

}