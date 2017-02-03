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
	virtual void process( event * evt);
	virtual void terminate();

	virtual double avg_ped_value( std::vector<int> * waveform);
	virtual double std_ped_value( std::vector<int> * waveform);

private:

	int _nsample;

	ClassDef(module_pedestal,0);
	
};

#endif