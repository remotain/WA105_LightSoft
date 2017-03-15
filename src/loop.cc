/**

    loop.cc
    Purpose: Handle event loop over a TChain

    @author Alberto Remoto
    @version 1.0 2017-02-03

 	The class definition in loop.h has been generated automatically
 	by the ROOT utility TTree::MakeSelector(). This class is derived
 	from the ROOT class TSelector. For more information on the TSelector
 	framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.
 	
 	The following methods are defined in this file:
 	   Begin():        called every time a loop on the tree starts,
 	                   a convenient place to create your histograms.
 	   SlaveBegin():   called after Begin(), when on PROOF called only on the
 	                   slave servers.
 	   Process():      called for each event, in this function you decide what
 	                   to read and fill your histograms.
 	   SlaveTerminate: called at the end of the loop on the tree, when on PROOF
 	                   called only on the slave servers.
 	   Terminate():    called at the end of the loop on the tree,
 	                   a convenient place to draw/fit your histograms.

**/

#define loop_cxx

#include "loop.h"
#include <TH2.h>
#include <TStyle.h>

void loop::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   Info("Begin", "Begin process" );

	if( _k_save_output ) {
		
		_output_file = new TFile(_output_file_name,"RECREATE");
		
		if( ! _output_file->IsOpen()) Fatal("Begin", "Output file not open: %s", _output_file_name);
		
		_output_tree = new TTree("reco_tree", "reco_tree");
		_event->set_output_tree( _output_tree );

	}
}

void loop::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

	// The module::begin() function is called of each module present in the _module_list
   for(int i = 0; i < _module_list.size(); i++) {
       _module_list[i]->begin();
   }
 
}

Bool_t loop::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either loop::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

	if (entry % 100 == 0){
		Info("Process", "Entry %lli" , entry );
	}
	
	
	GetEntry(entry);
	
	// Each event is passed to the module::process() of each module present in the
	// _module_list for processing
    for(int i = 0; i < _module_list.size(); i++) {
        _module_list[i]->process(_event);
    }
    	
	if( _k_save_output ) {
		_output_file->cd();
		_output_tree->Fill();	
	}
	
   return kTRUE;
}

void loop::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

	// The module::temrinate() function is called of each module present in the _module_list
    for(int i = 0; i < _module_list.size(); i++) {
        _module_list[i]->terminate();
    }
    


}

void loop::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

	if( _k_save_output ) {
		_output_tree->Write();
		_output_file->Close();
	}

   Info("Terminate", "Terminate process" );

}
