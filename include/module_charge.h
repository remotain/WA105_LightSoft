/*
	
	module_charge.h
	Purpose: Base class for charge calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
*/

#ifndef module_charge_h
#define module_charge_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_charge : public module {

public:

    module_charge() {
	
		_pulse_max_tolerance   = 5;
		_pulse_start_amplitude = 0.20;
	
	};
	module_charge(module_charge &) { };
    virtual ~module_charge() { };

	virtual void begin();
	virtual void process( event * evt);
	virtual void terminate();
	
	virtual void set_pulse_max_tolerance( int a_value) { _pulse_max_tolerance = a_value; };
	virtual int get_pulse_max_tolerance() { return _pulse_max_tolerance; };
	
	virtual void set_pulse_start_amplitude( double a_value ) { _pulse_start_amplitude = a_value; };
	virtual int get_pulse_start_amplitude() { return _pulse_start_amplitude; };

private:

	int _pulse_max_tolerance; // Tolerance on the pulse maximum in term of pedestal std
	double _pulse_start_amplitude; // Amplitude which define the pulse time start in term of % of the pulse maximum

	ClassDef(module_charge,0);
	
};

#endif