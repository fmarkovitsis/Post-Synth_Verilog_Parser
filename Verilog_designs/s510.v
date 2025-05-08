/////////////////////////////////////////////////////////////
// Created by: Synopsys DC Expert(TM) in wire load mode
// Version   : O-2018.06-SP4
// Date      : Sun Nov 22 10:19:33 2020
/////////////////////////////////////////////////////////////


module s510 ( GND, VDD, CK, cblank, cclr, cnt10, cnt13, cnt21, cnt261, cnt272, 
        cnt283, cnt284, cnt44, cnt45, cnt509, cnt511, cnt567, cnt591, csm, 
        csync, john, pc, pclr, pcnt12, pcnt17, pcnt241, pcnt27, pcnt6, vsync
 );
  input GND, VDD, CK, cnt10, cnt13, cnt21, cnt261, cnt272, cnt283, cnt284,
         cnt44, cnt45, cnt509, cnt511, cnt567, cnt591, john, pcnt12, pcnt17,
         pcnt241, pcnt27, pcnt6;
  output cblank, cclr, csm, csync, pc, pclr, vsync;
  wire   st_5, st_4, st_3, st_2, st_1, st_0, n1, n2, n3, n4, n5, n6, n7, n8,
         n9, n10, n11, n12, n13, n14, n15, n16, n17, n18, n19, n20, n21, n22,
         n23, n24, n25, n26, n27, n28, n29, n30, n31, n32, n33, n34, n35, n36,
         n37, n38, n39, n40, n41, n42, n43, n44, n45, n46, n47, n48, n49, n50,
         n51, n52, n53, n54, n55, n56, n57, n58, n59, n60, n61, n62, n63, n64,
         n65, n66, n67, n68, n69, n70, n71, n72, n73, n74, n75, n76, n77, n78,
         n79, n80, n81, n82, n83, n84, n85, n86, n87, n88, n89, n90, n91, n92,
         n93, n94, n95, n96, n97, n98, n99, n100, n101, n102, n103, n104, n105,
         n106, n107, n108, n109, n110, n111, n112, n113, n114, n115, n116,
         n117, n118, n119, n120, n121, n122, n123, n124, n125, n126, n127,
         n128, n129, n130, n131, n132, n133, n134, n135, n136, n137, n138,
         n139, n140, n141, n142, n143, n144, n145, n146, n147, n148, n149,
         n150, n151, n152, n153, n154, n155, n156, n157, n158, n159, n160,
         n161, n162, n163, n164, n165, n166, n167, n168, n169, n170, n171,
         n172, n173, n174, n175, n180, n182, n184;

  DFF_X1 DFF_0 ( .D(n182), .CK(CK), .Q(st_5), .QN(n4) );
  DFF_X1 DFF_2 ( .D(n184), .CK(CK), .Q(st_3), .QN(n12) );
  DFF_X1 DFF_3 ( .D(n174), .CK(CK), .Q(st_2), .QN(n16) );
  DFF_X1 DFF_1 ( .D(n175), .CK(CK), .Q(st_4), .QN(n8) );
  DFF_X1 DFF_5 ( .D(n173), .CK(CK), .Q(st_0), .QN(n18) );
  DFF_X1 DFF_4 ( .D(n180), .CK(CK), .Q(st_1), .QN(n17) );
  INV_X1 U186 ( .A(n33), .ZN(n3) );
  INV_X1 U187 ( .A(n74), .ZN(n14) );
  INV_X1 U188 ( .A(n117), .ZN(n2) );
  INV_X1 U189 ( .A(n121), .ZN(n11) );
  INV_X1 U190 ( .A(n123), .ZN(n10) );
  NOR2_X1 U191 ( .A1(n58), .A2(n16), .ZN(n39) );
  NOR2_X1 U192 ( .A1(n86), .A2(n33), .ZN(n90) );
  NAND2_X1 U193 ( .A1(n18), .A2(n16), .ZN(n98) );
  NOR3_X1 U194 ( .A1(n74), .A2(n4), .A3(n18), .ZN(n73) );
  NAND2_X1 U195 ( .A1(n8), .A2(n4), .ZN(n33) );
  NOR3_X1 U196 ( .A1(n86), .A2(n10), .A3(n4), .ZN(n131) );
  NAND3_X1 U197 ( .A1(n11), .A2(n16), .A3(n3), .ZN(n117) );
  INV_X1 U198 ( .A(n86), .ZN(n15) );
  NOR2_X1 U199 ( .A1(n58), .A2(n87), .ZN(n130) );
  INV_X1 U200 ( .A(n116), .ZN(n13) );
  NAND2_X1 U201 ( .A1(n17), .A2(n12), .ZN(n121) );
  NAND2_X1 U202 ( .A1(n115), .A2(n116), .ZN(n74) );
  NAND2_X1 U203 ( .A1(n16), .A2(n17), .ZN(n115) );
  INV_X1 U204 ( .A(n106), .ZN(n7) );
  INV_X1 U205 ( .A(n34), .ZN(n5) );
  INV_X1 U206 ( .A(n87), .ZN(n6) );
  NAND2_X1 U207 ( .A1(n33), .A2(n16), .ZN(n99) );
  INV_X1 U208 ( .A(n58), .ZN(n9) );
  NAND3_X1 U209 ( .A1(n41), .A2(n42), .A3(n43), .ZN(n40) );
  NAND2_X1 U210 ( .A1(n39), .A2(n59), .ZN(n42) );
  NAND2_X1 U211 ( .A1(n13), .A2(n62), .ZN(n41) );
  NAND2_X1 U212 ( .A1(n44), .A2(n16), .ZN(n43) );
  NAND2_X1 U213 ( .A1(n4), .A2(n50), .ZN(n49) );
  NAND2_X1 U214 ( .A1(n12), .A2(n8), .ZN(n50) );
  NAND2_X1 U215 ( .A1(n81), .A2(n19), .ZN(n80) );
  NAND4_X1 U216 ( .A1(n69), .A2(n70), .A3(n71), .A4(n72), .ZN(n174) );
  NAND2_X1 U217 ( .A1(n90), .A2(n17), .ZN(n69) );
  NAND2_X1 U218 ( .A1(n75), .A2(n18), .ZN(n71) );
  NOR3_X1 U219 ( .A1(n73), .A2(n7), .A3(n39), .ZN(n72) );
  NAND2_X1 U220 ( .A1(n170), .A2(n99), .ZN(n169) );
  NAND2_X1 U221 ( .A1(n18), .A2(n4), .ZN(n170) );
  NAND3_X1 U222 ( .A1(n24), .A2(n25), .A3(n26), .ZN(n173) );
  NAND2_X1 U223 ( .A1(n6), .A2(n39), .ZN(n24) );
  NOR3_X1 U224 ( .A1(n27), .A2(n28), .A3(n29), .ZN(n26) );
  NAND2_X1 U225 ( .A1(n40), .A2(n18), .ZN(n25) );
  NOR2_X1 U226 ( .A1(n19), .A2(n23), .ZN(n136) );
  NOR2_X1 U227 ( .A1(n3), .A2(n86), .ZN(n109) );
  NOR2_X1 U228 ( .A1(n81), .A2(n114), .ZN(n122) );
  NAND2_X1 U229 ( .A1(n123), .A2(n124), .ZN(n114) );
  NOR2_X1 U230 ( .A1(n171), .A2(n34), .ZN(csm) );
  NOR2_X1 U231 ( .A1(n172), .A2(n10), .ZN(n171) );
  NOR2_X1 U232 ( .A1(n18), .A2(n12), .ZN(n172) );
  NAND2_X1 U233 ( .A1(n149), .A2(n150), .ZN(pclr) );
  NAND2_X1 U234 ( .A1(n90), .A2(n10), .ZN(n149) );
  NAND3_X1 U235 ( .A1(n13), .A2(n12), .A3(n6), .ZN(n150) );
  NAND2_X1 U236 ( .A1(st_4), .A2(st_0), .ZN(n87) );
  NOR2_X1 U237 ( .A1(st_1), .A2(st_5), .ZN(n81) );
  NAND2_X1 U238 ( .A1(st_0), .A2(n16), .ZN(n86) );
  NAND2_X1 U239 ( .A1(st_1), .A2(st_2), .ZN(n116) );
  NAND2_X1 U240 ( .A1(st_3), .A2(st_1), .ZN(n123) );
  NAND2_X1 U241 ( .A1(st_3), .A2(n17), .ZN(n58) );
  NOR3_X1 U242 ( .A1(n121), .A2(st_0), .A3(n16), .ZN(n35) );
  NAND3_X1 U243 ( .A1(st_2), .A2(n8), .A3(st_3), .ZN(n106) );
  NOR3_X1 U244 ( .A1(n116), .A2(n144), .A3(n12), .ZN(n141) );
  NOR2_X1 U245 ( .A1(pcnt241), .A2(n21), .ZN(n144) );
  INV_X1 U246 ( .A(cnt511), .ZN(n21) );
  NOR3_X1 U247 ( .A1(n18), .A2(st_3), .A3(n30), .ZN(n29) );
  NOR2_X1 U248 ( .A1(n31), .A2(n32), .ZN(n30) );
  NOR3_X1 U249 ( .A1(n34), .A2(st_1), .A3(cnt261), .ZN(n31) );
  NOR2_X1 U250 ( .A1(n14), .A2(n33), .ZN(n32) );
  NOR3_X1 U251 ( .A1(n123), .A2(st_2), .A3(n143), .ZN(n142) );
  NOR2_X1 U252 ( .A1(pcnt27), .A2(n22), .ZN(n143) );
  INV_X1 U253 ( .A(cnt567), .ZN(n22) );
  NOR2_X1 U254 ( .A1(n36), .A2(n8), .ZN(n27) );
  NOR2_X1 U255 ( .A1(n37), .A2(n38), .ZN(n36) );
  AND2_X1 U256 ( .A1(n39), .A2(cnt21), .ZN(n37) );
  AND2_X1 U257 ( .A1(n35), .A2(cnt45), .ZN(n38) );
  NAND2_X1 U258 ( .A1(st_1), .A2(st_5), .ZN(n124) );
  NOR2_X1 U259 ( .A1(st_3), .A2(n133), .ZN(n132) );
  NOR2_X1 U260 ( .A1(n134), .A2(n135), .ZN(n133) );
  NOR2_X1 U261 ( .A1(n16), .A2(n87), .ZN(n135) );
  NOR4_X1 U262 ( .A1(st_5), .A2(n136), .A3(n18), .A4(n116), .ZN(n134) );
  NAND2_X1 U263 ( .A1(st_5), .A2(st_2), .ZN(n34) );
  NOR2_X1 U264 ( .A1(n167), .A2(n168), .ZN(n166) );
  NOR2_X1 U265 ( .A1(st_1), .A2(n106), .ZN(n168) );
  NOR2_X1 U266 ( .A1(n121), .A2(n87), .ZN(n167) );
  NAND2_X1 U267 ( .A1(st_1), .A2(n82), .ZN(n70) );
  NAND2_X1 U268 ( .A1(n83), .A2(n84), .ZN(n82) );
  NAND2_X1 U269 ( .A1(n85), .A2(n12), .ZN(n84) );
  NAND2_X1 U270 ( .A1(n15), .A2(st_4), .ZN(n83) );
  NAND3_X1 U271 ( .A1(n138), .A2(n139), .A3(n140), .ZN(n137) );
  NAND2_X1 U272 ( .A1(st_1), .A2(n33), .ZN(n138) );
  OR2_X1 U273 ( .A1(st_3), .A2(n145), .ZN(n139) );
  NOR3_X1 U274 ( .A1(n141), .A2(n2), .A3(n142), .ZN(n140) );
  NOR3_X1 U275 ( .A1(n146), .A2(n5), .A3(n147), .ZN(n145) );
  NOR3_X1 U276 ( .A1(n17), .A2(st_2), .A3(n148), .ZN(n147) );
  NOR2_X1 U277 ( .A1(cnt13), .A2(n116), .ZN(n146) );
  NOR2_X1 U278 ( .A1(pcnt12), .A2(n20), .ZN(n148) );
  NAND2_X1 U279 ( .A1(st_4), .A2(n54), .ZN(n45) );
  NAND3_X1 U280 ( .A1(n55), .A2(n56), .A3(n57), .ZN(n54) );
  NAND2_X1 U281 ( .A1(cnt21), .A2(n12), .ZN(n57) );
  NAND2_X1 U282 ( .A1(cnt283), .A2(n10), .ZN(n55) );
  NAND3_X1 U283 ( .A1(n86), .A2(n87), .A3(n88), .ZN(n85) );
  NAND3_X1 U284 ( .A1(n89), .A2(n4), .A3(st_0), .ZN(n88) );
  NAND2_X1 U285 ( .A1(cnt284), .A2(n23), .ZN(n89) );
  NAND4_X1 U286 ( .A1(n155), .A2(n156), .A3(n98), .A4(n58), .ZN(n154) );
  NAND3_X1 U287 ( .A1(n18), .A2(n12), .A3(st_1), .ZN(n156) );
  NAND2_X1 U288 ( .A1(st_0), .A2(n157), .ZN(n155) );
  NAND2_X1 U289 ( .A1(n12), .A2(n16), .ZN(n157) );
  NAND2_X1 U290 ( .A1(n81), .A2(n95), .ZN(n93) );
  NAND2_X1 U291 ( .A1(n96), .A2(n97), .ZN(n95) );
  OR2_X1 U292 ( .A1(n98), .A2(st_3), .ZN(n97) );
  NAND2_X1 U293 ( .A1(n15), .A2(st_3), .ZN(n96) );
  NAND4_X1 U294 ( .A1(n45), .A2(n46), .A3(n47), .A4(n48), .ZN(n44) );
  NAND3_X1 U295 ( .A1(st_5), .A2(n17), .A3(cnt45), .ZN(n47) );
  NAND3_X1 U296 ( .A1(st_1), .A2(n49), .A3(cnt44), .ZN(n48) );
  NAND2_X1 U297 ( .A1(n3), .A2(n51), .ZN(n46) );
  NAND3_X1 U298 ( .A1(n63), .A2(n64), .A3(n65), .ZN(n62) );
  NAND3_X1 U299 ( .A1(st_5), .A2(n12), .A3(cnt10), .ZN(n63) );
  NAND2_X1 U300 ( .A1(st_4), .A2(n66), .ZN(n65) );
  NAND3_X1 U301 ( .A1(st_3), .A2(n3), .A3(cnt511), .ZN(n64) );
  NAND2_X1 U302 ( .A1(cnt13), .A2(n4), .ZN(n78) );
  NAND4_X1 U303 ( .A1(n91), .A2(n92), .A3(n93), .A4(n94), .ZN(n175) );
  NAND2_X1 U304 ( .A1(st_4), .A2(n18), .ZN(n91) );
  NAND2_X1 U305 ( .A1(n10), .A2(n5), .ZN(n92) );
  NAND3_X1 U306 ( .A1(st_0), .A2(n3), .A3(n14), .ZN(n94) );
  NAND4_X1 U307 ( .A1(n163), .A2(n164), .A3(n165), .A4(n166), .ZN(n184) );
  OR2_X1 U308 ( .A1(n124), .A2(n18), .ZN(n165) );
  NAND2_X1 U309 ( .A1(st_3), .A2(n169), .ZN(n163) );
  NAND3_X1 U310 ( .A1(st_1), .A2(n8), .A3(n15), .ZN(n164) );
  AND4_X1 U311 ( .A1(pcnt6), .A2(cnt284), .A3(n3), .A4(n35), .ZN(n28) );
  NAND2_X1 U312 ( .A1(n67), .A2(n68), .ZN(n66) );
  NAND2_X1 U313 ( .A1(cnt10), .A2(st_3), .ZN(n68) );
  NAND2_X1 U314 ( .A1(john), .A2(n12), .ZN(n67) );
  NAND2_X1 U315 ( .A1(n60), .A2(n61), .ZN(n59) );
  NAND2_X1 U316 ( .A1(cnt509), .A2(st_5), .ZN(n60) );
  NAND2_X1 U317 ( .A1(cnt272), .A2(n3), .ZN(n61) );
  NAND3_X1 U318 ( .A1(n151), .A2(n152), .A3(n153), .ZN(n182) );
  NAND3_X1 U319 ( .A1(st_0), .A2(st_2), .A3(n10), .ZN(n151) );
  NAND3_X1 U320 ( .A1(n11), .A2(n8), .A3(n15), .ZN(n152) );
  NAND2_X1 U321 ( .A1(st_5), .A2(n154), .ZN(n153) );
  NAND2_X1 U322 ( .A1(n52), .A2(n53), .ZN(n51) );
  NAND2_X1 U323 ( .A1(cnt567), .A2(n10), .ZN(n52) );
  NAND2_X1 U324 ( .A1(cnt591), .A2(n9), .ZN(n53) );
  NAND2_X1 U325 ( .A1(cnt45), .A2(n9), .ZN(n56) );
  NAND2_X1 U326 ( .A1(n76), .A2(n77), .ZN(n75) );
  NAND2_X1 U327 ( .A1(st_2), .A2(n79), .ZN(n76) );
  NAND2_X1 U328 ( .A1(n13), .A2(n78), .ZN(n77) );
  NAND2_X1 U329 ( .A1(n8), .A2(n80), .ZN(n79) );
  NAND3_X1 U330 ( .A1(n127), .A2(n128), .A3(n129), .ZN(n180) );
  NAND2_X1 U331 ( .A1(n7), .A2(st_0), .ZN(n127) );
  NOR3_X1 U332 ( .A1(n130), .A2(n131), .A3(n132), .ZN(n129) );
  NAND2_X1 U333 ( .A1(n137), .A2(n18), .ZN(n128) );
  NOR2_X1 U334 ( .A1(st_1), .A2(n98), .ZN(n104) );
  NOR2_X1 U335 ( .A1(st_1), .A2(n87), .ZN(n110) );
  NAND4_X1 U336 ( .A1(n86), .A2(n87), .A3(n117), .A4(n118), .ZN(cclr) );
  NOR2_X1 U337 ( .A1(n119), .A2(n120), .ZN(n118) );
  AND2_X1 U338 ( .A1(n35), .A2(st_5), .ZN(n120) );
  NOR2_X1 U339 ( .A1(n122), .A2(n18), .ZN(n119) );
  AND2_X1 U340 ( .A1(st_2), .A2(n81), .ZN(n103) );
  NAND2_X1 U341 ( .A1(n124), .A2(n162), .ZN(n161) );
  NAND2_X1 U342 ( .A1(n10), .A2(st_4), .ZN(n162) );
  NAND4_X1 U343 ( .A1(n105), .A2(n106), .A3(n107), .A4(n108), .ZN(csync) );
  NAND2_X1 U344 ( .A1(n111), .A2(n18), .ZN(n107) );
  NAND3_X1 U345 ( .A1(st_0), .A2(n3), .A3(n13), .ZN(n105) );
  NOR2_X1 U346 ( .A1(n109), .A2(n110), .ZN(n108) );
  INV_X1 U347 ( .A(cnt284), .ZN(n19) );
  INV_X1 U348 ( .A(pcnt17), .ZN(n23) );
  NAND3_X1 U349 ( .A1(n112), .A2(n113), .A3(n1), .ZN(n111) );
  INV_X1 U350 ( .A(n114), .ZN(n1) );
  NAND2_X1 U351 ( .A1(n14), .A2(n8), .ZN(n113) );
  NAND2_X1 U352 ( .A1(st_3), .A2(n3), .ZN(n112) );
  NAND4_X1 U353 ( .A1(n99), .A2(n100), .A3(n101), .A4(n102), .ZN(vsync) );
  NAND2_X1 U354 ( .A1(n13), .A2(n8), .ZN(n100) );
  NAND2_X1 U355 ( .A1(st_0), .A2(st_1), .ZN(n101) );
  NOR3_X1 U356 ( .A1(n103), .A2(st_3), .A3(n104), .ZN(n102) );
  NAND3_X1 U357 ( .A1(n125), .A2(n117), .A3(n126), .ZN(pc) );
  NAND2_X1 U358 ( .A1(n90), .A2(n123), .ZN(n126) );
  NAND3_X1 U359 ( .A1(n10), .A2(st_2), .A3(n6), .ZN(n125) );
  NAND3_X1 U360 ( .A1(n158), .A2(n159), .A3(n160), .ZN(cblank) );
  NAND2_X1 U361 ( .A1(n15), .A2(n161), .ZN(n159) );
  NAND2_X1 U362 ( .A1(n7), .A2(n18), .ZN(n160) );
  NAND2_X1 U363 ( .A1(st_3), .A2(n5), .ZN(n158) );
  INV_X1 U364 ( .A(cnt44), .ZN(n20) );
endmodule

