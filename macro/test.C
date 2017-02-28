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
	t->Add("$WLS_PATH/examples/output_000211.root");
	//
	// Create the loop object
	//
	loop * l = new loop();
	//
	// Add modules to the even processing pipeline
	//
	l->add_module( new module_pedestal    );
	l->add_module( new module_charge      );
	l->add_module( new module_evt_dump    );
	l->add_module( new module_evt_display );

	//l->add_module( new module_output    ); // DOES NOT WORK AT THE MOMENT!!

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
