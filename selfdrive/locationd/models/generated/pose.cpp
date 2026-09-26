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
void err_fun(double *nom_x, double *delta_x, double *out_2547418662005312230) {
   out_2547418662005312230[0] = delta_x[0] + nom_x[0];
   out_2547418662005312230[1] = delta_x[1] + nom_x[1];
   out_2547418662005312230[2] = delta_x[2] + nom_x[2];
   out_2547418662005312230[3] = delta_x[3] + nom_x[3];
   out_2547418662005312230[4] = delta_x[4] + nom_x[4];
   out_2547418662005312230[5] = delta_x[5] + nom_x[5];
   out_2547418662005312230[6] = delta_x[6] + nom_x[6];
   out_2547418662005312230[7] = delta_x[7] + nom_x[7];
   out_2547418662005312230[8] = delta_x[8] + nom_x[8];
   out_2547418662005312230[9] = delta_x[9] + nom_x[9];
   out_2547418662005312230[10] = delta_x[10] + nom_x[10];
   out_2547418662005312230[11] = delta_x[11] + nom_x[11];
   out_2547418662005312230[12] = delta_x[12] + nom_x[12];
   out_2547418662005312230[13] = delta_x[13] + nom_x[13];
   out_2547418662005312230[14] = delta_x[14] + nom_x[14];
   out_2547418662005312230[15] = delta_x[15] + nom_x[15];
   out_2547418662005312230[16] = delta_x[16] + nom_x[16];
   out_2547418662005312230[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7399773008628044860) {
   out_7399773008628044860[0] = -nom_x[0] + true_x[0];
   out_7399773008628044860[1] = -nom_x[1] + true_x[1];
   out_7399773008628044860[2] = -nom_x[2] + true_x[2];
   out_7399773008628044860[3] = -nom_x[3] + true_x[3];
   out_7399773008628044860[4] = -nom_x[4] + true_x[4];
   out_7399773008628044860[5] = -nom_x[5] + true_x[5];
   out_7399773008628044860[6] = -nom_x[6] + true_x[6];
   out_7399773008628044860[7] = -nom_x[7] + true_x[7];
   out_7399773008628044860[8] = -nom_x[8] + true_x[8];
   out_7399773008628044860[9] = -nom_x[9] + true_x[9];
   out_7399773008628044860[10] = -nom_x[10] + true_x[10];
   out_7399773008628044860[11] = -nom_x[11] + true_x[11];
   out_7399773008628044860[12] = -nom_x[12] + true_x[12];
   out_7399773008628044860[13] = -nom_x[13] + true_x[13];
   out_7399773008628044860[14] = -nom_x[14] + true_x[14];
   out_7399773008628044860[15] = -nom_x[15] + true_x[15];
   out_7399773008628044860[16] = -nom_x[16] + true_x[16];
   out_7399773008628044860[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5714773270956696752) {
   out_5714773270956696752[0] = 1.0;
   out_5714773270956696752[1] = 0.0;
   out_5714773270956696752[2] = 0.0;
   out_5714773270956696752[3] = 0.0;
   out_5714773270956696752[4] = 0.0;
   out_5714773270956696752[5] = 0.0;
   out_5714773270956696752[6] = 0.0;
   out_5714773270956696752[7] = 0.0;
   out_5714773270956696752[8] = 0.0;
   out_5714773270956696752[9] = 0.0;
   out_5714773270956696752[10] = 0.0;
   out_5714773270956696752[11] = 0.0;
   out_5714773270956696752[12] = 0.0;
   out_5714773270956696752[13] = 0.0;
   out_5714773270956696752[14] = 0.0;
   out_5714773270956696752[15] = 0.0;
   out_5714773270956696752[16] = 0.0;
   out_5714773270956696752[17] = 0.0;
   out_5714773270956696752[18] = 0.0;
   out_5714773270956696752[19] = 1.0;
   out_5714773270956696752[20] = 0.0;
   out_5714773270956696752[21] = 0.0;
   out_5714773270956696752[22] = 0.0;
   out_5714773270956696752[23] = 0.0;
   out_5714773270956696752[24] = 0.0;
   out_5714773270956696752[25] = 0.0;
   out_5714773270956696752[26] = 0.0;
   out_5714773270956696752[27] = 0.0;
   out_5714773270956696752[28] = 0.0;
   out_5714773270956696752[29] = 0.0;
   out_5714773270956696752[30] = 0.0;
   out_5714773270956696752[31] = 0.0;
   out_5714773270956696752[32] = 0.0;
   out_5714773270956696752[33] = 0.0;
   out_5714773270956696752[34] = 0.0;
   out_5714773270956696752[35] = 0.0;
   out_5714773270956696752[36] = 0.0;
   out_5714773270956696752[37] = 0.0;
   out_5714773270956696752[38] = 1.0;
   out_5714773270956696752[39] = 0.0;
   out_5714773270956696752[40] = 0.0;
   out_5714773270956696752[41] = 0.0;
   out_5714773270956696752[42] = 0.0;
   out_5714773270956696752[43] = 0.0;
   out_5714773270956696752[44] = 0.0;
   out_5714773270956696752[45] = 0.0;
   out_5714773270956696752[46] = 0.0;
   out_5714773270956696752[47] = 0.0;
   out_5714773270956696752[48] = 0.0;
   out_5714773270956696752[49] = 0.0;
   out_5714773270956696752[50] = 0.0;
   out_5714773270956696752[51] = 0.0;
   out_5714773270956696752[52] = 0.0;
   out_5714773270956696752[53] = 0.0;
   out_5714773270956696752[54] = 0.0;
   out_5714773270956696752[55] = 0.0;
   out_5714773270956696752[56] = 0.0;
   out_5714773270956696752[57] = 1.0;
   out_5714773270956696752[58] = 0.0;
   out_5714773270956696752[59] = 0.0;
   out_5714773270956696752[60] = 0.0;
   out_5714773270956696752[61] = 0.0;
   out_5714773270956696752[62] = 0.0;
   out_5714773270956696752[63] = 0.0;
   out_5714773270956696752[64] = 0.0;
   out_5714773270956696752[65] = 0.0;
   out_5714773270956696752[66] = 0.0;
   out_5714773270956696752[67] = 0.0;
   out_5714773270956696752[68] = 0.0;
   out_5714773270956696752[69] = 0.0;
   out_5714773270956696752[70] = 0.0;
   out_5714773270956696752[71] = 0.0;
   out_5714773270956696752[72] = 0.0;
   out_5714773270956696752[73] = 0.0;
   out_5714773270956696752[74] = 0.0;
   out_5714773270956696752[75] = 0.0;
   out_5714773270956696752[76] = 1.0;
   out_5714773270956696752[77] = 0.0;
   out_5714773270956696752[78] = 0.0;
   out_5714773270956696752[79] = 0.0;
   out_5714773270956696752[80] = 0.0;
   out_5714773270956696752[81] = 0.0;
   out_5714773270956696752[82] = 0.0;
   out_5714773270956696752[83] = 0.0;
   out_5714773270956696752[84] = 0.0;
   out_5714773270956696752[85] = 0.0;
   out_5714773270956696752[86] = 0.0;
   out_5714773270956696752[87] = 0.0;
   out_5714773270956696752[88] = 0.0;
   out_5714773270956696752[89] = 0.0;
   out_5714773270956696752[90] = 0.0;
   out_5714773270956696752[91] = 0.0;
   out_5714773270956696752[92] = 0.0;
   out_5714773270956696752[93] = 0.0;
   out_5714773270956696752[94] = 0.0;
   out_5714773270956696752[95] = 1.0;
   out_5714773270956696752[96] = 0.0;
   out_5714773270956696752[97] = 0.0;
   out_5714773270956696752[98] = 0.0;
   out_5714773270956696752[99] = 0.0;
   out_5714773270956696752[100] = 0.0;
   out_5714773270956696752[101] = 0.0;
   out_5714773270956696752[102] = 0.0;
   out_5714773270956696752[103] = 0.0;
   out_5714773270956696752[104] = 0.0;
   out_5714773270956696752[105] = 0.0;
   out_5714773270956696752[106] = 0.0;
   out_5714773270956696752[107] = 0.0;
   out_5714773270956696752[108] = 0.0;
   out_5714773270956696752[109] = 0.0;
   out_5714773270956696752[110] = 0.0;
   out_5714773270956696752[111] = 0.0;
   out_5714773270956696752[112] = 0.0;
   out_5714773270956696752[113] = 0.0;
   out_5714773270956696752[114] = 1.0;
   out_5714773270956696752[115] = 0.0;
   out_5714773270956696752[116] = 0.0;
   out_5714773270956696752[117] = 0.0;
   out_5714773270956696752[118] = 0.0;
   out_5714773270956696752[119] = 0.0;
   out_5714773270956696752[120] = 0.0;
   out_5714773270956696752[121] = 0.0;
   out_5714773270956696752[122] = 0.0;
   out_5714773270956696752[123] = 0.0;
   out_5714773270956696752[124] = 0.0;
   out_5714773270956696752[125] = 0.0;
   out_5714773270956696752[126] = 0.0;
   out_5714773270956696752[127] = 0.0;
   out_5714773270956696752[128] = 0.0;
   out_5714773270956696752[129] = 0.0;
   out_5714773270956696752[130] = 0.0;
   out_5714773270956696752[131] = 0.0;
   out_5714773270956696752[132] = 0.0;
   out_5714773270956696752[133] = 1.0;
   out_5714773270956696752[134] = 0.0;
   out_5714773270956696752[135] = 0.0;
   out_5714773270956696752[136] = 0.0;
   out_5714773270956696752[137] = 0.0;
   out_5714773270956696752[138] = 0.0;
   out_5714773270956696752[139] = 0.0;
   out_5714773270956696752[140] = 0.0;
   out_5714773270956696752[141] = 0.0;
   out_5714773270956696752[142] = 0.0;
   out_5714773270956696752[143] = 0.0;
   out_5714773270956696752[144] = 0.0;
   out_5714773270956696752[145] = 0.0;
   out_5714773270956696752[146] = 0.0;
   out_5714773270956696752[147] = 0.0;
   out_5714773270956696752[148] = 0.0;
   out_5714773270956696752[149] = 0.0;
   out_5714773270956696752[150] = 0.0;
   out_5714773270956696752[151] = 0.0;
   out_5714773270956696752[152] = 1.0;
   out_5714773270956696752[153] = 0.0;
   out_5714773270956696752[154] = 0.0;
   out_5714773270956696752[155] = 0.0;
   out_5714773270956696752[156] = 0.0;
   out_5714773270956696752[157] = 0.0;
   out_5714773270956696752[158] = 0.0;
   out_5714773270956696752[159] = 0.0;
   out_5714773270956696752[160] = 0.0;
   out_5714773270956696752[161] = 0.0;
   out_5714773270956696752[162] = 0.0;
   out_5714773270956696752[163] = 0.0;
   out_5714773270956696752[164] = 0.0;
   out_5714773270956696752[165] = 0.0;
   out_5714773270956696752[166] = 0.0;
   out_5714773270956696752[167] = 0.0;
   out_5714773270956696752[168] = 0.0;
   out_5714773270956696752[169] = 0.0;
   out_5714773270956696752[170] = 0.0;
   out_5714773270956696752[171] = 1.0;
   out_5714773270956696752[172] = 0.0;
   out_5714773270956696752[173] = 0.0;
   out_5714773270956696752[174] = 0.0;
   out_5714773270956696752[175] = 0.0;
   out_5714773270956696752[176] = 0.0;
   out_5714773270956696752[177] = 0.0;
   out_5714773270956696752[178] = 0.0;
   out_5714773270956696752[179] = 0.0;
   out_5714773270956696752[180] = 0.0;
   out_5714773270956696752[181] = 0.0;
   out_5714773270956696752[182] = 0.0;
   out_5714773270956696752[183] = 0.0;
   out_5714773270956696752[184] = 0.0;
   out_5714773270956696752[185] = 0.0;
   out_5714773270956696752[186] = 0.0;
   out_5714773270956696752[187] = 0.0;
   out_5714773270956696752[188] = 0.0;
   out_5714773270956696752[189] = 0.0;
   out_5714773270956696752[190] = 1.0;
   out_5714773270956696752[191] = 0.0;
   out_5714773270956696752[192] = 0.0;
   out_5714773270956696752[193] = 0.0;
   out_5714773270956696752[194] = 0.0;
   out_5714773270956696752[195] = 0.0;
   out_5714773270956696752[196] = 0.0;
   out_5714773270956696752[197] = 0.0;
   out_5714773270956696752[198] = 0.0;
   out_5714773270956696752[199] = 0.0;
   out_5714773270956696752[200] = 0.0;
   out_5714773270956696752[201] = 0.0;
   out_5714773270956696752[202] = 0.0;
   out_5714773270956696752[203] = 0.0;
   out_5714773270956696752[204] = 0.0;
   out_5714773270956696752[205] = 0.0;
   out_5714773270956696752[206] = 0.0;
   out_5714773270956696752[207] = 0.0;
   out_5714773270956696752[208] = 0.0;
   out_5714773270956696752[209] = 1.0;
   out_5714773270956696752[210] = 0.0;
   out_5714773270956696752[211] = 0.0;
   out_5714773270956696752[212] = 0.0;
   out_5714773270956696752[213] = 0.0;
   out_5714773270956696752[214] = 0.0;
   out_5714773270956696752[215] = 0.0;
   out_5714773270956696752[216] = 0.0;
   out_5714773270956696752[217] = 0.0;
   out_5714773270956696752[218] = 0.0;
   out_5714773270956696752[219] = 0.0;
   out_5714773270956696752[220] = 0.0;
   out_5714773270956696752[221] = 0.0;
   out_5714773270956696752[222] = 0.0;
   out_5714773270956696752[223] = 0.0;
   out_5714773270956696752[224] = 0.0;
   out_5714773270956696752[225] = 0.0;
   out_5714773270956696752[226] = 0.0;
   out_5714773270956696752[227] = 0.0;
   out_5714773270956696752[228] = 1.0;
   out_5714773270956696752[229] = 0.0;
   out_5714773270956696752[230] = 0.0;
   out_5714773270956696752[231] = 0.0;
   out_5714773270956696752[232] = 0.0;
   out_5714773270956696752[233] = 0.0;
   out_5714773270956696752[234] = 0.0;
   out_5714773270956696752[235] = 0.0;
   out_5714773270956696752[236] = 0.0;
   out_5714773270956696752[237] = 0.0;
   out_5714773270956696752[238] = 0.0;
   out_5714773270956696752[239] = 0.0;
   out_5714773270956696752[240] = 0.0;
   out_5714773270956696752[241] = 0.0;
   out_5714773270956696752[242] = 0.0;
   out_5714773270956696752[243] = 0.0;
   out_5714773270956696752[244] = 0.0;
   out_5714773270956696752[245] = 0.0;
   out_5714773270956696752[246] = 0.0;
   out_5714773270956696752[247] = 1.0;
   out_5714773270956696752[248] = 0.0;
   out_5714773270956696752[249] = 0.0;
   out_5714773270956696752[250] = 0.0;
   out_5714773270956696752[251] = 0.0;
   out_5714773270956696752[252] = 0.0;
   out_5714773270956696752[253] = 0.0;
   out_5714773270956696752[254] = 0.0;
   out_5714773270956696752[255] = 0.0;
   out_5714773270956696752[256] = 0.0;
   out_5714773270956696752[257] = 0.0;
   out_5714773270956696752[258] = 0.0;
   out_5714773270956696752[259] = 0.0;
   out_5714773270956696752[260] = 0.0;
   out_5714773270956696752[261] = 0.0;
   out_5714773270956696752[262] = 0.0;
   out_5714773270956696752[263] = 0.0;
   out_5714773270956696752[264] = 0.0;
   out_5714773270956696752[265] = 0.0;
   out_5714773270956696752[266] = 1.0;
   out_5714773270956696752[267] = 0.0;
   out_5714773270956696752[268] = 0.0;
   out_5714773270956696752[269] = 0.0;
   out_5714773270956696752[270] = 0.0;
   out_5714773270956696752[271] = 0.0;
   out_5714773270956696752[272] = 0.0;
   out_5714773270956696752[273] = 0.0;
   out_5714773270956696752[274] = 0.0;
   out_5714773270956696752[275] = 0.0;
   out_5714773270956696752[276] = 0.0;
   out_5714773270956696752[277] = 0.0;
   out_5714773270956696752[278] = 0.0;
   out_5714773270956696752[279] = 0.0;
   out_5714773270956696752[280] = 0.0;
   out_5714773270956696752[281] = 0.0;
   out_5714773270956696752[282] = 0.0;
   out_5714773270956696752[283] = 0.0;
   out_5714773270956696752[284] = 0.0;
   out_5714773270956696752[285] = 1.0;
   out_5714773270956696752[286] = 0.0;
   out_5714773270956696752[287] = 0.0;
   out_5714773270956696752[288] = 0.0;
   out_5714773270956696752[289] = 0.0;
   out_5714773270956696752[290] = 0.0;
   out_5714773270956696752[291] = 0.0;
   out_5714773270956696752[292] = 0.0;
   out_5714773270956696752[293] = 0.0;
   out_5714773270956696752[294] = 0.0;
   out_5714773270956696752[295] = 0.0;
   out_5714773270956696752[296] = 0.0;
   out_5714773270956696752[297] = 0.0;
   out_5714773270956696752[298] = 0.0;
   out_5714773270956696752[299] = 0.0;
   out_5714773270956696752[300] = 0.0;
   out_5714773270956696752[301] = 0.0;
   out_5714773270956696752[302] = 0.0;
   out_5714773270956696752[303] = 0.0;
   out_5714773270956696752[304] = 1.0;
   out_5714773270956696752[305] = 0.0;
   out_5714773270956696752[306] = 0.0;
   out_5714773270956696752[307] = 0.0;
   out_5714773270956696752[308] = 0.0;
   out_5714773270956696752[309] = 0.0;
   out_5714773270956696752[310] = 0.0;
   out_5714773270956696752[311] = 0.0;
   out_5714773270956696752[312] = 0.0;
   out_5714773270956696752[313] = 0.0;
   out_5714773270956696752[314] = 0.0;
   out_5714773270956696752[315] = 0.0;
   out_5714773270956696752[316] = 0.0;
   out_5714773270956696752[317] = 0.0;
   out_5714773270956696752[318] = 0.0;
   out_5714773270956696752[319] = 0.0;
   out_5714773270956696752[320] = 0.0;
   out_5714773270956696752[321] = 0.0;
   out_5714773270956696752[322] = 0.0;
   out_5714773270956696752[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_2896016994829875537) {
   out_2896016994829875537[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_2896016994829875537[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_2896016994829875537[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_2896016994829875537[3] = dt*state[12] + state[3];
   out_2896016994829875537[4] = dt*state[13] + state[4];
   out_2896016994829875537[5] = dt*state[14] + state[5];
   out_2896016994829875537[6] = state[6];
   out_2896016994829875537[7] = state[7];
   out_2896016994829875537[8] = state[8];
   out_2896016994829875537[9] = state[9];
   out_2896016994829875537[10] = state[10];
   out_2896016994829875537[11] = state[11];
   out_2896016994829875537[12] = state[12];
   out_2896016994829875537[13] = state[13];
   out_2896016994829875537[14] = state[14];
   out_2896016994829875537[15] = state[15];
   out_2896016994829875537[16] = state[16];
   out_2896016994829875537[17] = state[17];
}
void F_fun(double *state, double dt, double *out_4605913986885817776) {
   out_4605913986885817776[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4605913986885817776[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4605913986885817776[2] = 0;
   out_4605913986885817776[3] = 0;
   out_4605913986885817776[4] = 0;
   out_4605913986885817776[5] = 0;
   out_4605913986885817776[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4605913986885817776[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4605913986885817776[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_4605913986885817776[9] = 0;
   out_4605913986885817776[10] = 0;
   out_4605913986885817776[11] = 0;
   out_4605913986885817776[12] = 0;
   out_4605913986885817776[13] = 0;
   out_4605913986885817776[14] = 0;
   out_4605913986885817776[15] = 0;
   out_4605913986885817776[16] = 0;
   out_4605913986885817776[17] = 0;
   out_4605913986885817776[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4605913986885817776[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4605913986885817776[20] = 0;
   out_4605913986885817776[21] = 0;
   out_4605913986885817776[22] = 0;
   out_4605913986885817776[23] = 0;
   out_4605913986885817776[24] = 0;
   out_4605913986885817776[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4605913986885817776[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_4605913986885817776[27] = 0;
   out_4605913986885817776[28] = 0;
   out_4605913986885817776[29] = 0;
   out_4605913986885817776[30] = 0;
   out_4605913986885817776[31] = 0;
   out_4605913986885817776[32] = 0;
   out_4605913986885817776[33] = 0;
   out_4605913986885817776[34] = 0;
   out_4605913986885817776[35] = 0;
   out_4605913986885817776[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4605913986885817776[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4605913986885817776[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4605913986885817776[39] = 0;
   out_4605913986885817776[40] = 0;
   out_4605913986885817776[41] = 0;
   out_4605913986885817776[42] = 0;
   out_4605913986885817776[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4605913986885817776[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_4605913986885817776[45] = 0;
   out_4605913986885817776[46] = 0;
   out_4605913986885817776[47] = 0;
   out_4605913986885817776[48] = 0;
   out_4605913986885817776[49] = 0;
   out_4605913986885817776[50] = 0;
   out_4605913986885817776[51] = 0;
   out_4605913986885817776[52] = 0;
   out_4605913986885817776[53] = 0;
   out_4605913986885817776[54] = 0;
   out_4605913986885817776[55] = 0;
   out_4605913986885817776[56] = 0;
   out_4605913986885817776[57] = 1;
   out_4605913986885817776[58] = 0;
   out_4605913986885817776[59] = 0;
   out_4605913986885817776[60] = 0;
   out_4605913986885817776[61] = 0;
   out_4605913986885817776[62] = 0;
   out_4605913986885817776[63] = 0;
   out_4605913986885817776[64] = 0;
   out_4605913986885817776[65] = 0;
   out_4605913986885817776[66] = dt;
   out_4605913986885817776[67] = 0;
   out_4605913986885817776[68] = 0;
   out_4605913986885817776[69] = 0;
   out_4605913986885817776[70] = 0;
   out_4605913986885817776[71] = 0;
   out_4605913986885817776[72] = 0;
   out_4605913986885817776[73] = 0;
   out_4605913986885817776[74] = 0;
   out_4605913986885817776[75] = 0;
   out_4605913986885817776[76] = 1;
   out_4605913986885817776[77] = 0;
   out_4605913986885817776[78] = 0;
   out_4605913986885817776[79] = 0;
   out_4605913986885817776[80] = 0;
   out_4605913986885817776[81] = 0;
   out_4605913986885817776[82] = 0;
   out_4605913986885817776[83] = 0;
   out_4605913986885817776[84] = 0;
   out_4605913986885817776[85] = dt;
   out_4605913986885817776[86] = 0;
   out_4605913986885817776[87] = 0;
   out_4605913986885817776[88] = 0;
   out_4605913986885817776[89] = 0;
   out_4605913986885817776[90] = 0;
   out_4605913986885817776[91] = 0;
   out_4605913986885817776[92] = 0;
   out_4605913986885817776[93] = 0;
   out_4605913986885817776[94] = 0;
   out_4605913986885817776[95] = 1;
   out_4605913986885817776[96] = 0;
   out_4605913986885817776[97] = 0;
   out_4605913986885817776[98] = 0;
   out_4605913986885817776[99] = 0;
   out_4605913986885817776[100] = 0;
   out_4605913986885817776[101] = 0;
   out_4605913986885817776[102] = 0;
   out_4605913986885817776[103] = 0;
   out_4605913986885817776[104] = dt;
   out_4605913986885817776[105] = 0;
   out_4605913986885817776[106] = 0;
   out_4605913986885817776[107] = 0;
   out_4605913986885817776[108] = 0;
   out_4605913986885817776[109] = 0;
   out_4605913986885817776[110] = 0;
   out_4605913986885817776[111] = 0;
   out_4605913986885817776[112] = 0;
   out_4605913986885817776[113] = 0;
   out_4605913986885817776[114] = 1;
   out_4605913986885817776[115] = 0;
   out_4605913986885817776[116] = 0;
   out_4605913986885817776[117] = 0;
   out_4605913986885817776[118] = 0;
   out_4605913986885817776[119] = 0;
   out_4605913986885817776[120] = 0;
   out_4605913986885817776[121] = 0;
   out_4605913986885817776[122] = 0;
   out_4605913986885817776[123] = 0;
   out_4605913986885817776[124] = 0;
   out_4605913986885817776[125] = 0;
   out_4605913986885817776[126] = 0;
   out_4605913986885817776[127] = 0;
   out_4605913986885817776[128] = 0;
   out_4605913986885817776[129] = 0;
   out_4605913986885817776[130] = 0;
   out_4605913986885817776[131] = 0;
   out_4605913986885817776[132] = 0;
   out_4605913986885817776[133] = 1;
   out_4605913986885817776[134] = 0;
   out_4605913986885817776[135] = 0;
   out_4605913986885817776[136] = 0;
   out_4605913986885817776[137] = 0;
   out_4605913986885817776[138] = 0;
   out_4605913986885817776[139] = 0;
   out_4605913986885817776[140] = 0;
   out_4605913986885817776[141] = 0;
   out_4605913986885817776[142] = 0;
   out_4605913986885817776[143] = 0;
   out_4605913986885817776[144] = 0;
   out_4605913986885817776[145] = 0;
   out_4605913986885817776[146] = 0;
   out_4605913986885817776[147] = 0;
   out_4605913986885817776[148] = 0;
   out_4605913986885817776[149] = 0;
   out_4605913986885817776[150] = 0;
   out_4605913986885817776[151] = 0;
   out_4605913986885817776[152] = 1;
   out_4605913986885817776[153] = 0;
   out_4605913986885817776[154] = 0;
   out_4605913986885817776[155] = 0;
   out_4605913986885817776[156] = 0;
   out_4605913986885817776[157] = 0;
   out_4605913986885817776[158] = 0;
   out_4605913986885817776[159] = 0;
   out_4605913986885817776[160] = 0;
   out_4605913986885817776[161] = 0;
   out_4605913986885817776[162] = 0;
   out_4605913986885817776[163] = 0;
   out_4605913986885817776[164] = 0;
   out_4605913986885817776[165] = 0;
   out_4605913986885817776[166] = 0;
   out_4605913986885817776[167] = 0;
   out_4605913986885817776[168] = 0;
   out_4605913986885817776[169] = 0;
   out_4605913986885817776[170] = 0;
   out_4605913986885817776[171] = 1;
   out_4605913986885817776[172] = 0;
   out_4605913986885817776[173] = 0;
   out_4605913986885817776[174] = 0;
   out_4605913986885817776[175] = 0;
   out_4605913986885817776[176] = 0;
   out_4605913986885817776[177] = 0;
   out_4605913986885817776[178] = 0;
   out_4605913986885817776[179] = 0;
   out_4605913986885817776[180] = 0;
   out_4605913986885817776[181] = 0;
   out_4605913986885817776[182] = 0;
   out_4605913986885817776[183] = 0;
   out_4605913986885817776[184] = 0;
   out_4605913986885817776[185] = 0;
   out_4605913986885817776[186] = 0;
   out_4605913986885817776[187] = 0;
   out_4605913986885817776[188] = 0;
   out_4605913986885817776[189] = 0;
   out_4605913986885817776[190] = 1;
   out_4605913986885817776[191] = 0;
   out_4605913986885817776[192] = 0;
   out_4605913986885817776[193] = 0;
   out_4605913986885817776[194] = 0;
   out_4605913986885817776[195] = 0;
   out_4605913986885817776[196] = 0;
   out_4605913986885817776[197] = 0;
   out_4605913986885817776[198] = 0;
   out_4605913986885817776[199] = 0;
   out_4605913986885817776[200] = 0;
   out_4605913986885817776[201] = 0;
   out_4605913986885817776[202] = 0;
   out_4605913986885817776[203] = 0;
   out_4605913986885817776[204] = 0;
   out_4605913986885817776[205] = 0;
   out_4605913986885817776[206] = 0;
   out_4605913986885817776[207] = 0;
   out_4605913986885817776[208] = 0;
   out_4605913986885817776[209] = 1;
   out_4605913986885817776[210] = 0;
   out_4605913986885817776[211] = 0;
   out_4605913986885817776[212] = 0;
   out_4605913986885817776[213] = 0;
   out_4605913986885817776[214] = 0;
   out_4605913986885817776[215] = 0;
   out_4605913986885817776[216] = 0;
   out_4605913986885817776[217] = 0;
   out_4605913986885817776[218] = 0;
   out_4605913986885817776[219] = 0;
   out_4605913986885817776[220] = 0;
   out_4605913986885817776[221] = 0;
   out_4605913986885817776[222] = 0;
   out_4605913986885817776[223] = 0;
   out_4605913986885817776[224] = 0;
   out_4605913986885817776[225] = 0;
   out_4605913986885817776[226] = 0;
   out_4605913986885817776[227] = 0;
   out_4605913986885817776[228] = 1;
   out_4605913986885817776[229] = 0;
   out_4605913986885817776[230] = 0;
   out_4605913986885817776[231] = 0;
   out_4605913986885817776[232] = 0;
   out_4605913986885817776[233] = 0;
   out_4605913986885817776[234] = 0;
   out_4605913986885817776[235] = 0;
   out_4605913986885817776[236] = 0;
   out_4605913986885817776[237] = 0;
   out_4605913986885817776[238] = 0;
   out_4605913986885817776[239] = 0;
   out_4605913986885817776[240] = 0;
   out_4605913986885817776[241] = 0;
   out_4605913986885817776[242] = 0;
   out_4605913986885817776[243] = 0;
   out_4605913986885817776[244] = 0;
   out_4605913986885817776[245] = 0;
   out_4605913986885817776[246] = 0;
   out_4605913986885817776[247] = 1;
   out_4605913986885817776[248] = 0;
   out_4605913986885817776[249] = 0;
   out_4605913986885817776[250] = 0;
   out_4605913986885817776[251] = 0;
   out_4605913986885817776[252] = 0;
   out_4605913986885817776[253] = 0;
   out_4605913986885817776[254] = 0;
   out_4605913986885817776[255] = 0;
   out_4605913986885817776[256] = 0;
   out_4605913986885817776[257] = 0;
   out_4605913986885817776[258] = 0;
   out_4605913986885817776[259] = 0;
   out_4605913986885817776[260] = 0;
   out_4605913986885817776[261] = 0;
   out_4605913986885817776[262] = 0;
   out_4605913986885817776[263] = 0;
   out_4605913986885817776[264] = 0;
   out_4605913986885817776[265] = 0;
   out_4605913986885817776[266] = 1;
   out_4605913986885817776[267] = 0;
   out_4605913986885817776[268] = 0;
   out_4605913986885817776[269] = 0;
   out_4605913986885817776[270] = 0;
   out_4605913986885817776[271] = 0;
   out_4605913986885817776[272] = 0;
   out_4605913986885817776[273] = 0;
   out_4605913986885817776[274] = 0;
   out_4605913986885817776[275] = 0;
   out_4605913986885817776[276] = 0;
   out_4605913986885817776[277] = 0;
   out_4605913986885817776[278] = 0;
   out_4605913986885817776[279] = 0;
   out_4605913986885817776[280] = 0;
   out_4605913986885817776[281] = 0;
   out_4605913986885817776[282] = 0;
   out_4605913986885817776[283] = 0;
   out_4605913986885817776[284] = 0;
   out_4605913986885817776[285] = 1;
   out_4605913986885817776[286] = 0;
   out_4605913986885817776[287] = 0;
   out_4605913986885817776[288] = 0;
   out_4605913986885817776[289] = 0;
   out_4605913986885817776[290] = 0;
   out_4605913986885817776[291] = 0;
   out_4605913986885817776[292] = 0;
   out_4605913986885817776[293] = 0;
   out_4605913986885817776[294] = 0;
   out_4605913986885817776[295] = 0;
   out_4605913986885817776[296] = 0;
   out_4605913986885817776[297] = 0;
   out_4605913986885817776[298] = 0;
   out_4605913986885817776[299] = 0;
   out_4605913986885817776[300] = 0;
   out_4605913986885817776[301] = 0;
   out_4605913986885817776[302] = 0;
   out_4605913986885817776[303] = 0;
   out_4605913986885817776[304] = 1;
   out_4605913986885817776[305] = 0;
   out_4605913986885817776[306] = 0;
   out_4605913986885817776[307] = 0;
   out_4605913986885817776[308] = 0;
   out_4605913986885817776[309] = 0;
   out_4605913986885817776[310] = 0;
   out_4605913986885817776[311] = 0;
   out_4605913986885817776[312] = 0;
   out_4605913986885817776[313] = 0;
   out_4605913986885817776[314] = 0;
   out_4605913986885817776[315] = 0;
   out_4605913986885817776[316] = 0;
   out_4605913986885817776[317] = 0;
   out_4605913986885817776[318] = 0;
   out_4605913986885817776[319] = 0;
   out_4605913986885817776[320] = 0;
   out_4605913986885817776[321] = 0;
   out_4605913986885817776[322] = 0;
   out_4605913986885817776[323] = 1;
}
void h_4(double *state, double *unused, double *out_5842182755326302952) {
   out_5842182755326302952[0] = state[6] + state[9];
   out_5842182755326302952[1] = state[7] + state[10];
   out_5842182755326302952[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_3229588395101124590) {
   out_3229588395101124590[0] = 0;
   out_3229588395101124590[1] = 0;
   out_3229588395101124590[2] = 0;
   out_3229588395101124590[3] = 0;
   out_3229588395101124590[4] = 0;
   out_3229588395101124590[5] = 0;
   out_3229588395101124590[6] = 1;
   out_3229588395101124590[7] = 0;
   out_3229588395101124590[8] = 0;
   out_3229588395101124590[9] = 1;
   out_3229588395101124590[10] = 0;
   out_3229588395101124590[11] = 0;
   out_3229588395101124590[12] = 0;
   out_3229588395101124590[13] = 0;
   out_3229588395101124590[14] = 0;
   out_3229588395101124590[15] = 0;
   out_3229588395101124590[16] = 0;
   out_3229588395101124590[17] = 0;
   out_3229588395101124590[18] = 0;
   out_3229588395101124590[19] = 0;
   out_3229588395101124590[20] = 0;
   out_3229588395101124590[21] = 0;
   out_3229588395101124590[22] = 0;
   out_3229588395101124590[23] = 0;
   out_3229588395101124590[24] = 0;
   out_3229588395101124590[25] = 1;
   out_3229588395101124590[26] = 0;
   out_3229588395101124590[27] = 0;
   out_3229588395101124590[28] = 1;
   out_3229588395101124590[29] = 0;
   out_3229588395101124590[30] = 0;
   out_3229588395101124590[31] = 0;
   out_3229588395101124590[32] = 0;
   out_3229588395101124590[33] = 0;
   out_3229588395101124590[34] = 0;
   out_3229588395101124590[35] = 0;
   out_3229588395101124590[36] = 0;
   out_3229588395101124590[37] = 0;
   out_3229588395101124590[38] = 0;
   out_3229588395101124590[39] = 0;
   out_3229588395101124590[40] = 0;
   out_3229588395101124590[41] = 0;
   out_3229588395101124590[42] = 0;
   out_3229588395101124590[43] = 0;
   out_3229588395101124590[44] = 1;
   out_3229588395101124590[45] = 0;
   out_3229588395101124590[46] = 0;
   out_3229588395101124590[47] = 1;
   out_3229588395101124590[48] = 0;
   out_3229588395101124590[49] = 0;
   out_3229588395101124590[50] = 0;
   out_3229588395101124590[51] = 0;
   out_3229588395101124590[52] = 0;
   out_3229588395101124590[53] = 0;
}
void h_10(double *state, double *unused, double *out_3449867082812412812) {
   out_3449867082812412812[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3449867082812412812[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3449867082812412812[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7178221840794629758) {
   out_7178221840794629758[0] = 0;
   out_7178221840794629758[1] = 9.8100000000000005*cos(state[1]);
   out_7178221840794629758[2] = 0;
   out_7178221840794629758[3] = 0;
   out_7178221840794629758[4] = -state[8];
   out_7178221840794629758[5] = state[7];
   out_7178221840794629758[6] = 0;
   out_7178221840794629758[7] = state[5];
   out_7178221840794629758[8] = -state[4];
   out_7178221840794629758[9] = 0;
   out_7178221840794629758[10] = 0;
   out_7178221840794629758[11] = 0;
   out_7178221840794629758[12] = 1;
   out_7178221840794629758[13] = 0;
   out_7178221840794629758[14] = 0;
   out_7178221840794629758[15] = 1;
   out_7178221840794629758[16] = 0;
   out_7178221840794629758[17] = 0;
   out_7178221840794629758[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7178221840794629758[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7178221840794629758[20] = 0;
   out_7178221840794629758[21] = state[8];
   out_7178221840794629758[22] = 0;
   out_7178221840794629758[23] = -state[6];
   out_7178221840794629758[24] = -state[5];
   out_7178221840794629758[25] = 0;
   out_7178221840794629758[26] = state[3];
   out_7178221840794629758[27] = 0;
   out_7178221840794629758[28] = 0;
   out_7178221840794629758[29] = 0;
   out_7178221840794629758[30] = 0;
   out_7178221840794629758[31] = 1;
   out_7178221840794629758[32] = 0;
   out_7178221840794629758[33] = 0;
   out_7178221840794629758[34] = 1;
   out_7178221840794629758[35] = 0;
   out_7178221840794629758[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7178221840794629758[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7178221840794629758[38] = 0;
   out_7178221840794629758[39] = -state[7];
   out_7178221840794629758[40] = state[6];
   out_7178221840794629758[41] = 0;
   out_7178221840794629758[42] = state[4];
   out_7178221840794629758[43] = -state[3];
   out_7178221840794629758[44] = 0;
   out_7178221840794629758[45] = 0;
   out_7178221840794629758[46] = 0;
   out_7178221840794629758[47] = 0;
   out_7178221840794629758[48] = 0;
   out_7178221840794629758[49] = 0;
   out_7178221840794629758[50] = 1;
   out_7178221840794629758[51] = 0;
   out_7178221840794629758[52] = 0;
   out_7178221840794629758[53] = 1;
}
void h_13(double *state, double *unused, double *out_2961129492765088647) {
   out_2961129492765088647[0] = state[3];
   out_2961129492765088647[1] = state[4];
   out_2961129492765088647[2] = state[5];
}
void H_13(double *state, double *unused, double *out_17314569768791789) {
   out_17314569768791789[0] = 0;
   out_17314569768791789[1] = 0;
   out_17314569768791789[2] = 0;
   out_17314569768791789[3] = 1;
   out_17314569768791789[4] = 0;
   out_17314569768791789[5] = 0;
   out_17314569768791789[6] = 0;
   out_17314569768791789[7] = 0;
   out_17314569768791789[8] = 0;
   out_17314569768791789[9] = 0;
   out_17314569768791789[10] = 0;
   out_17314569768791789[11] = 0;
   out_17314569768791789[12] = 0;
   out_17314569768791789[13] = 0;
   out_17314569768791789[14] = 0;
   out_17314569768791789[15] = 0;
   out_17314569768791789[16] = 0;
   out_17314569768791789[17] = 0;
   out_17314569768791789[18] = 0;
   out_17314569768791789[19] = 0;
   out_17314569768791789[20] = 0;
   out_17314569768791789[21] = 0;
   out_17314569768791789[22] = 1;
   out_17314569768791789[23] = 0;
   out_17314569768791789[24] = 0;
   out_17314569768791789[25] = 0;
   out_17314569768791789[26] = 0;
   out_17314569768791789[27] = 0;
   out_17314569768791789[28] = 0;
   out_17314569768791789[29] = 0;
   out_17314569768791789[30] = 0;
   out_17314569768791789[31] = 0;
   out_17314569768791789[32] = 0;
   out_17314569768791789[33] = 0;
   out_17314569768791789[34] = 0;
   out_17314569768791789[35] = 0;
   out_17314569768791789[36] = 0;
   out_17314569768791789[37] = 0;
   out_17314569768791789[38] = 0;
   out_17314569768791789[39] = 0;
   out_17314569768791789[40] = 0;
   out_17314569768791789[41] = 1;
   out_17314569768791789[42] = 0;
   out_17314569768791789[43] = 0;
   out_17314569768791789[44] = 0;
   out_17314569768791789[45] = 0;
   out_17314569768791789[46] = 0;
   out_17314569768791789[47] = 0;
   out_17314569768791789[48] = 0;
   out_17314569768791789[49] = 0;
   out_17314569768791789[50] = 0;
   out_17314569768791789[51] = 0;
   out_17314569768791789[52] = 0;
   out_17314569768791789[53] = 0;
}
void h_14(double *state, double *unused, double *out_5769522878399662028) {
   out_5769522878399662028[0] = state[6];
   out_5769522878399662028[1] = state[7];
   out_5769522878399662028[2] = state[8];
}
void H_14(double *state, double *unused, double *out_733652461238359939) {
   out_733652461238359939[0] = 0;
   out_733652461238359939[1] = 0;
   out_733652461238359939[2] = 0;
   out_733652461238359939[3] = 0;
   out_733652461238359939[4] = 0;
   out_733652461238359939[5] = 0;
   out_733652461238359939[6] = 1;
   out_733652461238359939[7] = 0;
   out_733652461238359939[8] = 0;
   out_733652461238359939[9] = 0;
   out_733652461238359939[10] = 0;
   out_733652461238359939[11] = 0;
   out_733652461238359939[12] = 0;
   out_733652461238359939[13] = 0;
   out_733652461238359939[14] = 0;
   out_733652461238359939[15] = 0;
   out_733652461238359939[16] = 0;
   out_733652461238359939[17] = 0;
   out_733652461238359939[18] = 0;
   out_733652461238359939[19] = 0;
   out_733652461238359939[20] = 0;
   out_733652461238359939[21] = 0;
   out_733652461238359939[22] = 0;
   out_733652461238359939[23] = 0;
   out_733652461238359939[24] = 0;
   out_733652461238359939[25] = 1;
   out_733652461238359939[26] = 0;
   out_733652461238359939[27] = 0;
   out_733652461238359939[28] = 0;
   out_733652461238359939[29] = 0;
   out_733652461238359939[30] = 0;
   out_733652461238359939[31] = 0;
   out_733652461238359939[32] = 0;
   out_733652461238359939[33] = 0;
   out_733652461238359939[34] = 0;
   out_733652461238359939[35] = 0;
   out_733652461238359939[36] = 0;
   out_733652461238359939[37] = 0;
   out_733652461238359939[38] = 0;
   out_733652461238359939[39] = 0;
   out_733652461238359939[40] = 0;
   out_733652461238359939[41] = 0;
   out_733652461238359939[42] = 0;
   out_733652461238359939[43] = 0;
   out_733652461238359939[44] = 1;
   out_733652461238359939[45] = 0;
   out_733652461238359939[46] = 0;
   out_733652461238359939[47] = 0;
   out_733652461238359939[48] = 0;
   out_733652461238359939[49] = 0;
   out_733652461238359939[50] = 0;
   out_733652461238359939[51] = 0;
   out_733652461238359939[52] = 0;
   out_733652461238359939[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2547418662005312230) {
  err_fun(nom_x, delta_x, out_2547418662005312230);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7399773008628044860) {
  inv_err_fun(nom_x, true_x, out_7399773008628044860);
}
void pose_H_mod_fun(double *state, double *out_5714773270956696752) {
  H_mod_fun(state, out_5714773270956696752);
}
void pose_f_fun(double *state, double dt, double *out_2896016994829875537) {
  f_fun(state,  dt, out_2896016994829875537);
}
void pose_F_fun(double *state, double dt, double *out_4605913986885817776) {
  F_fun(state,  dt, out_4605913986885817776);
}
void pose_h_4(double *state, double *unused, double *out_5842182755326302952) {
  h_4(state, unused, out_5842182755326302952);
}
void pose_H_4(double *state, double *unused, double *out_3229588395101124590) {
  H_4(state, unused, out_3229588395101124590);
}
void pose_h_10(double *state, double *unused, double *out_3449867082812412812) {
  h_10(state, unused, out_3449867082812412812);
}
void pose_H_10(double *state, double *unused, double *out_7178221840794629758) {
  H_10(state, unused, out_7178221840794629758);
}
void pose_h_13(double *state, double *unused, double *out_2961129492765088647) {
  h_13(state, unused, out_2961129492765088647);
}
void pose_H_13(double *state, double *unused, double *out_17314569768791789) {
  H_13(state, unused, out_17314569768791789);
}
void pose_h_14(double *state, double *unused, double *out_5769522878399662028) {
  h_14(state, unused, out_5769522878399662028);
}
void pose_H_14(double *state, double *unused, double *out_733652461238359939) {
  H_14(state, unused, out_733652461238359939);
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
