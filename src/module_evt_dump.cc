#define module_evt_dump_cxx

#include "module_evt_dump.h"
#include <iostream>

void module_evt_dump::begin(){

}

void module_evt_dump::process( event * evt){
	
	std::cout << "Dump event number: " << evt->get_nevent() << std::endl;
	std::cout << "" << std::endl;
	std::cout << "\t Time stamp       : " << evt->get_time_stamp()  << std::endl; 
	std::cout << "\t Num. of channels : " << evt->get_nchannels()   << std::endl; 
	std::cout << "\t Num. of samples  : " << evt->get_nsamples()    << std::endl; 
	std::cout << "\t Sample frequency : " << evt->get_time_sample() << std::endl; 
	std::cout << "" << std::endl;			
	std::cout << "\t Waveform ch0 : " << evt->get_waveform(0) << std::endl;  
	std::cout << "\t pedestal     : " << evt->get_reco_pedestal(0) << "+/-" << evt->get_reco_pedestal_std(0) << std::endl;  
	std::cout << "\t charge       : " << evt->get_reco_charge(0) << std::endl;  
	std::cout << "" << std::endl;			
	std::cout << "\t Waveform ch1 : " << evt->get_waveform(1) << std::endl;  
	std::cout << "\t pedestal     : " << evt->get_reco_pedestal(1) << "+/-" << evt->get_reco_pedestal_std(1) << std::endl;  
	std::cout << "\t charge       : " << evt->get_reco_charge(1) << std::endl;  
		
}

void module_evt_dump::terminate(){;}