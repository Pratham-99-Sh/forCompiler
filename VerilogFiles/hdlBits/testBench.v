`timescale 10ns/1ns
`include "top_module.v"
module testBench;
reg [3:0] in_supply;
wire [1:0] pos_recieved;
top_module top_module_0 (in_supply, pos_recieved);

initial
begin
    in_supply = 4'd0;
    #10 in_supply = 4'd1;
    #10 in_supply = 4'd2;
    #10 in_supply = 4'd3;
    #10 in_supply = 4'd4;
    #10 in_supply = 4'd5;
    #10 in_supply = 4'd6;
    #10 in_supply = 4'd7;
    #10 in_supply = 4'd8;
    #10 in_supply = 4'd9;
    #10 in_supply = 4'd10;
    #10 in_supply = 4'd11;
    #10 in_supply = 4'd12;
    #10 in_supply = 4'd13;
    #10 in_supply = 4'd14;
    #10 in_supply = 4'd15;
    #10 in_supply = 4'd16;
    #10 in_supply = 4'd29;
    #10 in_supply = 4'd30;
    #10 in_supply = 4'd31;
    $finish;
end

initial begin
    $dumpfile("testBench.vcd");
    $dumpvars(0, testBench);
end

endmodule