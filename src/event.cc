/*
	
	event.cc
	Purpose: Define the interface to interact with the event
	
	@author Alberto Remoto
	@version 1.0 2017-02-03
	
	Description: the class define the interface to interact with the event.
	
*/ 

#define event_cxx

#include "event.h"

ClassImp(event)

void event::init( TTree * tree ) {	
	
	// Connect the class branches to the tree to automatically retrieve and set 
	// the data members. This function is called each time the loop needs to 
	// initialize a new tree or chain.

	set_input_tree( tree);

}

void event::set_input_tree( TTree * tree){
	
	_chain = tree;
	
	_chain->SetMakeClass(1);
	
	if( strcmp(tree->GetName(), "midas_data") == 0 ){
	
		_chain->SetBranchAddress("TimeStamp"     , &_time_stamp    , &_b_time_stamp  );
		_chain->SetBranchAddress("event"         , &_nevent        , &_b_event       );
		_chain->SetBranchAddress("nchannels"     , &_nchannels     , &_b_nchannels   );
		_chain->SetBranchAddress("nsamples"      , &_nsamples      , &_b_nsamples    );
		_chain->SetBranchAddress("TimeSample"    , &_time_sample   , &_b_time_sample );
		_chain->SetBranchAddress("crt_daq_match" , &_crt_daq_match , &_b_crt_daq_match );
		_chain->SetBranchAddress("adc_value_0"   , _adc_value_0    , &_b_adc_value_0 );
		_chain->SetBranchAddress("adc_value_1"   , _adc_value_1    , &_b_adc_value_1 );
		_chain->SetBranchAddress("adc_value_2"   , _adc_value_2    , &_b_adc_value_2 );
		_chain->SetBranchAddress("adc_value_3"   , _adc_value_3    , &_b_adc_value_3 );
		_chain->SetBranchAddress("adc_value_4"   , _adc_value_4    , &_b_adc_value_4 );
		_chain->SetBranchAddress("adc_value_5"   , _adc_value_5    , &_b_adc_value_5 );

	} else if ( strcmp( tree->GetName(), "reco_data") == 0 ){

		Warning("set_input_tree", "Input the reco_data tree has not been tested yet!");
		
		_chain->SetBranchAddress("_time_stamp"          , &_time_stamp         , &_b_time_stamp          );
		_chain->SetBranchAddress("nevent"               , &_nevent             , &_b_event               );
		_chain->SetBranchAddress("_nsamples"            , &_nsamples           , &_b_nsamples            );
		_chain->SetBranchAddress("_time_sample"         , &_time_sample        , &_b_time_sample         );
		_chain->SetBranchAddress("_crt_daq_match"       , &_crt_daq_match      , &_b_crt_daq_match       );
		_chain->SetBranchAddress( "_waveform_0"         , _waveform_0          , &_b_waveform_0          );
		_chain->SetBranchAddress( "_waveform_1"         , _waveform_1          , &_b_waveform_1          );
		_chain->SetBranchAddress( "_waveform_2"         , _waveform_2          , &_b_waveform_2          );
		_chain->SetBranchAddress( "_waveform_3"         , _waveform_3          , &_b_waveform_3          );
		_chain->SetBranchAddress( "_waveform_4"         , _waveform_4          , &_b_waveform_4          );
		_chain->SetBranchAddress( "_waveform_5"         , _waveform_5          , &_b_waveform_5          );
		_chain->SetBranchAddress( "_reco_pedestals"     , &_reco_pedestals     , &_b_reco_pedestals      );
		_chain->SetBranchAddress( "_reco_pedestals_std" , &_reco_pedestals_std , &_b_reco_pedestals_std  );
		_chain->SetBranchAddress( "_reco_min_adc"       , &_reco_min_adc       , &_b_reco_min_adc        );
		_chain->SetBranchAddress( "_reco_min_adc_time"  , &_reco_min_adc_time  , &_b_reco_min_adc_time   );
		_chain->SetBranchAddress( "_reco_charges"       , &_reco_charges       , &_b_reco_charges        );	
		_chain->SetBranchAddress( "_reco_n_peaks"       , &_reco_n_peaks       , &_b_reco_n_peaks        );	
		
	} else {
		
		Fatal("set_input_tree", "Input tree not recognized: %s", tree->GetName() );
		
	}
	
}

