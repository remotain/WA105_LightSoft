/*
	
	event.h
	Purpose: Define the interface to interact with the event
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: the class define the interface to interact with the event.
	
*/ 

#define event_cxx

#include "event.h"

void event::init( TTree * tree ) {	
	
	// Connect the class branches to the tree to automatically retrieve and set 
	// the data members. This function is called each time the loop needs to 
	// initialize a new tree or chain.
	
	_chain = tree;
	
	_chain->SetMakeClass(1);
	
	_chain->SetBranchAddress("TimeStamp"   , &_time_stamp  , &_b_time_stamp  );
	_chain->SetBranchAddress("event"       , &_nevent      , &_b_event       );
	_chain->SetBranchAddress("nchannels"   , &_nchannels   , &_b_nchannels   );
	_chain->SetBranchAddress("nsamples"    , &_nsamples    , &_b_nsamples    );
	_chain->SetBranchAddress("TimeSample"  , &_time_sample , &_b_time_sample );
	_chain->SetBranchAddress("adc_value_0" , _adc_value_0  , &_b_adc_value_0 );
	_chain->SetBranchAddress("adc_value_1" , _adc_value_1  , &_b_adc_value_1 );

}


void event::clean(){
	
	// Clean all the data member of the current events
	
	_time_stamp        = -1;
	_nevent            = -1;
	_nchannels         = -1;
	_nsamples          = -1;
	_time_sample       = -1;
	
	delete _waveform_0; _waveform_0 = 0;
	delete _waveform_1; _waveform_1 = 0;
	
	_reco_pedestals.assign(_nchannels_active,-1.); 
	_reco_pedestals_std.assign(_nchannels_active,-1.); 
    _reco_charges.assign(_nchannels_active, -1.);   
	
}

std::vector<int> * event::get_waveform( int ch ){
	
	// Return a pointer to the waveform of a given channel. If the pointer is not
	// yet defined, the function create it before returning.
	
	if ( ch == 0) {
		if ( _waveform_0 == 0 ){
			_waveform_0 = new std::vector<int>( _adc_value_0 , std::end(_adc_value_0) ) ;
		} return _waveform_0 ;
	}
	else if ( ch == 1) {      
		if ( _waveform_1 == 0 ){
			_waveform_1 = new std::vector<int>( _adc_value_1 , std::end(_adc_value_1) ) ;
		} return _waveform_1 ;
	}
	return 0; 

}