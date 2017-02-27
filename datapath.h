#ifndef DE_H
#define DE_H
#include<systemc.h>
#include"Adder.h"
#include "partsLibrary.h"

SC_MODULE(datapath) {
	//port declaration
	sc_in <sc_logic> rst, clk;
	sc_out <sc_logic> start;
	sc_signal <sc_logic> enCounter;
	sc_signal <sc_logic> rstCounter;
	sc_signal <sc_logic> initCounter;
	sc_in <sc_logic> done;
	sc_signal <sc_logic> eq, lt;
	sc_signal <sc_logic> rstA, rstB, rstt;
	sc_out <sc_lv<8>> result;
	sc_in <sc_lv<8>> a_in, b_in;
	sc_out <sc_lv<8>> a_out, b_out;

	//signal declaration
	sc_signal <sc_lv<8>> sum;
	sc_signal <sc_lv<8>> countValue, initialCount;
	sc_signal <sc_lv<8>> temp_out;
	sc_signal <sc_logic> go;
	sc_signal <sc_lv<8>> aval, bval;

	//instantiation
	dRegisterRaE* regA;
	dRegisterRaE* regB;
	dRegisterRaE* temp;
	dRegisterRaE* regRes;
	Adder<8>* add;
	uCounterRaEL* Bcounter;
	comparator* compare;


	SC_CTOR(datapath) {

		initialCount = sc_lv<8>("00000000");
		sum = sc_lv<8>("00000000");

		regA = new dRegisterRaE("A_register");
		regA->clk(clk);
		regA->rst(rstA);
		regA->cen(go);
		regA->regin(aval);
		regA->regout(a_out);

		regB = new dRegisterRaE("B_register");
		regB->clk(clk);
		regB->rst(rstB);
		regB->cen(go);
		regB->regin(bval);
		regB->regout(b_out);

		temp = new dRegisterRaE("temp_register");
		temp->clk(clk);
		temp->rst(rstt);
		temp->cen(lt);
		temp->regin(sum);
		temp->regout(temp_out);

		regRes = new dRegisterRaE("result_register");
		regRes->clk(clk);
		regRes->rst(rst);
		regRes->cen(done);
		regRes->regin(sum);
		regRes->regout(result);

		compare = new comparator("Comparator");
		compare->ain(countValue);
		compare->bin(b_out);
		compare->lt(lt);
		compare->eq(eq);

		Bcounter = new uCounterRaEL("B_counter");
		Bcounter->rst(rstCounter);
		Bcounter->clk(clk);
		Bcounter->cen(enCounter);
		Bcounter->pld(initCounter);
		Bcounter->parin(initialCount);
		Bcounter->cntout(countValue);

		add = new Adder<8>("Adder");
		add->in1(a_out);
		add->in2(sum);
		add->out(sum);

		//process declaration
		SC_METHOD(datapath_assign);
		sensitive << start;
	}

	void datapath_assign() {
		go = start.read();
		aval = a_in.read();
		bval = b_in.read();
	}
};

#endif