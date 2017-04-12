/*
	
	module_time_series.cc
	Purpose: Base class for time_series calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: 
	
*/

#define module_time_series_cxx

#include "module_time_series.h"
#include "plotter.h"

#include <TMath.h>

#include <iostream>
#include <algorithm>
#include <numeric> 


void module_time_series::begin(){

	_t_zero = 0;
	_t_counter = 0;
	
	begin_pool();
	
};

void module_time_series::process( event * evt){	
	
	if( _t_zero == 0 ) _t_zero = evt->get_time_stamp();
	
	if( evt->get_time_stamp() - _t_zero < _t_span){
		
		push_pool( evt );
		
	} else {
		
		process_pool();
		empty_pool();
		
		_t_zero = evt->get_time_stamp();
		_t_counter = 0;
		
	}
	
	
};

void module_time_series::terminate(){
	
	terminate_pool();
	
};

void module_time_series::begin_pool(){

	TGraph * _g_rate = new TGraph ();
	_g_rate->SetName("event_rate");
	_g_rate->SetTitle("Event Rate; Run Time; Event Rate "); 

	plotter::get_me().add( _g_rate ); 

}

void module_time_series::terminate_pool(){

}


void module_time_series::process_pool(){

	int tmp = 0;

    for (std::vector<event*>::iterator evt = _event_pool.begin() ; evt != _event_pool.end(); ++evt){
    	
		tmp++;
		
    }
	
	plotter::get_me().findGraph("event_rate")->SetPoint(_t_counter, _t_zero, tmp);
	std::cout<<_t_zero << " "<<tmp<<std::endl;
 
	
};