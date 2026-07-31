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
void err_fun(double *nom_x, double *delta_x, double *out_7283166407761929442) {
   out_7283166407761929442[0] = delta_x[0] + nom_x[0];
   out_7283166407761929442[1] = delta_x[1] + nom_x[1];
   out_7283166407761929442[2] = delta_x[2] + nom_x[2];
   out_7283166407761929442[3] = delta_x[3] + nom_x[3];
   out_7283166407761929442[4] = delta_x[4] + nom_x[4];
   out_7283166407761929442[5] = delta_x[5] + nom_x[5];
   out_7283166407761929442[6] = delta_x[6] + nom_x[6];
   out_7283166407761929442[7] = delta_x[7] + nom_x[7];
   out_7283166407761929442[8] = delta_x[8] + nom_x[8];
   out_7283166407761929442[9] = delta_x[9] + nom_x[9];
   out_7283166407761929442[10] = delta_x[10] + nom_x[10];
   out_7283166407761929442[11] = delta_x[11] + nom_x[11];
   out_7283166407761929442[12] = delta_x[12] + nom_x[12];
   out_7283166407761929442[13] = delta_x[13] + nom_x[13];
   out_7283166407761929442[14] = delta_x[14] + nom_x[14];
   out_7283166407761929442[15] = delta_x[15] + nom_x[15];
   out_7283166407761929442[16] = delta_x[16] + nom_x[16];
   out_7283166407761929442[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_546984208695000774) {
   out_546984208695000774[0] = -nom_x[0] + true_x[0];
   out_546984208695000774[1] = -nom_x[1] + true_x[1];
   out_546984208695000774[2] = -nom_x[2] + true_x[2];
   out_546984208695000774[3] = -nom_x[3] + true_x[3];
   out_546984208695000774[4] = -nom_x[4] + true_x[4];
   out_546984208695000774[5] = -nom_x[5] + true_x[5];
   out_546984208695000774[6] = -nom_x[6] + true_x[6];
   out_546984208695000774[7] = -nom_x[7] + true_x[7];
   out_546984208695000774[8] = -nom_x[8] + true_x[8];
   out_546984208695000774[9] = -nom_x[9] + true_x[9];
   out_546984208695000774[10] = -nom_x[10] + true_x[10];
   out_546984208695000774[11] = -nom_x[11] + true_x[11];
   out_546984208695000774[12] = -nom_x[12] + true_x[12];
   out_546984208695000774[13] = -nom_x[13] + true_x[13];
   out_546984208695000774[14] = -nom_x[14] + true_x[14];
   out_546984208695000774[15] = -nom_x[15] + true_x[15];
   out_546984208695000774[16] = -nom_x[16] + true_x[16];
   out_546984208695000774[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3827791306191189093) {
   out_3827791306191189093[0] = 1.0;
   out_3827791306191189093[1] = 0.0;
   out_3827791306191189093[2] = 0.0;
   out_3827791306191189093[3] = 0.0;
   out_3827791306191189093[4] = 0.0;
   out_3827791306191189093[5] = 0.0;
   out_3827791306191189093[6] = 0.0;
   out_3827791306191189093[7] = 0.0;
   out_3827791306191189093[8] = 0.0;
   out_3827791306191189093[9] = 0.0;
   out_3827791306191189093[10] = 0.0;
   out_3827791306191189093[11] = 0.0;
   out_3827791306191189093[12] = 0.0;
   out_3827791306191189093[13] = 0.0;
   out_3827791306191189093[14] = 0.0;
   out_3827791306191189093[15] = 0.0;
   out_3827791306191189093[16] = 0.0;
   out_3827791306191189093[17] = 0.0;
   out_3827791306191189093[18] = 0.0;
   out_3827791306191189093[19] = 1.0;
   out_3827791306191189093[20] = 0.0;
   out_3827791306191189093[21] = 0.0;
   out_3827791306191189093[22] = 0.0;
   out_3827791306191189093[23] = 0.0;
   out_3827791306191189093[24] = 0.0;
   out_3827791306191189093[25] = 0.0;
   out_3827791306191189093[26] = 0.0;
   out_3827791306191189093[27] = 0.0;
   out_3827791306191189093[28] = 0.0;
   out_3827791306191189093[29] = 0.0;
   out_3827791306191189093[30] = 0.0;
   out_3827791306191189093[31] = 0.0;
   out_3827791306191189093[32] = 0.0;
   out_3827791306191189093[33] = 0.0;
   out_3827791306191189093[34] = 0.0;
   out_3827791306191189093[35] = 0.0;
   out_3827791306191189093[36] = 0.0;
   out_3827791306191189093[37] = 0.0;
   out_3827791306191189093[38] = 1.0;
   out_3827791306191189093[39] = 0.0;
   out_3827791306191189093[40] = 0.0;
   out_3827791306191189093[41] = 0.0;
   out_3827791306191189093[42] = 0.0;
   out_3827791306191189093[43] = 0.0;
   out_3827791306191189093[44] = 0.0;
   out_3827791306191189093[45] = 0.0;
   out_3827791306191189093[46] = 0.0;
   out_3827791306191189093[47] = 0.0;
   out_3827791306191189093[48] = 0.0;
   out_3827791306191189093[49] = 0.0;
   out_3827791306191189093[50] = 0.0;
   out_3827791306191189093[51] = 0.0;
   out_3827791306191189093[52] = 0.0;
   out_3827791306191189093[53] = 0.0;
   out_3827791306191189093[54] = 0.0;
   out_3827791306191189093[55] = 0.0;
   out_3827791306191189093[56] = 0.0;
   out_3827791306191189093[57] = 1.0;
   out_3827791306191189093[58] = 0.0;
   out_3827791306191189093[59] = 0.0;
   out_3827791306191189093[60] = 0.0;
   out_3827791306191189093[61] = 0.0;
   out_3827791306191189093[62] = 0.0;
   out_3827791306191189093[63] = 0.0;
   out_3827791306191189093[64] = 0.0;
   out_3827791306191189093[65] = 0.0;
   out_3827791306191189093[66] = 0.0;
   out_3827791306191189093[67] = 0.0;
   out_3827791306191189093[68] = 0.0;
   out_3827791306191189093[69] = 0.0;
   out_3827791306191189093[70] = 0.0;
   out_3827791306191189093[71] = 0.0;
   out_3827791306191189093[72] = 0.0;
   out_3827791306191189093[73] = 0.0;
   out_3827791306191189093[74] = 0.0;
   out_3827791306191189093[75] = 0.0;
   out_3827791306191189093[76] = 1.0;
   out_3827791306191189093[77] = 0.0;
   out_3827791306191189093[78] = 0.0;
   out_3827791306191189093[79] = 0.0;
   out_3827791306191189093[80] = 0.0;
   out_3827791306191189093[81] = 0.0;
   out_3827791306191189093[82] = 0.0;
   out_3827791306191189093[83] = 0.0;
   out_3827791306191189093[84] = 0.0;
   out_3827791306191189093[85] = 0.0;
   out_3827791306191189093[86] = 0.0;
   out_3827791306191189093[87] = 0.0;
   out_3827791306191189093[88] = 0.0;
   out_3827791306191189093[89] = 0.0;
   out_3827791306191189093[90] = 0.0;
   out_3827791306191189093[91] = 0.0;
   out_3827791306191189093[92] = 0.0;
   out_3827791306191189093[93] = 0.0;
   out_3827791306191189093[94] = 0.0;
   out_3827791306191189093[95] = 1.0;
   out_3827791306191189093[96] = 0.0;
   out_3827791306191189093[97] = 0.0;
   out_3827791306191189093[98] = 0.0;
   out_3827791306191189093[99] = 0.0;
   out_3827791306191189093[100] = 0.0;
   out_3827791306191189093[101] = 0.0;
   out_3827791306191189093[102] = 0.0;
   out_3827791306191189093[103] = 0.0;
   out_3827791306191189093[104] = 0.0;
   out_3827791306191189093[105] = 0.0;
   out_3827791306191189093[106] = 0.0;
   out_3827791306191189093[107] = 0.0;
   out_3827791306191189093[108] = 0.0;
   out_3827791306191189093[109] = 0.0;
   out_3827791306191189093[110] = 0.0;
   out_3827791306191189093[111] = 0.0;
   out_3827791306191189093[112] = 0.0;
   out_3827791306191189093[113] = 0.0;
   out_3827791306191189093[114] = 1.0;
   out_3827791306191189093[115] = 0.0;
   out_3827791306191189093[116] = 0.0;
   out_3827791306191189093[117] = 0.0;
   out_3827791306191189093[118] = 0.0;
   out_3827791306191189093[119] = 0.0;
   out_3827791306191189093[120] = 0.0;
   out_3827791306191189093[121] = 0.0;
   out_3827791306191189093[122] = 0.0;
   out_3827791306191189093[123] = 0.0;
   out_3827791306191189093[124] = 0.0;
   out_3827791306191189093[125] = 0.0;
   out_3827791306191189093[126] = 0.0;
   out_3827791306191189093[127] = 0.0;
   out_3827791306191189093[128] = 0.0;
   out_3827791306191189093[129] = 0.0;
   out_3827791306191189093[130] = 0.0;
   out_3827791306191189093[131] = 0.0;
   out_3827791306191189093[132] = 0.0;
   out_3827791306191189093[133] = 1.0;
   out_3827791306191189093[134] = 0.0;
   out_3827791306191189093[135] = 0.0;
   out_3827791306191189093[136] = 0.0;
   out_3827791306191189093[137] = 0.0;
   out_3827791306191189093[138] = 0.0;
   out_3827791306191189093[139] = 0.0;
   out_3827791306191189093[140] = 0.0;
   out_3827791306191189093[141] = 0.0;
   out_3827791306191189093[142] = 0.0;
   out_3827791306191189093[143] = 0.0;
   out_3827791306191189093[144] = 0.0;
   out_3827791306191189093[145] = 0.0;
   out_3827791306191189093[146] = 0.0;
   out_3827791306191189093[147] = 0.0;
   out_3827791306191189093[148] = 0.0;
   out_3827791306191189093[149] = 0.0;
   out_3827791306191189093[150] = 0.0;
   out_3827791306191189093[151] = 0.0;
   out_3827791306191189093[152] = 1.0;
   out_3827791306191189093[153] = 0.0;
   out_3827791306191189093[154] = 0.0;
   out_3827791306191189093[155] = 0.0;
   out_3827791306191189093[156] = 0.0;
   out_3827791306191189093[157] = 0.0;
   out_3827791306191189093[158] = 0.0;
   out_3827791306191189093[159] = 0.0;
   out_3827791306191189093[160] = 0.0;
   out_3827791306191189093[161] = 0.0;
   out_3827791306191189093[162] = 0.0;
   out_3827791306191189093[163] = 0.0;
   out_3827791306191189093[164] = 0.0;
   out_3827791306191189093[165] = 0.0;
   out_3827791306191189093[166] = 0.0;
   out_3827791306191189093[167] = 0.0;
   out_3827791306191189093[168] = 0.0;
   out_3827791306191189093[169] = 0.0;
   out_3827791306191189093[170] = 0.0;
   out_3827791306191189093[171] = 1.0;
   out_3827791306191189093[172] = 0.0;
   out_3827791306191189093[173] = 0.0;
   out_3827791306191189093[174] = 0.0;
   out_3827791306191189093[175] = 0.0;
   out_3827791306191189093[176] = 0.0;
   out_3827791306191189093[177] = 0.0;
   out_3827791306191189093[178] = 0.0;
   out_3827791306191189093[179] = 0.0;
   out_3827791306191189093[180] = 0.0;
   out_3827791306191189093[181] = 0.0;
   out_3827791306191189093[182] = 0.0;
   out_3827791306191189093[183] = 0.0;
   out_3827791306191189093[184] = 0.0;
   out_3827791306191189093[185] = 0.0;
   out_3827791306191189093[186] = 0.0;
   out_3827791306191189093[187] = 0.0;
   out_3827791306191189093[188] = 0.0;
   out_3827791306191189093[189] = 0.0;
   out_3827791306191189093[190] = 1.0;
   out_3827791306191189093[191] = 0.0;
   out_3827791306191189093[192] = 0.0;
   out_3827791306191189093[193] = 0.0;
   out_3827791306191189093[194] = 0.0;
   out_3827791306191189093[195] = 0.0;
   out_3827791306191189093[196] = 0.0;
   out_3827791306191189093[197] = 0.0;
   out_3827791306191189093[198] = 0.0;
   out_3827791306191189093[199] = 0.0;
   out_3827791306191189093[200] = 0.0;
   out_3827791306191189093[201] = 0.0;
   out_3827791306191189093[202] = 0.0;
   out_3827791306191189093[203] = 0.0;
   out_3827791306191189093[204] = 0.0;
   out_3827791306191189093[205] = 0.0;
   out_3827791306191189093[206] = 0.0;
   out_3827791306191189093[207] = 0.0;
   out_3827791306191189093[208] = 0.0;
   out_3827791306191189093[209] = 1.0;
   out_3827791306191189093[210] = 0.0;
   out_3827791306191189093[211] = 0.0;
   out_3827791306191189093[212] = 0.0;
   out_3827791306191189093[213] = 0.0;
   out_3827791306191189093[214] = 0.0;
   out_3827791306191189093[215] = 0.0;
   out_3827791306191189093[216] = 0.0;
   out_3827791306191189093[217] = 0.0;
   out_3827791306191189093[218] = 0.0;
   out_3827791306191189093[219] = 0.0;
   out_3827791306191189093[220] = 0.0;
   out_3827791306191189093[221] = 0.0;
   out_3827791306191189093[222] = 0.0;
   out_3827791306191189093[223] = 0.0;
   out_3827791306191189093[224] = 0.0;
   out_3827791306191189093[225] = 0.0;
   out_3827791306191189093[226] = 0.0;
   out_3827791306191189093[227] = 0.0;
   out_3827791306191189093[228] = 1.0;
   out_3827791306191189093[229] = 0.0;
   out_3827791306191189093[230] = 0.0;
   out_3827791306191189093[231] = 0.0;
   out_3827791306191189093[232] = 0.0;
   out_3827791306191189093[233] = 0.0;
   out_3827791306191189093[234] = 0.0;
   out_3827791306191189093[235] = 0.0;
   out_3827791306191189093[236] = 0.0;
   out_3827791306191189093[237] = 0.0;
   out_3827791306191189093[238] = 0.0;
   out_3827791306191189093[239] = 0.0;
   out_3827791306191189093[240] = 0.0;
   out_3827791306191189093[241] = 0.0;
   out_3827791306191189093[242] = 0.0;
   out_3827791306191189093[243] = 0.0;
   out_3827791306191189093[244] = 0.0;
   out_3827791306191189093[245] = 0.0;
   out_3827791306191189093[246] = 0.0;
   out_3827791306191189093[247] = 1.0;
   out_3827791306191189093[248] = 0.0;
   out_3827791306191189093[249] = 0.0;
   out_3827791306191189093[250] = 0.0;
   out_3827791306191189093[251] = 0.0;
   out_3827791306191189093[252] = 0.0;
   out_3827791306191189093[253] = 0.0;
   out_3827791306191189093[254] = 0.0;
   out_3827791306191189093[255] = 0.0;
   out_3827791306191189093[256] = 0.0;
   out_3827791306191189093[257] = 0.0;
   out_3827791306191189093[258] = 0.0;
   out_3827791306191189093[259] = 0.0;
   out_3827791306191189093[260] = 0.0;
   out_3827791306191189093[261] = 0.0;
   out_3827791306191189093[262] = 0.0;
   out_3827791306191189093[263] = 0.0;
   out_3827791306191189093[264] = 0.0;
   out_3827791306191189093[265] = 0.0;
   out_3827791306191189093[266] = 1.0;
   out_3827791306191189093[267] = 0.0;
   out_3827791306191189093[268] = 0.0;
   out_3827791306191189093[269] = 0.0;
   out_3827791306191189093[270] = 0.0;
   out_3827791306191189093[271] = 0.0;
   out_3827791306191189093[272] = 0.0;
   out_3827791306191189093[273] = 0.0;
   out_3827791306191189093[274] = 0.0;
   out_3827791306191189093[275] = 0.0;
   out_3827791306191189093[276] = 0.0;
   out_3827791306191189093[277] = 0.0;
   out_3827791306191189093[278] = 0.0;
   out_3827791306191189093[279] = 0.0;
   out_3827791306191189093[280] = 0.0;
   out_3827791306191189093[281] = 0.0;
   out_3827791306191189093[282] = 0.0;
   out_3827791306191189093[283] = 0.0;
   out_3827791306191189093[284] = 0.0;
   out_3827791306191189093[285] = 1.0;
   out_3827791306191189093[286] = 0.0;
   out_3827791306191189093[287] = 0.0;
   out_3827791306191189093[288] = 0.0;
   out_3827791306191189093[289] = 0.0;
   out_3827791306191189093[290] = 0.0;
   out_3827791306191189093[291] = 0.0;
   out_3827791306191189093[292] = 0.0;
   out_3827791306191189093[293] = 0.0;
   out_3827791306191189093[294] = 0.0;
   out_3827791306191189093[295] = 0.0;
   out_3827791306191189093[296] = 0.0;
   out_3827791306191189093[297] = 0.0;
   out_3827791306191189093[298] = 0.0;
   out_3827791306191189093[299] = 0.0;
   out_3827791306191189093[300] = 0.0;
   out_3827791306191189093[301] = 0.0;
   out_3827791306191189093[302] = 0.0;
   out_3827791306191189093[303] = 0.0;
   out_3827791306191189093[304] = 1.0;
   out_3827791306191189093[305] = 0.0;
   out_3827791306191189093[306] = 0.0;
   out_3827791306191189093[307] = 0.0;
   out_3827791306191189093[308] = 0.0;
   out_3827791306191189093[309] = 0.0;
   out_3827791306191189093[310] = 0.0;
   out_3827791306191189093[311] = 0.0;
   out_3827791306191189093[312] = 0.0;
   out_3827791306191189093[313] = 0.0;
   out_3827791306191189093[314] = 0.0;
   out_3827791306191189093[315] = 0.0;
   out_3827791306191189093[316] = 0.0;
   out_3827791306191189093[317] = 0.0;
   out_3827791306191189093[318] = 0.0;
   out_3827791306191189093[319] = 0.0;
   out_3827791306191189093[320] = 0.0;
   out_3827791306191189093[321] = 0.0;
   out_3827791306191189093[322] = 0.0;
   out_3827791306191189093[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_6733983040945921210) {
   out_6733983040945921210[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_6733983040945921210[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_6733983040945921210[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_6733983040945921210[3] = dt*state[12] + state[3];
   out_6733983040945921210[4] = dt*state[13] + state[4];
   out_6733983040945921210[5] = dt*state[14] + state[5];
   out_6733983040945921210[6] = state[6];
   out_6733983040945921210[7] = state[7];
   out_6733983040945921210[8] = state[8];
   out_6733983040945921210[9] = state[9];
   out_6733983040945921210[10] = state[10];
   out_6733983040945921210[11] = state[11];
   out_6733983040945921210[12] = state[12];
   out_6733983040945921210[13] = state[13];
   out_6733983040945921210[14] = state[14];
   out_6733983040945921210[15] = state[15];
   out_6733983040945921210[16] = state[16];
   out_6733983040945921210[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6995611375067508290) {
   out_6995611375067508290[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6995611375067508290[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6995611375067508290[2] = 0;
   out_6995611375067508290[3] = 0;
   out_6995611375067508290[4] = 0;
   out_6995611375067508290[5] = 0;
   out_6995611375067508290[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6995611375067508290[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6995611375067508290[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6995611375067508290[9] = 0;
   out_6995611375067508290[10] = 0;
   out_6995611375067508290[11] = 0;
   out_6995611375067508290[12] = 0;
   out_6995611375067508290[13] = 0;
   out_6995611375067508290[14] = 0;
   out_6995611375067508290[15] = 0;
   out_6995611375067508290[16] = 0;
   out_6995611375067508290[17] = 0;
   out_6995611375067508290[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6995611375067508290[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6995611375067508290[20] = 0;
   out_6995611375067508290[21] = 0;
   out_6995611375067508290[22] = 0;
   out_6995611375067508290[23] = 0;
   out_6995611375067508290[24] = 0;
   out_6995611375067508290[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6995611375067508290[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6995611375067508290[27] = 0;
   out_6995611375067508290[28] = 0;
   out_6995611375067508290[29] = 0;
   out_6995611375067508290[30] = 0;
   out_6995611375067508290[31] = 0;
   out_6995611375067508290[32] = 0;
   out_6995611375067508290[33] = 0;
   out_6995611375067508290[34] = 0;
   out_6995611375067508290[35] = 0;
   out_6995611375067508290[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6995611375067508290[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6995611375067508290[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6995611375067508290[39] = 0;
   out_6995611375067508290[40] = 0;
   out_6995611375067508290[41] = 0;
   out_6995611375067508290[42] = 0;
   out_6995611375067508290[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6995611375067508290[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6995611375067508290[45] = 0;
   out_6995611375067508290[46] = 0;
   out_6995611375067508290[47] = 0;
   out_6995611375067508290[48] = 0;
   out_6995611375067508290[49] = 0;
   out_6995611375067508290[50] = 0;
   out_6995611375067508290[51] = 0;
   out_6995611375067508290[52] = 0;
   out_6995611375067508290[53] = 0;
   out_6995611375067508290[54] = 0;
   out_6995611375067508290[55] = 0;
   out_6995611375067508290[56] = 0;
   out_6995611375067508290[57] = 1;
   out_6995611375067508290[58] = 0;
   out_6995611375067508290[59] = 0;
   out_6995611375067508290[60] = 0;
   out_6995611375067508290[61] = 0;
   out_6995611375067508290[62] = 0;
   out_6995611375067508290[63] = 0;
   out_6995611375067508290[64] = 0;
   out_6995611375067508290[65] = 0;
   out_6995611375067508290[66] = dt;
   out_6995611375067508290[67] = 0;
   out_6995611375067508290[68] = 0;
   out_6995611375067508290[69] = 0;
   out_6995611375067508290[70] = 0;
   out_6995611375067508290[71] = 0;
   out_6995611375067508290[72] = 0;
   out_6995611375067508290[73] = 0;
   out_6995611375067508290[74] = 0;
   out_6995611375067508290[75] = 0;
   out_6995611375067508290[76] = 1;
   out_6995611375067508290[77] = 0;
   out_6995611375067508290[78] = 0;
   out_6995611375067508290[79] = 0;
   out_6995611375067508290[80] = 0;
   out_6995611375067508290[81] = 0;
   out_6995611375067508290[82] = 0;
   out_6995611375067508290[83] = 0;
   out_6995611375067508290[84] = 0;
   out_6995611375067508290[85] = dt;
   out_6995611375067508290[86] = 0;
   out_6995611375067508290[87] = 0;
   out_6995611375067508290[88] = 0;
   out_6995611375067508290[89] = 0;
   out_6995611375067508290[90] = 0;
   out_6995611375067508290[91] = 0;
   out_6995611375067508290[92] = 0;
   out_6995611375067508290[93] = 0;
   out_6995611375067508290[94] = 0;
   out_6995611375067508290[95] = 1;
   out_6995611375067508290[96] = 0;
   out_6995611375067508290[97] = 0;
   out_6995611375067508290[98] = 0;
   out_6995611375067508290[99] = 0;
   out_6995611375067508290[100] = 0;
   out_6995611375067508290[101] = 0;
   out_6995611375067508290[102] = 0;
   out_6995611375067508290[103] = 0;
   out_6995611375067508290[104] = dt;
   out_6995611375067508290[105] = 0;
   out_6995611375067508290[106] = 0;
   out_6995611375067508290[107] = 0;
   out_6995611375067508290[108] = 0;
   out_6995611375067508290[109] = 0;
   out_6995611375067508290[110] = 0;
   out_6995611375067508290[111] = 0;
   out_6995611375067508290[112] = 0;
   out_6995611375067508290[113] = 0;
   out_6995611375067508290[114] = 1;
   out_6995611375067508290[115] = 0;
   out_6995611375067508290[116] = 0;
   out_6995611375067508290[117] = 0;
   out_6995611375067508290[118] = 0;
   out_6995611375067508290[119] = 0;
   out_6995611375067508290[120] = 0;
   out_6995611375067508290[121] = 0;
   out_6995611375067508290[122] = 0;
   out_6995611375067508290[123] = 0;
   out_6995611375067508290[124] = 0;
   out_6995611375067508290[125] = 0;
   out_6995611375067508290[126] = 0;
   out_6995611375067508290[127] = 0;
   out_6995611375067508290[128] = 0;
   out_6995611375067508290[129] = 0;
   out_6995611375067508290[130] = 0;
   out_6995611375067508290[131] = 0;
   out_6995611375067508290[132] = 0;
   out_6995611375067508290[133] = 1;
   out_6995611375067508290[134] = 0;
   out_6995611375067508290[135] = 0;
   out_6995611375067508290[136] = 0;
   out_6995611375067508290[137] = 0;
   out_6995611375067508290[138] = 0;
   out_6995611375067508290[139] = 0;
   out_6995611375067508290[140] = 0;
   out_6995611375067508290[141] = 0;
   out_6995611375067508290[142] = 0;
   out_6995611375067508290[143] = 0;
   out_6995611375067508290[144] = 0;
   out_6995611375067508290[145] = 0;
   out_6995611375067508290[146] = 0;
   out_6995611375067508290[147] = 0;
   out_6995611375067508290[148] = 0;
   out_6995611375067508290[149] = 0;
   out_6995611375067508290[150] = 0;
   out_6995611375067508290[151] = 0;
   out_6995611375067508290[152] = 1;
   out_6995611375067508290[153] = 0;
   out_6995611375067508290[154] = 0;
   out_6995611375067508290[155] = 0;
   out_6995611375067508290[156] = 0;
   out_6995611375067508290[157] = 0;
   out_6995611375067508290[158] = 0;
   out_6995611375067508290[159] = 0;
   out_6995611375067508290[160] = 0;
   out_6995611375067508290[161] = 0;
   out_6995611375067508290[162] = 0;
   out_6995611375067508290[163] = 0;
   out_6995611375067508290[164] = 0;
   out_6995611375067508290[165] = 0;
   out_6995611375067508290[166] = 0;
   out_6995611375067508290[167] = 0;
   out_6995611375067508290[168] = 0;
   out_6995611375067508290[169] = 0;
   out_6995611375067508290[170] = 0;
   out_6995611375067508290[171] = 1;
   out_6995611375067508290[172] = 0;
   out_6995611375067508290[173] = 0;
   out_6995611375067508290[174] = 0;
   out_6995611375067508290[175] = 0;
   out_6995611375067508290[176] = 0;
   out_6995611375067508290[177] = 0;
   out_6995611375067508290[178] = 0;
   out_6995611375067508290[179] = 0;
   out_6995611375067508290[180] = 0;
   out_6995611375067508290[181] = 0;
   out_6995611375067508290[182] = 0;
   out_6995611375067508290[183] = 0;
   out_6995611375067508290[184] = 0;
   out_6995611375067508290[185] = 0;
   out_6995611375067508290[186] = 0;
   out_6995611375067508290[187] = 0;
   out_6995611375067508290[188] = 0;
   out_6995611375067508290[189] = 0;
   out_6995611375067508290[190] = 1;
   out_6995611375067508290[191] = 0;
   out_6995611375067508290[192] = 0;
   out_6995611375067508290[193] = 0;
   out_6995611375067508290[194] = 0;
   out_6995611375067508290[195] = 0;
   out_6995611375067508290[196] = 0;
   out_6995611375067508290[197] = 0;
   out_6995611375067508290[198] = 0;
   out_6995611375067508290[199] = 0;
   out_6995611375067508290[200] = 0;
   out_6995611375067508290[201] = 0;
   out_6995611375067508290[202] = 0;
   out_6995611375067508290[203] = 0;
   out_6995611375067508290[204] = 0;
   out_6995611375067508290[205] = 0;
   out_6995611375067508290[206] = 0;
   out_6995611375067508290[207] = 0;
   out_6995611375067508290[208] = 0;
   out_6995611375067508290[209] = 1;
   out_6995611375067508290[210] = 0;
   out_6995611375067508290[211] = 0;
   out_6995611375067508290[212] = 0;
   out_6995611375067508290[213] = 0;
   out_6995611375067508290[214] = 0;
   out_6995611375067508290[215] = 0;
   out_6995611375067508290[216] = 0;
   out_6995611375067508290[217] = 0;
   out_6995611375067508290[218] = 0;
   out_6995611375067508290[219] = 0;
   out_6995611375067508290[220] = 0;
   out_6995611375067508290[221] = 0;
   out_6995611375067508290[222] = 0;
   out_6995611375067508290[223] = 0;
   out_6995611375067508290[224] = 0;
   out_6995611375067508290[225] = 0;
   out_6995611375067508290[226] = 0;
   out_6995611375067508290[227] = 0;
   out_6995611375067508290[228] = 1;
   out_6995611375067508290[229] = 0;
   out_6995611375067508290[230] = 0;
   out_6995611375067508290[231] = 0;
   out_6995611375067508290[232] = 0;
   out_6995611375067508290[233] = 0;
   out_6995611375067508290[234] = 0;
   out_6995611375067508290[235] = 0;
   out_6995611375067508290[236] = 0;
   out_6995611375067508290[237] = 0;
   out_6995611375067508290[238] = 0;
   out_6995611375067508290[239] = 0;
   out_6995611375067508290[240] = 0;
   out_6995611375067508290[241] = 0;
   out_6995611375067508290[242] = 0;
   out_6995611375067508290[243] = 0;
   out_6995611375067508290[244] = 0;
   out_6995611375067508290[245] = 0;
   out_6995611375067508290[246] = 0;
   out_6995611375067508290[247] = 1;
   out_6995611375067508290[248] = 0;
   out_6995611375067508290[249] = 0;
   out_6995611375067508290[250] = 0;
   out_6995611375067508290[251] = 0;
   out_6995611375067508290[252] = 0;
   out_6995611375067508290[253] = 0;
   out_6995611375067508290[254] = 0;
   out_6995611375067508290[255] = 0;
   out_6995611375067508290[256] = 0;
   out_6995611375067508290[257] = 0;
   out_6995611375067508290[258] = 0;
   out_6995611375067508290[259] = 0;
   out_6995611375067508290[260] = 0;
   out_6995611375067508290[261] = 0;
   out_6995611375067508290[262] = 0;
   out_6995611375067508290[263] = 0;
   out_6995611375067508290[264] = 0;
   out_6995611375067508290[265] = 0;
   out_6995611375067508290[266] = 1;
   out_6995611375067508290[267] = 0;
   out_6995611375067508290[268] = 0;
   out_6995611375067508290[269] = 0;
   out_6995611375067508290[270] = 0;
   out_6995611375067508290[271] = 0;
   out_6995611375067508290[272] = 0;
   out_6995611375067508290[273] = 0;
   out_6995611375067508290[274] = 0;
   out_6995611375067508290[275] = 0;
   out_6995611375067508290[276] = 0;
   out_6995611375067508290[277] = 0;
   out_6995611375067508290[278] = 0;
   out_6995611375067508290[279] = 0;
   out_6995611375067508290[280] = 0;
   out_6995611375067508290[281] = 0;
   out_6995611375067508290[282] = 0;
   out_6995611375067508290[283] = 0;
   out_6995611375067508290[284] = 0;
   out_6995611375067508290[285] = 1;
   out_6995611375067508290[286] = 0;
   out_6995611375067508290[287] = 0;
   out_6995611375067508290[288] = 0;
   out_6995611375067508290[289] = 0;
   out_6995611375067508290[290] = 0;
   out_6995611375067508290[291] = 0;
   out_6995611375067508290[292] = 0;
   out_6995611375067508290[293] = 0;
   out_6995611375067508290[294] = 0;
   out_6995611375067508290[295] = 0;
   out_6995611375067508290[296] = 0;
   out_6995611375067508290[297] = 0;
   out_6995611375067508290[298] = 0;
   out_6995611375067508290[299] = 0;
   out_6995611375067508290[300] = 0;
   out_6995611375067508290[301] = 0;
   out_6995611375067508290[302] = 0;
   out_6995611375067508290[303] = 0;
   out_6995611375067508290[304] = 1;
   out_6995611375067508290[305] = 0;
   out_6995611375067508290[306] = 0;
   out_6995611375067508290[307] = 0;
   out_6995611375067508290[308] = 0;
   out_6995611375067508290[309] = 0;
   out_6995611375067508290[310] = 0;
   out_6995611375067508290[311] = 0;
   out_6995611375067508290[312] = 0;
   out_6995611375067508290[313] = 0;
   out_6995611375067508290[314] = 0;
   out_6995611375067508290[315] = 0;
   out_6995611375067508290[316] = 0;
   out_6995611375067508290[317] = 0;
   out_6995611375067508290[318] = 0;
   out_6995611375067508290[319] = 0;
   out_6995611375067508290[320] = 0;
   out_6995611375067508290[321] = 0;
   out_6995611375067508290[322] = 0;
   out_6995611375067508290[323] = 1;
}
void h_4(double *state, double *unused, double *out_3714895458843600451) {
   out_3714895458843600451[0] = state[6] + state[9];
   out_3714895458843600451[1] = state[7] + state[10];
   out_3714895458843600451[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_2008092580284892232) {
   out_2008092580284892232[0] = 0;
   out_2008092580284892232[1] = 0;
   out_2008092580284892232[2] = 0;
   out_2008092580284892232[3] = 0;
   out_2008092580284892232[4] = 0;
   out_2008092580284892232[5] = 0;
   out_2008092580284892232[6] = 1;
   out_2008092580284892232[7] = 0;
   out_2008092580284892232[8] = 0;
   out_2008092580284892232[9] = 1;
   out_2008092580284892232[10] = 0;
   out_2008092580284892232[11] = 0;
   out_2008092580284892232[12] = 0;
   out_2008092580284892232[13] = 0;
   out_2008092580284892232[14] = 0;
   out_2008092580284892232[15] = 0;
   out_2008092580284892232[16] = 0;
   out_2008092580284892232[17] = 0;
   out_2008092580284892232[18] = 0;
   out_2008092580284892232[19] = 0;
   out_2008092580284892232[20] = 0;
   out_2008092580284892232[21] = 0;
   out_2008092580284892232[22] = 0;
   out_2008092580284892232[23] = 0;
   out_2008092580284892232[24] = 0;
   out_2008092580284892232[25] = 1;
   out_2008092580284892232[26] = 0;
   out_2008092580284892232[27] = 0;
   out_2008092580284892232[28] = 1;
   out_2008092580284892232[29] = 0;
   out_2008092580284892232[30] = 0;
   out_2008092580284892232[31] = 0;
   out_2008092580284892232[32] = 0;
   out_2008092580284892232[33] = 0;
   out_2008092580284892232[34] = 0;
   out_2008092580284892232[35] = 0;
   out_2008092580284892232[36] = 0;
   out_2008092580284892232[37] = 0;
   out_2008092580284892232[38] = 0;
   out_2008092580284892232[39] = 0;
   out_2008092580284892232[40] = 0;
   out_2008092580284892232[41] = 0;
   out_2008092580284892232[42] = 0;
   out_2008092580284892232[43] = 0;
   out_2008092580284892232[44] = 1;
   out_2008092580284892232[45] = 0;
   out_2008092580284892232[46] = 0;
   out_2008092580284892232[47] = 1;
   out_2008092580284892232[48] = 0;
   out_2008092580284892232[49] = 0;
   out_2008092580284892232[50] = 0;
   out_2008092580284892232[51] = 0;
   out_2008092580284892232[52] = 0;
   out_2008092580284892232[53] = 0;
}
void h_10(double *state, double *unused, double *out_144058714348640715) {
   out_144058714348640715[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_144058714348640715[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_144058714348640715[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6768538146622882928) {
   out_6768538146622882928[0] = 0;
   out_6768538146622882928[1] = 9.8100000000000005*cos(state[1]);
   out_6768538146622882928[2] = 0;
   out_6768538146622882928[3] = 0;
   out_6768538146622882928[4] = -state[8];
   out_6768538146622882928[5] = state[7];
   out_6768538146622882928[6] = 0;
   out_6768538146622882928[7] = state[5];
   out_6768538146622882928[8] = -state[4];
   out_6768538146622882928[9] = 0;
   out_6768538146622882928[10] = 0;
   out_6768538146622882928[11] = 0;
   out_6768538146622882928[12] = 1;
   out_6768538146622882928[13] = 0;
   out_6768538146622882928[14] = 0;
   out_6768538146622882928[15] = 1;
   out_6768538146622882928[16] = 0;
   out_6768538146622882928[17] = 0;
   out_6768538146622882928[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6768538146622882928[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6768538146622882928[20] = 0;
   out_6768538146622882928[21] = state[8];
   out_6768538146622882928[22] = 0;
   out_6768538146622882928[23] = -state[6];
   out_6768538146622882928[24] = -state[5];
   out_6768538146622882928[25] = 0;
   out_6768538146622882928[26] = state[3];
   out_6768538146622882928[27] = 0;
   out_6768538146622882928[28] = 0;
   out_6768538146622882928[29] = 0;
   out_6768538146622882928[30] = 0;
   out_6768538146622882928[31] = 1;
   out_6768538146622882928[32] = 0;
   out_6768538146622882928[33] = 0;
   out_6768538146622882928[34] = 1;
   out_6768538146622882928[35] = 0;
   out_6768538146622882928[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6768538146622882928[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6768538146622882928[38] = 0;
   out_6768538146622882928[39] = -state[7];
   out_6768538146622882928[40] = state[6];
   out_6768538146622882928[41] = 0;
   out_6768538146622882928[42] = state[4];
   out_6768538146622882928[43] = -state[3];
   out_6768538146622882928[44] = 0;
   out_6768538146622882928[45] = 0;
   out_6768538146622882928[46] = 0;
   out_6768538146622882928[47] = 0;
   out_6768538146622882928[48] = 0;
   out_6768538146622882928[49] = 0;
   out_6768538146622882928[50] = 1;
   out_6768538146622882928[51] = 0;
   out_6768538146622882928[52] = 0;
   out_6768538146622882928[53] = 1;
}
void h_13(double *state, double *unused, double *out_6588557550924599957) {
   out_6588557550924599957[0] = state[3];
   out_6588557550924599957[1] = state[4];
   out_6588557550924599957[2] = state[5];
}
void H_13(double *state, double *unused, double *out_5220366405617225033) {
   out_5220366405617225033[0] = 0;
   out_5220366405617225033[1] = 0;
   out_5220366405617225033[2] = 0;
   out_5220366405617225033[3] = 1;
   out_5220366405617225033[4] = 0;
   out_5220366405617225033[5] = 0;
   out_5220366405617225033[6] = 0;
   out_5220366405617225033[7] = 0;
   out_5220366405617225033[8] = 0;
   out_5220366405617225033[9] = 0;
   out_5220366405617225033[10] = 0;
   out_5220366405617225033[11] = 0;
   out_5220366405617225033[12] = 0;
   out_5220366405617225033[13] = 0;
   out_5220366405617225033[14] = 0;
   out_5220366405617225033[15] = 0;
   out_5220366405617225033[16] = 0;
   out_5220366405617225033[17] = 0;
   out_5220366405617225033[18] = 0;
   out_5220366405617225033[19] = 0;
   out_5220366405617225033[20] = 0;
   out_5220366405617225033[21] = 0;
   out_5220366405617225033[22] = 1;
   out_5220366405617225033[23] = 0;
   out_5220366405617225033[24] = 0;
   out_5220366405617225033[25] = 0;
   out_5220366405617225033[26] = 0;
   out_5220366405617225033[27] = 0;
   out_5220366405617225033[28] = 0;
   out_5220366405617225033[29] = 0;
   out_5220366405617225033[30] = 0;
   out_5220366405617225033[31] = 0;
   out_5220366405617225033[32] = 0;
   out_5220366405617225033[33] = 0;
   out_5220366405617225033[34] = 0;
   out_5220366405617225033[35] = 0;
   out_5220366405617225033[36] = 0;
   out_5220366405617225033[37] = 0;
   out_5220366405617225033[38] = 0;
   out_5220366405617225033[39] = 0;
   out_5220366405617225033[40] = 0;
   out_5220366405617225033[41] = 1;
   out_5220366405617225033[42] = 0;
   out_5220366405617225033[43] = 0;
   out_5220366405617225033[44] = 0;
   out_5220366405617225033[45] = 0;
   out_5220366405617225033[46] = 0;
   out_5220366405617225033[47] = 0;
   out_5220366405617225033[48] = 0;
   out_5220366405617225033[49] = 0;
   out_5220366405617225033[50] = 0;
   out_5220366405617225033[51] = 0;
   out_5220366405617225033[52] = 0;
   out_5220366405617225033[53] = 0;
}
void h_14(double *state, double *unused, double *out_8672702186703207605) {
   out_8672702186703207605[0] = state[6];
   out_8672702186703207605[1] = state[7];
   out_8672702186703207605[2] = state[8];
}
void H_14(double *state, double *unused, double *out_5971333436624376761) {
   out_5971333436624376761[0] = 0;
   out_5971333436624376761[1] = 0;
   out_5971333436624376761[2] = 0;
   out_5971333436624376761[3] = 0;
   out_5971333436624376761[4] = 0;
   out_5971333436624376761[5] = 0;
   out_5971333436624376761[6] = 1;
   out_5971333436624376761[7] = 0;
   out_5971333436624376761[8] = 0;
   out_5971333436624376761[9] = 0;
   out_5971333436624376761[10] = 0;
   out_5971333436624376761[11] = 0;
   out_5971333436624376761[12] = 0;
   out_5971333436624376761[13] = 0;
   out_5971333436624376761[14] = 0;
   out_5971333436624376761[15] = 0;
   out_5971333436624376761[16] = 0;
   out_5971333436624376761[17] = 0;
   out_5971333436624376761[18] = 0;
   out_5971333436624376761[19] = 0;
   out_5971333436624376761[20] = 0;
   out_5971333436624376761[21] = 0;
   out_5971333436624376761[22] = 0;
   out_5971333436624376761[23] = 0;
   out_5971333436624376761[24] = 0;
   out_5971333436624376761[25] = 1;
   out_5971333436624376761[26] = 0;
   out_5971333436624376761[27] = 0;
   out_5971333436624376761[28] = 0;
   out_5971333436624376761[29] = 0;
   out_5971333436624376761[30] = 0;
   out_5971333436624376761[31] = 0;
   out_5971333436624376761[32] = 0;
   out_5971333436624376761[33] = 0;
   out_5971333436624376761[34] = 0;
   out_5971333436624376761[35] = 0;
   out_5971333436624376761[36] = 0;
   out_5971333436624376761[37] = 0;
   out_5971333436624376761[38] = 0;
   out_5971333436624376761[39] = 0;
   out_5971333436624376761[40] = 0;
   out_5971333436624376761[41] = 0;
   out_5971333436624376761[42] = 0;
   out_5971333436624376761[43] = 0;
   out_5971333436624376761[44] = 1;
   out_5971333436624376761[45] = 0;
   out_5971333436624376761[46] = 0;
   out_5971333436624376761[47] = 0;
   out_5971333436624376761[48] = 0;
   out_5971333436624376761[49] = 0;
   out_5971333436624376761[50] = 0;
   out_5971333436624376761[51] = 0;
   out_5971333436624376761[52] = 0;
   out_5971333436624376761[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_7283166407761929442) {
  err_fun(nom_x, delta_x, out_7283166407761929442);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_546984208695000774) {
  inv_err_fun(nom_x, true_x, out_546984208695000774);
}
void pose_H_mod_fun(double *state, double *out_3827791306191189093) {
  H_mod_fun(state, out_3827791306191189093);
}
void pose_f_fun(double *state, double dt, double *out_6733983040945921210) {
  f_fun(state,  dt, out_6733983040945921210);
}
void pose_F_fun(double *state, double dt, double *out_6995611375067508290) {
  F_fun(state,  dt, out_6995611375067508290);
}
void pose_h_4(double *state, double *unused, double *out_3714895458843600451) {
  h_4(state, unused, out_3714895458843600451);
}
void pose_H_4(double *state, double *unused, double *out_2008092580284892232) {
  H_4(state, unused, out_2008092580284892232);
}
void pose_h_10(double *state, double *unused, double *out_144058714348640715) {
  h_10(state, unused, out_144058714348640715);
}
void pose_H_10(double *state, double *unused, double *out_6768538146622882928) {
  H_10(state, unused, out_6768538146622882928);
}
void pose_h_13(double *state, double *unused, double *out_6588557550924599957) {
  h_13(state, unused, out_6588557550924599957);
}
void pose_H_13(double *state, double *unused, double *out_5220366405617225033) {
  H_13(state, unused, out_5220366405617225033);
}
void pose_h_14(double *state, double *unused, double *out_8672702186703207605) {
  h_14(state, unused, out_8672702186703207605);
}
void pose_H_14(double *state, double *unused, double *out_5971333436624376761) {
  H_14(state, unused, out_5971333436624376761);
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
