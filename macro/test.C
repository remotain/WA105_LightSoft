{
	int run_number = 186;

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
	// Create an instance of the module_pedestal 
	//
	module_pedestal * my_module_pedestal = new module_pedestal();
	my_module_pedestal->set_nsample(999); // set the number of sample used to compute the pedestal
	//
	// Create an instance of the module_charge
	//
	module_charge * my_module_charge = new module_charge();
	//
	// Add modules to the even processing pipeline
	//
	l->add_module( my_module_pedestal );
	l->add_module( my_module_charge   );

	l->add_module( new module_plot_dump ); 
	//l->add_module( new module_evt_dump );


	//
	// Run the loop
	//	
    t->Process(l);
	//
	// Save plots to file
	//	
	plotter::get_me().save_as( TString::Format("test%08d.pdf", run_number));
	plotter::get_me().save_as( TString::Format("test%08d.root", run_number));
	//
}
