{
	//
	// Load library
	//
	gSystem->Load("../build/lib/libLightSoft.dylib");
	//
	// Create the TChain to process
	//
	TChain * t = new TChain("midas_data");
	//
	// Add root file to process
	//
	t->Add("../examples/output_000211.root");
	//
	// Create the loop object
	//
	loop * l = new loop();
	//
	//
	//
	l->add_module( new module_pedestal    );
	l->add_module( new module_charge      );
	l->add_module( new module_evt_dump    );
	//l->add_module( new module_evt_display );
	//
	//
	//
    t->Process(l);
	//	
}
