`timescale 1ns/1ns

module tb;
  reg x=1'b0;
  
  always
    begin
      #10  x=~x;
    end
  
  initial 
    begin
      $dumpfile("dump.vcd");
      $dumpvars(1);
    end
  
  initial
    begin
      #200 $finish;
    end
endmodule