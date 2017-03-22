void simple_ana(int run_number = 0){
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
	t->Add( TString::Format("$WLS_DATA/output%08d.root", run_number) );
	//
	// Create the loop object
	//
	loop * l = new loop();
	//
	// Create an instance of the module_pedestal 
	//
	module_pedestal * my_module_pedestal = new module_pedestal();
	//
	// set the number of sample used to compute the pedestal
	//
	my_module_pedestal->set_nsample(100); 
	//
	// Create an instance of the module_charge
	//
	module_charge * my_module_charge = new module_charge();
	//	
	// Set integration time window
	//
	my_module_charge->set_integration_window_length(30);
	my_module_charge->set_integration_window_start(990-30);		
	//
	// Add modules to the even processing pipeline
	//
	l->add_module( my_module_pedestal );
	l->add_module( my_module_charge   );
	l->add_module( new module_plot_dump ); 
	//l->add_module( new module_evt_dump );
	//
	// Write processed event on an output tree
	//
	l->save_output_tree( TString::Format("$WLS_DATA/recoed%08d.root", run_number) );
	//
	// Run the loop
	//	
	t->Process(l);
    //t->Process(l,"", 800, 800);
	//
	// Save plots to file
	//	
	plotter::get_me().save_as( TString::Format("simple_ana_run_%08d.pdf", run_number));
	plotter::get_me().save_as( TString::Format("$WLS_PLOT/simple_ana_run_%08d.root", run_number));
	//
	
}
