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

#include <TFile.h>
#include <TCanvas.h>
#include <TH2.h>
#include <TProfile.h>
#include <TH2Poly.h>

enum kCanvas { 
	Canvas,
	wCh0,
	wCh1,
	wCh2,
	wCh3,
	wCh4,
	wAll,
	crtT,
	crtW,
	crtXY1,
	crtXY2,
	viewYZ,
	viewXY
};


class module_evt_display : public module {

public:

    module_evt_display(): c_pmt(0) {
	
		c_pmt = new TCanvas("PMT Display", "PMT Display", 5000, 5000);
		
	
	};
	
	module_evt_display(module_evt_display &) { };
    virtual ~module_evt_display() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();

	TVirtualPad * go_to_pad( kCanvas k );

    TCanvas * c_pmt; //! Canvas to display the event
    TCanvas * c_crt; //! Canvas to display the event
	
	std::vector<TH1F*> _waveform;
	std::vector<TProfile*> _waveform_avg;
	
private:

	TH2Poly *_view_yz;
	TH2Poly *_view_xy;

	ClassDef(module_evt_display,0);
	
};

#endif