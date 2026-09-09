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
void err_fun(double *nom_x, double *delta_x, double *out_7151556355931759320) {
   out_7151556355931759320[0] = delta_x[0] + nom_x[0];
   out_7151556355931759320[1] = delta_x[1] + nom_x[1];
   out_7151556355931759320[2] = delta_x[2] + nom_x[2];
   out_7151556355931759320[3] = delta_x[3] + nom_x[3];
   out_7151556355931759320[4] = delta_x[4] + nom_x[4];
   out_7151556355931759320[5] = delta_x[5] + nom_x[5];
   out_7151556355931759320[6] = delta_x[6] + nom_x[6];
   out_7151556355931759320[7] = delta_x[7] + nom_x[7];
   out_7151556355931759320[8] = delta_x[8] + nom_x[8];
   out_7151556355931759320[9] = delta_x[9] + nom_x[9];
   out_7151556355931759320[10] = delta_x[10] + nom_x[10];
   out_7151556355931759320[11] = delta_x[11] + nom_x[11];
   out_7151556355931759320[12] = delta_x[12] + nom_x[12];
   out_7151556355931759320[13] = delta_x[13] + nom_x[13];
   out_7151556355931759320[14] = delta_x[14] + nom_x[14];
   out_7151556355931759320[15] = delta_x[15] + nom_x[15];
   out_7151556355931759320[16] = delta_x[16] + nom_x[16];
   out_7151556355931759320[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_659960172465309786) {
   out_659960172465309786[0] = -nom_x[0] + true_x[0];
   out_659960172465309786[1] = -nom_x[1] + true_x[1];
   out_659960172465309786[2] = -nom_x[2] + true_x[2];
   out_659960172465309786[3] = -nom_x[3] + true_x[3];
   out_659960172465309786[4] = -nom_x[4] + true_x[4];
   out_659960172465309786[5] = -nom_x[5] + true_x[5];
   out_659960172465309786[6] = -nom_x[6] + true_x[6];
   out_659960172465309786[7] = -nom_x[7] + true_x[7];
   out_659960172465309786[8] = -nom_x[8] + true_x[8];
   out_659960172465309786[9] = -nom_x[9] + true_x[9];
   out_659960172465309786[10] = -nom_x[10] + true_x[10];
   out_659960172465309786[11] = -nom_x[11] + true_x[11];
   out_659960172465309786[12] = -nom_x[12] + true_x[12];
   out_659960172465309786[13] = -nom_x[13] + true_x[13];
   out_659960172465309786[14] = -nom_x[14] + true_x[14];
   out_659960172465309786[15] = -nom_x[15] + true_x[15];
   out_659960172465309786[16] = -nom_x[16] + true_x[16];
   out_659960172465309786[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3449117321369348042) {
   out_3449117321369348042[0] = 1.0;
   out_3449117321369348042[1] = 0.0;
   out_3449117321369348042[2] = 0.0;
   out_3449117321369348042[3] = 0.0;
   out_3449117321369348042[4] = 0.0;
   out_3449117321369348042[5] = 0.0;
   out_3449117321369348042[6] = 0.0;
   out_3449117321369348042[7] = 0.0;
   out_3449117321369348042[8] = 0.0;
   out_3449117321369348042[9] = 0.0;
   out_3449117321369348042[10] = 0.0;
   out_3449117321369348042[11] = 0.0;
   out_3449117321369348042[12] = 0.0;
   out_3449117321369348042[13] = 0.0;
   out_3449117321369348042[14] = 0.0;
   out_3449117321369348042[15] = 0.0;
   out_3449117321369348042[16] = 0.0;
   out_3449117321369348042[17] = 0.0;
   out_3449117321369348042[18] = 0.0;
   out_3449117321369348042[19] = 1.0;
   out_3449117321369348042[20] = 0.0;
   out_3449117321369348042[21] = 0.0;
   out_3449117321369348042[22] = 0.0;
   out_3449117321369348042[23] = 0.0;
   out_3449117321369348042[24] = 0.0;
   out_3449117321369348042[25] = 0.0;
   out_3449117321369348042[26] = 0.0;
   out_3449117321369348042[27] = 0.0;
   out_3449117321369348042[28] = 0.0;
   out_3449117321369348042[29] = 0.0;
   out_3449117321369348042[30] = 0.0;
   out_3449117321369348042[31] = 0.0;
   out_3449117321369348042[32] = 0.0;
   out_3449117321369348042[33] = 0.0;
   out_3449117321369348042[34] = 0.0;
   out_3449117321369348042[35] = 0.0;
   out_3449117321369348042[36] = 0.0;
   out_3449117321369348042[37] = 0.0;
   out_3449117321369348042[38] = 1.0;
   out_3449117321369348042[39] = 0.0;
   out_3449117321369348042[40] = 0.0;
   out_3449117321369348042[41] = 0.0;
   out_3449117321369348042[42] = 0.0;
   out_3449117321369348042[43] = 0.0;
   out_3449117321369348042[44] = 0.0;
   out_3449117321369348042[45] = 0.0;
   out_3449117321369348042[46] = 0.0;
   out_3449117321369348042[47] = 0.0;
   out_3449117321369348042[48] = 0.0;
   out_3449117321369348042[49] = 0.0;
   out_3449117321369348042[50] = 0.0;
   out_3449117321369348042[51] = 0.0;
   out_3449117321369348042[52] = 0.0;
   out_3449117321369348042[53] = 0.0;
   out_3449117321369348042[54] = 0.0;
   out_3449117321369348042[55] = 0.0;
   out_3449117321369348042[56] = 0.0;
   out_3449117321369348042[57] = 1.0;
   out_3449117321369348042[58] = 0.0;
   out_3449117321369348042[59] = 0.0;
   out_3449117321369348042[60] = 0.0;
   out_3449117321369348042[61] = 0.0;
   out_3449117321369348042[62] = 0.0;
   out_3449117321369348042[63] = 0.0;
   out_3449117321369348042[64] = 0.0;
   out_3449117321369348042[65] = 0.0;
   out_3449117321369348042[66] = 0.0;
   out_3449117321369348042[67] = 0.0;
   out_3449117321369348042[68] = 0.0;
   out_3449117321369348042[69] = 0.0;
   out_3449117321369348042[70] = 0.0;
   out_3449117321369348042[71] = 0.0;
   out_3449117321369348042[72] = 0.0;
   out_3449117321369348042[73] = 0.0;
   out_3449117321369348042[74] = 0.0;
   out_3449117321369348042[75] = 0.0;
   out_3449117321369348042[76] = 1.0;
   out_3449117321369348042[77] = 0.0;
   out_3449117321369348042[78] = 0.0;
   out_3449117321369348042[79] = 0.0;
   out_3449117321369348042[80] = 0.0;
   out_3449117321369348042[81] = 0.0;
   out_3449117321369348042[82] = 0.0;
   out_3449117321369348042[83] = 0.0;
   out_3449117321369348042[84] = 0.0;
   out_3449117321369348042[85] = 0.0;
   out_3449117321369348042[86] = 0.0;
   out_3449117321369348042[87] = 0.0;
   out_3449117321369348042[88] = 0.0;
   out_3449117321369348042[89] = 0.0;
   out_3449117321369348042[90] = 0.0;
   out_3449117321369348042[91] = 0.0;
   out_3449117321369348042[92] = 0.0;
   out_3449117321369348042[93] = 0.0;
   out_3449117321369348042[94] = 0.0;
   out_3449117321369348042[95] = 1.0;
   out_3449117321369348042[96] = 0.0;
   out_3449117321369348042[97] = 0.0;
   out_3449117321369348042[98] = 0.0;
   out_3449117321369348042[99] = 0.0;
   out_3449117321369348042[100] = 0.0;
   out_3449117321369348042[101] = 0.0;
   out_3449117321369348042[102] = 0.0;
   out_3449117321369348042[103] = 0.0;
   out_3449117321369348042[104] = 0.0;
   out_3449117321369348042[105] = 0.0;
   out_3449117321369348042[106] = 0.0;
   out_3449117321369348042[107] = 0.0;
   out_3449117321369348042[108] = 0.0;
   out_3449117321369348042[109] = 0.0;
   out_3449117321369348042[110] = 0.0;
   out_3449117321369348042[111] = 0.0;
   out_3449117321369348042[112] = 0.0;
   out_3449117321369348042[113] = 0.0;
   out_3449117321369348042[114] = 1.0;
   out_3449117321369348042[115] = 0.0;
   out_3449117321369348042[116] = 0.0;
   out_3449117321369348042[117] = 0.0;
   out_3449117321369348042[118] = 0.0;
   out_3449117321369348042[119] = 0.0;
   out_3449117321369348042[120] = 0.0;
   out_3449117321369348042[121] = 0.0;
   out_3449117321369348042[122] = 0.0;
   out_3449117321369348042[123] = 0.0;
   out_3449117321369348042[124] = 0.0;
   out_3449117321369348042[125] = 0.0;
   out_3449117321369348042[126] = 0.0;
   out_3449117321369348042[127] = 0.0;
   out_3449117321369348042[128] = 0.0;
   out_3449117321369348042[129] = 0.0;
   out_3449117321369348042[130] = 0.0;
   out_3449117321369348042[131] = 0.0;
   out_3449117321369348042[132] = 0.0;
   out_3449117321369348042[133] = 1.0;
   out_3449117321369348042[134] = 0.0;
   out_3449117321369348042[135] = 0.0;
   out_3449117321369348042[136] = 0.0;
   out_3449117321369348042[137] = 0.0;
   out_3449117321369348042[138] = 0.0;
   out_3449117321369348042[139] = 0.0;
   out_3449117321369348042[140] = 0.0;
   out_3449117321369348042[141] = 0.0;
   out_3449117321369348042[142] = 0.0;
   out_3449117321369348042[143] = 0.0;
   out_3449117321369348042[144] = 0.0;
   out_3449117321369348042[145] = 0.0;
   out_3449117321369348042[146] = 0.0;
   out_3449117321369348042[147] = 0.0;
   out_3449117321369348042[148] = 0.0;
   out_3449117321369348042[149] = 0.0;
   out_3449117321369348042[150] = 0.0;
   out_3449117321369348042[151] = 0.0;
   out_3449117321369348042[152] = 1.0;
   out_3449117321369348042[153] = 0.0;
   out_3449117321369348042[154] = 0.0;
   out_3449117321369348042[155] = 0.0;
   out_3449117321369348042[156] = 0.0;
   out_3449117321369348042[157] = 0.0;
   out_3449117321369348042[158] = 0.0;
   out_3449117321369348042[159] = 0.0;
   out_3449117321369348042[160] = 0.0;
   out_3449117321369348042[161] = 0.0;
   out_3449117321369348042[162] = 0.0;
   out_3449117321369348042[163] = 0.0;
   out_3449117321369348042[164] = 0.0;
   out_3449117321369348042[165] = 0.0;
   out_3449117321369348042[166] = 0.0;
   out_3449117321369348042[167] = 0.0;
   out_3449117321369348042[168] = 0.0;
   out_3449117321369348042[169] = 0.0;
   out_3449117321369348042[170] = 0.0;
   out_3449117321369348042[171] = 1.0;
   out_3449117321369348042[172] = 0.0;
   out_3449117321369348042[173] = 0.0;
   out_3449117321369348042[174] = 0.0;
   out_3449117321369348042[175] = 0.0;
   out_3449117321369348042[176] = 0.0;
   out_3449117321369348042[177] = 0.0;
   out_3449117321369348042[178] = 0.0;
   out_3449117321369348042[179] = 0.0;
   out_3449117321369348042[180] = 0.0;
   out_3449117321369348042[181] = 0.0;
   out_3449117321369348042[182] = 0.0;
   out_3449117321369348042[183] = 0.0;
   out_3449117321369348042[184] = 0.0;
   out_3449117321369348042[185] = 0.0;
   out_3449117321369348042[186] = 0.0;
   out_3449117321369348042[187] = 0.0;
   out_3449117321369348042[188] = 0.0;
   out_3449117321369348042[189] = 0.0;
   out_3449117321369348042[190] = 1.0;
   out_3449117321369348042[191] = 0.0;
   out_3449117321369348042[192] = 0.0;
   out_3449117321369348042[193] = 0.0;
   out_3449117321369348042[194] = 0.0;
   out_3449117321369348042[195] = 0.0;
   out_3449117321369348042[196] = 0.0;
   out_3449117321369348042[197] = 0.0;
   out_3449117321369348042[198] = 0.0;
   out_3449117321369348042[199] = 0.0;
   out_3449117321369348042[200] = 0.0;
   out_3449117321369348042[201] = 0.0;
   out_3449117321369348042[202] = 0.0;
   out_3449117321369348042[203] = 0.0;
   out_3449117321369348042[204] = 0.0;
   out_3449117321369348042[205] = 0.0;
   out_3449117321369348042[206] = 0.0;
   out_3449117321369348042[207] = 0.0;
   out_3449117321369348042[208] = 0.0;
   out_3449117321369348042[209] = 1.0;
   out_3449117321369348042[210] = 0.0;
   out_3449117321369348042[211] = 0.0;
   out_3449117321369348042[212] = 0.0;
   out_3449117321369348042[213] = 0.0;
   out_3449117321369348042[214] = 0.0;
   out_3449117321369348042[215] = 0.0;
   out_3449117321369348042[216] = 0.0;
   out_3449117321369348042[217] = 0.0;
   out_3449117321369348042[218] = 0.0;
   out_3449117321369348042[219] = 0.0;
   out_3449117321369348042[220] = 0.0;
   out_3449117321369348042[221] = 0.0;
   out_3449117321369348042[222] = 0.0;
   out_3449117321369348042[223] = 0.0;
   out_3449117321369348042[224] = 0.0;
   out_3449117321369348042[225] = 0.0;
   out_3449117321369348042[226] = 0.0;
   out_3449117321369348042[227] = 0.0;
   out_3449117321369348042[228] = 1.0;
   out_3449117321369348042[229] = 0.0;
   out_3449117321369348042[230] = 0.0;
   out_3449117321369348042[231] = 0.0;
   out_3449117321369348042[232] = 0.0;
   out_3449117321369348042[233] = 0.0;
   out_3449117321369348042[234] = 0.0;
   out_3449117321369348042[235] = 0.0;
   out_3449117321369348042[236] = 0.0;
   out_3449117321369348042[237] = 0.0;
   out_3449117321369348042[238] = 0.0;
   out_3449117321369348042[239] = 0.0;
   out_3449117321369348042[240] = 0.0;
   out_3449117321369348042[241] = 0.0;
   out_3449117321369348042[242] = 0.0;
   out_3449117321369348042[243] = 0.0;
   out_3449117321369348042[244] = 0.0;
   out_3449117321369348042[245] = 0.0;
   out_3449117321369348042[246] = 0.0;
   out_3449117321369348042[247] = 1.0;
   out_3449117321369348042[248] = 0.0;
   out_3449117321369348042[249] = 0.0;
   out_3449117321369348042[250] = 0.0;
   out_3449117321369348042[251] = 0.0;
   out_3449117321369348042[252] = 0.0;
   out_3449117321369348042[253] = 0.0;
   out_3449117321369348042[254] = 0.0;
   out_3449117321369348042[255] = 0.0;
   out_3449117321369348042[256] = 0.0;
   out_3449117321369348042[257] = 0.0;
   out_3449117321369348042[258] = 0.0;
   out_3449117321369348042[259] = 0.0;
   out_3449117321369348042[260] = 0.0;
   out_3449117321369348042[261] = 0.0;
   out_3449117321369348042[262] = 0.0;
   out_3449117321369348042[263] = 0.0;
   out_3449117321369348042[264] = 0.0;
   out_3449117321369348042[265] = 0.0;
   out_3449117321369348042[266] = 1.0;
   out_3449117321369348042[267] = 0.0;
   out_3449117321369348042[268] = 0.0;
   out_3449117321369348042[269] = 0.0;
   out_3449117321369348042[270] = 0.0;
   out_3449117321369348042[271] = 0.0;
   out_3449117321369348042[272] = 0.0;
   out_3449117321369348042[273] = 0.0;
   out_3449117321369348042[274] = 0.0;
   out_3449117321369348042[275] = 0.0;
   out_3449117321369348042[276] = 0.0;
   out_3449117321369348042[277] = 0.0;
   out_3449117321369348042[278] = 0.0;
   out_3449117321369348042[279] = 0.0;
   out_3449117321369348042[280] = 0.0;
   out_3449117321369348042[281] = 0.0;
   out_3449117321369348042[282] = 0.0;
   out_3449117321369348042[283] = 0.0;
   out_3449117321369348042[284] = 0.0;
   out_3449117321369348042[285] = 1.0;
   out_3449117321369348042[286] = 0.0;
   out_3449117321369348042[287] = 0.0;
   out_3449117321369348042[288] = 0.0;
   out_3449117321369348042[289] = 0.0;
   out_3449117321369348042[290] = 0.0;
   out_3449117321369348042[291] = 0.0;
   out_3449117321369348042[292] = 0.0;
   out_3449117321369348042[293] = 0.0;
   out_3449117321369348042[294] = 0.0;
   out_3449117321369348042[295] = 0.0;
   out_3449117321369348042[296] = 0.0;
   out_3449117321369348042[297] = 0.0;
   out_3449117321369348042[298] = 0.0;
   out_3449117321369348042[299] = 0.0;
   out_3449117321369348042[300] = 0.0;
   out_3449117321369348042[301] = 0.0;
   out_3449117321369348042[302] = 0.0;
   out_3449117321369348042[303] = 0.0;
   out_3449117321369348042[304] = 1.0;
   out_3449117321369348042[305] = 0.0;
   out_3449117321369348042[306] = 0.0;
   out_3449117321369348042[307] = 0.0;
   out_3449117321369348042[308] = 0.0;
   out_3449117321369348042[309] = 0.0;
   out_3449117321369348042[310] = 0.0;
   out_3449117321369348042[311] = 0.0;
   out_3449117321369348042[312] = 0.0;
   out_3449117321369348042[313] = 0.0;
   out_3449117321369348042[314] = 0.0;
   out_3449117321369348042[315] = 0.0;
   out_3449117321369348042[316] = 0.0;
   out_3449117321369348042[317] = 0.0;
   out_3449117321369348042[318] = 0.0;
   out_3449117321369348042[319] = 0.0;
   out_3449117321369348042[320] = 0.0;
   out_3449117321369348042[321] = 0.0;
   out_3449117321369348042[322] = 0.0;
   out_3449117321369348042[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5011277720700882846) {
   out_5011277720700882846[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5011277720700882846[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5011277720700882846[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5011277720700882846[3] = dt*state[12] + state[3];
   out_5011277720700882846[4] = dt*state[13] + state[4];
   out_5011277720700882846[5] = dt*state[14] + state[5];
   out_5011277720700882846[6] = state[6];
   out_5011277720700882846[7] = state[7];
   out_5011277720700882846[8] = state[8];
   out_5011277720700882846[9] = state[9];
   out_5011277720700882846[10] = state[10];
   out_5011277720700882846[11] = state[11];
   out_5011277720700882846[12] = state[12];
   out_5011277720700882846[13] = state[13];
   out_5011277720700882846[14] = state[14];
   out_5011277720700882846[15] = state[15];
   out_5011277720700882846[16] = state[16];
   out_5011277720700882846[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8549798686069518373) {
   out_8549798686069518373[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8549798686069518373[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8549798686069518373[2] = 0;
   out_8549798686069518373[3] = 0;
   out_8549798686069518373[4] = 0;
   out_8549798686069518373[5] = 0;
   out_8549798686069518373[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8549798686069518373[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8549798686069518373[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8549798686069518373[9] = 0;
   out_8549798686069518373[10] = 0;
   out_8549798686069518373[11] = 0;
   out_8549798686069518373[12] = 0;
   out_8549798686069518373[13] = 0;
   out_8549798686069518373[14] = 0;
   out_8549798686069518373[15] = 0;
   out_8549798686069518373[16] = 0;
   out_8549798686069518373[17] = 0;
   out_8549798686069518373[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8549798686069518373[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8549798686069518373[20] = 0;
   out_8549798686069518373[21] = 0;
   out_8549798686069518373[22] = 0;
   out_8549798686069518373[23] = 0;
   out_8549798686069518373[24] = 0;
   out_8549798686069518373[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8549798686069518373[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8549798686069518373[27] = 0;
   out_8549798686069518373[28] = 0;
   out_8549798686069518373[29] = 0;
   out_8549798686069518373[30] = 0;
   out_8549798686069518373[31] = 0;
   out_8549798686069518373[32] = 0;
   out_8549798686069518373[33] = 0;
   out_8549798686069518373[34] = 0;
   out_8549798686069518373[35] = 0;
   out_8549798686069518373[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8549798686069518373[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8549798686069518373[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8549798686069518373[39] = 0;
   out_8549798686069518373[40] = 0;
   out_8549798686069518373[41] = 0;
   out_8549798686069518373[42] = 0;
   out_8549798686069518373[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8549798686069518373[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8549798686069518373[45] = 0;
   out_8549798686069518373[46] = 0;
   out_8549798686069518373[47] = 0;
   out_8549798686069518373[48] = 0;
   out_8549798686069518373[49] = 0;
   out_8549798686069518373[50] = 0;
   out_8549798686069518373[51] = 0;
   out_8549798686069518373[52] = 0;
   out_8549798686069518373[53] = 0;
   out_8549798686069518373[54] = 0;
   out_8549798686069518373[55] = 0;
   out_8549798686069518373[56] = 0;
   out_8549798686069518373[57] = 1;
   out_8549798686069518373[58] = 0;
   out_8549798686069518373[59] = 0;
   out_8549798686069518373[60] = 0;
   out_8549798686069518373[61] = 0;
   out_8549798686069518373[62] = 0;
   out_8549798686069518373[63] = 0;
   out_8549798686069518373[64] = 0;
   out_8549798686069518373[65] = 0;
   out_8549798686069518373[66] = dt;
   out_8549798686069518373[67] = 0;
   out_8549798686069518373[68] = 0;
   out_8549798686069518373[69] = 0;
   out_8549798686069518373[70] = 0;
   out_8549798686069518373[71] = 0;
   out_8549798686069518373[72] = 0;
   out_8549798686069518373[73] = 0;
   out_8549798686069518373[74] = 0;
   out_8549798686069518373[75] = 0;
   out_8549798686069518373[76] = 1;
   out_8549798686069518373[77] = 0;
   out_8549798686069518373[78] = 0;
   out_8549798686069518373[79] = 0;
   out_8549798686069518373[80] = 0;
   out_8549798686069518373[81] = 0;
   out_8549798686069518373[82] = 0;
   out_8549798686069518373[83] = 0;
   out_8549798686069518373[84] = 0;
   out_8549798686069518373[85] = dt;
   out_8549798686069518373[86] = 0;
   out_8549798686069518373[87] = 0;
   out_8549798686069518373[88] = 0;
   out_8549798686069518373[89] = 0;
   out_8549798686069518373[90] = 0;
   out_8549798686069518373[91] = 0;
   out_8549798686069518373[92] = 0;
   out_8549798686069518373[93] = 0;
   out_8549798686069518373[94] = 0;
   out_8549798686069518373[95] = 1;
   out_8549798686069518373[96] = 0;
   out_8549798686069518373[97] = 0;
   out_8549798686069518373[98] = 0;
   out_8549798686069518373[99] = 0;
   out_8549798686069518373[100] = 0;
   out_8549798686069518373[101] = 0;
   out_8549798686069518373[102] = 0;
   out_8549798686069518373[103] = 0;
   out_8549798686069518373[104] = dt;
   out_8549798686069518373[105] = 0;
   out_8549798686069518373[106] = 0;
   out_8549798686069518373[107] = 0;
   out_8549798686069518373[108] = 0;
   out_8549798686069518373[109] = 0;
   out_8549798686069518373[110] = 0;
   out_8549798686069518373[111] = 0;
   out_8549798686069518373[112] = 0;
   out_8549798686069518373[113] = 0;
   out_8549798686069518373[114] = 1;
   out_8549798686069518373[115] = 0;
   out_8549798686069518373[116] = 0;
   out_8549798686069518373[117] = 0;
   out_8549798686069518373[118] = 0;
   out_8549798686069518373[119] = 0;
   out_8549798686069518373[120] = 0;
   out_8549798686069518373[121] = 0;
   out_8549798686069518373[122] = 0;
   out_8549798686069518373[123] = 0;
   out_8549798686069518373[124] = 0;
   out_8549798686069518373[125] = 0;
   out_8549798686069518373[126] = 0;
   out_8549798686069518373[127] = 0;
   out_8549798686069518373[128] = 0;
   out_8549798686069518373[129] = 0;
   out_8549798686069518373[130] = 0;
   out_8549798686069518373[131] = 0;
   out_8549798686069518373[132] = 0;
   out_8549798686069518373[133] = 1;
   out_8549798686069518373[134] = 0;
   out_8549798686069518373[135] = 0;
   out_8549798686069518373[136] = 0;
   out_8549798686069518373[137] = 0;
   out_8549798686069518373[138] = 0;
   out_8549798686069518373[139] = 0;
   out_8549798686069518373[140] = 0;
   out_8549798686069518373[141] = 0;
   out_8549798686069518373[142] = 0;
   out_8549798686069518373[143] = 0;
   out_8549798686069518373[144] = 0;
   out_8549798686069518373[145] = 0;
   out_8549798686069518373[146] = 0;
   out_8549798686069518373[147] = 0;
   out_8549798686069518373[148] = 0;
   out_8549798686069518373[149] = 0;
   out_8549798686069518373[150] = 0;
   out_8549798686069518373[151] = 0;
   out_8549798686069518373[152] = 1;
   out_8549798686069518373[153] = 0;
   out_8549798686069518373[154] = 0;
   out_8549798686069518373[155] = 0;
   out_8549798686069518373[156] = 0;
   out_8549798686069518373[157] = 0;
   out_8549798686069518373[158] = 0;
   out_8549798686069518373[159] = 0;
   out_8549798686069518373[160] = 0;
   out_8549798686069518373[161] = 0;
   out_8549798686069518373[162] = 0;
   out_8549798686069518373[163] = 0;
   out_8549798686069518373[164] = 0;
   out_8549798686069518373[165] = 0;
   out_8549798686069518373[166] = 0;
   out_8549798686069518373[167] = 0;
   out_8549798686069518373[168] = 0;
   out_8549798686069518373[169] = 0;
   out_8549798686069518373[170] = 0;
   out_8549798686069518373[171] = 1;
   out_8549798686069518373[172] = 0;
   out_8549798686069518373[173] = 0;
   out_8549798686069518373[174] = 0;
   out_8549798686069518373[175] = 0;
   out_8549798686069518373[176] = 0;
   out_8549798686069518373[177] = 0;
   out_8549798686069518373[178] = 0;
   out_8549798686069518373[179] = 0;
   out_8549798686069518373[180] = 0;
   out_8549798686069518373[181] = 0;
   out_8549798686069518373[182] = 0;
   out_8549798686069518373[183] = 0;
   out_8549798686069518373[184] = 0;
   out_8549798686069518373[185] = 0;
   out_8549798686069518373[186] = 0;
   out_8549798686069518373[187] = 0;
   out_8549798686069518373[188] = 0;
   out_8549798686069518373[189] = 0;
   out_8549798686069518373[190] = 1;
   out_8549798686069518373[191] = 0;
   out_8549798686069518373[192] = 0;
   out_8549798686069518373[193] = 0;
   out_8549798686069518373[194] = 0;
   out_8549798686069518373[195] = 0;
   out_8549798686069518373[196] = 0;
   out_8549798686069518373[197] = 0;
   out_8549798686069518373[198] = 0;
   out_8549798686069518373[199] = 0;
   out_8549798686069518373[200] = 0;
   out_8549798686069518373[201] = 0;
   out_8549798686069518373[202] = 0;
   out_8549798686069518373[203] = 0;
   out_8549798686069518373[204] = 0;
   out_8549798686069518373[205] = 0;
   out_8549798686069518373[206] = 0;
   out_8549798686069518373[207] = 0;
   out_8549798686069518373[208] = 0;
   out_8549798686069518373[209] = 1;
   out_8549798686069518373[210] = 0;
   out_8549798686069518373[211] = 0;
   out_8549798686069518373[212] = 0;
   out_8549798686069518373[213] = 0;
   out_8549798686069518373[214] = 0;
   out_8549798686069518373[215] = 0;
   out_8549798686069518373[216] = 0;
   out_8549798686069518373[217] = 0;
   out_8549798686069518373[218] = 0;
   out_8549798686069518373[219] = 0;
   out_8549798686069518373[220] = 0;
   out_8549798686069518373[221] = 0;
   out_8549798686069518373[222] = 0;
   out_8549798686069518373[223] = 0;
   out_8549798686069518373[224] = 0;
   out_8549798686069518373[225] = 0;
   out_8549798686069518373[226] = 0;
   out_8549798686069518373[227] = 0;
   out_8549798686069518373[228] = 1;
   out_8549798686069518373[229] = 0;
   out_8549798686069518373[230] = 0;
   out_8549798686069518373[231] = 0;
   out_8549798686069518373[232] = 0;
   out_8549798686069518373[233] = 0;
   out_8549798686069518373[234] = 0;
   out_8549798686069518373[235] = 0;
   out_8549798686069518373[236] = 0;
   out_8549798686069518373[237] = 0;
   out_8549798686069518373[238] = 0;
   out_8549798686069518373[239] = 0;
   out_8549798686069518373[240] = 0;
   out_8549798686069518373[241] = 0;
   out_8549798686069518373[242] = 0;
   out_8549798686069518373[243] = 0;
   out_8549798686069518373[244] = 0;
   out_8549798686069518373[245] = 0;
   out_8549798686069518373[246] = 0;
   out_8549798686069518373[247] = 1;
   out_8549798686069518373[248] = 0;
   out_8549798686069518373[249] = 0;
   out_8549798686069518373[250] = 0;
   out_8549798686069518373[251] = 0;
   out_8549798686069518373[252] = 0;
   out_8549798686069518373[253] = 0;
   out_8549798686069518373[254] = 0;
   out_8549798686069518373[255] = 0;
   out_8549798686069518373[256] = 0;
   out_8549798686069518373[257] = 0;
   out_8549798686069518373[258] = 0;
   out_8549798686069518373[259] = 0;
   out_8549798686069518373[260] = 0;
   out_8549798686069518373[261] = 0;
   out_8549798686069518373[262] = 0;
   out_8549798686069518373[263] = 0;
   out_8549798686069518373[264] = 0;
   out_8549798686069518373[265] = 0;
   out_8549798686069518373[266] = 1;
   out_8549798686069518373[267] = 0;
   out_8549798686069518373[268] = 0;
   out_8549798686069518373[269] = 0;
   out_8549798686069518373[270] = 0;
   out_8549798686069518373[271] = 0;
   out_8549798686069518373[272] = 0;
   out_8549798686069518373[273] = 0;
   out_8549798686069518373[274] = 0;
   out_8549798686069518373[275] = 0;
   out_8549798686069518373[276] = 0;
   out_8549798686069518373[277] = 0;
   out_8549798686069518373[278] = 0;
   out_8549798686069518373[279] = 0;
   out_8549798686069518373[280] = 0;
   out_8549798686069518373[281] = 0;
   out_8549798686069518373[282] = 0;
   out_8549798686069518373[283] = 0;
   out_8549798686069518373[284] = 0;
   out_8549798686069518373[285] = 1;
   out_8549798686069518373[286] = 0;
   out_8549798686069518373[287] = 0;
   out_8549798686069518373[288] = 0;
   out_8549798686069518373[289] = 0;
   out_8549798686069518373[290] = 0;
   out_8549798686069518373[291] = 0;
   out_8549798686069518373[292] = 0;
   out_8549798686069518373[293] = 0;
   out_8549798686069518373[294] = 0;
   out_8549798686069518373[295] = 0;
   out_8549798686069518373[296] = 0;
   out_8549798686069518373[297] = 0;
   out_8549798686069518373[298] = 0;
   out_8549798686069518373[299] = 0;
   out_8549798686069518373[300] = 0;
   out_8549798686069518373[301] = 0;
   out_8549798686069518373[302] = 0;
   out_8549798686069518373[303] = 0;
   out_8549798686069518373[304] = 1;
   out_8549798686069518373[305] = 0;
   out_8549798686069518373[306] = 0;
   out_8549798686069518373[307] = 0;
   out_8549798686069518373[308] = 0;
   out_8549798686069518373[309] = 0;
   out_8549798686069518373[310] = 0;
   out_8549798686069518373[311] = 0;
   out_8549798686069518373[312] = 0;
   out_8549798686069518373[313] = 0;
   out_8549798686069518373[314] = 0;
   out_8549798686069518373[315] = 0;
   out_8549798686069518373[316] = 0;
   out_8549798686069518373[317] = 0;
   out_8549798686069518373[318] = 0;
   out_8549798686069518373[319] = 0;
   out_8549798686069518373[320] = 0;
   out_8549798686069518373[321] = 0;
   out_8549798686069518373[322] = 0;
   out_8549798686069518373[323] = 1;
}
void h_4(double *state, double *unused, double *out_6117192379534719749) {
   out_6117192379534719749[0] = state[6] + state[9];
   out_6117192379534719749[1] = state[7] + state[10];
   out_6117192379534719749[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1703401063669732693) {
   out_1703401063669732693[0] = 0;
   out_1703401063669732693[1] = 0;
   out_1703401063669732693[2] = 0;
   out_1703401063669732693[3] = 0;
   out_1703401063669732693[4] = 0;
   out_1703401063669732693[5] = 0;
   out_1703401063669732693[6] = 1;
   out_1703401063669732693[7] = 0;
   out_1703401063669732693[8] = 0;
   out_1703401063669732693[9] = 1;
   out_1703401063669732693[10] = 0;
   out_1703401063669732693[11] = 0;
   out_1703401063669732693[12] = 0;
   out_1703401063669732693[13] = 0;
   out_1703401063669732693[14] = 0;
   out_1703401063669732693[15] = 0;
   out_1703401063669732693[16] = 0;
   out_1703401063669732693[17] = 0;
   out_1703401063669732693[18] = 0;
   out_1703401063669732693[19] = 0;
   out_1703401063669732693[20] = 0;
   out_1703401063669732693[21] = 0;
   out_1703401063669732693[22] = 0;
   out_1703401063669732693[23] = 0;
   out_1703401063669732693[24] = 0;
   out_1703401063669732693[25] = 1;
   out_1703401063669732693[26] = 0;
   out_1703401063669732693[27] = 0;
   out_1703401063669732693[28] = 1;
   out_1703401063669732693[29] = 0;
   out_1703401063669732693[30] = 0;
   out_1703401063669732693[31] = 0;
   out_1703401063669732693[32] = 0;
   out_1703401063669732693[33] = 0;
   out_1703401063669732693[34] = 0;
   out_1703401063669732693[35] = 0;
   out_1703401063669732693[36] = 0;
   out_1703401063669732693[37] = 0;
   out_1703401063669732693[38] = 0;
   out_1703401063669732693[39] = 0;
   out_1703401063669732693[40] = 0;
   out_1703401063669732693[41] = 0;
   out_1703401063669732693[42] = 0;
   out_1703401063669732693[43] = 0;
   out_1703401063669732693[44] = 1;
   out_1703401063669732693[45] = 0;
   out_1703401063669732693[46] = 0;
   out_1703401063669732693[47] = 1;
   out_1703401063669732693[48] = 0;
   out_1703401063669732693[49] = 0;
   out_1703401063669732693[50] = 0;
   out_1703401063669732693[51] = 0;
   out_1703401063669732693[52] = 0;
   out_1703401063669732693[53] = 0;
}
void h_10(double *state, double *unused, double *out_2733554222400647132) {
   out_2733554222400647132[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2733554222400647132[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2733554222400647132[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_1998743020988853441) {
   out_1998743020988853441[0] = 0;
   out_1998743020988853441[1] = 9.8100000000000005*cos(state[1]);
   out_1998743020988853441[2] = 0;
   out_1998743020988853441[3] = 0;
   out_1998743020988853441[4] = -state[8];
   out_1998743020988853441[5] = state[7];
   out_1998743020988853441[6] = 0;
   out_1998743020988853441[7] = state[5];
   out_1998743020988853441[8] = -state[4];
   out_1998743020988853441[9] = 0;
   out_1998743020988853441[10] = 0;
   out_1998743020988853441[11] = 0;
   out_1998743020988853441[12] = 1;
   out_1998743020988853441[13] = 0;
   out_1998743020988853441[14] = 0;
   out_1998743020988853441[15] = 1;
   out_1998743020988853441[16] = 0;
   out_1998743020988853441[17] = 0;
   out_1998743020988853441[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_1998743020988853441[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_1998743020988853441[20] = 0;
   out_1998743020988853441[21] = state[8];
   out_1998743020988853441[22] = 0;
   out_1998743020988853441[23] = -state[6];
   out_1998743020988853441[24] = -state[5];
   out_1998743020988853441[25] = 0;
   out_1998743020988853441[26] = state[3];
   out_1998743020988853441[27] = 0;
   out_1998743020988853441[28] = 0;
   out_1998743020988853441[29] = 0;
   out_1998743020988853441[30] = 0;
   out_1998743020988853441[31] = 1;
   out_1998743020988853441[32] = 0;
   out_1998743020988853441[33] = 0;
   out_1998743020988853441[34] = 1;
   out_1998743020988853441[35] = 0;
   out_1998743020988853441[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_1998743020988853441[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_1998743020988853441[38] = 0;
   out_1998743020988853441[39] = -state[7];
   out_1998743020988853441[40] = state[6];
   out_1998743020988853441[41] = 0;
   out_1998743020988853441[42] = state[4];
   out_1998743020988853441[43] = -state[3];
   out_1998743020988853441[44] = 0;
   out_1998743020988853441[45] = 0;
   out_1998743020988853441[46] = 0;
   out_1998743020988853441[47] = 0;
   out_1998743020988853441[48] = 0;
   out_1998743020988853441[49] = 0;
   out_1998743020988853441[50] = 1;
   out_1998743020988853441[51] = 0;
   out_1998743020988853441[52] = 0;
   out_1998743020988853441[53] = 1;
}
void h_13(double *state, double *unused, double *out_6711610153155625838) {
   out_6711610153155625838[0] = state[3];
   out_6711610153155625838[1] = state[4];
   out_6711610153155625838[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4915674889002065494) {
   out_4915674889002065494[0] = 0;
   out_4915674889002065494[1] = 0;
   out_4915674889002065494[2] = 0;
   out_4915674889002065494[3] = 1;
   out_4915674889002065494[4] = 0;
   out_4915674889002065494[5] = 0;
   out_4915674889002065494[6] = 0;
   out_4915674889002065494[7] = 0;
   out_4915674889002065494[8] = 0;
   out_4915674889002065494[9] = 0;
   out_4915674889002065494[10] = 0;
   out_4915674889002065494[11] = 0;
   out_4915674889002065494[12] = 0;
   out_4915674889002065494[13] = 0;
   out_4915674889002065494[14] = 0;
   out_4915674889002065494[15] = 0;
   out_4915674889002065494[16] = 0;
   out_4915674889002065494[17] = 0;
   out_4915674889002065494[18] = 0;
   out_4915674889002065494[19] = 0;
   out_4915674889002065494[20] = 0;
   out_4915674889002065494[21] = 0;
   out_4915674889002065494[22] = 1;
   out_4915674889002065494[23] = 0;
   out_4915674889002065494[24] = 0;
   out_4915674889002065494[25] = 0;
   out_4915674889002065494[26] = 0;
   out_4915674889002065494[27] = 0;
   out_4915674889002065494[28] = 0;
   out_4915674889002065494[29] = 0;
   out_4915674889002065494[30] = 0;
   out_4915674889002065494[31] = 0;
   out_4915674889002065494[32] = 0;
   out_4915674889002065494[33] = 0;
   out_4915674889002065494[34] = 0;
   out_4915674889002065494[35] = 0;
   out_4915674889002065494[36] = 0;
   out_4915674889002065494[37] = 0;
   out_4915674889002065494[38] = 0;
   out_4915674889002065494[39] = 0;
   out_4915674889002065494[40] = 0;
   out_4915674889002065494[41] = 1;
   out_4915674889002065494[42] = 0;
   out_4915674889002065494[43] = 0;
   out_4915674889002065494[44] = 0;
   out_4915674889002065494[45] = 0;
   out_4915674889002065494[46] = 0;
   out_4915674889002065494[47] = 0;
   out_4915674889002065494[48] = 0;
   out_4915674889002065494[49] = 0;
   out_4915674889002065494[50] = 0;
   out_4915674889002065494[51] = 0;
   out_4915674889002065494[52] = 0;
   out_4915674889002065494[53] = 0;
}
void h_14(double *state, double *unused, double *out_6016470627401781103) {
   out_6016470627401781103[0] = state[6];
   out_6016470627401781103[1] = state[7];
   out_6016470627401781103[2] = state[8];
}
void H_14(double *state, double *unused, double *out_1379387368625639603) {
   out_1379387368625639603[0] = 0;
   out_1379387368625639603[1] = 0;
   out_1379387368625639603[2] = 0;
   out_1379387368625639603[3] = 0;
   out_1379387368625639603[4] = 0;
   out_1379387368625639603[5] = 0;
   out_1379387368625639603[6] = 1;
   out_1379387368625639603[7] = 0;
   out_1379387368625639603[8] = 0;
   out_1379387368625639603[9] = 0;
   out_1379387368625639603[10] = 0;
   out_1379387368625639603[11] = 0;
   out_1379387368625639603[12] = 0;
   out_1379387368625639603[13] = 0;
   out_1379387368625639603[14] = 0;
   out_1379387368625639603[15] = 0;
   out_1379387368625639603[16] = 0;
   out_1379387368625639603[17] = 0;
   out_1379387368625639603[18] = 0;
   out_1379387368625639603[19] = 0;
   out_1379387368625639603[20] = 0;
   out_1379387368625639603[21] = 0;
   out_1379387368625639603[22] = 0;
   out_1379387368625639603[23] = 0;
   out_1379387368625639603[24] = 0;
   out_1379387368625639603[25] = 1;
   out_1379387368625639603[26] = 0;
   out_1379387368625639603[27] = 0;
   out_1379387368625639603[28] = 0;
   out_1379387368625639603[29] = 0;
   out_1379387368625639603[30] = 0;
   out_1379387368625639603[31] = 0;
   out_1379387368625639603[32] = 0;
   out_1379387368625639603[33] = 0;
   out_1379387368625639603[34] = 0;
   out_1379387368625639603[35] = 0;
   out_1379387368625639603[36] = 0;
   out_1379387368625639603[37] = 0;
   out_1379387368625639603[38] = 0;
   out_1379387368625639603[39] = 0;
   out_1379387368625639603[40] = 0;
   out_1379387368625639603[41] = 0;
   out_1379387368625639603[42] = 0;
   out_1379387368625639603[43] = 0;
   out_1379387368625639603[44] = 1;
   out_1379387368625639603[45] = 0;
   out_1379387368625639603[46] = 0;
   out_1379387368625639603[47] = 0;
   out_1379387368625639603[48] = 0;
   out_1379387368625639603[49] = 0;
   out_1379387368625639603[50] = 0;
   out_1379387368625639603[51] = 0;
   out_1379387368625639603[52] = 0;
   out_1379387368625639603[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7151556355931759320) {
  err_fun(nom_x, delta_x, out_7151556355931759320);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_659960172465309786) {
  inv_err_fun(nom_x, true_x, out_659960172465309786);
}
void pose_H_mod_fun(double *state, double *out_3449117321369348042) {
  H_mod_fun(state, out_3449117321369348042);
}
void pose_f_fun(double *state, double dt, double *out_5011277720700882846) {
  f_fun(state,  dt, out_5011277720700882846);
}
void pose_F_fun(double *state, double dt, double *out_8549798686069518373) {
  F_fun(state,  dt, out_8549798686069518373);
}
void pose_h_4(double *state, double *unused, double *out_6117192379534719749) {
  h_4(state, unused, out_6117192379534719749);
}
void pose_H_4(double *state, double *unused, double *out_1703401063669732693) {
  H_4(state, unused, out_1703401063669732693);
}
void pose_h_10(double *state, double *unused, double *out_2733554222400647132) {
  h_10(state, unused, out_2733554222400647132);
}
void pose_H_10(double *state, double *unused, double *out_1998743020988853441) {
  H_10(state, unused, out_1998743020988853441);
}
void pose_h_13(double *state, double *unused, double *out_6711610153155625838) {
  h_13(state, unused, out_6711610153155625838);
}
void pose_H_13(double *state, double *unused, double *out_4915674889002065494) {
  H_13(state, unused, out_4915674889002065494);
}
void pose_h_14(double *state, double *unused, double *out_6016470627401781103) {
  h_14(state, unused, out_6016470627401781103);
}
void pose_H_14(double *state, double *unused, double *out_1379387368625639603) {
  H_14(state, unused, out_1379387368625639603);
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
