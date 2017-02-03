/*	
	plotter.h
	Purpose: handle plotting function of the framework
		
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: please refer to the class definition in include/module.h

*/

#define plotter_cxx

#include "plotter.h"

TH1 * plotter::find( const char* name ) 
{ 
	// Find object by name in the _collection THashList.

	TH1 * obj = (TH1*) _collection->FindObject(name); 
	
	if ( !obj ) Error("find()", "Histo '%s' not found in collection", name);
		
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
			
			if( h == _collection->First()) c.Print( TString::Format("%s(", filename) );
			else if( h == _collection->Last()) c.Print( TString::Format("%s)", filename) );
			else c.Print(filename);
		
		}
		
	
		
		return;
	}
	
	gROOT->SetBatch(false);
	
	Error("save_as", "cannot open file: %s", filename);	
	
}
