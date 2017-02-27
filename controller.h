#include<systemc.h>

SC_MODULE(controller) {

	sc_in <sc_logic> rst, clk;
	sc_signal <sc_logic> rstA, rstB, rstt;
	sc_signal <sc_logic> enCounter;
	sc_signal <sc_logic> rstCounter;
	sc_signal <sc_logic> initCounter;
	sc_signal <sc_logic> done;
	sc_signal <sc_logic> eq, lt;

	sc_in <sc_logic> go;

	enum states { s0, s1, s2, s3 };

	sc_signal <states> p_state, n_state;

	void comb_func();
	void seq_func();

	SC_CTOR(controller) {
		SC_METHOD(comb_func);
		sensitive << go << p_state;
		SC_THREAD(seq_func);
		sensitive << clk.pos() << rst;
	};

};