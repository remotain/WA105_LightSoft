/*

	event.h
	Purpose: Define the interface to interact with the event
		
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: the class define the interface to interact with the event.
	
	The following data member are extracted from the input TChain:
	
	'''
	int _time_stamp        ;
	int _nevent            ;
	int _nchannels         ;
	int _nsamples          ;
	int _time_sample       ;
	int _adc_value_0[1000] ;
	int _adc_value_1[1000] ;
	'''
	
	Datamemeber containing "reco" in their name are obtained from processing 
	throug dedicated module:
	
	'''
	std::vector<double> _reco_pedestals       ;
	std::vector<double> _reco_pedestals_std   ;
	std::vector<double> _reco_charges         ;
	'''
	
	The variable "_nchannels_active" represent the number of active channel 
	to be expected. At the moment is defined in the class constructor but in 
	future it is expected to be defined either globally or by the user
	
	
*/

#ifndef event_h
#define event_h

#include <TObject.h>
#include <TChain.h>

#include <string.h>
#include <vector>

class event : public TObject {

public:

    event(): _chain(0),
		 	 _waveform_0(0),
			 _waveform_1(0),
			 _waveform_2(0),
			 _waveform_3(0),
			 _waveform_4(0),
 			 _waveform_5(0) { 
	
		_nch = 6;
    
		reset();
    
	};
	
	event(event &) { };
	
    virtual ~event() { };

	void init( TTree * tree );
	void reset();
	void assign();
	void set_input_tree( TTree * tree);
	void set_output_tree( TTree * tree);
	
	
	void set_time_stamp  ( int a_value ) { _time_stamp  = a_value ; };
	void set_nevent      ( int a_value ) { _nevent      = a_value ; };
	void set_nchannels   ( int a_value ) { _nchannels   = a_value ; };
	void set_nsamples    ( int a_value ) { _nsamples    = a_value ; };
	void set_time        ( int a_value ) { _time_sample = a_value ; };

	//void set_adc_value_0 ( int * a_value ) { _adc_value_0 = a_value; };
	//void set_adc_value_1 ( int * a_value ) { _adc_value_1 = a_value; };

	bool set_reco_pedestal ( int ch , double a_value ) { 
		// Set reconstructed pedestal value for each channel
		if (ch < _nchannels ) { 
			_reco_pedestals[ch] = a_value; 
			return true;
		} else return false; 
	};
	
	bool set_reco_pedestal_std ( int ch , double a_value ) { 
		// Set reconstructed pedestal standard deviation value for each channel
		if (ch < _nchannels ) { 
			_reco_pedestals_std[ch] = a_value; 
			return true;
		} else return false; 
	};

	bool set_reco_min_adc   ( int ch , double a_value ) {
		// Set reconstructed charge value for each channel 
		if (ch < _nchannels ) { 
			_reco_min_adc[ch] = a_value; 
			return true; 
		} else return false; 
	};

	bool set_reco_min_adc_time  ( int ch , double a_value ) {
		// Set reconstructed charge value for each channel 
		if (ch < _nchannels ) { 
			_reco_min_adc_time[ch] = a_value; 
			return true; 
		} else return false; 
	};

	
	bool set_reco_charge   ( int ch , double a_value ) {
		// Set reconstructed charge value for each channel 
		if (ch < _nchannels ) { 
			_reco_charges[ch] = a_value; 
			return true; 
		} else return false; 
	};

	bool set_reco_n_peaks   ( int ch , double a_value ) {
		// Set reconstructed charge value for each channel 
		if (ch < _nchannels ) { 
			_reco_n_peaks[ch] = a_value; 
			return true; 
		} else return false; 
	};

	
	void set_reco_total_charge (double a_value ) { _reco_total_charge = a_value; };

	TTree * get_chain() {return _chain; };

	int              get_n_channels_active() { return _nch; };
	
	int              get_time_stamp  ( ) { return _time_stamp   ; };
	int              get_nevent      ( ) { return _nevent       ; };
	int              get_nchannels   ( ) { return _nchannels    ; };
	int              get_nsamples    ( ) { return _nsamples     ; };
	int              get_time_sample ( ) { return _time_sample  ; }; // s

	int              get_crt_daq_match()      { return _crt_daq_match;                     };
	int              get_crt_reco()           { return _crt_reco;                          };

	float            get_crt_tof_H1V1()       { return _crt_tof_H1V1;                      };
	float            get_crt_tof_H2V2()       { return _crt_tof_H2V2;                      };	
	float            get_crt_tof()            { return _crt_tof;                           };

	int   *          get_crt_adc( int plane ) { return (plane < 4) ? _crt_adc[plane] : 0 ; };
	
