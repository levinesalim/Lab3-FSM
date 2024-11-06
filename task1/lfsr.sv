//we will include everything from the design
//we must have a signal sine generation
//vbdFlag() is needed
module lfsr(
    input   logic       clk,
    input   logic       rst,
    input   logic       en,
    output  logic [4:1] data_out
);

    logic[4:1] sreg; //adding definition for sreg

always_ff @ (posedge clk, posedge rst)
    if (rst)
        sreg <= 4'b1;
    else begin
        sreg <= {sreg[3:1], sreg[4] ^ sreg[3]};
    end

assign data_out = sreg; 
endmodule
