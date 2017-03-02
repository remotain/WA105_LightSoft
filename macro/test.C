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
	// Create an instance of the module_pedestal 
	//
	module_pedestal * my_module_pedestal = new module_pedestal();
	my_module_pedestal->set_nsample(100); // set the number of sample used to compute the pedestal
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
	l->add_module( new module_evt_dump );


	//
	// Run the loop
	//	
    t->Process(l);
	//
	// Save plots to file
	//	
	plotter::get_me().save_as("test.pdf");
	plotter::get_me().save_as("test.root");
	//
}
