#include <systemc.h>

// nBitAdder: n Bit adder with carry in and carry out
class nBitAdder : public sc_module  
{
	public:
	sc_port<sc_signal_in_if <sc_lv<8>>, 1> ain, bin;
	sc_port<sc_signal_in_if <sc_logic>, 1> ci;
	sc_port<sc_signal_out_if <sc_lv<8>>, 1> addout;
	sc_port<sc_signal_out_if <sc_logic>, 1> co;

	SC_CTOR(nBitAdder)
	{
		SC_METHOD(adding);
		sensitive << ain << bin << ci;
	}
	void adding();
};
// comparator
SC_MODULE(comparator)
{
	sc_in<sc_lv<8>> ain, bin;
	sc_out<sc_logic> lt, eq, gt;

	void comparing();

	SC_CTOR(comparator)
	{
		SC_METHOD(comparing);
		sensitive << ain << bin;
	}
};

// octalMux2to1: 8-bit 2 to 1 multiplexer
SC_MODULE(octalMux2to1)
{
	sc_in<sc_logic> sel;
	sc_in<sc_lv<8> > ain, bin;
	sc_out<sc_lv<8> > yout;

	SC_CTOR(octalMux2to1)
	{
		SC_METHOD(muxing);
		sensitive << ain << bin << sel;
	}
	void muxing();
};

// octalTriState: 8-bit Tri-state logic
SC_MODULE(octalTriState)
{
	sc_in<sc_logic> sel;
	sc_in<sc_lv<8> > ain;
	sc_out<sc_lv<8> > yout;

	SC_CTOR(octalTriState)
	{
		SC_METHOD(selecting);
		sensitive << ain << sel;
	}
	void selecting();
};

// dRegisterRaE: D Register w/ asynch Reset, clock Enable
SC_MODULE(dRegisterRaE)
{
	sc_in<sc_logic> clk, rst, cen;
	sc_in<sc_lv<8> > regin;
	sc_out<sc_lv<8> > regout;

	SC_CTOR(dRegisterRaE)
	{
		SC_METHOD(registering);
		sensitive << rst << clk;
	}
	void registering();
};

// dRegisterRaEZ: D Register w/ asynch Reset, clock Enable, load Zero
SC_MODULE(dRegisterRaEZ)
{
	sc_in<sc_logic> rst, clk, cen, zer;
	sc_in<sc_lv<8> > regin;
	sc_out<sc_lv<8> > regout;

	SC_CTOR(dRegisterRaEZ)
	{
		SC_METHOD(registering);
		sensitive << rst << clk;
	}
	void registering();
};

// dRegisterRsE: D Register w/ sync Reset, clock Enable
SC_MODULE(dRegisterRsE)
{
	sc_in<sc_logic> rst, clk, cen;
	sc_in<sc_lv<8> > regin;
	sc_out<sc_lv<8> > regout;
	sc_signal<sc_logic> w;
	sc_out<sc_logic> y;


	SC_CTOR(dRegisterRsE)
	{
		SC_METHOD(registering);
		sensitive << clk.pos();
	}
	void registering();
};

// uCounterRaEL: Up-counter w/ asynch Reset, clock Enable, parralel Load
SC_MODULE(uCounterRaEL)
{
	sc_in<sc_logic> rst, clk, cen, pld;
	sc_in<sc_lv<8> > parin;
	sc_out<sc_lv<8> > cntout;

	SC_CTOR(uCounterRaEL)
	{
		SC_METHOD(counting);
		sensitive << rst << clk;
	}
	void counting();
};


// uCounterRaELCo: Up-counter w/ asynch Reset, clock Enable, parallel Load, Carry
SC_MODULE(uCounterRaELCo)
{
	sc_in<sc_logic> rst, clk, cen, pld;
	sc_in<sc_logic> ci;
	sc_out<sc_logic> co;
	sc_in<sc_lv<8> > parin;
	sc_out<sc_lv<8> > cntout;

	SC_CTOR(uCounterRaELCo)
	{
		SC_METHOD(counting);
		sensitive << rst << clk;
		SC_METHOD(carrying);
		sensitive << ci << cntout;
	}
	void counting();
	void carrying();
};

