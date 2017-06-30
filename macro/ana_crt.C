void ana_crt(int run_number = 0){
	//
	// Load library
	//
	gSystem->Load("$WLS_PATH/build/lib/libLightSoft");
	//
	// Info level
	//
	gErrorIgnoreLevel = kInfo; // kWarning;
	//
	// Create the TChain to process
	//
	TChain * t = new TChain("midas_data");
	//
	// Add root file to process
	//
	t->Add( TString::Format("$WLS_DATA/output%08d.root", run_number) );
	//
	// Create the loop object
	//
	loop * l = new loop();
	//
	// Create an instance of the module_pedestal 
	//
	module_crt_ana * my_module_crt_ana = new module_crt_ana();
	//
	// Add modules to the even processing pipeline
	//		
	l->add_module( my_module_crt_ana );
	//
	// Run the loop
	//	
	t->Process(l);
	//
	// Save plots to file
	//	
	plotter::get_me().save_as( TString::Format("ana_crt_run_%08d.pdf", run_number));
	plotter::get_me().save_as( TString::Format("$WLS_PLOT/ana_crt_run_%08d.root", run_number));
	//
}
