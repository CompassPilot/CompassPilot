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
void err_fun(double *nom_x, double *delta_x, double *out_3291478583356534624) {
   out_3291478583356534624[0] = delta_x[0] + nom_x[0];
   out_3291478583356534624[1] = delta_x[1] + nom_x[1];
   out_3291478583356534624[2] = delta_x[2] + nom_x[2];
   out_3291478583356534624[3] = delta_x[3] + nom_x[3];
   out_3291478583356534624[4] = delta_x[4] + nom_x[4];
   out_3291478583356534624[5] = delta_x[5] + nom_x[5];
   out_3291478583356534624[6] = delta_x[6] + nom_x[6];
   out_3291478583356534624[7] = delta_x[7] + nom_x[7];
   out_3291478583356534624[8] = delta_x[8] + nom_x[8];
   out_3291478583356534624[9] = delta_x[9] + nom_x[9];
   out_3291478583356534624[10] = delta_x[10] + nom_x[10];
   out_3291478583356534624[11] = delta_x[11] + nom_x[11];
   out_3291478583356534624[12] = delta_x[12] + nom_x[12];
   out_3291478583356534624[13] = delta_x[13] + nom_x[13];
   out_3291478583356534624[14] = delta_x[14] + nom_x[14];
   out_3291478583356534624[15] = delta_x[15] + nom_x[15];
   out_3291478583356534624[16] = delta_x[16] + nom_x[16];
   out_3291478583356534624[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8622738967567708549) {
   out_8622738967567708549[0] = -nom_x[0] + true_x[0];
   out_8622738967567708549[1] = -nom_x[1] + true_x[1];
   out_8622738967567708549[2] = -nom_x[2] + true_x[2];
   out_8622738967567708549[3] = -nom_x[3] + true_x[3];
   out_8622738967567708549[4] = -nom_x[4] + true_x[4];
   out_8622738967567708549[5] = -nom_x[5] + true_x[5];
   out_8622738967567708549[6] = -nom_x[6] + true_x[6];
   out_8622738967567708549[7] = -nom_x[7] + true_x[7];
   out_8622738967567708549[8] = -nom_x[8] + true_x[8];
   out_8622738967567708549[9] = -nom_x[9] + true_x[9];
   out_8622738967567708549[10] = -nom_x[10] + true_x[10];
   out_8622738967567708549[11] = -nom_x[11] + true_x[11];
   out_8622738967567708549[12] = -nom_x[12] + true_x[12];
   out_8622738967567708549[13] = -nom_x[13] + true_x[13];
   out_8622738967567708549[14] = -nom_x[14] + true_x[14];
   out_8622738967567708549[15] = -nom_x[15] + true_x[15];
   out_8622738967567708549[16] = -nom_x[16] + true_x[16];
   out_8622738967567708549[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_4432635606321955062) {
   out_4432635606321955062[0] = 1.0;
   out_4432635606321955062[1] = 0.0;
   out_4432635606321955062[2] = 0.0;
   out_4432635606321955062[3] = 0.0;
   out_4432635606321955062[4] = 0.0;
   out_4432635606321955062[5] = 0.0;
   out_4432635606321955062[6] = 0.0;
   out_4432635606321955062[7] = 0.0;
   out_4432635606321955062[8] = 0.0;
   out_4432635606321955062[9] = 0.0;
   out_4432635606321955062[10] = 0.0;
   out_4432635606321955062[11] = 0.0;
   out_4432635606321955062[12] = 0.0;
   out_4432635606321955062[13] = 0.0;
   out_4432635606321955062[14] = 0.0;
   out_4432635606321955062[15] = 0.0;
   out_4432635606321955062[16] = 0.0;
   out_4432635606321955062[17] = 0.0;
   out_4432635606321955062[18] = 0.0;
   out_4432635606321955062[19] = 1.0;
   out_4432635606321955062[20] = 0.0;
   out_4432635606321955062[21] = 0.0;
   out_4432635606321955062[22] = 0.0;
   out_4432635606321955062[23] = 0.0;
   out_4432635606321955062[24] = 0.0;
   out_4432635606321955062[25] = 0.0;
   out_4432635606321955062[26] = 0.0;
   out_4432635606321955062[27] = 0.0;
   out_4432635606321955062[28] = 0.0;
   out_4432635606321955062[29] = 0.0;
   out_4432635606321955062[30] = 0.0;
   out_4432635606321955062[31] = 0.0;
   out_4432635606321955062[32] = 0.0;
   out_4432635606321955062[33] = 0.0;
   out_4432635606321955062[34] = 0.0;
   out_4432635606321955062[35] = 0.0;
   out_4432635606321955062[36] = 0.0;
   out_4432635606321955062[37] = 0.0;
   out_4432635606321955062[38] = 1.0;
   out_4432635606321955062[39] = 0.0;
   out_4432635606321955062[40] = 0.0;
   out_4432635606321955062[41] = 0.0;
   out_4432635606321955062[42] = 0.0;
   out_4432635606321955062[43] = 0.0;
   out_4432635606321955062[44] = 0.0;
   out_4432635606321955062[45] = 0.0;
   out_4432635606321955062[46] = 0.0;
   out_4432635606321955062[47] = 0.0;
   out_4432635606321955062[48] = 0.0;
   out_4432635606321955062[49] = 0.0;
   out_4432635606321955062[50] = 0.0;
   out_4432635606321955062[51] = 0.0;
   out_4432635606321955062[52] = 0.0;
   out_4432635606321955062[53] = 0.0;
   out_4432635606321955062[54] = 0.0;
   out_4432635606321955062[55] = 0.0;
   out_4432635606321955062[56] = 0.0;
   out_4432635606321955062[57] = 1.0;
   out_4432635606321955062[58] = 0.0;
   out_4432635606321955062[59] = 0.0;
   out_4432635606321955062[60] = 0.0;
   out_4432635606321955062[61] = 0.0;
   out_4432635606321955062[62] = 0.0;
   out_4432635606321955062[63] = 0.0;
   out_4432635606321955062[64] = 0.0;
   out_4432635606321955062[65] = 0.0;
   out_4432635606321955062[66] = 0.0;
   out_4432635606321955062[67] = 0.0;
   out_4432635606321955062[68] = 0.0;
   out_4432635606321955062[69] = 0.0;
   out_4432635606321955062[70] = 0.0;
   out_4432635606321955062[71] = 0.0;
   out_4432635606321955062[72] = 0.0;
   out_4432635606321955062[73] = 0.0;
   out_4432635606321955062[74] = 0.0;
   out_4432635606321955062[75] = 0.0;
   out_4432635606321955062[76] = 1.0;
   out_4432635606321955062[77] = 0.0;
   out_4432635606321955062[78] = 0.0;
   out_4432635606321955062[79] = 0.0;
   out_4432635606321955062[80] = 0.0;
   out_4432635606321955062[81] = 0.0;
   out_4432635606321955062[82] = 0.0;
   out_4432635606321955062[83] = 0.0;
   out_4432635606321955062[84] = 0.0;
   out_4432635606321955062[85] = 0.0;
   out_4432635606321955062[86] = 0.0;
   out_4432635606321955062[87] = 0.0;
   out_4432635606321955062[88] = 0.0;
   out_4432635606321955062[89] = 0.0;
   out_4432635606321955062[90] = 0.0;
   out_4432635606321955062[91] = 0.0;
   out_4432635606321955062[92] = 0.0;
   out_4432635606321955062[93] = 0.0;
   out_4432635606321955062[94] = 0.0;
   out_4432635606321955062[95] = 1.0;
   out_4432635606321955062[96] = 0.0;
   out_4432635606321955062[97] = 0.0;
   out_4432635606321955062[98] = 0.0;
   out_4432635606321955062[99] = 0.0;
   out_4432635606321955062[100] = 0.0;
   out_4432635606321955062[101] = 0.0;
   out_4432635606321955062[102] = 0.0;
   out_4432635606321955062[103] = 0.0;
   out_4432635606321955062[104] = 0.0;
   out_4432635606321955062[105] = 0.0;
   out_4432635606321955062[106] = 0.0;
   out_4432635606321955062[107] = 0.0;
   out_4432635606321955062[108] = 0.0;
   out_4432635606321955062[109] = 0.0;
   out_4432635606321955062[110] = 0.0;
   out_4432635606321955062[111] = 0.0;
   out_4432635606321955062[112] = 0.0;
   out_4432635606321955062[113] = 0.0;
   out_4432635606321955062[114] = 1.0;
   out_4432635606321955062[115] = 0.0;
   out_4432635606321955062[116] = 0.0;
   out_4432635606321955062[117] = 0.0;
   out_4432635606321955062[118] = 0.0;
   out_4432635606321955062[119] = 0.0;
   out_4432635606321955062[120] = 0.0;
   out_4432635606321955062[121] = 0.0;
   out_4432635606321955062[122] = 0.0;
   out_4432635606321955062[123] = 0.0;
   out_4432635606321955062[124] = 0.0;
   out_4432635606321955062[125] = 0.0;
   out_4432635606321955062[126] = 0.0;
   out_4432635606321955062[127] = 0.0;
   out_4432635606321955062[128] = 0.0;
   out_4432635606321955062[129] = 0.0;
   out_4432635606321955062[130] = 0.0;
   out_4432635606321955062[131] = 0.0;
   out_4432635606321955062[132] = 0.0;
   out_4432635606321955062[133] = 1.0;
   out_4432635606321955062[134] = 0.0;
   out_4432635606321955062[135] = 0.0;
   out_4432635606321955062[136] = 0.0;
   out_4432635606321955062[137] = 0.0;
   out_4432635606321955062[138] = 0.0;
   out_4432635606321955062[139] = 0.0;
   out_4432635606321955062[140] = 0.0;
   out_4432635606321955062[141] = 0.0;
   out_4432635606321955062[142] = 0.0;
   out_4432635606321955062[143] = 0.0;
   out_4432635606321955062[144] = 0.0;
   out_4432635606321955062[145] = 0.0;
   out_4432635606321955062[146] = 0.0;
   out_4432635606321955062[147] = 0.0;
   out_4432635606321955062[148] = 0.0;
   out_4432635606321955062[149] = 0.0;
   out_4432635606321955062[150] = 0.0;
   out_4432635606321955062[151] = 0.0;
   out_4432635606321955062[152] = 1.0;
   out_4432635606321955062[153] = 0.0;
   out_4432635606321955062[154] = 0.0;
   out_4432635606321955062[155] = 0.0;
   out_4432635606321955062[156] = 0.0;
   out_4432635606321955062[157] = 0.0;
   out_4432635606321955062[158] = 0.0;
   out_4432635606321955062[159] = 0.0;
   out_4432635606321955062[160] = 0.0;
   out_4432635606321955062[161] = 0.0;
   out_4432635606321955062[162] = 0.0;
   out_4432635606321955062[163] = 0.0;
   out_4432635606321955062[164] = 0.0;
   out_4432635606321955062[165] = 0.0;
   out_4432635606321955062[166] = 0.0;
   out_4432635606321955062[167] = 0.0;
   out_4432635606321955062[168] = 0.0;
   out_4432635606321955062[169] = 0.0;
   out_4432635606321955062[170] = 0.0;
   out_4432635606321955062[171] = 1.0;
   out_4432635606321955062[172] = 0.0;
   out_4432635606321955062[173] = 0.0;
   out_4432635606321955062[174] = 0.0;
   out_4432635606321955062[175] = 0.0;
   out_4432635606321955062[176] = 0.0;
   out_4432635606321955062[177] = 0.0;
   out_4432635606321955062[178] = 0.0;
   out_4432635606321955062[179] = 0.0;
   out_4432635606321955062[180] = 0.0;
   out_4432635606321955062[181] = 0.0;
   out_4432635606321955062[182] = 0.0;
   out_4432635606321955062[183] = 0.0;
   out_4432635606321955062[184] = 0.0;
   out_4432635606321955062[185] = 0.0;
   out_4432635606321955062[186] = 0.0;
   out_4432635606321955062[187] = 0.0;
   out_4432635606321955062[188] = 0.0;
   out_4432635606321955062[189] = 0.0;
   out_4432635606321955062[190] = 1.0;
   out_4432635606321955062[191] = 0.0;
   out_4432635606321955062[192] = 0.0;
   out_4432635606321955062[193] = 0.0;
   out_4432635606321955062[194] = 0.0;
   out_4432635606321955062[195] = 0.0;
   out_4432635606321955062[196] = 0.0;
   out_4432635606321955062[197] = 0.0;
   out_4432635606321955062[198] = 0.0;
   out_4432635606321955062[199] = 0.0;
   out_4432635606321955062[200] = 0.0;
   out_4432635606321955062[201] = 0.0;
   out_4432635606321955062[202] = 0.0;
   out_4432635606321955062[203] = 0.0;
   out_4432635606321955062[204] = 0.0;
   out_4432635606321955062[205] = 0.0;
   out_4432635606321955062[206] = 0.0;
   out_4432635606321955062[207] = 0.0;
   out_4432635606321955062[208] = 0.0;
   out_4432635606321955062[209] = 1.0;
   out_4432635606321955062[210] = 0.0;
   out_4432635606321955062[211] = 0.0;
   out_4432635606321955062[212] = 0.0;
   out_4432635606321955062[213] = 0.0;
   out_4432635606321955062[214] = 0.0;
   out_4432635606321955062[215] = 0.0;
   out_4432635606321955062[216] = 0.0;
   out_4432635606321955062[217] = 0.0;
   out_4432635606321955062[218] = 0.0;
   out_4432635606321955062[219] = 0.0;
   out_4432635606321955062[220] = 0.0;
   out_4432635606321955062[221] = 0.0;
   out_4432635606321955062[222] = 0.0;
   out_4432635606321955062[223] = 0.0;
   out_4432635606321955062[224] = 0.0;
   out_4432635606321955062[225] = 0.0;
   out_4432635606321955062[226] = 0.0;
   out_4432635606321955062[227] = 0.0;
   out_4432635606321955062[228] = 1.0;
   out_4432635606321955062[229] = 0.0;
   out_4432635606321955062[230] = 0.0;
   out_4432635606321955062[231] = 0.0;
   out_4432635606321955062[232] = 0.0;
   out_4432635606321955062[233] = 0.0;
   out_4432635606321955062[234] = 0.0;
   out_4432635606321955062[235] = 0.0;
   out_4432635606321955062[236] = 0.0;
   out_4432635606321955062[237] = 0.0;
   out_4432635606321955062[238] = 0.0;
   out_4432635606321955062[239] = 0.0;
   out_4432635606321955062[240] = 0.0;
   out_4432635606321955062[241] = 0.0;
   out_4432635606321955062[242] = 0.0;
   out_4432635606321955062[243] = 0.0;
   out_4432635606321955062[244] = 0.0;
   out_4432635606321955062[245] = 0.0;
   out_4432635606321955062[246] = 0.0;
   out_4432635606321955062[247] = 1.0;
   out_4432635606321955062[248] = 0.0;
   out_4432635606321955062[249] = 0.0;
   out_4432635606321955062[250] = 0.0;
   out_4432635606321955062[251] = 0.0;
   out_4432635606321955062[252] = 0.0;
   out_4432635606321955062[253] = 0.0;
   out_4432635606321955062[254] = 0.0;
   out_4432635606321955062[255] = 0.0;
   out_4432635606321955062[256] = 0.0;
   out_4432635606321955062[257] = 0.0;
   out_4432635606321955062[258] = 0.0;
   out_4432635606321955062[259] = 0.0;
   out_4432635606321955062[260] = 0.0;
   out_4432635606321955062[261] = 0.0;
   out_4432635606321955062[262] = 0.0;
   out_4432635606321955062[263] = 0.0;
   out_4432635606321955062[264] = 0.0;
   out_4432635606321955062[265] = 0.0;
   out_4432635606321955062[266] = 1.0;
   out_4432635606321955062[267] = 0.0;
   out_4432635606321955062[268] = 0.0;
   out_4432635606321955062[269] = 0.0;
   out_4432635606321955062[270] = 0.0;
   out_4432635606321955062[271] = 0.0;
   out_4432635606321955062[272] = 0.0;
   out_4432635606321955062[273] = 0.0;
   out_4432635606321955062[274] = 0.0;
   out_4432635606321955062[275] = 0.0;
   out_4432635606321955062[276] = 0.0;
   out_4432635606321955062[277] = 0.0;
   out_4432635606321955062[278] = 0.0;
   out_4432635606321955062[279] = 0.0;
   out_4432635606321955062[280] = 0.0;
   out_4432635606321955062[281] = 0.0;
   out_4432635606321955062[282] = 0.0;
   out_4432635606321955062[283] = 0.0;
   out_4432635606321955062[284] = 0.0;
   out_4432635606321955062[285] = 1.0;
   out_4432635606321955062[286] = 0.0;
   out_4432635606321955062[287] = 0.0;
   out_4432635606321955062[288] = 0.0;
   out_4432635606321955062[289] = 0.0;
   out_4432635606321955062[290] = 0.0;
   out_4432635606321955062[291] = 0.0;
   out_4432635606321955062[292] = 0.0;
   out_4432635606321955062[293] = 0.0;
   out_4432635606321955062[294] = 0.0;
   out_4432635606321955062[295] = 0.0;
   out_4432635606321955062[296] = 0.0;
   out_4432635606321955062[297] = 0.0;
   out_4432635606321955062[298] = 0.0;
   out_4432635606321955062[299] = 0.0;
   out_4432635606321955062[300] = 0.0;
   out_4432635606321955062[301] = 0.0;
   out_4432635606321955062[302] = 0.0;
   out_4432635606321955062[303] = 0.0;
   out_4432635606321955062[304] = 1.0;
   out_4432635606321955062[305] = 0.0;
   out_4432635606321955062[306] = 0.0;
   out_4432635606321955062[307] = 0.0;
   out_4432635606321955062[308] = 0.0;
   out_4432635606321955062[309] = 0.0;
   out_4432635606321955062[310] = 0.0;
   out_4432635606321955062[311] = 0.0;
   out_4432635606321955062[312] = 0.0;
   out_4432635606321955062[313] = 0.0;
   out_4432635606321955062[314] = 0.0;
   out_4432635606321955062[315] = 0.0;
   out_4432635606321955062[316] = 0.0;
   out_4432635606321955062[317] = 0.0;
   out_4432635606321955062[318] = 0.0;
   out_4432635606321955062[319] = 0.0;
   out_4432635606321955062[320] = 0.0;
   out_4432635606321955062[321] = 0.0;
   out_4432635606321955062[322] = 0.0;
   out_4432635606321955062[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_872598189031658011) {
   out_872598189031658011[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_872598189031658011[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_872598189031658011[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_872598189031658011[3] = dt*state[12] + state[3];
   out_872598189031658011[4] = dt*state[13] + state[4];
   out_872598189031658011[5] = dt*state[14] + state[5];
   out_872598189031658011[6] = state[6];
   out_872598189031658011[7] = state[7];
   out_872598189031658011[8] = state[8];
   out_872598189031658011[9] = state[9];
   out_872598189031658011[10] = state[10];
   out_872598189031658011[11] = state[11];
   out_872598189031658011[12] = state[12];
   out_872598189031658011[13] = state[13];
   out_872598189031658011[14] = state[14];
   out_872598189031658011[15] = state[15];
   out_872598189031658011[16] = state[16];
   out_872598189031658011[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2142823975635459713) {
   out_2142823975635459713[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2142823975635459713[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2142823975635459713[2] = 0;
   out_2142823975635459713[3] = 0;
   out_2142823975635459713[4] = 0;
   out_2142823975635459713[5] = 0;
   out_2142823975635459713[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2142823975635459713[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2142823975635459713[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2142823975635459713[9] = 0;
   out_2142823975635459713[10] = 0;
   out_2142823975635459713[11] = 0;
   out_2142823975635459713[12] = 0;
   out_2142823975635459713[13] = 0;
   out_2142823975635459713[14] = 0;
   out_2142823975635459713[15] = 0;
   out_2142823975635459713[16] = 0;
   out_2142823975635459713[17] = 0;
   out_2142823975635459713[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2142823975635459713[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2142823975635459713[20] = 0;
   out_2142823975635459713[21] = 0;
   out_2142823975635459713[22] = 0;
   out_2142823975635459713[23] = 0;
   out_2142823975635459713[24] = 0;
   out_2142823975635459713[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2142823975635459713[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2142823975635459713[27] = 0;
   out_2142823975635459713[28] = 0;
   out_2142823975635459713[29] = 0;
   out_2142823975635459713[30] = 0;
   out_2142823975635459713[31] = 0;
   out_2142823975635459713[32] = 0;
   out_2142823975635459713[33] = 0;
   out_2142823975635459713[34] = 0;
   out_2142823975635459713[35] = 0;
   out_2142823975635459713[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2142823975635459713[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2142823975635459713[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2142823975635459713[39] = 0;
   out_2142823975635459713[40] = 0;
   out_2142823975635459713[41] = 0;
   out_2142823975635459713[42] = 0;
   out_2142823975635459713[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2142823975635459713[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2142823975635459713[45] = 0;
   out_2142823975635459713[46] = 0;
   out_2142823975635459713[47] = 0;
   out_2142823975635459713[48] = 0;
   out_2142823975635459713[49] = 0;
   out_2142823975635459713[50] = 0;
   out_2142823975635459713[51] = 0;
   out_2142823975635459713[52] = 0;
   out_2142823975635459713[53] = 0;
   out_2142823975635459713[54] = 0;
   out_2142823975635459713[55] = 0;
   out_2142823975635459713[56] = 0;
   out_2142823975635459713[57] = 1;
   out_2142823975635459713[58] = 0;
   out_2142823975635459713[59] = 0;
   out_2142823975635459713[60] = 0;
   out_2142823975635459713[61] = 0;
   out_2142823975635459713[62] = 0;
   out_2142823975635459713[63] = 0;
   out_2142823975635459713[64] = 0;
   out_2142823975635459713[65] = 0;
   out_2142823975635459713[66] = dt;
   out_2142823975635459713[67] = 0;
   out_2142823975635459713[68] = 0;
   out_2142823975635459713[69] = 0;
   out_2142823975635459713[70] = 0;
   out_2142823975635459713[71] = 0;
   out_2142823975635459713[72] = 0;
   out_2142823975635459713[73] = 0;
   out_2142823975635459713[74] = 0;
   out_2142823975635459713[75] = 0;
   out_2142823975635459713[76] = 1;
   out_2142823975635459713[77] = 0;
   out_2142823975635459713[78] = 0;
   out_2142823975635459713[79] = 0;
   out_2142823975635459713[80] = 0;
   out_2142823975635459713[81] = 0;
   out_2142823975635459713[82] = 0;
   out_2142823975635459713[83] = 0;
   out_2142823975635459713[84] = 0;
   out_2142823975635459713[85] = dt;
   out_2142823975635459713[86] = 0;
   out_2142823975635459713[87] = 0;
   out_2142823975635459713[88] = 0;
   out_2142823975635459713[89] = 0;
   out_2142823975635459713[90] = 0;
   out_2142823975635459713[91] = 0;
   out_2142823975635459713[92] = 0;
   out_2142823975635459713[93] = 0;
   out_2142823975635459713[94] = 0;
   out_2142823975635459713[95] = 1;
   out_2142823975635459713[96] = 0;
   out_2142823975635459713[97] = 0;
   out_2142823975635459713[98] = 0;
   out_2142823975635459713[99] = 0;
   out_2142823975635459713[100] = 0;
   out_2142823975635459713[101] = 0;
   out_2142823975635459713[102] = 0;
   out_2142823975635459713[103] = 0;
   out_2142823975635459713[104] = dt;
   out_2142823975635459713[105] = 0;
   out_2142823975635459713[106] = 0;
   out_2142823975635459713[107] = 0;
   out_2142823975635459713[108] = 0;
   out_2142823975635459713[109] = 0;
   out_2142823975635459713[110] = 0;
   out_2142823975635459713[111] = 0;
   out_2142823975635459713[112] = 0;
   out_2142823975635459713[113] = 0;
   out_2142823975635459713[114] = 1;
   out_2142823975635459713[115] = 0;
   out_2142823975635459713[116] = 0;
   out_2142823975635459713[117] = 0;
   out_2142823975635459713[118] = 0;
   out_2142823975635459713[119] = 0;
   out_2142823975635459713[120] = 0;
   out_2142823975635459713[121] = 0;
   out_2142823975635459713[122] = 0;
   out_2142823975635459713[123] = 0;
   out_2142823975635459713[124] = 0;
   out_2142823975635459713[125] = 0;
   out_2142823975635459713[126] = 0;
   out_2142823975635459713[127] = 0;
   out_2142823975635459713[128] = 0;
   out_2142823975635459713[129] = 0;
   out_2142823975635459713[130] = 0;
   out_2142823975635459713[131] = 0;
   out_2142823975635459713[132] = 0;
   out_2142823975635459713[133] = 1;
   out_2142823975635459713[134] = 0;
   out_2142823975635459713[135] = 0;
   out_2142823975635459713[136] = 0;
   out_2142823975635459713[137] = 0;
   out_2142823975635459713[138] = 0;
   out_2142823975635459713[139] = 0;
   out_2142823975635459713[140] = 0;
   out_2142823975635459713[141] = 0;
   out_2142823975635459713[142] = 0;
   out_2142823975635459713[143] = 0;
   out_2142823975635459713[144] = 0;
   out_2142823975635459713[145] = 0;
   out_2142823975635459713[146] = 0;
   out_2142823975635459713[147] = 0;
   out_2142823975635459713[148] = 0;
   out_2142823975635459713[149] = 0;
   out_2142823975635459713[150] = 0;
   out_2142823975635459713[151] = 0;
   out_2142823975635459713[152] = 1;
   out_2142823975635459713[153] = 0;
   out_2142823975635459713[154] = 0;
   out_2142823975635459713[155] = 0;
   out_2142823975635459713[156] = 0;
   out_2142823975635459713[157] = 0;
   out_2142823975635459713[158] = 0;
   out_2142823975635459713[159] = 0;
   out_2142823975635459713[160] = 0;
   out_2142823975635459713[161] = 0;
   out_2142823975635459713[162] = 0;
   out_2142823975635459713[163] = 0;
   out_2142823975635459713[164] = 0;
   out_2142823975635459713[165] = 0;
   out_2142823975635459713[166] = 0;
   out_2142823975635459713[167] = 0;
   out_2142823975635459713[168] = 0;
   out_2142823975635459713[169] = 0;
   out_2142823975635459713[170] = 0;
   out_2142823975635459713[171] = 1;
   out_2142823975635459713[172] = 0;
   out_2142823975635459713[173] = 0;
   out_2142823975635459713[174] = 0;
   out_2142823975635459713[175] = 0;
   out_2142823975635459713[176] = 0;
   out_2142823975635459713[177] = 0;
   out_2142823975635459713[178] = 0;
   out_2142823975635459713[179] = 0;
   out_2142823975635459713[180] = 0;
   out_2142823975635459713[181] = 0;
   out_2142823975635459713[182] = 0;
   out_2142823975635459713[183] = 0;
   out_2142823975635459713[184] = 0;
   out_2142823975635459713[185] = 0;
   out_2142823975635459713[186] = 0;
   out_2142823975635459713[187] = 0;
   out_2142823975635459713[188] = 0;
   out_2142823975635459713[189] = 0;
   out_2142823975635459713[190] = 1;
   out_2142823975635459713[191] = 0;
   out_2142823975635459713[192] = 0;
   out_2142823975635459713[193] = 0;
   out_2142823975635459713[194] = 0;
   out_2142823975635459713[195] = 0;
   out_2142823975635459713[196] = 0;
   out_2142823975635459713[197] = 0;
   out_2142823975635459713[198] = 0;
   out_2142823975635459713[199] = 0;
   out_2142823975635459713[200] = 0;
   out_2142823975635459713[201] = 0;
   out_2142823975635459713[202] = 0;
   out_2142823975635459713[203] = 0;
   out_2142823975635459713[204] = 0;
   out_2142823975635459713[205] = 0;
   out_2142823975635459713[206] = 0;
   out_2142823975635459713[207] = 0;
   out_2142823975635459713[208] = 0;
   out_2142823975635459713[209] = 1;
   out_2142823975635459713[210] = 0;
   out_2142823975635459713[211] = 0;
   out_2142823975635459713[212] = 0;
   out_2142823975635459713[213] = 0;
   out_2142823975635459713[214] = 0;
   out_2142823975635459713[215] = 0;
   out_2142823975635459713[216] = 0;
   out_2142823975635459713[217] = 0;
   out_2142823975635459713[218] = 0;
   out_2142823975635459713[219] = 0;
   out_2142823975635459713[220] = 0;
   out_2142823975635459713[221] = 0;
   out_2142823975635459713[222] = 0;
   out_2142823975635459713[223] = 0;
   out_2142823975635459713[224] = 0;
   out_2142823975635459713[225] = 0;
   out_2142823975635459713[226] = 0;
   out_2142823975635459713[227] = 0;
   out_2142823975635459713[228] = 1;
   out_2142823975635459713[229] = 0;
   out_2142823975635459713[230] = 0;
   out_2142823975635459713[231] = 0;
   out_2142823975635459713[232] = 0;
   out_2142823975635459713[233] = 0;
   out_2142823975635459713[234] = 0;
   out_2142823975635459713[235] = 0;
   out_2142823975635459713[236] = 0;
   out_2142823975635459713[237] = 0;
   out_2142823975635459713[238] = 0;
   out_2142823975635459713[239] = 0;
   out_2142823975635459713[240] = 0;
   out_2142823975635459713[241] = 0;
   out_2142823975635459713[242] = 0;
   out_2142823975635459713[243] = 0;
   out_2142823975635459713[244] = 0;
   out_2142823975635459713[245] = 0;
   out_2142823975635459713[246] = 0;
   out_2142823975635459713[247] = 1;
   out_2142823975635459713[248] = 0;
   out_2142823975635459713[249] = 0;
   out_2142823975635459713[250] = 0;
   out_2142823975635459713[251] = 0;
   out_2142823975635459713[252] = 0;
   out_2142823975635459713[253] = 0;
   out_2142823975635459713[254] = 0;
   out_2142823975635459713[255] = 0;
   out_2142823975635459713[256] = 0;
   out_2142823975635459713[257] = 0;
   out_2142823975635459713[258] = 0;
   out_2142823975635459713[259] = 0;
   out_2142823975635459713[260] = 0;
   out_2142823975635459713[261] = 0;
   out_2142823975635459713[262] = 0;
   out_2142823975635459713[263] = 0;
   out_2142823975635459713[264] = 0;
   out_2142823975635459713[265] = 0;
   out_2142823975635459713[266] = 1;
   out_2142823975635459713[267] = 0;
   out_2142823975635459713[268] = 0;
   out_2142823975635459713[269] = 0;
   out_2142823975635459713[270] = 0;
   out_2142823975635459713[271] = 0;
   out_2142823975635459713[272] = 0;
   out_2142823975635459713[273] = 0;
   out_2142823975635459713[274] = 0;
   out_2142823975635459713[275] = 0;
   out_2142823975635459713[276] = 0;
   out_2142823975635459713[277] = 0;
   out_2142823975635459713[278] = 0;
   out_2142823975635459713[279] = 0;
   out_2142823975635459713[280] = 0;
   out_2142823975635459713[281] = 0;
   out_2142823975635459713[282] = 0;
   out_2142823975635459713[283] = 0;
   out_2142823975635459713[284] = 0;
   out_2142823975635459713[285] = 1;
   out_2142823975635459713[286] = 0;
   out_2142823975635459713[287] = 0;
   out_2142823975635459713[288] = 0;
   out_2142823975635459713[289] = 0;
   out_2142823975635459713[290] = 0;
   out_2142823975635459713[291] = 0;
   out_2142823975635459713[292] = 0;
   out_2142823975635459713[293] = 0;
   out_2142823975635459713[294] = 0;
   out_2142823975635459713[295] = 0;
   out_2142823975635459713[296] = 0;
   out_2142823975635459713[297] = 0;
   out_2142823975635459713[298] = 0;
   out_2142823975635459713[299] = 0;
   out_2142823975635459713[300] = 0;
   out_2142823975635459713[301] = 0;
   out_2142823975635459713[302] = 0;
   out_2142823975635459713[303] = 0;
   out_2142823975635459713[304] = 1;
   out_2142823975635459713[305] = 0;
   out_2142823975635459713[306] = 0;
   out_2142823975635459713[307] = 0;
   out_2142823975635459713[308] = 0;
   out_2142823975635459713[309] = 0;
   out_2142823975635459713[310] = 0;
   out_2142823975635459713[311] = 0;
   out_2142823975635459713[312] = 0;
   out_2142823975635459713[313] = 0;
   out_2142823975635459713[314] = 0;
   out_2142823975635459713[315] = 0;
   out_2142823975635459713[316] = 0;
   out_2142823975635459713[317] = 0;
   out_2142823975635459713[318] = 0;
   out_2142823975635459713[319] = 0;
   out_2142823975635459713[320] = 0;
   out_2142823975635459713[321] = 0;
   out_2142823975635459713[322] = 0;
   out_2142823975635459713[323] = 1;
}
void h_4(double *state, double *unused, double *out_1527567868933253243) {
   out_1527567868933253243[0] = state[6] + state[9];
   out_1527567868933253243[1] = state[7] + state[10];
   out_1527567868933253243[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6820365971482965361) {
   out_6820365971482965361[0] = 0;
   out_6820365971482965361[1] = 0;
   out_6820365971482965361[2] = 0;
   out_6820365971482965361[3] = 0;
   out_6820365971482965361[4] = 0;
   out_6820365971482965361[5] = 0;
   out_6820365971482965361[6] = 1;
   out_6820365971482965361[7] = 0;
   out_6820365971482965361[8] = 0;
   out_6820365971482965361[9] = 1;
   out_6820365971482965361[10] = 0;
   out_6820365971482965361[11] = 0;
   out_6820365971482965361[12] = 0;
   out_6820365971482965361[13] = 0;
   out_6820365971482965361[14] = 0;
   out_6820365971482965361[15] = 0;
   out_6820365971482965361[16] = 0;
   out_6820365971482965361[17] = 0;
   out_6820365971482965361[18] = 0;
   out_6820365971482965361[19] = 0;
   out_6820365971482965361[20] = 0;
   out_6820365971482965361[21] = 0;
   out_6820365971482965361[22] = 0;
   out_6820365971482965361[23] = 0;
   out_6820365971482965361[24] = 0;
   out_6820365971482965361[25] = 1;
   out_6820365971482965361[26] = 0;
   out_6820365971482965361[27] = 0;
   out_6820365971482965361[28] = 1;
   out_6820365971482965361[29] = 0;
   out_6820365971482965361[30] = 0;
   out_6820365971482965361[31] = 0;
   out_6820365971482965361[32] = 0;
   out_6820365971482965361[33] = 0;
   out_6820365971482965361[34] = 0;
   out_6820365971482965361[35] = 0;
   out_6820365971482965361[36] = 0;
   out_6820365971482965361[37] = 0;
   out_6820365971482965361[38] = 0;
   out_6820365971482965361[39] = 0;
   out_6820365971482965361[40] = 0;
   out_6820365971482965361[41] = 0;
   out_6820365971482965361[42] = 0;
   out_6820365971482965361[43] = 0;
   out_6820365971482965361[44] = 1;
   out_6820365971482965361[45] = 0;
   out_6820365971482965361[46] = 0;
   out_6820365971482965361[47] = 1;
   out_6820365971482965361[48] = 0;
   out_6820365971482965361[49] = 0;
   out_6820365971482965361[50] = 0;
   out_6820365971482965361[51] = 0;
   out_6820365971482965361[52] = 0;
   out_6820365971482965361[53] = 0;
}
void h_10(double *state, double *unused, double *out_4124637140898740964) {
   out_4124637140898740964[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_4124637140898740964[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_4124637140898740964[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_7216042770550817325) {
   out_7216042770550817325[0] = 0;
   out_7216042770550817325[1] = 9.8100000000000005*cos(state[1]);
   out_7216042770550817325[2] = 0;
   out_7216042770550817325[3] = 0;
   out_7216042770550817325[4] = -state[8];
   out_7216042770550817325[5] = state[7];
   out_7216042770550817325[6] = 0;
   out_7216042770550817325[7] = state[5];
   out_7216042770550817325[8] = -state[4];
   out_7216042770550817325[9] = 0;
   out_7216042770550817325[10] = 0;
   out_7216042770550817325[11] = 0;
   out_7216042770550817325[12] = 1;
   out_7216042770550817325[13] = 0;
   out_7216042770550817325[14] = 0;
   out_7216042770550817325[15] = 1;
   out_7216042770550817325[16] = 0;
   out_7216042770550817325[17] = 0;
   out_7216042770550817325[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_7216042770550817325[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_7216042770550817325[20] = 0;
   out_7216042770550817325[21] = state[8];
   out_7216042770550817325[22] = 0;
   out_7216042770550817325[23] = -state[6];
   out_7216042770550817325[24] = -state[5];
   out_7216042770550817325[25] = 0;
   out_7216042770550817325[26] = state[3];
   out_7216042770550817325[27] = 0;
   out_7216042770550817325[28] = 0;
   out_7216042770550817325[29] = 0;
   out_7216042770550817325[30] = 0;
   out_7216042770550817325[31] = 1;
   out_7216042770550817325[32] = 0;
   out_7216042770550817325[33] = 0;
   out_7216042770550817325[34] = 1;
   out_7216042770550817325[35] = 0;
   out_7216042770550817325[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_7216042770550817325[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_7216042770550817325[38] = 0;
   out_7216042770550817325[39] = -state[7];
   out_7216042770550817325[40] = state[6];
   out_7216042770550817325[41] = 0;
   out_7216042770550817325[42] = state[4];
   out_7216042770550817325[43] = -state[3];
   out_7216042770550817325[44] = 0;
   out_7216042770550817325[45] = 0;
   out_7216042770550817325[46] = 0;
   out_7216042770550817325[47] = 0;
   out_7216042770550817325[48] = 0;
   out_7216042770550817325[49] = 0;
   out_7216042770550817325[50] = 1;
   out_7216042770550817325[51] = 0;
   out_7216042770550817325[52] = 0;
   out_7216042770550817325[53] = 1;
}
void h_13(double *state, double *unused, double *out_5617317736233702869) {
   out_5617317736233702869[0] = state[3];
   out_5617317736233702869[1] = state[4];
   out_5617317736233702869[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3608092146150632560) {
   out_3608092146150632560[0] = 0;
   out_3608092146150632560[1] = 0;
   out_3608092146150632560[2] = 0;
   out_3608092146150632560[3] = 1;
   out_3608092146150632560[4] = 0;
   out_3608092146150632560[5] = 0;
   out_3608092146150632560[6] = 0;
   out_3608092146150632560[7] = 0;
   out_3608092146150632560[8] = 0;
   out_3608092146150632560[9] = 0;
   out_3608092146150632560[10] = 0;
   out_3608092146150632560[11] = 0;
   out_3608092146150632560[12] = 0;
   out_3608092146150632560[13] = 0;
   out_3608092146150632560[14] = 0;
   out_3608092146150632560[15] = 0;
   out_3608092146150632560[16] = 0;
   out_3608092146150632560[17] = 0;
   out_3608092146150632560[18] = 0;
   out_3608092146150632560[19] = 0;
   out_3608092146150632560[20] = 0;
   out_3608092146150632560[21] = 0;
   out_3608092146150632560[22] = 1;
   out_3608092146150632560[23] = 0;
   out_3608092146150632560[24] = 0;
   out_3608092146150632560[25] = 0;
   out_3608092146150632560[26] = 0;
   out_3608092146150632560[27] = 0;
   out_3608092146150632560[28] = 0;
   out_3608092146150632560[29] = 0;
   out_3608092146150632560[30] = 0;
   out_3608092146150632560[31] = 0;
   out_3608092146150632560[32] = 0;
   out_3608092146150632560[33] = 0;
   out_3608092146150632560[34] = 0;
   out_3608092146150632560[35] = 0;
   out_3608092146150632560[36] = 0;
   out_3608092146150632560[37] = 0;
   out_3608092146150632560[38] = 0;
   out_3608092146150632560[39] = 0;
   out_3608092146150632560[40] = 0;
   out_3608092146150632560[41] = 1;
   out_3608092146150632560[42] = 0;
   out_3608092146150632560[43] = 0;
   out_3608092146150632560[44] = 0;
   out_3608092146150632560[45] = 0;
   out_3608092146150632560[46] = 0;
   out_3608092146150632560[47] = 0;
   out_3608092146150632560[48] = 0;
   out_3608092146150632560[49] = 0;
   out_3608092146150632560[50] = 0;
   out_3608092146150632560[51] = 0;
   out_3608092146150632560[52] = 0;
   out_3608092146150632560[53] = 0;
}
void h_14(double *state, double *unused, double *out_2577074895762232854) {
   out_2577074895762232854[0] = state[6];
   out_2577074895762232854[1] = state[7];
   out_2577074895762232854[2] = state[8];
}
void H_14(double *state, double *unused, double *out_4145232286946845831) {
   out_4145232286946845831[0] = 0;
   out_4145232286946845831[1] = 0;
   out_4145232286946845831[2] = 0;
   out_4145232286946845831[3] = 0;
   out_4145232286946845831[4] = 0;
   out_4145232286946845831[5] = 0;
   out_4145232286946845831[6] = 1;
   out_4145232286946845831[7] = 0;
   out_4145232286946845831[8] = 0;
   out_4145232286946845831[9] = 0;
   out_4145232286946845831[10] = 0;
   out_4145232286946845831[11] = 0;
   out_4145232286946845831[12] = 0;
   out_4145232286946845831[13] = 0;
   out_4145232286946845831[14] = 0;
   out_4145232286946845831[15] = 0;
   out_4145232286946845831[16] = 0;
   out_4145232286946845831[17] = 0;
   out_4145232286946845831[18] = 0;
   out_4145232286946845831[19] = 0;
   out_4145232286946845831[20] = 0;
   out_4145232286946845831[21] = 0;
   out_4145232286946845831[22] = 0;
   out_4145232286946845831[23] = 0;
   out_4145232286946845831[24] = 0;
   out_4145232286946845831[25] = 1;
   out_4145232286946845831[26] = 0;
   out_4145232286946845831[27] = 0;
   out_4145232286946845831[28] = 0;
   out_4145232286946845831[29] = 0;
   out_4145232286946845831[30] = 0;
   out_4145232286946845831[31] = 0;
   out_4145232286946845831[32] = 0;
   out_4145232286946845831[33] = 0;
   out_4145232286946845831[34] = 0;
   out_4145232286946845831[35] = 0;
   out_4145232286946845831[36] = 0;
   out_4145232286946845831[37] = 0;
   out_4145232286946845831[38] = 0;
   out_4145232286946845831[39] = 0;
   out_4145232286946845831[40] = 0;
   out_4145232286946845831[41] = 0;
   out_4145232286946845831[42] = 0;
   out_4145232286946845831[43] = 0;
   out_4145232286946845831[44] = 1;
   out_4145232286946845831[45] = 0;
   out_4145232286946845831[46] = 0;
   out_4145232286946845831[47] = 0;
   out_4145232286946845831[48] = 0;
   out_4145232286946845831[49] = 0;
   out_4145232286946845831[50] = 0;
   out_4145232286946845831[51] = 0;
   out_4145232286946845831[52] = 0;
   out_4145232286946845831[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_3291478583356534624) {
  err_fun(nom_x, delta_x, out_3291478583356534624);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8622738967567708549) {
  inv_err_fun(nom_x, true_x, out_8622738967567708549);
}
void pose_H_mod_fun(double *state, double *out_4432635606321955062) {
  H_mod_fun(state, out_4432635606321955062);
}
void pose_f_fun(double *state, double dt, double *out_872598189031658011) {
  f_fun(state,  dt, out_872598189031658011);
}
void pose_F_fun(double *state, double dt, double *out_2142823975635459713) {
  F_fun(state,  dt, out_2142823975635459713);
}
void pose_h_4(double *state, double *unused, double *out_1527567868933253243) {
  h_4(state, unused, out_1527567868933253243);
}
void pose_H_4(double *state, double *unused, double *out_6820365971482965361) {
  H_4(state, unused, out_6820365971482965361);
}
void pose_h_10(double *state, double *unused, double *out_4124637140898740964) {
  h_10(state, unused, out_4124637140898740964);
}
void pose_H_10(double *state, double *unused, double *out_7216042770550817325) {
  H_10(state, unused, out_7216042770550817325);
}
void pose_h_13(double *state, double *unused, double *out_5617317736233702869) {
  h_13(state, unused, out_5617317736233702869);
}
void pose_H_13(double *state, double *unused, double *out_3608092146150632560) {
  H_13(state, unused, out_3608092146150632560);
}
void pose_h_14(double *state, double *unused, double *out_2577074895762232854) {
  h_14(state, unused, out_2577074895762232854);
}
void pose_H_14(double *state, double *unused, double *out_4145232286946845831) {
  H_14(state, unused, out_4145232286946845831);
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
