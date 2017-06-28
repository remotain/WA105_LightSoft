/*
	
	module_template.h
	Purpose: Template class for module
	
	@author Alberto Remoto
	@version 1.0 2017-06-28
	
*/

#ifndef module_template_h
#define module_template_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_template : public module {

public:

    module_template() {	};
	module_template(module_template &) { };
    
	virtual ~module_template() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();
	
private:

	ClassDef(module_template,0);
	
};

#endif