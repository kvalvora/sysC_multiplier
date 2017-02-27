#include <systemc.h>

template <int T> SC_MODULE (Adder){
	sc_in <sc_lv<T> > in1, in2; 
	sc_out < sc_lv<T> > out; 
	
	SC_CTOR (Adder){
		SC_METHOD(Adding); 
		sensitive << in1 << in2;
	}
	void Adding(){

		//cout << " in ADD" << in1 <<"  " << in2 <<endl; 
		sc_lv<T> vout; 
		vout = (sc_uint<T>) in1 + (sc_uint<T>) in2; 
		
		//co = vout[T]; 
		out = vout; 
		//cout << " in ADD" << in1 <<" + " << in2 << " = "<< vout << endl; 
	}
};