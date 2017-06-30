trigger_studies(){

gStyle->SetOptStat(0);

TFile *_file0 = TFile::Open("$WLS_DATA/recoed00000772.root");

TH2F * h1 = new TH2F("h1","Peak position vs channel;Channel;Peak position [ns]; Num of entries", 5, 0, 5, 250, 0, 1000);

reco_data->Draw("_reco_min_adc_time[0]:0>>h1"  , "" , "goff" );
reco_data->Draw("_reco_min_adc_time[1]:1>>+h1" , "" , "goff" );
reco_data->Draw("_reco_min_adc_time[2]:2>>+h1" , "" , "goff" );
reco_data->Draw("_reco_min_adc_time[3]:3>>+h1" , "" , "goff" );
reco_data->Draw("_reco_min_adc_time[4]:4>>+h1" , "" , "goff" );

TCanvas *c1 = new TCanvas();
h1->Draw("colz");


TH2F * h2 = new TH2F("h2","Peak amplitude vs channel;Channel;Peak amplitude [ADC]; Event fraction", 5, 0, 5, 128, 0, 4092);

reco_data->Draw("_reco_min_adc[0]:0>>h2"  , "_reco_min_adc[0]>=0" , "goff" );
reco_data->Draw("_reco_min_adc[1]:1>>+h2" , "_reco_min_adc[1]>=0" , "goff" );
reco_data->Draw("_reco_min_adc[2]:2>>+h2" , "_reco_min_adc[2]>=0" , "goff" );
reco_data->Draw("_reco_min_adc[3]:3>>+h2" , "_reco_min_adc[3]>=0" , "goff" );
reco_data->Draw("_reco_min_adc[4]:4>>+h2" , "_reco_min_adc[4]>=0" , "goff" );

h2->Scale(1/float(reco_data->GetEntries()));
h2->GetYaxis()->SetTitleOffset(1.4); 
h2->GetZaxis()->SetRangeUser(0,1);

//int n_point = 8;
//TString tmp_sel = "_reco_min_adc[0]>=%d&&_reco_min_adc[1]>=%d&&_reco_min_adc[2]>=%d&&_reco_min_adc[3]>=%d&&_reco_min_adc[4]>=%d";
//TGraph * g0 = new TGraph(n_point);
//for( int i = 0; i < n_point; i++ ){
//	
//	int th = i * 500;
//	
//	double f = reco_data->GetEntries( TString::Format(tmp_sel.Data(), th, th, th, th, th) ) / float(reco_data->GetEntries());
//	
//	g0->SetPoint(i, th,  f);
//	
//}
//
//TCanvas *cg1 = new TCanvas();
//g0->SetTitle("Fraction of events above threshold; Threshold [ADC]; Event Fraction");
//g0->SetMarkerStyle(20);
//g0->Draw("ALP");


//TCanvas *c2 = new TCanvas();
//h2->Draw("colz");
//
//TCanvas *c3 = new TCanvas();
//c3->Divide(5,5);
//
//int n_ch = 5;
//
//for( int i=0; i < n_ch; i++ ){
//
//	for( int j=0; j < n_ch; j++ ){
//	
//		c3->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc[%d]:_reco_min_adc[%d]>>_amp_corr_%d_%d(128,0,4092, 128,0,4092)",i,j,i,j)  , "" , "colz" );
//		c3->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc[%d]:_reco_min_adc[%d]>>_amp_corr_%d_%d(128,0,4092, 128,0,4092)",i,j,i,j)  , "" , "colz" );
//		c3->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc[%d]:_reco_min_adc[%d]>>_amp_corr_%d_%d(128,0,4092, 128,0,4092)",i,j,i,j)  , "" , "colz" );
//		c3->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc[%d]:_reco_min_adc[%d]>>_amp_corr_%d_%d(128,0,4092, 128,0,4092)",i,j,i,j)  , "" , "colz" );
//		c3->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc[%d]:_reco_min_adc[%d]>>_amp_corr_%d_%d(128,0,4092, 128,0,4092)",i,j,i,j)  , "" , "colz" );
//		
//	}
//	
//}

//TCanvas *c4 = new TCanvas();
//c4->Divide(5,5);
//
//gStyle->SetOptStat(1);
//
//int n_ch = 5;
//
//for( int i=0; i < n_ch; i++ ){
//
//	for( int j=0; j < n_ch; j++ ){
//	
//		c4->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc_time[%d]:_reco_min_adc_time[%d]>>_time_corr_%d_%d(100, 250, 650, 100, 250, 650)",i,j,i,j)  , "" , "colz" );
//		c4->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc_time[%d]:_reco_min_adc_time[%d]>>_time_corr_%d_%d(100, 250, 650, 100, 250, 650)",i,j,i,j)  , "" , "colz" );
//		c4->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc_time[%d]:_reco_min_adc_time[%d]>>_time_corr_%d_%d(100, 250, 650, 100, 250, 650)",i,j,i,j)  , "" , "colz" );
//		c4->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc_time[%d]:_reco_min_adc_time[%d]>>_time_corr_%d_%d(100, 250, 650, 100, 250, 650)",i,j,i,j)  , "" , "colz" );
//		c4->cd( n_ch * i + (j+1) ); reco_data->Draw(TString::Format("_reco_min_adc_time[%d]:_reco_min_adc_time[%d]>>_time_corr_%d_%d(100, 250, 650, 100, 250, 650)",i,j,i,j)  , "" , "colz" );
//		
//	}
//	
//}


TTree *_tree = (TTree*)_file0->Get("reco_data");
_tree->SetBranchStatus("*",0);

std::vector<int> * _reco_min_adc;
_tree->SetBranchStatus("_reco_min_adc",1);
_tree->SetBranchAddress("_reco_min_adc", &_reco_min_adc);
//
TH1F *hdt_500 = new TH1F("hdt_500",""  ,6,0,6);
TH1F *hdt_1000 = new TH1F("hdt_1000","",6,0,6);
TH1F *hdt_1500 = new TH1F("hdt_1500","",6,0,6);
TH1F *hdt_2000 = new TH1F("hdt_2000","",6,0,6);
TH1F *hdt_2500 = new TH1F("hdt_2500","",6,0,6);
TH1F *hdt_3000 = new TH1F("hdt_3000","",6,0,6);
TH1F *hdt_3500 = new TH1F("hdt_3500","",6,0,6);
TH1F *hdt_3600 = new TH1F("hdt_3600","",6,0,6);
TH1F *hdt_3700 = new TH1F("hdt_3700","",6,0,6);
TH1F *hdt_3800 = new TH1F("hdt_3800","",6,0,6);
TH1F *hdt_3900 = new TH1F("hdt_3900","",6,0,6);
TH1F *hdt_3990 = new TH1F("hdt_3990","",6,0,6);
//
//
UInt_t noe = _tree->GetEntries();

for (UInt_t i = 0; i < noe; ++i) {

	_tree->GetEntry(i);

	int counter_500  = 0;
	int counter_1000 = 0;
	int counter_1500 = 0;
	int counter_2000 = 0;
	int counter_2500 = 0;
	int counter_3000 = 0;
	int counter_3500 = 0;
	int counter_3600 = 0;
	int counter_3700 = 0;
	int counter_3800 = 0;
	int counter_3900 = 0;
	int counter_3990 = 0;
	
	
	for(int j =0; j<5; j++){
		
		//if( _reco_min_adc->at(j) != -1 ){ 
		
		int peak =  _reco_min_adc->at(j);
		
		if( peak == -1 ) peak = 4000;
		
		if( peak <= 500  ) counter_500++;
		if( peak <= 1000 ) counter_1000++;
		if( peak <= 1500 ) counter_1500++;
		if( peak <= 2000 ) counter_2000++;
		if( peak <= 2500 ) counter_2500++;
		if( peak <= 3000 ) counter_3000++;
		if( peak <= 3500 ) counter_3500++;
		if( peak <= 3600 ) counter_3600++;
		if( peak <= 3700 ) counter_3700++;
		if( peak <= 3800 ) counter_3800++;
		if( peak <= 3900 ) counter_3900++;
		if( peak <= 3990 ) counter_3990++;
		
			//}
	
	}

	hdt_500  -> Fill(counter_500 );
	hdt_1000 -> Fill(counter_1000 );
	hdt_1500 -> Fill(counter_1500 );
	hdt_2000 -> Fill(counter_2000 );
	hdt_2500 -> Fill(counter_2500 );
	hdt_3000 -> Fill(counter_3000 );
	hdt_3500 -> Fill(counter_3500 );
	hdt_3600 -> Fill(counter_3600 );
	hdt_3700 -> Fill(counter_3700 );
	hdt_3800 -> Fill(counter_3800 );
	hdt_3900 -> Fill(counter_3900 );
	hdt_3990 -> Fill(counter_3990 );


}

hdt_500  -> Scale(1/float(noe)); hdt_500  -> SetLineColor( kRed);   hdt_500  -> Draw(      ); hdt_500 -> GetYaxis()->SetRangeUser(0,1.1);
hdt_1000 -> Scale(1/float(noe)); hdt_1000 -> SetLineStyle(7);       hdt_1000 -> Draw("same"); 
hdt_1500 -> Scale(1/float(noe)); hdt_1500 -> SetLineStyle(7);       hdt_1500 -> Draw("same"); 
hdt_2000 -> Scale(1/float(noe)); hdt_2000 -> SetLineStyle(7);       hdt_2000 -> Draw("same"); 
hdt_2500 -> Scale(1/float(noe)); hdt_2500 -> SetLineStyle(7);       hdt_2500 -> Draw("same"); 
hdt_3000 -> Scale(1/float(noe)); hdt_3000 -> SetLineStyle(7);       hdt_3000 -> Draw("same"); 
hdt_3500 -> Scale(1/float(noe)); hdt_3500 -> SetLineStyle(7);       hdt_3500 -> Draw("same"); 
hdt_3600 -> Scale(1/float(noe)); hdt_3600 -> SetLineStyle(7);       hdt_3600 -> Draw("same"); 
hdt_3700 -> Scale(1/float(noe)); hdt_3700 -> SetLineStyle(7);       hdt_3700 -> Draw("same"); 
hdt_3800 -> Scale(1/float(noe)); hdt_3800 -> SetLineStyle(7);       hdt_3800 -> Draw("same"); 
hdt_3900 -> Scale(1/float(noe)); hdt_3900 -> SetLineStyle(7);       hdt_3900 -> Draw("same"); 
hdt_3990 -> Scale(1/float(noe)); hdt_3990 -> SetLineColor( kGreen); hdt_3990 -> Draw("same"); 


//TCanvas * cc = new TCanvas();
//hdt->Draw();
//cc->Update();




}