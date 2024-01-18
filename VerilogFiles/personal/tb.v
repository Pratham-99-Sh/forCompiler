`timescale 10ns/1ns
`include "inv.v"
module tb;

reg in;
wire out;
inv mod0 (in, out);

initial begin
    #10 in = 1'b0;
    #10 in = 1'b1;
    #10 in = 1'b0;
    #10 in = 1'b1;
    #10 in = 1'b0;
    #10 in = 1'b1;
    #10 in = 1'b0;
    #10 in = 1'b1;
    #10 in = 1'b0;
    $finish;
end

initial begin
    $dumpfile("tb.vcd");
    $dumpvars(0, tb);
end

endmodule