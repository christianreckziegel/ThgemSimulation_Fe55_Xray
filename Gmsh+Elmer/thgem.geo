//
// Parameters:
//

ccd=0.1; ref1=0.01; ref2=0.005; //cm
conductor_radius = 0.06/2; //cm
dielectric_radius = 0.05/2; //cm
conductor_thickness= 0.001;//cm
dielectric_thickness= 0.05; //cm
drift_length=0.9; //cm, originally 0.5cm
induction_length=0.9; //cm, originally 0.5cm

//
//
//
// FIRST LAYER
//
//
//

// Upper left semi circle
x=-ccd/4; y=ccd*Sqrt(3)/2; z=conductor_thickness+dielectric_thickness/2;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p1=newp; Point(p1)={x+radius, y, z, ref2};
p2=newp; Point(p2)={x, y-radius, z, ref2};

c1=newc; Circle(c1)={p1, center, p2};


// Middle right semi circle

x=ccd/4; y=0; z=conductor_thickness+dielectric_thickness/2;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p3=newp; Point(p3)={x, y+radius, z, ref2};
p4=newp; Point(p4)={x-radius, y, z, ref2};
p5=newp; Point(p5)={x, y-radius, z, ref2};

c3=newc; Circle(c3)={p3, center, p4};
c4=newc; Circle(c4)={p4, center, p5};

// Lower left semi circle
x=-ccd/4; y=-ccd*Sqrt(3)/2; z=conductor_thickness+dielectric_thickness/2;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p6=newp; Point(p6)={x, y+radius, z, ref2};
p7=newp; Point(p7)={x+radius, y, z, ref2};

c5=newc; Circle(c5)={p6, center, p7};

//
//
//
// SECOND LAYER
//
//
//

// Upper left semi circle
x=-ccd/4; y=ccd*Sqrt(3)/2; z=dielectric_thickness/2;

radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p8=newp; Point(p8)={x+radius, y, z, ref2};
p9=newp; Point(p9)={x, y-radius, z, ref2};

c6=newc; Circle(c6)={p8, center, p9};

radius=dielectric_radius;

p10=newp; Point(p10)={x+radius, y, z, ref2};
p11=newp; Point(p11)={x, y-radius, z, ref2};

c7=newc; Circle(c7)={p10, center, p11};

// Middle right semi circle

x=ccd/4; y=0;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p12=newp; Point(p12)={x, y+radius, z, ref2};
p13=newp; Point(p13)={x-radius, y, z, ref2};
p14=newp; Point(p14)={x, y-radius, z, ref2};

c8=newc; Circle(c8)={p12, center, p13};
c9=newc; Circle(c9)={p13, center, p14};

radius=dielectric_radius;

p15=newp; Point(p15)={x, y+radius, z, ref2};
p16=newp; Point(p16)={x-radius, y, z, ref2};
p17=newp; Point(p17)={x, y-radius, z, ref2};

c10=newc; Circle(c10)={p15, center, p16};
c11=newc; Circle(c11)={p16, center, p17};

// Lower left semi circle

x=-ccd/4; y=-ccd*Sqrt(3)/2;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p18=newp; Point(p18)={x, y+radius, z, ref2};
p19=newp; Point(p19)={x+radius, y, z, ref2};

c12=newc; Circle(c12)={p18, center, p19};

radius=dielectric_radius;

p20=newp; Point(p20)={x, y+radius, z, ref2};
p21=newp; Point(p21)={x+radius, y, z, ref2};

c13=newc; Circle(c13)={p20, center, p21};

//
//
//
// THIRD LAYER
//
//
//

/// Upper left semi circle
x=-ccd/4; y=ccd*Sqrt(3)/2; z=-dielectric_thickness/2;

radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p22=newp; Point(p22)={x+radius, y, z, ref2};
p23=newp; Point(p23)={x, y-radius, z, ref2};

c14=newc; Circle(c14)={p22, center, p23};

radius=dielectric_radius;

p24=newp; Point(p24)={x+radius, y, z, ref2};
p25=newp; Point(p25)={x, y-radius, z, ref2};

c15=newc; Circle(c15)={p24, center, p25};

// Middle right semi circle

x=ccd/4; y=0;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p26=newp; Point(p26)={x, y+radius, z, ref2};
p27=newp; Point(p27)={x-radius, y, z, ref2};
p28=newp; Point(p28)={x, y-radius, z, ref2};

