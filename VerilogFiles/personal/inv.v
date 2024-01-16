module inv(input in, output out);
wire w1;
nmos n1 (out, in, contrl);
pmos p1 (out, in, contrl);
endmodule