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

#include <vector>

class event : public TObject {

public:

    event(): _chain(0),
		 	 _waveform_0(0),
			 _waveform_1(0),
			 _waveform_2(0),
			 _waveform_3(0),
			 _waveform_4(0) { 
	
		_nchannels_active = 2;
    
		reset();
    
	};
	
	event(event &) { };
	
    virtual ~event() { };

	void init( TTree * tree );
	void reset();
	void assign();

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
	
	bool set_reco_charge   ( int ch , double a_value ) {
		// Set reconstructed charge value for each channel 
		if (ch < _nchannels ) { 
			_reco_charges[ch] = a_value; 
			return true; 
		} else return false; 
	};

	TTree * get_chain() {return _chain; };

	int              get_n_channels_active() { return _nchannels_active; };
	
	int              get_time_stamp  ( ) { return _time_stamp   ; };
	int              get_nevent      ( ) { return _nevent       ; };
	int              get_nchannels   ( ) { return _nchannels    ; };
	int              get_nsamples    ( ) { return _nsamples     ; };
	int              get_time_sample ( ) { return _time_sample  ; };

	int*             get_adc_value_0 ( ) { return _adc_value_0  ; };
	int*             get_adc_value_1 ( ) { return _adc_value_1  ; };
	int*             get_adc_value_2 ( ) { return _adc_value_2  ; };
	int*             get_adc_value_3 ( ) { return _adc_value_3  ; };
	int*             get_adc_value_4 ( ) { return _adc_value_4  ; };

	std::vector<int> * get_waveform ( int ch );

	double           get_reco_pedestal     ( int ch ) { return (ch < _nchannels_active ) ? _reco_pedestals[ch]     : -1 ; };
	double           get_reco_pedestal_std ( int ch ) { return (ch < _nchannels_active ) ? _reco_pedestals_std[ch] : -1 ; };
	double           get_reco_charge       ( int ch ) { return (ch < _nchannels_active ) ? _reco_charges[ch]       : -1 ; };

private:
	
	TTree              *_chain;
	
	int              _nchannels_active ;
	
	int              _time_stamp       ;
    int              _nevent           ;
    int              _nchannels        ;
    int              _nsamples         ;
    int              _time_sample      ;

    int              _adc_value_0[1000];
    int              _adc_value_1[1000];
    int              _adc_value_2[1000];
    int              _adc_value_3[1000];
    int              _adc_value_4[1000];

	std::vector<int>      *_waveform_0;
	std::vector<int>      *_waveform_1;
	std::vector<int>      *_waveform_2;
	std::vector<int>      *_waveform_3;
	std::vector<int>      *_waveform_4;

	//std::vector< * std::vector<int> > _waveform;

	std::vector<double>   _reco_pedestals       ;
	std::vector<double>   _reco_pedestals_std   ;
	std::vector<double>   _reco_charges         ;

    // List of branches
    TBranch            *_b_time_stamp;   //! Input branch
    TBranch            *_b_event;        //! Input branch
    TBranch            *_b_nchannels;    //! Input branch
    TBranch            *_b_nsamples;     //! Input branch
    TBranch            *_b_time_sample;  //! Input branch
    TBranch            *_b_adc_value_0;  //! Input branch
    TBranch            *_b_adc_value_1;  //! Input branch
    TBranch            *_b_adc_value_2;  //! Input branch
    TBranch            *_b_adc_value_3;  //! Input branch
    TBranch            *_b_adc_value_4;  //! Input branch
	
ClassDef(event,1);
	
};

#endif