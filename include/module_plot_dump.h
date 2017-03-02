/*
	
	module_plot_dump.h
	Purpose: Base class to dump some plot
	
	@author Alberto Remoto
	@version 1.0 2017-03-0s
	
*/

#ifndef module_plot_dump_h
#define module_plot_dump_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_plot_dump : public module {

public:

    module_plot_dump() { };
	module_plot_dump(module_plot_dump &) { };
    virtual ~module_plot_dump() { };

	virtual void begin();
	virtual void process( event * evt);
	virtual void terminate();

private:

	int _n_evt;
	double _t_min, _t_max; 
	std::vector<double> _t;

	ClassDef(module_plot_dump,0);
	
};

#endif