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

void dress_plot(ROOT::Fit::FitResult _res, TH1 * _h, TPad * _c, double _r_min, double _r_max){
	
	const int _mode;
	
	// Complete function
	if( _res.NPar() == 8 ){
	
		TF1 * _afit = new TF1("_afit", scint_time_3, _r_min, _r_max, 8);	
		_afit->SetParName(0, "TT");   	  _afit->SetParameter( 0, _res.Parameter(0));
		_afit->SetParName(1, "TTS");	  _afit->SetParameter( 1, _res.Parameter(1));
		_afit->SetParName(2, "a_{1}");	  _afit->SetParameter( 2, _res.Parameter(2));
		_afit->SetParName(3, "#tau_{1}"); _afit->SetParameter( 3, _res.Parameter(3));
		_afit->SetParName(4, "a_{2}");	  _afit->SetParameter( 4, _res.Parameter(4));
		_afit->SetParName(5, "#tau_{2}"); _afit->SetParameter( 5, _res.Parameter(5));
		_afit->SetParName(6, "a_{3}");	  _afit->SetParameter( 6, _res.Parameter(6));
		_afit->SetParName(7, "#tau_{3}"); _afit->SetParameter( 7, _res.Parameter(7));
		
		TF1 * _afit_1 = new TF1("_afit_1", scint_time_1, _r_min, _r_max, 4);
		_afit_1->SetParName(0, "TT");   	_afit_1->SetParameter( 0, _res.Parameter(0));
		_afit_1->SetParName(1, "TTS");	    _afit_1->SetParameter( 1, _res.Parameter(1));
		_afit_1->SetParName(2, "a_{1}");	_afit_1->SetParameter( 2, _res.Parameter(2));
		_afit_1->SetParName(3, "#tau_{1}"); _afit_1->SetParameter( 3, _res.Parameter(3));
		_afit_1->SetLineColor(kGray+3);
		_afit_1->SetLineStyle(7);
    	
		TF1 * _afit_2 = new TF1("_afit_2", scint_time_1, _r_min, _r_max, 4);
		_afit_2->SetParName(0, "TT");   	_afit_2->SetParameter( 0, _res.Parameter(0));
		_afit_2->SetParName(1, "TTS");	    _afit_2->SetParameter( 1, _res.Parameter(1));
		_afit_2->SetParName(2, "a_{2}");	_afit_2->SetParameter( 2, _res.Parameter(4));
		_afit_2->SetParName(3, "#tau_{2}"); _afit_2->SetParameter( 3, _res.Parameter(5));
		_afit_2->SetLineColor(kGray+3);
		_afit_2->SetLineStyle(7);
    	
		TF1 * _afit_3 = new TF1("_afit_3", scint_time_1, _r_min, _r_max, 4);
		_afit_3->SetParName(0, "TT");   	_afit_3->SetParameter( 0, _res.Parameter(0));
		_afit_3->SetParName(1, "TTS");	    _afit_3->SetParameter( 1, _res.Parameter(1));
		_afit_3->SetParName(2, "a_{3}");    _afit_3->SetParameter( 2, _res.Parameter(6));
		_afit_3->SetParName(3, "#tau_{3}"); _afit_3->SetParameter( 3, _res.Parameter(7));
		_afit_3->SetLineColor(kGray+3);
		_afit_3->SetLineStyle(7);
    	
		_afit_1->SetNpx(500);
		_afit_2->SetNpx(500);
		_afit_3->SetNpx(500);
		_afit->SetNpx(500);
	
	} 	if( _res.NPar() == 6 ){
	
		TF1 * _afit = new TF1("_afit", scint_time_2, _r_min, _r_max, 8);	
		_afit->SetParName(0, "TT");   	  _afit->SetParameter( 0, _res.Parameter(0));
		_afit->SetParName(1, "TTS");	  _afit->SetParameter( 1, _res.Parameter(1));
		_afit->SetParName(2, "a_{1}");	  _afit->SetParameter( 2, _res.Parameter(2));
		_afit->SetParName(3, "#tau_{1}"); _afit->SetParameter( 3, _res.Parameter(3));
		_afit->SetParName(4, "a_{3}");	  _afit->SetParameter( 4, _res.Parameter(4));
		_afit->SetParName(5, "#tau_{3}"); _afit->SetParameter( 5, _res.Parameter(5));
		
		TF1 * _afit_1 = new TF1("_afit_1", scint_time_1, _r_min, _r_max, 4);
		_afit_1->SetParName(0, "TT");   	_afit_1->SetParameter( 0, _res.Parameter(0));
		_afit_1->SetParName(1, "TTS");	    _afit_1->SetParameter( 1, _res.Parameter(1));
		_afit_1->SetParName(2, "a_{1}");	_afit_1->SetParameter( 2, _res.Parameter(2));
		_afit_1->SetParName(3, "#tau_{1}"); _afit_1->SetParameter( 3, _res.Parameter(3));
		_afit_1->SetLineColor(kGray+3);
		_afit_1->SetLineStyle(7);
    	
		TF1 * _afit_2 = new TF1("_afit_2", scint_time_1, _r_min, _r_max, 4);
		_afit_2->SetParName(0, "TT");   	_afit_2->SetParameter( 0, _res.Parameter(0));
		_afit_2->SetParName(1, "TTS");	    _afit_2->SetParameter( 1, _res.Parameter(1));
		_afit_2->SetParName(2, "a_{2}");	_afit_2->SetParameter( 2, _res.Parameter(4));
		_afit_2->SetParName(3, "#tau_{2}"); _afit_2->SetParameter( 3, _res.Parameter(5));
		_afit_2->SetLineColor(kGray+3);
		_afit_2->SetLineStyle(7);
		    	
		_afit_1->SetNpx(500);
		_afit_2->SetNpx(500);
		_afit->SetNpx(500);
	
	} else if ( _res.NPar() == 4 ) {
		
		TF1 * _afit = new TF1("_afit", scint_time_1, _r_min, _r_max, 4);
		_afit->SetParName(0, "TT");   	  _afit->SetParameter( 0, _res.Parameter(0));
		_afit->SetParName(1, "TTS");	  _afit->SetParameter( 1, _res.Parameter(1));
		_afit->SetParName(2, "a_{1}");	  _afit->SetParameter( 2, _res.Parameter(2));
		_afit->SetParName(3, "#tau_{1}"); _afit->SetParameter( 3, _res.Parameter(3));
		
	}
 	
	//TCanvas * _c = new TCanvas();

	_c->SetLogy(true);
	
	_h->SetStats(false); 

	//_h->Rebin(4);
	
	double _y_min = 0.01 * _h->GetMaximum();
	double _y_max = 1.2 * _h->GetMaximum();
	
	_h->GetYaxis()->SetRangeUser(_y_min, _y_max);
	
	_h->Draw();
		
	// Complete function
	if( _res.NPar() == 8 ){
		_afit_1->Draw("same");
		_afit_2->Draw("same");
		_afit_3->Draw("same");
	} 
	else if( _res.NPar() == 6 ){
		_afit_1->Draw("same");
		_afit_2->Draw("same");
	}

		
	_afit->Draw("same");

	TPaveText *pt = new TPaveText(0.63,0.42,0.88,0.87, "NDCT");
	pt->SetTextAlign(11);
	pt->SetTextFont(42);
	pt->SetTextSize(0.035);
	pt->SetFillColor(kWhite);

	pt->AddText( TString::Format("%s : %.2f #pm %.2f ns"       , "t_{0}"      , _res.Parameter(0), _res.ParError(0)));
	pt->AddText( TString::Format("%s : %.2f #pm %.2f ns"       , "#sigma"     , _res.Parameter(1), _res.ParError(1)));
	pt->AddText( TString::Format("%s : %.0f #pm %.0f"          , "a_{1}"      , _res.Parameter(2), _res.ParError(2)));
	pt->AddText( TString::Format("%s : %.2f #pm %.2f ns"       , "#tau_{1}"   , _res.Parameter(3), _res.ParError(3)));

	if( _res.NPar() == 8 ){
		pt->AddText( TString::Format("%s : %.1f #pm %.1f"          , "a_{2}"      , _res.Parameter(4), _res.ParError(4)));
		pt->AddText( TString::Format("%s : %.0f #pm %.0f ns"       , "#tau_{2}"   , _res.Parameter(5), _res.ParError(5)));
		pt->AddText( TString::Format("%s : %.0f #pm %.0f"          , "a_{3}"      , _res.Parameter(6), _res.ParError(6)));
		pt->AddText( TString::Format("%s : %.0f #pm %.0f ns"       , "#tau_{3}"   , _res.Parameter(7), _res.ParError(7)));
	} else if( _res.NPar() == 6 ){
		pt->AddText( TString::Format("%s : %.0f #pm %.0f"          , "a_{3}"      , _res.Parameter(4), _res.ParError(4)));
		pt->AddText( TString::Format("%s : %.0f #pm %.0f ns"       , "#tau_{3}"   , _res.Parameter(5), _res.ParError(5)));
	}

				
	pt->AddText( TString::Format("%s : %.0f/%i"                , "#chi^2/dof" , _res.Chi2()      , _res.Ndf()));						
				
	pt->Draw();

	_c->Update();

	//_c->Print("scint_time.pdf");
	
	//if( _res.NPar() == 8 ){
    //
	//	double int_1 = _afit_1->Integral(_r_min, _r_max);
	//	double int_2 = _afit_2->Integral(_r_min, _r_max);
	//	double int_3 = _afit_3->Integral(_r_min, _r_max);
	//
	//	std::cout << "Integral 1: " << int_1 << std::endl;
	//	std::cout << "Integral 2: " << int_2 << std::endl;
	//	std::cout << "Integral 3: " << int_3 << std::endl;
    //
	//}	
	
}

