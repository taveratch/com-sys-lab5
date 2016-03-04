//------------------------------------------------------------------
// Simple 4-bits adder
//
// SystemC for VHDL engineers
// (c)www.ht-lab.com
//------------------------------------------------------------------
#ifndef ADDER_H
#define ADDER_H

#include <systemc.h>

SC_MODULE(adder) {
    sc_in<sc_uint<16> > ain, bin;
    sc_out<bool> co;
    sc_out<sc_uint<16> > sum;
    sc_in<bool> operation;
    bool co0, co1, co2, co3;
    sc_uint<16> sum_s;

    // 1-bit ripple carry fulladder, note the cof reference bool&
    bool fulladder(bool a, bool b, bool cif, bool& cof) {
        bool sumr;
        sumr =(a ^ b) ^ cif;
        cof=(a & b) | ((a ^ b) & cif);
        return sumr;
    }


    void p1() {
        sc_uint<16> tempB = bin.read();
        if(operation.read() == 1) //Subtract
          tempB = tempB ^ 65535;
        sum_s[0]=fulladder(ain.read()[0],tempB[0],operation.read(), co0);
        sum_s[1]=fulladder(ain.read()[1],tempB[1],co0,co1);
        sum_s[2]=fulladder(ain.read()[2],tempB[2],co1,co2);
        sum_s[3]=fulladder(ain.read()[3],tempB[3],co2,co3);
        sum_s[4]=fulladder(ain.read()[4],tempB[4],co3, co0);
        sum_s[5]=fulladder(ain.read()[5],tempB[5],co0,co1);
        sum_s[6]=fulladder(ain.read()[6],tempB[6],co1,co2);
        sum_s[7]=fulladder(ain.read()[7],tempB[7],co2,co3);
        sum_s[8]=fulladder(ain.read()[8],tempB[8],co3, co0);
        sum_s[9]=fulladder(ain.read()[9],tempB[9],co0,co1);
        sum_s[10]=fulladder(ain.read()[10],tempB[10],co1,co2);
        sum_s[11]=fulladder(ain.read()[11],tempB[11],co2,co3);
        sum_s[12]=fulladder(ain.read()[12],tempB[12],co3, co0);
        sum_s[13]=fulladder(ain.read()[13],tempB[13],co0,co1);
        sum_s[14]=fulladder(ain.read()[14],tempB[14],co1,co2);
        sum_s[15]=fulladder(ain.read()[15],tempB[15],co2,co3);

        sum.write(sum_s);
        co.write(co3);


    }

    SC_CTOR(adder) {
        SC_METHOD(p1);
        sensitive << ain << bin;
    }
};
#endif
