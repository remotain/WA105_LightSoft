double func(double *x, double *par, int index = 2) {

	double TT  = par[0]; // PMT Transit Time
	double TTS = par[1]; // PMT Transit Time Spread (Jitter)
	
	double A   = par[index]; // Normalisation
	double tau = par[index+1]; // Time constant 

	double t = x[0]; // Variable

	double c = A / TMath::Sqrt( TMath::TwoPi() * TTS );
		
	double t1 = (TTS *TTS) / (2 * tau * tau);
		
	double t2 = t - TT; 
	t2 /= tau;		
		
	double t3 = (TTS * TTS) - (tau * (t-TT));
	t3 /= (TMath::Sqrt(2) * TTS * tau);
		
	return c * TMath::Exp( t1 - t2 ) * ( 1 - TMath::Erf(t3) );

}

double scint_time_1(double *x, double *par){
	return func(x, par, 2);
}

double scint_time_2(double *x, double *par){	
	return func(x, par, 2) + func(x, par, 4);
}

double scint_time_3(double *x, double *par){	
	return func(x, par, 2) + func(x, par, 4) + func(x, par, 6);
}

void dress_plot(ROOT::Fit::FitResult _res, TH1 * _h,  double _r_min, double _r_max){
	
	const int _mode;
	
	TF1 * _afit = new TF1("_afit", scint_time_3, _r_min, _r_max, 8);	
	_afit->SetParName(0, "TT");   	  _afit->SetParameter( 0, _res.Parameter(0));
	_afit->SetParName(1, "TTS");	  _afit->SetParameter( 1, _res.Parameter(1));
	_afit->SetParName(2, "A");	      _afit->SetParameter( 2, _res.Parameter(2));
	_afit->SetParName(3, "#tau_{1}"); _afit->SetParameter( 3, _res.Parameter(3));
	_afit->SetParName(4, "B");	      _afit->SetParameter( 4, _res.Parameter(4));
	_afit->SetParName(5, "#tau_{2}"); _afit->SetParameter( 5, _res.Parameter(5));
	_afit->SetParName(6, "C");	      _afit->SetParameter( 6, _res.Parameter(6));
	_afit->SetParName(7, "#tau_{3}"); _afit->SetParameter( 7, _res.Parameter(7));
	
	TF1 * _afit_1 = new TF1("_afit_1", scint_time_1, _r_min, _r_max, 4);
	_afit_1->SetParName(0, "TT");   	_afit_1->SetParameter( 0, _res.Parameter(0));
	_afit_1->SetParName(1, "TTS");	    _afit_1->SetParameter( 1, _res.Parameter(1));
	_afit_1->SetParName(2, "A");	    _afit_1->SetParameter( 2, _res.Parameter(2));
	_afit_1->SetParName(3, "#tau_{1}"); _afit_1->SetParameter( 3, _res.Parameter(3));
	_afit_1->SetLineColor(kGray+3);
	_afit_1->SetLineStyle(7);

	TF1 * _afit_2 = new TF1("_afit_2", scint_time_1, _r_min, _r_max, 4);
	_afit_2->SetParName(0, "TT");   	_afit_2->SetParameter( 0, _res.Parameter(0));
	_afit_2->SetParName(1, "TTS");	    _afit_2->SetParameter( 1, _res.Parameter(1));
	_afit_2->SetParName(2, "A");	    _afit_2->SetParameter( 2, _res.Parameter(4));
	_afit_2->SetParName(3, "#tau_{1}"); _afit_2->SetParameter( 3, _res.Parameter(5));
	_afit_2->SetLineColor(kGray+3);
	_afit_2->SetLineStyle(7);

	TF1 * _afit_3 = new TF1("_afit_3", scint_time_1, _r_min, _r_max, 4);
	_afit_3->SetParName(0, "TT");   	_afit_3->SetParameter( 0, _res.Parameter(0));
	_afit_3->SetParName(1, "TTS");	    _afit_3->SetParameter( 1, _res.Parameter(1));
	_afit_3->SetParName(2, "A");	    _afit_3->SetParameter( 2, _res.Parameter(6));
	_afit_3->SetParName(3, "#tau_{1}"); _afit_3->SetParameter( 3, _res.Parameter(7));
	_afit_3->SetLineColor(kGray+3);
	_afit_3->SetLineStyle(7);

	_afit_1->SetNpx(500);
	_afit_2->SetNpx(500);
	_afit_3->SetNpx(500);
	_afit->SetNpx(500);

	TCanvas * _c = new TCanvas();

	_c->SetLogy(true);
	
	_h->SetStats(false); 

	//_h->Rebin(4);
	
	_h->Draw();
		
	_afit_1->Draw("same");
	_afit_2->Draw("same");
	_afit_3->Draw("same");
		
	_afit->Draw("same");

	TPaveText *pt = new TPaveText(0.63,0.42,0.88,0.87, "NDCT");
	pt->SetTextAlign(11);
	pt->SetTextFont(42);
	pt->SetTextSize(0.035);
	pt->SetFillColor(kWhite);
	pt->AddText( TString::Format("%s : %.2f #pm %.2f ns"       , "t_{0}"      , _res.Parameter(0), _res.ParError(0)));
	pt->AddText( TString::Format("%s : %.2f #pm %.2f ns"       , "#sigma"     , _res.Parameter(1), _res.ParError(1)));
	pt->AddText( TString::Format("%s : %.0f #pm %.0f"          , "A"	      , _res.Parameter(2), _res.ParError(2)));
	pt->AddText( TString::Format("%s : %.2f #pm %.2f ns"       , "#tau_{1}"   , _res.Parameter(3), _res.ParError(3)));
	pt->AddText( TString::Format("%s : %.1f #pm %.1f"          , "B"          , _res.Parameter(4), _res.ParError(4)));
	pt->AddText( TString::Format("%s : %.0f #pm %.0f ns"       , "#tau_{2}"   , _res.Parameter(5), _res.ParError(5)));
	pt->AddText( TString::Format("%s : %.0f #pm %.0f"          , "C"          , _res.Parameter(6), _res.ParError(6)));
	pt->AddText( TString::Format("%s : %.0f #pm %.0f ns"       , "#tau_{3}"   , _res.Parameter(7), _res.ParError(7)));
	pt->AddText( TString::Format("%s : %.0f/%i"                , "#chi^2/dof" , _res.Chi2()      , _res.Ndf()));			
				
	pt->Draw();

	_c->Print("scint_time.pdf");
	
	double int_1 = _afit_1->Integral(_r_min, _r_max);
	double int_2 = _afit_2->Integral(_r_min, _r_max);
	double int_3 = _afit_3->Integral(_r_min, _r_max);
	
	std::cout << "Integral 1: " << int_1 << std::endl;
	std::cout << "Integral 2: " << int_2 << std::endl;
	std::cout << "Integral 3: " << int_3 << std::endl;
	
	
}

