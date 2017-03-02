/*
	
	module_plot_dump.cc
	Purpose: Base class to dump some plot
	
	@author Alberto Remoto
	@version 1.0 2017-03-02
	
	Description: the module dump plot in the plotter singelton
	
*/


#define module_plot_dump_cxx

#include "module_plot_dump.h"
#include "plotter.h"
#include <iostream>

void module_plot_dump::begin(){
	
	_n_evt = 0;
	
	_t_min = 0;
	_t_max = 0;
	
}

void module_plot_dump::process( event * evt){
	
	if( _t_min == 0 ) _t_min = evt->get_time_stamp();
	
	if( _t_max < evt->get_time_stamp() ) _t_max =  evt->get_time_stamp();
	
	_t.push_back(evt->get_time_stamp() - _t_min);
	
	_n_evt++;
		
}

void module_plot_dump::terminate(){
	
	int nbins = (int) ceil((_t_max - _t_min) / 60.);
	
	std::vector<double> w (_t.size(), 1/60.);
	
	plotter::get_me().add( new TH1F ("event_rate", "Event rate; Run time [s]; Events/s", nbins, 0, _t_max-_t_min) ); 	
	
	plotter::get_me().find("event_rate")->FillN(_t.size(), &_t[0], &w[0]);
	
}