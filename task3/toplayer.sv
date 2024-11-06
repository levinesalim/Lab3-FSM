module toplayer #(
    parameter WIDTH = 16
    
)(
    //interface signals
    input logic         en,
    input logic         rst,
    input logic         clk,
    input logic [WIDTH-1:0]  N,
    output logic [7:0] data_out,
    output logic        tick
);

clktick clockticks (
    .clk (clk),
    .rst (rst),
    .en (en),
    .N (N),
    .tick (tick) 
);

f1_fsm finitemachine (
    .clk (clk),
    .rst (rst),
    .en (tick),
    .data_out (data_out)
);

endmodule
