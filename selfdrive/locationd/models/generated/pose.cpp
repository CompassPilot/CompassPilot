#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2988555708200788841) {
   out_2988555708200788841[0] = delta_x[0] + nom_x[0];
   out_2988555708200788841[1] = delta_x[1] + nom_x[1];
   out_2988555708200788841[2] = delta_x[2] + nom_x[2];
   out_2988555708200788841[3] = delta_x[3] + nom_x[3];
   out_2988555708200788841[4] = delta_x[4] + nom_x[4];
   out_2988555708200788841[5] = delta_x[5] + nom_x[5];
   out_2988555708200788841[6] = delta_x[6] + nom_x[6];
   out_2988555708200788841[7] = delta_x[7] + nom_x[7];
   out_2988555708200788841[8] = delta_x[8] + nom_x[8];
   out_2988555708200788841[9] = delta_x[9] + nom_x[9];
   out_2988555708200788841[10] = delta_x[10] + nom_x[10];
   out_2988555708200788841[11] = delta_x[11] + nom_x[11];
   out_2988555708200788841[12] = delta_x[12] + nom_x[12];
   out_2988555708200788841[13] = delta_x[13] + nom_x[13];
   out_2988555708200788841[14] = delta_x[14] + nom_x[14];
   out_2988555708200788841[15] = delta_x[15] + nom_x[15];
   out_2988555708200788841[16] = delta_x[16] + nom_x[16];
   out_2988555708200788841[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_2701064156642240678) {
   out_2701064156642240678[0] = -nom_x[0] + true_x[0];
   out_2701064156642240678[1] = -nom_x[1] + true_x[1];
   out_2701064156642240678[2] = -nom_x[2] + true_x[2];
   out_2701064156642240678[3] = -nom_x[3] + true_x[3];
   out_2701064156642240678[4] = -nom_x[4] + true_x[4];
   out_2701064156642240678[5] = -nom_x[5] + true_x[5];
   out_2701064156642240678[6] = -nom_x[6] + true_x[6];
   out_2701064156642240678[7] = -nom_x[7] + true_x[7];
   out_2701064156642240678[8] = -nom_x[8] + true_x[8];
   out_2701064156642240678[9] = -nom_x[9] + true_x[9];
   out_2701064156642240678[10] = -nom_x[10] + true_x[10];
   out_2701064156642240678[11] = -nom_x[11] + true_x[11];
   out_2701064156642240678[12] = -nom_x[12] + true_x[12];
   out_2701064156642240678[13] = -nom_x[13] + true_x[13];
   out_2701064156642240678[14] = -nom_x[14] + true_x[14];
   out_2701064156642240678[15] = -nom_x[15] + true_x[15];
   out_2701064156642240678[16] = -nom_x[16] + true_x[16];
   out_2701064156642240678[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5968360833876018355) {
   out_5968360833876018355[0] = 1.0;
   out_5968360833876018355[1] = 0.0;
   out_5968360833876018355[2] = 0.0;
   out_5968360833876018355[3] = 0.0;
   out_5968360833876018355[4] = 0.0;
   out_5968360833876018355[5] = 0.0;
   out_5968360833876018355[6] = 0.0;
   out_5968360833876018355[7] = 0.0;
   out_5968360833876018355[8] = 0.0;
   out_5968360833876018355[9] = 0.0;
   out_5968360833876018355[10] = 0.0;
   out_5968360833876018355[11] = 0.0;
   out_5968360833876018355[12] = 0.0;
   out_5968360833876018355[13] = 0.0;
   out_5968360833876018355[14] = 0.0;
   out_5968360833876018355[15] = 0.0;
   out_5968360833876018355[16] = 0.0;
   out_5968360833876018355[17] = 0.0;
   out_5968360833876018355[18] = 0.0;
   out_5968360833876018355[19] = 1.0;
   out_5968360833876018355[20] = 0.0;
   out_5968360833876018355[21] = 0.0;
   out_5968360833876018355[22] = 0.0;
   out_5968360833876018355[23] = 0.0;
   out_5968360833876018355[24] = 0.0;
   out_5968360833876018355[25] = 0.0;
   out_5968360833876018355[26] = 0.0;
   out_5968360833876018355[27] = 0.0;
   out_5968360833876018355[28] = 0.0;
   out_5968360833876018355[29] = 0.0;
   out_5968360833876018355[30] = 0.0;
   out_5968360833876018355[31] = 0.0;
   out_5968360833876018355[32] = 0.0;
   out_5968360833876018355[33] = 0.0;
   out_5968360833876018355[34] = 0.0;
   out_5968360833876018355[35] = 0.0;
   out_5968360833876018355[36] = 0.0;
   out_5968360833876018355[37] = 0.0;
   out_5968360833876018355[38] = 1.0;
   out_5968360833876018355[39] = 0.0;
   out_5968360833876018355[40] = 0.0;
   out_5968360833876018355[41] = 0.0;
   out_5968360833876018355[42] = 0.0;
   out_5968360833876018355[43] = 0.0;
   out_5968360833876018355[44] = 0.0;
   out_5968360833876018355[45] = 0.0;
   out_5968360833876018355[46] = 0.0;
   out_5968360833876018355[47] = 0.0;
   out_5968360833876018355[48] = 0.0;
   out_5968360833876018355[49] = 0.0;
   out_5968360833876018355[50] = 0.0;
   out_5968360833876018355[51] = 0.0;
   out_5968360833876018355[52] = 0.0;
   out_5968360833876018355[53] = 0.0;
   out_5968360833876018355[54] = 0.0;
   out_5968360833876018355[55] = 0.0;
   out_5968360833876018355[56] = 0.0;
   out_5968360833876018355[57] = 1.0;
   out_5968360833876018355[58] = 0.0;
   out_5968360833876018355[59] = 0.0;
   out_5968360833876018355[60] = 0.0;
   out_5968360833876018355[61] = 0.0;
   out_5968360833876018355[62] = 0.0;
   out_5968360833876018355[63] = 0.0;
   out_5968360833876018355[64] = 0.0;
   out_5968360833876018355[65] = 0.0;
   out_5968360833876018355[66] = 0.0;
   out_5968360833876018355[67] = 0.0;
   out_5968360833876018355[68] = 0.0;
   out_5968360833876018355[69] = 0.0;
   out_5968360833876018355[70] = 0.0;
   out_5968360833876018355[71] = 0.0;
   out_5968360833876018355[72] = 0.0;
   out_5968360833876018355[73] = 0.0;
   out_5968360833876018355[74] = 0.0;
   out_5968360833876018355[75] = 0.0;
   out_5968360833876018355[76] = 1.0;
   out_5968360833876018355[77] = 0.0;
   out_5968360833876018355[78] = 0.0;
   out_5968360833876018355[79] = 0.0;
   out_5968360833876018355[80] = 0.0;
   out_5968360833876018355[81] = 0.0;
   out_5968360833876018355[82] = 0.0;
   out_5968360833876018355[83] = 0.0;
   out_5968360833876018355[84] = 0.0;
   out_5968360833876018355[85] = 0.0;
   out_5968360833876018355[86] = 0.0;
   out_5968360833876018355[87] = 0.0;
   out_5968360833876018355[88] = 0.0;
   out_5968360833876018355[89] = 0.0;
   out_5968360833876018355[90] = 0.0;
   out_5968360833876018355[91] = 0.0;
   out_5968360833876018355[92] = 0.0;
   out_5968360833876018355[93] = 0.0;
   out_5968360833876018355[94] = 0.0;
   out_5968360833876018355[95] = 1.0;
   out_5968360833876018355[96] = 0.0;
   out_5968360833876018355[97] = 0.0;
   out_5968360833876018355[98] = 0.0;
   out_5968360833876018355[99] = 0.0;
   out_5968360833876018355[100] = 0.0;
   out_5968360833876018355[101] = 0.0;
   out_5968360833876018355[102] = 0.0;
   out_5968360833876018355[103] = 0.0;
   out_5968360833876018355[104] = 0.0;
   out_5968360833876018355[105] = 0.0;
   out_5968360833876018355[106] = 0.0;
   out_5968360833876018355[107] = 0.0;
   out_5968360833876018355[108] = 0.0;
   out_5968360833876018355[109] = 0.0;
   out_5968360833876018355[110] = 0.0;
   out_5968360833876018355[111] = 0.0;
   out_5968360833876018355[112] = 0.0;
   out_5968360833876018355[113] = 0.0;
   out_5968360833876018355[114] = 1.0;
   out_5968360833876018355[115] = 0.0;
   out_5968360833876018355[116] = 0.0;
   out_5968360833876018355[117] = 0.0;
   out_5968360833876018355[118] = 0.0;
   out_5968360833876018355[119] = 0.0;
   out_5968360833876018355[120] = 0.0;
   out_5968360833876018355[121] = 0.0;
   out_5968360833876018355[122] = 0.0;
   out_5968360833876018355[123] = 0.0;
   out_5968360833876018355[124] = 0.0;
   out_5968360833876018355[125] = 0.0;
   out_5968360833876018355[126] = 0.0;
   out_5968360833876018355[127] = 0.0;
   out_5968360833876018355[128] = 0.0;
   out_5968360833876018355[129] = 0.0;
   out_5968360833876018355[130] = 0.0;
   out_5968360833876018355[131] = 0.0;
   out_5968360833876018355[132] = 0.0;
   out_5968360833876018355[133] = 1.0;
   out_5968360833876018355[134] = 0.0;
   out_5968360833876018355[135] = 0.0;
   out_5968360833876018355[136] = 0.0;
   out_5968360833876018355[137] = 0.0;
   out_5968360833876018355[138] = 0.0;
   out_5968360833876018355[139] = 0.0;
   out_5968360833876018355[140] = 0.0;
   out_5968360833876018355[141] = 0.0;
   out_5968360833876018355[142] = 0.0;
   out_5968360833876018355[143] = 0.0;
   out_5968360833876018355[144] = 0.0;
   out_5968360833876018355[145] = 0.0;
   out_5968360833876018355[146] = 0.0;
   out_5968360833876018355[147] = 0.0;
   out_5968360833876018355[148] = 0.0;
   out_5968360833876018355[149] = 0.0;
   out_5968360833876018355[150] = 0.0;
   out_5968360833876018355[151] = 0.0;
   out_5968360833876018355[152] = 1.0;
   out_5968360833876018355[153] = 0.0;
   out_5968360833876018355[154] = 0.0;
   out_5968360833876018355[155] = 0.0;
   out_5968360833876018355[156] = 0.0;
   out_5968360833876018355[157] = 0.0;
   out_5968360833876018355[158] = 0.0;
   out_5968360833876018355[159] = 0.0;
   out_5968360833876018355[160] = 0.0;
   out_5968360833876018355[161] = 0.0;
   out_5968360833876018355[162] = 0.0;
   out_5968360833876018355[163] = 0.0;
   out_5968360833876018355[164] = 0.0;
   out_5968360833876018355[165] = 0.0;
   out_5968360833876018355[166] = 0.0;
   out_5968360833876018355[167] = 0.0;
   out_5968360833876018355[168] = 0.0;
   out_5968360833876018355[169] = 0.0;
   out_5968360833876018355[170] = 0.0;
   out_5968360833876018355[171] = 1.0;
   out_5968360833876018355[172] = 0.0;
   out_5968360833876018355[173] = 0.0;
   out_5968360833876018355[174] = 0.0;
   out_5968360833876018355[175] = 0.0;
   out_5968360833876018355[176] = 0.0;
   out_5968360833876018355[177] = 0.0;
   out_5968360833876018355[178] = 0.0;
   out_5968360833876018355[179] = 0.0;
   out_5968360833876018355[180] = 0.0;
   out_5968360833876018355[181] = 0.0;
   out_5968360833876018355[182] = 0.0;
   out_5968360833876018355[183] = 0.0;
   out_5968360833876018355[184] = 0.0;
   out_5968360833876018355[185] = 0.0;
   out_5968360833876018355[186] = 0.0;
   out_5968360833876018355[187] = 0.0;
   out_5968360833876018355[188] = 0.0;
   out_5968360833876018355[189] = 0.0;
   out_5968360833876018355[190] = 1.0;
   out_5968360833876018355[191] = 0.0;
   out_5968360833876018355[192] = 0.0;
   out_5968360833876018355[193] = 0.0;
   out_5968360833876018355[194] = 0.0;
   out_5968360833876018355[195] = 0.0;
   out_5968360833876018355[196] = 0.0;
   out_5968360833876018355[197] = 0.0;
   out_5968360833876018355[198] = 0.0;
   out_5968360833876018355[199] = 0.0;
   out_5968360833876018355[200] = 0.0;
   out_5968360833876018355[201] = 0.0;
   out_5968360833876018355[202] = 0.0;
   out_5968360833876018355[203] = 0.0;
   out_5968360833876018355[204] = 0.0;
   out_5968360833876018355[205] = 0.0;
   out_5968360833876018355[206] = 0.0;
   out_5968360833876018355[207] = 0.0;
   out_5968360833876018355[208] = 0.0;
   out_5968360833876018355[209] = 1.0;
   out_5968360833876018355[210] = 0.0;
   out_5968360833876018355[211] = 0.0;
   out_5968360833876018355[212] = 0.0;
   out_5968360833876018355[213] = 0.0;
   out_5968360833876018355[214] = 0.0;
   out_5968360833876018355[215] = 0.0;
   out_5968360833876018355[216] = 0.0;
   out_5968360833876018355[217] = 0.0;
   out_5968360833876018355[218] = 0.0;
   out_5968360833876018355[219] = 0.0;
   out_5968360833876018355[220] = 0.0;
   out_5968360833876018355[221] = 0.0;
   out_5968360833876018355[222] = 0.0;
   out_5968360833876018355[223] = 0.0;
   out_5968360833876018355[224] = 0.0;
   out_5968360833876018355[225] = 0.0;
   out_5968360833876018355[226] = 0.0;
   out_5968360833876018355[227] = 0.0;
   out_5968360833876018355[228] = 1.0;
   out_5968360833876018355[229] = 0.0;
   out_5968360833876018355[230] = 0.0;
   out_5968360833876018355[231] = 0.0;
   out_5968360833876018355[232] = 0.0;
   out_5968360833876018355[233] = 0.0;
   out_5968360833876018355[234] = 0.0;
   out_5968360833876018355[235] = 0.0;
   out_5968360833876018355[236] = 0.0;
   out_5968360833876018355[237] = 0.0;
   out_5968360833876018355[238] = 0.0;
   out_5968360833876018355[239] = 0.0;
   out_5968360833876018355[240] = 0.0;
   out_5968360833876018355[241] = 0.0;
   out_5968360833876018355[242] = 0.0;
   out_5968360833876018355[243] = 0.0;
   out_5968360833876018355[244] = 0.0;
   out_5968360833876018355[245] = 0.0;
   out_5968360833876018355[246] = 0.0;
   out_5968360833876018355[247] = 1.0;
   out_5968360833876018355[248] = 0.0;
   out_5968360833876018355[249] = 0.0;
   out_5968360833876018355[250] = 0.0;
   out_5968360833876018355[251] = 0.0;
   out_5968360833876018355[252] = 0.0;
   out_5968360833876018355[253] = 0.0;
   out_5968360833876018355[254] = 0.0;
   out_5968360833876018355[255] = 0.0;
   out_5968360833876018355[256] = 0.0;
   out_5968360833876018355[257] = 0.0;
   out_5968360833876018355[258] = 0.0;
   out_5968360833876018355[259] = 0.0;
   out_5968360833876018355[260] = 0.0;
   out_5968360833876018355[261] = 0.0;
   out_5968360833876018355[262] = 0.0;
   out_5968360833876018355[263] = 0.0;
   out_5968360833876018355[264] = 0.0;
   out_5968360833876018355[265] = 0.0;
   out_5968360833876018355[266] = 1.0;
   out_5968360833876018355[267] = 0.0;
   out_5968360833876018355[268] = 0.0;
   out_5968360833876018355[269] = 0.0;
   out_5968360833876018355[270] = 0.0;
   out_5968360833876018355[271] = 0.0;
   out_5968360833876018355[272] = 0.0;
   out_5968360833876018355[273] = 0.0;
   out_5968360833876018355[274] = 0.0;
   out_5968360833876018355[275] = 0.0;
   out_5968360833876018355[276] = 0.0;
   out_5968360833876018355[277] = 0.0;
   out_5968360833876018355[278] = 0.0;
   out_5968360833876018355[279] = 0.0;
   out_5968360833876018355[280] = 0.0;
   out_5968360833876018355[281] = 0.0;
   out_5968360833876018355[282] = 0.0;
   out_5968360833876018355[283] = 0.0;
   out_5968360833876018355[284] = 0.0;
   out_5968360833876018355[285] = 1.0;
   out_5968360833876018355[286] = 0.0;
   out_5968360833876018355[287] = 0.0;
   out_5968360833876018355[288] = 0.0;
   out_5968360833876018355[289] = 0.0;
   out_5968360833876018355[290] = 0.0;
   out_5968360833876018355[291] = 0.0;
   out_5968360833876018355[292] = 0.0;
   out_5968360833876018355[293] = 0.0;
   out_5968360833876018355[294] = 0.0;
   out_5968360833876018355[295] = 0.0;
   out_5968360833876018355[296] = 0.0;
   out_5968360833876018355[297] = 0.0;
   out_5968360833876018355[298] = 0.0;
   out_5968360833876018355[299] = 0.0;
   out_5968360833876018355[300] = 0.0;
   out_5968360833876018355[301] = 0.0;
   out_5968360833876018355[302] = 0.0;
   out_5968360833876018355[303] = 0.0;
   out_5968360833876018355[304] = 1.0;
   out_5968360833876018355[305] = 0.0;
   out_5968360833876018355[306] = 0.0;
   out_5968360833876018355[307] = 0.0;
   out_5968360833876018355[308] = 0.0;
   out_5968360833876018355[309] = 0.0;
   out_5968360833876018355[310] = 0.0;
   out_5968360833876018355[311] = 0.0;
   out_5968360833876018355[312] = 0.0;
   out_5968360833876018355[313] = 0.0;
   out_5968360833876018355[314] = 0.0;
   out_5968360833876018355[315] = 0.0;
   out_5968360833876018355[316] = 0.0;
   out_5968360833876018355[317] = 0.0;
   out_5968360833876018355[318] = 0.0;
   out_5968360833876018355[319] = 0.0;
   out_5968360833876018355[320] = 0.0;
   out_5968360833876018355[321] = 0.0;
   out_5968360833876018355[322] = 0.0;
   out_5968360833876018355[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_1848968576771995423) {
   out_1848968576771995423[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_1848968576771995423[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_1848968576771995423[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_1848968576771995423[3] = dt*state[12] + state[3];
   out_1848968576771995423[4] = dt*state[13] + state[4];
   out_1848968576771995423[5] = dt*state[14] + state[5];
   out_1848968576771995423[6] = state[6];
   out_1848968576771995423[7] = state[7];
   out_1848968576771995423[8] = state[8];
   out_1848968576771995423[9] = state[9];
   out_1848968576771995423[10] = state[10];
   out_1848968576771995423[11] = state[11];
   out_1848968576771995423[12] = state[12];
   out_1848968576771995423[13] = state[13];
   out_1848968576771995423[14] = state[14];
   out_1848968576771995423[15] = state[15];
   out_1848968576771995423[16] = state[16];
   out_1848968576771995423[17] = state[17];
}
void F_fun(double *state, double dt, double *out_3155877724521984150) {
   out_3155877724521984150[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3155877724521984150[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3155877724521984150[2] = 0;
   out_3155877724521984150[3] = 0;
   out_3155877724521984150[4] = 0;
   out_3155877724521984150[5] = 0;
   out_3155877724521984150[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3155877724521984150[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3155877724521984150[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_3155877724521984150[9] = 0;
   out_3155877724521984150[10] = 0;
   out_3155877724521984150[11] = 0;
   out_3155877724521984150[12] = 0;
   out_3155877724521984150[13] = 0;
   out_3155877724521984150[14] = 0;
   out_3155877724521984150[15] = 0;
   out_3155877724521984150[16] = 0;
   out_3155877724521984150[17] = 0;
   out_3155877724521984150[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3155877724521984150[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3155877724521984150[20] = 0;
   out_3155877724521984150[21] = 0;
   out_3155877724521984150[22] = 0;
   out_3155877724521984150[23] = 0;
   out_3155877724521984150[24] = 0;
   out_3155877724521984150[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3155877724521984150[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_3155877724521984150[27] = 0;
   out_3155877724521984150[28] = 0;
   out_3155877724521984150[29] = 0;
   out_3155877724521984150[30] = 0;
   out_3155877724521984150[31] = 0;
   out_3155877724521984150[32] = 0;
   out_3155877724521984150[33] = 0;
   out_3155877724521984150[34] = 0;
   out_3155877724521984150[35] = 0;
   out_3155877724521984150[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3155877724521984150[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3155877724521984150[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3155877724521984150[39] = 0;
   out_3155877724521984150[40] = 0;
   out_3155877724521984150[41] = 0;
   out_3155877724521984150[42] = 0;
   out_3155877724521984150[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3155877724521984150[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_3155877724521984150[45] = 0;
   out_3155877724521984150[46] = 0;
   out_3155877724521984150[47] = 0;
   out_3155877724521984150[48] = 0;
   out_3155877724521984150[49] = 0;
   out_3155877724521984150[50] = 0;
   out_3155877724521984150[51] = 0;
   out_3155877724521984150[52] = 0;
   out_3155877724521984150[53] = 0;
   out_3155877724521984150[54] = 0;
   out_3155877724521984150[55] = 0;
   out_3155877724521984150[56] = 0;
   out_3155877724521984150[57] = 1;
   out_3155877724521984150[58] = 0;
   out_3155877724521984150[59] = 0;
   out_3155877724521984150[60] = 0;
   out_3155877724521984150[61] = 0;
   out_3155877724521984150[62] = 0;
   out_3155877724521984150[63] = 0;
   out_3155877724521984150[64] = 0;
   out_3155877724521984150[65] = 0;
   out_3155877724521984150[66] = dt;
   out_3155877724521984150[67] = 0;
   out_3155877724521984150[68] = 0;
   out_3155877724521984150[69] = 0;
   out_3155877724521984150[70] = 0;
   out_3155877724521984150[71] = 0;
   out_3155877724521984150[72] = 0;
   out_3155877724521984150[73] = 0;
   out_3155877724521984150[74] = 0;
   out_3155877724521984150[75] = 0;
   out_3155877724521984150[76] = 1;
   out_3155877724521984150[77] = 0;
   out_3155877724521984150[78] = 0;
   out_3155877724521984150[79] = 0;
   out_3155877724521984150[80] = 0;
   out_3155877724521984150[81] = 0;
   out_3155877724521984150[82] = 0;
   out_3155877724521984150[83] = 0;
   out_3155877724521984150[84] = 0;
   out_3155877724521984150[85] = dt;
   out_3155877724521984150[86] = 0;
   out_3155877724521984150[87] = 0;
   out_3155877724521984150[88] = 0;
   out_3155877724521984150[89] = 0;
   out_3155877724521984150[90] = 0;
   out_3155877724521984150[91] = 0;
   out_3155877724521984150[92] = 0;
   out_3155877724521984150[93] = 0;
   out_3155877724521984150[94] = 0;
   out_3155877724521984150[95] = 1;
   out_3155877724521984150[96] = 0;
   out_3155877724521984150[97] = 0;
   out_3155877724521984150[98] = 0;
   out_3155877724521984150[99] = 0;
   out_3155877724521984150[100] = 0;
   out_3155877724521984150[101] = 0;
   out_3155877724521984150[102] = 0;
   out_3155877724521984150[103] = 0;
   out_3155877724521984150[104] = dt;
   out_3155877724521984150[105] = 0;
   out_3155877724521984150[106] = 0;
   out_3155877724521984150[107] = 0;
   out_3155877724521984150[108] = 0;
   out_3155877724521984150[109] = 0;
   out_3155877724521984150[110] = 0;
   out_3155877724521984150[111] = 0;
   out_3155877724521984150[112] = 0;
   out_3155877724521984150[113] = 0;
   out_3155877724521984150[114] = 1;
   out_3155877724521984150[115] = 0;
   out_3155877724521984150[116] = 0;
   out_3155877724521984150[117] = 0;
   out_3155877724521984150[118] = 0;
   out_3155877724521984150[119] = 0;
   out_3155877724521984150[120] = 0;
   out_3155877724521984150[121] = 0;
   out_3155877724521984150[122] = 0;
   out_3155877724521984150[123] = 0;
   out_3155877724521984150[124] = 0;
   out_3155877724521984150[125] = 0;
   out_3155877724521984150[126] = 0;
   out_3155877724521984150[127] = 0;
   out_3155877724521984150[128] = 0;
   out_3155877724521984150[129] = 0;
   out_3155877724521984150[130] = 0;
   out_3155877724521984150[131] = 0;
   out_3155877724521984150[132] = 0;
   out_3155877724521984150[133] = 1;
   out_3155877724521984150[134] = 0;
   out_3155877724521984150[135] = 0;
   out_3155877724521984150[136] = 0;
   out_3155877724521984150[137] = 0;
   out_3155877724521984150[138] = 0;
   out_3155877724521984150[139] = 0;
   out_3155877724521984150[140] = 0;
   out_3155877724521984150[141] = 0;
   out_3155877724521984150[142] = 0;
   out_3155877724521984150[143] = 0;
   out_3155877724521984150[144] = 0;
   out_3155877724521984150[145] = 0;
   out_3155877724521984150[146] = 0;
   out_3155877724521984150[147] = 0;
   out_3155877724521984150[148] = 0;
   out_3155877724521984150[149] = 0;
   out_3155877724521984150[150] = 0;
   out_3155877724521984150[151] = 0;
   out_3155877724521984150[152] = 1;
   out_3155877724521984150[153] = 0;
   out_3155877724521984150[154] = 0;
   out_3155877724521984150[155] = 0;
   out_3155877724521984150[156] = 0;
   out_3155877724521984150[157] = 0;
   out_3155877724521984150[158] = 0;
   out_3155877724521984150[159] = 0;
   out_3155877724521984150[160] = 0;
   out_3155877724521984150[161] = 0;
   out_3155877724521984150[162] = 0;
   out_3155877724521984150[163] = 0;
   out_3155877724521984150[164] = 0;
   out_3155877724521984150[165] = 0;
   out_3155877724521984150[166] = 0;
   out_3155877724521984150[167] = 0;
   out_3155877724521984150[168] = 0;
   out_3155877724521984150[169] = 0;
   out_3155877724521984150[170] = 0;
   out_3155877724521984150[171] = 1;
   out_3155877724521984150[172] = 0;
   out_3155877724521984150[173] = 0;
   out_3155877724521984150[174] = 0;
   out_3155877724521984150[175] = 0;
   out_3155877724521984150[176] = 0;
   out_3155877724521984150[177] = 0;
   out_3155877724521984150[178] = 0;
   out_3155877724521984150[179] = 0;
   out_3155877724521984150[180] = 0;
   out_3155877724521984150[181] = 0;
   out_3155877724521984150[182] = 0;
   out_3155877724521984150[183] = 0;
   out_3155877724521984150[184] = 0;
   out_3155877724521984150[185] = 0;
   out_3155877724521984150[186] = 0;
   out_3155877724521984150[187] = 0;
   out_3155877724521984150[188] = 0;
   out_3155877724521984150[189] = 0;
   out_3155877724521984150[190] = 1;
   out_3155877724521984150[191] = 0;
   out_3155877724521984150[192] = 0;
   out_3155877724521984150[193] = 0;
   out_3155877724521984150[194] = 0;
   out_3155877724521984150[195] = 0;
   out_3155877724521984150[196] = 0;
   out_3155877724521984150[197] = 0;
   out_3155877724521984150[198] = 0;
   out_3155877724521984150[199] = 0;
   out_3155877724521984150[200] = 0;
   out_3155877724521984150[201] = 0;
   out_3155877724521984150[202] = 0;
   out_3155877724521984150[203] = 0;
   out_3155877724521984150[204] = 0;
   out_3155877724521984150[205] = 0;
   out_3155877724521984150[206] = 0;
   out_3155877724521984150[207] = 0;
   out_3155877724521984150[208] = 0;
   out_3155877724521984150[209] = 1;
   out_3155877724521984150[210] = 0;
   out_3155877724521984150[211] = 0;
   out_3155877724521984150[212] = 0;
   out_3155877724521984150[213] = 0;
   out_3155877724521984150[214] = 0;
   out_3155877724521984150[215] = 0;
   out_3155877724521984150[216] = 0;
   out_3155877724521984150[217] = 0;
   out_3155877724521984150[218] = 0;
   out_3155877724521984150[219] = 0;
   out_3155877724521984150[220] = 0;
   out_3155877724521984150[221] = 0;
   out_3155877724521984150[222] = 0;
   out_3155877724521984150[223] = 0;
   out_3155877724521984150[224] = 0;
   out_3155877724521984150[225] = 0;
   out_3155877724521984150[226] = 0;
   out_3155877724521984150[227] = 0;
   out_3155877724521984150[228] = 1;
   out_3155877724521984150[229] = 0;
   out_3155877724521984150[230] = 0;
   out_3155877724521984150[231] = 0;
   out_3155877724521984150[232] = 0;
   out_3155877724521984150[233] = 0;
   out_3155877724521984150[234] = 0;
   out_3155877724521984150[235] = 0;
   out_3155877724521984150[236] = 0;
   out_3155877724521984150[237] = 0;
   out_3155877724521984150[238] = 0;
   out_3155877724521984150[239] = 0;
   out_3155877724521984150[240] = 0;
   out_3155877724521984150[241] = 0;
   out_3155877724521984150[242] = 0;
   out_3155877724521984150[243] = 0;
   out_3155877724521984150[244] = 0;
   out_3155877724521984150[245] = 0;
   out_3155877724521984150[246] = 0;
   out_3155877724521984150[247] = 1;
   out_3155877724521984150[248] = 0;
   out_3155877724521984150[249] = 0;
   out_3155877724521984150[250] = 0;
   out_3155877724521984150[251] = 0;
   out_3155877724521984150[252] = 0;
   out_3155877724521984150[253] = 0;
   out_3155877724521984150[254] = 0;
   out_3155877724521984150[255] = 0;
   out_3155877724521984150[256] = 0;
   out_3155877724521984150[257] = 0;
   out_3155877724521984150[258] = 0;
   out_3155877724521984150[259] = 0;
   out_3155877724521984150[260] = 0;
   out_3155877724521984150[261] = 0;
   out_3155877724521984150[262] = 0;
   out_3155877724521984150[263] = 0;
   out_3155877724521984150[264] = 0;
   out_3155877724521984150[265] = 0;
   out_3155877724521984150[266] = 1;
   out_3155877724521984150[267] = 0;
   out_3155877724521984150[268] = 0;
   out_3155877724521984150[269] = 0;
   out_3155877724521984150[270] = 0;
   out_3155877724521984150[271] = 0;
   out_3155877724521984150[272] = 0;
   out_3155877724521984150[273] = 0;
   out_3155877724521984150[274] = 0;
   out_3155877724521984150[275] = 0;
   out_3155877724521984150[276] = 0;
   out_3155877724521984150[277] = 0;
   out_3155877724521984150[278] = 0;
   out_3155877724521984150[279] = 0;
   out_3155877724521984150[280] = 0;
   out_3155877724521984150[281] = 0;
   out_3155877724521984150[282] = 0;
   out_3155877724521984150[283] = 0;
   out_3155877724521984150[284] = 0;
   out_3155877724521984150[285] = 1;
   out_3155877724521984150[286] = 0;
   out_3155877724521984150[287] = 0;
   out_3155877724521984150[288] = 0;
   out_3155877724521984150[289] = 0;
   out_3155877724521984150[290] = 0;
   out_3155877724521984150[291] = 0;
   out_3155877724521984150[292] = 0;
   out_3155877724521984150[293] = 0;
   out_3155877724521984150[294] = 0;
   out_3155877724521984150[295] = 0;
   out_3155877724521984150[296] = 0;
   out_3155877724521984150[297] = 0;
   out_3155877724521984150[298] = 0;
   out_3155877724521984150[299] = 0;
   out_3155877724521984150[300] = 0;
   out_3155877724521984150[301] = 0;
   out_3155877724521984150[302] = 0;
   out_3155877724521984150[303] = 0;
   out_3155877724521984150[304] = 1;
   out_3155877724521984150[305] = 0;
   out_3155877724521984150[306] = 0;
   out_3155877724521984150[307] = 0;
   out_3155877724521984150[308] = 0;
   out_3155877724521984150[309] = 0;
   out_3155877724521984150[310] = 0;
   out_3155877724521984150[311] = 0;
   out_3155877724521984150[312] = 0;
   out_3155877724521984150[313] = 0;
   out_3155877724521984150[314] = 0;
   out_3155877724521984150[315] = 0;
   out_3155877724521984150[316] = 0;
   out_3155877724521984150[317] = 0;
   out_3155877724521984150[318] = 0;
   out_3155877724521984150[319] = 0;
   out_3155877724521984150[320] = 0;
   out_3155877724521984150[321] = 0;
   out_3155877724521984150[322] = 0;
   out_3155877724521984150[323] = 1;
}
void h_4(double *state, double *unused, double *out_2502869184113054181) {
   out_2502869184113054181[0] = state[6] + state[9];
   out_2502869184113054181[1] = state[7] + state[10];
   out_2502869184113054181[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_5214199831821305748) {
   out_5214199831821305748[0] = 0;
   out_5214199831821305748[1] = 0;
   out_5214199831821305748[2] = 0;
   out_5214199831821305748[3] = 0;
   out_5214199831821305748[4] = 0;
   out_5214199831821305748[5] = 0;
   out_5214199831821305748[6] = 1;
   out_5214199831821305748[7] = 0;
   out_5214199831821305748[8] = 0;
   out_5214199831821305748[9] = 1;
   out_5214199831821305748[10] = 0;
   out_5214199831821305748[11] = 0;
   out_5214199831821305748[12] = 0;
   out_5214199831821305748[13] = 0;
   out_5214199831821305748[14] = 0;
   out_5214199831821305748[15] = 0;
   out_5214199831821305748[16] = 0;
   out_5214199831821305748[17] = 0;
   out_5214199831821305748[18] = 0;
   out_5214199831821305748[19] = 0;
   out_5214199831821305748[20] = 0;
   out_5214199831821305748[21] = 0;
   out_5214199831821305748[22] = 0;
   out_5214199831821305748[23] = 0;
   out_5214199831821305748[24] = 0;
   out_5214199831821305748[25] = 1;
   out_5214199831821305748[26] = 0;
   out_5214199831821305748[27] = 0;
   out_5214199831821305748[28] = 1;
   out_5214199831821305748[29] = 0;
   out_5214199831821305748[30] = 0;
   out_5214199831821305748[31] = 0;
   out_5214199831821305748[32] = 0;
   out_5214199831821305748[33] = 0;
   out_5214199831821305748[34] = 0;
   out_5214199831821305748[35] = 0;
   out_5214199831821305748[36] = 0;
   out_5214199831821305748[37] = 0;
   out_5214199831821305748[38] = 0;
   out_5214199831821305748[39] = 0;
   out_5214199831821305748[40] = 0;
   out_5214199831821305748[41] = 0;
   out_5214199831821305748[42] = 0;
   out_5214199831821305748[43] = 0;
   out_5214199831821305748[44] = 1;
   out_5214199831821305748[45] = 0;
   out_5214199831821305748[46] = 0;
   out_5214199831821305748[47] = 1;
   out_5214199831821305748[48] = 0;
   out_5214199831821305748[49] = 0;
   out_5214199831821305748[50] = 0;
   out_5214199831821305748[51] = 0;
   out_5214199831821305748[52] = 0;
   out_5214199831821305748[53] = 0;
}
void h_10(double *state, double *unused, double *out_3666588124569296206) {
   out_3666588124569296206[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3666588124569296206[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3666588124569296206[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_5786440187132908313) {
   out_5786440187132908313[0] = 0;
   out_5786440187132908313[1] = 9.8100000000000005*cos(state[1]);
   out_5786440187132908313[2] = 0;
   out_5786440187132908313[3] = 0;
   out_5786440187132908313[4] = -state[8];
   out_5786440187132908313[5] = state[7];
   out_5786440187132908313[6] = 0;
   out_5786440187132908313[7] = state[5];
   out_5786440187132908313[8] = -state[4];
   out_5786440187132908313[9] = 0;
   out_5786440187132908313[10] = 0;
   out_5786440187132908313[11] = 0;
   out_5786440187132908313[12] = 1;
   out_5786440187132908313[13] = 0;
   out_5786440187132908313[14] = 0;
   out_5786440187132908313[15] = 1;
   out_5786440187132908313[16] = 0;
   out_5786440187132908313[17] = 0;
   out_5786440187132908313[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_5786440187132908313[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_5786440187132908313[20] = 0;
   out_5786440187132908313[21] = state[8];
   out_5786440187132908313[22] = 0;
   out_5786440187132908313[23] = -state[6];
   out_5786440187132908313[24] = -state[5];
   out_5786440187132908313[25] = 0;
   out_5786440187132908313[26] = state[3];
   out_5786440187132908313[27] = 0;
   out_5786440187132908313[28] = 0;
   out_5786440187132908313[29] = 0;
   out_5786440187132908313[30] = 0;
   out_5786440187132908313[31] = 1;
   out_5786440187132908313[32] = 0;
   out_5786440187132908313[33] = 0;
   out_5786440187132908313[34] = 1;
   out_5786440187132908313[35] = 0;
   out_5786440187132908313[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_5786440187132908313[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_5786440187132908313[38] = 0;
   out_5786440187132908313[39] = -state[7];
   out_5786440187132908313[40] = state[6];
   out_5786440187132908313[41] = 0;
   out_5786440187132908313[42] = state[4];
   out_5786440187132908313[43] = -state[3];
   out_5786440187132908313[44] = 0;
   out_5786440187132908313[45] = 0;
   out_5786440187132908313[46] = 0;
   out_5786440187132908313[47] = 0;
   out_5786440187132908313[48] = 0;
   out_5786440187132908313[49] = 0;
   out_5786440187132908313[50] = 1;
   out_5786440187132908313[51] = 0;
   out_5786440187132908313[52] = 0;
   out_5786440187132908313[53] = 1;
}
void h_13(double *state, double *unused, double *out_3939295682978216666) {
   out_3939295682978216666[0] = state[3];
   out_3939295682978216666[1] = state[4];
   out_3939295682978216666[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2396431376495395181) {
   out_2396431376495395181[0] = 0;
   out_2396431376495395181[1] = 0;
   out_2396431376495395181[2] = 0;
   out_2396431376495395181[3] = 1;
   out_2396431376495395181[4] = 0;
   out_2396431376495395181[5] = 0;
   out_2396431376495395181[6] = 0;
   out_2396431376495395181[7] = 0;
   out_2396431376495395181[8] = 0;
   out_2396431376495395181[9] = 0;
   out_2396431376495395181[10] = 0;
   out_2396431376495395181[11] = 0;
   out_2396431376495395181[12] = 0;
   out_2396431376495395181[13] = 0;
   out_2396431376495395181[14] = 0;
   out_2396431376495395181[15] = 0;
   out_2396431376495395181[16] = 0;
   out_2396431376495395181[17] = 0;
   out_2396431376495395181[18] = 0;
   out_2396431376495395181[19] = 0;
   out_2396431376495395181[20] = 0;
   out_2396431376495395181[21] = 0;
   out_2396431376495395181[22] = 1;
   out_2396431376495395181[23] = 0;
   out_2396431376495395181[24] = 0;
   out_2396431376495395181[25] = 0;
   out_2396431376495395181[26] = 0;
   out_2396431376495395181[27] = 0;
   out_2396431376495395181[28] = 0;
   out_2396431376495395181[29] = 0;
   out_2396431376495395181[30] = 0;
   out_2396431376495395181[31] = 0;
   out_2396431376495395181[32] = 0;
   out_2396431376495395181[33] = 0;
   out_2396431376495395181[34] = 0;
   out_2396431376495395181[35] = 0;
   out_2396431376495395181[36] = 0;
   out_2396431376495395181[37] = 0;
   out_2396431376495395181[38] = 0;
   out_2396431376495395181[39] = 0;
   out_2396431376495395181[40] = 0;
   out_2396431376495395181[41] = 1;
   out_2396431376495395181[42] = 0;
   out_2396431376495395181[43] = 0;
   out_2396431376495395181[44] = 0;
   out_2396431376495395181[45] = 0;
   out_2396431376495395181[46] = 0;
   out_2396431376495395181[47] = 0;
   out_2396431376495395181[48] = 0;
   out_2396431376495395181[49] = 0;
   out_2396431376495395181[50] = 0;
   out_2396431376495395181[51] = 0;
   out_2396431376495395181[52] = 0;
   out_2396431376495395181[53] = 0;
}
void h_14(double *state, double *unused, double *out_6847784443772444789) {
   out_6847784443772444789[0] = state[6];
   out_6847784443772444789[1] = state[7];
   out_6847784443772444789[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8296988264116678044) {
   out_8296988264116678044[0] = 0;
   out_8296988264116678044[1] = 0;
   out_8296988264116678044[2] = 0;
   out_8296988264116678044[3] = 0;
   out_8296988264116678044[4] = 0;
   out_8296988264116678044[5] = 0;
   out_8296988264116678044[6] = 1;
   out_8296988264116678044[7] = 0;
   out_8296988264116678044[8] = 0;
   out_8296988264116678044[9] = 0;
   out_8296988264116678044[10] = 0;
   out_8296988264116678044[11] = 0;
   out_8296988264116678044[12] = 0;
   out_8296988264116678044[13] = 0;
   out_8296988264116678044[14] = 0;
   out_8296988264116678044[15] = 0;
   out_8296988264116678044[16] = 0;
   out_8296988264116678044[17] = 0;
   out_8296988264116678044[18] = 0;
   out_8296988264116678044[19] = 0;
   out_8296988264116678044[20] = 0;
   out_8296988264116678044[21] = 0;
   out_8296988264116678044[22] = 0;
   out_8296988264116678044[23] = 0;
   out_8296988264116678044[24] = 0;
   out_8296988264116678044[25] = 1;
   out_8296988264116678044[26] = 0;
   out_8296988264116678044[27] = 0;
   out_8296988264116678044[28] = 0;
   out_8296988264116678044[29] = 0;
   out_8296988264116678044[30] = 0;
   out_8296988264116678044[31] = 0;
   out_8296988264116678044[32] = 0;
   out_8296988264116678044[33] = 0;
   out_8296988264116678044[34] = 0;
   out_8296988264116678044[35] = 0;
   out_8296988264116678044[36] = 0;
   out_8296988264116678044[37] = 0;
   out_8296988264116678044[38] = 0;
   out_8296988264116678044[39] = 0;
   out_8296988264116678044[40] = 0;
   out_8296988264116678044[41] = 0;
   out_8296988264116678044[42] = 0;
   out_8296988264116678044[43] = 0;
   out_8296988264116678044[44] = 1;
   out_8296988264116678044[45] = 0;
   out_8296988264116678044[46] = 0;
   out_8296988264116678044[47] = 0;
   out_8296988264116678044[48] = 0;
   out_8296988264116678044[49] = 0;
   out_8296988264116678044[50] = 0;
   out_8296988264116678044[51] = 0;
   out_8296988264116678044[52] = 0;
   out_8296988264116678044[53] = 0;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_2988555708200788841) {
  err_fun(nom_x, delta_x, out_2988555708200788841);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2701064156642240678) {
  inv_err_fun(nom_x, true_x, out_2701064156642240678);
}
void pose_H_mod_fun(double *state, double *out_5968360833876018355) {
  H_mod_fun(state, out_5968360833876018355);
}
void pose_f_fun(double *state, double dt, double *out_1848968576771995423) {
  f_fun(state,  dt, out_1848968576771995423);
}
void pose_F_fun(double *state, double dt, double *out_3155877724521984150) {
  F_fun(state,  dt, out_3155877724521984150);
}
void pose_h_4(double *state, double *unused, double *out_2502869184113054181) {
  h_4(state, unused, out_2502869184113054181);
}
void pose_H_4(double *state, double *unused, double *out_5214199831821305748) {
  H_4(state, unused, out_5214199831821305748);
}
void pose_h_10(double *state, double *unused, double *out_3666588124569296206) {
  h_10(state, unused, out_3666588124569296206);
}
void pose_H_10(double *state, double *unused, double *out_5786440187132908313) {
  H_10(state, unused, out_5786440187132908313);
}
void pose_h_13(double *state, double *unused, double *out_3939295682978216666) {
  h_13(state, unused, out_3939295682978216666);
}
void pose_H_13(double *state, double *unused, double *out_2396431376495395181) {
  H_13(state, unused, out_2396431376495395181);
}
void pose_h_14(double *state, double *unused, double *out_6847784443772444789) {
  h_14(state, unused, out_6847784443772444789);
}
void pose_H_14(double *state, double *unused, double *out_8296988264116678044) {
  H_14(state, unused, out_8296988264116678044);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