// rShifterRaEL: right Shiftregister w/ asyn Reset, shift Enable, parallel Load
SC_MODULE(rShifterRaEL)
{
	sc_in<sc_logic> rst, clk, sen, pld;
	sc_in<sc_logic> sin;
	sc_in<sc_lv<8> > parin;
	sc_out<sc_lv<8> > shftout;

	void shifting();

	SC_CTOR(rShifterRaEL)
	{
		SC_METHOD(shifting);
		sensitive << rst << clk;
	}
};

// Memory: Templated memory w/ datain, dataout, chip-select, read-write-bar
template<int ADDRESS, int WORD_LENGTH>
class Memory : public sc_module {
public:
	sc_in<sc_lv<ADDRESS>> addr;
	sc_in<sc_lv<WORD_LENGTH>> datain;
	sc_out<sc_lv<WORD_LENGTH>> dataout;
	sc_in<sc_logic> cs, rwbar;

	int addrSpace;
	sc_uint <WORD_LENGTH> *mem;

	void meminit();
	void memread();
	void memwrite();
	void memdump();

	SC_HAS_PROCESS(Memory);
	Memory(sc_module_name);
};

template<int ADDRESS, int WORD_LENGTH>
Memory<ADDRESS, WORD_LENGTH>::Memory(sc_module_name) 
{
	addrSpace = int(pow(2.0, ADDRESS));
	mem = new sc_uint<WORD_LENGTH>[addrSpace];

	SC_THREAD(meminit);
	SC_METHOD(memread);
	sensitive << addr << cs << rwbar;
	SC_METHOD(memwrite);
	sensitive << addr << datain << cs << rwbar;
	SC_THREAD(memdump);
}

template<int ADDRESS, int WORD_LENGTH>
void Memory<ADDRESS, WORD_LENGTH>::meminit() {

	ifstream in("memin.txt");
	int i;
	sc_lv<WORD_LENGTH> data;

	for (i = 0; i<addrSpace; i++) {
		in >> data;
		mem[i] = data;
		cout << "Init at: " << i << " writes: " << data << '\n';
	}
}

template<int ADDRESS, int WORD_LENGTH>
void Memory<ADDRESS, WORD_LENGTH>::memwrite() {
	sc_uint<ADDRESS> ad;
	if (cs->read() == '1') {
		if (rwbar->read() == '0') {
			ad = addr; 
			mem[ad] = datain;
		}
	}
}

template<int ADDRESS, int WORD_LENGTH>
void Memory<ADDRESS, WORD_LENGTH>::memread() {
	sc_uint<ADDRESS> ad;
	if (cs->read() == '1') {
		if (rwbar->read() == '1') {
			ad = addr; 
			dataout = mem[ad];
		}
	}
}

template<int ADDRESS, int WORD_LENGTH>
void Memory<ADDRESS, WORD_LENGTH>::memdump() {
	int i;
	sc_lv<WORD_LENGTH> data;
	ofstream out("memout.txt");
	wait(2000, SC_NS);
	for (i = 0; i<addrSpace; i++) {
		data = mem[i];
		out << i << ":\t" << data << "\n";
	}
}

// nBitAdder: n Bit adder with carry in and carry out
SC_MODULE(nBitAdder_channelSpecific)
{
	sc_in<sc_lv<8> > ain, bin;
	sc_in<sc_logic> ci;
	sc_out<sc_lv<8> > addout;
	sc_out<sc_logic > co;

	SC_CTOR(nBitAdder_channelSpecific)
	{
		SC_METHOD(adding);
		sensitive << ain << bin << ci;
	}
	void adding();
};

