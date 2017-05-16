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
#include <TProfile.h>

class module_evt_display : public module {

public:

    module_evt_display() { };
	module_evt_display(module_evt_display &) { };
    virtual ~module_evt_display() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();

    TCanvas * c_pmt; //! Canvas to display the event
    TCanvas * c_crt; //! Canvas to display the event
	
	std::vector<TH1F*> _waveform;
	std::vector<TProfile*> _waveform_avg;
	
private:

	ClassDef(module_evt_display,0);
	
};

#endif