ROOT::Fit::FitResult fit_waveform_data(TH1 * _h, double * limit = 0, double * init = 0){	
	
	//TFile * _file = new TFile(f_name, "READ");
	
	//TH1F * _h = (TH1F*) _file->Get("overall_waveform_ch4");
	
	//TProfile * _profile = (TProfile*) _file->Get("overall_waveform_ch4");
	
	//TH1D * _h = _profile->ProjectionX("_h","E");
	
	_h->Scale(-1); // Reverse the waveform

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
	double _r_min = 500;   // ns
	double _r_max = 3995;  // ns
	
	if ( limit != 0 ){
		_r_min = limit[0];
		_r_max = limit[1];
		
	}
	
	if( init !=0 && init[4] == -1 || init[5] == -1){
		
		TF1 * _func = new TF1("scint_time", scint_time_2, _r_min, _r_max, 6);		
		
	} else {
		
		TF1 * _func = new TF1("scint_time", scint_time_3, _r_min, _r_max, 8);		
	}
	
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
		
	if( init == 0 ) {	
		
		fitter.Config().ParSettings(0).Set("t_{0}"    ,  510 , 1.);
		fitter.Config().ParSettings(1).Set("#sigma"   ,   11 , 1.);
		fitter.Config().ParSettings(2).Set("a_{1}"    , 1600 , 1.);
		fitter.Config().ParSettings(3).Set("#tau_{1}" ,    6 , 1.); fitter.Config().ParSettings(3).Fix();
		fitter.Config().ParSettings(4).Set("a_{2}"    ,  100 , 1.);
		fitter.Config().ParSettings(5).Set("#tau_{2}" ,   57 , 1.); 
		fitter.Config().ParSettings(6).Set("a_{3}"    ,   19 , 1.);
		fitter.Config().ParSettings(7).Set("#tau_{3}" , 3500 , 1.);

	} else {

		if( init !=0 && init[4] == -1 || init[5] == -1){

			fitter.Config().ParSettings(0).Set("t_{0}"    ,  init[0] , 1.);
			fitter.Config().ParSettings(1).Set("#sigma"   ,  init[1] , 1.);
			fitter.Config().ParSettings(2).Set("a_{1}"    ,  init[2] , 1.);
			fitter.Config().ParSettings(3).Set("#tau_{1}" ,  init[3] , 1.);  fitter.Config().ParSettings(3).Fix();
			fitter.Config().ParSettings(4).Set("a_{3}"    ,  init[6] , 1.);
			fitter.Config().ParSettings(5).Set("#tau_{3}" ,  init[7] , 1.);


		} else {

			fitter.Config().ParSettings(0).Set("t_{0}"    ,  init[0] , 1.);
			fitter.Config().ParSettings(1).Set("#sigma"   ,  init[1] , 1.);
			fitter.Config().ParSettings(2).Set("a_{1}"    ,  init[2] , 1.);
			fitter.Config().ParSettings(3).Set("#tau_{1}" ,  init[3] , 1.);  fitter.Config().ParSettings(3).Fix();
			fitter.Config().ParSettings(4).Set("a_{2}"    ,  init[4] , 1. ); //fitter.Config().ParSettings(4).Fix(); 
			fitter.Config().ParSettings(5).Set("#tau_{2}" ,  init[5] , 1. ); //fitter.Config().ParSettings(5).Fix(); 
			fitter.Config().ParSettings(6).Set("a_{3}"    ,  init[6] , 1.);
			fitter.Config().ParSettings(7).Set("#tau_{3}" ,  init[7] , 1.);
		
		}
		
	}
	
	
	
	fitter.LikelihoodFit(data);				
			
	ROOT::Fit::FitResult _res = fitter.Result();	
	
	return _res;
		
}

