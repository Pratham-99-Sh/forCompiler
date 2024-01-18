module inv(input inp, output oup);
wire w1;
nmos n1 (oup, 1, inp);
pmos p1 (oup, 1, inp);
endmodule