void fit_waveform_data(){	
	
	TFile * _file = new TFile("$WLS_PATH/test00000211.root", "READ");
	
	//TH1F * _h = (TH1F*) _file->Get("overall_waveform_ch4");
	
	TProfile * _profile = (TProfile*) _file->Get("overall_waveform_ch4");
	
	TH1D * _h = _profile->ProjectionX("_h","E");
	
	_h->Scale(-1); // Reverse the waveform

	_h->SetTitle("Scintillation time in GAr (1000 mBar, 215 K)");

	_h->GetYaxis()->SetTitle("Arbitrary units");

	_h->GetXaxis()->SetRangeUser(400, 3995);

	_h->GetYaxis()->SetRangeUser(1, 100);

	///
	// Fit the pedestal
	//
	
	TF1 * _func_pedestal = new TF1("pedestal", "pol0", 0 ,4000);
		
	TFitResultPtr r = _h->Fit(_func_pedestal, "F0S","",0, 400);			
		
	_h->Add(_func_pedestal, -1 );
		
	//
	// Fit function and range
	// 
		
	double _r_min = 506; // ns
	double _r_max = 3995; // ns
		
	TF1 * _func = new TF1("scint_time", scint_time_3, _r_min, _r_max, 8);		
		
	// Fitting gears
	
	ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2","Migrad");
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(1000000);
	ROOT::Math::MinimizerOptions::SetDefaultTolerance(0.01);
	ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(2);
	
	ROOT::Fit::DataOptions opt;
	opt.fUseRange = true;
	ROOT::Fit::DataRange range(_r_min, _r_max);
	ROOT::Fit::BinData data(opt, range);
	ROOT::Fit::FillData(data, _h);	
	
	ROOT::Math::WrappedMultiTF1 _fit_func( *_func, 1 );
    
    ROOT::Fit::Fitter fitter;
    
    fitter.SetFunction( _fit_func, false); 
		
	fitter.Config().ParSettings(0).Set("t_{0}"    ,  540 , 0.1);
	fitter.Config().ParSettings(1).Set("#sigma"   ,   11 , 0.1);
	fitter.Config().ParSettings(2).Set("A"	      , 1600 , 0.1);
	fitter.Config().ParSettings(3).Set("#tau_{1}" ,    6 , 0.1); fitter.Config().ParSettings(3).Fix();
	fitter.Config().ParSettings(4).Set("B"        ,  100 , 0.1);
	fitter.Config().ParSettings(5).Set("#tau_{2}" ,   57 , 0.1);
	fitter.Config().ParSettings(6).Set("C"        ,   19 , 0.1);
	fitter.Config().ParSettings(7).Set("#tau_{3}" , 3500 , 0.1);
	
	fitter.LikelihoodFit(data);				
			
	ROOT::Fit::FitResult _res = fitter.Result();	
	
	dress_plot(_res, _h, _r_min, _r_max);
		
}

