/*
	
	module_evt_dump.h
	Purpose: Base class to dump events on the terminal
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
*/

#ifndef module_evt_dump_h
#define module_evt_dump_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_evt_dump : public module {

public:

    module_evt_dump() { };
	module_evt_dump(module_evt_dump &) { };
    virtual ~module_evt_dump() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();

private:

	ClassDef(module_evt_dump,0);
	
};

#endif