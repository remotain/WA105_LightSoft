#ifndef module_pedestal_h
#define module_pedestal_h

#include <TObject.h>

#include "module.h"
#include "event.h"


class module_pedestal : public module {

public:

    module_pedestal() { };
	module_pedestal(module_pedestal &) { };
    virtual ~module_pedestal() { };

	virtual void begin();
	virtual void process( event * e);
	virtual void terminate();

private:

	ClassDef(module_pedestal,0);
	
};

#endif