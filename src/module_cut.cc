/*
	
	module_cut.cc
	Purpose: Base class for cut calculation
	
	@author Alberto Remoto
	@version 1.0 
*/

#define module_cut_cxx

#include "module_cut.h"
#include "plotter.h"

#include <iostream>
#include <algorithm>
#include <numeric> 

#include <TSystem.h>
#include <TTimer.h>
#include <TCanvas.h>
#include <TMath.h>

void module_cut::begin(){
		
};

bool module_cut::process( event * evt){
	
	
	if( _cut_crt_time_stamp ){
		
		if( evt->get_time_stamp() < _time_stamp_start || evt->get_time_stamp() > _time_stamp_stop){
			
			return false;
			
		}
		
	}
	
    if ( _cut_crt_reco && evt->get_crt_reco() == 0 ) {
    	
		_counter_crt_reco++;
		return false;
		
    }
		
	if( _cut_pmt_saturate ){
		
		for (int ch = 0; ch < evt->get_nchannels(); ch++){
				
			if( TMath::MinElement( evt->get_waveform(ch)->size() , &evt->get_waveform(ch)->at(0) ) == 0 || 
				TMath::MaxElement( evt->get_waveform(ch)->size() , &evt->get_waveform(ch)->at(0) ) == 4096){
				
				_counter_pmt_saturate++;
				return false;	
			} 
		
		}
	}
	
	if ( _cut_pmt_peak_t ){
		
		if( _pmt_peak_t_min != -1 && _pmt_peak_t_max != -1 ){
		
			if( evt->get_reco_min_adc_time(0) < _pmt_peak_t_min || evt->get_reco_min_adc_time(0) > _pmt_peak_t_max ||
			    evt->get_reco_min_adc_time(1) < _pmt_peak_t_min || evt->get_reco_min_adc_time(1) > _pmt_peak_t_max ||
				evt->get_reco_min_adc_time(2) < _pmt_peak_t_min || evt->get_reco_min_adc_time(2) > _pmt_peak_t_max ||
				evt->get_reco_min_adc_time(3) < _pmt_peak_t_min || evt->get_reco_min_adc_time(3) > _pmt_peak_t_max ||
				evt->get_reco_min_adc_time(4) < _pmt_peak_t_min || evt->get_reco_min_adc_time(4) > _pmt_peak_t_max ){
				
				_counter_pmt_peak++;
				return false;
				
			} 
		}
	}
	
    if ( _cut_crt_delta_t ){ 
		
		double dt = evt->get_crt_track_time()[1] -  evt->get_crt_track_time()[0];
    	
		if( dt < _crt_delta_t_min || dt > _crt_delta_t_max ){
		
			return false;
		}
		
    }
	
    if ( _cut_crt_track ){ 
    	
		if( _crt_track_angle_min != -1 && _crt_track_angle_max != -1 ){
		
			if( evt->get_crt_track_param()[1] < _crt_track_angle_min ||  evt->get_crt_track_param()[1] > _crt_track_angle_max ){
				
				return false;
				
			}
		
		} 
		
		if( _crt_track_z_min != -1 && _crt_track_z_max != -1 ){
		
			if( evt->get_crt_track_param()[0] < _crt_track_z_min ||  evt->get_crt_track_param()[0] > _crt_track_z_max ){
				
				return false;
		
			}
		
		
		}
	
	}

	
	return true;
		
};

void module_cut::terminate(){

	Info("terminate()", "# CRT match    : %d", _counter_crt_match   );
	Info("terminate()", "# CRT reco     : %d", _counter_crt_reco    );		
	Info("terminate()", "# PMT saturate : %d", _counter_pmt_saturate);
	Info("terminate()", "# PMT peak     : %d", _counter_pmt_peak    );
	
};

