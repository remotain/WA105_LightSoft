/**
	
	module_output.cc
	Purpose: Write events on output file. (DOES NOT WORK AT THE MOMENT!!)
	
	@author Alberto Remoto
	@version 1.0 2017-02-09
	
	Description: 
	
**/

#define module_output_cxx

#include "module_output.h"

void module_output::begin(){
	
	_file = new TFile( _file_name, "RECREATE" );

	_tree = new TTree( _tree_name, _tree_name );
	
	event * _evt_ptr = 0;
	
};

bool module_output::process( event * evt){
	
	//_evt_ptr = evt;
	
	//_tree->Branch("event", &evt, 32000, 1 );
	
	_tree->Fill();
	
	return true;
	
};

void module_output::terminate(){
	
	_tree->Print();
	
	_file->Write();
	
	_file->Close();
	
};