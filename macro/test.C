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
    t->Process(l);
	//	
}
