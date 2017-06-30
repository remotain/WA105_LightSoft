#include <map>

trigger_scan(){

gSystem->Load("$WLS_PATH/build/lib/libLightSoft");

gStyle->SetOptStat(0);

TFile* _file_500  = new TFile("$WLS_DATA/recoed00000741.root");
TFile* _file_1000 = new TFile("$WLS_DATA/recoed00000742.root");
TFile* _file_1500 = new TFile("$WLS_DATA/recoed00000743.root");
TFile* _file_2000 = new TFile("$WLS_DATA/recoed00000744.root");
TFile* _file_2500 = new TFile("$WLS_DATA/recoed00000745.root");
TFile* _file_3000 = new TFile("$WLS_DATA/recoed00000746.root");
TFile* _file_3500 = new TFile("$WLS_DATA/recoed00000747.root");
TFile* _file_3600 = new TFile("$WLS_DATA/recoed00000769.root");
TFile* _file_3700 = new TFile("$WLS_DATA/recoed00000770.root");
TFile* _file_3800 = new TFile("$WLS_DATA/recoed00000762.root");
TFile* _file_3900 = new TFile("$WLS_DATA/recoed00000763.root");
TFile* _file_3950 = new TFile("$WLS_DATA/recoed00000764.root");
TFile* _file_3975 = new TFile("$WLS_DATA/recoed00000765.root");
TFile* _file_3980 = new TFile("$WLS_DATA/recoed00000766.root");
TFile* _file_3985 = new TFile("$WLS_DATA/recoed00000767.root");
TFile* _file_3990 = new TFile("$WLS_DATA/recoed00000768.root");

//TH1F * _h_500  = plot_amp_vs_th( _file_500 , "500" ); _h_500 ->Draw();
//TH1F * _h_1000 = plot_amp_vs_th( _file_1000, "1000"); _h_1000->Draw("same");
//TH1F * _h_1500 = plot_amp_vs_th( _file_1500, "1500"); _h_1500->Draw("same");
//TH1F * _h_2000 = plot_amp_vs_th( _file_2000, "2000"); _h_2000->Draw("same");
//TH1F * _h_2500 = plot_amp_vs_th( _file_2500, "2500"); _h_2500->Draw("same");
//TH1F * _h_3000 = plot_amp_vs_th( _file_3000, "3000"); _h_3000->Draw("same");
//TH1F * _h_3500 = plot_amp_vs_th( _file_3500, "3500"); _h_3500->Draw("same");
//TH1F * _h_3600 = plot_amp_vs_th( _file_3600, "3600"); _h_3600->Draw("same");
//TH1F * _h_3700 = plot_amp_vs_th( _file_3700, "3700"); _h_3700->Draw("same");
//TH1F * _h_3800 = plot_amp_vs_th( _file_3800, "3800"); _h_3800->Draw("same");
//TH1F * _h_3900 = plot_amp_vs_th( _file_3900, "3900"); _h_3900->Draw("same");
//TH1F * _h_3950 = plot_amp_vs_th( _file_3950, "3950"); _h_3950->Draw("same");
//TH1F * _h_3975 = plot_amp_vs_th( _file_3975, "3975"); _h_3975->Draw("same");
//TH1F * _h_3980 = plot_amp_vs_th( _file_3980, "3980"); _h_3980->Draw("same");
//TH1F * _h_3985 = plot_amp_vs_th( _file_3985, "3985"); _h_3985->Draw("same");
//TH1F * _h_3990 = plot_amp_vs_th( _file_3990, "3990"); _h_3990->Draw("same");

TCanvas * _c_amp  = new TCanvas();
_c_amp->Divide(4,4);

_c_amp->cd(1 ); gPad->SetLogz(true); TH2F * _h_amp_500  = plot_amp_vs_ch( _file_500 , "500" ); _h_amp_500 ->GetYaxis()->SetTitleOffset(1.4); _h_amp_500 ->GetZaxis()->SetRangeUser(0,1); _h_amp_500 ->Draw("col");
_c_amp->cd(2 ); gPad->SetLogz(true); TH2F * _h_amp_1000 = plot_amp_vs_ch( _file_1000, "1000"); _h_amp_1000->GetYaxis()->SetTitleOffset(1.4); _h_amp_1000->GetZaxis()->SetRangeUser(0,1); _h_amp_1000->Draw("col");
_c_amp->cd(3 ); gPad->SetLogz(true); TH2F * _h_amp_1500 = plot_amp_vs_ch( _file_1500, "1500"); _h_amp_1500->GetYaxis()->SetTitleOffset(1.4); _h_amp_1500->GetZaxis()->SetRangeUser(0,1); _h_amp_1500->Draw("col");
_c_amp->cd(4 ); gPad->SetLogz(true); TH2F * _h_amp_2000 = plot_amp_vs_ch( _file_2000, "2000"); _h_amp_2000->GetYaxis()->SetTitleOffset(1.4); _h_amp_2000->GetZaxis()->SetRangeUser(0,1); _h_amp_2000->Draw("colz");
_c_amp->cd(5 ); gPad->SetLogz(true); TH2F * _h_amp_2500 = plot_amp_vs_ch( _file_2500, "2500"); _h_amp_2500->GetYaxis()->SetTitleOffset(1.4); _h_amp_2500->GetZaxis()->SetRangeUser(0,1); _h_amp_2500->Draw("col");
_c_amp->cd(6 ); gPad->SetLogz(true); TH2F * _h_amp_3000 = plot_amp_vs_ch( _file_3000, "3000"); _h_amp_3000->GetYaxis()->SetTitleOffset(1.4); _h_amp_3000->GetZaxis()->SetRangeUser(0,1); _h_amp_3000->Draw("col");
_c_amp->cd(7 ); gPad->SetLogz(true); TH2F * _h_amp_3500 = plot_amp_vs_ch( _file_3500, "3500"); _h_amp_3500->GetYaxis()->SetTitleOffset(1.4); _h_amp_3500->GetZaxis()->SetRangeUser(0,1); _h_amp_3500->Draw("col");
_c_amp->cd(8 ); gPad->SetLogz(true); TH2F * _h_amp_3600 = plot_amp_vs_ch( _file_3600, "3600"); _h_amp_3600->GetYaxis()->SetTitleOffset(1.4); _h_amp_3600->GetZaxis()->SetRangeUser(0,1); _h_amp_3600->Draw("colz");
_c_amp->cd(9 ); gPad->SetLogz(true); TH2F * _h_amp_3700 = plot_amp_vs_ch( _file_3700, "3700"); _h_amp_3700->GetYaxis()->SetTitleOffset(1.4); _h_amp_3700->GetZaxis()->SetRangeUser(0,1); _h_amp_3700->Draw("col");
_c_amp->cd(10); gPad->SetLogz(true); TH2F * _h_amp_3800 = plot_amp_vs_ch( _file_3800, "3800"); _h_amp_3800->GetYaxis()->SetTitleOffset(1.4); _h_amp_3800->GetZaxis()->SetRangeUser(0,1); _h_amp_3800->Draw("col");
_c_amp->cd(11); gPad->SetLogz(true); TH2F * _h_amp_3900 = plot_amp_vs_ch( _file_3900, "3900"); _h_amp_3900->GetYaxis()->SetTitleOffset(1.4); _h_amp_3900->GetZaxis()->SetRangeUser(0,1); _h_amp_3900->Draw("col");
_c_amp->cd(12); gPad->SetLogz(true); TH2F * _h_amp_3950 = plot_amp_vs_ch( _file_3950, "3950"); _h_amp_3950->GetYaxis()->SetTitleOffset(1.4); _h_amp_3950->GetZaxis()->SetRangeUser(0,1); _h_amp_3950->Draw("colz");
_c_amp->cd(13); gPad->SetLogz(true); TH2F * _h_amp_3975 = plot_amp_vs_ch( _file_3975, "3975"); _h_amp_3975->GetYaxis()->SetTitleOffset(1.4); _h_amp_3975->GetZaxis()->SetRangeUser(0,1); _h_amp_3975->Draw("col");
_c_amp->cd(14); gPad->SetLogz(true); TH2F * _h_amp_3980 = plot_amp_vs_ch( _file_3980, "3980"); _h_amp_3980->GetYaxis()->SetTitleOffset(1.4); _h_amp_3980->GetZaxis()->SetRangeUser(0,1); _h_amp_3980->Draw("col");
_c_amp->cd(15); gPad->SetLogz(true); TH2F * _h_amp_3985 = plot_amp_vs_ch( _file_3985, "3985"); _h_amp_3985->GetYaxis()->SetTitleOffset(1.4); _h_amp_3985->GetZaxis()->SetRangeUser(0,1); _h_amp_3985->Draw("col");
_c_amp->cd(16); gPad->SetLogz(true); TH2F * _h_amp_3990 = plot_amp_vs_ch( _file_3990, "3990"); _h_amp_3990->GetYaxis()->SetTitleOffset(1.4); _h_amp_3990->GetZaxis()->SetRangeUser(0,1); _h_amp_3990->Draw("colz");

TCanvas * _c_charge  = new TCanvas();
_c_charge->Divide(4,4);

_c_charge->cd(1 ); gPad->SetLogy(true); 
	TH1F * _h_charge_500_0 = plot_charge_vs_ch( _file_500 , "500", 0 ); _h_charge_500_0 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_500_0 ->Draw("");
	TH1F * _h_charge_500_1 = plot_charge_vs_ch( _file_500 , "500", 1 ); _h_charge_500_1 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_500_1 ->Draw("same");
	TH1F * _h_charge_500_2 = plot_charge_vs_ch( _file_500 , "500", 2 ); _h_charge_500_2 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_500_2 ->Draw("same");
	TH1F * _h_charge_500_3 = plot_charge_vs_ch( _file_500 , "500", 3 ); _h_charge_500_3 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_500_3 ->Draw("same");
	TH1F * _h_charge_500_4 = plot_charge_vs_ch( _file_500 , "500", 4 ); _h_charge_500_4 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_500_4 ->Draw("same");	

_c_charge->cd(2 ); gPad->SetLogy(true); 
	TH1F * _h_charge_1000_0 = plot_charge_vs_ch( _file_1000 , "1000", 0 ); _h_charge_1000_0 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1000_0 ->Draw("");
	TH1F * _h_charge_1000_1 = plot_charge_vs_ch( _file_1000 , "1000", 1 ); _h_charge_1000_1 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1000_1 ->Draw("same");
	TH1F * _h_charge_1000_2 = plot_charge_vs_ch( _file_1000 , "1000", 2 ); _h_charge_1000_2 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1000_2 ->Draw("same");
	TH1F * _h_charge_1000_3 = plot_charge_vs_ch( _file_1000 , "1000", 3 ); _h_charge_1000_3 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1000_3 ->Draw("same");
	TH1F * _h_charge_1000_4 = plot_charge_vs_ch( _file_1000 , "1000", 4 ); _h_charge_1000_4 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1000_4 ->Draw("same");	

_c_charge->cd(3 ); gPad->SetLogy(true); 
	TH1F * _h_charge_1500_0 = plot_charge_vs_ch( _file_1500 , "1500", 0 ); _h_charge_1500_0 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1500_0 ->Draw("");
	TH1F * _h_charge_1500_1 = plot_charge_vs_ch( _file_1500 , "1500", 1 ); _h_charge_1500_1 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1500_1 ->Draw("same");
	TH1F * _h_charge_1500_2 = plot_charge_vs_ch( _file_1500 , "1500", 2 ); _h_charge_1500_2 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1500_2 ->Draw("same");
	TH1F * _h_charge_1500_3 = plot_charge_vs_ch( _file_1500 , "1500", 3 ); _h_charge_1500_3 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1500_3 ->Draw("same");
	TH1F * _h_charge_1500_4 = plot_charge_vs_ch( _file_1500 , "1500", 4 ); _h_charge_1500_4 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_1500_4 ->Draw("same");	

_c_charge->cd(4 ); gPad->SetLogy(true); 
	TH1F * _h_charge_2000_0 = plot_charge_vs_ch( _file_2000 , "2000", 0 ); _h_charge_2000_0 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_2000_0 ->Draw("");
	TH1F * _h_charge_2000_1 = plot_charge_vs_ch( _file_2000 , "2000", 1 ); _h_charge_2000_1 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_2000_1 ->Draw("same");
	TH1F * _h_charge_2000_2 = plot_charge_vs_ch( _file_2000 , "2000", 2 ); _h_charge_2000_2 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_2000_2 ->Draw("same");
	TH1F * _h_charge_2000_3 = plot_charge_vs_ch( _file_2000 , "2000", 3 ); _h_charge_2000_3 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_2000_3 ->Draw("same");
	TH1F * _h_charge_2000_4 = plot_charge_vs_ch( _file_2000 , "2000", 4 ); _h_charge_2000_4 ->GetYaxis()->SetTitleOffset(1.4); _h_charge_2000_4 ->Draw("same");	

//_c_charge->cd(5 ); gPad->SetLogy(true); 
//	TH1F * _h_charge_2500 = plot_charge_vs_ch( _file_2500, "2500"); _h_charge_2500->GetYaxis()->SetTitleOffset(1.4); _h_charge_2500->Draw("col");
//_c_charge->cd(6 ); gPad->SetLogy(true); 
//	TH1F * _h_charge_3000 = plot_charge_vs_ch( _file_3000, "3000"); _h_charge_3000->GetYaxis()->SetTitleOffset(1.4); _h_charge_3000->Draw("col");
//_c_charge->cd(7 ); gPad->SetLogy(true); 
//	TH1F * _h_charge_3500 = plot_charge_vs_ch( _file_3500, "3500"); _h_charge_3500->GetYaxis()->SetTitleOffset(1.4); _h_charge_3500->Draw("col");
//_c_charge->cd(8 ); gPad->SetLogy(true); 
//	TH1F * _h_charge_3600 = plot_charge_vs_ch( _file_3600, "3600"); _h_charge_3600->GetYaxis()->SetTitleOffset(1.4); _h_charge_3600->Draw("colz");
//_c_charge->cd(9 ); gPad->SetLogy(true); 
//	TH1F * _h_charge_3700 = plot_charge_vs_ch( _file_3700, "3700"); _h_charge_3700->GetYaxis()->SetTitleOffset(1.4); _h_charge_3700->Draw("col");
//_c_charge->cd(10); gPad->SetLogy(true); 
//	TH1F * _h_charge_3800 = plot_charge_vs_ch( _file_3800, "3800"); _h_charge_3800->GetYaxis()->SetTitleOffset(1.4); _h_charge_3800->Draw("col");
//_c_charge->cd(11); gPad->SetLogy(true); 
//	TH1F * _h_charge_3900 = plot_charge_vs_ch( _file_3900, "3900"); _h_charge_3900->GetYaxis()->SetTitleOffset(1.4); _h_charge_3900->Draw("col");
//_c_charge->cd(12); gPad->SetLogy(true); 
//	TH1F * _h_charge_3950 = plot_charge_vs_ch( _file_3950, "3950"); _h_charge_3950->GetYaxis()->SetTitleOffset(1.4); _h_charge_3950->Draw("colz");
//_c_charge->cd(13); gPad->SetLogy(true); 
//	TH1F * _h_charge_3975 = plot_charge_vs_ch( _file_3975, "3975"); _h_charge_3975->GetYaxis()->SetTitleOffset(1.4); _h_charge_3975->Draw("col");
//_c_charge->cd(14); gPad->SetLogy(true); 
//	TH1F * _h_charge_3980 = plot_charge_vs_ch( _file_3980, "3980"); _h_charge_3980->GetYaxis()->SetTitleOffset(1.4); _h_charge_3980->Draw("col");
//_c_charge->cd(15); gPad->SetLogy(true); 
//	TH1F * _h_charge_3985 = plot_charge_vs_ch( _file_3985, "3985"); _h_charge_3985->GetYaxis()->SetTitleOffset(1.4); _h_charge_3985->Draw("col");
//_c_charge->cd(16); gPad->SetLogy(true); 
//	TH1F * _h_charge_3990 = plot_charge_vs_ch( _file_3990, "3990"); _h_charge_3990->GetYaxis()->SetTitleOffset(1.4); _h_charge_3990->Draw("colz");



TGraph * g = new TGraph(16);
_file_500 ->cd(); g->SetPoint( 0  , 500  , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_1000->cd(); g->SetPoint( 1  , 1000 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_1500->cd(); g->SetPoint( 2  , 1500 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_2000->cd(); g->SetPoint( 3  , 2000 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_2500->cd(); g->SetPoint( 4  , 2500 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3000->cd(); g->SetPoint( 5  , 3000 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3500->cd(); g->SetPoint( 6  , 3500 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3600->cd(); g->SetPoint( 7  , 3600 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3700->cd(); g->SetPoint( 8  , 3700 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3800->cd(); g->SetPoint( 9  , 3800 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3900->cd(); g->SetPoint( 10 , 3900 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3950->cd(); g->SetPoint( 11 , 3950 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3975->cd(); g->SetPoint( 12 , 3975 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3980->cd(); g->SetPoint( 13 , 3980 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3985->cd(); g->SetPoint( 14 , 3985 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 
_file_3990->cd(); g->SetPoint( 15 , 3990 , reco_data->GetEntriesFast()/float(reco_data->GetMaximum("_time_stamp") - reco_data->GetMinimum("_time_stamp")) ); 

TCanvas * c1 = new TCanvas();
g->Draw("ALP*");
g->SetTitle("Trigger rate vs threshold; Threshold [ADC]; Rate [Hz]");
g->GetYaxis()->SetRangeUser(1e-1,5e3);
g->SetMarkerStyle(20);
c1->SetLogy(true);
c1->Update();


TGraph * g_nsamples = new TGraph(16);
_file_500 ->cd(); g_nsamples->SetPoint( 0  , 500  , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_1000->cd(); g_nsamples->SetPoint( 1  , 1000 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_1500->cd(); g_nsamples->SetPoint( 2  , 1500 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_2000->cd(); g_nsamples->SetPoint( 3  , 2000 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_2500->cd(); g_nsamples->SetPoint( 4  , 2500 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3000->cd(); g_nsamples->SetPoint( 5  , 3000 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3500->cd(); g_nsamples->SetPoint( 6  , 3500 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3600->cd(); g_nsamples->SetPoint( 7  , 3600 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3700->cd(); g_nsamples->SetPoint( 8  , 3700 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3800->cd(); g_nsamples->SetPoint( 9  , 3800 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3900->cd(); g_nsamples->SetPoint( 10 , 3900 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3950->cd(); g_nsamples->SetPoint( 11 , 3950 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3975->cd(); g_nsamples->SetPoint( 12 , 3975 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3980->cd(); g_nsamples->SetPoint( 13 , 3980 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3985->cd(); g_nsamples->SetPoint( 14 , 3985 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
_file_3990->cd(); g_nsamples->SetPoint( 15 , 3990 , (reco_data->GetEntries("_nsamples!=1000")-1)/(float(reco_data->GetEntries()-1)) ); 
//
//TCanvas * c_nsamples = new TCanvas();
////c_nsamples->SetLogy(true);
//c_nsamples->Update();

TGraph * g_saturation = new TGraph(16);

TString tmp_sel = "_reco_min_adc[0]==0||_reco_min_adc[1]==0||_reco_min_adc[2]==0||_reco_min_adc[3]==0||_reco_min_adc[4]==0";

_file_500 ->cd(); g_saturation->SetPoint( 0  , 500  , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_1000->cd(); g_saturation->SetPoint( 1  , 1000 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_1500->cd(); g_saturation->SetPoint( 2  , 1500 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_2000->cd(); g_saturation->SetPoint( 3  , 2000 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_2500->cd(); g_saturation->SetPoint( 4  , 2500 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3000->cd(); g_saturation->SetPoint( 5  , 3000 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3500->cd(); g_saturation->SetPoint( 6  , 3500 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3600->cd(); g_saturation->SetPoint( 7  , 3600 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3700->cd(); g_saturation->SetPoint( 8  , 3700 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3800->cd(); g_saturation->SetPoint( 9  , 3800 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3900->cd(); g_saturation->SetPoint( 10 , 3900 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3950->cd(); g_saturation->SetPoint( 11 , 3950 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3975->cd(); g_saturation->SetPoint( 12 , 3975 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3980->cd(); g_saturation->SetPoint( 13 , 3980 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3985->cd(); g_saturation->SetPoint( 14 , 3985 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 
_file_3990->cd(); g_saturation->SetPoint( 15 , 3990 , reco_data->GetEntries(tmp_sel)/(float(reco_data->GetEntries())) ); 

//g_saturation->Draw("ALP*");
//g_saturation->SetTitle("Saturated waveforms; Threshold [ADC]; Saturated / Total");
//g_saturation->GetYaxis()->SetRangeUser(-.2,1.2);
//g_saturation->SetMarkerStyle(20);
//c_nsamples->SetLogy(true);

//g_nsamples->Draw("ALP*");
//g_nsamples->SetTitle("Overlapping trigger; Threshold [ADC]; Overlapped / Total");
//g_nsamples->GetYaxis()->SetRangeUser(-.02,.6);
//g_nsamples->SetMarkerStyle(20);

TCanvas * c_multig= new TCanvas();

TMultiGraph *g_multig = new TMultiGraph();
g_multig->SetTitle("; Threshold [ADC]; Fraction of total events");
g_multig->Add(g_saturation,"LP");
g_multig->Add(g_nsamples,"LP");
g_multig->Draw("A");

g_saturation->SetTitle("Saturated waveforms");
g_saturation->SetMarkerStyle(20);
g_saturation->SetMarkerColor(2);
g_saturation->SetFillColor(0);

g_nsamples->SetTitle("Overlapping trigger");
g_nsamples->SetMarkerStyle(20);
g_nsamples->SetMarkerColor(4);
g_nsamples->SetFillColor(0);


c_multig->BuildLegend();
c_multig->Update();


}

TH1F * plot_amp_vs_th(TFile * _file, TString label){
	
_file->cd();

TString tmp_name; tmp_name.Form("h_%s", label.Data());

TH1F * h = new TH1F(tmp_name,tmp_name,128,0,4096);

reco_data->Draw(TString::Format("_reco_min_adc[0]>>%s", tmp_name.Data()),"", "goff");		
	
h->Scale(1/float(reco_data->GetEntries()));
		
return h;	
	
}

TH2F * plot_amp_vs_ch(TFile* _file, TString label){
	
	_file->cd();

	TString tmp_name; tmp_name.Form("h_amp_%s", label.Data());

	TString tmp_title; tmp_title.Form(" Peak amplitude vs channel (%s ADC);Channel;Peak amplitude [ADC]; Num of entries ", label.Data());
	
	TH2F * h2 = new TH2F(tmp_name,tmp_title, 5, 0, 5, 128, 0, 4092);
	
	reco_data->Draw( TString::Format("_reco_min_adc[0]:0>>%s"  , tmp_name.Data() ) , "" , "goff" );
	reco_data->Draw( TString::Format("_reco_min_adc[1]:1>>+%s" , tmp_name.Data() ) , "" , "goff" );
	reco_data->Draw( TString::Format("_reco_min_adc[2]:2>>+%s" , tmp_name.Data() ) , "" , "goff" );
	reco_data->Draw( TString::Format("_reco_min_adc[3]:3>>+%s" , tmp_name.Data() ) , "" , "goff" );
	reco_data->Draw( TString::Format("_reco_min_adc[4]:4>>+%s" , tmp_name.Data() ) , "" , "goff" );
	
	h2->Scale(1/float(reco_data->GetEntries()));
	
	return h2;
	
}

TH1F * plot_charge_vs_ch(TFile* _file, TString label, int ch = 0){
	
	_file->cd();

	TString tmp_name; tmp_name.Form("h_charge_%s", label.Data());

	TString tmp_title; tmp_title.Form(" Charge vs channel (%s ADC);Channel; Charge [ADC*ns]; Num of entries ", label.Data());

	TH1F * h1 = new TH1F(tmp_name,tmp_title, 500, 1,1);

	reco_data->Draw( TString::Format("Sum$((_waveform_%d-_reco_pedestals[%d])*_time_sample)>>%s", ch, ch, tmp_name.Data() ) , "" , "goff" );

	h1->Scale(1/float(reco_data->GetEntries()));
	
	return h1;
	
}
