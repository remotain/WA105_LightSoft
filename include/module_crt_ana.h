/*
	
	module_crt_ana.h
	Purpose: Template class for module
	
	@author Alberto Remoto
	@version 1.0 2017-06-28
	
*/

#ifndef module_crt_ana_h
#define module_crt_ana_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_crt_ana : public module {

public:

    module_crt_ana() {	};
	module_crt_ana(module_crt_ana &) { };
    
	virtual ~module_crt_ana() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();
	
private:

	ClassDef(module_crt_ana,0);
	
};

#endif
