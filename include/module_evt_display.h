/*
	
	module_evt_display.h
	Purpose: Base class to display events
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
*/

#ifndef module_evt_display_h
#define module_evt_display_h

#include <TObject.h>

#include "module.h"
#include "event.h"

#include <TCanvas.h>
#include <TH2.h>

class module_evt_display : public module {

public:

    module_evt_display() { };
	module_evt_display(module_evt_display &) { };
    virtual ~module_evt_display() { };

	virtual void begin();
	virtual void process( event * evt);
	virtual void terminate();

    TCanvas * c; //! Canvas to display the event
	
	std::vector<TH1F*> _waveform;
	
private:

	ClassDef(module_evt_display,0);
	
};

#endif