#include"mulTB.h"

int sc_main(int argc, char **argv) {

	mulTB TB1("testbench1");
	sc_trace_file* vcdfile;

	vcdfile = sc_create_vcd_trace_file("Multiplier_test");
	sc_trace(vcdfile, TB1.clk, "clk");
	sc_trace(vcdfile, TB1.rst, "rst");
	sc_trace(vcdfile, TB1.start, "start");
	sc_trace(vcdfile, TB1.done, "done");
	sc_trace(vcdfile, TB1.a_in, "a_in");
	sc_trace(vcdfile, TB1.a_in, "b_in");
	sc_trace(vcdfile, TB1.result, "result");
	sc_start(12000, SC_NS);
	return 0;
}
