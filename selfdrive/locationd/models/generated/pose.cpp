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
void err_fun(double *nom_x, double *delta_x, double *out_8800160146285448971) {
   out_8800160146285448971[0] = delta_x[0] + nom_x[0];
   out_8800160146285448971[1] = delta_x[1] + nom_x[1];
   out_8800160146285448971[2] = delta_x[2] + nom_x[2];
   out_8800160146285448971[3] = delta_x[3] + nom_x[3];
   out_8800160146285448971[4] = delta_x[4] + nom_x[4];
   out_8800160146285448971[5] = delta_x[5] + nom_x[5];
   out_8800160146285448971[6] = delta_x[6] + nom_x[6];
   out_8800160146285448971[7] = delta_x[7] + nom_x[7];
   out_8800160146285448971[8] = delta_x[8] + nom_x[8];
   out_8800160146285448971[9] = delta_x[9] + nom_x[9];
   out_8800160146285448971[10] = delta_x[10] + nom_x[10];
   out_8800160146285448971[11] = delta_x[11] + nom_x[11];
   out_8800160146285448971[12] = delta_x[12] + nom_x[12];
   out_8800160146285448971[13] = delta_x[13] + nom_x[13];
   out_8800160146285448971[14] = delta_x[14] + nom_x[14];
   out_8800160146285448971[15] = delta_x[15] + nom_x[15];
   out_8800160146285448971[16] = delta_x[16] + nom_x[16];
   out_8800160146285448971[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3072673840862845580) {
   out_3072673840862845580[0] = -nom_x[0] + true_x[0];
   out_3072673840862845580[1] = -nom_x[1] + true_x[1];
   out_3072673840862845580[2] = -nom_x[2] + true_x[2];
   out_3072673840862845580[3] = -nom_x[3] + true_x[3];
   out_3072673840862845580[4] = -nom_x[4] + true_x[4];
   out_3072673840862845580[5] = -nom_x[5] + true_x[5];
   out_3072673840862845580[6] = -nom_x[6] + true_x[6];
   out_3072673840862845580[7] = -nom_x[7] + true_x[7];
   out_3072673840862845580[8] = -nom_x[8] + true_x[8];
   out_3072673840862845580[9] = -nom_x[9] + true_x[9];
   out_3072673840862845580[10] = -nom_x[10] + true_x[10];
   out_3072673840862845580[11] = -nom_x[11] + true_x[11];
   out_3072673840862845580[12] = -nom_x[12] + true_x[12];
   out_3072673840862845580[13] = -nom_x[13] + true_x[13];
   out_3072673840862845580[14] = -nom_x[14] + true_x[14];
   out_3072673840862845580[15] = -nom_x[15] + true_x[15];
   out_3072673840862845580[16] = -nom_x[16] + true_x[16];
   out_3072673840862845580[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_6930602079968694147) {
   out_6930602079968694147[0] = 1.0;
   out_6930602079968694147[1] = 0.0;
   out_6930602079968694147[2] = 0.0;
   out_6930602079968694147[3] = 0.0;
   out_6930602079968694147[4] = 0.0;
   out_6930602079968694147[5] = 0.0;
   out_6930602079968694147[6] = 0.0;
   out_6930602079968694147[7] = 0.0;
   out_6930602079968694147[8] = 0.0;
   out_6930602079968694147[9] = 0.0;
   out_6930602079968694147[10] = 0.0;
   out_6930602079968694147[11] = 0.0;
   out_6930602079968694147[12] = 0.0;
   out_6930602079968694147[13] = 0.0;
   out_6930602079968694147[14] = 0.0;
   out_6930602079968694147[15] = 0.0;
   out_6930602079968694147[16] = 0.0;
   out_6930602079968694147[17] = 0.0;
   out_6930602079968694147[18] = 0.0;
   out_6930602079968694147[19] = 1.0;
   out_6930602079968694147[20] = 0.0;
   out_6930602079968694147[21] = 0.0;
   out_6930602079968694147[22] = 0.0;
   out_6930602079968694147[23] = 0.0;
   out_6930602079968694147[24] = 0.0;
   out_6930602079968694147[25] = 0.0;
   out_6930602079968694147[26] = 0.0;
   out_6930602079968694147[27] = 0.0;
   out_6930602079968694147[28] = 0.0;
   out_6930602079968694147[29] = 0.0;
   out_6930602079968694147[30] = 0.0;
   out_6930602079968694147[31] = 0.0;
   out_6930602079968694147[32] = 0.0;
   out_6930602079968694147[33] = 0.0;
   out_6930602079968694147[34] = 0.0;
   out_6930602079968694147[35] = 0.0;
   out_6930602079968694147[36] = 0.0;
   out_6930602079968694147[37] = 0.0;
   out_6930602079968694147[38] = 1.0;
   out_6930602079968694147[39] = 0.0;
   out_6930602079968694147[40] = 0.0;
   out_6930602079968694147[41] = 0.0;
   out_6930602079968694147[42] = 0.0;
   out_6930602079968694147[43] = 0.0;
   out_6930602079968694147[44] = 0.0;
   out_6930602079968694147[45] = 0.0;
   out_6930602079968694147[46] = 0.0;
   out_6930602079968694147[47] = 0.0;
   out_6930602079968694147[48] = 0.0;
   out_6930602079968694147[49] = 0.0;
   out_6930602079968694147[50] = 0.0;
   out_6930602079968694147[51] = 0.0;
   out_6930602079968694147[52] = 0.0;
   out_6930602079968694147[53] = 0.0;
   out_6930602079968694147[54] = 0.0;
   out_6930602079968694147[55] = 0.0;
   out_6930602079968694147[56] = 0.0;
   out_6930602079968694147[57] = 1.0;
   out_6930602079968694147[58] = 0.0;
   out_6930602079968694147[59] = 0.0;
   out_6930602079968694147[60] = 0.0;
   out_6930602079968694147[61] = 0.0;
   out_6930602079968694147[62] = 0.0;
   out_6930602079968694147[63] = 0.0;
   out_6930602079968694147[64] = 0.0;
   out_6930602079968694147[65] = 0.0;
   out_6930602079968694147[66] = 0.0;
   out_6930602079968694147[67] = 0.0;
   out_6930602079968694147[68] = 0.0;
   out_6930602079968694147[69] = 0.0;
   out_6930602079968694147[70] = 0.0;
   out_6930602079968694147[71] = 0.0;
   out_6930602079968694147[72] = 0.0;
   out_6930602079968694147[73] = 0.0;
   out_6930602079968694147[74] = 0.0;
   out_6930602079968694147[75] = 0.0;
   out_6930602079968694147[76] = 1.0;
   out_6930602079968694147[77] = 0.0;
   out_6930602079968694147[78] = 0.0;
   out_6930602079968694147[79] = 0.0;
   out_6930602079968694147[80] = 0.0;
   out_6930602079968694147[81] = 0.0;
   out_6930602079968694147[82] = 0.0;
   out_6930602079968694147[83] = 0.0;
   out_6930602079968694147[84] = 0.0;
   out_6930602079968694147[85] = 0.0;
   out_6930602079968694147[86] = 0.0;
   out_6930602079968694147[87] = 0.0;
   out_6930602079968694147[88] = 0.0;
   out_6930602079968694147[89] = 0.0;
   out_6930602079968694147[90] = 0.0;
   out_6930602079968694147[91] = 0.0;
   out_6930602079968694147[92] = 0.0;
   out_6930602079968694147[93] = 0.0;
   out_6930602079968694147[94] = 0.0;
   out_6930602079968694147[95] = 1.0;
   out_6930602079968694147[96] = 0.0;
   out_6930602079968694147[97] = 0.0;
   out_6930602079968694147[98] = 0.0;
   out_6930602079968694147[99] = 0.0;
   out_6930602079968694147[100] = 0.0;
   out_6930602079968694147[101] = 0.0;
   out_6930602079968694147[102] = 0.0;
   out_6930602079968694147[103] = 0.0;
   out_6930602079968694147[104] = 0.0;
   out_6930602079968694147[105] = 0.0;
   out_6930602079968694147[106] = 0.0;
   out_6930602079968694147[107] = 0.0;
   out_6930602079968694147[108] = 0.0;
   out_6930602079968694147[109] = 0.0;
   out_6930602079968694147[110] = 0.0;
   out_6930602079968694147[111] = 0.0;
   out_6930602079968694147[112] = 0.0;
   out_6930602079968694147[113] = 0.0;
   out_6930602079968694147[114] = 1.0;
   out_6930602079968694147[115] = 0.0;
   out_6930602079968694147[116] = 0.0;
   out_6930602079968694147[117] = 0.0;
   out_6930602079968694147[118] = 0.0;
   out_6930602079968694147[119] = 0.0;
   out_6930602079968694147[120] = 0.0;
   out_6930602079968694147[121] = 0.0;
   out_6930602079968694147[122] = 0.0;
   out_6930602079968694147[123] = 0.0;
   out_6930602079968694147[124] = 0.0;
   out_6930602079968694147[125] = 0.0;
   out_6930602079968694147[126] = 0.0;
   out_6930602079968694147[127] = 0.0;
   out_6930602079968694147[128] = 0.0;
   out_6930602079968694147[129] = 0.0;
   out_6930602079968694147[130] = 0.0;
   out_6930602079968694147[131] = 0.0;
   out_6930602079968694147[132] = 0.0;
   out_6930602079968694147[133] = 1.0;
   out_6930602079968694147[134] = 0.0;
   out_6930602079968694147[135] = 0.0;
   out_6930602079968694147[136] = 0.0;
   out_6930602079968694147[137] = 0.0;
   out_6930602079968694147[138] = 0.0;
   out_6930602079968694147[139] = 0.0;
   out_6930602079968694147[140] = 0.0;
   out_6930602079968694147[141] = 0.0;
   out_6930602079968694147[142] = 0.0;
   out_6930602079968694147[143] = 0.0;
   out_6930602079968694147[144] = 0.0;
   out_6930602079968694147[145] = 0.0;
   out_6930602079968694147[146] = 0.0;
   out_6930602079968694147[147] = 0.0;
   out_6930602079968694147[148] = 0.0;
   out_6930602079968694147[149] = 0.0;
   out_6930602079968694147[150] = 0.0;
   out_6930602079968694147[151] = 0.0;
   out_6930602079968694147[152] = 1.0;
   out_6930602079968694147[153] = 0.0;
   out_6930602079968694147[154] = 0.0;
   out_6930602079968694147[155] = 0.0;
   out_6930602079968694147[156] = 0.0;
   out_6930602079968694147[157] = 0.0;
   out_6930602079968694147[158] = 0.0;
   out_6930602079968694147[159] = 0.0;
   out_6930602079968694147[160] = 0.0;
   out_6930602079968694147[161] = 0.0;
   out_6930602079968694147[162] = 0.0;
   out_6930602079968694147[163] = 0.0;
   out_6930602079968694147[164] = 0.0;
   out_6930602079968694147[165] = 0.0;
   out_6930602079968694147[166] = 0.0;
   out_6930602079968694147[167] = 0.0;
   out_6930602079968694147[168] = 0.0;
   out_6930602079968694147[169] = 0.0;
   out_6930602079968694147[170] = 0.0;
   out_6930602079968694147[171] = 1.0;
   out_6930602079968694147[172] = 0.0;
   out_6930602079968694147[173] = 0.0;
   out_6930602079968694147[174] = 0.0;
   out_6930602079968694147[175] = 0.0;
   out_6930602079968694147[176] = 0.0;
   out_6930602079968694147[177] = 0.0;
   out_6930602079968694147[178] = 0.0;
   out_6930602079968694147[179] = 0.0;
   out_6930602079968694147[180] = 0.0;
   out_6930602079968694147[181] = 0.0;
   out_6930602079968694147[182] = 0.0;
   out_6930602079968694147[183] = 0.0;
   out_6930602079968694147[184] = 0.0;
   out_6930602079968694147[185] = 0.0;
   out_6930602079968694147[186] = 0.0;
   out_6930602079968694147[187] = 0.0;
   out_6930602079968694147[188] = 0.0;
   out_6930602079968694147[189] = 0.0;
   out_6930602079968694147[190] = 1.0;
   out_6930602079968694147[191] = 0.0;
   out_6930602079968694147[192] = 0.0;
   out_6930602079968694147[193] = 0.0;
   out_6930602079968694147[194] = 0.0;
   out_6930602079968694147[195] = 0.0;
   out_6930602079968694147[196] = 0.0;
   out_6930602079968694147[197] = 0.0;
   out_6930602079968694147[198] = 0.0;
   out_6930602079968694147[199] = 0.0;
   out_6930602079968694147[200] = 0.0;
   out_6930602079968694147[201] = 0.0;
   out_6930602079968694147[202] = 0.0;
   out_6930602079968694147[203] = 0.0;
   out_6930602079968694147[204] = 0.0;
   out_6930602079968694147[205] = 0.0;
   out_6930602079968694147[206] = 0.0;
   out_6930602079968694147[207] = 0.0;
   out_6930602079968694147[208] = 0.0;
   out_6930602079968694147[209] = 1.0;
   out_6930602079968694147[210] = 0.0;
   out_6930602079968694147[211] = 0.0;
   out_6930602079968694147[212] = 0.0;
   out_6930602079968694147[213] = 0.0;
   out_6930602079968694147[214] = 0.0;
   out_6930602079968694147[215] = 0.0;
   out_6930602079968694147[216] = 0.0;
   out_6930602079968694147[217] = 0.0;
   out_6930602079968694147[218] = 0.0;
   out_6930602079968694147[219] = 0.0;
   out_6930602079968694147[220] = 0.0;
   out_6930602079968694147[221] = 0.0;
   out_6930602079968694147[222] = 0.0;
   out_6930602079968694147[223] = 0.0;
   out_6930602079968694147[224] = 0.0;
   out_6930602079968694147[225] = 0.0;
   out_6930602079968694147[226] = 0.0;
   out_6930602079968694147[227] = 0.0;
   out_6930602079968694147[228] = 1.0;
   out_6930602079968694147[229] = 0.0;
   out_6930602079968694147[230] = 0.0;
   out_6930602079968694147[231] = 0.0;
   out_6930602079968694147[232] = 0.0;
   out_6930602079968694147[233] = 0.0;
   out_6930602079968694147[234] = 0.0;
   out_6930602079968694147[235] = 0.0;
   out_6930602079968694147[236] = 0.0;
   out_6930602079968694147[237] = 0.0;
   out_6930602079968694147[238] = 0.0;
   out_6930602079968694147[239] = 0.0;
   out_6930602079968694147[240] = 0.0;
   out_6930602079968694147[241] = 0.0;
   out_6930602079968694147[242] = 0.0;
   out_6930602079968694147[243] = 0.0;
   out_6930602079968694147[244] = 0.0;
   out_6930602079968694147[245] = 0.0;
   out_6930602079968694147[246] = 0.0;
   out_6930602079968694147[247] = 1.0;
   out_6930602079968694147[248] = 0.0;
   out_6930602079968694147[249] = 0.0;
   out_6930602079968694147[250] = 0.0;
   out_6930602079968694147[251] = 0.0;
   out_6930602079968694147[252] = 0.0;
   out_6930602079968694147[253] = 0.0;
   out_6930602079968694147[254] = 0.0;
   out_6930602079968694147[255] = 0.0;
   out_6930602079968694147[256] = 0.0;
   out_6930602079968694147[257] = 0.0;
   out_6930602079968694147[258] = 0.0;
   out_6930602079968694147[259] = 0.0;
   out_6930602079968694147[260] = 0.0;
   out_6930602079968694147[261] = 0.0;
   out_6930602079968694147[262] = 0.0;
   out_6930602079968694147[263] = 0.0;
   out_6930602079968694147[264] = 0.0;
   out_6930602079968694147[265] = 0.0;
   out_6930602079968694147[266] = 1.0;
   out_6930602079968694147[267] = 0.0;
   out_6930602079968694147[268] = 0.0;
   out_6930602079968694147[269] = 0.0;
   out_6930602079968694147[270] = 0.0;
   out_6930602079968694147[271] = 0.0;
   out_6930602079968694147[272] = 0.0;
   out_6930602079968694147[273] = 0.0;
   out_6930602079968694147[274] = 0.0;
   out_6930602079968694147[275] = 0.0;
   out_6930602079968694147[276] = 0.0;
   out_6930602079968694147[277] = 0.0;
   out_6930602079968694147[278] = 0.0;
   out_6930602079968694147[279] = 0.0;
   out_6930602079968694147[280] = 0.0;
   out_6930602079968694147[281] = 0.0;
   out_6930602079968694147[282] = 0.0;
   out_6930602079968694147[283] = 0.0;
   out_6930602079968694147[284] = 0.0;
   out_6930602079968694147[285] = 1.0;
   out_6930602079968694147[286] = 0.0;
   out_6930602079968694147[287] = 0.0;
   out_6930602079968694147[288] = 0.0;
   out_6930602079968694147[289] = 0.0;
   out_6930602079968694147[290] = 0.0;
   out_6930602079968694147[291] = 0.0;
   out_6930602079968694147[292] = 0.0;
   out_6930602079968694147[293] = 0.0;
   out_6930602079968694147[294] = 0.0;
   out_6930602079968694147[295] = 0.0;
   out_6930602079968694147[296] = 0.0;
   out_6930602079968694147[297] = 0.0;
   out_6930602079968694147[298] = 0.0;
   out_6930602079968694147[299] = 0.0;
   out_6930602079968694147[300] = 0.0;
   out_6930602079968694147[301] = 0.0;
   out_6930602079968694147[302] = 0.0;
   out_6930602079968694147[303] = 0.0;
   out_6930602079968694147[304] = 1.0;
   out_6930602079968694147[305] = 0.0;
   out_6930602079968694147[306] = 0.0;
   out_6930602079968694147[307] = 0.0;
   out_6930602079968694147[308] = 0.0;
   out_6930602079968694147[309] = 0.0;
   out_6930602079968694147[310] = 0.0;
   out_6930602079968694147[311] = 0.0;
   out_6930602079968694147[312] = 0.0;
   out_6930602079968694147[313] = 0.0;
   out_6930602079968694147[314] = 0.0;
   out_6930602079968694147[315] = 0.0;
   out_6930602079968694147[316] = 0.0;
   out_6930602079968694147[317] = 0.0;
   out_6930602079968694147[318] = 0.0;
   out_6930602079968694147[319] = 0.0;
   out_6930602079968694147[320] = 0.0;
   out_6930602079968694147[321] = 0.0;
   out_6930602079968694147[322] = 0.0;
   out_6930602079968694147[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_406523832625579260) {
   out_406523832625579260[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_406523832625579260[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_406523832625579260[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_406523832625579260[3] = dt*state[12] + state[3];
   out_406523832625579260[4] = dt*state[13] + state[4];
   out_406523832625579260[5] = dt*state[14] + state[5];
   out_406523832625579260[6] = state[6];
   out_406523832625579260[7] = state[7];
   out_406523832625579260[8] = state[8];
   out_406523832625579260[9] = state[9];
   out_406523832625579260[10] = state[10];
   out_406523832625579260[11] = state[11];
   out_406523832625579260[12] = state[12];
   out_406523832625579260[13] = state[13];
   out_406523832625579260[14] = state[14];
   out_406523832625579260[15] = state[15];
   out_406523832625579260[16] = state[16];
   out_406523832625579260[17] = state[17];
}
void F_fun(double *state, double dt, double *out_848753936125427471) {
   out_848753936125427471[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_848753936125427471[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_848753936125427471[2] = 0;
   out_848753936125427471[3] = 0;
   out_848753936125427471[4] = 0;
   out_848753936125427471[5] = 0;
   out_848753936125427471[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_848753936125427471[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_848753936125427471[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_848753936125427471[9] = 0;
   out_848753936125427471[10] = 0;
   out_848753936125427471[11] = 0;
   out_848753936125427471[12] = 0;
   out_848753936125427471[13] = 0;
   out_848753936125427471[14] = 0;
   out_848753936125427471[15] = 0;
   out_848753936125427471[16] = 0;
   out_848753936125427471[17] = 0;
   out_848753936125427471[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_848753936125427471[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_848753936125427471[20] = 0;
   out_848753936125427471[21] = 0;
   out_848753936125427471[22] = 0;
   out_848753936125427471[23] = 0;
   out_848753936125427471[24] = 0;
   out_848753936125427471[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_848753936125427471[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_848753936125427471[27] = 0;
   out_848753936125427471[28] = 0;
   out_848753936125427471[29] = 0;
   out_848753936125427471[30] = 0;
   out_848753936125427471[31] = 0;
   out_848753936125427471[32] = 0;
   out_848753936125427471[33] = 0;
   out_848753936125427471[34] = 0;
   out_848753936125427471[35] = 0;
   out_848753936125427471[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_848753936125427471[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_848753936125427471[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_848753936125427471[39] = 0;
   out_848753936125427471[40] = 0;
   out_848753936125427471[41] = 0;
   out_848753936125427471[42] = 0;
   out_848753936125427471[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_848753936125427471[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_848753936125427471[45] = 0;
   out_848753936125427471[46] = 0;
   out_848753936125427471[47] = 0;
   out_848753936125427471[48] = 0;
   out_848753936125427471[49] = 0;
   out_848753936125427471[50] = 0;
   out_848753936125427471[51] = 0;
   out_848753936125427471[52] = 0;
   out_848753936125427471[53] = 0;
   out_848753936125427471[54] = 0;
   out_848753936125427471[55] = 0;
   out_848753936125427471[56] = 0;
   out_848753936125427471[57] = 1;
   out_848753936125427471[58] = 0;
   out_848753936125427471[59] = 0;
   out_848753936125427471[60] = 0;
   out_848753936125427471[61] = 0;
   out_848753936125427471[62] = 0;
   out_848753936125427471[63] = 0;
   out_848753936125427471[64] = 0;
   out_848753936125427471[65] = 0;
   out_848753936125427471[66] = dt;
   out_848753936125427471[67] = 0;
   out_848753936125427471[68] = 0;
   out_848753936125427471[69] = 0;
   out_848753936125427471[70] = 0;
   out_848753936125427471[71] = 0;
   out_848753936125427471[72] = 0;
   out_848753936125427471[73] = 0;
   out_848753936125427471[74] = 0;
   out_848753936125427471[75] = 0;
   out_848753936125427471[76] = 1;
   out_848753936125427471[77] = 0;
   out_848753936125427471[78] = 0;
   out_848753936125427471[79] = 0;
   out_848753936125427471[80] = 0;
   out_848753936125427471[81] = 0;
   out_848753936125427471[82] = 0;
   out_848753936125427471[83] = 0;
   out_848753936125427471[84] = 0;
   out_848753936125427471[85] = dt;
   out_848753936125427471[86] = 0;
   out_848753936125427471[87] = 0;
   out_848753936125427471[88] = 0;
   out_848753936125427471[89] = 0;
   out_848753936125427471[90] = 0;
   out_848753936125427471[91] = 0;
   out_848753936125427471[92] = 0;
   out_848753936125427471[93] = 0;
   out_848753936125427471[94] = 0;
   out_848753936125427471[95] = 1;
   out_848753936125427471[96] = 0;
   out_848753936125427471[97] = 0;
   out_848753936125427471[98] = 0;
   out_848753936125427471[99] = 0;
   out_848753936125427471[100] = 0;
   out_848753936125427471[101] = 0;
   out_848753936125427471[102] = 0;
   out_848753936125427471[103] = 0;
   out_848753936125427471[104] = dt;
   out_848753936125427471[105] = 0;
   out_848753936125427471[106] = 0;
   out_848753936125427471[107] = 0;
   out_848753936125427471[108] = 0;
   out_848753936125427471[109] = 0;
   out_848753936125427471[110] = 0;
   out_848753936125427471[111] = 0;
   out_848753936125427471[112] = 0;
   out_848753936125427471[113] = 0;
   out_848753936125427471[114] = 1;
   out_848753936125427471[115] = 0;
   out_848753936125427471[116] = 0;
   out_848753936125427471[117] = 0;
   out_848753936125427471[118] = 0;
   out_848753936125427471[119] = 0;
   out_848753936125427471[120] = 0;
   out_848753936125427471[121] = 0;
   out_848753936125427471[122] = 0;
   out_848753936125427471[123] = 0;
   out_848753936125427471[124] = 0;
   out_848753936125427471[125] = 0;
   out_848753936125427471[126] = 0;
   out_848753936125427471[127] = 0;
   out_848753936125427471[128] = 0;
   out_848753936125427471[129] = 0;
   out_848753936125427471[130] = 0;
   out_848753936125427471[131] = 0;
   out_848753936125427471[132] = 0;
   out_848753936125427471[133] = 1;
   out_848753936125427471[134] = 0;
   out_848753936125427471[135] = 0;
   out_848753936125427471[136] = 0;
   out_848753936125427471[137] = 0;
   out_848753936125427471[138] = 0;
   out_848753936125427471[139] = 0;
   out_848753936125427471[140] = 0;
   out_848753936125427471[141] = 0;
   out_848753936125427471[142] = 0;
   out_848753936125427471[143] = 0;
   out_848753936125427471[144] = 0;
   out_848753936125427471[145] = 0;
   out_848753936125427471[146] = 0;
   out_848753936125427471[147] = 0;
   out_848753936125427471[148] = 0;
   out_848753936125427471[149] = 0;
   out_848753936125427471[150] = 0;
   out_848753936125427471[151] = 0;
   out_848753936125427471[152] = 1;
   out_848753936125427471[153] = 0;
   out_848753936125427471[154] = 0;
   out_848753936125427471[155] = 0;
   out_848753936125427471[156] = 0;
   out_848753936125427471[157] = 0;
   out_848753936125427471[158] = 0;
   out_848753936125427471[159] = 0;
   out_848753936125427471[160] = 0;
   out_848753936125427471[161] = 0;
   out_848753936125427471[162] = 0;
   out_848753936125427471[163] = 0;
   out_848753936125427471[164] = 0;
   out_848753936125427471[165] = 0;
   out_848753936125427471[166] = 0;
   out_848753936125427471[167] = 0;
   out_848753936125427471[168] = 0;
   out_848753936125427471[169] = 0;
   out_848753936125427471[170] = 0;
   out_848753936125427471[171] = 1;
   out_848753936125427471[172] = 0;
   out_848753936125427471[173] = 0;
   out_848753936125427471[174] = 0;
   out_848753936125427471[175] = 0;
   out_848753936125427471[176] = 0;
   out_848753936125427471[177] = 0;
   out_848753936125427471[178] = 0;
   out_848753936125427471[179] = 0;
   out_848753936125427471[180] = 0;
   out_848753936125427471[181] = 0;
   out_848753936125427471[182] = 0;
   out_848753936125427471[183] = 0;
   out_848753936125427471[184] = 0;
   out_848753936125427471[185] = 0;
   out_848753936125427471[186] = 0;
   out_848753936125427471[187] = 0;
   out_848753936125427471[188] = 0;
   out_848753936125427471[189] = 0;
   out_848753936125427471[190] = 1;
   out_848753936125427471[191] = 0;
   out_848753936125427471[192] = 0;
   out_848753936125427471[193] = 0;
   out_848753936125427471[194] = 0;
   out_848753936125427471[195] = 0;
   out_848753936125427471[196] = 0;
   out_848753936125427471[197] = 0;
   out_848753936125427471[198] = 0;
   out_848753936125427471[199] = 0;
   out_848753936125427471[200] = 0;
   out_848753936125427471[201] = 0;
   out_848753936125427471[202] = 0;
   out_848753936125427471[203] = 0;
   out_848753936125427471[204] = 0;
   out_848753936125427471[205] = 0;
   out_848753936125427471[206] = 0;
   out_848753936125427471[207] = 0;
   out_848753936125427471[208] = 0;
   out_848753936125427471[209] = 1;
   out_848753936125427471[210] = 0;
   out_848753936125427471[211] = 0;
   out_848753936125427471[212] = 0;
   out_848753936125427471[213] = 0;
   out_848753936125427471[214] = 0;
   out_848753936125427471[215] = 0;
   out_848753936125427471[216] = 0;
   out_848753936125427471[217] = 0;
   out_848753936125427471[218] = 0;
   out_848753936125427471[219] = 0;
   out_848753936125427471[220] = 0;
   out_848753936125427471[221] = 0;
   out_848753936125427471[222] = 0;
   out_848753936125427471[223] = 0;
   out_848753936125427471[224] = 0;
   out_848753936125427471[225] = 0;
   out_848753936125427471[226] = 0;
   out_848753936125427471[227] = 0;
   out_848753936125427471[228] = 1;
   out_848753936125427471[229] = 0;
   out_848753936125427471[230] = 0;
   out_848753936125427471[231] = 0;
   out_848753936125427471[232] = 0;
   out_848753936125427471[233] = 0;
   out_848753936125427471[234] = 0;
   out_848753936125427471[235] = 0;
   out_848753936125427471[236] = 0;
   out_848753936125427471[237] = 0;
   out_848753936125427471[238] = 0;
   out_848753936125427471[239] = 0;
   out_848753936125427471[240] = 0;
   out_848753936125427471[241] = 0;
   out_848753936125427471[242] = 0;
   out_848753936125427471[243] = 0;
   out_848753936125427471[244] = 0;
   out_848753936125427471[245] = 0;
   out_848753936125427471[246] = 0;
   out_848753936125427471[247] = 1;
   out_848753936125427471[248] = 0;
   out_848753936125427471[249] = 0;
   out_848753936125427471[250] = 0;
   out_848753936125427471[251] = 0;
   out_848753936125427471[252] = 0;
   out_848753936125427471[253] = 0;
   out_848753936125427471[254] = 0;
   out_848753936125427471[255] = 0;
   out_848753936125427471[256] = 0;
   out_848753936125427471[257] = 0;
   out_848753936125427471[258] = 0;
   out_848753936125427471[259] = 0;
   out_848753936125427471[260] = 0;
   out_848753936125427471[261] = 0;
   out_848753936125427471[262] = 0;
   out_848753936125427471[263] = 0;
   out_848753936125427471[264] = 0;
   out_848753936125427471[265] = 0;
   out_848753936125427471[266] = 1;
   out_848753936125427471[267] = 0;
   out_848753936125427471[268] = 0;
   out_848753936125427471[269] = 0;
   out_848753936125427471[270] = 0;
   out_848753936125427471[271] = 0;
   out_848753936125427471[272] = 0;
   out_848753936125427471[273] = 0;
   out_848753936125427471[274] = 0;
   out_848753936125427471[275] = 0;
   out_848753936125427471[276] = 0;
   out_848753936125427471[277] = 0;
   out_848753936125427471[278] = 0;
   out_848753936125427471[279] = 0;
   out_848753936125427471[280] = 0;
   out_848753936125427471[281] = 0;
   out_848753936125427471[282] = 0;
   out_848753936125427471[283] = 0;
   out_848753936125427471[284] = 0;
   out_848753936125427471[285] = 1;
   out_848753936125427471[286] = 0;
   out_848753936125427471[287] = 0;
   out_848753936125427471[288] = 0;
   out_848753936125427471[289] = 0;
   out_848753936125427471[290] = 0;
   out_848753936125427471[291] = 0;
   out_848753936125427471[292] = 0;
   out_848753936125427471[293] = 0;
   out_848753936125427471[294] = 0;
   out_848753936125427471[295] = 0;
   out_848753936125427471[296] = 0;
   out_848753936125427471[297] = 0;
   out_848753936125427471[298] = 0;
   out_848753936125427471[299] = 0;
   out_848753936125427471[300] = 0;
   out_848753936125427471[301] = 0;
   out_848753936125427471[302] = 0;
   out_848753936125427471[303] = 0;
   out_848753936125427471[304] = 1;
   out_848753936125427471[305] = 0;
   out_848753936125427471[306] = 0;
   out_848753936125427471[307] = 0;
   out_848753936125427471[308] = 0;
   out_848753936125427471[309] = 0;
   out_848753936125427471[310] = 0;
   out_848753936125427471[311] = 0;
   out_848753936125427471[312] = 0;
   out_848753936125427471[313] = 0;
   out_848753936125427471[314] = 0;
   out_848753936125427471[315] = 0;
   out_848753936125427471[316] = 0;
   out_848753936125427471[317] = 0;
   out_848753936125427471[318] = 0;
   out_848753936125427471[319] = 0;
   out_848753936125427471[320] = 0;
   out_848753936125427471[321] = 0;
   out_848753936125427471[322] = 0;
   out_848753936125427471[323] = 1;
}
void h_4(double *state, double *unused, double *out_8157496129265217886) {
   out_8157496129265217886[0] = state[6] + state[9];
   out_8157496129265217886[1] = state[7] + state[10];
   out_8157496129265217886[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_1170939759003718403) {
   out_1170939759003718403[0] = 0;
   out_1170939759003718403[1] = 0;
   out_1170939759003718403[2] = 0;
   out_1170939759003718403[3] = 0;
   out_1170939759003718403[4] = 0;
   out_1170939759003718403[5] = 0;
   out_1170939759003718403[6] = 1;
   out_1170939759003718403[7] = 0;
   out_1170939759003718403[8] = 0;
   out_1170939759003718403[9] = 1;
   out_1170939759003718403[10] = 0;
   out_1170939759003718403[11] = 0;
   out_1170939759003718403[12] = 0;
   out_1170939759003718403[13] = 0;
   out_1170939759003718403[14] = 0;
   out_1170939759003718403[15] = 0;
   out_1170939759003718403[16] = 0;
   out_1170939759003718403[17] = 0;
   out_1170939759003718403[18] = 0;
   out_1170939759003718403[19] = 0;
   out_1170939759003718403[20] = 0;
   out_1170939759003718403[21] = 0;
   out_1170939759003718403[22] = 0;
   out_1170939759003718403[23] = 0;
   out_1170939759003718403[24] = 0;
   out_1170939759003718403[25] = 1;
   out_1170939759003718403[26] = 0;
   out_1170939759003718403[27] = 0;
   out_1170939759003718403[28] = 1;
   out_1170939759003718403[29] = 0;
   out_1170939759003718403[30] = 0;
   out_1170939759003718403[31] = 0;
   out_1170939759003718403[32] = 0;
   out_1170939759003718403[33] = 0;
   out_1170939759003718403[34] = 0;
   out_1170939759003718403[35] = 0;
   out_1170939759003718403[36] = 0;
   out_1170939759003718403[37] = 0;
   out_1170939759003718403[38] = 0;
   out_1170939759003718403[39] = 0;
   out_1170939759003718403[40] = 0;
   out_1170939759003718403[41] = 0;
   out_1170939759003718403[42] = 0;
   out_1170939759003718403[43] = 0;
   out_1170939759003718403[44] = 1;
   out_1170939759003718403[45] = 0;
   out_1170939759003718403[46] = 0;
   out_1170939759003718403[47] = 1;
   out_1170939759003718403[48] = 0;
   out_1170939759003718403[49] = 0;
   out_1170939759003718403[50] = 0;
   out_1170939759003718403[51] = 0;
   out_1170939759003718403[52] = 0;
   out_1170939759003718403[53] = 0;
}
void h_10(double *state, double *unused, double *out_2237221901333140328) {
   out_2237221901333140328[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2237221901333140328[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2237221901333140328[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_9147651789234380968) {
   out_9147651789234380968[0] = 0;
   out_9147651789234380968[1] = 9.8100000000000005*cos(state[1]);
   out_9147651789234380968[2] = 0;
   out_9147651789234380968[3] = 0;
   out_9147651789234380968[4] = -state[8];
   out_9147651789234380968[5] = state[7];
   out_9147651789234380968[6] = 0;
   out_9147651789234380968[7] = state[5];
   out_9147651789234380968[8] = -state[4];
   out_9147651789234380968[9] = 0;
   out_9147651789234380968[10] = 0;
   out_9147651789234380968[11] = 0;
   out_9147651789234380968[12] = 1;
   out_9147651789234380968[13] = 0;
   out_9147651789234380968[14] = 0;
   out_9147651789234380968[15] = 1;
   out_9147651789234380968[16] = 0;
   out_9147651789234380968[17] = 0;
   out_9147651789234380968[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_9147651789234380968[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_9147651789234380968[20] = 0;
   out_9147651789234380968[21] = state[8];
   out_9147651789234380968[22] = 0;
   out_9147651789234380968[23] = -state[6];
   out_9147651789234380968[24] = -state[5];
   out_9147651789234380968[25] = 0;
   out_9147651789234380968[26] = state[3];
   out_9147651789234380968[27] = 0;
   out_9147651789234380968[28] = 0;
   out_9147651789234380968[29] = 0;
   out_9147651789234380968[30] = 0;
   out_9147651789234380968[31] = 1;
   out_9147651789234380968[32] = 0;
   out_9147651789234380968[33] = 0;
   out_9147651789234380968[34] = 1;
   out_9147651789234380968[35] = 0;
   out_9147651789234380968[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_9147651789234380968[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_9147651789234380968[38] = 0;
   out_9147651789234380968[39] = -state[7];
   out_9147651789234380968[40] = state[6];
   out_9147651789234380968[41] = 0;
   out_9147651789234380968[42] = state[4];
   out_9147651789234380968[43] = -state[3];
   out_9147651789234380968[44] = 0;
   out_9147651789234380968[45] = 0;
   out_9147651789234380968[46] = 0;
   out_9147651789234380968[47] = 0;
   out_9147651789234380968[48] = 0;
   out_9147651789234380968[49] = 0;
   out_9147651789234380968[50] = 1;
   out_9147651789234380968[51] = 0;
   out_9147651789234380968[52] = 0;
   out_9147651789234380968[53] = 1;
}
void h_13(double *state, double *unused, double *out_5159652440714071710) {
   out_5159652440714071710[0] = state[3];
   out_5159652440714071710[1] = state[4];
   out_5159652440714071710[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2041334066328614398) {
   out_2041334066328614398[0] = 0;
   out_2041334066328614398[1] = 0;
   out_2041334066328614398[2] = 0;
   out_2041334066328614398[3] = 1;
   out_2041334066328614398[4] = 0;
   out_2041334066328614398[5] = 0;
   out_2041334066328614398[6] = 0;
   out_2041334066328614398[7] = 0;
   out_2041334066328614398[8] = 0;
   out_2041334066328614398[9] = 0;
   out_2041334066328614398[10] = 0;
   out_2041334066328614398[11] = 0;
   out_2041334066328614398[12] = 0;
   out_2041334066328614398[13] = 0;
   out_2041334066328614398[14] = 0;
   out_2041334066328614398[15] = 0;
   out_2041334066328614398[16] = 0;
   out_2041334066328614398[17] = 0;
   out_2041334066328614398[18] = 0;
   out_2041334066328614398[19] = 0;
   out_2041334066328614398[20] = 0;
   out_2041334066328614398[21] = 0;
   out_2041334066328614398[22] = 1;
   out_2041334066328614398[23] = 0;
   out_2041334066328614398[24] = 0;
   out_2041334066328614398[25] = 0;
   out_2041334066328614398[26] = 0;
   out_2041334066328614398[27] = 0;
   out_2041334066328614398[28] = 0;
   out_2041334066328614398[29] = 0;
   out_2041334066328614398[30] = 0;
   out_2041334066328614398[31] = 0;
   out_2041334066328614398[32] = 0;
   out_2041334066328614398[33] = 0;
   out_2041334066328614398[34] = 0;
   out_2041334066328614398[35] = 0;
   out_2041334066328614398[36] = 0;
   out_2041334066328614398[37] = 0;
   out_2041334066328614398[38] = 0;
   out_2041334066328614398[39] = 0;
   out_2041334066328614398[40] = 0;
   out_2041334066328614398[41] = 1;
   out_2041334066328614398[42] = 0;
   out_2041334066328614398[43] = 0;
   out_2041334066328614398[44] = 0;
   out_2041334066328614398[45] = 0;
   out_2041334066328614398[46] = 0;
   out_2041334066328614398[47] = 0;
   out_2041334066328614398[48] = 0;
   out_2041334066328614398[49] = 0;
   out_2041334066328614398[50] = 0;
   out_2041334066328614398[51] = 0;
   out_2041334066328614398[52] = 0;
   out_2041334066328614398[53] = 0;
}
void h_14(double *state, double *unused, double *out_4170635472713662169) {
   out_4170635472713662169[0] = state[6];
   out_4170635472713662169[1] = state[7];
   out_4170635472713662169[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2792301097335766126) {
   out_2792301097335766126[0] = 0;
   out_2792301097335766126[1] = 0;
   out_2792301097335766126[2] = 0;
   out_2792301097335766126[3] = 0;
   out_2792301097335766126[4] = 0;
   out_2792301097335766126[5] = 0;
   out_2792301097335766126[6] = 1;
   out_2792301097335766126[7] = 0;
   out_2792301097335766126[8] = 0;
   out_2792301097335766126[9] = 0;
   out_2792301097335766126[10] = 0;
   out_2792301097335766126[11] = 0;
   out_2792301097335766126[12] = 0;
   out_2792301097335766126[13] = 0;
   out_2792301097335766126[14] = 0;
   out_2792301097335766126[15] = 0;
   out_2792301097335766126[16] = 0;
   out_2792301097335766126[17] = 0;
   out_2792301097335766126[18] = 0;
   out_2792301097335766126[19] = 0;
   out_2792301097335766126[20] = 0;
   out_2792301097335766126[21] = 0;
   out_2792301097335766126[22] = 0;
   out_2792301097335766126[23] = 0;
   out_2792301097335766126[24] = 0;
   out_2792301097335766126[25] = 1;
   out_2792301097335766126[26] = 0;
   out_2792301097335766126[27] = 0;
   out_2792301097335766126[28] = 0;
   out_2792301097335766126[29] = 0;
   out_2792301097335766126[30] = 0;
   out_2792301097335766126[31] = 0;
   out_2792301097335766126[32] = 0;
   out_2792301097335766126[33] = 0;
   out_2792301097335766126[34] = 0;
   out_2792301097335766126[35] = 0;
   out_2792301097335766126[36] = 0;
   out_2792301097335766126[37] = 0;
   out_2792301097335766126[38] = 0;
   out_2792301097335766126[39] = 0;
   out_2792301097335766126[40] = 0;
   out_2792301097335766126[41] = 0;
   out_2792301097335766126[42] = 0;
   out_2792301097335766126[43] = 0;
   out_2792301097335766126[44] = 1;
   out_2792301097335766126[45] = 0;
   out_2792301097335766126[46] = 0;
   out_2792301097335766126[47] = 0;
   out_2792301097335766126[48] = 0;
   out_2792301097335766126[49] = 0;
   out_2792301097335766126[50] = 0;
   out_2792301097335766126[51] = 0;
   out_2792301097335766126[52] = 0;
   out_2792301097335766126[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_8800160146285448971) {
  err_fun(nom_x, delta_x, out_8800160146285448971);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3072673840862845580) {
  inv_err_fun(nom_x, true_x, out_3072673840862845580);
}
void pose_H_mod_fun(double *state, double *out_6930602079968694147) {
  H_mod_fun(state, out_6930602079968694147);
}
void pose_f_fun(double *state, double dt, double *out_406523832625579260) {
  f_fun(state,  dt, out_406523832625579260);
}
void pose_F_fun(double *state, double dt, double *out_848753936125427471) {
  F_fun(state,  dt, out_848753936125427471);
}
void pose_h_4(double *state, double *unused, double *out_8157496129265217886) {
  h_4(state, unused, out_8157496129265217886);
}
void pose_H_4(double *state, double *unused, double *out_1170939759003718403) {
  H_4(state, unused, out_1170939759003718403);
}
void pose_h_10(double *state, double *unused, double *out_2237221901333140328) {
  h_10(state, unused, out_2237221901333140328);
}
void pose_H_10(double *state, double *unused, double *out_9147651789234380968) {
  H_10(state, unused, out_9147651789234380968);
}
void pose_h_13(double *state, double *unused, double *out_5159652440714071710) {
  h_13(state, unused, out_5159652440714071710);
}
void pose_H_13(double *state, double *unused, double *out_2041334066328614398) {
  H_13(state, unused, out_2041334066328614398);
}
void pose_h_14(double *state, double *unused, double *out_4170635472713662169) {
  h_14(state, unused, out_4170635472713662169);
}
void pose_H_14(double *state, double *unused, double *out_2792301097335766126) {
  H_14(state, unused, out_2792301097335766126);
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
