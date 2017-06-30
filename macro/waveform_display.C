void waveform_display(int run_number = 0){
	//
	// Load library
	//
	gSystem->Load("$WLS_PATH/build/lib/libLightSoft");
	//
	// Create the TChain to process
	//
	TChain * t = new TChain("midas_data");
	//
	// Add root file to process
	//
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );
	//t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 861) );
	//t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 862) );
	//t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", 922) );		
	//
	// Create the loop object
	//
	loop * l = new loop();
	//
	// Add modules to the even processing pipeline
	//
	module_cut * my_cut = new module_cut();

	//my_cut->set_cut_pmt_saturate (false);
	my_cut->set_cut_crt_match    ();
	my_cut->set_cut_crt_reco     ();
		
	//my_cut->set_cut_crt_track_angle (0, 0.1 );
	//my_cut->set_cut_crt_track_z     (-800, 200 );	
	
	//TTimeStamp tstart(2017,6,19,19,0,0,0,kFALSE);	
	//TTimeStamp tstop(2017,6,19,22,0,0,0,kFALSE);
	//my_cut->set_cut_time_stamp (tstart.AsDouble(),tstop.AsDouble());	
		
	l->add_module( my_cut );
	l->add_module( new module_evt_display );
	//
	// Run the loop
	//	
	t->Process(l);
	//t->Process(l,"", 10000000000, 21332); // Usage: nMAX, FirsEvent
	//
}