	float *          get_crt_track_param()    { return _crt_track_param;                   };
	int   *          get_crt_track_time()     { return _crt_track_time;                    };
	float *          get_crt_track_pos0()     { return _crt_track_pos0;                    };
	float *          get_crt_track_pos1()     { return _crt_track_pos1;                    };


	std::vector<int>  get_crt_channel_hits( int plane , double threshold = 1000);
	std::vector<int>  get_crt_strip_hits( int plane , double threshold = 1000);

	std::vector<int> * get_waveform ( int ch );

	double           get_reco_pedestal     ( int ch) { return (ch < _nch ) ? _reco_pedestals[ch]     : -1 ; };
	double           get_reco_pedestal_std ( int ch) { return (ch < _nch ) ? _reco_pedestals_std[ch] : -1 ; };
	double           get_reco_min_adc      ( int ch) { return (ch < _nch ) ? _reco_min_adc[ch]       : -1 ; };
	double           get_reco_min_adc_time ( int ch) { return (ch < _nch ) ? _reco_min_adc_time[ch]  : -1 ; };	
	double           get_reco_charge       ( int ch) { return (ch < _nch ) ? _reco_charges[ch]       : -1 ; };
	double           get_reco_n_peaks      ( int ch) { return (ch < _nch ) ? _reco_n_peaks[ch]       : -1 ; };
	double           get_reco_total_charge (       ) { return _reco_total_charge; };
	
private:
	
	TTree              *_chain;
	
	int              _nch ;
	
	int              _time_stamp       ;
    int              _nevent           ;
    int              _nchannels        ;
    int              _nsamples         ;
    int              _time_sample      ;

	int				 _crt_daq_match     ;
	int              _crt_reco           ;
	int              _crt_adc[4][32]     ;
	float            _crt_track_param[2] ;
	int              _crt_track_time[2]  ;
	float            _crt_track_pos0[3]  ;
	float            _crt_track_pos1[3]  ;	
	float 			 _crt_tof_H1V1;
	float 			 _crt_tof_H2V2;
	float			 _crt_tof;

    int              _adc_value_0[300000];
    int              _adc_value_1[300000];
    int              _adc_value_2[300000];
    int              _adc_value_3[300000];
    int              _adc_value_4[300000];
    int              _adc_value_5[300000];	


	std::vector<int>      *_waveform_0;
	std::vector<int>      *_waveform_1;
	std::vector<int>      *_waveform_2;
	std::vector<int>      *_waveform_3;
	std::vector<int>      *_waveform_4;
	std::vector<int>      *_waveform_5;

	//std::vector< * std::vector<int> > _waveform;

	std::vector<double>   _reco_pedestals       ;
	std::vector<double>   _reco_pedestals_std   ;
	std::vector<double>   _reco_charges         ;
	
	std::vector<double>   _reco_min_adc         ;
	std::vector<double>   _reco_min_adc_time    ;
		
	std::vector<double>   _reco_n_peaks         ;

	double _reco_total_charge;

    // List of branches
    TBranch *_b_time_stamp;   //! Input branch
    TBranch *_b_event;        //! Input branch
    TBranch *_b_nchannels;    //! Input branch
    TBranch *_b_nsamples;     //! Input branch
    TBranch *_b_time_sample;  //! Input branch
    TBranch *_b_crt_daq_match;//! Input branch
	TBranch *_b_crt_reco;
	TBranch *_b_crt_adc;
	TBranch *_b_crt_track_param;
	TBranch *_b_crt_track_time;
	TBranch *_b_crt_track_pos0;
	TBranch *_b_crt_track_pos1;
    TBranch *_b_crt_tof_H1V1;
    TBranch *_b_crt_tof_H2V2;
    TBranch *_b_crt_tof;
    TBranch *_b_adc_value_0;  //! Input branch
    TBranch *_b_adc_value_1;  //! Input branch
    TBranch *_b_adc_value_2;  //! Input branch
    TBranch *_b_adc_value_3;  //! Input branch
    TBranch *_b_adc_value_4;  //! Input branch
    TBranch *_b_adc_value_5;  //! Input branch	
	TBranch *_b_waveform_0;          
	TBranch *_b_waveform_1;          
	TBranch *_b_waveform_2;          
	TBranch *_b_waveform_3;          
	TBranch *_b_waveform_4;          
	TBranch *_b_waveform_5;          
	TBranch *_b_reco_pedestals;      
	TBranch *_b_reco_pedestals_std;  
	TBranch *_b_reco_charges;        
	TBranch *_b_reco_min_adc;        
	TBranch *_b_reco_min_adc_time;        
	TBranch *_b_reco_n_peaks;        
	
	
	
	
ClassDef(event,1);
	
};

#endif