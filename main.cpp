#include <systemc.h>

#include "ALU.h"

sc_signal<sc_uint<16> > ain,bin,sum;
sc_signal<bool> lessFlag,zero,owf;
sc_signal<sc_uint<4> > operation;

void print(){
  cout << "A : " << ain.read() << endl;
  cout << "B : " << bin.read() << endl;
  cout << "Operation : " << operation.read() << endl;
  cout << "Result : " << sum.read() << endl;
  cout << "Overflow : " << (owf.read()==1 ? "true" : "false") << endl;
  cout << "Zero flag : " << (zero.read() == 1 ? "true" : "false") << endl;
  cout << "Less than : " << (lessFlag.read() == 1 ? "true" : "false") << endl;
  cout << endl;
}

int sc_main(int argc, char* argv[])
{

  sc_trace_file *ar = sc_create_vcd_trace_file("Wave");
  sc_trace(ar, ain, "ain");
	sc_trace(ar, bin, "bin");
	sc_trace(ar, sum, "sum");
  sc_trace(ar, operation,"operation");
  sc_trace(ar, owf , "owf-flag");
  sc_trace(ar, zero , "zero-flag");
  sc_trace(ar, lessFlag, "less-than-flag");

  ain.write("0b0000000000001000");
  bin.write("0b0000000000000111");
  alu alu("alu");
  alu.ain(ain);
  alu.bin(bin);
  alu.sum(sum);
  alu.owf(owf);
  alu.zero(zero);
  alu.less(lessFlag);
  alu.operation(operation);

  /*Write dummy value*/
  operation.write(10);
  sc_start(100,SC_NS);

  /*Start ALU 6 times*/
  for(int i =0;i<7;i++){
    operation.write(i);
    sc_start(100,SC_NS);
    print(); //print the result
  }

  sc_close_vcd_trace_file(ar);
}
