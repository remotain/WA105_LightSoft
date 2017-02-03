/**
	
	module.h
	Purpose: Define the base module class
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: the class define the base module class to process events
	User module should inherit from this class and implement algorithm or action 
	to be perfomed on the events. 
	
	The class provide the following function:
	
	begin(): Called at the begin of the event loop. This function should be used
	to initiate the algorithm to be run on the events.
	
	process(event * evt): Called for each event in the event loop. This function 
	should be used to run the algorithm on the current event.
	
	terminate(): Called at the end of the event loop. This function should be used 
	to finilaze the algorithm or the processing of the module.
	
**/

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
	virtual void process( event * evt) {};
	virtual void terminate(){};

private:

	ClassDef(module,0);
	
};

#endif