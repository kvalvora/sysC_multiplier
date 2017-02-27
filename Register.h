#ifndef Dreg
#define Dreg

#include <systemc.h>

template <int T> SC_MODULE (Dregister){
	
	sc_in <sc_logic> clk, rst, cen; 
	sc_in <sc_lv<T> > regin; 
	sc_out <sc_lv<T> > regout; 

	SC_HAS_PROCESS (Dregister);
	Dregister (sc_module_name name_nt):sc_module(name_nt){
		
		SC_METHOD (registering); 
		sensitive << clk << rst; 
	}
	void registering()
	{
		sc_lv<T> tmp;
		if (rst =='1')
		{
			for (int i =0; i <T; i++)
				tmp[i] = sc_logic(0);
			regout = tmp;
		}
		else if ((clk->event()) && (clk =='1')){
			if (cen =='1') 
				regout = regin;
		}
		//cout << " in register " << datain << "  " << dataout << "  load " << ld <<endl;
		
	}
};
#endif