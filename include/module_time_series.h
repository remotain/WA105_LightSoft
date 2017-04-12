/*
	
	module_time_series.h
	Purpose: Base class for time_series 
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
*/

#ifndef module_time_series_h
#define module_time_series_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_time_series : public module {

public:

    module_time_series() {
		
	};
	module_time_series(module_time_series &) { };
    virtual ~module_time_series() { };

	virtual void begin();
	virtual void process( event * evt);
	virtual void terminate();

	virtual void push_pool(event * evt ){ _event_pool.push_back(evt); };
	virtual void empty_pool(){ _event_pool.clear(); };
	
	virtual void begin_pool();     // to be redefined 
	virtual void process_pool();   // to be redefined 
	virtual void terminate_pool(); // to be redefined 

	
	virtual void set_pool_minute(){ _t_span = 60; }; // seconds };
	virtual void set_pool_hour(){ _t_span = 60*60; }; // seconds };
	virtual void set_pool_day(){ _t_span = 60*60*24; }; // seconds };	
	
	virtual void set_time_span( int a_value ) { _t_span = a_value; };
	int get_time_span() { return _t_span; };
	
private:
	
	int _t_counter;
	int _t_zero;	
	int _t_span;
	std::vector<event*> _event_pool;
		
	ClassDef(module_time_series,0);
	
};

#endif