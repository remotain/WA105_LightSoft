#ifndef event_h
#define event_h

#include <TObject.h>
#include <TChain.h>

#include <vector>

class event : public TObject {

public:

    event(): _chain(0) { 
	
		_nchannels_active = 2;

		clean();

	};
	event(event &) { };
    virtual ~event() { };

	//void set_time_stamp  ( int a_value ) { _time_stamp  = a_value ; };
	//void set_nevent      ( int a_value ) { _nevent      = a_value ; };
	//void set_nchannels   ( int a_value ) { _nchannels   = a_value ; };
	//void set_nsamples    ( int a_value ) { _nsamples    = a_value ; };
	//void set_time        ( int a_value ) { _time_sample = a_value ; };
	//void set_adc_value_0 ( int * a_value ) { _adc_value_0 = a_value; };
	//void set_adc_value_1 ( int * a_value ) { _adc_value_1 = a_value; };

	void init( TTree * tree ) 
	{	
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

	bool set_pedestal ( int ch , double a_value ) { 
		if (ch < _nchannels ) { 
			_reco_pedestals[ch] = a_value; 
			return true;
		} else return false; 
	};
	bool set_charge   ( int ch , double a_value ) { 
		if (ch < _nchannels ) { 
			_reco_charges[ch] = a_value; 
			return true; 
		} else return false; 
	};

	bool clean(){
		
		_time_stamp        = -1;
		_nevent            = -1;
		_nchannels         = -1;
		_nsamples          = -1;
		_time_sample       = -1;
		
		_reco_pedestals.assign(_nchannels_active,-1.); 
	    _reco_charges.assign(_nchannels_active, -1.);   
		
	}

	TTree * get_chain() {return _chain; };
	
	int              get_time_stamp  ( ) { return _time_stamp   ; };
	int              get_nevent      ( ) { return _nevent       ; };
	int              get_nchannels   ( ) { return _nchannels    ; };
	int              get_nsamples    ( ) { return _nsamples     ; };
	int              get_time_sample ( ) { return _time_sample  ; };
	int*             get_adc_value_0 ( ) { return _adc_value_0  ; };
	int*             get_adc_value_1 ( ) { return _adc_value_1  ; };

	double           get_pedestal ( int ch ) { return (ch < _nchannels ) ? _reco_pedestals[ch] : -1 ; };
	double           get_charge   ( int ch ) { return (ch < _nchannels ) ? _reco_charges[ch]   : -1 ; };

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

	std::vector<double>   _reco_pedestals   ;
	std::vector<double>   _reco_charges     ;

    // List of branches
    TBranch            *_b_time_stamp;   //!
    TBranch            *_b_event;       //!
    TBranch            *_b_nchannels;   //!
    TBranch            *_b_nsamples;    //!
    TBranch            *_b_time_sample;  //!
    TBranch            *_b_adc_value_0; //!
    TBranch            *_b_adc_value_1; //!
	

ClassDef(event,0);
	
};

#endif