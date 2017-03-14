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
	//
	// Create the loop object
	//
	loop * l = new loop();
	//
	// Add modules to the even processing pipeline
	//
	l->add_module( new module_evt_display );
	//
	// Run the loop
	//	
	t->Process(l);
	//
}
