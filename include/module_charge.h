#ifndef module_charge_h
#define module_charge_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_charge : public module {

public:

    module_charge() { };
	module_charge(module_charge &) { };
    virtual ~module_charge() { };

	virtual void begin();
	virtual void process( event * evt);
	virtual void terminate();

private:

	ClassDef(module_charge,0);
	
};

#endif