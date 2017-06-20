/*	
	plotter.cc
	Purpose: handle plotting function of the framework
		
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: please refer to the class definition in include/plotter.h

*/

#define plotter_cxx

#include "plotter.h"

TH1 * plotter::find( const char* name ) 
{ 
	// Find object by name in the _collection THashList.

	TH1 * obj = (TH1*) _collection->FindObject(name); 
	
	//if ( !obj ) Info("find", "Histo '%s' not found in collection", name);
		
	return obj;
};

TH2 * plotter::find2d( const char* name ) 
{ 
	// Find object by name in the _collection THashList.

	TH2 * obj = (TH2*) _collection->FindObject(name); 
	
	//if ( !obj ) Info("find", "Histo '%s' not found in collection", name);
		
	return obj;
};

TGraph * plotter::findGraph( const char* name ) 
{ 
	// Find object by name in the _collection THashList.

	TGraph * obj = (TGraph*) _g_collection->FindObject(name); 
	
	//if ( !obj ) Info("find", "Graph '%s' not found in collection", name);
		
	return obj;
};

	
void plotter::save_as(const char* filename, Option_t* option)
{
	
	// Save plots found in the _collection THashList on a pdf file.
		
	gROOT->SetBatch(true);
		
	if (filename && strstr(filename,".pdf")) {
		
		TIter next(_collection);
		TH1D * h;
		
		while( (h = (TH1D *) next()) ) {
			
			TCanvas c (h->GetName(), h->GetTitle());
			h->Draw();
			
			Info("save_as", "Saving %s", h->GetName() );
			
			if( h == _collection->First()) {
				c.Print( TString::Format("%s(", filename) );
			} else if( h == _collection->Last() && _g_collection->GetEntries() == 0 ) {
				c.Print( TString::Format("%s)", filename) );
			} else {
				c.Print(filename);
			}
		
		}

		TIter g_next(_g_collection);
		TGraph * g;
		
		while( (g = (TGraph *) g_next()) ) {
			
			TCanvas c (g->GetName(), g->GetTitle());
			g->Draw("AP");
			
			Info("save_as", "Saving %s", g->GetName() );
			
			if( g == _g_collection->First() && _collection->GetEntries() == 0 ) {
				c.Print( TString::Format("%s(", filename) );
			} else if( g == _g_collection->Last()) {
				c.Print( TString::Format("%s)", filename) );
			} else {
				c.Print(filename);
			}
		
		}

		
	}
	
	else if (filename && strstr(filename,".root")) {
	
		TFile a_file(filename, "RECREATE");
	
		Info("save_as", "root file %s has been created", filename);
	
		TIter next(_collection);
		TH1D * h;
		
		while( (h = (TH1D *) next()) ) {
			
			Info("save_as", "Saving %s", h->GetName() );
			
			a_file.cd();
			
			h->Write();
			
			//Info("save_as", "Current histogram added to root file %s", filename);
			
		}
	
		TIter g_next(_g_collection);
		TH1D * g;
		
		while( (g = (TH1D *) g_next()) ) {
		
			Info("save_as", "Saving %s", g->GetName() );
			
			a_file.cd();
			
			g->Write();
			
			//Info("save_as", "Current histogram added to root file %s", filename);
			
		}
	
	
		a_file.Close();
		
	}
	 
	else {
		Error("save_as", "cannot open file: %s", filename);	
	} 
	 
	gROOT->SetBatch(false);
	
	
}
