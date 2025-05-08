/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : O-2018.06-SP4
// Date      : Sun Nov 22 10:04:01 2020
/////////////////////////////////////////////////////////////


module s344 ( GND, VDD, CK, A0, A1, A2, A3, B0, B1, B2, B3, CNTVCO2, CNTVCON2, 
        P0, P1, P2, P3, P4, P5, P6, P7, READY, START );
  input GND, VDD, CK, A0, A1, A2, A3, B0, B1, B2, B3, START;
  output CNTVCO2, CNTVCON2, P0, P1, P2, P3, P4, P5, P6, P7, READY;
  wire   CNTVG3VD, CNTVG2VD, CNTVG1VD, MRVG4VD, MRVG3VD, MRVG2VD, MRVG1VD, n1,
         n2, n3, n4, n6, n7, n8, n9, n10, n11, n12, n13, n14, n15, n16, n17,
         n18, n19, n20, n21, n22, n23, n24, n25, n26, n27, n28, n29, n30, n31,
         n32, n33, n34, n35, n36, n37, n38, n39, n40, n41, n42, n43, n44, n45,
         n46, n47, n48, n49, n50, n51, n52, n53, n54, n55, n56, n57, n58, n59,
         n60, n61, n62, n63, n64, n65, n66, n67, n68, n69, n70, n71, n72, n73,
         n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84, n85, n86, n87,
         n88, n89, n90, n91, n92, n93, n94, n95, n96, n97, n98, n99, n100,
         n101;

  DFF_X1 DFF_0 ( .D(CNTVG3VD), .CK(CK), .Q(n3), .QN(n89) );
  DFF_X1 DFF_14 ( .D(n94), .CK(CK), .Q(n14), .QN(n90) );
  DFF_X1 DFF_13 ( .D(n95), .CK(CK), .QN(n91) );
  DFF_X1 DFF_12 ( .D(n96), .CK(CK), .QN(n92) );
  DFF_X1 DFF_11 ( .D(n97), .CK(CK), .QN(n93) );
  DFF_X1 DFF_2 ( .D(CNTVG1VD), .CK(CK), .QN(n87) );
  DFF_X1 DFF_1 ( .D(CNTVG2VD), .CK(CK), .Q(n6), .QN(n88) );
  DFF_X1 DFF_6 ( .D(n98), .CK(CK), .QN(P4) );
  DFF_X1 DFF_5 ( .D(n99), .CK(CK), .Q(n11), .QN(P5) );
  DFF_X1 DFF_10 ( .D(MRVG1VD), .CK(CK), .Q(n13), .QN(P0) );
  DFF_X1 DFF_9 ( .D(MRVG2VD), .CK(CK), .QN(P1) );
  DFF_X1 DFF_8 ( .D(MRVG3VD), .CK(CK), .QN(P2) );
  DFF_X1 DFF_7 ( .D(MRVG4VD), .CK(CK), .QN(P3) );
  DFF_X1 DFF_3 ( .D(n101), .CK(CK), .Q(n7), .QN(P7) );
  DFF_X1 DFF_4 ( .D(n100), .CK(CK), .Q(n9), .QN(P6) );
  NOR3_X1 U104 ( .A1(n89), .A2(n87), .A3(n6), .ZN(READY) );
  INV_X1 U105 ( .A(n28), .ZN(n1) );
  INV_X1 U106 ( .A(n32), .ZN(n10) );
  INV_X1 U107 ( .A(n43), .ZN(n8) );
  NAND2_X1 U108 ( .A1(n18), .A2(n4), .ZN(n28) );
  INV_X1 U109 ( .A(n18), .ZN(n2) );
  NOR2_X1 U110 ( .A1(n63), .A2(n36), .ZN(n32) );
  AND2_X1 U111 ( .A1(n12), .A2(n64), .ZN(n63) );
  NAND2_X1 U112 ( .A1(n35), .A2(n11), .ZN(n64) );
  NOR2_X1 U113 ( .A1(n61), .A2(n46), .ZN(n43) );
  AND2_X1 U114 ( .A1(n10), .A2(n62), .ZN(n61) );
  NAND2_X1 U115 ( .A1(n45), .A2(n9), .ZN(n62) );
  INV_X1 U116 ( .A(READY), .ZN(n4) );
  NOR2_X1 U117 ( .A1(n11), .A2(n35), .ZN(n36) );
  NOR2_X1 U118 ( .A1(n9), .A2(n45), .ZN(n46) );
  NOR2_X1 U119 ( .A1(n7), .A2(n55), .ZN(n56) );
  NOR2_X1 U120 ( .A1(n59), .A2(n56), .ZN(n53) );
  AND2_X1 U121 ( .A1(n8), .A2(n60), .ZN(n59) );
  NAND2_X1 U122 ( .A1(n55), .A2(n7), .ZN(n60) );
  INV_X1 U123 ( .A(n34), .ZN(n12) );
  NAND2_X1 U124 ( .A1(n30), .A2(n31), .ZN(n29) );
  NAND2_X1 U125 ( .A1(n36), .A2(n12), .ZN(n30) );
  NAND2_X1 U126 ( .A1(n32), .A2(n33), .ZN(n31) );
  NAND3_X1 U127 ( .A1(n34), .A2(n11), .A3(n35), .ZN(n33) );
  NAND2_X1 U128 ( .A1(n41), .A2(n42), .ZN(n40) );
  NAND2_X1 U129 ( .A1(n46), .A2(n10), .ZN(n41) );
  NAND2_X1 U130 ( .A1(n43), .A2(n44), .ZN(n42) );
  NAND3_X1 U131 ( .A1(n45), .A2(n9), .A3(n32), .ZN(n44) );
  NAND2_X1 U132 ( .A1(n51), .A2(n52), .ZN(n50) );
  NAND2_X1 U133 ( .A1(n56), .A2(n8), .ZN(n51) );
  NAND2_X1 U134 ( .A1(n53), .A2(n54), .ZN(n52) );
  NAND3_X1 U135 ( .A1(n55), .A2(n7), .A3(n43), .ZN(n54) );
  NAND3_X1 U136 ( .A1(n57), .A2(n15), .A3(n58), .ZN(n101) );
  NAND2_X1 U137 ( .A1(n28), .A2(n7), .ZN(n58) );
  NAND2_X1 U138 ( .A1(n53), .A2(n1), .ZN(n57) );
  INV_X1 U139 ( .A(CNTVCO2), .ZN(CNTVCON2) );
  NOR3_X1 U140 ( .A1(n88), .A2(n87), .A3(n89), .ZN(CNTVCO2) );
  NOR2_X1 U141 ( .A1(n87), .A2(n88), .ZN(n84) );
  NOR2_X1 U142 ( .A1(READY), .A2(n87), .ZN(n86) );
  NOR2_X1 U143 ( .A1(P0), .A2(n4), .ZN(n81) );
  NOR2_X1 U144 ( .A1(P1), .A2(n4), .ZN(n77) );
  NOR2_X1 U145 ( .A1(P2), .A2(n4), .ZN(n73) );
  NOR2_X1 U146 ( .A1(P3), .A2(n4), .ZN(n67) );
  NAND3_X1 U147 ( .A1(n88), .A2(n89), .A3(n87), .ZN(n18) );
  NOR2_X1 U148 ( .A1(B3), .A2(READY), .ZN(n68) );
  NAND3_X1 U149 ( .A1(P4), .A2(n14), .A3(P0), .ZN(n34) );
  NOR3_X1 U150 ( .A1(n85), .A2(START), .A3(n84), .ZN(CNTVG2VD) );
  NOR2_X1 U151 ( .A1(n86), .A2(n6), .ZN(n85) );
  NOR3_X1 U152 ( .A1(n83), .A2(START), .A3(CNTVCO2), .ZN(CNTVG3VD) );
  NOR2_X1 U153 ( .A1(n84), .A2(n3), .ZN(n83) );
  NAND2_X1 U154 ( .A1(n15), .A2(n37), .ZN(n99) );
  NAND2_X1 U155 ( .A1(n38), .A2(n39), .ZN(n37) );
  NAND2_X1 U156 ( .A1(P5), .A2(n28), .ZN(n39) );
  NAND2_X1 U157 ( .A1(n1), .A2(n40), .ZN(n38) );
  NAND2_X1 U158 ( .A1(n15), .A2(n47), .ZN(n100) );
  NAND2_X1 U159 ( .A1(n48), .A2(n49), .ZN(n47) );
  NAND2_X1 U160 ( .A1(P6), .A2(n28), .ZN(n49) );
  NAND2_X1 U161 ( .A1(n1), .A2(n50), .ZN(n48) );
  NOR2_X1 U162 ( .A1(n90), .A2(n13), .ZN(n70) );
  NOR2_X1 U163 ( .A1(START), .A2(n86), .ZN(CNTVG1VD) );
  NOR2_X1 U164 ( .A1(n79), .A2(n80), .ZN(MRVG1VD) );
  AND2_X1 U165 ( .A1(n1), .A2(P1), .ZN(n80) );
  NOR3_X1 U166 ( .A1(n81), .A2(n1), .A3(n82), .ZN(n79) );
  NOR2_X1 U167 ( .A1(B0), .A2(READY), .ZN(n82) );
  NOR2_X1 U168 ( .A1(n75), .A2(n76), .ZN(MRVG2VD) );
  AND2_X1 U169 ( .A1(n1), .A2(P2), .ZN(n76) );
  NOR3_X1 U170 ( .A1(n77), .A2(n1), .A3(n78), .ZN(n75) );
  NOR2_X1 U171 ( .A1(B1), .A2(READY), .ZN(n78) );
  NOR2_X1 U172 ( .A1(n71), .A2(n72), .ZN(MRVG3VD) );
  AND2_X1 U173 ( .A1(n1), .A2(P3), .ZN(n72) );
  NOR3_X1 U174 ( .A1(n73), .A2(n1), .A3(n74), .ZN(n71) );
  NOR2_X1 U175 ( .A1(B2), .A2(READY), .ZN(n74) );
  NOR2_X1 U176 ( .A1(n65), .A2(n66), .ZN(MRVG4VD) );
  NOR3_X1 U177 ( .A1(n28), .A2(n12), .A3(n69), .ZN(n65) );
  NOR3_X1 U178 ( .A1(n67), .A2(n1), .A3(n68), .ZN(n66) );
  NOR2_X1 U179 ( .A1(n70), .A2(P4), .ZN(n69) );
  OR2_X1 U180 ( .A1(n13), .A2(n91), .ZN(n35) );
  OR2_X1 U181 ( .A1(n13), .A2(n92), .ZN(n45) );
  OR2_X1 U182 ( .A1(n13), .A2(n93), .ZN(n55) );
  NAND2_X1 U183 ( .A1(n16), .A2(n17), .ZN(n94) );
  NAND2_X1 U184 ( .A1(n18), .A2(n14), .ZN(n17) );
  NAND2_X1 U185 ( .A1(A0), .A2(n2), .ZN(n16) );
  NAND2_X1 U186 ( .A1(n15), .A2(n25), .ZN(n98) );
  NAND2_X1 U187 ( .A1(n26), .A2(n27), .ZN(n25) );
  NAND2_X1 U188 ( .A1(P4), .A2(n28), .ZN(n27) );
  NAND2_X1 U189 ( .A1(n1), .A2(n29), .ZN(n26) );
  NAND2_X1 U190 ( .A1(n19), .A2(n20), .ZN(n95) );
  NAND2_X1 U191 ( .A1(A1), .A2(n2), .ZN(n19) );
  OR2_X1 U192 ( .A1(n2), .A2(n91), .ZN(n20) );
  NAND2_X1 U193 ( .A1(n21), .A2(n22), .ZN(n96) );
  NAND2_X1 U194 ( .A1(A2), .A2(n2), .ZN(n21) );
  OR2_X1 U195 ( .A1(n2), .A2(n92), .ZN(n22) );
  NAND2_X1 U196 ( .A1(n23), .A2(n24), .ZN(n97) );
  NAND2_X1 U197 ( .A1(A3), .A2(n2), .ZN(n23) );
  OR2_X1 U198 ( .A1(n2), .A2(n93), .ZN(n24) );
  INV_X1 U199 ( .A(START), .ZN(n15) );
endmodule

