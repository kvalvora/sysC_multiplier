#include"mulTB.h"

void mulTB::inpA() {
	start = SC_LOGIC_0;
	WAIT(10, SC_NS);
	start = SC_LOGIC_1;
	a_in = "00000101";
	WAIT(100, SC_NS);
	start = SC_LOGIC_0;
}

void mulTB::inpB() {
	start = SC_LOGIC_0;
	WAIT(10, SC_NS);
	start = SC_LOGIC_1;
	b_in = "00000111";
	WAIT(100, SC_NS);
	start = SC_LOGIC_0;
}

void mulTB::clocking() {
	int i;
	clk = sc_logic('1');
	for (i = 0; i <= 50; i++)
	{
		clk = sc_logic('0');
		wait(50, SC_NS);
		clk = sc_logic('1');
		wait(50, SC_NS);
	}
}
void mulTB::resetting() {
	rst = (sc_logic)'0';
	wait(5, SC_NS);
	rst = (sc_logic)'1';
	wait(5, SC_NS);
	rst = (sc_logic)'0';
};

void mulTB::displaying() {

	cout << "a = " << a_in.read() <<"\n b="<< b_in.read() << "\nresult = " << result.read() << endl;
}