ROOT::Fit::FitResult fit_waveform_mc_1(){	
	
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
	fitter.Config().ParSettings(2).Set("a_{1}"    , 10000 , 0.1); //
	fitter.Config().ParSettings(3).Set("#tau_{1}" ,    10 , 0.1); //fitter.Config().ParSettings(3).Fix();
	fitter.Config().ParSettings(4).Set("a_{2}"    ,  1000 , 0.1); ////fitter.Config().ParSettings(4).Fix();
	fitter.Config().ParSettings(5).Set("#tau_{2}" ,   100 , 0.1); //fitter.Config().ParSettings(5).Fix();
	fitter.Config().ParSettings(6).Set("a_{3}"    ,   10 , 0.1);  //
	fitter.Config().ParSettings(7).Set("#tau_{3}" , 1500 , 0.1); //fitter.Config().ParSettings(7).Fix();
	
	fitter.LikelihoodFit(data);				
			
	ROOT::Fit::FitResult _res = fitter.Result();	
	
	return _res;
		
}

ROOT::Fit::FitResult fit_waveform_data_tail_only(TH1 * _h, double * limit = 0, double * init = 0){	
	
	//TFile * _file = new TFile(f_name, "READ");
	
	//TH1F * _h = (TH1F*) _file->Get("overall_waveform_ch4");
	
	//TProfile * _profile = (TProfile*) _file->Get("overall_waveform_ch4");
	
	//TH1D * _h = _profile->ProjectionX("_h","E");
	
	_h->Scale(-1); // Reverse the waveform

	_h->GetXaxis()->SetRangeUser(400, 3995);

	///
	// Fit the pedestal
	//
	
	TF1 * _func_pedestal = new TF1("pedestal", "pol0", 0 ,4000);
		
	TFitResultPtr r = _h->Fit(_func_pedestal, "F0S","",0, 400);			
		
	_h->Add(_func_pedestal, -1 );
		
	//
	// Fit function and range
	// 		
	double _r_min = 500;   // ns
	double _r_max = 3995;  // ns
	
	if ( limit != 0 ){
		_r_min = limit[0];
		_r_max = limit[1];
		
	}
		
	TF1 * _func = new TF1("scint_time", scint_time_1, _r_min, _r_max, 4);		
		
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
		
	fitter.Config().ParSettings(0).Set("t_{0}"    ,  539.30 , 0.1); fitter.Config().ParSettings(0).Fix();
	fitter.Config().ParSettings(1).Set("#sigma"   ,   10.12 , 0.1); fitter.Config().ParSettings(1).Fix();
	fitter.Config().ParSettings(2).Set("a_{3}"    ,   19 , 0.1);
	fitter.Config().ParSettings(3).Set("#tau_{3}" , 3500 , 0.1);
	
	
	fitter.LikelihoodFit(data);				
			
	ROOT::Fit::FitResult _res = fitter.Result();	
		
	return _res;
		
}

