{
	
	TFile *_file0 = TFile::Open("$WLS_DATA/output00000772.root");
	TFile *_file1 = TFile::Open("$WLS_DATA/output00000XXX.root");
	TFile *_file2 = TFile::Open("$WLS_DATA/output00000XXX.root");
	TFile *_file3 = TFile::Open("$WLS_DATA/output00000XXX.root");

	
	TGraph *g0 = new TGraph(n);
	TGraph *g1 = new TGraph(n);
	TGraph *g2 = new TGraph(n);
	TGraph *g3 = new TGraph(n);	
	
	double t, r, r_match, r_reco, r_sat;
	
	trigger_rate(_file0, t, r, r_match, r_reco, r_sat);
	
	g0->SetPoint(0, t0, r0);
	g1->SetPoint(0, t0, r1);
	
	trigger_rate(_file1, t, r, r_match, r_reco, r_sat);

	g0->SetPoint(1, t, r0);	
	g1->SetPoint(1, t, r1);		
	
	TMultiGraph
	
	g0->Draw("ALP");
	g1->Draw("LPsame");
	
}

trigger_rate(TFile * _file, double &t0, double &val0, double &val1, double &val2, double &val3){

_file0->cd();

double t_min = midas_data->GetMinimum("TimeStamp");
double t_max = midas_data->GetMaximum("TimeStamp");
double t_l = t_max-t_min;

t0 = t_min;

TString w1 = Form("crt_daq_match");
TString w2 = Form("crt_daq_match&&crt_reco");
TString w3 = Form("crt_daq_match&&crt_reco&& Min$(adc_value_0)>0 &&  Min$(adc_value_1)>0 && Min$(adc_value_2)>0 &&  Min$(adc_value_3)>0 &&  Min$(adc_value_0)>4");

val0 = midas_data->GetEntries()/t_l;
val1 = midas_data->GetEntries(w1)/t_l;
val2 = midas_data->GetEntries(w2)/t_l;
val3 = midas_data->GetEntries(w3)/t_l;

}

