/*
	
	module_peak_finder.h
	Purpose: Base class for peak_finder calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
*/

#ifndef module_peak_finder_h
#define module_peak_finder_h

#include <TObject.h>
#include <TSpectrum.h>

#include "module.h"
#include "event.h"

class module_peak_finder : public module {

public:

    module_peak_finder() {
		
	};
	module_peak_finder(module_peak_finder &) { };
    virtual ~module_peak_finder() { };

	virtual void begin();
	virtual void process( event * evt);
	virtual void terminate();
	
private:
		
	int _treshold;	
		
	ClassDef(module_peak_finder,0);
	
};

#endif