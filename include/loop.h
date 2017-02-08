/**

    loop.h
    Purpose: Handle event loop over a TChain

    @author Alberto Remoto
    @version 1.0 2017-02-03

	Description: the class has been generated automatically from 
	TChain::MakeSelector() in order to handle correctly the loop
	over chained tree. In the implementation proposed here the 
	information extracted from the TChain is passed to a class 
	"event" which instantiate its data memeber over the TChain
	branches. The "loop::Process" function pass the event to a 
	list of module defined by the user for event processing.

	The user is suppose to interface this class within a ROOT 
	macro as follows:

	'''
	TChain * t = new TChain("midas_data");
	t->Add("../examples/output_000211.root");
	loop * l = new loop();
    t->Process(l);
	'''

*/

#ifndef loop_h
#define loop_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

#include <iostream>
#include <vector>

using namespace std;

#include "event.h"
#include "module.h"

class loop : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   event          *_event;  //!pointer to the event
   
   vector<module*> _module_list; //!list of module to be executed over each event
   
   loop(TTree * /*tree*/ =0) : fChain(0), _event(0) { _event = new event(); }
   
   virtual ~loop() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   //virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0);
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   void add_module(module * a_module) { _module_list.push_back( a_module); };

   ClassDef(loop,0);
};

#endif

#ifdef loop_cxx
void loop::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;

   _event->init(fChain);

}

Bool_t loop::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

Int_t loop::GetEntry(Long64_t entry, Int_t getall)
{

	Int_t val = 0;
	
	if( fChain){
		val = fChain->GetTree()->GetEntry(entry, getall);
		_event->assign(); // set internal pointers for the new events
		
	}
	
	return val;
}

#endif // #ifdef loop_cxx
