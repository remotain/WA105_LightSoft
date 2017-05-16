/**
	
	module_output.h
	Purpose: Write events on output file. (DOES NOT WORK AT THE MOMENT!!)
	
	@author Alberto Remoto
	@version 1.0 2017-02-09

**/

#ifndef module_output_h
#define module_output_h

#include <TObject.h>
#include <TFile.h>
#include <TTree.h>
#include <iostream>

#include "module.h"
#include "event.h"

class module_output : public module {

public:

    module_output(): _file(0), _tree(0), _evt_ptr(0) { 
	
		_file_name = "light_soft_tree.root";
		_tree_name = "light_soft_tree";
	
	};
	
	module_output(module_output &) { };
    virtual ~module_output() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();

	void set_file_name( const char * a_string ) { _file_name = a_string; }; 
	void set_tree_name( const char * a_string ) { _tree_name = a_string; }; 
	
	const char * get_file_name() { return _file_name; }; 
	const char * get_tree_name() { return _tree_name; }; 
	
private:

	const char * _file_name;
	const char * _tree_name;

	TFile * _file;
	TTree * _tree;

	event * _evt_ptr;

	ClassDef(module_output,0);
	
};

#endif