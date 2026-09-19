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
void err_fun(double *nom_x, double *delta_x, double *out_5353336122144560205) {
   out_5353336122144560205[0] = delta_x[0] + nom_x[0];
   out_5353336122144560205[1] = delta_x[1] + nom_x[1];
   out_5353336122144560205[2] = delta_x[2] + nom_x[2];
   out_5353336122144560205[3] = delta_x[3] + nom_x[3];
   out_5353336122144560205[4] = delta_x[4] + nom_x[4];
   out_5353336122144560205[5] = delta_x[5] + nom_x[5];
   out_5353336122144560205[6] = delta_x[6] + nom_x[6];
   out_5353336122144560205[7] = delta_x[7] + nom_x[7];
   out_5353336122144560205[8] = delta_x[8] + nom_x[8];
   out_5353336122144560205[9] = delta_x[9] + nom_x[9];
   out_5353336122144560205[10] = delta_x[10] + nom_x[10];
   out_5353336122144560205[11] = delta_x[11] + nom_x[11];
   out_5353336122144560205[12] = delta_x[12] + nom_x[12];
   out_5353336122144560205[13] = delta_x[13] + nom_x[13];
   out_5353336122144560205[14] = delta_x[14] + nom_x[14];
   out_5353336122144560205[15] = delta_x[15] + nom_x[15];
   out_5353336122144560205[16] = delta_x[16] + nom_x[16];
   out_5353336122144560205[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4798572186740292528) {
   out_4798572186740292528[0] = -nom_x[0] + true_x[0];
   out_4798572186740292528[1] = -nom_x[1] + true_x[1];
   out_4798572186740292528[2] = -nom_x[2] + true_x[2];
   out_4798572186740292528[3] = -nom_x[3] + true_x[3];
   out_4798572186740292528[4] = -nom_x[4] + true_x[4];
   out_4798572186740292528[5] = -nom_x[5] + true_x[5];
   out_4798572186740292528[6] = -nom_x[6] + true_x[6];
   out_4798572186740292528[7] = -nom_x[7] + true_x[7];
   out_4798572186740292528[8] = -nom_x[8] + true_x[8];
   out_4798572186740292528[9] = -nom_x[9] + true_x[9];
   out_4798572186740292528[10] = -nom_x[10] + true_x[10];
   out_4798572186740292528[11] = -nom_x[11] + true_x[11];
   out_4798572186740292528[12] = -nom_x[12] + true_x[12];
   out_4798572186740292528[13] = -nom_x[13] + true_x[13];
   out_4798572186740292528[14] = -nom_x[14] + true_x[14];
   out_4798572186740292528[15] = -nom_x[15] + true_x[15];
   out_4798572186740292528[16] = -nom_x[16] + true_x[16];
   out_4798572186740292528[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7952152851251730240) {
   out_7952152851251730240[0] = 1.0;
   out_7952152851251730240[1] = 0.0;
   out_7952152851251730240[2] = 0.0;
   out_7952152851251730240[3] = 0.0;
   out_7952152851251730240[4] = 0.0;
   out_7952152851251730240[5] = 0.0;
   out_7952152851251730240[6] = 0.0;
   out_7952152851251730240[7] = 0.0;
   out_7952152851251730240[8] = 0.0;
   out_7952152851251730240[9] = 0.0;
   out_7952152851251730240[10] = 0.0;
   out_7952152851251730240[11] = 0.0;
   out_7952152851251730240[12] = 0.0;
   out_7952152851251730240[13] = 0.0;
   out_7952152851251730240[14] = 0.0;
   out_7952152851251730240[15] = 0.0;
   out_7952152851251730240[16] = 0.0;
   out_7952152851251730240[17] = 0.0;
   out_7952152851251730240[18] = 0.0;
   out_7952152851251730240[19] = 1.0;
   out_7952152851251730240[20] = 0.0;
   out_7952152851251730240[21] = 0.0;
   out_7952152851251730240[22] = 0.0;
   out_7952152851251730240[23] = 0.0;
   out_7952152851251730240[24] = 0.0;
   out_7952152851251730240[25] = 0.0;
   out_7952152851251730240[26] = 0.0;
   out_7952152851251730240[27] = 0.0;
   out_7952152851251730240[28] = 0.0;
   out_7952152851251730240[29] = 0.0;
   out_7952152851251730240[30] = 0.0;
   out_7952152851251730240[31] = 0.0;
   out_7952152851251730240[32] = 0.0;
   out_7952152851251730240[33] = 0.0;
   out_7952152851251730240[34] = 0.0;
   out_7952152851251730240[35] = 0.0;
   out_7952152851251730240[36] = 0.0;
   out_7952152851251730240[37] = 0.0;
   out_7952152851251730240[38] = 1.0;
   out_7952152851251730240[39] = 0.0;
   out_7952152851251730240[40] = 0.0;
   out_7952152851251730240[41] = 0.0;
   out_7952152851251730240[42] = 0.0;
   out_7952152851251730240[43] = 0.0;
   out_7952152851251730240[44] = 0.0;
   out_7952152851251730240[45] = 0.0;
   out_7952152851251730240[46] = 0.0;
   out_7952152851251730240[47] = 0.0;
   out_7952152851251730240[48] = 0.0;
   out_7952152851251730240[49] = 0.0;
   out_7952152851251730240[50] = 0.0;
   out_7952152851251730240[51] = 0.0;
   out_7952152851251730240[52] = 0.0;
   out_7952152851251730240[53] = 0.0;
   out_7952152851251730240[54] = 0.0;
   out_7952152851251730240[55] = 0.0;
   out_7952152851251730240[56] = 0.0;
   out_7952152851251730240[57] = 1.0;
   out_7952152851251730240[58] = 0.0;
   out_7952152851251730240[59] = 0.0;
   out_7952152851251730240[60] = 0.0;
   out_7952152851251730240[61] = 0.0;
   out_7952152851251730240[62] = 0.0;
   out_7952152851251730240[63] = 0.0;
   out_7952152851251730240[64] = 0.0;
   out_7952152851251730240[65] = 0.0;
   out_7952152851251730240[66] = 0.0;
   out_7952152851251730240[67] = 0.0;
   out_7952152851251730240[68] = 0.0;
   out_7952152851251730240[69] = 0.0;
   out_7952152851251730240[70] = 0.0;
   out_7952152851251730240[71] = 0.0;
   out_7952152851251730240[72] = 0.0;
   out_7952152851251730240[73] = 0.0;
   out_7952152851251730240[74] = 0.0;
   out_7952152851251730240[75] = 0.0;
   out_7952152851251730240[76] = 1.0;
   out_7952152851251730240[77] = 0.0;
   out_7952152851251730240[78] = 0.0;
   out_7952152851251730240[79] = 0.0;
   out_7952152851251730240[80] = 0.0;
   out_7952152851251730240[81] = 0.0;
   out_7952152851251730240[82] = 0.0;
   out_7952152851251730240[83] = 0.0;
   out_7952152851251730240[84] = 0.0;
   out_7952152851251730240[85] = 0.0;
   out_7952152851251730240[86] = 0.0;
   out_7952152851251730240[87] = 0.0;
   out_7952152851251730240[88] = 0.0;
   out_7952152851251730240[89] = 0.0;
   out_7952152851251730240[90] = 0.0;
   out_7952152851251730240[91] = 0.0;
   out_7952152851251730240[92] = 0.0;
   out_7952152851251730240[93] = 0.0;
   out_7952152851251730240[94] = 0.0;
   out_7952152851251730240[95] = 1.0;
   out_7952152851251730240[96] = 0.0;
   out_7952152851251730240[97] = 0.0;
   out_7952152851251730240[98] = 0.0;
   out_7952152851251730240[99] = 0.0;
   out_7952152851251730240[100] = 0.0;
   out_7952152851251730240[101] = 0.0;
   out_7952152851251730240[102] = 0.0;
   out_7952152851251730240[103] = 0.0;
   out_7952152851251730240[104] = 0.0;
   out_7952152851251730240[105] = 0.0;
   out_7952152851251730240[106] = 0.0;
   out_7952152851251730240[107] = 0.0;
   out_7952152851251730240[108] = 0.0;
   out_7952152851251730240[109] = 0.0;
   out_7952152851251730240[110] = 0.0;
   out_7952152851251730240[111] = 0.0;
   out_7952152851251730240[112] = 0.0;
   out_7952152851251730240[113] = 0.0;
   out_7952152851251730240[114] = 1.0;
   out_7952152851251730240[115] = 0.0;
   out_7952152851251730240[116] = 0.0;
   out_7952152851251730240[117] = 0.0;
   out_7952152851251730240[118] = 0.0;
   out_7952152851251730240[119] = 0.0;
   out_7952152851251730240[120] = 0.0;
   out_7952152851251730240[121] = 0.0;
   out_7952152851251730240[122] = 0.0;
   out_7952152851251730240[123] = 0.0;
   out_7952152851251730240[124] = 0.0;
   out_7952152851251730240[125] = 0.0;
   out_7952152851251730240[126] = 0.0;
   out_7952152851251730240[127] = 0.0;
   out_7952152851251730240[128] = 0.0;
   out_7952152851251730240[129] = 0.0;
   out_7952152851251730240[130] = 0.0;
   out_7952152851251730240[131] = 0.0;
   out_7952152851251730240[132] = 0.0;
   out_7952152851251730240[133] = 1.0;
   out_7952152851251730240[134] = 0.0;
   out_7952152851251730240[135] = 0.0;
   out_7952152851251730240[136] = 0.0;
   out_7952152851251730240[137] = 0.0;
   out_7952152851251730240[138] = 0.0;
   out_7952152851251730240[139] = 0.0;
   out_7952152851251730240[140] = 0.0;
   out_7952152851251730240[141] = 0.0;
   out_7952152851251730240[142] = 0.0;
   out_7952152851251730240[143] = 0.0;
   out_7952152851251730240[144] = 0.0;
   out_7952152851251730240[145] = 0.0;
   out_7952152851251730240[146] = 0.0;
   out_7952152851251730240[147] = 0.0;
   out_7952152851251730240[148] = 0.0;
   out_7952152851251730240[149] = 0.0;
   out_7952152851251730240[150] = 0.0;
   out_7952152851251730240[151] = 0.0;
   out_7952152851251730240[152] = 1.0;
   out_7952152851251730240[153] = 0.0;
   out_7952152851251730240[154] = 0.0;
   out_7952152851251730240[155] = 0.0;
   out_7952152851251730240[156] = 0.0;
   out_7952152851251730240[157] = 0.0;
   out_7952152851251730240[158] = 0.0;
   out_7952152851251730240[159] = 0.0;
   out_7952152851251730240[160] = 0.0;
   out_7952152851251730240[161] = 0.0;
   out_7952152851251730240[162] = 0.0;
   out_7952152851251730240[163] = 0.0;
   out_7952152851251730240[164] = 0.0;
   out_7952152851251730240[165] = 0.0;
   out_7952152851251730240[166] = 0.0;
   out_7952152851251730240[167] = 0.0;
   out_7952152851251730240[168] = 0.0;
   out_7952152851251730240[169] = 0.0;
   out_7952152851251730240[170] = 0.0;
   out_7952152851251730240[171] = 1.0;
   out_7952152851251730240[172] = 0.0;
   out_7952152851251730240[173] = 0.0;
   out_7952152851251730240[174] = 0.0;
   out_7952152851251730240[175] = 0.0;
   out_7952152851251730240[176] = 0.0;
   out_7952152851251730240[177] = 0.0;
   out_7952152851251730240[178] = 0.0;
   out_7952152851251730240[179] = 0.0;
   out_7952152851251730240[180] = 0.0;
   out_7952152851251730240[181] = 0.0;
   out_7952152851251730240[182] = 0.0;
   out_7952152851251730240[183] = 0.0;
   out_7952152851251730240[184] = 0.0;
   out_7952152851251730240[185] = 0.0;
   out_7952152851251730240[186] = 0.0;
   out_7952152851251730240[187] = 0.0;
   out_7952152851251730240[188] = 0.0;
   out_7952152851251730240[189] = 0.0;
   out_7952152851251730240[190] = 1.0;
   out_7952152851251730240[191] = 0.0;
   out_7952152851251730240[192] = 0.0;
   out_7952152851251730240[193] = 0.0;
   out_7952152851251730240[194] = 0.0;
   out_7952152851251730240[195] = 0.0;
   out_7952152851251730240[196] = 0.0;
   out_7952152851251730240[197] = 0.0;
   out_7952152851251730240[198] = 0.0;
   out_7952152851251730240[199] = 0.0;
   out_7952152851251730240[200] = 0.0;
   out_7952152851251730240[201] = 0.0;
   out_7952152851251730240[202] = 0.0;
   out_7952152851251730240[203] = 0.0;
   out_7952152851251730240[204] = 0.0;
   out_7952152851251730240[205] = 0.0;
   out_7952152851251730240[206] = 0.0;
   out_7952152851251730240[207] = 0.0;
   out_7952152851251730240[208] = 0.0;
   out_7952152851251730240[209] = 1.0;
   out_7952152851251730240[210] = 0.0;
   out_7952152851251730240[211] = 0.0;
   out_7952152851251730240[212] = 0.0;
   out_7952152851251730240[213] = 0.0;
   out_7952152851251730240[214] = 0.0;
   out_7952152851251730240[215] = 0.0;
   out_7952152851251730240[216] = 0.0;
   out_7952152851251730240[217] = 0.0;
   out_7952152851251730240[218] = 0.0;
   out_7952152851251730240[219] = 0.0;
   out_7952152851251730240[220] = 0.0;
   out_7952152851251730240[221] = 0.0;
   out_7952152851251730240[222] = 0.0;
   out_7952152851251730240[223] = 0.0;
   out_7952152851251730240[224] = 0.0;
   out_7952152851251730240[225] = 0.0;
   out_7952152851251730240[226] = 0.0;
   out_7952152851251730240[227] = 0.0;
   out_7952152851251730240[228] = 1.0;
   out_7952152851251730240[229] = 0.0;
   out_7952152851251730240[230] = 0.0;
   out_7952152851251730240[231] = 0.0;
   out_7952152851251730240[232] = 0.0;
   out_7952152851251730240[233] = 0.0;
   out_7952152851251730240[234] = 0.0;
   out_7952152851251730240[235] = 0.0;
   out_7952152851251730240[236] = 0.0;
   out_7952152851251730240[237] = 0.0;
   out_7952152851251730240[238] = 0.0;
   out_7952152851251730240[239] = 0.0;
   out_7952152851251730240[240] = 0.0;
   out_7952152851251730240[241] = 0.0;
   out_7952152851251730240[242] = 0.0;
   out_7952152851251730240[243] = 0.0;
   out_7952152851251730240[244] = 0.0;
   out_7952152851251730240[245] = 0.0;
   out_7952152851251730240[246] = 0.0;
   out_7952152851251730240[247] = 1.0;
   out_7952152851251730240[248] = 0.0;
   out_7952152851251730240[249] = 0.0;
   out_7952152851251730240[250] = 0.0;
   out_7952152851251730240[251] = 0.0;
   out_7952152851251730240[252] = 0.0;
   out_7952152851251730240[253] = 0.0;
   out_7952152851251730240[254] = 0.0;
   out_7952152851251730240[255] = 0.0;
   out_7952152851251730240[256] = 0.0;
   out_7952152851251730240[257] = 0.0;
   out_7952152851251730240[258] = 0.0;
   out_7952152851251730240[259] = 0.0;
   out_7952152851251730240[260] = 0.0;
   out_7952152851251730240[261] = 0.0;
   out_7952152851251730240[262] = 0.0;
   out_7952152851251730240[263] = 0.0;
   out_7952152851251730240[264] = 0.0;
   out_7952152851251730240[265] = 0.0;
   out_7952152851251730240[266] = 1.0;
   out_7952152851251730240[267] = 0.0;
   out_7952152851251730240[268] = 0.0;
   out_7952152851251730240[269] = 0.0;
   out_7952152851251730240[270] = 0.0;
   out_7952152851251730240[271] = 0.0;
   out_7952152851251730240[272] = 0.0;
   out_7952152851251730240[273] = 0.0;
   out_7952152851251730240[274] = 0.0;
   out_7952152851251730240[275] = 0.0;
   out_7952152851251730240[276] = 0.0;
   out_7952152851251730240[277] = 0.0;
   out_7952152851251730240[278] = 0.0;
   out_7952152851251730240[279] = 0.0;
   out_7952152851251730240[280] = 0.0;
   out_7952152851251730240[281] = 0.0;
   out_7952152851251730240[282] = 0.0;
   out_7952152851251730240[283] = 0.0;
   out_7952152851251730240[284] = 0.0;
   out_7952152851251730240[285] = 1.0;
   out_7952152851251730240[286] = 0.0;
   out_7952152851251730240[287] = 0.0;
   out_7952152851251730240[288] = 0.0;
   out_7952152851251730240[289] = 0.0;
   out_7952152851251730240[290] = 0.0;
   out_7952152851251730240[291] = 0.0;
   out_7952152851251730240[292] = 0.0;
   out_7952152851251730240[293] = 0.0;
   out_7952152851251730240[294] = 0.0;
   out_7952152851251730240[295] = 0.0;
   out_7952152851251730240[296] = 0.0;
   out_7952152851251730240[297] = 0.0;
   out_7952152851251730240[298] = 0.0;
   out_7952152851251730240[299] = 0.0;
   out_7952152851251730240[300] = 0.0;
   out_7952152851251730240[301] = 0.0;
   out_7952152851251730240[302] = 0.0;
   out_7952152851251730240[303] = 0.0;
   out_7952152851251730240[304] = 1.0;
   out_7952152851251730240[305] = 0.0;
   out_7952152851251730240[306] = 0.0;
   out_7952152851251730240[307] = 0.0;
   out_7952152851251730240[308] = 0.0;
   out_7952152851251730240[309] = 0.0;
   out_7952152851251730240[310] = 0.0;
   out_7952152851251730240[311] = 0.0;
   out_7952152851251730240[312] = 0.0;
   out_7952152851251730240[313] = 0.0;
   out_7952152851251730240[314] = 0.0;
   out_7952152851251730240[315] = 0.0;
   out_7952152851251730240[316] = 0.0;
   out_7952152851251730240[317] = 0.0;
   out_7952152851251730240[318] = 0.0;
   out_7952152851251730240[319] = 0.0;
   out_7952152851251730240[320] = 0.0;
   out_7952152851251730240[321] = 0.0;
   out_7952152851251730240[322] = 0.0;
   out_7952152851251730240[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7552017383192428802) {
   out_7552017383192428802[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7552017383192428802[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7552017383192428802[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7552017383192428802[3] = dt*state[12] + state[3];
   out_7552017383192428802[4] = dt*state[13] + state[4];
   out_7552017383192428802[5] = dt*state[14] + state[5];
   out_7552017383192428802[6] = state[6];
   out_7552017383192428802[7] = state[7];
   out_7552017383192428802[8] = state[8];
   out_7552017383192428802[9] = state[9];
   out_7552017383192428802[10] = state[10];
   out_7552017383192428802[11] = state[11];
   out_7552017383192428802[12] = state[12];
   out_7552017383192428802[13] = state[13];
   out_7552017383192428802[14] = state[14];
   out_7552017383192428802[15] = state[15];
   out_7552017383192428802[16] = state[16];
   out_7552017383192428802[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6783292645299155505) {
   out_6783292645299155505[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6783292645299155505[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6783292645299155505[2] = 0;
   out_6783292645299155505[3] = 0;
   out_6783292645299155505[4] = 0;
   out_6783292645299155505[5] = 0;
   out_6783292645299155505[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6783292645299155505[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6783292645299155505[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6783292645299155505[9] = 0;
   out_6783292645299155505[10] = 0;
   out_6783292645299155505[11] = 0;
   out_6783292645299155505[12] = 0;
   out_6783292645299155505[13] = 0;
   out_6783292645299155505[14] = 0;
   out_6783292645299155505[15] = 0;
   out_6783292645299155505[16] = 0;
   out_6783292645299155505[17] = 0;
   out_6783292645299155505[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6783292645299155505[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6783292645299155505[20] = 0;
   out_6783292645299155505[21] = 0;
   out_6783292645299155505[22] = 0;
   out_6783292645299155505[23] = 0;
   out_6783292645299155505[24] = 0;
   out_6783292645299155505[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6783292645299155505[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6783292645299155505[27] = 0;
   out_6783292645299155505[28] = 0;
   out_6783292645299155505[29] = 0;
   out_6783292645299155505[30] = 0;
   out_6783292645299155505[31] = 0;
   out_6783292645299155505[32] = 0;
   out_6783292645299155505[33] = 0;
   out_6783292645299155505[34] = 0;
   out_6783292645299155505[35] = 0;
   out_6783292645299155505[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6783292645299155505[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6783292645299155505[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6783292645299155505[39] = 0;
   out_6783292645299155505[40] = 0;
   out_6783292645299155505[41] = 0;
   out_6783292645299155505[42] = 0;
   out_6783292645299155505[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6783292645299155505[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6783292645299155505[45] = 0;
   out_6783292645299155505[46] = 0;
   out_6783292645299155505[47] = 0;
   out_6783292645299155505[48] = 0;
   out_6783292645299155505[49] = 0;
   out_6783292645299155505[50] = 0;
   out_6783292645299155505[51] = 0;
   out_6783292645299155505[52] = 0;
   out_6783292645299155505[53] = 0;
   out_6783292645299155505[54] = 0;
   out_6783292645299155505[55] = 0;
   out_6783292645299155505[56] = 0;
   out_6783292645299155505[57] = 1;
   out_6783292645299155505[58] = 0;
   out_6783292645299155505[59] = 0;
   out_6783292645299155505[60] = 0;
   out_6783292645299155505[61] = 0;
   out_6783292645299155505[62] = 0;
   out_6783292645299155505[63] = 0;
   out_6783292645299155505[64] = 0;
   out_6783292645299155505[65] = 0;
   out_6783292645299155505[66] = dt;
   out_6783292645299155505[67] = 0;
   out_6783292645299155505[68] = 0;
   out_6783292645299155505[69] = 0;
   out_6783292645299155505[70] = 0;
   out_6783292645299155505[71] = 0;
   out_6783292645299155505[72] = 0;
   out_6783292645299155505[73] = 0;
   out_6783292645299155505[74] = 0;
   out_6783292645299155505[75] = 0;
   out_6783292645299155505[76] = 1;
   out_6783292645299155505[77] = 0;
   out_6783292645299155505[78] = 0;
   out_6783292645299155505[79] = 0;
   out_6783292645299155505[80] = 0;
   out_6783292645299155505[81] = 0;
   out_6783292645299155505[82] = 0;
   out_6783292645299155505[83] = 0;
   out_6783292645299155505[84] = 0;
   out_6783292645299155505[85] = dt;
   out_6783292645299155505[86] = 0;
   out_6783292645299155505[87] = 0;
   out_6783292645299155505[88] = 0;
   out_6783292645299155505[89] = 0;
   out_6783292645299155505[90] = 0;
   out_6783292645299155505[91] = 0;
   out_6783292645299155505[92] = 0;
   out_6783292645299155505[93] = 0;
   out_6783292645299155505[94] = 0;
   out_6783292645299155505[95] = 1;
   out_6783292645299155505[96] = 0;
   out_6783292645299155505[97] = 0;
   out_6783292645299155505[98] = 0;
   out_6783292645299155505[99] = 0;
   out_6783292645299155505[100] = 0;
   out_6783292645299155505[101] = 0;
   out_6783292645299155505[102] = 0;
   out_6783292645299155505[103] = 0;
   out_6783292645299155505[104] = dt;
   out_6783292645299155505[105] = 0;
   out_6783292645299155505[106] = 0;
   out_6783292645299155505[107] = 0;
   out_6783292645299155505[108] = 0;
   out_6783292645299155505[109] = 0;
   out_6783292645299155505[110] = 0;
   out_6783292645299155505[111] = 0;
   out_6783292645299155505[112] = 0;
   out_6783292645299155505[113] = 0;
   out_6783292645299155505[114] = 1;
   out_6783292645299155505[115] = 0;
   out_6783292645299155505[116] = 0;
   out_6783292645299155505[117] = 0;
   out_6783292645299155505[118] = 0;
   out_6783292645299155505[119] = 0;
   out_6783292645299155505[120] = 0;
   out_6783292645299155505[121] = 0;
   out_6783292645299155505[122] = 0;
   out_6783292645299155505[123] = 0;
   out_6783292645299155505[124] = 0;
   out_6783292645299155505[125] = 0;
   out_6783292645299155505[126] = 0;
   out_6783292645299155505[127] = 0;
   out_6783292645299155505[128] = 0;
   out_6783292645299155505[129] = 0;
   out_6783292645299155505[130] = 0;
   out_6783292645299155505[131] = 0;
   out_6783292645299155505[132] = 0;
   out_6783292645299155505[133] = 1;
   out_6783292645299155505[134] = 0;
   out_6783292645299155505[135] = 0;
   out_6783292645299155505[136] = 0;
   out_6783292645299155505[137] = 0;
   out_6783292645299155505[138] = 0;
   out_6783292645299155505[139] = 0;
   out_6783292645299155505[140] = 0;
   out_6783292645299155505[141] = 0;
   out_6783292645299155505[142] = 0;
   out_6783292645299155505[143] = 0;
   out_6783292645299155505[144] = 0;
   out_6783292645299155505[145] = 0;
   out_6783292645299155505[146] = 0;
   out_6783292645299155505[147] = 0;
   out_6783292645299155505[148] = 0;
   out_6783292645299155505[149] = 0;
   out_6783292645299155505[150] = 0;
   out_6783292645299155505[151] = 0;
   out_6783292645299155505[152] = 1;
   out_6783292645299155505[153] = 0;
   out_6783292645299155505[154] = 0;
   out_6783292645299155505[155] = 0;
   out_6783292645299155505[156] = 0;
   out_6783292645299155505[157] = 0;
   out_6783292645299155505[158] = 0;
   out_6783292645299155505[159] = 0;
   out_6783292645299155505[160] = 0;
   out_6783292645299155505[161] = 0;
   out_6783292645299155505[162] = 0;
   out_6783292645299155505[163] = 0;
   out_6783292645299155505[164] = 0;
   out_6783292645299155505[165] = 0;
   out_6783292645299155505[166] = 0;
   out_6783292645299155505[167] = 0;
   out_6783292645299155505[168] = 0;
   out_6783292645299155505[169] = 0;
   out_6783292645299155505[170] = 0;
   out_6783292645299155505[171] = 1;
   out_6783292645299155505[172] = 0;
   out_6783292645299155505[173] = 0;
   out_6783292645299155505[174] = 0;
   out_6783292645299155505[175] = 0;
   out_6783292645299155505[176] = 0;
   out_6783292645299155505[177] = 0;
   out_6783292645299155505[178] = 0;
   out_6783292645299155505[179] = 0;
   out_6783292645299155505[180] = 0;
   out_6783292645299155505[181] = 0;
   out_6783292645299155505[182] = 0;
   out_6783292645299155505[183] = 0;
   out_6783292645299155505[184] = 0;
   out_6783292645299155505[185] = 0;
   out_6783292645299155505[186] = 0;
   out_6783292645299155505[187] = 0;
   out_6783292645299155505[188] = 0;
   out_6783292645299155505[189] = 0;
   out_6783292645299155505[190] = 1;
   out_6783292645299155505[191] = 0;
   out_6783292645299155505[192] = 0;
   out_6783292645299155505[193] = 0;
   out_6783292645299155505[194] = 0;
   out_6783292645299155505[195] = 0;
   out_6783292645299155505[196] = 0;
   out_6783292645299155505[197] = 0;
   out_6783292645299155505[198] = 0;
   out_6783292645299155505[199] = 0;
   out_6783292645299155505[200] = 0;
   out_6783292645299155505[201] = 0;
   out_6783292645299155505[202] = 0;
   out_6783292645299155505[203] = 0;
   out_6783292645299155505[204] = 0;
   out_6783292645299155505[205] = 0;
   out_6783292645299155505[206] = 0;
   out_6783292645299155505[207] = 0;
   out_6783292645299155505[208] = 0;
   out_6783292645299155505[209] = 1;
   out_6783292645299155505[210] = 0;
   out_6783292645299155505[211] = 0;
   out_6783292645299155505[212] = 0;
   out_6783292645299155505[213] = 0;
   out_6783292645299155505[214] = 0;
   out_6783292645299155505[215] = 0;
   out_6783292645299155505[216] = 0;
   out_6783292645299155505[217] = 0;
   out_6783292645299155505[218] = 0;
   out_6783292645299155505[219] = 0;
   out_6783292645299155505[220] = 0;
   out_6783292645299155505[221] = 0;
   out_6783292645299155505[222] = 0;
   out_6783292645299155505[223] = 0;
   out_6783292645299155505[224] = 0;
   out_6783292645299155505[225] = 0;
   out_6783292645299155505[226] = 0;
   out_6783292645299155505[227] = 0;
   out_6783292645299155505[228] = 1;
   out_6783292645299155505[229] = 0;
   out_6783292645299155505[230] = 0;
   out_6783292645299155505[231] = 0;
   out_6783292645299155505[232] = 0;
   out_6783292645299155505[233] = 0;
   out_6783292645299155505[234] = 0;
   out_6783292645299155505[235] = 0;
   out_6783292645299155505[236] = 0;
   out_6783292645299155505[237] = 0;
   out_6783292645299155505[238] = 0;
   out_6783292645299155505[239] = 0;
   out_6783292645299155505[240] = 0;
   out_6783292645299155505[241] = 0;
   out_6783292645299155505[242] = 0;
   out_6783292645299155505[243] = 0;
   out_6783292645299155505[244] = 0;
   out_6783292645299155505[245] = 0;
   out_6783292645299155505[246] = 0;
   out_6783292645299155505[247] = 1;
   out_6783292645299155505[248] = 0;
   out_6783292645299155505[249] = 0;
   out_6783292645299155505[250] = 0;
   out_6783292645299155505[251] = 0;
   out_6783292645299155505[252] = 0;
   out_6783292645299155505[253] = 0;
   out_6783292645299155505[254] = 0;
   out_6783292645299155505[255] = 0;
   out_6783292645299155505[256] = 0;
   out_6783292645299155505[257] = 0;
   out_6783292645299155505[258] = 0;
   out_6783292645299155505[259] = 0;
   out_6783292645299155505[260] = 0;
   out_6783292645299155505[261] = 0;
   out_6783292645299155505[262] = 0;
   out_6783292645299155505[263] = 0;
   out_6783292645299155505[264] = 0;
   out_6783292645299155505[265] = 0;
   out_6783292645299155505[266] = 1;
   out_6783292645299155505[267] = 0;
   out_6783292645299155505[268] = 0;
   out_6783292645299155505[269] = 0;
   out_6783292645299155505[270] = 0;
   out_6783292645299155505[271] = 0;
   out_6783292645299155505[272] = 0;
   out_6783292645299155505[273] = 0;
   out_6783292645299155505[274] = 0;
   out_6783292645299155505[275] = 0;
   out_6783292645299155505[276] = 0;
   out_6783292645299155505[277] = 0;
   out_6783292645299155505[278] = 0;
   out_6783292645299155505[279] = 0;
   out_6783292645299155505[280] = 0;
   out_6783292645299155505[281] = 0;
   out_6783292645299155505[282] = 0;
   out_6783292645299155505[283] = 0;
   out_6783292645299155505[284] = 0;
   out_6783292645299155505[285] = 1;
   out_6783292645299155505[286] = 0;
   out_6783292645299155505[287] = 0;
   out_6783292645299155505[288] = 0;
   out_6783292645299155505[289] = 0;
   out_6783292645299155505[290] = 0;
   out_6783292645299155505[291] = 0;
   out_6783292645299155505[292] = 0;
   out_6783292645299155505[293] = 0;
   out_6783292645299155505[294] = 0;
   out_6783292645299155505[295] = 0;
   out_6783292645299155505[296] = 0;
   out_6783292645299155505[297] = 0;
   out_6783292645299155505[298] = 0;
   out_6783292645299155505[299] = 0;
   out_6783292645299155505[300] = 0;
   out_6783292645299155505[301] = 0;
   out_6783292645299155505[302] = 0;
   out_6783292645299155505[303] = 0;
   out_6783292645299155505[304] = 1;
   out_6783292645299155505[305] = 0;
   out_6783292645299155505[306] = 0;
   out_6783292645299155505[307] = 0;
   out_6783292645299155505[308] = 0;
   out_6783292645299155505[309] = 0;
   out_6783292645299155505[310] = 0;
   out_6783292645299155505[311] = 0;
   out_6783292645299155505[312] = 0;
   out_6783292645299155505[313] = 0;
   out_6783292645299155505[314] = 0;
   out_6783292645299155505[315] = 0;
   out_6783292645299155505[316] = 0;
   out_6783292645299155505[317] = 0;
   out_6783292645299155505[318] = 0;
   out_6783292645299155505[319] = 0;
   out_6783292645299155505[320] = 0;
   out_6783292645299155505[321] = 0;
   out_6783292645299155505[322] = 0;
   out_6783292645299155505[323] = 1;
}
void h_4(double *state, double *unused, double *out_3201313637048019244) {
   out_3201313637048019244[0] = state[6] + state[9];
   out_3201313637048019244[1] = state[7] + state[10];
   out_3201313637048019244[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_7197991849197017633) {
   out_7197991849197017633[0] = 0;
   out_7197991849197017633[1] = 0;
   out_7197991849197017633[2] = 0;
   out_7197991849197017633[3] = 0;
   out_7197991849197017633[4] = 0;
   out_7197991849197017633[5] = 0;
   out_7197991849197017633[6] = 1;
   out_7197991849197017633[7] = 0;
   out_7197991849197017633[8] = 0;
   out_7197991849197017633[9] = 1;
   out_7197991849197017633[10] = 0;
   out_7197991849197017633[11] = 0;
   out_7197991849197017633[12] = 0;
   out_7197991849197017633[13] = 0;
   out_7197991849197017633[14] = 0;
   out_7197991849197017633[15] = 0;
   out_7197991849197017633[16] = 0;
   out_7197991849197017633[17] = 0;
   out_7197991849197017633[18] = 0;
   out_7197991849197017633[19] = 0;
   out_7197991849197017633[20] = 0;
   out_7197991849197017633[21] = 0;
   out_7197991849197017633[22] = 0;
   out_7197991849197017633[23] = 0;
   out_7197991849197017633[24] = 0;
   out_7197991849197017633[25] = 1;
   out_7197991849197017633[26] = 0;
   out_7197991849197017633[27] = 0;
   out_7197991849197017633[28] = 1;
   out_7197991849197017633[29] = 0;
   out_7197991849197017633[30] = 0;
   out_7197991849197017633[31] = 0;
   out_7197991849197017633[32] = 0;
   out_7197991849197017633[33] = 0;
   out_7197991849197017633[34] = 0;
   out_7197991849197017633[35] = 0;
   out_7197991849197017633[36] = 0;
   out_7197991849197017633[37] = 0;
   out_7197991849197017633[38] = 0;
   out_7197991849197017633[39] = 0;
   out_7197991849197017633[40] = 0;
   out_7197991849197017633[41] = 0;
   out_7197991849197017633[42] = 0;
   out_7197991849197017633[43] = 0;
   out_7197991849197017633[44] = 1;
   out_7197991849197017633[45] = 0;
   out_7197991849197017633[46] = 0;
   out_7197991849197017633[47] = 1;
   out_7197991849197017633[48] = 0;
   out_7197991849197017633[49] = 0;
   out_7197991849197017633[50] = 0;
   out_7197991849197017633[51] = 0;
   out_7197991849197017633[52] = 0;
   out_7197991849197017633[53] = 0;
}
void h_10(double *state, double *unused, double *out_7841290235876673145) {
   out_7841290235876673145[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7841290235876673145[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7841290235876673145[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_4457773099460457900) {
   out_4457773099460457900[0] = 0;
   out_4457773099460457900[1] = 9.8100000000000005*cos(state[1]);
   out_4457773099460457900[2] = 0;
   out_4457773099460457900[3] = 0;
   out_4457773099460457900[4] = -state[8];
   out_4457773099460457900[5] = state[7];
   out_4457773099460457900[6] = 0;
   out_4457773099460457900[7] = state[5];
   out_4457773099460457900[8] = -state[4];
   out_4457773099460457900[9] = 0;
   out_4457773099460457900[10] = 0;
   out_4457773099460457900[11] = 0;
   out_4457773099460457900[12] = 1;
   out_4457773099460457900[13] = 0;
   out_4457773099460457900[14] = 0;
   out_4457773099460457900[15] = 1;
   out_4457773099460457900[16] = 0;
   out_4457773099460457900[17] = 0;
   out_4457773099460457900[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_4457773099460457900[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_4457773099460457900[20] = 0;
   out_4457773099460457900[21] = state[8];
   out_4457773099460457900[22] = 0;
   out_4457773099460457900[23] = -state[6];
   out_4457773099460457900[24] = -state[5];
   out_4457773099460457900[25] = 0;
   out_4457773099460457900[26] = state[3];
   out_4457773099460457900[27] = 0;
   out_4457773099460457900[28] = 0;
   out_4457773099460457900[29] = 0;
   out_4457773099460457900[30] = 0;
   out_4457773099460457900[31] = 1;
   out_4457773099460457900[32] = 0;
   out_4457773099460457900[33] = 0;
   out_4457773099460457900[34] = 1;
   out_4457773099460457900[35] = 0;
   out_4457773099460457900[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_4457773099460457900[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_4457773099460457900[38] = 0;
   out_4457773099460457900[39] = -state[7];
   out_4457773099460457900[40] = state[6];
   out_4457773099460457900[41] = 0;
   out_4457773099460457900[42] = state[4];
   out_4457773099460457900[43] = -state[3];
   out_4457773099460457900[44] = 0;
   out_4457773099460457900[45] = 0;
   out_4457773099460457900[46] = 0;
   out_4457773099460457900[47] = 0;
   out_4457773099460457900[48] = 0;
   out_4457773099460457900[49] = 0;
   out_4457773099460457900[50] = 1;
   out_4457773099460457900[51] = 0;
   out_4457773099460457900[52] = 0;
   out_4457773099460457900[53] = 1;
}
void h_13(double *state, double *unused, double *out_6486454295362862882) {
   out_6486454295362862882[0] = state[3];
   out_6486454295362862882[1] = state[4];
   out_6486454295362862882[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3985718023864684832) {
   out_3985718023864684832[0] = 0;
   out_3985718023864684832[1] = 0;
   out_3985718023864684832[2] = 0;
   out_3985718023864684832[3] = 1;
   out_3985718023864684832[4] = 0;
   out_3985718023864684832[5] = 0;
   out_3985718023864684832[6] = 0;
   out_3985718023864684832[7] = 0;
   out_3985718023864684832[8] = 0;
   out_3985718023864684832[9] = 0;
   out_3985718023864684832[10] = 0;
   out_3985718023864684832[11] = 0;
   out_3985718023864684832[12] = 0;
   out_3985718023864684832[13] = 0;
   out_3985718023864684832[14] = 0;
   out_3985718023864684832[15] = 0;
   out_3985718023864684832[16] = 0;
   out_3985718023864684832[17] = 0;
   out_3985718023864684832[18] = 0;
   out_3985718023864684832[19] = 0;
   out_3985718023864684832[20] = 0;
   out_3985718023864684832[21] = 0;
   out_3985718023864684832[22] = 1;
   out_3985718023864684832[23] = 0;
   out_3985718023864684832[24] = 0;
   out_3985718023864684832[25] = 0;
   out_3985718023864684832[26] = 0;
   out_3985718023864684832[27] = 0;
   out_3985718023864684832[28] = 0;
   out_3985718023864684832[29] = 0;
   out_3985718023864684832[30] = 0;
   out_3985718023864684832[31] = 0;
   out_3985718023864684832[32] = 0;
   out_3985718023864684832[33] = 0;
   out_3985718023864684832[34] = 0;
   out_3985718023864684832[35] = 0;
   out_3985718023864684832[36] = 0;
   out_3985718023864684832[37] = 0;
   out_3985718023864684832[38] = 0;
   out_3985718023864684832[39] = 0;
   out_3985718023864684832[40] = 0;
   out_3985718023864684832[41] = 1;
   out_3985718023864684832[42] = 0;
   out_3985718023864684832[43] = 0;
   out_3985718023864684832[44] = 0;
   out_3985718023864684832[45] = 0;
   out_3985718023864684832[46] = 0;
   out_3985718023864684832[47] = 0;
   out_3985718023864684832[48] = 0;
   out_3985718023864684832[49] = 0;
   out_3985718023864684832[50] = 0;
   out_3985718023864684832[51] = 0;
   out_3985718023864684832[52] = 0;
   out_3985718023864684832[53] = 0;
}
void h_14(double *state, double *unused, double *out_6937527919275139740) {
   out_6937527919275139740[0] = state[6];
   out_6937527919275139740[1] = state[7];
   out_6937527919275139740[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3234750992857533104) {
   out_3234750992857533104[0] = 0;
   out_3234750992857533104[1] = 0;
   out_3234750992857533104[2] = 0;
   out_3234750992857533104[3] = 0;
   out_3234750992857533104[4] = 0;
   out_3234750992857533104[5] = 0;
   out_3234750992857533104[6] = 1;
   out_3234750992857533104[7] = 0;
   out_3234750992857533104[8] = 0;
   out_3234750992857533104[9] = 0;
   out_3234750992857533104[10] = 0;
   out_3234750992857533104[11] = 0;
   out_3234750992857533104[12] = 0;
   out_3234750992857533104[13] = 0;
   out_3234750992857533104[14] = 0;
   out_3234750992857533104[15] = 0;
   out_3234750992857533104[16] = 0;
   out_3234750992857533104[17] = 0;
   out_3234750992857533104[18] = 0;
   out_3234750992857533104[19] = 0;
   out_3234750992857533104[20] = 0;
   out_3234750992857533104[21] = 0;
   out_3234750992857533104[22] = 0;
   out_3234750992857533104[23] = 0;
   out_3234750992857533104[24] = 0;
   out_3234750992857533104[25] = 1;
   out_3234750992857533104[26] = 0;
   out_3234750992857533104[27] = 0;
   out_3234750992857533104[28] = 0;
   out_3234750992857533104[29] = 0;
   out_3234750992857533104[30] = 0;
   out_3234750992857533104[31] = 0;
   out_3234750992857533104[32] = 0;
   out_3234750992857533104[33] = 0;
   out_3234750992857533104[34] = 0;
   out_3234750992857533104[35] = 0;
   out_3234750992857533104[36] = 0;
   out_3234750992857533104[37] = 0;
   out_3234750992857533104[38] = 0;
   out_3234750992857533104[39] = 0;
   out_3234750992857533104[40] = 0;
   out_3234750992857533104[41] = 0;
   out_3234750992857533104[42] = 0;
   out_3234750992857533104[43] = 0;
   out_3234750992857533104[44] = 1;
   out_3234750992857533104[45] = 0;
   out_3234750992857533104[46] = 0;
   out_3234750992857533104[47] = 0;
   out_3234750992857533104[48] = 0;
   out_3234750992857533104[49] = 0;
   out_3234750992857533104[50] = 0;
   out_3234750992857533104[51] = 0;
   out_3234750992857533104[52] = 0;
   out_3234750992857533104[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_5353336122144560205) {
  err_fun(nom_x, delta_x, out_5353336122144560205);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4798572186740292528) {
  inv_err_fun(nom_x, true_x, out_4798572186740292528);
}
void pose_H_mod_fun(double *state, double *out_7952152851251730240) {
  H_mod_fun(state, out_7952152851251730240);
}
void pose_f_fun(double *state, double dt, double *out_7552017383192428802) {
  f_fun(state,  dt, out_7552017383192428802);
}
void pose_F_fun(double *state, double dt, double *out_6783292645299155505) {
  F_fun(state,  dt, out_6783292645299155505);
}
void pose_h_4(double *state, double *unused, double *out_3201313637048019244) {
  h_4(state, unused, out_3201313637048019244);
}
void pose_H_4(double *state, double *unused, double *out_7197991849197017633) {
  H_4(state, unused, out_7197991849197017633);
}
void pose_h_10(double *state, double *unused, double *out_7841290235876673145) {
  h_10(state, unused, out_7841290235876673145);
}
void pose_H_10(double *state, double *unused, double *out_4457773099460457900) {
  H_10(state, unused, out_4457773099460457900);
}
void pose_h_13(double *state, double *unused, double *out_6486454295362862882) {
  h_13(state, unused, out_6486454295362862882);
}
void pose_H_13(double *state, double *unused, double *out_3985718023864684832) {
  H_13(state, unused, out_3985718023864684832);
}
void pose_h_14(double *state, double *unused, double *out_6937527919275139740) {
  h_14(state, unused, out_6937527919275139740);
}
void pose_H_14(double *state, double *unused, double *out_3234750992857533104) {
  H_14(state, unused, out_3234750992857533104);
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
