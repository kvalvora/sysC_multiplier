#include"controller.h"

void controller::comb_func() 
{
	enCounter = SC_LOGIC_0;
	initCounter = SC_LOGIC_0;
	rstCounter = SC_LOGIC_0;
	done = SC_LOGIC_0;
	rstA = SC_LOGIC_0;
	rstB = SC_LOGIC_0;
	rstt = SC_LOGIC_0;

	n_state = s0;

	switch (p_state)
	{
	case s0:
		rstCounter = SC_LOGIC_1;
		rstA = SC_LOGIC_1;
		rstB = SC_LOGIC_1;
		rstt = SC_LOGIC_1;

		if (go == '1')
			n_state = s1;
		else
			n_state = s0;
		break;
	case s1:
		rstA = SC_LOGIC_0;
		rstB = SC_LOGIC_0;
		n_state = s2;
		break;
	case s2:
		initCounter = SC_LOGIC_1;
		enCounter = SC_LOGIC_1;
		n_state = s3;
		break;
	case s3:
		enCounter = SC_LOGIC_1;
		if (eq == 0)
			n_state = s3;
		else
		{
			n_state = s1;
			done = SC_LOGIC_1;
		}
		break;
	default:
		enCounter = SC_LOGIC_0;
		initCounter = SC_LOGIC_0;
		rstCounter = SC_LOGIC_0;
		done = SC_LOGIC_0;
		rstA = SC_LOGIC_0;
		rstB = SC_LOGIC_0;
		rstt = SC_LOGIC_0;

		n_state = s0;
		break;
	}
}
void controller::seq_func()
{
	while (1) {
		if (rst == '1')
			p_state = s0;
		else if (clk.event() && (clk == '1'))
			p_state = n_state;
		wait();
	}
}