c16=newc; Circle(c16)={p26, center, p27};
c17=newc; Circle(c17)={p27, center, p28};

radius=dielectric_radius;

p29=newp; Point(p29)={x, y+radius, z, ref2};
p30=newp; Point(p30)={x-radius, y, z, ref2};
p31=newp; Point(p31)={x, y-radius, z, ref2};

c18=newc; Circle(c18)={p29, center, p30};
c19=newc; Circle(c19)={p30, center, p31};

// Lower left semi circle

x=-ccd/4; y=-ccd*Sqrt(3)/2;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p32=newp; Point(p32)={x, y+radius, z, ref2};
p33=newp; Point(p33)={x+radius, y, z, ref2};

c20=newc; Circle(c20)={p32, center, p33};

radius=dielectric_radius;

p34=newp; Point(p34)={x, y+radius, z, ref2};
p35=newp; Point(p35)={x+radius, y, z, ref2};

c21=newc; Circle(c21)={p34, center, p35};

//
//
//
// FOURTH LAYER
//
//
//

// Upper left semi circle
x=-ccd/4; y=ccd*Sqrt(3)/2; z=-conductor_thickness-dielectric_thickness/2;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p36=newp; Point(p36)={x+radius, y, z, ref2};
p37=newp; Point(p37)={x, y-radius, z, ref2};

c22=newc; Circle(c22)={p36, center, p37};


// Middle right semi circle

x=ccd/4; y=0;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p38=newp; Point(p38)={x, y+radius, z, ref2};
p39=newp; Point(p39)={x-radius, y, z, ref2};
p40=newp; Point(p40)={x, y-radius, z, ref2};

c23=newc; Circle(c23)={p38, center, p39};
c24=newc; Circle(c24)={p39, center, p40};

// Lower left semi circle
x=-ccd/4; y=-ccd*Sqrt(3)/2;
radius=conductor_radius;

center=newp; Point(center)={x,y,z,ref2};
p41=newp; Point(p41)={x, y+radius, z, ref2};
p42=newp; Point(p42)={x+radius, y, z, ref2};

c25=newc; Circle(c25)={p41, center, p42};

//
// Adding corners
//
x=ccd/4; y=ccd*Sqrt(3)/2; z=conductor_thickness+dielectric_thickness/2;
p43=newp; Point(p43)={x, y, z, ref1};

x=ccd/4; y=-ccd*Sqrt(3)/2;
p44=newp; Point(p44)={x, y, z, ref1};

x=ccd/4; y=ccd*Sqrt(3)/2; z=dielectric_thickness/2;
p45=newp; Point(p45)={x, y, z, ref1};

x=ccd/4; y=-ccd*Sqrt(3)/2;
p46=newp; Point(p46)={x, y, z, ref1};

x=ccd/4; y=ccd*Sqrt(3)/2; z=-dielectric_thickness/2;
p47=newp; Point(p47)={x, y, z, ref1};

x=ccd/4; y=-ccd*Sqrt(3)/2;
p48=newp; Point(p48)={x, y, z, ref1};

x=ccd/4; y=ccd*Sqrt(3)/2; z=-conductor_thickness-dielectric_thickness/2;
p49=newp; Point(p49)={x, y, z, ref1};

x=ccd/4; y=-ccd*Sqrt(3)/2;
p50=newp; Point(p50)={x, y, z, ref1};

x=-ccd/4; y=ccd*Sqrt(3)/2; z=conductor_thickness+dielectric_thickness/2+induction_length;
p51=newp; Point(p51)={x,y,z,ref1};
x=ccd/4;
p52=newp; Point(p52)={x,y,z,ref1};
y=-ccd*Sqrt(3)/2;
p53=newp; Point(p53)={x,y,z,ref1};
x=-ccd/4;
p54=newp; Point(p54)={x,y,z,ref1};

x=-ccd/4; y=ccd*Sqrt(3)/2; z=-conductor_thickness-dielectric_thickness/2-drift_length;
p55=newp; Point(p55)={x,y,z,ref1};
x=ccd/4;
p56=newp; Point(p56)={x,y,z,ref1};
y=-ccd*Sqrt(3)/2;
p57=newp; Point(p57)={x,y,z,ref1};
x=-ccd/4;
p58=newp; Point(p58)={x,y,z,ref1};

