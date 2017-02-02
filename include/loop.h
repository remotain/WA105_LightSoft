//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb  1 13:41:22 2017 by ROOT version 5.34/34
// from TTree midas_data/MIDAS data
// found on file: output_000211.root
//////////////////////////////////////////////////////////

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

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class loop : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   event          *_event;
   
   vector<module*> _module_list;
   
   // Declaration of leaf types
   //Int_t           TimeStamp;
   //Int_t           nevent;
   //Int_t           nchannels;
   //Int_t           nsamples;
   //Int_t           TimeSample;
   //Int_t           adc_value_0[1000];
   //Int_t           adc_value_1[1000];

   // List of branches
   //TBranch        *b_TimeStamp;   //!
   //TBranch        *b_nevent;   //!
   //TBranch        *b_nchannels;   //!
   //TBranch        *b_nsamples;   //!
   //TBranch        *b_TimeSample;   //!
   //TBranch        *b_adc_value_0;   //!
   //TBranch        *b_adc_value_1;   //!

   loop(TTree * /*tree*/ =0) : fChain(0), _event(0) { _event = new event(); }
   
   virtual ~loop() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
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
   //fChain->SetMakeClass(1);

   _event->init(fChain);

   //fChain->SetBranchAddress("TimeStamp", &TimeStamp, &b_TimeStamp);
   //fChain->SetBranchAddress("event", &event, &b_event);
   //fChain->SetBranchAddress("nchannels", &nchannels, &b_nchannels);
   //fChain->SetBranchAddress("nsamples", &nsamples, &b_nsamples);
   //fChain->SetBranchAddress("TimeSample", &TimeSample, &b_TimeSample);
   //fChain->SetBranchAddress("adc_value_0", adc_value_0, &b_adc_value_0);
   //fChain->SetBranchAddress("adc_value_1", adc_value_1, &b_adc_value_1);

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

#endif // #ifdef loop_cxx
