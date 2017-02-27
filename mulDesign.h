#include"datapath.h"
#include"controller.h"

SC_MODULE(mul) {
	//port declaration
	sc_in <sc_logic> rst, clk;
	sc_out <sc_logic> start;
	sc_in <sc_logic> done;
	sc_out <sc_lv<8>> result;
	sc_in <sc_lv<8>> a_in, b_in;
	sc_out <sc_lv<8>> a_out, b_out;
	sc_in <sc_logic> go;

	datapath* DP;
	controller* CNTRL;

	SC_CTOR(mul) {
		DP = new datapath("Datapath");
		DP->rst(rst);
		DP->clk(clk);
		DP->start(start);
		DP->done(done);
		DP->result(result);
		DP->a_in(a_in);
		DP->b_in(b_in);
		DP->a_out(a_out);
		DP->b_out(b_out);

		CNTRL = new controller("controller");
		CNTRL->rst(rst);
		CNTRL->clk(clk);
		CNTRL->go(go);
	}
};