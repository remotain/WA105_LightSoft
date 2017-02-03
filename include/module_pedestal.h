/**
	
	module_pedestal.cc
	Purpose: Base class for pedestal calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03

**/

#ifndef module_pedestal_h
#define module_pedestal_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_pedestal : public module {

public:

    module_pedestal() { _nsample = -1; };
	module_pedestal(module_pedestal &) { };
    virtual ~module_pedestal() { };

	virtual void begin();
	virtual void process( event * evt);
	virtual void terminate();

	virtual void set_nsample( int a_value) { _nsample = a_value; };
	virtual int get_nsample() { return _nsample; };
	
	virtual double calculate_pedestal_average( std::vector<int> * waveform);
	virtual double calculate_pedestal_standard_deviation( std::vector<int> * waveform);

private:

	int _nsample;

	ClassDef(module_pedestal,0);
	
};

#endif