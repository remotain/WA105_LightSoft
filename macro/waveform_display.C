{
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
	t->Add("$WLS_PATH/examples/output00000186.root");
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
