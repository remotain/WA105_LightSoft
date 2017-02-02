#ifndef module_h
#define module_h

#include <TObject.h>

#include "event.h"

class module : public TObject {

public:

    module() { };
	module(module &) { };
    virtual ~module() { };

	virtual void begin(){};
	virtual void process( event * e) {};
	virtual void terminate(){};

private:

	ClassDef(module,0);
	
};

#endif