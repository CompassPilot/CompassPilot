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
void err_fun(double *nom_x, double *delta_x, double *out_2139705222199814366) {
   out_2139705222199814366[0] = delta_x[0] + nom_x[0];
   out_2139705222199814366[1] = delta_x[1] + nom_x[1];
   out_2139705222199814366[2] = delta_x[2] + nom_x[2];
   out_2139705222199814366[3] = delta_x[3] + nom_x[3];
   out_2139705222199814366[4] = delta_x[4] + nom_x[4];
   out_2139705222199814366[5] = delta_x[5] + nom_x[5];
   out_2139705222199814366[6] = delta_x[6] + nom_x[6];
   out_2139705222199814366[7] = delta_x[7] + nom_x[7];
   out_2139705222199814366[8] = delta_x[8] + nom_x[8];
   out_2139705222199814366[9] = delta_x[9] + nom_x[9];
   out_2139705222199814366[10] = delta_x[10] + nom_x[10];
   out_2139705222199814366[11] = delta_x[11] + nom_x[11];
   out_2139705222199814366[12] = delta_x[12] + nom_x[12];
   out_2139705222199814366[13] = delta_x[13] + nom_x[13];
   out_2139705222199814366[14] = delta_x[14] + nom_x[14];
   out_2139705222199814366[15] = delta_x[15] + nom_x[15];
   out_2139705222199814366[16] = delta_x[16] + nom_x[16];
   out_2139705222199814366[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5823649811361463428) {
   out_5823649811361463428[0] = -nom_x[0] + true_x[0];
   out_5823649811361463428[1] = -nom_x[1] + true_x[1];
   out_5823649811361463428[2] = -nom_x[2] + true_x[2];
   out_5823649811361463428[3] = -nom_x[3] + true_x[3];
   out_5823649811361463428[4] = -nom_x[4] + true_x[4];
   out_5823649811361463428[5] = -nom_x[5] + true_x[5];
   out_5823649811361463428[6] = -nom_x[6] + true_x[6];
   out_5823649811361463428[7] = -nom_x[7] + true_x[7];
   out_5823649811361463428[8] = -nom_x[8] + true_x[8];
   out_5823649811361463428[9] = -nom_x[9] + true_x[9];
   out_5823649811361463428[10] = -nom_x[10] + true_x[10];
   out_5823649811361463428[11] = -nom_x[11] + true_x[11];
   out_5823649811361463428[12] = -nom_x[12] + true_x[12];
   out_5823649811361463428[13] = -nom_x[13] + true_x[13];
   out_5823649811361463428[14] = -nom_x[14] + true_x[14];
   out_5823649811361463428[15] = -nom_x[15] + true_x[15];
   out_5823649811361463428[16] = -nom_x[16] + true_x[16];
   out_5823649811361463428[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_7742649709516102044) {
   out_7742649709516102044[0] = 1.0;
   out_7742649709516102044[1] = 0.0;
   out_7742649709516102044[2] = 0.0;
   out_7742649709516102044[3] = 0.0;
   out_7742649709516102044[4] = 0.0;
   out_7742649709516102044[5] = 0.0;
   out_7742649709516102044[6] = 0.0;
   out_7742649709516102044[7] = 0.0;
   out_7742649709516102044[8] = 0.0;
   out_7742649709516102044[9] = 0.0;
   out_7742649709516102044[10] = 0.0;
   out_7742649709516102044[11] = 0.0;
   out_7742649709516102044[12] = 0.0;
   out_7742649709516102044[13] = 0.0;
   out_7742649709516102044[14] = 0.0;
   out_7742649709516102044[15] = 0.0;
   out_7742649709516102044[16] = 0.0;
   out_7742649709516102044[17] = 0.0;
   out_7742649709516102044[18] = 0.0;
   out_7742649709516102044[19] = 1.0;
   out_7742649709516102044[20] = 0.0;
   out_7742649709516102044[21] = 0.0;
   out_7742649709516102044[22] = 0.0;
   out_7742649709516102044[23] = 0.0;
   out_7742649709516102044[24] = 0.0;
   out_7742649709516102044[25] = 0.0;
   out_7742649709516102044[26] = 0.0;
   out_7742649709516102044[27] = 0.0;
   out_7742649709516102044[28] = 0.0;
   out_7742649709516102044[29] = 0.0;
   out_7742649709516102044[30] = 0.0;
   out_7742649709516102044[31] = 0.0;
   out_7742649709516102044[32] = 0.0;
   out_7742649709516102044[33] = 0.0;
   out_7742649709516102044[34] = 0.0;
   out_7742649709516102044[35] = 0.0;
   out_7742649709516102044[36] = 0.0;
   out_7742649709516102044[37] = 0.0;
   out_7742649709516102044[38] = 1.0;
   out_7742649709516102044[39] = 0.0;
   out_7742649709516102044[40] = 0.0;
   out_7742649709516102044[41] = 0.0;
   out_7742649709516102044[42] = 0.0;
   out_7742649709516102044[43] = 0.0;
   out_7742649709516102044[44] = 0.0;
   out_7742649709516102044[45] = 0.0;
   out_7742649709516102044[46] = 0.0;
   out_7742649709516102044[47] = 0.0;
   out_7742649709516102044[48] = 0.0;
   out_7742649709516102044[49] = 0.0;
   out_7742649709516102044[50] = 0.0;
   out_7742649709516102044[51] = 0.0;
   out_7742649709516102044[52] = 0.0;
   out_7742649709516102044[53] = 0.0;
   out_7742649709516102044[54] = 0.0;
   out_7742649709516102044[55] = 0.0;
   out_7742649709516102044[56] = 0.0;
   out_7742649709516102044[57] = 1.0;
   out_7742649709516102044[58] = 0.0;
   out_7742649709516102044[59] = 0.0;
   out_7742649709516102044[60] = 0.0;
   out_7742649709516102044[61] = 0.0;
   out_7742649709516102044[62] = 0.0;
   out_7742649709516102044[63] = 0.0;
   out_7742649709516102044[64] = 0.0;
   out_7742649709516102044[65] = 0.0;
   out_7742649709516102044[66] = 0.0;
   out_7742649709516102044[67] = 0.0;
   out_7742649709516102044[68] = 0.0;
   out_7742649709516102044[69] = 0.0;
   out_7742649709516102044[70] = 0.0;
   out_7742649709516102044[71] = 0.0;
   out_7742649709516102044[72] = 0.0;
   out_7742649709516102044[73] = 0.0;
   out_7742649709516102044[74] = 0.0;
   out_7742649709516102044[75] = 0.0;
   out_7742649709516102044[76] = 1.0;
   out_7742649709516102044[77] = 0.0;
   out_7742649709516102044[78] = 0.0;
   out_7742649709516102044[79] = 0.0;
   out_7742649709516102044[80] = 0.0;
   out_7742649709516102044[81] = 0.0;
   out_7742649709516102044[82] = 0.0;
   out_7742649709516102044[83] = 0.0;
   out_7742649709516102044[84] = 0.0;
   out_7742649709516102044[85] = 0.0;
   out_7742649709516102044[86] = 0.0;
   out_7742649709516102044[87] = 0.0;
   out_7742649709516102044[88] = 0.0;
   out_7742649709516102044[89] = 0.0;
   out_7742649709516102044[90] = 0.0;
   out_7742649709516102044[91] = 0.0;
   out_7742649709516102044[92] = 0.0;
   out_7742649709516102044[93] = 0.0;
   out_7742649709516102044[94] = 0.0;
   out_7742649709516102044[95] = 1.0;
   out_7742649709516102044[96] = 0.0;
   out_7742649709516102044[97] = 0.0;
   out_7742649709516102044[98] = 0.0;
   out_7742649709516102044[99] = 0.0;
   out_7742649709516102044[100] = 0.0;
   out_7742649709516102044[101] = 0.0;
   out_7742649709516102044[102] = 0.0;
   out_7742649709516102044[103] = 0.0;
   out_7742649709516102044[104] = 0.0;
   out_7742649709516102044[105] = 0.0;
   out_7742649709516102044[106] = 0.0;
   out_7742649709516102044[107] = 0.0;
   out_7742649709516102044[108] = 0.0;
   out_7742649709516102044[109] = 0.0;
   out_7742649709516102044[110] = 0.0;
   out_7742649709516102044[111] = 0.0;
   out_7742649709516102044[112] = 0.0;
   out_7742649709516102044[113] = 0.0;
   out_7742649709516102044[114] = 1.0;
   out_7742649709516102044[115] = 0.0;
   out_7742649709516102044[116] = 0.0;
   out_7742649709516102044[117] = 0.0;
   out_7742649709516102044[118] = 0.0;
   out_7742649709516102044[119] = 0.0;
   out_7742649709516102044[120] = 0.0;
   out_7742649709516102044[121] = 0.0;
   out_7742649709516102044[122] = 0.0;
   out_7742649709516102044[123] = 0.0;
   out_7742649709516102044[124] = 0.0;
   out_7742649709516102044[125] = 0.0;
   out_7742649709516102044[126] = 0.0;
   out_7742649709516102044[127] = 0.0;
   out_7742649709516102044[128] = 0.0;
   out_7742649709516102044[129] = 0.0;
   out_7742649709516102044[130] = 0.0;
   out_7742649709516102044[131] = 0.0;
   out_7742649709516102044[132] = 0.0;
   out_7742649709516102044[133] = 1.0;
   out_7742649709516102044[134] = 0.0;
   out_7742649709516102044[135] = 0.0;
   out_7742649709516102044[136] = 0.0;
   out_7742649709516102044[137] = 0.0;
   out_7742649709516102044[138] = 0.0;
   out_7742649709516102044[139] = 0.0;
   out_7742649709516102044[140] = 0.0;
   out_7742649709516102044[141] = 0.0;
   out_7742649709516102044[142] = 0.0;
   out_7742649709516102044[143] = 0.0;
   out_7742649709516102044[144] = 0.0;
   out_7742649709516102044[145] = 0.0;
   out_7742649709516102044[146] = 0.0;
   out_7742649709516102044[147] = 0.0;
   out_7742649709516102044[148] = 0.0;
   out_7742649709516102044[149] = 0.0;
   out_7742649709516102044[150] = 0.0;
   out_7742649709516102044[151] = 0.0;
   out_7742649709516102044[152] = 1.0;
   out_7742649709516102044[153] = 0.0;
   out_7742649709516102044[154] = 0.0;
   out_7742649709516102044[155] = 0.0;
   out_7742649709516102044[156] = 0.0;
   out_7742649709516102044[157] = 0.0;
   out_7742649709516102044[158] = 0.0;
   out_7742649709516102044[159] = 0.0;
   out_7742649709516102044[160] = 0.0;
   out_7742649709516102044[161] = 0.0;
   out_7742649709516102044[162] = 0.0;
   out_7742649709516102044[163] = 0.0;
   out_7742649709516102044[164] = 0.0;
   out_7742649709516102044[165] = 0.0;
   out_7742649709516102044[166] = 0.0;
   out_7742649709516102044[167] = 0.0;
   out_7742649709516102044[168] = 0.0;
   out_7742649709516102044[169] = 0.0;
   out_7742649709516102044[170] = 0.0;
   out_7742649709516102044[171] = 1.0;
   out_7742649709516102044[172] = 0.0;
   out_7742649709516102044[173] = 0.0;
   out_7742649709516102044[174] = 0.0;
   out_7742649709516102044[175] = 0.0;
   out_7742649709516102044[176] = 0.0;
   out_7742649709516102044[177] = 0.0;
   out_7742649709516102044[178] = 0.0;
   out_7742649709516102044[179] = 0.0;
   out_7742649709516102044[180] = 0.0;
   out_7742649709516102044[181] = 0.0;
   out_7742649709516102044[182] = 0.0;
   out_7742649709516102044[183] = 0.0;
   out_7742649709516102044[184] = 0.0;
   out_7742649709516102044[185] = 0.0;
   out_7742649709516102044[186] = 0.0;
   out_7742649709516102044[187] = 0.0;
   out_7742649709516102044[188] = 0.0;
   out_7742649709516102044[189] = 0.0;
   out_7742649709516102044[190] = 1.0;
   out_7742649709516102044[191] = 0.0;
   out_7742649709516102044[192] = 0.0;
   out_7742649709516102044[193] = 0.0;
   out_7742649709516102044[194] = 0.0;
   out_7742649709516102044[195] = 0.0;
   out_7742649709516102044[196] = 0.0;
   out_7742649709516102044[197] = 0.0;
   out_7742649709516102044[198] = 0.0;
   out_7742649709516102044[199] = 0.0;
   out_7742649709516102044[200] = 0.0;
   out_7742649709516102044[201] = 0.0;
   out_7742649709516102044[202] = 0.0;
   out_7742649709516102044[203] = 0.0;
   out_7742649709516102044[204] = 0.0;
   out_7742649709516102044[205] = 0.0;
   out_7742649709516102044[206] = 0.0;
   out_7742649709516102044[207] = 0.0;
   out_7742649709516102044[208] = 0.0;
   out_7742649709516102044[209] = 1.0;
   out_7742649709516102044[210] = 0.0;
   out_7742649709516102044[211] = 0.0;
   out_7742649709516102044[212] = 0.0;
   out_7742649709516102044[213] = 0.0;
   out_7742649709516102044[214] = 0.0;
   out_7742649709516102044[215] = 0.0;
   out_7742649709516102044[216] = 0.0;
   out_7742649709516102044[217] = 0.0;
   out_7742649709516102044[218] = 0.0;
   out_7742649709516102044[219] = 0.0;
   out_7742649709516102044[220] = 0.0;
   out_7742649709516102044[221] = 0.0;
   out_7742649709516102044[222] = 0.0;
   out_7742649709516102044[223] = 0.0;
   out_7742649709516102044[224] = 0.0;
   out_7742649709516102044[225] = 0.0;
   out_7742649709516102044[226] = 0.0;
   out_7742649709516102044[227] = 0.0;
   out_7742649709516102044[228] = 1.0;
   out_7742649709516102044[229] = 0.0;
   out_7742649709516102044[230] = 0.0;
   out_7742649709516102044[231] = 0.0;
   out_7742649709516102044[232] = 0.0;
   out_7742649709516102044[233] = 0.0;
   out_7742649709516102044[234] = 0.0;
   out_7742649709516102044[235] = 0.0;
   out_7742649709516102044[236] = 0.0;
   out_7742649709516102044[237] = 0.0;
   out_7742649709516102044[238] = 0.0;
   out_7742649709516102044[239] = 0.0;
   out_7742649709516102044[240] = 0.0;
   out_7742649709516102044[241] = 0.0;
   out_7742649709516102044[242] = 0.0;
   out_7742649709516102044[243] = 0.0;
   out_7742649709516102044[244] = 0.0;
   out_7742649709516102044[245] = 0.0;
   out_7742649709516102044[246] = 0.0;
   out_7742649709516102044[247] = 1.0;
   out_7742649709516102044[248] = 0.0;
   out_7742649709516102044[249] = 0.0;
   out_7742649709516102044[250] = 0.0;
   out_7742649709516102044[251] = 0.0;
   out_7742649709516102044[252] = 0.0;
   out_7742649709516102044[253] = 0.0;
   out_7742649709516102044[254] = 0.0;
   out_7742649709516102044[255] = 0.0;
   out_7742649709516102044[256] = 0.0;
   out_7742649709516102044[257] = 0.0;
   out_7742649709516102044[258] = 0.0;
   out_7742649709516102044[259] = 0.0;
   out_7742649709516102044[260] = 0.0;
   out_7742649709516102044[261] = 0.0;
   out_7742649709516102044[262] = 0.0;
   out_7742649709516102044[263] = 0.0;
   out_7742649709516102044[264] = 0.0;
   out_7742649709516102044[265] = 0.0;
   out_7742649709516102044[266] = 1.0;
   out_7742649709516102044[267] = 0.0;
   out_7742649709516102044[268] = 0.0;
   out_7742649709516102044[269] = 0.0;
   out_7742649709516102044[270] = 0.0;
   out_7742649709516102044[271] = 0.0;
   out_7742649709516102044[272] = 0.0;
   out_7742649709516102044[273] = 0.0;
   out_7742649709516102044[274] = 0.0;
   out_7742649709516102044[275] = 0.0;
   out_7742649709516102044[276] = 0.0;
   out_7742649709516102044[277] = 0.0;
   out_7742649709516102044[278] = 0.0;
   out_7742649709516102044[279] = 0.0;
   out_7742649709516102044[280] = 0.0;
   out_7742649709516102044[281] = 0.0;
   out_7742649709516102044[282] = 0.0;
   out_7742649709516102044[283] = 0.0;
   out_7742649709516102044[284] = 0.0;
   out_7742649709516102044[285] = 1.0;
   out_7742649709516102044[286] = 0.0;
   out_7742649709516102044[287] = 0.0;
   out_7742649709516102044[288] = 0.0;
   out_7742649709516102044[289] = 0.0;
   out_7742649709516102044[290] = 0.0;
   out_7742649709516102044[291] = 0.0;
   out_7742649709516102044[292] = 0.0;
   out_7742649709516102044[293] = 0.0;
   out_7742649709516102044[294] = 0.0;
   out_7742649709516102044[295] = 0.0;
   out_7742649709516102044[296] = 0.0;
   out_7742649709516102044[297] = 0.0;
   out_7742649709516102044[298] = 0.0;
   out_7742649709516102044[299] = 0.0;
   out_7742649709516102044[300] = 0.0;
   out_7742649709516102044[301] = 0.0;
   out_7742649709516102044[302] = 0.0;
   out_7742649709516102044[303] = 0.0;
   out_7742649709516102044[304] = 1.0;
   out_7742649709516102044[305] = 0.0;
   out_7742649709516102044[306] = 0.0;
   out_7742649709516102044[307] = 0.0;
   out_7742649709516102044[308] = 0.0;
   out_7742649709516102044[309] = 0.0;
   out_7742649709516102044[310] = 0.0;
   out_7742649709516102044[311] = 0.0;
   out_7742649709516102044[312] = 0.0;
   out_7742649709516102044[313] = 0.0;
   out_7742649709516102044[314] = 0.0;
   out_7742649709516102044[315] = 0.0;
   out_7742649709516102044[316] = 0.0;
   out_7742649709516102044[317] = 0.0;
   out_7742649709516102044[318] = 0.0;
   out_7742649709516102044[319] = 0.0;
   out_7742649709516102044[320] = 0.0;
   out_7742649709516102044[321] = 0.0;
   out_7742649709516102044[322] = 0.0;
   out_7742649709516102044[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_3760212722055020200) {
   out_3760212722055020200[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_3760212722055020200[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_3760212722055020200[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_3760212722055020200[3] = dt*state[12] + state[3];
   out_3760212722055020200[4] = dt*state[13] + state[4];
   out_3760212722055020200[5] = dt*state[14] + state[5];
   out_3760212722055020200[6] = state[6];
   out_3760212722055020200[7] = state[7];
   out_3760212722055020200[8] = state[8];
   out_3760212722055020200[9] = state[9];
   out_3760212722055020200[10] = state[10];
   out_3760212722055020200[11] = state[11];
   out_3760212722055020200[12] = state[12];
   out_3760212722055020200[13] = state[13];
   out_3760212722055020200[14] = state[14];
   out_3760212722055020200[15] = state[15];
   out_3760212722055020200[16] = state[16];
   out_3760212722055020200[17] = state[17];
}
void F_fun(double *state, double dt, double *out_8097536246104009244) {
   out_8097536246104009244[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8097536246104009244[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8097536246104009244[2] = 0;
   out_8097536246104009244[3] = 0;
   out_8097536246104009244[4] = 0;
   out_8097536246104009244[5] = 0;
   out_8097536246104009244[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8097536246104009244[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8097536246104009244[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_8097536246104009244[9] = 0;
   out_8097536246104009244[10] = 0;
   out_8097536246104009244[11] = 0;
   out_8097536246104009244[12] = 0;
   out_8097536246104009244[13] = 0;
   out_8097536246104009244[14] = 0;
   out_8097536246104009244[15] = 0;
   out_8097536246104009244[16] = 0;
   out_8097536246104009244[17] = 0;
   out_8097536246104009244[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8097536246104009244[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8097536246104009244[20] = 0;
   out_8097536246104009244[21] = 0;
   out_8097536246104009244[22] = 0;
   out_8097536246104009244[23] = 0;
   out_8097536246104009244[24] = 0;
   out_8097536246104009244[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8097536246104009244[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_8097536246104009244[27] = 0;
   out_8097536246104009244[28] = 0;
   out_8097536246104009244[29] = 0;
   out_8097536246104009244[30] = 0;
   out_8097536246104009244[31] = 0;
   out_8097536246104009244[32] = 0;
   out_8097536246104009244[33] = 0;
   out_8097536246104009244[34] = 0;
   out_8097536246104009244[35] = 0;
   out_8097536246104009244[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8097536246104009244[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8097536246104009244[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8097536246104009244[39] = 0;
   out_8097536246104009244[40] = 0;
   out_8097536246104009244[41] = 0;
   out_8097536246104009244[42] = 0;
   out_8097536246104009244[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8097536246104009244[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_8097536246104009244[45] = 0;
   out_8097536246104009244[46] = 0;
   out_8097536246104009244[47] = 0;
   out_8097536246104009244[48] = 0;
   out_8097536246104009244[49] = 0;
   out_8097536246104009244[50] = 0;
   out_8097536246104009244[51] = 0;
   out_8097536246104009244[52] = 0;
   out_8097536246104009244[53] = 0;
   out_8097536246104009244[54] = 0;
   out_8097536246104009244[55] = 0;
   out_8097536246104009244[56] = 0;
   out_8097536246104009244[57] = 1;
   out_8097536246104009244[58] = 0;
   out_8097536246104009244[59] = 0;
   out_8097536246104009244[60] = 0;
   out_8097536246104009244[61] = 0;
   out_8097536246104009244[62] = 0;
   out_8097536246104009244[63] = 0;
   out_8097536246104009244[64] = 0;
   out_8097536246104009244[65] = 0;
   out_8097536246104009244[66] = dt;
   out_8097536246104009244[67] = 0;
   out_8097536246104009244[68] = 0;
   out_8097536246104009244[69] = 0;
   out_8097536246104009244[70] = 0;
   out_8097536246104009244[71] = 0;
   out_8097536246104009244[72] = 0;
   out_8097536246104009244[73] = 0;
   out_8097536246104009244[74] = 0;
   out_8097536246104009244[75] = 0;
   out_8097536246104009244[76] = 1;
   out_8097536246104009244[77] = 0;
   out_8097536246104009244[78] = 0;
   out_8097536246104009244[79] = 0;
   out_8097536246104009244[80] = 0;
   out_8097536246104009244[81] = 0;
   out_8097536246104009244[82] = 0;
   out_8097536246104009244[83] = 0;
   out_8097536246104009244[84] = 0;
   out_8097536246104009244[85] = dt;
   out_8097536246104009244[86] = 0;
   out_8097536246104009244[87] = 0;
   out_8097536246104009244[88] = 0;
   out_8097536246104009244[89] = 0;
   out_8097536246104009244[90] = 0;
   out_8097536246104009244[91] = 0;
   out_8097536246104009244[92] = 0;
   out_8097536246104009244[93] = 0;
   out_8097536246104009244[94] = 0;
   out_8097536246104009244[95] = 1;
   out_8097536246104009244[96] = 0;
   out_8097536246104009244[97] = 0;
   out_8097536246104009244[98] = 0;
   out_8097536246104009244[99] = 0;
   out_8097536246104009244[100] = 0;
   out_8097536246104009244[101] = 0;
   out_8097536246104009244[102] = 0;
   out_8097536246104009244[103] = 0;
   out_8097536246104009244[104] = dt;
   out_8097536246104009244[105] = 0;
   out_8097536246104009244[106] = 0;
   out_8097536246104009244[107] = 0;
   out_8097536246104009244[108] = 0;
   out_8097536246104009244[109] = 0;
   out_8097536246104009244[110] = 0;
   out_8097536246104009244[111] = 0;
   out_8097536246104009244[112] = 0;
   out_8097536246104009244[113] = 0;
   out_8097536246104009244[114] = 1;
   out_8097536246104009244[115] = 0;
   out_8097536246104009244[116] = 0;
   out_8097536246104009244[117] = 0;
   out_8097536246104009244[118] = 0;
   out_8097536246104009244[119] = 0;
   out_8097536246104009244[120] = 0;
   out_8097536246104009244[121] = 0;
   out_8097536246104009244[122] = 0;
   out_8097536246104009244[123] = 0;
   out_8097536246104009244[124] = 0;
   out_8097536246104009244[125] = 0;
   out_8097536246104009244[126] = 0;
   out_8097536246104009244[127] = 0;
   out_8097536246104009244[128] = 0;
   out_8097536246104009244[129] = 0;
   out_8097536246104009244[130] = 0;
   out_8097536246104009244[131] = 0;
   out_8097536246104009244[132] = 0;
   out_8097536246104009244[133] = 1;
   out_8097536246104009244[134] = 0;
   out_8097536246104009244[135] = 0;
   out_8097536246104009244[136] = 0;
   out_8097536246104009244[137] = 0;
   out_8097536246104009244[138] = 0;
   out_8097536246104009244[139] = 0;
   out_8097536246104009244[140] = 0;
   out_8097536246104009244[141] = 0;
   out_8097536246104009244[142] = 0;
   out_8097536246104009244[143] = 0;
   out_8097536246104009244[144] = 0;
   out_8097536246104009244[145] = 0;
   out_8097536246104009244[146] = 0;
   out_8097536246104009244[147] = 0;
   out_8097536246104009244[148] = 0;
   out_8097536246104009244[149] = 0;
   out_8097536246104009244[150] = 0;
   out_8097536246104009244[151] = 0;
   out_8097536246104009244[152] = 1;
   out_8097536246104009244[153] = 0;
   out_8097536246104009244[154] = 0;
   out_8097536246104009244[155] = 0;
   out_8097536246104009244[156] = 0;
   out_8097536246104009244[157] = 0;
   out_8097536246104009244[158] = 0;
   out_8097536246104009244[159] = 0;
   out_8097536246104009244[160] = 0;
   out_8097536246104009244[161] = 0;
   out_8097536246104009244[162] = 0;
   out_8097536246104009244[163] = 0;
   out_8097536246104009244[164] = 0;
   out_8097536246104009244[165] = 0;
   out_8097536246104009244[166] = 0;
   out_8097536246104009244[167] = 0;
   out_8097536246104009244[168] = 0;
   out_8097536246104009244[169] = 0;
   out_8097536246104009244[170] = 0;
   out_8097536246104009244[171] = 1;
   out_8097536246104009244[172] = 0;
   out_8097536246104009244[173] = 0;
   out_8097536246104009244[174] = 0;
   out_8097536246104009244[175] = 0;
   out_8097536246104009244[176] = 0;
   out_8097536246104009244[177] = 0;
   out_8097536246104009244[178] = 0;
   out_8097536246104009244[179] = 0;
   out_8097536246104009244[180] = 0;
   out_8097536246104009244[181] = 0;
   out_8097536246104009244[182] = 0;
   out_8097536246104009244[183] = 0;
   out_8097536246104009244[184] = 0;
   out_8097536246104009244[185] = 0;
   out_8097536246104009244[186] = 0;
   out_8097536246104009244[187] = 0;
   out_8097536246104009244[188] = 0;
   out_8097536246104009244[189] = 0;
   out_8097536246104009244[190] = 1;
   out_8097536246104009244[191] = 0;
   out_8097536246104009244[192] = 0;
   out_8097536246104009244[193] = 0;
   out_8097536246104009244[194] = 0;
   out_8097536246104009244[195] = 0;
   out_8097536246104009244[196] = 0;
   out_8097536246104009244[197] = 0;
   out_8097536246104009244[198] = 0;
   out_8097536246104009244[199] = 0;
   out_8097536246104009244[200] = 0;
   out_8097536246104009244[201] = 0;
   out_8097536246104009244[202] = 0;
   out_8097536246104009244[203] = 0;
   out_8097536246104009244[204] = 0;
   out_8097536246104009244[205] = 0;
   out_8097536246104009244[206] = 0;
   out_8097536246104009244[207] = 0;
   out_8097536246104009244[208] = 0;
   out_8097536246104009244[209] = 1;
   out_8097536246104009244[210] = 0;
   out_8097536246104009244[211] = 0;
   out_8097536246104009244[212] = 0;
   out_8097536246104009244[213] = 0;
   out_8097536246104009244[214] = 0;
   out_8097536246104009244[215] = 0;
   out_8097536246104009244[216] = 0;
   out_8097536246104009244[217] = 0;
   out_8097536246104009244[218] = 0;
   out_8097536246104009244[219] = 0;
   out_8097536246104009244[220] = 0;
   out_8097536246104009244[221] = 0;
   out_8097536246104009244[222] = 0;
   out_8097536246104009244[223] = 0;
   out_8097536246104009244[224] = 0;
   out_8097536246104009244[225] = 0;
   out_8097536246104009244[226] = 0;
   out_8097536246104009244[227] = 0;
   out_8097536246104009244[228] = 1;
   out_8097536246104009244[229] = 0;
   out_8097536246104009244[230] = 0;
   out_8097536246104009244[231] = 0;
   out_8097536246104009244[232] = 0;
   out_8097536246104009244[233] = 0;
   out_8097536246104009244[234] = 0;
   out_8097536246104009244[235] = 0;
   out_8097536246104009244[236] = 0;
   out_8097536246104009244[237] = 0;
   out_8097536246104009244[238] = 0;
   out_8097536246104009244[239] = 0;
   out_8097536246104009244[240] = 0;
   out_8097536246104009244[241] = 0;
   out_8097536246104009244[242] = 0;
   out_8097536246104009244[243] = 0;
   out_8097536246104009244[244] = 0;
   out_8097536246104009244[245] = 0;
   out_8097536246104009244[246] = 0;
   out_8097536246104009244[247] = 1;
   out_8097536246104009244[248] = 0;
   out_8097536246104009244[249] = 0;
   out_8097536246104009244[250] = 0;
   out_8097536246104009244[251] = 0;
   out_8097536246104009244[252] = 0;
   out_8097536246104009244[253] = 0;
   out_8097536246104009244[254] = 0;
   out_8097536246104009244[255] = 0;
   out_8097536246104009244[256] = 0;
   out_8097536246104009244[257] = 0;
   out_8097536246104009244[258] = 0;
   out_8097536246104009244[259] = 0;
   out_8097536246104009244[260] = 0;
   out_8097536246104009244[261] = 0;
   out_8097536246104009244[262] = 0;
   out_8097536246104009244[263] = 0;
   out_8097536246104009244[264] = 0;
   out_8097536246104009244[265] = 0;
   out_8097536246104009244[266] = 1;
   out_8097536246104009244[267] = 0;
   out_8097536246104009244[268] = 0;
   out_8097536246104009244[269] = 0;
   out_8097536246104009244[270] = 0;
   out_8097536246104009244[271] = 0;
   out_8097536246104009244[272] = 0;
   out_8097536246104009244[273] = 0;
   out_8097536246104009244[274] = 0;
   out_8097536246104009244[275] = 0;
   out_8097536246104009244[276] = 0;
   out_8097536246104009244[277] = 0;
   out_8097536246104009244[278] = 0;
   out_8097536246104009244[279] = 0;
   out_8097536246104009244[280] = 0;
   out_8097536246104009244[281] = 0;
   out_8097536246104009244[282] = 0;
   out_8097536246104009244[283] = 0;
   out_8097536246104009244[284] = 0;
   out_8097536246104009244[285] = 1;
   out_8097536246104009244[286] = 0;
   out_8097536246104009244[287] = 0;
   out_8097536246104009244[288] = 0;
   out_8097536246104009244[289] = 0;
   out_8097536246104009244[290] = 0;
   out_8097536246104009244[291] = 0;
   out_8097536246104009244[292] = 0;
   out_8097536246104009244[293] = 0;
   out_8097536246104009244[294] = 0;
   out_8097536246104009244[295] = 0;
   out_8097536246104009244[296] = 0;
   out_8097536246104009244[297] = 0;
   out_8097536246104009244[298] = 0;
   out_8097536246104009244[299] = 0;
   out_8097536246104009244[300] = 0;
   out_8097536246104009244[301] = 0;
   out_8097536246104009244[302] = 0;
   out_8097536246104009244[303] = 0;
   out_8097536246104009244[304] = 1;
   out_8097536246104009244[305] = 0;
   out_8097536246104009244[306] = 0;
   out_8097536246104009244[307] = 0;
   out_8097536246104009244[308] = 0;
   out_8097536246104009244[309] = 0;
   out_8097536246104009244[310] = 0;
   out_8097536246104009244[311] = 0;
   out_8097536246104009244[312] = 0;
   out_8097536246104009244[313] = 0;
   out_8097536246104009244[314] = 0;
   out_8097536246104009244[315] = 0;
   out_8097536246104009244[316] = 0;
   out_8097536246104009244[317] = 0;
   out_8097536246104009244[318] = 0;
   out_8097536246104009244[319] = 0;
   out_8097536246104009244[320] = 0;
   out_8097536246104009244[321] = 0;
   out_8097536246104009244[322] = 0;
   out_8097536246104009244[323] = 1;
}
void h_4(double *state, double *unused, double *out_3390290786106786870) {
   out_3390290786106786870[0] = state[6] + state[9];
   out_3390290786106786870[1] = state[7] + state[10];
   out_3390290786106786870[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_4468427630725152791) {
   out_4468427630725152791[0] = 0;
   out_4468427630725152791[1] = 0;
   out_4468427630725152791[2] = 0;
   out_4468427630725152791[3] = 0;
   out_4468427630725152791[4] = 0;
   out_4468427630725152791[5] = 0;
   out_4468427630725152791[6] = 1;
   out_4468427630725152791[7] = 0;
   out_4468427630725152791[8] = 0;
   out_4468427630725152791[9] = 1;
   out_4468427630725152791[10] = 0;
   out_4468427630725152791[11] = 0;
   out_4468427630725152791[12] = 0;
   out_4468427630725152791[13] = 0;
   out_4468427630725152791[14] = 0;
   out_4468427630725152791[15] = 0;
   out_4468427630725152791[16] = 0;
   out_4468427630725152791[17] = 0;
   out_4468427630725152791[18] = 0;
   out_4468427630725152791[19] = 0;
   out_4468427630725152791[20] = 0;
   out_4468427630725152791[21] = 0;
   out_4468427630725152791[22] = 0;
   out_4468427630725152791[23] = 0;
   out_4468427630725152791[24] = 0;
   out_4468427630725152791[25] = 1;
   out_4468427630725152791[26] = 0;
   out_4468427630725152791[27] = 0;
   out_4468427630725152791[28] = 1;
   out_4468427630725152791[29] = 0;
   out_4468427630725152791[30] = 0;
   out_4468427630725152791[31] = 0;
   out_4468427630725152791[32] = 0;
   out_4468427630725152791[33] = 0;
   out_4468427630725152791[34] = 0;
   out_4468427630725152791[35] = 0;
   out_4468427630725152791[36] = 0;
   out_4468427630725152791[37] = 0;
   out_4468427630725152791[38] = 0;
   out_4468427630725152791[39] = 0;
   out_4468427630725152791[40] = 0;
   out_4468427630725152791[41] = 0;
   out_4468427630725152791[42] = 0;
   out_4468427630725152791[43] = 0;
   out_4468427630725152791[44] = 1;
   out_4468427630725152791[45] = 0;
   out_4468427630725152791[46] = 0;
   out_4468427630725152791[47] = 1;
   out_4468427630725152791[48] = 0;
   out_4468427630725152791[49] = 0;
   out_4468427630725152791[50] = 0;
   out_4468427630725152791[51] = 0;
   out_4468427630725152791[52] = 0;
   out_4468427630725152791[53] = 0;
}
void h_10(double *state, double *unused, double *out_3462457376472911907) {
   out_3462457376472911907[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_3462457376472911907[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_3462457376472911907[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_6419953993889457901) {
   out_6419953993889457901[0] = 0;
   out_6419953993889457901[1] = 9.8100000000000005*cos(state[1]);
   out_6419953993889457901[2] = 0;
   out_6419953993889457901[3] = 0;
   out_6419953993889457901[4] = -state[8];
   out_6419953993889457901[5] = state[7];
   out_6419953993889457901[6] = 0;
   out_6419953993889457901[7] = state[5];
   out_6419953993889457901[8] = -state[4];
   out_6419953993889457901[9] = 0;
   out_6419953993889457901[10] = 0;
   out_6419953993889457901[11] = 0;
   out_6419953993889457901[12] = 1;
   out_6419953993889457901[13] = 0;
   out_6419953993889457901[14] = 0;
   out_6419953993889457901[15] = 1;
   out_6419953993889457901[16] = 0;
   out_6419953993889457901[17] = 0;
   out_6419953993889457901[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_6419953993889457901[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_6419953993889457901[20] = 0;
   out_6419953993889457901[21] = state[8];
   out_6419953993889457901[22] = 0;
   out_6419953993889457901[23] = -state[6];
   out_6419953993889457901[24] = -state[5];
   out_6419953993889457901[25] = 0;
   out_6419953993889457901[26] = state[3];
   out_6419953993889457901[27] = 0;
   out_6419953993889457901[28] = 0;
   out_6419953993889457901[29] = 0;
   out_6419953993889457901[30] = 0;
   out_6419953993889457901[31] = 1;
   out_6419953993889457901[32] = 0;
   out_6419953993889457901[33] = 0;
   out_6419953993889457901[34] = 1;
   out_6419953993889457901[35] = 0;
   out_6419953993889457901[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_6419953993889457901[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_6419953993889457901[38] = 0;
   out_6419953993889457901[39] = -state[7];
   out_6419953993889457901[40] = state[6];
   out_6419953993889457901[41] = 0;
   out_6419953993889457901[42] = state[4];
   out_6419953993889457901[43] = -state[3];
   out_6419953993889457901[44] = 0;
   out_6419953993889457901[45] = 0;
   out_6419953993889457901[46] = 0;
   out_6419953993889457901[47] = 0;
   out_6419953993889457901[48] = 0;
   out_6419953993889457901[49] = 0;
   out_6419953993889457901[50] = 1;
   out_6419953993889457901[51] = 0;
   out_6419953993889457901[52] = 0;
   out_6419953993889457901[53] = 1;
}
void h_13(double *state, double *unused, double *out_4244633994094952731) {
   out_4244633994094952731[0] = state[3];
   out_4244633994094952731[1] = state[4];
   out_4244633994094952731[2] = state[5];
}
void H_13(double *state, double *unused, double *out_7680701456057485592) {
   out_7680701456057485592[0] = 0;
   out_7680701456057485592[1] = 0;
   out_7680701456057485592[2] = 0;
   out_7680701456057485592[3] = 1;
   out_7680701456057485592[4] = 0;
   out_7680701456057485592[5] = 0;
   out_7680701456057485592[6] = 0;
   out_7680701456057485592[7] = 0;
   out_7680701456057485592[8] = 0;
   out_7680701456057485592[9] = 0;
   out_7680701456057485592[10] = 0;
   out_7680701456057485592[11] = 0;
   out_7680701456057485592[12] = 0;
   out_7680701456057485592[13] = 0;
   out_7680701456057485592[14] = 0;
   out_7680701456057485592[15] = 0;
   out_7680701456057485592[16] = 0;
   out_7680701456057485592[17] = 0;
   out_7680701456057485592[18] = 0;
   out_7680701456057485592[19] = 0;
   out_7680701456057485592[20] = 0;
   out_7680701456057485592[21] = 0;
   out_7680701456057485592[22] = 1;
   out_7680701456057485592[23] = 0;
   out_7680701456057485592[24] = 0;
   out_7680701456057485592[25] = 0;
   out_7680701456057485592[26] = 0;
   out_7680701456057485592[27] = 0;
   out_7680701456057485592[28] = 0;
   out_7680701456057485592[29] = 0;
   out_7680701456057485592[30] = 0;
   out_7680701456057485592[31] = 0;
   out_7680701456057485592[32] = 0;
   out_7680701456057485592[33] = 0;
   out_7680701456057485592[34] = 0;
   out_7680701456057485592[35] = 0;
   out_7680701456057485592[36] = 0;
   out_7680701456057485592[37] = 0;
   out_7680701456057485592[38] = 0;
   out_7680701456057485592[39] = 0;
   out_7680701456057485592[40] = 0;
   out_7680701456057485592[41] = 1;
   out_7680701456057485592[42] = 0;
   out_7680701456057485592[43] = 0;
   out_7680701456057485592[44] = 0;
   out_7680701456057485592[45] = 0;
   out_7680701456057485592[46] = 0;
   out_7680701456057485592[47] = 0;
   out_7680701456057485592[48] = 0;
   out_7680701456057485592[49] = 0;
   out_7680701456057485592[50] = 0;
   out_7680701456057485592[51] = 0;
   out_7680701456057485592[52] = 0;
   out_7680701456057485592[53] = 0;
}
void h_14(double *state, double *unused, double *out_4959751181186855862) {
   out_4959751181186855862[0] = state[6];
   out_4959751181186855862[1] = state[7];
   out_4959751181186855862[2] = state[8];
}
void H_14(double *state, double *unused, double *out_8431668487064637320) {
   out_8431668487064637320[0] = 0;
   out_8431668487064637320[1] = 0;
   out_8431668487064637320[2] = 0;
   out_8431668487064637320[3] = 0;
   out_8431668487064637320[4] = 0;
   out_8431668487064637320[5] = 0;
   out_8431668487064637320[6] = 1;
   out_8431668487064637320[7] = 0;
   out_8431668487064637320[8] = 0;
   out_8431668487064637320[9] = 0;
   out_8431668487064637320[10] = 0;
   out_8431668487064637320[11] = 0;
   out_8431668487064637320[12] = 0;
   out_8431668487064637320[13] = 0;
   out_8431668487064637320[14] = 0;
   out_8431668487064637320[15] = 0;
   out_8431668487064637320[16] = 0;
   out_8431668487064637320[17] = 0;
   out_8431668487064637320[18] = 0;
   out_8431668487064637320[19] = 0;
   out_8431668487064637320[20] = 0;
   out_8431668487064637320[21] = 0;
   out_8431668487064637320[22] = 0;
   out_8431668487064637320[23] = 0;
   out_8431668487064637320[24] = 0;
   out_8431668487064637320[25] = 1;
   out_8431668487064637320[26] = 0;
   out_8431668487064637320[27] = 0;
   out_8431668487064637320[28] = 0;
   out_8431668487064637320[29] = 0;
   out_8431668487064637320[30] = 0;
   out_8431668487064637320[31] = 0;
   out_8431668487064637320[32] = 0;
   out_8431668487064637320[33] = 0;
   out_8431668487064637320[34] = 0;
   out_8431668487064637320[35] = 0;
   out_8431668487064637320[36] = 0;
   out_8431668487064637320[37] = 0;
   out_8431668487064637320[38] = 0;
   out_8431668487064637320[39] = 0;
   out_8431668487064637320[40] = 0;
   out_8431668487064637320[41] = 0;
   out_8431668487064637320[42] = 0;
   out_8431668487064637320[43] = 0;
   out_8431668487064637320[44] = 1;
   out_8431668487064637320[45] = 0;
   out_8431668487064637320[46] = 0;
   out_8431668487064637320[47] = 0;
   out_8431668487064637320[48] = 0;
   out_8431668487064637320[49] = 0;
   out_8431668487064637320[50] = 0;
   out_8431668487064637320[51] = 0;
   out_8431668487064637320[52] = 0;
   out_8431668487064637320[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_2139705222199814366) {
  err_fun(nom_x, delta_x, out_2139705222199814366);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5823649811361463428) {
  inv_err_fun(nom_x, true_x, out_5823649811361463428);
}
void pose_H_mod_fun(double *state, double *out_7742649709516102044) {
  H_mod_fun(state, out_7742649709516102044);
}
void pose_f_fun(double *state, double dt, double *out_3760212722055020200) {
  f_fun(state,  dt, out_3760212722055020200);
}
void pose_F_fun(double *state, double dt, double *out_8097536246104009244) {
  F_fun(state,  dt, out_8097536246104009244);
}
void pose_h_4(double *state, double *unused, double *out_3390290786106786870) {
  h_4(state, unused, out_3390290786106786870);
}
void pose_H_4(double *state, double *unused, double *out_4468427630725152791) {
  H_4(state, unused, out_4468427630725152791);
}
void pose_h_10(double *state, double *unused, double *out_3462457376472911907) {
  h_10(state, unused, out_3462457376472911907);
}
void pose_H_10(double *state, double *unused, double *out_6419953993889457901) {
  H_10(state, unused, out_6419953993889457901);
}
void pose_h_13(double *state, double *unused, double *out_4244633994094952731) {
  h_13(state, unused, out_4244633994094952731);
}
void pose_H_13(double *state, double *unused, double *out_7680701456057485592) {
  H_13(state, unused, out_7680701456057485592);
}
void pose_h_14(double *state, double *unused, double *out_4959751181186855862) {
  h_14(state, unused, out_4959751181186855862);
}
void pose_H_14(double *state, double *unused, double *out_8431668487064637320) {
  H_14(state, unused, out_8431668487064637320);
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
