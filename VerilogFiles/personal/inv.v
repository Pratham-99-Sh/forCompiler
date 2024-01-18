module inv(input inp, output oup);
wire w1;
supply1 vdd;
nmos n1 (oup, vdd, inp);
pmos p1 (oup, vdd, inp);
endmodule