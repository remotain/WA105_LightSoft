#ifndef obj_pulse_h
#define obj_pulse_h

#include <TObject.h>
#include <TChain.h>

class obj_pulse : public TObject {

public:

    obj_pulse(){};
    
	obj_pulse(obj_pulse &) { };
	
    virtual ~obj_pulse() { };

	int get_n_samples(){return _n_samples; };	
	int get_t_start  (){return _t_start;   };
	int get_t_stop   (){return _t_stop;    };
	double get_charge   (){return _charge;    };
	double get_amplitude(){return _amplitude; };

	void set_n_samples( int a_value    ){ _n_samples = a_value; };	
	void set_t_start  ( int a_value    ){ _t_start   = a_value; };
	void set_t_stop   ( int a_value    ){ _t_stop    = a_value; };
	void set_charge   ( double a_value ){ _charge    = a_value; };
	void set_amplitude( double a_value ){ _amplitude = a_value; };

private:
	
	int _n_samples;	
	int _t_start;
	int _t_stop;
	double _charge;
	double _amplitude;
	
ClassDef(obj_pulse,1);
	
};

#endif