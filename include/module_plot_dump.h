/*
	
	module_plot_dump.h
	Purpose: Base class to dump some plot
	
	@author Alberto Remoto
	@version 1.0 2017-03-0s
	
*/

#ifndef module_plot_dump_h
#define module_plot_dump_h

#include <TObject.h>
#include <TMath.h>

#include "module.h"
#include "event.h"

class module_plot_dump : public module {

public:

    module_plot_dump() { };
	module_plot_dump(module_plot_dump &) { };
    virtual ~module_plot_dump() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();

private:

	int _n_evt, _n_evt_exc;
	double _t_min, _t_max; 
	std::vector<double> _t;

	std::vector<int> _avg_w_ch0;
	std::vector<int> _avg_w_ch1;
	std::vector<int> _avg_w_ch2;
	std::vector<int> _avg_w_ch3;
	std::vector<int> _avg_w_ch4;			

	std::vector<int> _std_w_ch0;
	std::vector<int> _std_w_ch1;
	std::vector<int> _std_w_ch2;
	std::vector<int> _std_w_ch3;
	std::vector<int> _std_w_ch4;			


	ClassDef(module_plot_dump,0);
	
};

#endif