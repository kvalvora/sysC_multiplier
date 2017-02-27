#include"mulDesign.h"

SC_MODULE(mulTB) {

	sc_signal <sc_logic> rst, clk, start;
	sc_signal <sc_logic> done;
	sc_signal <sc_lv<8>> result;
	sc_signal <sc_lv<8>> a_in, b_in;
	sc_signal <sc_lv<8>> a_out, b_out;
	sc_signal <sc_logic> go;

	mul* mul1;

	SC_CTOR(mulTB) {
		mul1 = new mul("multiplier1");
		mul1->rst(rst);
		mul1->clk(clk);
		mul1->start(start);
		mul1->done(done);
		mul1->result(result);
		mul1->a_in(a_in);
		mul1->b_in(b_in);
		mul1->a_out(a_out);
		mul1->b_out(b_out);
		mul1->go(go);

		SC_THREAD(inpA);
		SC_THREAD(inpB);
		SC_THREAD(resetting);
		SC_THREAD(clocking);
		SC_THREAD(displaying);
		sensitive << done.posedge_event();
	}
	void inpA();
	void inpB();
	void resetting();
	void clocking();
	void displaying();
};