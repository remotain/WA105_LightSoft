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
#include <numeric>

void module_plot_dump::begin(){
	
	_n_evt = 0;
	_n_evt_exc = 0;
	
	_t_min = 0;
	_t_max = 0;
	
	//plotter::get_me().add( new TH2F ("overall_waveform_2d", "Overal waveform; Time [ns]; Channel; ADC counts", 1000, 0, 4000, 5, 0, 5) ); 	
	plotter::get_me().add( new TProfile ("overall_waveform_ch0", "Overal waveform ch 0; Time [ns]; ADC counts", 1000, 0, 4000, "i") ); 	
	plotter::get_me().add( new TProfile ("overall_waveform_ch1", "Overal waveform ch 1; Time [ns]; ADC counts", 1000, 0, 4000, "i") ); 	
	plotter::get_me().add( new TProfile ("overall_waveform_ch2", "Overal waveform ch 2; Time [ns]; ADC counts", 1000, 0, 4000, "i") ); 	
	plotter::get_me().add( new TProfile ("overall_waveform_ch3", "Overal waveform ch 3; Time [ns]; ADC counts", 1000, 0, 4000, "i") ); 	
	plotter::get_me().add( new TProfile ("overall_waveform_ch4", "Overal waveform ch 4; Time [ns]; ADC counts", 1000, 0, 4000, "i") ); 				

	plotter::get_me().add( new TH1F ("sum_waveform_ch4", "Sum waveform ch 4; Time [ns]; ADC counts", 1000, 0, 4000) ); 				
	
}

void module_plot_dump::process( event * evt){
	
	if( _t_min == 0 ) _t_min = evt->get_time_stamp();
	
	if( _t_max < evt->get_time_stamp() ) _t_max =  evt->get_time_stamp();
	
	_t.push_back(evt->get_time_stamp() - _t_min);	
	
	for (int ch = 0; ch < evt->get_nchannels(); ch++){
		
		//std::vector<int> * waveform = evt->get_waveform(ch);
		//std::vector<int>::iterator result = std::min_element(waveform->begin()+100, waveform->begin()+200);
		//int dt = std::distance(waveform->begin(), result);
		
		// exclude saturated waveforms
		int min_adc_count = TMath::MinElement( evt->get_waveform(ch)->size() , &evt->get_waveform(ch)->at(0) );
		int max_adc_count = TMath::MaxElement( evt->get_waveform(ch)->size() , &evt->get_waveform(ch)->at(0) );
		if( min_adc_count == 0 || max_adc_count == 4096){
			_n_evt_exc++;
			continue;	
		} 
		
		for (int i = 0; i < evt->get_waveform(ch)->size(); i++ ){
			
			plotter::get_me().find( TString::Format("overall_waveform_ch%i", ch ) )->Fill( i * 4 , evt->get_waveform(ch)->at(i));

			if(ch == 4) {
				plotter::get_me().find( TString::Format("sum_waveform_ch%i", ch ) )->Fill( i * 4 , evt->get_waveform(ch)->at(i));
			}
			
			//plotter::get_me().find2d("overall_waveform_2d")->Fill(i*4, ch, evt->get_waveform(ch)->at(i));
		    //plotter::get_me().find("overall_waveform_1d")->Fill(i*4, evt->get_waveform(ch)->at(i));	
			
			
		}
		
	}
	
	_n_evt++;
		
}

void module_plot_dump::terminate(){
	
	Info("terminate", "Number of evens saturated : %i", _n_evt_exc);
	
	int nbins = (int) ceil((_t_max - _t_min) / 60.);
	
	std::vector<double> w (_t.size(), 1/60.);
	
	plotter::get_me().add( new TH1F ("event_rate", "Event rate; Run time [s]; Events/s", nbins, 0, _t_max-_t_min) ); 	
	
	plotter::get_me().find("event_rate")->FillN(_t.size(), &_t[0], &w[0]);

	//plotter::get_me().find2d("overall_waveform_2d")->Scale(1./(double)_n_evt);
	//plotter::get_me().find("overall_waveform_1d")->Scale(1./(double)_n_evt);

	//plotter::get_me().find( "overall_waveform_ch0" )->Scale( 1./(double)_n_evt );
	//plotter::get_me().find( "overall_waveform_ch1" )->Scale( 1./(double)_n_evt );
	//plotter::get_me().find( "overall_waveform_ch2" )->Scale( 1./(double)_n_evt );
	//plotter::get_me().find( "overall_waveform_ch3" )->Scale( 1./(double)_n_evt );
	//plotter::get_me().find( "overall_waveform_ch4" )->Scale( 1./(double)_n_evt );
	
	plotter::get_me().find( "overall_waveform_ch0" )->GetYaxis()->SetRangeUser(0, 4500);
	plotter::get_me().find( "overall_waveform_ch1" )->GetYaxis()->SetRangeUser(0, 4500);
	plotter::get_me().find( "overall_waveform_ch2" )->GetYaxis()->SetRangeUser(0, 4500);
	plotter::get_me().find( "overall_waveform_ch3" )->GetYaxis()->SetRangeUser(0, 4500);
	plotter::get_me().find( "overall_waveform_ch4" )->GetYaxis()->SetRangeUser(0, 4500);
	
	//plotter::get_me().find("overall_waveform_ch0")->Sumw2();
	//plotter::get_me().find("overall_waveform_ch1")->Sumw2();
	//plotter::get_me().find("overall_waveform_ch2")->Sumw2();
	//plotter::get_me().find("overall_waveform_ch3")->Sumw2();
	//plotter::get_me().find("overall_waveform_ch4")->Sumw2();
	
	
}