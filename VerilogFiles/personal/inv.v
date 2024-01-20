module inv(input wire inp, output wire oup);
wire w1;
supply1 vdd;
supply0 gnd;
nmos n1 (oup, gnd, inp);
pmos p1 (oup, vdd, inp);
endmodule