/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : O-2018.06-SP4
// Date      : Sun Nov 22 10:12:45 2020
/////////////////////////////////////////////////////////////


module s400 ( GND, VDD, CK, CLR, FM, GRN1, GRN2, RED1, RED2, TEST, YLW1, YLW2
 );
  input GND, VDD, CK, CLR, FM, TEST;
  output GRN1, GRN2, RED1, RED2, YLW1, YLW2;
  wire   TESTLVIINLATCHVCDAD, FMLVIINLATCHVCDAD, TCOMB_YA2, Y1C, R2C,
         TCOMB_GA2, TCOMB_GA1, C3_Q3VD, C3_Q2VD, C3_Q1VD, C3_Q0VD, UC_16VD,
         UC_17VD, UC_18VD, UC_19VD, UC_8VD, UC_9VD, UC_10VD, UC_11VD, n1, n2,
         n3, n5, n7, n9, n18, n19, n20, n21, n22, n23, n24, n25, n26, n27, n28,
         n29, n30, n31, n32, n33, n34, n35, n36, n37, n38, n39, n40, n41, n42,
         n43, n44, n45, n46, n47, n48, n49, n50, n51, n52, n53, n54, n55, n56,
         n57, n58, n59, n60, n61, n62, n63, n64, n65, n66, n67, n68, n69, n70,
         n71, n72, n73, n74, n75, n76, n77, n78, n79, n80, n81, n82, n83, n84,
         n85, n86, n87, n88, n90, n91, n92, n94, n95, n96, n97, n98, n99, n100,
         n101, n104, n105, n106, n107, n108, n109, n110, n111, n112, n113,
         n114, n115;

  DFF_X1 DFF_0 ( .D(TESTLVIINLATCHVCDAD), .CK(CK), .QN(n95) );
  DFF_X1 DFF_1 ( .D(FMLVIINLATCHVCDAD), .CK(CK), .Q(n107), .QN(n94) );
  DFF_X1 DFF_2 ( .D(TCOMB_YA2), .CK(CK), .Q(YLW2) );
  DFF_X1 DFF_3 ( .D(Y1C), .CK(CK), .QN(YLW1) );
  DFF_X1 DFF_4 ( .D(R2C), .CK(CK), .QN(RED2) );
  DFF_X1 DFF_5 ( .D(n104), .CK(CK), .Q(RED1) );
  DFF_X1 DFF_6 ( .D(TCOMB_GA2), .CK(CK), .Q(GRN2) );
  DFF_X1 DFF_7 ( .D(TCOMB_GA1), .CK(CK), .Q(GRN1) );
  DFF_X1 DFF_8 ( .D(n101), .CK(CK), .QN(n100) );
  DFF_X1 DFF_9 ( .D(C3_Q3VD), .CK(CK), .Q(n105), .QN(n96) );
  DFF_X1 DFF_10 ( .D(C3_Q2VD), .CK(CK), .Q(n110), .QN(n99) );
  DFF_X1 DFF_11 ( .D(C3_Q1VD), .CK(CK), .Q(n108), .QN(n97) );
  DFF_X1 DFF_12 ( .D(C3_Q0VD), .CK(CK), .Q(n106), .QN(n98) );
  DFF_X1 DFF_13 ( .D(UC_16VD), .CK(CK), .Q(n113) );
  DFF_X1 DFF_14 ( .D(UC_17VD), .CK(CK), .Q(n109), .QN(n92) );
  DFF_X1 DFF_15 ( .D(UC_18VD), .CK(CK), .Q(n115), .QN(n91) );
  DFF_X1 DFF_16 ( .D(UC_19VD), .CK(CK), .QN(n90) );
  DFF_X1 DFF_17 ( .D(UC_8VD), .CK(CK), .Q(n112) );
  DFF_X1 DFF_18 ( .D(UC_9VD), .CK(CK), .Q(n114), .QN(n88) );
  DFF_X1 DFF_19 ( .D(UC_10VD), .CK(CK), .QN(n86) );
  DFF_X1 DFF_20 ( .D(UC_11VD), .CK(CK), .Q(n111), .QN(n87) );
  INV_X1 U107 ( .A(n62), .ZN(n7) );
  NAND2_X1 U108 ( .A1(n67), .A2(n28), .ZN(n101) );
  NAND2_X1 U109 ( .A1(n7), .A2(n60), .ZN(n67) );
  NAND2_X1 U110 ( .A1(n49), .A2(n18), .ZN(n39) );
  NOR2_X1 U111 ( .A1(n106), .A2(n108), .ZN(n29) );
  NOR4_X1 U112 ( .A1(n7), .A2(n9), .A3(n57), .A4(n58), .ZN(TCOMB_GA2) );
  INV_X1 U113 ( .A(n56), .ZN(n9) );
  NAND2_X1 U114 ( .A1(n51), .A2(n18), .ZN(n33) );
  NAND2_X1 U115 ( .A1(n78), .A2(n18), .ZN(n74) );
  NAND3_X1 U116 ( .A1(n106), .A2(n108), .A3(n18), .ZN(n56) );
  NAND2_X1 U117 ( .A1(n18), .A2(n110), .ZN(n62) );
  NOR3_X1 U118 ( .A1(n74), .A2(n82), .A3(n81), .ZN(C3_Q0VD) );
  NOR2_X1 U119 ( .A1(n2), .A2(n106), .ZN(n82) );
  NOR3_X1 U120 ( .A1(n76), .A2(n1), .A3(n75), .ZN(C3_Q2VD) );
  NOR2_X1 U121 ( .A1(n79), .A2(n7), .ZN(n76) );
  INV_X1 U122 ( .A(n78), .ZN(n1) );
  NOR2_X1 U123 ( .A1(n56), .A2(n49), .ZN(n79) );
  NOR3_X1 U124 ( .A1(n74), .A2(n77), .A3(n80), .ZN(C3_Q1VD) );
  NOR2_X1 U125 ( .A1(n81), .A2(n108), .ZN(n80) );
  NOR3_X1 U126 ( .A1(n39), .A2(n46), .A3(n47), .ZN(UC_17VD) );
  NOR2_X1 U127 ( .A1(n43), .A2(n109), .ZN(n47) );
  AND2_X1 U128 ( .A1(n43), .A2(n109), .ZN(n46) );
  AND2_X1 U129 ( .A1(n29), .A2(n107), .ZN(n60) );
  INV_X1 U130 ( .A(n49), .ZN(n2) );
  AND2_X1 U131 ( .A1(n77), .A2(n110), .ZN(n75) );
  INV_X1 U132 ( .A(n42), .ZN(n3) );
  NAND2_X1 U133 ( .A1(n58), .A2(n68), .ZN(n28) );
  NAND2_X1 U134 ( .A1(n63), .A2(n110), .ZN(n68) );
  NOR2_X1 U135 ( .A1(n48), .A2(n39), .ZN(UC_16VD) );
  NOR2_X1 U136 ( .A1(n46), .A2(n113), .ZN(n48) );
  NOR2_X1 U137 ( .A1(n23), .A2(n56), .ZN(TCOMB_YA2) );
  NAND2_X1 U138 ( .A1(n18), .A2(n23), .ZN(n69) );
  NOR2_X1 U139 ( .A1(n111), .A2(n33), .ZN(UC_11VD) );
  NOR2_X1 U140 ( .A1(n37), .A2(n33), .ZN(UC_8VD) );
  NOR2_X1 U141 ( .A1(n34), .A2(n112), .ZN(n37) );
  NOR2_X1 U142 ( .A1(n73), .A2(n74), .ZN(C3_Q3VD) );
  NOR2_X1 U143 ( .A1(n75), .A2(n105), .ZN(n73) );
  NAND2_X1 U144 ( .A1(n18), .A2(n20), .ZN(n104) );
  NAND2_X1 U145 ( .A1(n5), .A2(n21), .ZN(n20) );
  INV_X1 U146 ( .A(n23), .ZN(n5) );
  NAND2_X1 U147 ( .A1(n105), .A2(n22), .ZN(n21) );
  NOR2_X1 U148 ( .A1(n64), .A2(n65), .ZN(R2C) );
  NOR2_X1 U149 ( .A1(n66), .A2(n109), .ZN(n64) );
  NOR2_X1 U150 ( .A1(n101), .A2(n66), .ZN(n65) );
  AND2_X1 U151 ( .A1(n69), .A2(n70), .ZN(n66) );
  NOR2_X1 U152 ( .A1(n24), .A2(n25), .ZN(Y1C) );
  NOR2_X1 U153 ( .A1(n26), .A2(n109), .ZN(n24) );
  NOR2_X1 U154 ( .A1(n101), .A2(n26), .ZN(n25) );
  AND2_X1 U155 ( .A1(n27), .A2(n28), .ZN(n26) );
  NOR4_X1 U156 ( .A1(n107), .A2(n105), .A3(n108), .A4(n98), .ZN(n63) );
  NOR3_X1 U157 ( .A1(n91), .A2(n90), .A3(n3), .ZN(n43) );
  NOR3_X1 U158 ( .A1(n87), .A2(n86), .A3(n88), .ZN(n34) );
  NOR3_X1 U159 ( .A1(CLR), .A2(n96), .A3(n106), .ZN(n57) );
  NAND3_X1 U160 ( .A1(n42), .A2(n113), .A3(n84), .ZN(n49) );
  NAND3_X1 U161 ( .A1(n91), .A2(n92), .A3(n90), .ZN(n84) );
  NOR2_X1 U162 ( .A1(n98), .A2(n49), .ZN(n81) );
  NOR3_X1 U163 ( .A1(n98), .A2(n97), .A3(n49), .ZN(n77) );
  NOR2_X1 U164 ( .A1(n100), .A2(CLR), .ZN(n58) );
  NOR4_X1 U165 ( .A1(n59), .A2(n60), .A3(n61), .A4(n62), .ZN(TCOMB_GA1) );
  NOR2_X1 U166 ( .A1(n96), .A2(n94), .ZN(n61) );
  NOR2_X1 U167 ( .A1(n100), .A2(n63), .ZN(n59) );
  NOR3_X1 U168 ( .A1(CLR), .A2(n54), .A3(n55), .ZN(TESTLVIINLATCHVCDAD) );
  AND2_X1 U169 ( .A1(n19), .A2(n95), .ZN(n54) );
  NOR2_X1 U170 ( .A1(n95), .A2(n19), .ZN(n55) );
  INV_X1 U171 ( .A(TEST), .ZN(n19) );
  NAND2_X1 U172 ( .A1(n95), .A2(n51), .ZN(n42) );
  NAND2_X1 U173 ( .A1(n99), .A2(n100), .ZN(n23) );
  NAND2_X1 U174 ( .A1(n85), .A2(n112), .ZN(n51) );
  NAND3_X1 U175 ( .A1(n87), .A2(n88), .A3(n86), .ZN(n85) );
  NOR3_X1 U176 ( .A1(CLR), .A2(n71), .A3(n72), .ZN(FMLVIINLATCHVCDAD) );
  AND2_X1 U177 ( .A1(n107), .A2(FM), .ZN(n72) );
  NOR2_X1 U178 ( .A1(FM), .A2(n107), .ZN(n71) );
  NOR3_X1 U179 ( .A1(n33), .A2(n34), .A3(n35), .ZN(UC_9VD) );
  NOR2_X1 U180 ( .A1(n36), .A2(n114), .ZN(n35) );
  NOR2_X1 U181 ( .A1(n86), .A2(n87), .ZN(n36) );
  NOR3_X1 U182 ( .A1(n39), .A2(n43), .A3(n44), .ZN(UC_18VD) );
  NOR2_X1 U183 ( .A1(n45), .A2(n115), .ZN(n44) );
  NOR2_X1 U184 ( .A1(n90), .A2(n3), .ZN(n45) );
  NAND3_X1 U185 ( .A1(n83), .A2(n105), .A3(n2), .ZN(n78) );
  NAND2_X1 U186 ( .A1(n99), .A2(n29), .ZN(n83) );
  NAND2_X1 U187 ( .A1(n97), .A2(n106), .ZN(n22) );
  NOR2_X1 U188 ( .A1(n38), .A2(n39), .ZN(UC_19VD) );
  NOR2_X1 U189 ( .A1(n40), .A2(n41), .ZN(n38) );
  AND2_X1 U190 ( .A1(n42), .A2(n90), .ZN(n40) );
  NOR2_X1 U191 ( .A1(n90), .A2(n42), .ZN(n41) );
  NOR2_X1 U192 ( .A1(n50), .A2(n33), .ZN(UC_10VD) );
  NOR2_X1 U193 ( .A1(n52), .A2(n53), .ZN(n50) );
  AND2_X1 U194 ( .A1(n111), .A2(n86), .ZN(n52) );
  NOR2_X1 U195 ( .A1(n86), .A2(n111), .ZN(n53) );
  NAND2_X1 U196 ( .A1(n57), .A2(n97), .ZN(n70) );
  NAND2_X1 U197 ( .A1(n29), .A2(n30), .ZN(n27) );
  NAND2_X1 U198 ( .A1(n31), .A2(n32), .ZN(n30) );
  NAND3_X1 U199 ( .A1(n18), .A2(n105), .A3(n99), .ZN(n31) );
  NAND3_X1 U200 ( .A1(n96), .A2(n107), .A3(n7), .ZN(n32) );
  INV_X1 U201 ( .A(CLR), .ZN(n18) );
endmodule

