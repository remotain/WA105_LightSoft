/*
	
	module_cut.h
	Purpose: Base class for cut calculation
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
*/

#ifndef module_cut_h
#define module_cut_h

#include <TObject.h>

#include "module.h"
#include "event.h"

class module_cut : public module {

public:

    module_cut() {	

		_cut_pmt_saturate = false;
		_cut_pmt_peak_t   = false;
		
		_cut_crt_match    = false;
		_cut_crt_reco     = false;
		_cut_crt_delta_t  = false;
		_cut_crt_track    = false;	
		
		_cut_crt_time_stamp   = false;	
		
		_pmt_peak_t_min       = -1.;
		_pmt_peak_t_max       = -1.;
		
		_crt_delta_t_min      = -1.;
		_crt_delta_t_max      = -1.;

		_crt_track_angle_min  = -1.;
		_crt_track_angle_max  = -1.;		

		_crt_track_z_min      = -1.;
		_crt_track_z_max      = -1.;
		
		_counter_pmt_saturate = 0;
		_counter_pmt_peak     = 0;
		_counter_crt_match    = 0;
		_counter_crt_reco     = 0;
		
		_time_stamp_start = -1;
		_time_stamp_stop  = -1;

			
	};
	
	module_cut(module_cut &) { };
    
	virtual ~module_cut() { };

	virtual void begin();
	virtual bool process( event * evt);
	virtual void terminate();	
	
	void set_cut_pmt_saturate( bool set = true ) { _cut_pmt_saturate = set; };

	void set_cut_pmt_peak_t( double min = 400., double max = 700. ) { 
		_cut_pmt_peak_t = true;
		_pmt_peak_t_min = min;
		_pmt_peak_t_max = max;
	};

	void set_cut_crt_match   ( bool set = true ) { _cut_crt_match    = set; };

	void set_cut_crt_reco    ( bool set = true ) { _cut_crt_reco     = set; };	

	void set_cut_time_stamp( double start = -1, double stop = -1) {
		
		_cut_crt_time_stamp = true;	
		
		_time_stamp_start = start;
		_time_stamp_stop  = stop;
		
	}

	void set_cut_crt_delta_t ( double min = 100., double max = 130.) { 
		_cut_crt_delta_t = true; 
		_crt_delta_t_min = min; 
		_crt_delta_t_max = max; 
	};

	void set_cut_crt_track_angle ( double min = -1., double max = -1.) { 
		_cut_crt_track       = true; 
		_crt_track_angle_min = min; 
		_crt_track_angle_max = max; 
	};

	void set_cut_crt_track_z ( double min = -1., double max = -1.) { 
		_cut_crt_track     = true; 
		_crt_track_z_min = min; 
		_crt_track_z_max = max; 
	};



private:

	bool _cut_pmt_saturate ;
	bool _cut_pmt_peak_t   ;
	bool _cut_crt_match    ;
    bool _cut_crt_reco     ;
    bool _cut_crt_delta_t  ;
    bool _cut_crt_track    ;
	bool _cut_crt_time_stamp;

	double _pmt_peak_t_min ;
	double _pmt_peak_t_max ;

	double _crt_delta_t_min;
	double _crt_delta_t_max;
	
	double _crt_track_angle_min;
	double _crt_track_angle_max;

	double _crt_track_z_min    ;
	double _crt_track_z_max    ;
		
	
	int _counter_pmt_saturate ;
	int _counter_pmt_peak ;
	int _counter_crt_match    ;
    int _counter_crt_reco     ;

	int _time_stamp_start;
	int _time_stamp_stop;

		  
	ClassDef(module_cut,0);
	
};

#endif