//
//
//
// ADDING LINES
//
//
//

Line(25) = {64, 63}; Line(26) = {64, 65}; Line(27) = {65, 66}; Line(28) = {63, 66};
Line(29) = {65, 56}; Line(30) = {56, 10}; Line(31) = {10, 25}; Line(32) = {25, 58};
Line(33) = {58, 56}; Line(34) = {56, 7}; Line(35) = {58, 19}; Line(36) = {7, 19};
Line(37) = {6, 18}; Line(38) = {19, 22}; Line(39) = {18, 21}; Line(40) = {5, 17};
Line(41) = {17, 20}; Line(42) = {17, 57}; Line(43) = {5, 55}; Line(44) = {55, 57};
Line(45) = {55, 2}; Line(46) = {2, 12}; Line(47) = {12, 57}; Line(48) = {13, 3};
Line(49) = {13, 15}; Line(50) = {14, 12}; Line(51) = {3, 9}; Line(52) = {13, 24};
Line(53) = {24, 9}; Line(54) = {24, 26}; Line(55) = {25, 27}; Line(56) = {64, 55}; 
Line(57) = {57, 59}; Line(58) = {59, 29}; Line(59) = {29, 31}; Line(60) = {31, 14};
Line(61) = {32, 15}; Line(62) = {32, 30}; Line(63) = {30, 41}; Line(64) = {41, 43};
Line(65) = {43, 26}; Line(66) = {44, 42}; Line(67) = {42, 60}; Line(68) = {60, 58};
Line(69) = {27, 44}; Line(70) = {22, 39}; Line(71) = {39, 36}; Line(72) = {36, 60};
Line(73) = {21, 38}; Line(74) = {38, 35}; Line(75) = {20, 37}; Line(76) = {37, 34};
Line(77) = {34, 59}; Line(78) = {35, 50}; Line(79) = {36, 51}; Line(80) = {51, 62};
Line(81) = {62, 60}; Line(82) = {62, 54}; Line(83) = {54, 42}; Line(84) = {53, 41};
Line(85) = {53, 47}; Line(86) = {47, 30}; Line(87) = {46, 29}; Line(88) = {46, 61};
Line(89) = {61, 59}; Line(90) = {61, 49}; Line(91) = {49, 34}; Line(92) = {62, 69};
Line(93) = {69, 68}; Line(94) = {68, 61}; Line(95) = {68, 67}; Line(96) = {67, 70};
Line(97) = {70, 69}; Line(98) = {63, 67}; Line(99) = {66, 70};

//
//
//
// ADDING SURFACES
//
//
//

