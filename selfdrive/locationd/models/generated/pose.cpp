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
void err_fun(double *nom_x, double *delta_x, double *out_6512097809109486594) {
   out_6512097809109486594[0] = delta_x[0] + nom_x[0];
   out_6512097809109486594[1] = delta_x[1] + nom_x[1];
   out_6512097809109486594[2] = delta_x[2] + nom_x[2];
   out_6512097809109486594[3] = delta_x[3] + nom_x[3];
   out_6512097809109486594[4] = delta_x[4] + nom_x[4];
   out_6512097809109486594[5] = delta_x[5] + nom_x[5];
   out_6512097809109486594[6] = delta_x[6] + nom_x[6];
   out_6512097809109486594[7] = delta_x[7] + nom_x[7];
   out_6512097809109486594[8] = delta_x[8] + nom_x[8];
   out_6512097809109486594[9] = delta_x[9] + nom_x[9];
   out_6512097809109486594[10] = delta_x[10] + nom_x[10];
   out_6512097809109486594[11] = delta_x[11] + nom_x[11];
   out_6512097809109486594[12] = delta_x[12] + nom_x[12];
   out_6512097809109486594[13] = delta_x[13] + nom_x[13];
   out_6512097809109486594[14] = delta_x[14] + nom_x[14];
   out_6512097809109486594[15] = delta_x[15] + nom_x[15];
   out_6512097809109486594[16] = delta_x[16] + nom_x[16];
   out_6512097809109486594[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6429931426526857200) {
   out_6429931426526857200[0] = -nom_x[0] + true_x[0];
   out_6429931426526857200[1] = -nom_x[1] + true_x[1];
   out_6429931426526857200[2] = -nom_x[2] + true_x[2];
   out_6429931426526857200[3] = -nom_x[3] + true_x[3];
   out_6429931426526857200[4] = -nom_x[4] + true_x[4];
   out_6429931426526857200[5] = -nom_x[5] + true_x[5];
   out_6429931426526857200[6] = -nom_x[6] + true_x[6];
   out_6429931426526857200[7] = -nom_x[7] + true_x[7];
   out_6429931426526857200[8] = -nom_x[8] + true_x[8];
   out_6429931426526857200[9] = -nom_x[9] + true_x[9];
   out_6429931426526857200[10] = -nom_x[10] + true_x[10];
   out_6429931426526857200[11] = -nom_x[11] + true_x[11];
   out_6429931426526857200[12] = -nom_x[12] + true_x[12];
   out_6429931426526857200[13] = -nom_x[13] + true_x[13];
   out_6429931426526857200[14] = -nom_x[14] + true_x[14];
   out_6429931426526857200[15] = -nom_x[15] + true_x[15];
   out_6429931426526857200[16] = -nom_x[16] + true_x[16];
   out_6429931426526857200[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_797770248136307860) {
   out_797770248136307860[0] = 1.0;
   out_797770248136307860[1] = 0.0;
   out_797770248136307860[2] = 0.0;
   out_797770248136307860[3] = 0.0;
   out_797770248136307860[4] = 0.0;
   out_797770248136307860[5] = 0.0;
   out_797770248136307860[6] = 0.0;
   out_797770248136307860[7] = 0.0;
   out_797770248136307860[8] = 0.0;
   out_797770248136307860[9] = 0.0;
   out_797770248136307860[10] = 0.0;
   out_797770248136307860[11] = 0.0;
   out_797770248136307860[12] = 0.0;
   out_797770248136307860[13] = 0.0;
   out_797770248136307860[14] = 0.0;
   out_797770248136307860[15] = 0.0;
   out_797770248136307860[16] = 0.0;
   out_797770248136307860[17] = 0.0;
   out_797770248136307860[18] = 0.0;
   out_797770248136307860[19] = 1.0;
   out_797770248136307860[20] = 0.0;
   out_797770248136307860[21] = 0.0;
   out_797770248136307860[22] = 0.0;
   out_797770248136307860[23] = 0.0;
   out_797770248136307860[24] = 0.0;
   out_797770248136307860[25] = 0.0;
   out_797770248136307860[26] = 0.0;
   out_797770248136307860[27] = 0.0;
   out_797770248136307860[28] = 0.0;
   out_797770248136307860[29] = 0.0;
   out_797770248136307860[30] = 0.0;
   out_797770248136307860[31] = 0.0;
   out_797770248136307860[32] = 0.0;
   out_797770248136307860[33] = 0.0;
   out_797770248136307860[34] = 0.0;
   out_797770248136307860[35] = 0.0;
   out_797770248136307860[36] = 0.0;
   out_797770248136307860[37] = 0.0;
   out_797770248136307860[38] = 1.0;
   out_797770248136307860[39] = 0.0;
   out_797770248136307860[40] = 0.0;
   out_797770248136307860[41] = 0.0;
   out_797770248136307860[42] = 0.0;
   out_797770248136307860[43] = 0.0;
   out_797770248136307860[44] = 0.0;
   out_797770248136307860[45] = 0.0;
   out_797770248136307860[46] = 0.0;
   out_797770248136307860[47] = 0.0;
   out_797770248136307860[48] = 0.0;
   out_797770248136307860[49] = 0.0;
   out_797770248136307860[50] = 0.0;
   out_797770248136307860[51] = 0.0;
   out_797770248136307860[52] = 0.0;
   out_797770248136307860[53] = 0.0;
   out_797770248136307860[54] = 0.0;
   out_797770248136307860[55] = 0.0;
   out_797770248136307860[56] = 0.0;
   out_797770248136307860[57] = 1.0;
   out_797770248136307860[58] = 0.0;
   out_797770248136307860[59] = 0.0;
   out_797770248136307860[60] = 0.0;
   out_797770248136307860[61] = 0.0;
   out_797770248136307860[62] = 0.0;
   out_797770248136307860[63] = 0.0;
   out_797770248136307860[64] = 0.0;
   out_797770248136307860[65] = 0.0;
   out_797770248136307860[66] = 0.0;
   out_797770248136307860[67] = 0.0;
   out_797770248136307860[68] = 0.0;
   out_797770248136307860[69] = 0.0;
   out_797770248136307860[70] = 0.0;
   out_797770248136307860[71] = 0.0;
   out_797770248136307860[72] = 0.0;
   out_797770248136307860[73] = 0.0;
   out_797770248136307860[74] = 0.0;
   out_797770248136307860[75] = 0.0;
   out_797770248136307860[76] = 1.0;
   out_797770248136307860[77] = 0.0;
   out_797770248136307860[78] = 0.0;
   out_797770248136307860[79] = 0.0;
   out_797770248136307860[80] = 0.0;
   out_797770248136307860[81] = 0.0;
   out_797770248136307860[82] = 0.0;
   out_797770248136307860[83] = 0.0;
   out_797770248136307860[84] = 0.0;
   out_797770248136307860[85] = 0.0;
   out_797770248136307860[86] = 0.0;
   out_797770248136307860[87] = 0.0;
   out_797770248136307860[88] = 0.0;
   out_797770248136307860[89] = 0.0;
   out_797770248136307860[90] = 0.0;
   out_797770248136307860[91] = 0.0;
   out_797770248136307860[92] = 0.0;
   out_797770248136307860[93] = 0.0;
   out_797770248136307860[94] = 0.0;
   out_797770248136307860[95] = 1.0;
   out_797770248136307860[96] = 0.0;
   out_797770248136307860[97] = 0.0;
   out_797770248136307860[98] = 0.0;
   out_797770248136307860[99] = 0.0;
   out_797770248136307860[100] = 0.0;
   out_797770248136307860[101] = 0.0;
   out_797770248136307860[102] = 0.0;
   out_797770248136307860[103] = 0.0;
   out_797770248136307860[104] = 0.0;
   out_797770248136307860[105] = 0.0;
   out_797770248136307860[106] = 0.0;
   out_797770248136307860[107] = 0.0;
   out_797770248136307860[108] = 0.0;
   out_797770248136307860[109] = 0.0;
   out_797770248136307860[110] = 0.0;
   out_797770248136307860[111] = 0.0;
   out_797770248136307860[112] = 0.0;
   out_797770248136307860[113] = 0.0;
   out_797770248136307860[114] = 1.0;
   out_797770248136307860[115] = 0.0;
   out_797770248136307860[116] = 0.0;
   out_797770248136307860[117] = 0.0;
   out_797770248136307860[118] = 0.0;
   out_797770248136307860[119] = 0.0;
   out_797770248136307860[120] = 0.0;
   out_797770248136307860[121] = 0.0;
   out_797770248136307860[122] = 0.0;
   out_797770248136307860[123] = 0.0;
   out_797770248136307860[124] = 0.0;
   out_797770248136307860[125] = 0.0;
   out_797770248136307860[126] = 0.0;
   out_797770248136307860[127] = 0.0;
   out_797770248136307860[128] = 0.0;
   out_797770248136307860[129] = 0.0;
   out_797770248136307860[130] = 0.0;
   out_797770248136307860[131] = 0.0;
   out_797770248136307860[132] = 0.0;
   out_797770248136307860[133] = 1.0;
   out_797770248136307860[134] = 0.0;
   out_797770248136307860[135] = 0.0;
   out_797770248136307860[136] = 0.0;
   out_797770248136307860[137] = 0.0;
   out_797770248136307860[138] = 0.0;
   out_797770248136307860[139] = 0.0;
   out_797770248136307860[140] = 0.0;
   out_797770248136307860[141] = 0.0;
   out_797770248136307860[142] = 0.0;
   out_797770248136307860[143] = 0.0;
   out_797770248136307860[144] = 0.0;
   out_797770248136307860[145] = 0.0;
   out_797770248136307860[146] = 0.0;
   out_797770248136307860[147] = 0.0;
   out_797770248136307860[148] = 0.0;
   out_797770248136307860[149] = 0.0;
   out_797770248136307860[150] = 0.0;
   out_797770248136307860[151] = 0.0;
   out_797770248136307860[152] = 1.0;
   out_797770248136307860[153] = 0.0;
   out_797770248136307860[154] = 0.0;
   out_797770248136307860[155] = 0.0;
   out_797770248136307860[156] = 0.0;
   out_797770248136307860[157] = 0.0;
   out_797770248136307860[158] = 0.0;
   out_797770248136307860[159] = 0.0;
   out_797770248136307860[160] = 0.0;
   out_797770248136307860[161] = 0.0;
   out_797770248136307860[162] = 0.0;
   out_797770248136307860[163] = 0.0;
   out_797770248136307860[164] = 0.0;
   out_797770248136307860[165] = 0.0;
   out_797770248136307860[166] = 0.0;
   out_797770248136307860[167] = 0.0;
   out_797770248136307860[168] = 0.0;
   out_797770248136307860[169] = 0.0;
   out_797770248136307860[170] = 0.0;
   out_797770248136307860[171] = 1.0;
   out_797770248136307860[172] = 0.0;
   out_797770248136307860[173] = 0.0;
   out_797770248136307860[174] = 0.0;
   out_797770248136307860[175] = 0.0;
   out_797770248136307860[176] = 0.0;
   out_797770248136307860[177] = 0.0;
   out_797770248136307860[178] = 0.0;
   out_797770248136307860[179] = 0.0;
   out_797770248136307860[180] = 0.0;
   out_797770248136307860[181] = 0.0;
   out_797770248136307860[182] = 0.0;
   out_797770248136307860[183] = 0.0;
   out_797770248136307860[184] = 0.0;
   out_797770248136307860[185] = 0.0;
   out_797770248136307860[186] = 0.0;
   out_797770248136307860[187] = 0.0;
   out_797770248136307860[188] = 0.0;
   out_797770248136307860[189] = 0.0;
   out_797770248136307860[190] = 1.0;
   out_797770248136307860[191] = 0.0;
   out_797770248136307860[192] = 0.0;
   out_797770248136307860[193] = 0.0;
   out_797770248136307860[194] = 0.0;
   out_797770248136307860[195] = 0.0;
   out_797770248136307860[196] = 0.0;
   out_797770248136307860[197] = 0.0;
   out_797770248136307860[198] = 0.0;
   out_797770248136307860[199] = 0.0;
   out_797770248136307860[200] = 0.0;
   out_797770248136307860[201] = 0.0;
   out_797770248136307860[202] = 0.0;
   out_797770248136307860[203] = 0.0;
   out_797770248136307860[204] = 0.0;
   out_797770248136307860[205] = 0.0;
   out_797770248136307860[206] = 0.0;
   out_797770248136307860[207] = 0.0;
   out_797770248136307860[208] = 0.0;
   out_797770248136307860[209] = 1.0;
   out_797770248136307860[210] = 0.0;
   out_797770248136307860[211] = 0.0;
   out_797770248136307860[212] = 0.0;
   out_797770248136307860[213] = 0.0;
   out_797770248136307860[214] = 0.0;
   out_797770248136307860[215] = 0.0;
   out_797770248136307860[216] = 0.0;
   out_797770248136307860[217] = 0.0;
   out_797770248136307860[218] = 0.0;
   out_797770248136307860[219] = 0.0;
   out_797770248136307860[220] = 0.0;
   out_797770248136307860[221] = 0.0;
   out_797770248136307860[222] = 0.0;
   out_797770248136307860[223] = 0.0;
   out_797770248136307860[224] = 0.0;
   out_797770248136307860[225] = 0.0;
   out_797770248136307860[226] = 0.0;
   out_797770248136307860[227] = 0.0;
   out_797770248136307860[228] = 1.0;
   out_797770248136307860[229] = 0.0;
   out_797770248136307860[230] = 0.0;
   out_797770248136307860[231] = 0.0;
   out_797770248136307860[232] = 0.0;
   out_797770248136307860[233] = 0.0;
   out_797770248136307860[234] = 0.0;
   out_797770248136307860[235] = 0.0;
   out_797770248136307860[236] = 0.0;
   out_797770248136307860[237] = 0.0;
   out_797770248136307860[238] = 0.0;
   out_797770248136307860[239] = 0.0;
   out_797770248136307860[240] = 0.0;
   out_797770248136307860[241] = 0.0;
   out_797770248136307860[242] = 0.0;
   out_797770248136307860[243] = 0.0;
   out_797770248136307860[244] = 0.0;
   out_797770248136307860[245] = 0.0;
   out_797770248136307860[246] = 0.0;
   out_797770248136307860[247] = 1.0;
   out_797770248136307860[248] = 0.0;
   out_797770248136307860[249] = 0.0;
   out_797770248136307860[250] = 0.0;
   out_797770248136307860[251] = 0.0;
   out_797770248136307860[252] = 0.0;
   out_797770248136307860[253] = 0.0;
   out_797770248136307860[254] = 0.0;
   out_797770248136307860[255] = 0.0;
   out_797770248136307860[256] = 0.0;
   out_797770248136307860[257] = 0.0;
   out_797770248136307860[258] = 0.0;
   out_797770248136307860[259] = 0.0;
   out_797770248136307860[260] = 0.0;
   out_797770248136307860[261] = 0.0;
   out_797770248136307860[262] = 0.0;
   out_797770248136307860[263] = 0.0;
   out_797770248136307860[264] = 0.0;
   out_797770248136307860[265] = 0.0;
   out_797770248136307860[266] = 1.0;
   out_797770248136307860[267] = 0.0;
   out_797770248136307860[268] = 0.0;
   out_797770248136307860[269] = 0.0;
   out_797770248136307860[270] = 0.0;
   out_797770248136307860[271] = 0.0;
   out_797770248136307860[272] = 0.0;
   out_797770248136307860[273] = 0.0;
   out_797770248136307860[274] = 0.0;
   out_797770248136307860[275] = 0.0;
   out_797770248136307860[276] = 0.0;
   out_797770248136307860[277] = 0.0;
   out_797770248136307860[278] = 0.0;
   out_797770248136307860[279] = 0.0;
   out_797770248136307860[280] = 0.0;
   out_797770248136307860[281] = 0.0;
   out_797770248136307860[282] = 0.0;
   out_797770248136307860[283] = 0.0;
   out_797770248136307860[284] = 0.0;
   out_797770248136307860[285] = 1.0;
   out_797770248136307860[286] = 0.0;
   out_797770248136307860[287] = 0.0;
   out_797770248136307860[288] = 0.0;
   out_797770248136307860[289] = 0.0;
   out_797770248136307860[290] = 0.0;
   out_797770248136307860[291] = 0.0;
   out_797770248136307860[292] = 0.0;
   out_797770248136307860[293] = 0.0;
   out_797770248136307860[294] = 0.0;
   out_797770248136307860[295] = 0.0;
   out_797770248136307860[296] = 0.0;
   out_797770248136307860[297] = 0.0;
   out_797770248136307860[298] = 0.0;
   out_797770248136307860[299] = 0.0;
   out_797770248136307860[300] = 0.0;
   out_797770248136307860[301] = 0.0;
   out_797770248136307860[302] = 0.0;
   out_797770248136307860[303] = 0.0;
   out_797770248136307860[304] = 1.0;
   out_797770248136307860[305] = 0.0;
   out_797770248136307860[306] = 0.0;
   out_797770248136307860[307] = 0.0;
   out_797770248136307860[308] = 0.0;
   out_797770248136307860[309] = 0.0;
   out_797770248136307860[310] = 0.0;
   out_797770248136307860[311] = 0.0;
   out_797770248136307860[312] = 0.0;
   out_797770248136307860[313] = 0.0;
   out_797770248136307860[314] = 0.0;
   out_797770248136307860[315] = 0.0;
   out_797770248136307860[316] = 0.0;
   out_797770248136307860[317] = 0.0;
   out_797770248136307860[318] = 0.0;
   out_797770248136307860[319] = 0.0;
   out_797770248136307860[320] = 0.0;
   out_797770248136307860[321] = 0.0;
   out_797770248136307860[322] = 0.0;
   out_797770248136307860[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_8790483116213543922) {
   out_8790483116213543922[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_8790483116213543922[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_8790483116213543922[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_8790483116213543922[3] = dt*state[12] + state[3];
   out_8790483116213543922[4] = dt*state[13] + state[4];
   out_8790483116213543922[5] = dt*state[14] + state[5];
   out_8790483116213543922[6] = state[6];
   out_8790483116213543922[7] = state[7];
   out_8790483116213543922[8] = state[8];
   out_8790483116213543922[9] = state[9];
   out_8790483116213543922[10] = state[10];
   out_8790483116213543922[11] = state[11];
   out_8790483116213543922[12] = state[12];
   out_8790483116213543922[13] = state[13];
   out_8790483116213543922[14] = state[14];
   out_8790483116213543922[15] = state[15];
   out_8790483116213543922[16] = state[16];
   out_8790483116213543922[17] = state[17];
}
void F_fun(double *state, double dt, double *out_9177730108629592028) {
   out_9177730108629592028[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9177730108629592028[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9177730108629592028[2] = 0;
   out_9177730108629592028[3] = 0;
   out_9177730108629592028[4] = 0;
   out_9177730108629592028[5] = 0;
   out_9177730108629592028[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9177730108629592028[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9177730108629592028[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_9177730108629592028[9] = 0;
   out_9177730108629592028[10] = 0;
   out_9177730108629592028[11] = 0;
   out_9177730108629592028[12] = 0;
   out_9177730108629592028[13] = 0;
   out_9177730108629592028[14] = 0;
   out_9177730108629592028[15] = 0;
   out_9177730108629592028[16] = 0;
   out_9177730108629592028[17] = 0;
   out_9177730108629592028[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9177730108629592028[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9177730108629592028[20] = 0;
   out_9177730108629592028[21] = 0;
   out_9177730108629592028[22] = 0;
   out_9177730108629592028[23] = 0;
   out_9177730108629592028[24] = 0;
   out_9177730108629592028[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9177730108629592028[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_9177730108629592028[27] = 0;
   out_9177730108629592028[28] = 0;
   out_9177730108629592028[29] = 0;
   out_9177730108629592028[30] = 0;
   out_9177730108629592028[31] = 0;
   out_9177730108629592028[32] = 0;
   out_9177730108629592028[33] = 0;
   out_9177730108629592028[34] = 0;
   out_9177730108629592028[35] = 0;
   out_9177730108629592028[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9177730108629592028[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9177730108629592028[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9177730108629592028[39] = 0;
   out_9177730108629592028[40] = 0;
   out_9177730108629592028[41] = 0;
   out_9177730108629592028[42] = 0;
   out_9177730108629592028[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9177730108629592028[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_9177730108629592028[45] = 0;
   out_9177730108629592028[46] = 0;
   out_9177730108629592028[47] = 0;
   out_9177730108629592028[48] = 0;
   out_9177730108629592028[49] = 0;
   out_9177730108629592028[50] = 0;
   out_9177730108629592028[51] = 0;
   out_9177730108629592028[52] = 0;
   out_9177730108629592028[53] = 0;
   out_9177730108629592028[54] = 0;
   out_9177730108629592028[55] = 0;
   out_9177730108629592028[56] = 0;
   out_9177730108629592028[57] = 1;
   out_9177730108629592028[58] = 0;
   out_9177730108629592028[59] = 0;
   out_9177730108629592028[60] = 0;
   out_9177730108629592028[61] = 0;
   out_9177730108629592028[62] = 0;
   out_9177730108629592028[63] = 0;
   out_9177730108629592028[64] = 0;
   out_9177730108629592028[65] = 0;
   out_9177730108629592028[66] = dt;
   out_9177730108629592028[67] = 0;
   out_9177730108629592028[68] = 0;
   out_9177730108629592028[69] = 0;
   out_9177730108629592028[70] = 0;
   out_9177730108629592028[71] = 0;
   out_9177730108629592028[72] = 0;
   out_9177730108629592028[73] = 0;
   out_9177730108629592028[74] = 0;
   out_9177730108629592028[75] = 0;
   out_9177730108629592028[76] = 1;
   out_9177730108629592028[77] = 0;
   out_9177730108629592028[78] = 0;
   out_9177730108629592028[79] = 0;
   out_9177730108629592028[80] = 0;
   out_9177730108629592028[81] = 0;
   out_9177730108629592028[82] = 0;
   out_9177730108629592028[83] = 0;
   out_9177730108629592028[84] = 0;
   out_9177730108629592028[85] = dt;
   out_9177730108629592028[86] = 0;
   out_9177730108629592028[87] = 0;
   out_9177730108629592028[88] = 0;
   out_9177730108629592028[89] = 0;
   out_9177730108629592028[90] = 0;
   out_9177730108629592028[91] = 0;
   out_9177730108629592028[92] = 0;
   out_9177730108629592028[93] = 0;
   out_9177730108629592028[94] = 0;
   out_9177730108629592028[95] = 1;
   out_9177730108629592028[96] = 0;
   out_9177730108629592028[97] = 0;
   out_9177730108629592028[98] = 0;
   out_9177730108629592028[99] = 0;
   out_9177730108629592028[100] = 0;
   out_9177730108629592028[101] = 0;
   out_9177730108629592028[102] = 0;
   out_9177730108629592028[103] = 0;
   out_9177730108629592028[104] = dt;
   out_9177730108629592028[105] = 0;
   out_9177730108629592028[106] = 0;
   out_9177730108629592028[107] = 0;
   out_9177730108629592028[108] = 0;
   out_9177730108629592028[109] = 0;
   out_9177730108629592028[110] = 0;
   out_9177730108629592028[111] = 0;
   out_9177730108629592028[112] = 0;
   out_9177730108629592028[113] = 0;
   out_9177730108629592028[114] = 1;
   out_9177730108629592028[115] = 0;
   out_9177730108629592028[116] = 0;
   out_9177730108629592028[117] = 0;
   out_9177730108629592028[118] = 0;
   out_9177730108629592028[119] = 0;
   out_9177730108629592028[120] = 0;
   out_9177730108629592028[121] = 0;
   out_9177730108629592028[122] = 0;
   out_9177730108629592028[123] = 0;
   out_9177730108629592028[124] = 0;
   out_9177730108629592028[125] = 0;
   out_9177730108629592028[126] = 0;
   out_9177730108629592028[127] = 0;
   out_9177730108629592028[128] = 0;
   out_9177730108629592028[129] = 0;
   out_9177730108629592028[130] = 0;
   out_9177730108629592028[131] = 0;
   out_9177730108629592028[132] = 0;
   out_9177730108629592028[133] = 1;
   out_9177730108629592028[134] = 0;
   out_9177730108629592028[135] = 0;
   out_9177730108629592028[136] = 0;
   out_9177730108629592028[137] = 0;
   out_9177730108629592028[138] = 0;
   out_9177730108629592028[139] = 0;
   out_9177730108629592028[140] = 0;
   out_9177730108629592028[141] = 0;
   out_9177730108629592028[142] = 0;
   out_9177730108629592028[143] = 0;
   out_9177730108629592028[144] = 0;
   out_9177730108629592028[145] = 0;
   out_9177730108629592028[146] = 0;
   out_9177730108629592028[147] = 0;
   out_9177730108629592028[148] = 0;
   out_9177730108629592028[149] = 0;
   out_9177730108629592028[150] = 0;
   out_9177730108629592028[151] = 0;
   out_9177730108629592028[152] = 1;
   out_9177730108629592028[153] = 0;
   out_9177730108629592028[154] = 0;
   out_9177730108629592028[155] = 0;
   out_9177730108629592028[156] = 0;
   out_9177730108629592028[157] = 0;
   out_9177730108629592028[158] = 0;
   out_9177730108629592028[159] = 0;
   out_9177730108629592028[160] = 0;
   out_9177730108629592028[161] = 0;
   out_9177730108629592028[162] = 0;
   out_9177730108629592028[163] = 0;
   out_9177730108629592028[164] = 0;
   out_9177730108629592028[165] = 0;
   out_9177730108629592028[166] = 0;
   out_9177730108629592028[167] = 0;
   out_9177730108629592028[168] = 0;
   out_9177730108629592028[169] = 0;
   out_9177730108629592028[170] = 0;
   out_9177730108629592028[171] = 1;
   out_9177730108629592028[172] = 0;
   out_9177730108629592028[173] = 0;
   out_9177730108629592028[174] = 0;
   out_9177730108629592028[175] = 0;
   out_9177730108629592028[176] = 0;
   out_9177730108629592028[177] = 0;
   out_9177730108629592028[178] = 0;
   out_9177730108629592028[179] = 0;
   out_9177730108629592028[180] = 0;
   out_9177730108629592028[181] = 0;
   out_9177730108629592028[182] = 0;
   out_9177730108629592028[183] = 0;
   out_9177730108629592028[184] = 0;
   out_9177730108629592028[185] = 0;
   out_9177730108629592028[186] = 0;
   out_9177730108629592028[187] = 0;
   out_9177730108629592028[188] = 0;
   out_9177730108629592028[189] = 0;
   out_9177730108629592028[190] = 1;
   out_9177730108629592028[191] = 0;
   out_9177730108629592028[192] = 0;
   out_9177730108629592028[193] = 0;
   out_9177730108629592028[194] = 0;
   out_9177730108629592028[195] = 0;
   out_9177730108629592028[196] = 0;
   out_9177730108629592028[197] = 0;
   out_9177730108629592028[198] = 0;
   out_9177730108629592028[199] = 0;
   out_9177730108629592028[200] = 0;
   out_9177730108629592028[201] = 0;
   out_9177730108629592028[202] = 0;
   out_9177730108629592028[203] = 0;
   out_9177730108629592028[204] = 0;
   out_9177730108629592028[205] = 0;
   out_9177730108629592028[206] = 0;
   out_9177730108629592028[207] = 0;
   out_9177730108629592028[208] = 0;
   out_9177730108629592028[209] = 1;
   out_9177730108629592028[210] = 0;
   out_9177730108629592028[211] = 0;
   out_9177730108629592028[212] = 0;
   out_9177730108629592028[213] = 0;
   out_9177730108629592028[214] = 0;
   out_9177730108629592028[215] = 0;
   out_9177730108629592028[216] = 0;
   out_9177730108629592028[217] = 0;
   out_9177730108629592028[218] = 0;
   out_9177730108629592028[219] = 0;
   out_9177730108629592028[220] = 0;
   out_9177730108629592028[221] = 0;
   out_9177730108629592028[222] = 0;
   out_9177730108629592028[223] = 0;
   out_9177730108629592028[224] = 0;
   out_9177730108629592028[225] = 0;
   out_9177730108629592028[226] = 0;
   out_9177730108629592028[227] = 0;
   out_9177730108629592028[228] = 1;
   out_9177730108629592028[229] = 0;
   out_9177730108629592028[230] = 0;
   out_9177730108629592028[231] = 0;
   out_9177730108629592028[232] = 0;
   out_9177730108629592028[233] = 0;
   out_9177730108629592028[234] = 0;
   out_9177730108629592028[235] = 0;
   out_9177730108629592028[236] = 0;
   out_9177730108629592028[237] = 0;
   out_9177730108629592028[238] = 0;
   out_9177730108629592028[239] = 0;
   out_9177730108629592028[240] = 0;
   out_9177730108629592028[241] = 0;
   out_9177730108629592028[242] = 0;
   out_9177730108629592028[243] = 0;
   out_9177730108629592028[244] = 0;
   out_9177730108629592028[245] = 0;
   out_9177730108629592028[246] = 0;
   out_9177730108629592028[247] = 1;
   out_9177730108629592028[248] = 0;
   out_9177730108629592028[249] = 0;
   out_9177730108629592028[250] = 0;
   out_9177730108629592028[251] = 0;
   out_9177730108629592028[252] = 0;
   out_9177730108629592028[253] = 0;
   out_9177730108629592028[254] = 0;
   out_9177730108629592028[255] = 0;
   out_9177730108629592028[256] = 0;
   out_9177730108629592028[257] = 0;
   out_9177730108629592028[258] = 0;
   out_9177730108629592028[259] = 0;
   out_9177730108629592028[260] = 0;
   out_9177730108629592028[261] = 0;
   out_9177730108629592028[262] = 0;
   out_9177730108629592028[263] = 0;
   out_9177730108629592028[264] = 0;
   out_9177730108629592028[265] = 0;
   out_9177730108629592028[266] = 1;
   out_9177730108629592028[267] = 0;
   out_9177730108629592028[268] = 0;
   out_9177730108629592028[269] = 0;
   out_9177730108629592028[270] = 0;
   out_9177730108629592028[271] = 0;
   out_9177730108629592028[272] = 0;
   out_9177730108629592028[273] = 0;
   out_9177730108629592028[274] = 0;
   out_9177730108629592028[275] = 0;
   out_9177730108629592028[276] = 0;
   out_9177730108629592028[277] = 0;
   out_9177730108629592028[278] = 0;
   out_9177730108629592028[279] = 0;
   out_9177730108629592028[280] = 0;
   out_9177730108629592028[281] = 0;
   out_9177730108629592028[282] = 0;
   out_9177730108629592028[283] = 0;
   out_9177730108629592028[284] = 0;
   out_9177730108629592028[285] = 1;
   out_9177730108629592028[286] = 0;
   out_9177730108629592028[287] = 0;
   out_9177730108629592028[288] = 0;
   out_9177730108629592028[289] = 0;
   out_9177730108629592028[290] = 0;
   out_9177730108629592028[291] = 0;
   out_9177730108629592028[292] = 0;
   out_9177730108629592028[293] = 0;
   out_9177730108629592028[294] = 0;
   out_9177730108629592028[295] = 0;
   out_9177730108629592028[296] = 0;
   out_9177730108629592028[297] = 0;
   out_9177730108629592028[298] = 0;
   out_9177730108629592028[299] = 0;
   out_9177730108629592028[300] = 0;
   out_9177730108629592028[301] = 0;
   out_9177730108629592028[302] = 0;
   out_9177730108629592028[303] = 0;
   out_9177730108629592028[304] = 1;
   out_9177730108629592028[305] = 0;
   out_9177730108629592028[306] = 0;
   out_9177730108629592028[307] = 0;
   out_9177730108629592028[308] = 0;
   out_9177730108629592028[309] = 0;
   out_9177730108629592028[310] = 0;
   out_9177730108629592028[311] = 0;
   out_9177730108629592028[312] = 0;
   out_9177730108629592028[313] = 0;
   out_9177730108629592028[314] = 0;
   out_9177730108629592028[315] = 0;
   out_9177730108629592028[316] = 0;
   out_9177730108629592028[317] = 0;
   out_9177730108629592028[318] = 0;
   out_9177730108629592028[319] = 0;
   out_9177730108629592028[320] = 0;
   out_9177730108629592028[321] = 0;
   out_9177730108629592028[322] = 0;
   out_9177730108629592028[323] = 1;
}
void h_4(double *state, double *unused, double *out_7984495719087756063) {
   out_7984495719087756063[0] = state[6] + state[9];
   out_7984495719087756063[1] = state[7] + state[10];
   out_7984495719087756063[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6645852054888266581) {
   out_6645852054888266581[0] = 0;
   out_6645852054888266581[1] = 0;
   out_6645852054888266581[2] = 0;
   out_6645852054888266581[3] = 0;
   out_6645852054888266581[4] = 0;
   out_6645852054888266581[5] = 0;
   out_6645852054888266581[6] = 1;
   out_6645852054888266581[7] = 0;
   out_6645852054888266581[8] = 0;
   out_6645852054888266581[9] = 1;
   out_6645852054888266581[10] = 0;
   out_6645852054888266581[11] = 0;
   out_6645852054888266581[12] = 0;
   out_6645852054888266581[13] = 0;
   out_6645852054888266581[14] = 0;
   out_6645852054888266581[15] = 0;
   out_6645852054888266581[16] = 0;
   out_6645852054888266581[17] = 0;
   out_6645852054888266581[18] = 0;
   out_6645852054888266581[19] = 0;
   out_6645852054888266581[20] = 0;
   out_6645852054888266581[21] = 0;
   out_6645852054888266581[22] = 0;
   out_6645852054888266581[23] = 0;
   out_6645852054888266581[24] = 0;
   out_6645852054888266581[25] = 1;
   out_6645852054888266581[26] = 0;
   out_6645852054888266581[27] = 0;
   out_6645852054888266581[28] = 1;
   out_6645852054888266581[29] = 0;
   out_6645852054888266581[30] = 0;
   out_6645852054888266581[31] = 0;
   out_6645852054888266581[32] = 0;
   out_6645852054888266581[33] = 0;
   out_6645852054888266581[34] = 0;
   out_6645852054888266581[35] = 0;
   out_6645852054888266581[36] = 0;
   out_6645852054888266581[37] = 0;
   out_6645852054888266581[38] = 0;
   out_6645852054888266581[39] = 0;
   out_6645852054888266581[40] = 0;
   out_6645852054888266581[41] = 0;
   out_6645852054888266581[42] = 0;
   out_6645852054888266581[43] = 0;
   out_6645852054888266581[44] = 1;
   out_6645852054888266581[45] = 0;
   out_6645852054888266581[46] = 0;
   out_6645852054888266581[47] = 1;
   out_6645852054888266581[48] = 0;
   out_6645852054888266581[49] = 0;
   out_6645852054888266581[50] = 0;
   out_6645852054888266581[51] = 0;
   out_6645852054888266581[52] = 0;
   out_6645852054888266581[53] = 0;
}
void h_10(double *state, double *unused, double *out_7217217585169764441) {
   out_7217217585169764441[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_7217217585169764441[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_7217217585169764441[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_2486700685078595702) {
   out_2486700685078595702[0] = 0;
   out_2486700685078595702[1] = 9.8100000000000005*cos(state[1]);
   out_2486700685078595702[2] = 0;
   out_2486700685078595702[3] = 0;
   out_2486700685078595702[4] = -state[8];
   out_2486700685078595702[5] = state[7];
   out_2486700685078595702[6] = 0;
   out_2486700685078595702[7] = state[5];
   out_2486700685078595702[8] = -state[4];
   out_2486700685078595702[9] = 0;
   out_2486700685078595702[10] = 0;
   out_2486700685078595702[11] = 0;
   out_2486700685078595702[12] = 1;
   out_2486700685078595702[13] = 0;
   out_2486700685078595702[14] = 0;
   out_2486700685078595702[15] = 1;
   out_2486700685078595702[16] = 0;
   out_2486700685078595702[17] = 0;
   out_2486700685078595702[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_2486700685078595702[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_2486700685078595702[20] = 0;
   out_2486700685078595702[21] = state[8];
   out_2486700685078595702[22] = 0;
   out_2486700685078595702[23] = -state[6];
   out_2486700685078595702[24] = -state[5];
   out_2486700685078595702[25] = 0;
   out_2486700685078595702[26] = state[3];
   out_2486700685078595702[27] = 0;
   out_2486700685078595702[28] = 0;
   out_2486700685078595702[29] = 0;
   out_2486700685078595702[30] = 0;
   out_2486700685078595702[31] = 1;
   out_2486700685078595702[32] = 0;
   out_2486700685078595702[33] = 0;
   out_2486700685078595702[34] = 1;
   out_2486700685078595702[35] = 0;
   out_2486700685078595702[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_2486700685078595702[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_2486700685078595702[38] = 0;
   out_2486700685078595702[39] = -state[7];
   out_2486700685078595702[40] = state[6];
   out_2486700685078595702[41] = 0;
   out_2486700685078595702[42] = state[4];
   out_2486700685078595702[43] = -state[3];
   out_2486700685078595702[44] = 0;
   out_2486700685078595702[45] = 0;
   out_2486700685078595702[46] = 0;
   out_2486700685078595702[47] = 0;
   out_2486700685078595702[48] = 0;
   out_2486700685078595702[49] = 0;
   out_2486700685078595702[50] = 1;
   out_2486700685078595702[51] = 0;
   out_2486700685078595702[52] = 0;
   out_2486700685078595702[53] = 1;
}
void h_13(double *state, double *unused, double *out_4227448484818960513) {
   out_4227448484818960513[0] = state[3];
   out_4227448484818960513[1] = state[4];
   out_4227448484818960513[2] = state[5];
}
void H_13(double *state, double *unused, double *out_3433578229555933780) {
   out_3433578229555933780[0] = 0;
   out_3433578229555933780[1] = 0;
   out_3433578229555933780[2] = 0;
   out_3433578229555933780[3] = 1;
   out_3433578229555933780[4] = 0;
   out_3433578229555933780[5] = 0;
   out_3433578229555933780[6] = 0;
   out_3433578229555933780[7] = 0;
   out_3433578229555933780[8] = 0;
   out_3433578229555933780[9] = 0;
   out_3433578229555933780[10] = 0;
   out_3433578229555933780[11] = 0;
   out_3433578229555933780[12] = 0;
   out_3433578229555933780[13] = 0;
   out_3433578229555933780[14] = 0;
   out_3433578229555933780[15] = 0;
   out_3433578229555933780[16] = 0;
   out_3433578229555933780[17] = 0;
   out_3433578229555933780[18] = 0;
   out_3433578229555933780[19] = 0;
   out_3433578229555933780[20] = 0;
   out_3433578229555933780[21] = 0;
   out_3433578229555933780[22] = 1;
   out_3433578229555933780[23] = 0;
   out_3433578229555933780[24] = 0;
   out_3433578229555933780[25] = 0;
   out_3433578229555933780[26] = 0;
   out_3433578229555933780[27] = 0;
   out_3433578229555933780[28] = 0;
   out_3433578229555933780[29] = 0;
   out_3433578229555933780[30] = 0;
   out_3433578229555933780[31] = 0;
   out_3433578229555933780[32] = 0;
   out_3433578229555933780[33] = 0;
   out_3433578229555933780[34] = 0;
   out_3433578229555933780[35] = 0;
   out_3433578229555933780[36] = 0;
   out_3433578229555933780[37] = 0;
   out_3433578229555933780[38] = 0;
   out_3433578229555933780[39] = 0;
   out_3433578229555933780[40] = 0;
   out_3433578229555933780[41] = 1;
   out_3433578229555933780[42] = 0;
   out_3433578229555933780[43] = 0;
   out_3433578229555933780[44] = 0;
   out_3433578229555933780[45] = 0;
   out_3433578229555933780[46] = 0;
   out_3433578229555933780[47] = 0;
   out_3433578229555933780[48] = 0;
   out_3433578229555933780[49] = 0;
   out_3433578229555933780[50] = 0;
   out_3433578229555933780[51] = 0;
   out_3433578229555933780[52] = 0;
   out_3433578229555933780[53] = 0;
}
void h_14(double *state, double *unused, double *out_4160763402509463502) {
   out_4160763402509463502[0] = state[6];
   out_4160763402509463502[1] = state[7];
   out_4160763402509463502[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2682611198548782052) {
   out_2682611198548782052[0] = 0;
   out_2682611198548782052[1] = 0;
   out_2682611198548782052[2] = 0;
   out_2682611198548782052[3] = 0;
   out_2682611198548782052[4] = 0;
   out_2682611198548782052[5] = 0;
   out_2682611198548782052[6] = 1;
   out_2682611198548782052[7] = 0;
   out_2682611198548782052[8] = 0;
   out_2682611198548782052[9] = 0;
   out_2682611198548782052[10] = 0;
   out_2682611198548782052[11] = 0;
   out_2682611198548782052[12] = 0;
   out_2682611198548782052[13] = 0;
   out_2682611198548782052[14] = 0;
   out_2682611198548782052[15] = 0;
   out_2682611198548782052[16] = 0;
   out_2682611198548782052[17] = 0;
   out_2682611198548782052[18] = 0;
   out_2682611198548782052[19] = 0;
   out_2682611198548782052[20] = 0;
   out_2682611198548782052[21] = 0;
   out_2682611198548782052[22] = 0;
   out_2682611198548782052[23] = 0;
   out_2682611198548782052[24] = 0;
   out_2682611198548782052[25] = 1;
   out_2682611198548782052[26] = 0;
   out_2682611198548782052[27] = 0;
   out_2682611198548782052[28] = 0;
   out_2682611198548782052[29] = 0;
   out_2682611198548782052[30] = 0;
   out_2682611198548782052[31] = 0;
   out_2682611198548782052[32] = 0;
   out_2682611198548782052[33] = 0;
   out_2682611198548782052[34] = 0;
   out_2682611198548782052[35] = 0;
   out_2682611198548782052[36] = 0;
   out_2682611198548782052[37] = 0;
   out_2682611198548782052[38] = 0;
   out_2682611198548782052[39] = 0;
   out_2682611198548782052[40] = 0;
   out_2682611198548782052[41] = 0;
   out_2682611198548782052[42] = 0;
   out_2682611198548782052[43] = 0;
   out_2682611198548782052[44] = 1;
   out_2682611198548782052[45] = 0;
   out_2682611198548782052[46] = 0;
   out_2682611198548782052[47] = 0;
   out_2682611198548782052[48] = 0;
   out_2682611198548782052[49] = 0;
   out_2682611198548782052[50] = 0;
   out_2682611198548782052[51] = 0;
   out_2682611198548782052[52] = 0;
   out_2682611198548782052[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_6512097809109486594) {
  err_fun(nom_x, delta_x, out_6512097809109486594);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6429931426526857200) {
  inv_err_fun(nom_x, true_x, out_6429931426526857200);
}
void pose_H_mod_fun(double *state, double *out_797770248136307860) {
  H_mod_fun(state, out_797770248136307860);
}
void pose_f_fun(double *state, double dt, double *out_8790483116213543922) {
  f_fun(state,  dt, out_8790483116213543922);
}
void pose_F_fun(double *state, double dt, double *out_9177730108629592028) {
  F_fun(state,  dt, out_9177730108629592028);
}
void pose_h_4(double *state, double *unused, double *out_7984495719087756063) {
  h_4(state, unused, out_7984495719087756063);
}
void pose_H_4(double *state, double *unused, double *out_6645852054888266581) {
  H_4(state, unused, out_6645852054888266581);
}
void pose_h_10(double *state, double *unused, double *out_7217217585169764441) {
  h_10(state, unused, out_7217217585169764441);
}
void pose_H_10(double *state, double *unused, double *out_2486700685078595702) {
  H_10(state, unused, out_2486700685078595702);
}
void pose_h_13(double *state, double *unused, double *out_4227448484818960513) {
  h_13(state, unused, out_4227448484818960513);
}
void pose_H_13(double *state, double *unused, double *out_3433578229555933780) {
  H_13(state, unused, out_3433578229555933780);
}
void pose_h_14(double *state, double *unused, double *out_4160763402509463502) {
  h_14(state, unused, out_4160763402509463502);
}
void pose_H_14(double *state, double *unused, double *out_2682611198548782052) {
  H_14(state, unused, out_2682611198548782052);
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