void event::set_output_tree( TTree * tree){
	
	tree->Branch( "_time_stamp"         , &_time_stamp         , "_time_stamp/I"         );
	tree->Branch( "_nevent"             , &_nevent             , "_nevent/I"             );
	tree->Branch( "_nsamples"           , &_nsamples           , "_nsamples/I"           );
	tree->Branch( "_time_sample"        , &_time_sample        , "_time_sample/I"        );
	tree->Branch( "_crt_daq_match"      , &_crt_daq_match      , "_crt_daq_match/I"      );

	tree->Branch( "_waveform_0"         , "std::vector<int>"    , &_waveform_0          );
	tree->Branch( "_waveform_1"         , "std::vector<int>"    , &_waveform_1          );
	tree->Branch( "_waveform_2"         , "std::vector<int>"    , &_waveform_2          );
	tree->Branch( "_waveform_3"         , "std::vector<int>"    , &_waveform_3          );
	tree->Branch( "_waveform_4"         , "std::vector<int>"    , &_waveform_4          );
	tree->Branch( "_waveform_5"         , "std::vector<int>"    , &_waveform_5          );	
	tree->Branch( "_reco_pedestals"     , "std::vector<double>" , &_reco_pedestals      );
	tree->Branch( "_reco_pedestals_std" , "std::vector<double>" , &_reco_pedestals_std  );
	tree->Branch( "_reco_min_adc"       , "std::vector<double>" , &_reco_min_adc        );
	tree->Branch( "_reco_min_adc_time"  , "std::vector<double>" , &_reco_min_adc_time   );
	tree->Branch( "_reco_charges"       , "std::vector<double>" , &_reco_charges        );	
	tree->Branch( "_reco_n_peaks"       , "std::vector<double>" , &_reco_n_peaks        );	
		
}

void event::reset(){
	
	// Clean vectors and pointer
	
	delete _waveform_0; _waveform_0 = 0;
	delete _waveform_1; _waveform_1 = 0;
	delete _waveform_2; _waveform_2 = 0;
	delete _waveform_3; _waveform_3 = 0;
	delete _waveform_4; _waveform_4 = 0;
	delete _waveform_5; _waveform_5 = 0;	
	
	_reco_pedestals.assign(_nch,-1.); 
	_reco_pedestals_std.assign(_nch,-1.); 
    _reco_min_adc.assign(_nch,-1.); 
    _reco_min_adc_time.assign(_nch,-1.); 
    _reco_charges.assign(_nch, -1.);   
    _reco_n_peaks.assign(_nch, -1.);   
	
}

void event::assign(){
	
	// Assign the pointers for the new event
	
	reset();
	
	// Map the FADC channel to the PMT number
	//
	// FADC ch # PMT number
	//    0    #     1
	//    1    #     2
	//    2    #     3   
	//    3    #     4  
	//    4    #     5  
	//    5    #   empty 
	//    6    #   empty
	//    7    #   empty
	//    8    #   empty
	//
	_waveform_0 = new std::vector<int>( _adc_value_0 , &_adc_value_0[_nsamples-1] ) ;
	_waveform_1 = new std::vector<int>( _adc_value_1 , &_adc_value_1[_nsamples-1] ) ;
	_waveform_2 = new std::vector<int>( _adc_value_2 , &_adc_value_2[_nsamples-1] ) ;
	_waveform_3 = new std::vector<int>( _adc_value_3 , &_adc_value_3[_nsamples-1] ) ;
	_waveform_4 = new std::vector<int>( _adc_value_4 , &_adc_value_4[_nsamples-1] ) ;
	_waveform_5 = new std::vector<int>( _adc_value_5 , &_adc_value_5[_nsamples-1] ) ;

}

std::vector<int> * event::get_waveform( int ch ){
	
	// Return a pointer to the waveform of a given channel. If the pointer is not
	// yet defined, the function create it before returning.
	
	if      ( ch == 0) return _waveform_0 ;
	else if ( ch == 1) return _waveform_1 ;
	else if ( ch == 2) return _waveform_2 ;
	else if ( ch == 3) return _waveform_3 ;
	else if ( ch == 4) return _waveform_4 ;
	else if ( ch == 5) return _waveform_5 ;
	
	return 0; 

}
