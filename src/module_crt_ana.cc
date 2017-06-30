/*
	
	module_crt_ana.cc
	Purpose: Template class for module
	
	@author Alberto Remoto
	@version 1.0 2017-06-28

*/

#define module_crt_ana_cxx

#include "module_crt_ana.h"
#include "plotter.h"

void module_crt_ana::begin(){

	plotter::get_me().add( new TH1F("crt_tof", "CRT Time of flight", 100, -100, 100));
	plotter::get_me().add( new TH2F("crt_n_hits", "CRT number of hits ", 4, 0, 4, 16, 0, 16));
	plotter::get_me().add( new TH1F("crt_n_tot_hits", "CRT number of total hits ", 4*16, 0, 4*16));
};

bool module_crt_ana::process( event * evt){

	plotter::get_me().find("crt_tof")->Fill( evt->get_crt_tof() );

	int n_tot_hits = 0;

	for( int i=0; i<4; i++){
		std::vector<int> hits = evt->get_crt_strip_hits(i,1000);
		plotter::get_me().find("crt_n_hits")->Fill( i , hits.size() );
		
		n_tot_hits += hits.size();
	}

	plotter::get_me().find("crt_n_tot_hits")->Fill( n_tot_hits );
	
	return true;
		
};

void module_crt_ana::terminate(){
	
	//plotter::get_me().find("crt_n_hits")->Scale( 1/n );
	//plotter::get_me().find("crt_n_tot_hits")->Scale( 1/n );

};