TH1D * get_histo_to_fit(int ch, TFile * _file){
	
	//TH1F * _h = (TH1F*) _file->Get( TString::Format("overall_waveform_ch%i", ch ) );
	
	TProfile * _profile = (TProfile*) _file->Get( TString::Format("overall_waveform_ch%i", ch ) );
	
	if ( !_profile ) Fatal("", "Histo to fit not found");
		
	TH1D * _h = _profile->ProjectionX("_h","E");
	
	return _h;
	
}

void fit_waveform( int mode = 0, int channel = 0, int run = 211 ){
	
	char * f_name = TString::Format("$WLS_PLOT/simple_ana_run_%08d.root", run);
		
	TFile * _file = new TFile(f_name, "READ");
	
	TH1D * _h = get_histo_to_fit(channel, _file);
	
	_h->SetTitle( TString::Format("Scintillation light: run %i, ch. %i", run, channel) );

	_h->GetYaxis()->SetTitle("Arbitrary units");
	
	ROOT::Fit::FitResult _res;
	
	double limit[2];
	double init[7];
	
	// Perform the fit
	if (mode == 0) {
		
		limit[0] = 530;
		limit[1] = 3995;
		
		init[0] = 555;    // Fit t_0
		init[1] = 10;     // Fit sigma		
		init[2] = 10000 ;  // a1
		init[3] = 6    ;  // t1
		init[4] = 100  ;  // a2
		init[5] = 50   ;  // t2
		init[6] = 1000   ;  // a3
		init[7] = 1500 ;  // t3				
		
		_res = fit_waveform_data(_h, limit, init); 
		
	} else if (mode == 1) { // tail only
		
		limit[0] = 1500;
		limit[1] = 3995;
		
		
		_res = fit_waveform_data_tail_only(_h, limit); 

	} else if (mode == 2) { // mc 1
		_res = fit_waveform_mc_1(); 
	} else {
		_res = fit_waveform_data(_h); 
	}
	
	TCanvas * _c = new TCanvas();	
		
	// Dress	
	if ( mode == 1) 	
		dress_plot(_res, _h, _c, limit[0], limit[1]);
	else
		dress_plot(_res, _h, _c, limit[0], limit[1]);
			
	_c->Print(TString::Format("scint_time_n_%i_run_%08d_ch%i.pdf", mode, run, channel));		
			
	//_file->Close();
	
}

