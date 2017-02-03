/*	
	plotter.h
	Purpose: handle plotting function of the framework
		
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: implemented as singleton design pattern, the plotter class
	handle plots thorugh all the framework. In order to acess the plotter,
	it is enough to include this header file and call the "get_me()" method.

	To add a plot named "histo" to the plotter:

	'''
	plotter::get_me().add( new TH1D("histo", "histo", 100, 0 ,100) );
	'''

	To fill the plot named "histo": 
	
	'''
	plotter::get_me().find("histo")->Fill( some_value );
	'''

	To draw the plot named "histo": 
	'''
	plotter::get_me().find("histo")->Draw();
	'''
	
	To save its contect on a pdf file:
	'''
	plotter::get_me().save_as("file_name.pdf");
	'''

	
*/
#ifndef plotter_h
#define plotter_h

#include<TROOT.h>
#include<TObject.h>
#include<THashList.h>
#include<TH1.h>
#include<TH2.h>
#include<TFile.h>
#include<TCanvas.h>
#include<TKey.h>
#include<TString.h>

#include <cstring>
#include <iostream>

class plotter : TObject {

public:

	static plotter& get_me() {
		// The only instance
		// Guaranteed to be lazy initialized
		// Guaranteed that it will be destroyed correctly
		static plotter me;
		return me;
    }

	void add( TH1 * h ) { _collection->Add(h); };
	//void add( TH2 * h ) { _collection->Add(h); };

	TH1 * find( const char* name );
	
	THashList * get_collection(){ return _collection; };
	
	void save_as(const char* filename = "", Option_t* option = "");

private:
	// Private Constructor
    plotter(){ _collection = new THashList(); _collection->SetOwner(true); };
    ~plotter() { delete _collection; };
	
	// Stop the compiler generating methods of copy the object
    plotter(plotter const& copy);            // Not Implemented
    plotter& operator=(plotter const& copy); // Not Implemented

	THashList * _collection;
	
ClassDef(plotter,0);
		
};

#endif
