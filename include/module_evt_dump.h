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
	virtual void process( event * evt);
	virtual void terminate();

private:

	ClassDef(module_evt_dump,0);
	
};

#endif