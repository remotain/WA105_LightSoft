{
	//int run_number = 186; // 1h dry run
	int run_number = 211; // 30 min run with PMTs ON
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
	//t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );
	t->Add( TString::Format("$WLS_PATH/examples/output%08d.root", run_number) );
	//
	// Create the loop object
	//
	loop * l = new loop();
	//
	// Create an instance of the module_pedestal 
	//
	l->add_module( new module_pedestal );
	l->add_module( new module_peak_finder );
	//
	// Set output
	//
	l->write_output_tree(true);
	//
	// Run the loop
	//	
    t->Process(l);
	//
	// Save plots to file
	//	
	plotter::get_me().save_as( "test.pdf" );
	plotter::get_me().save_as( "test.root" );
	
	
}
