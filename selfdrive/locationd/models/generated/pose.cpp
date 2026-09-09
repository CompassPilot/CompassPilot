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
void err_fun(double *nom_x, double *delta_x, double *out_7808017239736434491) {
   out_7808017239736434491[0] = delta_x[0] + nom_x[0];
   out_7808017239736434491[1] = delta_x[1] + nom_x[1];
   out_7808017239736434491[2] = delta_x[2] + nom_x[2];
   out_7808017239736434491[3] = delta_x[3] + nom_x[3];
   out_7808017239736434491[4] = delta_x[4] + nom_x[4];
   out_7808017239736434491[5] = delta_x[5] + nom_x[5];
   out_7808017239736434491[6] = delta_x[6] + nom_x[6];
   out_7808017239736434491[7] = delta_x[7] + nom_x[7];
   out_7808017239736434491[8] = delta_x[8] + nom_x[8];
   out_7808017239736434491[9] = delta_x[9] + nom_x[9];
   out_7808017239736434491[10] = delta_x[10] + nom_x[10];
   out_7808017239736434491[11] = delta_x[11] + nom_x[11];
   out_7808017239736434491[12] = delta_x[12] + nom_x[12];
   out_7808017239736434491[13] = delta_x[13] + nom_x[13];
   out_7808017239736434491[14] = delta_x[14] + nom_x[14];
   out_7808017239736434491[15] = delta_x[15] + nom_x[15];
   out_7808017239736434491[16] = delta_x[16] + nom_x[16];
   out_7808017239736434491[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_476072578365709337) {
   out_476072578365709337[0] = -nom_x[0] + true_x[0];
   out_476072578365709337[1] = -nom_x[1] + true_x[1];
   out_476072578365709337[2] = -nom_x[2] + true_x[2];
   out_476072578365709337[3] = -nom_x[3] + true_x[3];
   out_476072578365709337[4] = -nom_x[4] + true_x[4];
   out_476072578365709337[5] = -nom_x[5] + true_x[5];
   out_476072578365709337[6] = -nom_x[6] + true_x[6];
   out_476072578365709337[7] = -nom_x[7] + true_x[7];
   out_476072578365709337[8] = -nom_x[8] + true_x[8];
   out_476072578365709337[9] = -nom_x[9] + true_x[9];
   out_476072578365709337[10] = -nom_x[10] + true_x[10];
   out_476072578365709337[11] = -nom_x[11] + true_x[11];
   out_476072578365709337[12] = -nom_x[12] + true_x[12];
   out_476072578365709337[13] = -nom_x[13] + true_x[13];
   out_476072578365709337[14] = -nom_x[14] + true_x[14];
   out_476072578365709337[15] = -nom_x[15] + true_x[15];
   out_476072578365709337[16] = -nom_x[16] + true_x[16];
   out_476072578365709337[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_8257603167809194144) {
   out_8257603167809194144[0] = 1.0;
   out_8257603167809194144[1] = 0.0;
   out_8257603167809194144[2] = 0.0;
   out_8257603167809194144[3] = 0.0;
   out_8257603167809194144[4] = 0.0;
   out_8257603167809194144[5] = 0.0;
   out_8257603167809194144[6] = 0.0;
   out_8257603167809194144[7] = 0.0;
   out_8257603167809194144[8] = 0.0;
   out_8257603167809194144[9] = 0.0;
   out_8257603167809194144[10] = 0.0;
   out_8257603167809194144[11] = 0.0;
   out_8257603167809194144[12] = 0.0;
   out_8257603167809194144[13] = 0.0;
   out_8257603167809194144[14] = 0.0;
   out_8257603167809194144[15] = 0.0;
   out_8257603167809194144[16] = 0.0;
   out_8257603167809194144[17] = 0.0;
   out_8257603167809194144[18] = 0.0;
   out_8257603167809194144[19] = 1.0;
   out_8257603167809194144[20] = 0.0;
   out_8257603167809194144[21] = 0.0;
   out_8257603167809194144[22] = 0.0;
   out_8257603167809194144[23] = 0.0;
   out_8257603167809194144[24] = 0.0;
   out_8257603167809194144[25] = 0.0;
   out_8257603167809194144[26] = 0.0;
   out_8257603167809194144[27] = 0.0;
   out_8257603167809194144[28] = 0.0;
   out_8257603167809194144[29] = 0.0;
   out_8257603167809194144[30] = 0.0;
   out_8257603167809194144[31] = 0.0;
   out_8257603167809194144[32] = 0.0;
   out_8257603167809194144[33] = 0.0;
   out_8257603167809194144[34] = 0.0;
   out_8257603167809194144[35] = 0.0;
   out_8257603167809194144[36] = 0.0;
   out_8257603167809194144[37] = 0.0;
   out_8257603167809194144[38] = 1.0;
   out_8257603167809194144[39] = 0.0;
   out_8257603167809194144[40] = 0.0;
   out_8257603167809194144[41] = 0.0;
   out_8257603167809194144[42] = 0.0;
   out_8257603167809194144[43] = 0.0;
   out_8257603167809194144[44] = 0.0;
   out_8257603167809194144[45] = 0.0;
   out_8257603167809194144[46] = 0.0;
   out_8257603167809194144[47] = 0.0;
   out_8257603167809194144[48] = 0.0;
   out_8257603167809194144[49] = 0.0;
   out_8257603167809194144[50] = 0.0;
   out_8257603167809194144[51] = 0.0;
   out_8257603167809194144[52] = 0.0;
   out_8257603167809194144[53] = 0.0;
   out_8257603167809194144[54] = 0.0;
   out_8257603167809194144[55] = 0.0;
   out_8257603167809194144[56] = 0.0;
   out_8257603167809194144[57] = 1.0;
   out_8257603167809194144[58] = 0.0;
   out_8257603167809194144[59] = 0.0;
   out_8257603167809194144[60] = 0.0;
   out_8257603167809194144[61] = 0.0;
   out_8257603167809194144[62] = 0.0;
   out_8257603167809194144[63] = 0.0;
   out_8257603167809194144[64] = 0.0;
   out_8257603167809194144[65] = 0.0;
   out_8257603167809194144[66] = 0.0;
   out_8257603167809194144[67] = 0.0;
   out_8257603167809194144[68] = 0.0;
   out_8257603167809194144[69] = 0.0;
   out_8257603167809194144[70] = 0.0;
   out_8257603167809194144[71] = 0.0;
   out_8257603167809194144[72] = 0.0;
   out_8257603167809194144[73] = 0.0;
   out_8257603167809194144[74] = 0.0;
   out_8257603167809194144[75] = 0.0;
   out_8257603167809194144[76] = 1.0;
   out_8257603167809194144[77] = 0.0;
   out_8257603167809194144[78] = 0.0;
   out_8257603167809194144[79] = 0.0;
   out_8257603167809194144[80] = 0.0;
   out_8257603167809194144[81] = 0.0;
   out_8257603167809194144[82] = 0.0;
   out_8257603167809194144[83] = 0.0;
   out_8257603167809194144[84] = 0.0;
   out_8257603167809194144[85] = 0.0;
   out_8257603167809194144[86] = 0.0;
   out_8257603167809194144[87] = 0.0;
   out_8257603167809194144[88] = 0.0;
   out_8257603167809194144[89] = 0.0;
   out_8257603167809194144[90] = 0.0;
   out_8257603167809194144[91] = 0.0;
   out_8257603167809194144[92] = 0.0;
   out_8257603167809194144[93] = 0.0;
   out_8257603167809194144[94] = 0.0;
   out_8257603167809194144[95] = 1.0;
   out_8257603167809194144[96] = 0.0;
   out_8257603167809194144[97] = 0.0;
   out_8257603167809194144[98] = 0.0;
   out_8257603167809194144[99] = 0.0;
   out_8257603167809194144[100] = 0.0;
   out_8257603167809194144[101] = 0.0;
   out_8257603167809194144[102] = 0.0;
   out_8257603167809194144[103] = 0.0;
   out_8257603167809194144[104] = 0.0;
   out_8257603167809194144[105] = 0.0;
   out_8257603167809194144[106] = 0.0;
   out_8257603167809194144[107] = 0.0;
   out_8257603167809194144[108] = 0.0;
   out_8257603167809194144[109] = 0.0;
   out_8257603167809194144[110] = 0.0;
   out_8257603167809194144[111] = 0.0;
   out_8257603167809194144[112] = 0.0;
   out_8257603167809194144[113] = 0.0;
   out_8257603167809194144[114] = 1.0;
   out_8257603167809194144[115] = 0.0;
   out_8257603167809194144[116] = 0.0;
   out_8257603167809194144[117] = 0.0;
   out_8257603167809194144[118] = 0.0;
   out_8257603167809194144[119] = 0.0;
   out_8257603167809194144[120] = 0.0;
   out_8257603167809194144[121] = 0.0;
   out_8257603167809194144[122] = 0.0;
   out_8257603167809194144[123] = 0.0;
   out_8257603167809194144[124] = 0.0;
   out_8257603167809194144[125] = 0.0;
   out_8257603167809194144[126] = 0.0;
   out_8257603167809194144[127] = 0.0;
   out_8257603167809194144[128] = 0.0;
   out_8257603167809194144[129] = 0.0;
   out_8257603167809194144[130] = 0.0;
   out_8257603167809194144[131] = 0.0;
   out_8257603167809194144[132] = 0.0;
   out_8257603167809194144[133] = 1.0;
   out_8257603167809194144[134] = 0.0;
   out_8257603167809194144[135] = 0.0;
   out_8257603167809194144[136] = 0.0;
   out_8257603167809194144[137] = 0.0;
   out_8257603167809194144[138] = 0.0;
   out_8257603167809194144[139] = 0.0;
   out_8257603167809194144[140] = 0.0;
   out_8257603167809194144[141] = 0.0;
   out_8257603167809194144[142] = 0.0;
   out_8257603167809194144[143] = 0.0;
   out_8257603167809194144[144] = 0.0;
   out_8257603167809194144[145] = 0.0;
   out_8257603167809194144[146] = 0.0;
   out_8257603167809194144[147] = 0.0;
   out_8257603167809194144[148] = 0.0;
   out_8257603167809194144[149] = 0.0;
   out_8257603167809194144[150] = 0.0;
   out_8257603167809194144[151] = 0.0;
   out_8257603167809194144[152] = 1.0;
   out_8257603167809194144[153] = 0.0;
   out_8257603167809194144[154] = 0.0;
   out_8257603167809194144[155] = 0.0;
   out_8257603167809194144[156] = 0.0;
   out_8257603167809194144[157] = 0.0;
   out_8257603167809194144[158] = 0.0;
   out_8257603167809194144[159] = 0.0;
   out_8257603167809194144[160] = 0.0;
   out_8257603167809194144[161] = 0.0;
   out_8257603167809194144[162] = 0.0;
   out_8257603167809194144[163] = 0.0;
   out_8257603167809194144[164] = 0.0;
   out_8257603167809194144[165] = 0.0;
   out_8257603167809194144[166] = 0.0;
   out_8257603167809194144[167] = 0.0;
   out_8257603167809194144[168] = 0.0;
   out_8257603167809194144[169] = 0.0;
   out_8257603167809194144[170] = 0.0;
   out_8257603167809194144[171] = 1.0;
   out_8257603167809194144[172] = 0.0;
   out_8257603167809194144[173] = 0.0;
   out_8257603167809194144[174] = 0.0;
   out_8257603167809194144[175] = 0.0;
   out_8257603167809194144[176] = 0.0;
   out_8257603167809194144[177] = 0.0;
   out_8257603167809194144[178] = 0.0;
   out_8257603167809194144[179] = 0.0;
   out_8257603167809194144[180] = 0.0;
   out_8257603167809194144[181] = 0.0;
   out_8257603167809194144[182] = 0.0;
   out_8257603167809194144[183] = 0.0;
   out_8257603167809194144[184] = 0.0;
   out_8257603167809194144[185] = 0.0;
   out_8257603167809194144[186] = 0.0;
   out_8257603167809194144[187] = 0.0;
   out_8257603167809194144[188] = 0.0;
   out_8257603167809194144[189] = 0.0;
   out_8257603167809194144[190] = 1.0;
   out_8257603167809194144[191] = 0.0;
   out_8257603167809194144[192] = 0.0;
   out_8257603167809194144[193] = 0.0;
   out_8257603167809194144[194] = 0.0;
   out_8257603167809194144[195] = 0.0;
   out_8257603167809194144[196] = 0.0;
   out_8257603167809194144[197] = 0.0;
   out_8257603167809194144[198] = 0.0;
   out_8257603167809194144[199] = 0.0;
   out_8257603167809194144[200] = 0.0;
   out_8257603167809194144[201] = 0.0;
   out_8257603167809194144[202] = 0.0;
   out_8257603167809194144[203] = 0.0;
   out_8257603167809194144[204] = 0.0;
   out_8257603167809194144[205] = 0.0;
   out_8257603167809194144[206] = 0.0;
   out_8257603167809194144[207] = 0.0;
   out_8257603167809194144[208] = 0.0;
   out_8257603167809194144[209] = 1.0;
   out_8257603167809194144[210] = 0.0;
   out_8257603167809194144[211] = 0.0;
   out_8257603167809194144[212] = 0.0;
   out_8257603167809194144[213] = 0.0;
   out_8257603167809194144[214] = 0.0;
   out_8257603167809194144[215] = 0.0;
   out_8257603167809194144[216] = 0.0;
   out_8257603167809194144[217] = 0.0;
   out_8257603167809194144[218] = 0.0;
   out_8257603167809194144[219] = 0.0;
   out_8257603167809194144[220] = 0.0;
   out_8257603167809194144[221] = 0.0;
   out_8257603167809194144[222] = 0.0;
   out_8257603167809194144[223] = 0.0;
   out_8257603167809194144[224] = 0.0;
   out_8257603167809194144[225] = 0.0;
   out_8257603167809194144[226] = 0.0;
   out_8257603167809194144[227] = 0.0;
   out_8257603167809194144[228] = 1.0;
   out_8257603167809194144[229] = 0.0;
   out_8257603167809194144[230] = 0.0;
   out_8257603167809194144[231] = 0.0;
   out_8257603167809194144[232] = 0.0;
   out_8257603167809194144[233] = 0.0;
   out_8257603167809194144[234] = 0.0;
   out_8257603167809194144[235] = 0.0;
   out_8257603167809194144[236] = 0.0;
   out_8257603167809194144[237] = 0.0;
   out_8257603167809194144[238] = 0.0;
   out_8257603167809194144[239] = 0.0;
   out_8257603167809194144[240] = 0.0;
   out_8257603167809194144[241] = 0.0;
   out_8257603167809194144[242] = 0.0;
   out_8257603167809194144[243] = 0.0;
   out_8257603167809194144[244] = 0.0;
   out_8257603167809194144[245] = 0.0;
   out_8257603167809194144[246] = 0.0;
   out_8257603167809194144[247] = 1.0;
   out_8257603167809194144[248] = 0.0;
   out_8257603167809194144[249] = 0.0;
   out_8257603167809194144[250] = 0.0;
   out_8257603167809194144[251] = 0.0;
   out_8257603167809194144[252] = 0.0;
   out_8257603167809194144[253] = 0.0;
   out_8257603167809194144[254] = 0.0;
   out_8257603167809194144[255] = 0.0;
   out_8257603167809194144[256] = 0.0;
   out_8257603167809194144[257] = 0.0;
   out_8257603167809194144[258] = 0.0;
   out_8257603167809194144[259] = 0.0;
   out_8257603167809194144[260] = 0.0;
   out_8257603167809194144[261] = 0.0;
   out_8257603167809194144[262] = 0.0;
   out_8257603167809194144[263] = 0.0;
   out_8257603167809194144[264] = 0.0;
   out_8257603167809194144[265] = 0.0;
   out_8257603167809194144[266] = 1.0;
   out_8257603167809194144[267] = 0.0;
   out_8257603167809194144[268] = 0.0;
   out_8257603167809194144[269] = 0.0;
   out_8257603167809194144[270] = 0.0;
   out_8257603167809194144[271] = 0.0;
   out_8257603167809194144[272] = 0.0;
   out_8257603167809194144[273] = 0.0;
   out_8257603167809194144[274] = 0.0;
   out_8257603167809194144[275] = 0.0;
   out_8257603167809194144[276] = 0.0;
   out_8257603167809194144[277] = 0.0;
   out_8257603167809194144[278] = 0.0;
   out_8257603167809194144[279] = 0.0;
   out_8257603167809194144[280] = 0.0;
   out_8257603167809194144[281] = 0.0;
   out_8257603167809194144[282] = 0.0;
   out_8257603167809194144[283] = 0.0;
   out_8257603167809194144[284] = 0.0;
   out_8257603167809194144[285] = 1.0;
   out_8257603167809194144[286] = 0.0;
   out_8257603167809194144[287] = 0.0;
   out_8257603167809194144[288] = 0.0;
   out_8257603167809194144[289] = 0.0;
   out_8257603167809194144[290] = 0.0;
   out_8257603167809194144[291] = 0.0;
   out_8257603167809194144[292] = 0.0;
   out_8257603167809194144[293] = 0.0;
   out_8257603167809194144[294] = 0.0;
   out_8257603167809194144[295] = 0.0;
   out_8257603167809194144[296] = 0.0;
   out_8257603167809194144[297] = 0.0;
   out_8257603167809194144[298] = 0.0;
   out_8257603167809194144[299] = 0.0;
   out_8257603167809194144[300] = 0.0;
   out_8257603167809194144[301] = 0.0;
   out_8257603167809194144[302] = 0.0;
   out_8257603167809194144[303] = 0.0;
   out_8257603167809194144[304] = 1.0;
   out_8257603167809194144[305] = 0.0;
   out_8257603167809194144[306] = 0.0;
   out_8257603167809194144[307] = 0.0;
   out_8257603167809194144[308] = 0.0;
   out_8257603167809194144[309] = 0.0;
   out_8257603167809194144[310] = 0.0;
   out_8257603167809194144[311] = 0.0;
   out_8257603167809194144[312] = 0.0;
   out_8257603167809194144[313] = 0.0;
   out_8257603167809194144[314] = 0.0;
   out_8257603167809194144[315] = 0.0;
   out_8257603167809194144[316] = 0.0;
   out_8257603167809194144[317] = 0.0;
   out_8257603167809194144[318] = 0.0;
   out_8257603167809194144[319] = 0.0;
   out_8257603167809194144[320] = 0.0;
   out_8257603167809194144[321] = 0.0;
   out_8257603167809194144[322] = 0.0;
   out_8257603167809194144[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7273446577418706581) {
   out_7273446577418706581[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7273446577418706581[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7273446577418706581[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7273446577418706581[3] = dt*state[12] + state[3];
   out_7273446577418706581[4] = dt*state[13] + state[4];
   out_7273446577418706581[5] = dt*state[14] + state[5];
   out_7273446577418706581[6] = state[6];
   out_7273446577418706581[7] = state[7];
   out_7273446577418706581[8] = state[8];
   out_7273446577418706581[9] = state[9];
   out_7273446577418706581[10] = state[10];
   out_7273446577418706581[11] = state[11];
   out_7273446577418706581[12] = state[12];
   out_7273446577418706581[13] = state[13];
   out_7273446577418706581[14] = state[14];
   out_7273446577418706581[15] = state[15];
   out_7273446577418706581[16] = state[16];
   out_7273446577418706581[17] = state[17];
}
void F_fun(double *state, double dt, double *out_330211950996632566) {
   out_330211950996632566[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_330211950996632566[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_330211950996632566[2] = 0;
   out_330211950996632566[3] = 0;
   out_330211950996632566[4] = 0;
   out_330211950996632566[5] = 0;
   out_330211950996632566[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_330211950996632566[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_330211950996632566[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_330211950996632566[9] = 0;
   out_330211950996632566[10] = 0;
   out_330211950996632566[11] = 0;
   out_330211950996632566[12] = 0;
   out_330211950996632566[13] = 0;
   out_330211950996632566[14] = 0;
   out_330211950996632566[15] = 0;
   out_330211950996632566[16] = 0;
   out_330211950996632566[17] = 0;
   out_330211950996632566[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_330211950996632566[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_330211950996632566[20] = 0;
   out_330211950996632566[21] = 0;
   out_330211950996632566[22] = 0;
   out_330211950996632566[23] = 0;
   out_330211950996632566[24] = 0;
   out_330211950996632566[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_330211950996632566[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_330211950996632566[27] = 0;
   out_330211950996632566[28] = 0;
   out_330211950996632566[29] = 0;
   out_330211950996632566[30] = 0;
   out_330211950996632566[31] = 0;
   out_330211950996632566[32] = 0;
   out_330211950996632566[33] = 0;
   out_330211950996632566[34] = 0;
   out_330211950996632566[35] = 0;
   out_330211950996632566[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_330211950996632566[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_330211950996632566[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_330211950996632566[39] = 0;
   out_330211950996632566[40] = 0;
   out_330211950996632566[41] = 0;
   out_330211950996632566[42] = 0;
   out_330211950996632566[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_330211950996632566[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_330211950996632566[45] = 0;
   out_330211950996632566[46] = 0;
   out_330211950996632566[47] = 0;
   out_330211950996632566[48] = 0;
   out_330211950996632566[49] = 0;
   out_330211950996632566[50] = 0;
   out_330211950996632566[51] = 0;
   out_330211950996632566[52] = 0;
   out_330211950996632566[53] = 0;
   out_330211950996632566[54] = 0;
   out_330211950996632566[55] = 0;
   out_330211950996632566[56] = 0;
   out_330211950996632566[57] = 1;
   out_330211950996632566[58] = 0;
   out_330211950996632566[59] = 0;
   out_330211950996632566[60] = 0;
   out_330211950996632566[61] = 0;
   out_330211950996632566[62] = 0;
   out_330211950996632566[63] = 0;
   out_330211950996632566[64] = 0;
   out_330211950996632566[65] = 0;
   out_330211950996632566[66] = dt;
   out_330211950996632566[67] = 0;
   out_330211950996632566[68] = 0;
   out_330211950996632566[69] = 0;
   out_330211950996632566[70] = 0;
   out_330211950996632566[71] = 0;
   out_330211950996632566[72] = 0;
   out_330211950996632566[73] = 0;
   out_330211950996632566[74] = 0;
   out_330211950996632566[75] = 0;
   out_330211950996632566[76] = 1;
   out_330211950996632566[77] = 0;
   out_330211950996632566[78] = 0;
   out_330211950996632566[79] = 0;
   out_330211950996632566[80] = 0;
   out_330211950996632566[81] = 0;
   out_330211950996632566[82] = 0;
   out_330211950996632566[83] = 0;
   out_330211950996632566[84] = 0;
   out_330211950996632566[85] = dt;
   out_330211950996632566[86] = 0;
   out_330211950996632566[87] = 0;
   out_330211950996632566[88] = 0;
   out_330211950996632566[89] = 0;
   out_330211950996632566[90] = 0;
   out_330211950996632566[91] = 0;
   out_330211950996632566[92] = 0;
   out_330211950996632566[93] = 0;
   out_330211950996632566[94] = 0;
   out_330211950996632566[95] = 1;
   out_330211950996632566[96] = 0;
   out_330211950996632566[97] = 0;
   out_330211950996632566[98] = 0;
   out_330211950996632566[99] = 0;
   out_330211950996632566[100] = 0;
   out_330211950996632566[101] = 0;
   out_330211950996632566[102] = 0;
   out_330211950996632566[103] = 0;
   out_330211950996632566[104] = dt;
   out_330211950996632566[105] = 0;
   out_330211950996632566[106] = 0;
   out_330211950996632566[107] = 0;
   out_330211950996632566[108] = 0;
   out_330211950996632566[109] = 0;
   out_330211950996632566[110] = 0;
   out_330211950996632566[111] = 0;
   out_330211950996632566[112] = 0;
   out_330211950996632566[113] = 0;
   out_330211950996632566[114] = 1;
   out_330211950996632566[115] = 0;
   out_330211950996632566[116] = 0;
   out_330211950996632566[117] = 0;
   out_330211950996632566[118] = 0;
   out_330211950996632566[119] = 0;
   out_330211950996632566[120] = 0;
   out_330211950996632566[121] = 0;
   out_330211950996632566[122] = 0;
   out_330211950996632566[123] = 0;
   out_330211950996632566[124] = 0;
   out_330211950996632566[125] = 0;
   out_330211950996632566[126] = 0;
   out_330211950996632566[127] = 0;
   out_330211950996632566[128] = 0;
   out_330211950996632566[129] = 0;
   out_330211950996632566[130] = 0;
   out_330211950996632566[131] = 0;
   out_330211950996632566[132] = 0;
   out_330211950996632566[133] = 1;
   out_330211950996632566[134] = 0;
   out_330211950996632566[135] = 0;
   out_330211950996632566[136] = 0;
   out_330211950996632566[137] = 0;
   out_330211950996632566[138] = 0;
   out_330211950996632566[139] = 0;
   out_330211950996632566[140] = 0;
   out_330211950996632566[141] = 0;
   out_330211950996632566[142] = 0;
   out_330211950996632566[143] = 0;
   out_330211950996632566[144] = 0;
   out_330211950996632566[145] = 0;
   out_330211950996632566[146] = 0;
   out_330211950996632566[147] = 0;
   out_330211950996632566[148] = 0;
   out_330211950996632566[149] = 0;
   out_330211950996632566[150] = 0;
   out_330211950996632566[151] = 0;
   out_330211950996632566[152] = 1;
   out_330211950996632566[153] = 0;
   out_330211950996632566[154] = 0;
   out_330211950996632566[155] = 0;
   out_330211950996632566[156] = 0;
   out_330211950996632566[157] = 0;
   out_330211950996632566[158] = 0;
   out_330211950996632566[159] = 0;
   out_330211950996632566[160] = 0;
   out_330211950996632566[161] = 0;
   out_330211950996632566[162] = 0;
   out_330211950996632566[163] = 0;
   out_330211950996632566[164] = 0;
   out_330211950996632566[165] = 0;
   out_330211950996632566[166] = 0;
   out_330211950996632566[167] = 0;
   out_330211950996632566[168] = 0;
   out_330211950996632566[169] = 0;
   out_330211950996632566[170] = 0;
   out_330211950996632566[171] = 1;
   out_330211950996632566[172] = 0;
   out_330211950996632566[173] = 0;
   out_330211950996632566[174] = 0;
   out_330211950996632566[175] = 0;
   out_330211950996632566[176] = 0;
   out_330211950996632566[177] = 0;
   out_330211950996632566[178] = 0;
   out_330211950996632566[179] = 0;
   out_330211950996632566[180] = 0;
   out_330211950996632566[181] = 0;
   out_330211950996632566[182] = 0;
   out_330211950996632566[183] = 0;
   out_330211950996632566[184] = 0;
   out_330211950996632566[185] = 0;
   out_330211950996632566[186] = 0;
   out_330211950996632566[187] = 0;
   out_330211950996632566[188] = 0;
   out_330211950996632566[189] = 0;
   out_330211950996632566[190] = 1;
   out_330211950996632566[191] = 0;
   out_330211950996632566[192] = 0;
   out_330211950996632566[193] = 0;
   out_330211950996632566[194] = 0;
   out_330211950996632566[195] = 0;
   out_330211950996632566[196] = 0;
   out_330211950996632566[197] = 0;
   out_330211950996632566[198] = 0;
   out_330211950996632566[199] = 0;
   out_330211950996632566[200] = 0;
   out_330211950996632566[201] = 0;
   out_330211950996632566[202] = 0;
   out_330211950996632566[203] = 0;
   out_330211950996632566[204] = 0;
   out_330211950996632566[205] = 0;
   out_330211950996632566[206] = 0;
   out_330211950996632566[207] = 0;
   out_330211950996632566[208] = 0;
   out_330211950996632566[209] = 1;
   out_330211950996632566[210] = 0;
   out_330211950996632566[211] = 0;
   out_330211950996632566[212] = 0;
   out_330211950996632566[213] = 0;
   out_330211950996632566[214] = 0;
   out_330211950996632566[215] = 0;
   out_330211950996632566[216] = 0;
   out_330211950996632566[217] = 0;
   out_330211950996632566[218] = 0;
   out_330211950996632566[219] = 0;
   out_330211950996632566[220] = 0;
   out_330211950996632566[221] = 0;
   out_330211950996632566[222] = 0;
   out_330211950996632566[223] = 0;
   out_330211950996632566[224] = 0;
   out_330211950996632566[225] = 0;
   out_330211950996632566[226] = 0;
   out_330211950996632566[227] = 0;
   out_330211950996632566[228] = 1;
   out_330211950996632566[229] = 0;
   out_330211950996632566[230] = 0;
   out_330211950996632566[231] = 0;
   out_330211950996632566[232] = 0;
   out_330211950996632566[233] = 0;
   out_330211950996632566[234] = 0;
   out_330211950996632566[235] = 0;
   out_330211950996632566[236] = 0;
   out_330211950996632566[237] = 0;
   out_330211950996632566[238] = 0;
   out_330211950996632566[239] = 0;
   out_330211950996632566[240] = 0;
   out_330211950996632566[241] = 0;
   out_330211950996632566[242] = 0;
   out_330211950996632566[243] = 0;
   out_330211950996632566[244] = 0;
   out_330211950996632566[245] = 0;
   out_330211950996632566[246] = 0;
   out_330211950996632566[247] = 1;
   out_330211950996632566[248] = 0;
   out_330211950996632566[249] = 0;
   out_330211950996632566[250] = 0;
   out_330211950996632566[251] = 0;
   out_330211950996632566[252] = 0;
   out_330211950996632566[253] = 0;
   out_330211950996632566[254] = 0;
   out_330211950996632566[255] = 0;
   out_330211950996632566[256] = 0;
   out_330211950996632566[257] = 0;
   out_330211950996632566[258] = 0;
   out_330211950996632566[259] = 0;
   out_330211950996632566[260] = 0;
   out_330211950996632566[261] = 0;
   out_330211950996632566[262] = 0;
   out_330211950996632566[263] = 0;
   out_330211950996632566[264] = 0;
   out_330211950996632566[265] = 0;
   out_330211950996632566[266] = 1;
   out_330211950996632566[267] = 0;
   out_330211950996632566[268] = 0;
   out_330211950996632566[269] = 0;
   out_330211950996632566[270] = 0;
   out_330211950996632566[271] = 0;
   out_330211950996632566[272] = 0;
   out_330211950996632566[273] = 0;
   out_330211950996632566[274] = 0;
   out_330211950996632566[275] = 0;
   out_330211950996632566[276] = 0;
   out_330211950996632566[277] = 0;
   out_330211950996632566[278] = 0;
   out_330211950996632566[279] = 0;
   out_330211950996632566[280] = 0;
   out_330211950996632566[281] = 0;
   out_330211950996632566[282] = 0;
   out_330211950996632566[283] = 0;
   out_330211950996632566[284] = 0;
   out_330211950996632566[285] = 1;
   out_330211950996632566[286] = 0;
   out_330211950996632566[287] = 0;
   out_330211950996632566[288] = 0;
   out_330211950996632566[289] = 0;
   out_330211950996632566[290] = 0;
   out_330211950996632566[291] = 0;
   out_330211950996632566[292] = 0;
   out_330211950996632566[293] = 0;
   out_330211950996632566[294] = 0;
   out_330211950996632566[295] = 0;
   out_330211950996632566[296] = 0;
   out_330211950996632566[297] = 0;
   out_330211950996632566[298] = 0;
   out_330211950996632566[299] = 0;
   out_330211950996632566[300] = 0;
   out_330211950996632566[301] = 0;
   out_330211950996632566[302] = 0;
   out_330211950996632566[303] = 0;
   out_330211950996632566[304] = 1;
   out_330211950996632566[305] = 0;
   out_330211950996632566[306] = 0;
   out_330211950996632566[307] = 0;
   out_330211950996632566[308] = 0;
   out_330211950996632566[309] = 0;
   out_330211950996632566[310] = 0;
   out_330211950996632566[311] = 0;
   out_330211950996632566[312] = 0;
   out_330211950996632566[313] = 0;
   out_330211950996632566[314] = 0;
   out_330211950996632566[315] = 0;
   out_330211950996632566[316] = 0;
   out_330211950996632566[317] = 0;
   out_330211950996632566[318] = 0;
   out_330211950996632566[319] = 0;
   out_330211950996632566[320] = 0;
   out_330211950996632566[321] = 0;
   out_330211950996632566[322] = 0;
   out_330211950996632566[323] = 1;
}
void h_4(double *state, double *unused, double *out_7679267299934609420) {
   out_7679267299934609420[0] = state[6] + state[9];
   out_7679267299934609420[1] = state[7] + state[10];
   out_7679267299934609420[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_686758498248627198) {
   out_686758498248627198[0] = 0;
   out_686758498248627198[1] = 0;
   out_686758498248627198[2] = 0;
   out_686758498248627198[3] = 0;
   out_686758498248627198[4] = 0;
   out_686758498248627198[5] = 0;
   out_686758498248627198[6] = 1;
   out_686758498248627198[7] = 0;
   out_686758498248627198[8] = 0;
   out_686758498248627198[9] = 1;
   out_686758498248627198[10] = 0;
   out_686758498248627198[11] = 0;
   out_686758498248627198[12] = 0;
   out_686758498248627198[13] = 0;
   out_686758498248627198[14] = 0;
   out_686758498248627198[15] = 0;
   out_686758498248627198[16] = 0;
   out_686758498248627198[17] = 0;
   out_686758498248627198[18] = 0;
   out_686758498248627198[19] = 0;
   out_686758498248627198[20] = 0;
   out_686758498248627198[21] = 0;
   out_686758498248627198[22] = 0;
   out_686758498248627198[23] = 0;
   out_686758498248627198[24] = 0;
   out_686758498248627198[25] = 1;
   out_686758498248627198[26] = 0;
   out_686758498248627198[27] = 0;
   out_686758498248627198[28] = 1;
   out_686758498248627198[29] = 0;
   out_686758498248627198[30] = 0;
   out_686758498248627198[31] = 0;
   out_686758498248627198[32] = 0;
   out_686758498248627198[33] = 0;
   out_686758498248627198[34] = 0;
   out_686758498248627198[35] = 0;
   out_686758498248627198[36] = 0;
   out_686758498248627198[37] = 0;
   out_686758498248627198[38] = 0;
   out_686758498248627198[39] = 0;
   out_686758498248627198[40] = 0;
   out_686758498248627198[41] = 0;
   out_686758498248627198[42] = 0;
   out_686758498248627198[43] = 0;
   out_686758498248627198[44] = 1;
   out_686758498248627198[45] = 0;
   out_686758498248627198[46] = 0;
   out_686758498248627198[47] = 1;
   out_686758498248627198[48] = 0;
   out_686758498248627198[49] = 0;
   out_686758498248627198[50] = 0;
   out_686758498248627198[51] = 0;
   out_686758498248627198[52] = 0;
   out_686758498248627198[53] = 0;
}
void h_10(double *state, double *unused, double *out_5266209753521868204) {
   out_5266209753521868204[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_5266209753521868204[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_5266209753521868204[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7448573778899456695) {
   out_7448573778899456695[0] = 0;
   out_7448573778899456695[1] = 9.8100000000000005*cos(state[1]);
   out_7448573778899456695[2] = 0;
   out_7448573778899456695[3] = 0;
   out_7448573778899456695[4] = -state[8];
   out_7448573778899456695[5] = state[7];
   out_7448573778899456695[6] = 0;
   out_7448573778899456695[7] = state[5];
   out_7448573778899456695[8] = -state[4];
   out_7448573778899456695[9] = 0;
   out_7448573778899456695[10] = 0;
   out_7448573778899456695[11] = 0;
   out_7448573778899456695[12] = 1;
   out_7448573778899456695[13] = 0;
   out_7448573778899456695[14] = 0;
   out_7448573778899456695[15] = 1;
   out_7448573778899456695[16] = 0;
   out_7448573778899456695[17] = 0;
   out_7448573778899456695[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7448573778899456695[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7448573778899456695[20] = 0;
   out_7448573778899456695[21] = state[8];
   out_7448573778899456695[22] = 0;
   out_7448573778899456695[23] = -state[6];
   out_7448573778899456695[24] = -state[5];
   out_7448573778899456695[25] = 0;
   out_7448573778899456695[26] = state[3];
   out_7448573778899456695[27] = 0;
   out_7448573778899456695[28] = 0;
   out_7448573778899456695[29] = 0;
   out_7448573778899456695[30] = 0;
   out_7448573778899456695[31] = 1;
   out_7448573778899456695[32] = 0;
   out_7448573778899456695[33] = 0;
   out_7448573778899456695[34] = 1;
   out_7448573778899456695[35] = 0;
   out_7448573778899456695[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7448573778899456695[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7448573778899456695[38] = 0;
   out_7448573778899456695[39] = -state[7];
   out_7448573778899456695[40] = state[6];
   out_7448573778899456695[41] = 0;
   out_7448573778899456695[42] = state[4];
   out_7448573778899456695[43] = -state[3];
   out_7448573778899456695[44] = 0;
   out_7448573778899456695[45] = 0;
   out_7448573778899456695[46] = 0;
   out_7448573778899456695[47] = 0;
   out_7448573778899456695[48] = 0;
   out_7448573778899456695[49] = 0;
   out_7448573778899456695[50] = 1;
   out_7448573778899456695[51] = 0;
   out_7448573778899456695[52] = 0;
   out_7448573778899456695[53] = 1;
}
void h_13(double *state, double *unused, double *out_4542250088899745943) {
   out_4542250088899745943[0] = state[3];
   out_4542250088899745943[1] = state[4];
   out_4542250088899745943[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2525515327083705603) {
   out_2525515327083705603[0] = 0;
   out_2525515327083705603[1] = 0;
   out_2525515327083705603[2] = 0;
   out_2525515327083705603[3] = 1;
   out_2525515327083705603[4] = 0;
   out_2525515327083705603[5] = 0;
   out_2525515327083705603[6] = 0;
   out_2525515327083705603[7] = 0;
   out_2525515327083705603[8] = 0;
   out_2525515327083705603[9] = 0;
   out_2525515327083705603[10] = 0;
   out_2525515327083705603[11] = 0;
   out_2525515327083705603[12] = 0;
   out_2525515327083705603[13] = 0;
   out_2525515327083705603[14] = 0;
   out_2525515327083705603[15] = 0;
   out_2525515327083705603[16] = 0;
   out_2525515327083705603[17] = 0;
   out_2525515327083705603[18] = 0;
   out_2525515327083705603[19] = 0;
   out_2525515327083705603[20] = 0;
   out_2525515327083705603[21] = 0;
   out_2525515327083705603[22] = 1;
   out_2525515327083705603[23] = 0;
   out_2525515327083705603[24] = 0;
   out_2525515327083705603[25] = 0;
   out_2525515327083705603[26] = 0;
   out_2525515327083705603[27] = 0;
   out_2525515327083705603[28] = 0;
   out_2525515327083705603[29] = 0;
   out_2525515327083705603[30] = 0;
   out_2525515327083705603[31] = 0;
   out_2525515327083705603[32] = 0;
   out_2525515327083705603[33] = 0;
   out_2525515327083705603[34] = 0;
   out_2525515327083705603[35] = 0;
   out_2525515327083705603[36] = 0;
   out_2525515327083705603[37] = 0;
   out_2525515327083705603[38] = 0;
   out_2525515327083705603[39] = 0;
   out_2525515327083705603[40] = 0;
   out_2525515327083705603[41] = 1;
   out_2525515327083705603[42] = 0;
   out_2525515327083705603[43] = 0;
   out_2525515327083705603[44] = 0;
   out_2525515327083705603[45] = 0;
   out_2525515327083705603[46] = 0;
   out_2525515327083705603[47] = 0;
   out_2525515327083705603[48] = 0;
   out_2525515327083705603[49] = 0;
   out_2525515327083705603[50] = 0;
   out_2525515327083705603[51] = 0;
   out_2525515327083705603[52] = 0;
   out_2525515327083705603[53] = 0;
}
void h_14(double *state, double *unused, double *out_8415149323118688858) {
   out_8415149323118688858[0] = state[6];
   out_8415149323118688858[1] = state[7];
   out_8415149323118688858[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3276482358090857331) {
   out_3276482358090857331[0] = 0;
   out_3276482358090857331[1] = 0;
   out_3276482358090857331[2] = 0;
   out_3276482358090857331[3] = 0;
   out_3276482358090857331[4] = 0;
   out_3276482358090857331[5] = 0;
   out_3276482358090857331[6] = 1;
   out_3276482358090857331[7] = 0;
   out_3276482358090857331[8] = 0;
   out_3276482358090857331[9] = 0;
   out_3276482358090857331[10] = 0;
   out_3276482358090857331[11] = 0;
   out_3276482358090857331[12] = 0;
   out_3276482358090857331[13] = 0;
   out_3276482358090857331[14] = 0;
   out_3276482358090857331[15] = 0;
   out_3276482358090857331[16] = 0;
   out_3276482358090857331[17] = 0;
   out_3276482358090857331[18] = 0;
   out_3276482358090857331[19] = 0;
   out_3276482358090857331[20] = 0;
   out_3276482358090857331[21] = 0;
   out_3276482358090857331[22] = 0;
   out_3276482358090857331[23] = 0;
   out_3276482358090857331[24] = 0;
   out_3276482358090857331[25] = 1;
   out_3276482358090857331[26] = 0;
   out_3276482358090857331[27] = 0;
   out_3276482358090857331[28] = 0;
   out_3276482358090857331[29] = 0;
   out_3276482358090857331[30] = 0;
   out_3276482358090857331[31] = 0;
   out_3276482358090857331[32] = 0;
   out_3276482358090857331[33] = 0;
   out_3276482358090857331[34] = 0;
   out_3276482358090857331[35] = 0;
   out_3276482358090857331[36] = 0;
   out_3276482358090857331[37] = 0;
   out_3276482358090857331[38] = 0;
   out_3276482358090857331[39] = 0;
   out_3276482358090857331[40] = 0;
   out_3276482358090857331[41] = 0;
   out_3276482358090857331[42] = 0;
   out_3276482358090857331[43] = 0;
   out_3276482358090857331[44] = 1;
   out_3276482358090857331[45] = 0;
   out_3276482358090857331[46] = 0;
   out_3276482358090857331[47] = 0;
   out_3276482358090857331[48] = 0;
   out_3276482358090857331[49] = 0;
   out_3276482358090857331[50] = 0;
   out_3276482358090857331[51] = 0;
   out_3276482358090857331[52] = 0;
   out_3276482358090857331[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7808017239736434491) {
  err_fun(nom_x, delta_x, out_7808017239736434491);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_476072578365709337) {
  inv_err_fun(nom_x, true_x, out_476072578365709337);
}
void pose_H_mod_fun(double *state, double *out_8257603167809194144) {
  H_mod_fun(state, out_8257603167809194144);
}
void pose_f_fun(double *state, double dt, double *out_7273446577418706581) {
  f_fun(state,  dt, out_7273446577418706581);
}
void pose_F_fun(double *state, double dt, double *out_330211950996632566) {
  F_fun(state,  dt, out_330211950996632566);
}
void pose_h_4(double *state, double *unused, double *out_7679267299934609420) {
  h_4(state, unused, out_7679267299934609420);
}
void pose_H_4(double *state, double *unused, double *out_686758498248627198) {
  H_4(state, unused, out_686758498248627198);
}
void pose_h_10(double *state, double *unused, double *out_5266209753521868204) {
  h_10(state, unused, out_5266209753521868204);
}
void pose_H_10(double *state, double *unused, double *out_7448573778899456695) {
  H_10(state, unused, out_7448573778899456695);
}
void pose_h_13(double *state, double *unused, double *out_4542250088899745943) {
  h_13(state, unused, out_4542250088899745943);
}
void pose_H_13(double *state, double *unused, double *out_2525515327083705603) {
  H_13(state, unused, out_2525515327083705603);
}
void pose_h_14(double *state, double *unused, double *out_8415149323118688858) {
  h_14(state, unused, out_8415149323118688858);
}
void pose_H_14(double *state, double *unused, double *out_3276482358090857331) {
  H_14(state, unused, out_3276482358090857331);
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
