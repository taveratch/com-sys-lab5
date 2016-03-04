//------------------------------------------------------------------
// Simple 4-bits adder
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ALU_H
#define ALU_H

#include <systemc.h>

#include "adder.h"

SC_MODULE(alu) {
    sc_in<sc_uint<16> > ain, bin;
    sc_out<sc_uint<16> > sum;
    sc_out<bool> owf,less,zero;
    sc_in<sc_uint<4> > operation;
    sc_signal<bool> add,sub;
    adder ADD,SUB;
    sc_signal<sc_uint<16> > sumAdd,sumSub,sumXOR,sumAND,sumOR,sumNOTA,sumSTL;
    sc_signal<bool> owfAdd,owfSub,owfXOR,owfAND,owfOR,owfNOTA,owfSTL;
    // sc_signal<sc_uint<16> > sumAdd;
    void p1() {
      // while(true){

        sumXOR = ain.read() ^ bin.read();
        sumAND = ain.read() & bin.read();
        sumOR = ain.read() | bin.read();
        sumNOTA = ain.read() ^ 65535;
        sumSTL = ain.read() < bin.read() ? 1 : 0;
        // wait();
        less.write(sumSub.read()[15]== 1);
        if(operation.read() == 0){
            cout << "Addition" << endl;
            owf.write(owfAdd);
            zero.write(sumAdd.read()==0);
            sum.write(sumAdd);
        }else if(operation.read() == 1){
            cout << "Subtraction" << endl;
            owf.write(0);
            zero.write(sumSub.read()==0);
            sum.write(sumSub);
        }else if(operation.read() == 2){
            cout << "XOR" << endl;
            owf.write(0);
            zero.write(sumXOR.read() == 0);
            sum.write(sumXOR);
        }else if(operation.read() == 3){
            cout << "AND" << endl;
            owf.write(0);
            zero.write(sumAND.read() == 0);
            sum.write(sumAND);
        }else if(operation.read() == 4){
            cout << "OR" << endl;
            owf.write(0);
            zero.write(sumOR.read() == 0);
            sum.write(sumOR);
        }else if(operation.read() == 5){
            cout << "NOT A" << endl;
            owf.write(0);
            less.write(0);
            zero.write(sumNOTA.read() == 0);
            sum.write(sumNOTA);
        }else if(operation.read() == 6){
            cout << "STL" << endl;
            owf.write(0);
            less.write(sumSTL.read() == 1);
            zero.write(sumSTL.read() ==0);
            sum.write(sumSTL);
        }
        // wait();
      // }


    }

    SC_CTOR(alu) :  ADD("adder") , SUB("sub") {

        add = 0;
        ADD.ain(ain);
        ADD.bin(bin);
        ADD.sum(sumAdd);
        ADD.co(owfAdd);
        ADD.operation(add);

        sub = 1;
        SUB.ain(ain);
        SUB.bin(bin);
        SUB.sum(sumSub);
        SUB.co(owfSub);
        SUB.operation(sub);
        // sc_start(100,SC_NS);




        // sumAdd = sumSub;
        // add = 1;
        // SUB.ain(ain);
        // SUB.bin(bin);
        // SUB.sum(sumSub);
        // SUB.co(owf);
        // SUB.operation(sub);


        SC_METHOD(p1);
        sensitive << operation;
    }
};
#endif
