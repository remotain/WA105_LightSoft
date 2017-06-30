void fit_spe(){	

	TFile * _file = new TFile("$WLS_DATA/recoed00000211.root", "READ");
	
	//TH1F * _h = (TH1F*) _file->Get("charge_ch4");
	
	TTree * t = (TTree*) _file->Get("reco_data");
	
	t->Draw("_reco_charges[4]>>h(7000,-100,100)");
	
	TH1F * _h = gDirectory->Get("h");
	
	_h->SetTitle("SPE distribution Ch 4");

	_h->GetYaxis()->SetTitle("No.Entries");

	_h->GetXaxis()->SetTitle("Integrated ADC counts");

	double _r_min = -100;
	double _r_max = 50;

	_h->GetXaxis()->SetRangeUser(_r_min, _r_max);
		
	//TF1 * _func = new TF1("_func", "pol0+gaus(1)+gaus(4)+gaus(7)", _r_min, _r_max);
	TF1 * _func = new TF1("_func", "pol0+gaus(1)+gaus(4)", _r_min, _r_max);
	
    _func->SetParName(0, "Const"        ); _func->SetParameter(0, 1);
	_func->SetParName(1, "A_{Ped}"      ); _func->SetParameter(1, 200);
	_func->SetParName(2, "#LT Ped #GT"  ); _func->SetParameter(2, -1);
	_func->SetParName(3, "#sigma_{Ped}" ); _func->SetParameter(3, 10);	
	_func->SetParName(4, "A_{SPE}"      ); _func->SetParameter(4, 5);
	_func->SetParName(5, "#LT SPE #GT"  ); _func->SetParameter(5, -30);
	_func->SetParName(6, "#sigma_{SPE}" ); _func->SetParameter(6, 10);	
	//_func->SetParName(7, "A_{2PE}"); //_func->SetParameter(7, 1);
	//_func->SetParName(8, "#LT 2PE #GT"); //_func->SetParameter(8, -500);
	//_func->SetParName(9, "#sigma_{2PE}"); //_func->SetParameter(9, 400);	
		
	TFitResultPtr r = _h->Fit(_func, "LVEMR");
	
	TCanvas * _c = new TCanvas();
	
	_c->SetLogy(true);
	
	_h->Draw();
		
}