void fit_waveform_mc_1(){	
	
	TFile * _file = new TFile("$WLS_DATA/fout.root", "READ");
	
	TH1F * _h = (TH1F*) _file->Get("hScintTime");
		
	//_h->Scale(-1); // Reverse the waveform

	_h->SetTitle("Simulated scintillation time");

	_h->GetYaxis()->SetTitle("Arbitrary units");

	_h->GetXaxis()->SetRangeUser(0, 4000);

	_h->GetYaxis()->SetRangeUser(1, 1e4);

	_h->Sumw2();

	/////
	//// Fit the pedestal
	////
	//
	//TF1 * _func_pedestal = new TF1("pedestal", "pol0", 0 ,4000);
	//	
	//TFitResultPtr r = _h->Fit(_func_pedestal, "F0S","",0, 400);			
	//	
	//_h->Add(_func_pedestal, -1 );
		
	//
	// Fit function and range
	// 
		
	double _r_min = 50; // ns
	double _r_max = 4000; // ns
		
	TF1 * _func = new TF1("scint_time", scint_time_3, _r_min, _r_max, 8);		
		
	// Fitting gears
	
	ROOT::Math::MinimizerOptions::SetDefaultMinimizer("Minuit2","Migrad");
	ROOT::Math::MinimizerOptions::SetDefaultMaxFunctionCalls(1000000);
	ROOT::Math::MinimizerOptions::SetDefaultTolerance(0.01);
	ROOT::Math::MinimizerOptions::SetDefaultPrintLevel(2);
	
	ROOT::Fit::DataOptions opt;
	opt.fUseRange = true;
	ROOT::Fit::DataRange range(_r_min, _r_max);
	ROOT::Fit::BinData data(opt, range);
	ROOT::Fit::FillData(data, _h);	
	
	ROOT::Math::WrappedMultiTF1 _fit_func( *_func, 1 );
    
    ROOT::Fit::Fitter fitter;
    
    fitter.SetFunction( _fit_func, false); 
		
	fitter.Config().ParSettings(0).Set("t_{0}"    ,  100 , 0.1); //fitter.Config().ParSettings(0).Fix();
	fitter.Config().ParSettings(1).Set("#sigma"   ,   10 , 0.1); //fitter.Config().ParSettings(1).Fix();
	fitter.Config().ParSettings(2).Set("A"	      , 10000 , 0.1); //
	fitter.Config().ParSettings(3).Set("#tau_{1}" ,    10 , 0.1); //fitter.Config().ParSettings(3).Fix();
	fitter.Config().ParSettings(4).Set("B"        ,  1000 , 0.1); ////fitter.Config().ParSettings(4).Fix();
	fitter.Config().ParSettings(5).Set("#tau_{2}" ,   100 , 0.1); //fitter.Config().ParSettings(5).Fix();
	fitter.Config().ParSettings(6).Set("C"        ,   10 , 0.1);  //
	fitter.Config().ParSettings(7).Set("#tau_{3}" , 1500 , 0.1); //fitter.Config().ParSettings(7).Fix();
	
	fitter.LikelihoodFit(data);				
			
	ROOT::Fit::FitResult _res = fitter.Result();	
	
	dress_plot(_res, _h, _r_min, _r_max);
		
}

void fit_waveform( int mode = 0){
	
	switch (mode) {
		case 0: // data
			fit_waveform_data(); break;
		case 1: // mc 1
			fit_waveform_mc_1(); break;
		default: 
			fit_waveform_data(); break;
	}
	
	
}