Line Loop(100) = {28, 99, -96, -98}; Line Loop(101) = {51, -53, 54, -65, -64, -84, 85, 86, -62, 61, -49, 48}; Plane Surface(102) = {100, 101};
Line Loop(103) = {25, 98, -95, 94, -88, 87, 59, 60, 50, -46, -45, -56}; Plane Surface(104) = {103};
Line Loop(105) = {26, 29, 34, 36, 38, 70, 71, 79, 80, 92, 93, 94, 90, 91, -76, -75, -41, -40, 43, -56}; Plane Surface(106) = {105};
Line Loop(107) = {27, 99, 97, -92, 82, 83, -66, -69, -55, -31, -30, -29}; Plane Surface(108) = {107};
Line Loop(109) = {25, 28, -27, -26}; Plane Surface(110) = {109};
Line Loop(111) = {97, 93, 95, 96}; Plane Surface(112) = {111};
Line Loop(113) = {45, 1, 51, 4, -30, 34, -3, -2, 43}; Plane Surface(114) = {113};
Line Loop(115) = {80, 82, -24, 85, -21, 88, 90, 22, 23}; Plane Surface(116) = {115};
Line Loop(117) = {11, 55, -12, -54}; Plane Surface(118) = {117};
Line Loop(119) = {19, -66, -20, -64}; Plane Surface(120) = {119};
Line Loop(121) = {10, -38, -8, -7, 41, 9}; Plane Surface(122) = {121};
Line Loop(123) = {18, 71, -16, -15, -76, 17}; Plane Surface(124) = {123};
Line Loop(125) = {50, 5, 49, -6}; Plane Surface(126) = {125};
Line Loop(127) = {14, 62, -13, 59}; Plane Surface(128) = {127};
Line Loop(129) = {1, -48, -5, -46}; Ruled Surface(130) = {129};
Line Loop(131) = {6, -61, -14, 60}; Ruled Surface(132) = {131};
Line Loop(133) = {87, 13, -86, -21};Ruled Surface(134) = {133};
Line Loop(135) = {3, 36, -8, -37}; Ruled Surface(136) = {135};
Line Loop(137) = {37, -7, -40, 2}; Ruled Surface(138) = {137};
Line Loop(139) = {10, 70, -18, -73}; Ruled Surface(140) = {139}; 
Line Loop(141) = {9, 73, -17, -75}; Ruled Surface(142) = {141};
Line Loop(143) = {79, -23, -78, 16}; Ruled Surface(144) = {143};
Line Loop(145) = {78, -22, 91, 15}; Ruled Surface(146) = {145};
Line Loop(147) = {4, 31, -11, 53}; Ruled Surface(148) = {147};
Line Loop(149) = {12, 69, -20, 65}; Ruled Surface(150) = {149};
Line Loop(151) = {84, 19, -83, -24}; Ruled Surface(152) = {151};
Line Loop(154) = {34, 36, -35, 33}; Plane Surface(155) = {154};
Line Loop(156) = {30, 31, 32, 33}; Plane Surface(157) = {156};
Line Loop(158) = {51, -53, -52, 48}; Plane Surface(159) = {158};
Line Loop(160) = {45, 46, 47, -44}; Plane Surface(161) = {160};
Line Loop(162) = {43, 44, -42, -40}; Plane Surface(163) = {162};
Line Loop(164) = {32, 35, -8, -7, 42, -47, 5, 52, 11}; Plane Surface(165) = {164};
Line Loop(166) = {70, 71, 72, 68, 35, 38}; Plane Surface(167) = {166};
Line Loop(168) = {41, 75, 76, 77, -57, -42}; Plane Surface(169) = {168};
Line Loop(170) = {47, 57, 58, 59, 60, 50}; Plane Surface(171) = {170};
Line Loop(172) = {52, 54, -65, -64, -63, -62, 61, -49}; Plane Surface(173) = {172};
Line Loop(174) = {32, -68, -67, -66, -69, -55}; Plane Surface(175) = {174};
Line Loop(176) = {81, -72, 79, 80}; Plane Surface(177) = {176};
Line Loop(178) = {77, -89, 90, 91}; Plane Surface(179) = {178};
Line Loop(180) = {58, -87, 88, 89}; Plane Surface(181) = {180};
Line Loop(182) = {67, -81, 82, 83}; Plane Surface(183) = {182};
Line Loop(184) = {63, -84, 85, 86}; Plane Surface(185) = {184};
Line Loop(188) = {58, 13, 63, 19, 67, -72, -16, -15, 77}; Plane Surface(189) = {188};

//
//
//
// ADDING VOLUMES
//
//
//


Surface Loop(186) = {110, 104, 102, 108, 112, 106, 148, 114, 130, 136, 138, 150, 118, 120, 152, 116, 134, 128, 132, 126, 146, 144, 124, 140, 122, 142};

Volume(187) = {186}; // Gas volume

Surface Loop(190) = {116, 152, 134, 146, 144, 189, 181, 179, 177, 183, 185};

Volume(191) = {190}; // Top volume

Surface Loop(192) = {189, 165, 169, 171, 142, 122, 140, 124, 167, 175, 150, 118, 120, 173, 132, 126, 128};

Volume(193) = {192}; // Kapton volume

Surface Loop(194) = {165, 159, 148, 114, 130, 136, 138, 157, 155, 163, 161};

Volume(195) = {194}; // Bottom volume


//
//
//
// PHYSICAL VOLUMES AND BOUNDARIES
//
//
//

Physical Volume("Gas") = {187};
Physical Volume("Top") = {191};
Physical Volume("Kapton") = {193};
Physical Volume("Bottom") = {195};

Physical Surface("Cathode") = {112};
Physical Surface("Top boundary") = {116, 181, 134, 185, 152, 183, 177, 189, 146, 179, 144};
Physical Surface("Bottom boundary") = {114, 165, 163, 161, 130, 159, 148, 157, 155, 136, 138};
Physical Surface("Anode") = {110};

