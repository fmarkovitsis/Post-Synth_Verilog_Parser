/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : O-2018.06-SP4
// Date      : Sat Nov 21 12:03:26 2020
/////////////////////////////////////////////////////////////


module s27 ( GND, VDD, CK, G0, G1, G17, G2, G3 );
  input GND, VDD, CK, G0, G1, G2, G3;
  output G17;
  wire   G10, G13, n1, n2, n3, n4, n5, n6, n7, n8, n10, n11;

  DFF_X1 DFF_0 ( .D(G10), .CK(CK), .QN(n10) );
  DFF_X1 DFF_1 ( .D(n1), .CK(CK), .QN(n11) );
  DFF_X1 DFF_2 ( .D(G13), .CK(CK), .Q(n2) );
  INV_X1 U12 ( .A(G17), .ZN(n1) );
  NAND3_X1 U13 ( .A1(n4), .A2(n5), .A3(n10), .ZN(G17) );
  OR2_X1 U14 ( .A1(n8), .A2(G3), .ZN(n4) );
  NAND2_X1 U15 ( .A1(n6), .A2(n7), .ZN(n5) );
  NOR2_X1 U16 ( .A1(n11), .A2(G0), .ZN(n8) );
  NOR2_X1 U17 ( .A1(G2), .A2(n3), .ZN(G13) );
  NOR2_X1 U18 ( .A1(G1), .A2(n2), .ZN(n3) );
  OR2_X1 U19 ( .A1(G0), .A2(n11), .ZN(n7) );
  OR2_X1 U20 ( .A1(n2), .A2(G1), .ZN(n6) );
  AND2_X1 U21 ( .A1(G17), .A2(G0), .ZN(G10) );
endmodule