void fit_waveform_all_ch( int mode = 0, int run = 211, int part = 0 ){
	
	
	if( part == 0 ) {
		char * f_name = TString::Format("$WLS_PLOT/simple_ana_run_%08d.root", run);
	} else {
		char * f_name = TString::Format("$WLS_PLOT/simple_ana_run_%08d_%i.root", run, part);
	} 
	
	TFile * _file = new TFile(f_name, "READ");
		
	if( ! _file ) Fatal("", "File %s does not exist!", f_name);
		
	ROOT::Fit::FitResult _res;

	//_c->Divide(2,3);

	// Perform the fit	
	for( int i = 0; i < 5; i++){

		TCanvas * _c = new TCanvas(TString::Format("scint_time_m_%i_run_%i_ch_%i", mode, run, i), TString::Format("scint_time_m_%i_run_%i_ch_%i", mode, run, i));	

		TH1D * _h = get_histo_to_fit(i, _file);	

		_h->SetTitle( TString::Format("Scintillation light: run %i, ch. %i", run, i) );

		_h->GetYaxis()->SetTitle("Arbitrary units");

		double init[7];
		double limit[2];

		if (mode == 0){

			if ( i == 0 ) { 
				limit[0] = 480;
				limit[1] = 3995;
				
				init[0] = 520;    // Fit t_0
				init[1] = 11;     // Fit sigma		
				init[2] = 1600 ;  // a1
				init[3] = 6    ;  // t1
				init[4] = 100  ;  // a2
				init[5] = 57   ;  // t2
				init[6] = 19   ;  // a3
				init[7] = 3500 ;  // t3
				
				}
			if ( i == 1 ) { 
				limit[0] = 480;
				limit[1] = 3995;
				
				init[0] = 513;    // Fit t_0
				init[1] = 20;     // Fit sigma		
				init[2] = 1100 ;  // a1
				init[3] = 6    ;  // t1
				init[4] = 60  ;  // a2
				init[5] = 81   ;  // t2
				init[6] = 32   ;  // a3
				init[7] = 1400 ;  // t3

				}
			if ( i == 2 ) { 
				limit[0] = 540;
				limit[1] = 3995;
				
				init[0] = 580;    // Fit t_0
				init[1] = 24;     // Fit sigma		
				init[2] = 5000 ;  // a1
				init[3] = 6    ;  // t1
				init[4] = 0  ;  // a2
				init[5] = 1.   ;  // t2
				init[6] = 58   ;  // a3
				init[7] = 1300 ;  // t3
				
				}
			if ( i == 3 ) { 
				limit[0] = 540;
				limit[1] = 3995;
				
				init[0] = 580;    // Fit t_0
				init[1] = 24;     // Fit sigma		
				init[2] = 5000 ;  // a1
				init[3] = 6    ;  // t1
				init[4] = 0  ;  // a2
				init[5] = 1.   ;  // t2
				init[6] = 58   ;  // a3
				init[7] = 1300 ;  // t3			
				}
			if ( i == 4 ) { 
				limit[0] = 480;
				limit[1] = 3995;
				
				init[0] = 522;    // Fit t_0
				init[1] = 24;     // Fit sigma		
				init[2] = 3324 ;  // a1
				init[3] = 6    ;  // t1
				init[4] = 100  ;  // a2
				init[5] = 144   ;  // t2
				init[6] = 77   ;  // a3
				init[7] = 1700 ;  // t3				
				}
		    
			_res = fit_waveform_data(_h, init); 

			dress_plot(_res, _h, (TPad *)_c->cd(i+1) , 500, 4000);
		}
		
		else if (mode == 1) { // tail only
			
			_res = fit_waveform_data_tail_only(_h); 
			
			dress_plot(_res, _h, (TPad *)_c->cd(i+1) , 1500, 4000);
		
		}

		else{ 
			
			Fatal("","Non valid mode : %i ", mode);
			
		}
	
		_c->Print(TString::Format("scint_time_m_%i_run_%08d_ch_%i.pdf", mode, run, i));		
		
	}
			
	//_file->Close();
	
}