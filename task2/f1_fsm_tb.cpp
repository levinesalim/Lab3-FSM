#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vf1_fsm.h"
#include "vbuddy.cpp"     // include vbuddy code

int main(int argc, char **argv, char **env) {
  int simcyc;     // simulation clock count
  int clk;      

  Verilated::commandArgs(argc, argv);
  // init top verilog instance
  Vf1_fsm* top = new Vf1_fsm;
  // init trace dump
  Verilated::traceEverOn(true);
  VerilatedVcdC* tfp = new VerilatedVcdC;
  top->trace (tfp, 99);
  //CHANGE THIS
  tfp->open ("waveform.vcd");
 
  // init Vbuddy
  if (vbdOpen()!=1) return(-1);
  vbdHeader("L3T2:F1 Lights");
  //vbdSetMode(1);        // Flag mode set to one-shot

  // initialize simulation input 
  top->clk = 1;
  top->en = 1;
  top->rst = 0;

  // run simulation for MAX_SIM_CYC clock cycles
  for (simcyc=0; simcyc<600; simcyc++) {
    // dump variables into VCD file and toggle clock
    //top->rst = simcyc;
    for (clk=0; clk<2; clk++) {
      tfp->dump (2*simcyc+clk);
      top->clk = !top->clk;
      top->eval ();
    }

    top->en = vbdFlag();
    //displaying the result on the neopixel strip
    vbdBar(top->data_out & 0xFF);

    // either simulation finished, or 'q' is pressed
    if ((Verilated::gotFinish()) || (vbdGetkey()=='q')) 
      exit(0);
  }

  vbdClose();     // ++++
  tfp->close(); 
  printf("Exiting\n");
  exit(0);
}
