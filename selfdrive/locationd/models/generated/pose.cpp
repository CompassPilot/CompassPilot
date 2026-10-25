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
void err_fun(double *nom_x, double *delta_x, double *out_908254512132799916) {
   out_908254512132799916[0] = delta_x[0] + nom_x[0];
   out_908254512132799916[1] = delta_x[1] + nom_x[1];
   out_908254512132799916[2] = delta_x[2] + nom_x[2];
   out_908254512132799916[3] = delta_x[3] + nom_x[3];
   out_908254512132799916[4] = delta_x[4] + nom_x[4];
   out_908254512132799916[5] = delta_x[5] + nom_x[5];
   out_908254512132799916[6] = delta_x[6] + nom_x[6];
   out_908254512132799916[7] = delta_x[7] + nom_x[7];
   out_908254512132799916[8] = delta_x[8] + nom_x[8];
   out_908254512132799916[9] = delta_x[9] + nom_x[9];
   out_908254512132799916[10] = delta_x[10] + nom_x[10];
   out_908254512132799916[11] = delta_x[11] + nom_x[11];
   out_908254512132799916[12] = delta_x[12] + nom_x[12];
   out_908254512132799916[13] = delta_x[13] + nom_x[13];
   out_908254512132799916[14] = delta_x[14] + nom_x[14];
   out_908254512132799916[15] = delta_x[15] + nom_x[15];
   out_908254512132799916[16] = delta_x[16] + nom_x[16];
   out_908254512132799916[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1478078535588975513) {
   out_1478078535588975513[0] = -nom_x[0] + true_x[0];
   out_1478078535588975513[1] = -nom_x[1] + true_x[1];
   out_1478078535588975513[2] = -nom_x[2] + true_x[2];
   out_1478078535588975513[3] = -nom_x[3] + true_x[3];
   out_1478078535588975513[4] = -nom_x[4] + true_x[4];
   out_1478078535588975513[5] = -nom_x[5] + true_x[5];
   out_1478078535588975513[6] = -nom_x[6] + true_x[6];
   out_1478078535588975513[7] = -nom_x[7] + true_x[7];
   out_1478078535588975513[8] = -nom_x[8] + true_x[8];
   out_1478078535588975513[9] = -nom_x[9] + true_x[9];
   out_1478078535588975513[10] = -nom_x[10] + true_x[10];
   out_1478078535588975513[11] = -nom_x[11] + true_x[11];
   out_1478078535588975513[12] = -nom_x[12] + true_x[12];
   out_1478078535588975513[13] = -nom_x[13] + true_x[13];
   out_1478078535588975513[14] = -nom_x[14] + true_x[14];
   out_1478078535588975513[15] = -nom_x[15] + true_x[15];
   out_1478078535588975513[16] = -nom_x[16] + true_x[16];
   out_1478078535588975513[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_3249349051420756862) {
   out_3249349051420756862[0] = 1.0;
   out_3249349051420756862[1] = 0.0;
   out_3249349051420756862[2] = 0.0;
   out_3249349051420756862[3] = 0.0;
   out_3249349051420756862[4] = 0.0;
   out_3249349051420756862[5] = 0.0;
   out_3249349051420756862[6] = 0.0;
   out_3249349051420756862[7] = 0.0;
   out_3249349051420756862[8] = 0.0;
   out_3249349051420756862[9] = 0.0;
   out_3249349051420756862[10] = 0.0;
   out_3249349051420756862[11] = 0.0;
   out_3249349051420756862[12] = 0.0;
   out_3249349051420756862[13] = 0.0;
   out_3249349051420756862[14] = 0.0;
   out_3249349051420756862[15] = 0.0;
   out_3249349051420756862[16] = 0.0;
   out_3249349051420756862[17] = 0.0;
   out_3249349051420756862[18] = 0.0;
   out_3249349051420756862[19] = 1.0;
   out_3249349051420756862[20] = 0.0;
   out_3249349051420756862[21] = 0.0;
   out_3249349051420756862[22] = 0.0;
   out_3249349051420756862[23] = 0.0;
   out_3249349051420756862[24] = 0.0;
   out_3249349051420756862[25] = 0.0;
   out_3249349051420756862[26] = 0.0;
   out_3249349051420756862[27] = 0.0;
   out_3249349051420756862[28] = 0.0;
   out_3249349051420756862[29] = 0.0;
   out_3249349051420756862[30] = 0.0;
   out_3249349051420756862[31] = 0.0;
   out_3249349051420756862[32] = 0.0;
   out_3249349051420756862[33] = 0.0;
   out_3249349051420756862[34] = 0.0;
   out_3249349051420756862[35] = 0.0;
   out_3249349051420756862[36] = 0.0;
   out_3249349051420756862[37] = 0.0;
   out_3249349051420756862[38] = 1.0;
   out_3249349051420756862[39] = 0.0;
   out_3249349051420756862[40] = 0.0;
   out_3249349051420756862[41] = 0.0;
   out_3249349051420756862[42] = 0.0;
   out_3249349051420756862[43] = 0.0;
   out_3249349051420756862[44] = 0.0;
   out_3249349051420756862[45] = 0.0;
   out_3249349051420756862[46] = 0.0;
   out_3249349051420756862[47] = 0.0;
   out_3249349051420756862[48] = 0.0;
   out_3249349051420756862[49] = 0.0;
   out_3249349051420756862[50] = 0.0;
   out_3249349051420756862[51] = 0.0;
   out_3249349051420756862[52] = 0.0;
   out_3249349051420756862[53] = 0.0;
   out_3249349051420756862[54] = 0.0;
   out_3249349051420756862[55] = 0.0;
   out_3249349051420756862[56] = 0.0;
   out_3249349051420756862[57] = 1.0;
   out_3249349051420756862[58] = 0.0;
   out_3249349051420756862[59] = 0.0;
   out_3249349051420756862[60] = 0.0;
   out_3249349051420756862[61] = 0.0;
   out_3249349051420756862[62] = 0.0;
   out_3249349051420756862[63] = 0.0;
   out_3249349051420756862[64] = 0.0;
   out_3249349051420756862[65] = 0.0;
   out_3249349051420756862[66] = 0.0;
   out_3249349051420756862[67] = 0.0;
   out_3249349051420756862[68] = 0.0;
   out_3249349051420756862[69] = 0.0;
   out_3249349051420756862[70] = 0.0;
   out_3249349051420756862[71] = 0.0;
   out_3249349051420756862[72] = 0.0;
   out_3249349051420756862[73] = 0.0;
   out_3249349051420756862[74] = 0.0;
   out_3249349051420756862[75] = 0.0;
   out_3249349051420756862[76] = 1.0;
   out_3249349051420756862[77] = 0.0;
   out_3249349051420756862[78] = 0.0;
   out_3249349051420756862[79] = 0.0;
   out_3249349051420756862[80] = 0.0;
   out_3249349051420756862[81] = 0.0;
   out_3249349051420756862[82] = 0.0;
   out_3249349051420756862[83] = 0.0;
   out_3249349051420756862[84] = 0.0;
   out_3249349051420756862[85] = 0.0;
   out_3249349051420756862[86] = 0.0;
   out_3249349051420756862[87] = 0.0;
   out_3249349051420756862[88] = 0.0;
   out_3249349051420756862[89] = 0.0;
   out_3249349051420756862[90] = 0.0;
   out_3249349051420756862[91] = 0.0;
   out_3249349051420756862[92] = 0.0;
   out_3249349051420756862[93] = 0.0;
   out_3249349051420756862[94] = 0.0;
   out_3249349051420756862[95] = 1.0;
   out_3249349051420756862[96] = 0.0;
   out_3249349051420756862[97] = 0.0;
   out_3249349051420756862[98] = 0.0;
   out_3249349051420756862[99] = 0.0;
   out_3249349051420756862[100] = 0.0;
   out_3249349051420756862[101] = 0.0;
   out_3249349051420756862[102] = 0.0;
   out_3249349051420756862[103] = 0.0;
   out_3249349051420756862[104] = 0.0;
   out_3249349051420756862[105] = 0.0;
   out_3249349051420756862[106] = 0.0;
   out_3249349051420756862[107] = 0.0;
   out_3249349051420756862[108] = 0.0;
   out_3249349051420756862[109] = 0.0;
   out_3249349051420756862[110] = 0.0;
   out_3249349051420756862[111] = 0.0;
   out_3249349051420756862[112] = 0.0;
   out_3249349051420756862[113] = 0.0;
   out_3249349051420756862[114] = 1.0;
   out_3249349051420756862[115] = 0.0;
   out_3249349051420756862[116] = 0.0;
   out_3249349051420756862[117] = 0.0;
   out_3249349051420756862[118] = 0.0;
   out_3249349051420756862[119] = 0.0;
   out_3249349051420756862[120] = 0.0;
   out_3249349051420756862[121] = 0.0;
   out_3249349051420756862[122] = 0.0;
   out_3249349051420756862[123] = 0.0;
   out_3249349051420756862[124] = 0.0;
   out_3249349051420756862[125] = 0.0;
   out_3249349051420756862[126] = 0.0;
   out_3249349051420756862[127] = 0.0;
   out_3249349051420756862[128] = 0.0;
   out_3249349051420756862[129] = 0.0;
   out_3249349051420756862[130] = 0.0;
   out_3249349051420756862[131] = 0.0;
   out_3249349051420756862[132] = 0.0;
   out_3249349051420756862[133] = 1.0;
   out_3249349051420756862[134] = 0.0;
   out_3249349051420756862[135] = 0.0;
   out_3249349051420756862[136] = 0.0;
   out_3249349051420756862[137] = 0.0;
   out_3249349051420756862[138] = 0.0;
   out_3249349051420756862[139] = 0.0;
   out_3249349051420756862[140] = 0.0;
   out_3249349051420756862[141] = 0.0;
   out_3249349051420756862[142] = 0.0;
   out_3249349051420756862[143] = 0.0;
   out_3249349051420756862[144] = 0.0;
   out_3249349051420756862[145] = 0.0;
   out_3249349051420756862[146] = 0.0;
   out_3249349051420756862[147] = 0.0;
   out_3249349051420756862[148] = 0.0;
   out_3249349051420756862[149] = 0.0;
   out_3249349051420756862[150] = 0.0;
   out_3249349051420756862[151] = 0.0;
   out_3249349051420756862[152] = 1.0;
   out_3249349051420756862[153] = 0.0;
   out_3249349051420756862[154] = 0.0;
   out_3249349051420756862[155] = 0.0;
   out_3249349051420756862[156] = 0.0;
   out_3249349051420756862[157] = 0.0;
   out_3249349051420756862[158] = 0.0;
   out_3249349051420756862[159] = 0.0;
   out_3249349051420756862[160] = 0.0;
   out_3249349051420756862[161] = 0.0;
   out_3249349051420756862[162] = 0.0;
   out_3249349051420756862[163] = 0.0;
   out_3249349051420756862[164] = 0.0;
   out_3249349051420756862[165] = 0.0;
   out_3249349051420756862[166] = 0.0;
   out_3249349051420756862[167] = 0.0;
   out_3249349051420756862[168] = 0.0;
   out_3249349051420756862[169] = 0.0;
   out_3249349051420756862[170] = 0.0;
   out_3249349051420756862[171] = 1.0;
   out_3249349051420756862[172] = 0.0;
   out_3249349051420756862[173] = 0.0;
   out_3249349051420756862[174] = 0.0;
   out_3249349051420756862[175] = 0.0;
   out_3249349051420756862[176] = 0.0;
   out_3249349051420756862[177] = 0.0;
   out_3249349051420756862[178] = 0.0;
   out_3249349051420756862[179] = 0.0;
   out_3249349051420756862[180] = 0.0;
   out_3249349051420756862[181] = 0.0;
   out_3249349051420756862[182] = 0.0;
   out_3249349051420756862[183] = 0.0;
   out_3249349051420756862[184] = 0.0;
   out_3249349051420756862[185] = 0.0;
   out_3249349051420756862[186] = 0.0;
   out_3249349051420756862[187] = 0.0;
   out_3249349051420756862[188] = 0.0;
   out_3249349051420756862[189] = 0.0;
   out_3249349051420756862[190] = 1.0;
   out_3249349051420756862[191] = 0.0;
   out_3249349051420756862[192] = 0.0;
   out_3249349051420756862[193] = 0.0;
   out_3249349051420756862[194] = 0.0;
   out_3249349051420756862[195] = 0.0;
   out_3249349051420756862[196] = 0.0;
   out_3249349051420756862[197] = 0.0;
   out_3249349051420756862[198] = 0.0;
   out_3249349051420756862[199] = 0.0;
   out_3249349051420756862[200] = 0.0;
   out_3249349051420756862[201] = 0.0;
   out_3249349051420756862[202] = 0.0;
   out_3249349051420756862[203] = 0.0;
   out_3249349051420756862[204] = 0.0;
   out_3249349051420756862[205] = 0.0;
   out_3249349051420756862[206] = 0.0;
   out_3249349051420756862[207] = 0.0;
   out_3249349051420756862[208] = 0.0;
   out_3249349051420756862[209] = 1.0;
   out_3249349051420756862[210] = 0.0;
   out_3249349051420756862[211] = 0.0;
   out_3249349051420756862[212] = 0.0;
   out_3249349051420756862[213] = 0.0;
   out_3249349051420756862[214] = 0.0;
   out_3249349051420756862[215] = 0.0;
   out_3249349051420756862[216] = 0.0;
   out_3249349051420756862[217] = 0.0;
   out_3249349051420756862[218] = 0.0;
   out_3249349051420756862[219] = 0.0;
   out_3249349051420756862[220] = 0.0;
   out_3249349051420756862[221] = 0.0;
   out_3249349051420756862[222] = 0.0;
   out_3249349051420756862[223] = 0.0;
   out_3249349051420756862[224] = 0.0;
   out_3249349051420756862[225] = 0.0;
   out_3249349051420756862[226] = 0.0;
   out_3249349051420756862[227] = 0.0;
   out_3249349051420756862[228] = 1.0;
   out_3249349051420756862[229] = 0.0;
   out_3249349051420756862[230] = 0.0;
   out_3249349051420756862[231] = 0.0;
   out_3249349051420756862[232] = 0.0;
   out_3249349051420756862[233] = 0.0;
   out_3249349051420756862[234] = 0.0;
   out_3249349051420756862[235] = 0.0;
   out_3249349051420756862[236] = 0.0;
   out_3249349051420756862[237] = 0.0;
   out_3249349051420756862[238] = 0.0;
   out_3249349051420756862[239] = 0.0;
   out_3249349051420756862[240] = 0.0;
   out_3249349051420756862[241] = 0.0;
   out_3249349051420756862[242] = 0.0;
   out_3249349051420756862[243] = 0.0;
   out_3249349051420756862[244] = 0.0;
   out_3249349051420756862[245] = 0.0;
   out_3249349051420756862[246] = 0.0;
   out_3249349051420756862[247] = 1.0;
   out_3249349051420756862[248] = 0.0;
   out_3249349051420756862[249] = 0.0;
   out_3249349051420756862[250] = 0.0;
   out_3249349051420756862[251] = 0.0;
   out_3249349051420756862[252] = 0.0;
   out_3249349051420756862[253] = 0.0;
   out_3249349051420756862[254] = 0.0;
   out_3249349051420756862[255] = 0.0;
   out_3249349051420756862[256] = 0.0;
   out_3249349051420756862[257] = 0.0;
   out_3249349051420756862[258] = 0.0;
   out_3249349051420756862[259] = 0.0;
   out_3249349051420756862[260] = 0.0;
   out_3249349051420756862[261] = 0.0;
   out_3249349051420756862[262] = 0.0;
   out_3249349051420756862[263] = 0.0;
   out_3249349051420756862[264] = 0.0;
   out_3249349051420756862[265] = 0.0;
   out_3249349051420756862[266] = 1.0;
   out_3249349051420756862[267] = 0.0;
   out_3249349051420756862[268] = 0.0;
   out_3249349051420756862[269] = 0.0;
   out_3249349051420756862[270] = 0.0;
   out_3249349051420756862[271] = 0.0;
   out_3249349051420756862[272] = 0.0;
   out_3249349051420756862[273] = 0.0;
   out_3249349051420756862[274] = 0.0;
   out_3249349051420756862[275] = 0.0;
   out_3249349051420756862[276] = 0.0;
   out_3249349051420756862[277] = 0.0;
   out_3249349051420756862[278] = 0.0;
   out_3249349051420756862[279] = 0.0;
   out_3249349051420756862[280] = 0.0;
   out_3249349051420756862[281] = 0.0;
   out_3249349051420756862[282] = 0.0;
   out_3249349051420756862[283] = 0.0;
   out_3249349051420756862[284] = 0.0;
   out_3249349051420756862[285] = 1.0;
   out_3249349051420756862[286] = 0.0;
   out_3249349051420756862[287] = 0.0;
   out_3249349051420756862[288] = 0.0;
   out_3249349051420756862[289] = 0.0;
   out_3249349051420756862[290] = 0.0;
   out_3249349051420756862[291] = 0.0;
   out_3249349051420756862[292] = 0.0;
   out_3249349051420756862[293] = 0.0;
   out_3249349051420756862[294] = 0.0;
   out_3249349051420756862[295] = 0.0;
   out_3249349051420756862[296] = 0.0;
   out_3249349051420756862[297] = 0.0;
   out_3249349051420756862[298] = 0.0;
   out_3249349051420756862[299] = 0.0;
   out_3249349051420756862[300] = 0.0;
   out_3249349051420756862[301] = 0.0;
   out_3249349051420756862[302] = 0.0;
   out_3249349051420756862[303] = 0.0;
   out_3249349051420756862[304] = 1.0;
   out_3249349051420756862[305] = 0.0;
   out_3249349051420756862[306] = 0.0;
   out_3249349051420756862[307] = 0.0;
   out_3249349051420756862[308] = 0.0;
   out_3249349051420756862[309] = 0.0;
   out_3249349051420756862[310] = 0.0;
   out_3249349051420756862[311] = 0.0;
   out_3249349051420756862[312] = 0.0;
   out_3249349051420756862[313] = 0.0;
   out_3249349051420756862[314] = 0.0;
   out_3249349051420756862[315] = 0.0;
   out_3249349051420756862[316] = 0.0;
   out_3249349051420756862[317] = 0.0;
   out_3249349051420756862[318] = 0.0;
   out_3249349051420756862[319] = 0.0;
   out_3249349051420756862[320] = 0.0;
   out_3249349051420756862[321] = 0.0;
   out_3249349051420756862[322] = 0.0;
   out_3249349051420756862[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5432931765517539191) {
   out_5432931765517539191[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5432931765517539191[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5432931765517539191[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5432931765517539191[3] = dt*state[12] + state[3];
   out_5432931765517539191[4] = dt*state[13] + state[4];
   out_5432931765517539191[5] = dt*state[14] + state[5];
   out_5432931765517539191[6] = state[6];
   out_5432931765517539191[7] = state[7];
   out_5432931765517539191[8] = state[8];
   out_5432931765517539191[9] = state[9];
   out_5432931765517539191[10] = state[10];
   out_5432931765517539191[11] = state[11];
   out_5432931765517539191[12] = state[12];
   out_5432931765517539191[13] = state[13];
   out_5432931765517539191[14] = state[14];
   out_5432931765517539191[15] = state[15];
   out_5432931765517539191[16] = state[16];
   out_5432931765517539191[17] = state[17];
}
void F_fun(double *state, double dt, double *out_2727849687671059041) {
   out_2727849687671059041[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2727849687671059041[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2727849687671059041[2] = 0;
   out_2727849687671059041[3] = 0;
   out_2727849687671059041[4] = 0;
   out_2727849687671059041[5] = 0;
   out_2727849687671059041[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2727849687671059041[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2727849687671059041[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_2727849687671059041[9] = 0;
   out_2727849687671059041[10] = 0;
   out_2727849687671059041[11] = 0;
   out_2727849687671059041[12] = 0;
   out_2727849687671059041[13] = 0;
   out_2727849687671059041[14] = 0;
   out_2727849687671059041[15] = 0;
   out_2727849687671059041[16] = 0;
   out_2727849687671059041[17] = 0;
   out_2727849687671059041[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2727849687671059041[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2727849687671059041[20] = 0;
   out_2727849687671059041[21] = 0;
   out_2727849687671059041[22] = 0;
   out_2727849687671059041[23] = 0;
   out_2727849687671059041[24] = 0;
   out_2727849687671059041[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2727849687671059041[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_2727849687671059041[27] = 0;
   out_2727849687671059041[28] = 0;
   out_2727849687671059041[29] = 0;
   out_2727849687671059041[30] = 0;
   out_2727849687671059041[31] = 0;
   out_2727849687671059041[32] = 0;
   out_2727849687671059041[33] = 0;
   out_2727849687671059041[34] = 0;
   out_2727849687671059041[35] = 0;
   out_2727849687671059041[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2727849687671059041[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2727849687671059041[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2727849687671059041[39] = 0;
   out_2727849687671059041[40] = 0;
   out_2727849687671059041[41] = 0;
   out_2727849687671059041[42] = 0;
   out_2727849687671059041[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2727849687671059041[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_2727849687671059041[45] = 0;
   out_2727849687671059041[46] = 0;
   out_2727849687671059041[47] = 0;
   out_2727849687671059041[48] = 0;
   out_2727849687671059041[49] = 0;
   out_2727849687671059041[50] = 0;
   out_2727849687671059041[51] = 0;
   out_2727849687671059041[52] = 0;
   out_2727849687671059041[53] = 0;
   out_2727849687671059041[54] = 0;
   out_2727849687671059041[55] = 0;
   out_2727849687671059041[56] = 0;
   out_2727849687671059041[57] = 1;
   out_2727849687671059041[58] = 0;
   out_2727849687671059041[59] = 0;
   out_2727849687671059041[60] = 0;
   out_2727849687671059041[61] = 0;
   out_2727849687671059041[62] = 0;
   out_2727849687671059041[63] = 0;
   out_2727849687671059041[64] = 0;
   out_2727849687671059041[65] = 0;
   out_2727849687671059041[66] = dt;
   out_2727849687671059041[67] = 0;
   out_2727849687671059041[68] = 0;
   out_2727849687671059041[69] = 0;
   out_2727849687671059041[70] = 0;
   out_2727849687671059041[71] = 0;
   out_2727849687671059041[72] = 0;
   out_2727849687671059041[73] = 0;
   out_2727849687671059041[74] = 0;
   out_2727849687671059041[75] = 0;
   out_2727849687671059041[76] = 1;
   out_2727849687671059041[77] = 0;
   out_2727849687671059041[78] = 0;
   out_2727849687671059041[79] = 0;
   out_2727849687671059041[80] = 0;
   out_2727849687671059041[81] = 0;
   out_2727849687671059041[82] = 0;
   out_2727849687671059041[83] = 0;
   out_2727849687671059041[84] = 0;
   out_2727849687671059041[85] = dt;
   out_2727849687671059041[86] = 0;
   out_2727849687671059041[87] = 0;
   out_2727849687671059041[88] = 0;
   out_2727849687671059041[89] = 0;
   out_2727849687671059041[90] = 0;
   out_2727849687671059041[91] = 0;
   out_2727849687671059041[92] = 0;
   out_2727849687671059041[93] = 0;
   out_2727849687671059041[94] = 0;
   out_2727849687671059041[95] = 1;
   out_2727849687671059041[96] = 0;
   out_2727849687671059041[97] = 0;
   out_2727849687671059041[98] = 0;
   out_2727849687671059041[99] = 0;
   out_2727849687671059041[100] = 0;
   out_2727849687671059041[101] = 0;
   out_2727849687671059041[102] = 0;
   out_2727849687671059041[103] = 0;
   out_2727849687671059041[104] = dt;
   out_2727849687671059041[105] = 0;
   out_2727849687671059041[106] = 0;
   out_2727849687671059041[107] = 0;
   out_2727849687671059041[108] = 0;
   out_2727849687671059041[109] = 0;
   out_2727849687671059041[110] = 0;
   out_2727849687671059041[111] = 0;
   out_2727849687671059041[112] = 0;
   out_2727849687671059041[113] = 0;
   out_2727849687671059041[114] = 1;
   out_2727849687671059041[115] = 0;
   out_2727849687671059041[116] = 0;
   out_2727849687671059041[117] = 0;
   out_2727849687671059041[118] = 0;
   out_2727849687671059041[119] = 0;
   out_2727849687671059041[120] = 0;
   out_2727849687671059041[121] = 0;
   out_2727849687671059041[122] = 0;
   out_2727849687671059041[123] = 0;
   out_2727849687671059041[124] = 0;
   out_2727849687671059041[125] = 0;
   out_2727849687671059041[126] = 0;
   out_2727849687671059041[127] = 0;
   out_2727849687671059041[128] = 0;
   out_2727849687671059041[129] = 0;
   out_2727849687671059041[130] = 0;
   out_2727849687671059041[131] = 0;
   out_2727849687671059041[132] = 0;
   out_2727849687671059041[133] = 1;
   out_2727849687671059041[134] = 0;
   out_2727849687671059041[135] = 0;
   out_2727849687671059041[136] = 0;
   out_2727849687671059041[137] = 0;
   out_2727849687671059041[138] = 0;
   out_2727849687671059041[139] = 0;
   out_2727849687671059041[140] = 0;
   out_2727849687671059041[141] = 0;
   out_2727849687671059041[142] = 0;
   out_2727849687671059041[143] = 0;
   out_2727849687671059041[144] = 0;
   out_2727849687671059041[145] = 0;
   out_2727849687671059041[146] = 0;
   out_2727849687671059041[147] = 0;
   out_2727849687671059041[148] = 0;
   out_2727849687671059041[149] = 0;
   out_2727849687671059041[150] = 0;
   out_2727849687671059041[151] = 0;
   out_2727849687671059041[152] = 1;
   out_2727849687671059041[153] = 0;
   out_2727849687671059041[154] = 0;
   out_2727849687671059041[155] = 0;
   out_2727849687671059041[156] = 0;
   out_2727849687671059041[157] = 0;
   out_2727849687671059041[158] = 0;
   out_2727849687671059041[159] = 0;
   out_2727849687671059041[160] = 0;
   out_2727849687671059041[161] = 0;
   out_2727849687671059041[162] = 0;
   out_2727849687671059041[163] = 0;
   out_2727849687671059041[164] = 0;
   out_2727849687671059041[165] = 0;
   out_2727849687671059041[166] = 0;
   out_2727849687671059041[167] = 0;
   out_2727849687671059041[168] = 0;
   out_2727849687671059041[169] = 0;
   out_2727849687671059041[170] = 0;
   out_2727849687671059041[171] = 1;
   out_2727849687671059041[172] = 0;
   out_2727849687671059041[173] = 0;
   out_2727849687671059041[174] = 0;
   out_2727849687671059041[175] = 0;
   out_2727849687671059041[176] = 0;
   out_2727849687671059041[177] = 0;
   out_2727849687671059041[178] = 0;
   out_2727849687671059041[179] = 0;
   out_2727849687671059041[180] = 0;
   out_2727849687671059041[181] = 0;
   out_2727849687671059041[182] = 0;
   out_2727849687671059041[183] = 0;
   out_2727849687671059041[184] = 0;
   out_2727849687671059041[185] = 0;
   out_2727849687671059041[186] = 0;
   out_2727849687671059041[187] = 0;
   out_2727849687671059041[188] = 0;
   out_2727849687671059041[189] = 0;
   out_2727849687671059041[190] = 1;
   out_2727849687671059041[191] = 0;
   out_2727849687671059041[192] = 0;
   out_2727849687671059041[193] = 0;
   out_2727849687671059041[194] = 0;
   out_2727849687671059041[195] = 0;
   out_2727849687671059041[196] = 0;
   out_2727849687671059041[197] = 0;
   out_2727849687671059041[198] = 0;
   out_2727849687671059041[199] = 0;
   out_2727849687671059041[200] = 0;
   out_2727849687671059041[201] = 0;
   out_2727849687671059041[202] = 0;
   out_2727849687671059041[203] = 0;
   out_2727849687671059041[204] = 0;
   out_2727849687671059041[205] = 0;
   out_2727849687671059041[206] = 0;
   out_2727849687671059041[207] = 0;
   out_2727849687671059041[208] = 0;
   out_2727849687671059041[209] = 1;
   out_2727849687671059041[210] = 0;
   out_2727849687671059041[211] = 0;
   out_2727849687671059041[212] = 0;
   out_2727849687671059041[213] = 0;
   out_2727849687671059041[214] = 0;
   out_2727849687671059041[215] = 0;
   out_2727849687671059041[216] = 0;
   out_2727849687671059041[217] = 0;
   out_2727849687671059041[218] = 0;
   out_2727849687671059041[219] = 0;
   out_2727849687671059041[220] = 0;
   out_2727849687671059041[221] = 0;
   out_2727849687671059041[222] = 0;
   out_2727849687671059041[223] = 0;
   out_2727849687671059041[224] = 0;
   out_2727849687671059041[225] = 0;
   out_2727849687671059041[226] = 0;
   out_2727849687671059041[227] = 0;
   out_2727849687671059041[228] = 1;
   out_2727849687671059041[229] = 0;
   out_2727849687671059041[230] = 0;
   out_2727849687671059041[231] = 0;
   out_2727849687671059041[232] = 0;
   out_2727849687671059041[233] = 0;
   out_2727849687671059041[234] = 0;
   out_2727849687671059041[235] = 0;
   out_2727849687671059041[236] = 0;
   out_2727849687671059041[237] = 0;
   out_2727849687671059041[238] = 0;
   out_2727849687671059041[239] = 0;
   out_2727849687671059041[240] = 0;
   out_2727849687671059041[241] = 0;
   out_2727849687671059041[242] = 0;
   out_2727849687671059041[243] = 0;
   out_2727849687671059041[244] = 0;
   out_2727849687671059041[245] = 0;
   out_2727849687671059041[246] = 0;
   out_2727849687671059041[247] = 1;
   out_2727849687671059041[248] = 0;
   out_2727849687671059041[249] = 0;
   out_2727849687671059041[250] = 0;
   out_2727849687671059041[251] = 0;
   out_2727849687671059041[252] = 0;
   out_2727849687671059041[253] = 0;
   out_2727849687671059041[254] = 0;
   out_2727849687671059041[255] = 0;
   out_2727849687671059041[256] = 0;
   out_2727849687671059041[257] = 0;
   out_2727849687671059041[258] = 0;
   out_2727849687671059041[259] = 0;
   out_2727849687671059041[260] = 0;
   out_2727849687671059041[261] = 0;
   out_2727849687671059041[262] = 0;
   out_2727849687671059041[263] = 0;
   out_2727849687671059041[264] = 0;
   out_2727849687671059041[265] = 0;
   out_2727849687671059041[266] = 1;
   out_2727849687671059041[267] = 0;
   out_2727849687671059041[268] = 0;
   out_2727849687671059041[269] = 0;
   out_2727849687671059041[270] = 0;
   out_2727849687671059041[271] = 0;
   out_2727849687671059041[272] = 0;
   out_2727849687671059041[273] = 0;
   out_2727849687671059041[274] = 0;
   out_2727849687671059041[275] = 0;
   out_2727849687671059041[276] = 0;
   out_2727849687671059041[277] = 0;
   out_2727849687671059041[278] = 0;
   out_2727849687671059041[279] = 0;
   out_2727849687671059041[280] = 0;
   out_2727849687671059041[281] = 0;
   out_2727849687671059041[282] = 0;
   out_2727849687671059041[283] = 0;
   out_2727849687671059041[284] = 0;
   out_2727849687671059041[285] = 1;
   out_2727849687671059041[286] = 0;
   out_2727849687671059041[287] = 0;
   out_2727849687671059041[288] = 0;
   out_2727849687671059041[289] = 0;
   out_2727849687671059041[290] = 0;
   out_2727849687671059041[291] = 0;
   out_2727849687671059041[292] = 0;
   out_2727849687671059041[293] = 0;
   out_2727849687671059041[294] = 0;
   out_2727849687671059041[295] = 0;
   out_2727849687671059041[296] = 0;
   out_2727849687671059041[297] = 0;
   out_2727849687671059041[298] = 0;
   out_2727849687671059041[299] = 0;
   out_2727849687671059041[300] = 0;
   out_2727849687671059041[301] = 0;
   out_2727849687671059041[302] = 0;
   out_2727849687671059041[303] = 0;
   out_2727849687671059041[304] = 1;
   out_2727849687671059041[305] = 0;
   out_2727849687671059041[306] = 0;
   out_2727849687671059041[307] = 0;
   out_2727849687671059041[308] = 0;
   out_2727849687671059041[309] = 0;
   out_2727849687671059041[310] = 0;
   out_2727849687671059041[311] = 0;
   out_2727849687671059041[312] = 0;
   out_2727849687671059041[313] = 0;
   out_2727849687671059041[314] = 0;
   out_2727849687671059041[315] = 0;
   out_2727849687671059041[316] = 0;
   out_2727849687671059041[317] = 0;
   out_2727849687671059041[318] = 0;
   out_2727849687671059041[319] = 0;
   out_2727849687671059041[320] = 0;
   out_2727849687671059041[321] = 0;
   out_2727849687671059041[322] = 0;
   out_2727849687671059041[323] = 1;
}
void h_4(double *state, double *unused, double *out_7232734351538059647) {
   out_7232734351538059647[0] = state[6] + state[9];
   out_7232734351538059647[1] = state[7] + state[10];
   out_7232734351538059647[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6523571130211706115) {
   out_6523571130211706115[0] = 0;
   out_6523571130211706115[1] = 0;
   out_6523571130211706115[2] = 0;
   out_6523571130211706115[3] = 0;
   out_6523571130211706115[4] = 0;
   out_6523571130211706115[5] = 0;
   out_6523571130211706115[6] = 1;
   out_6523571130211706115[7] = 0;
   out_6523571130211706115[8] = 0;
   out_6523571130211706115[9] = 1;
   out_6523571130211706115[10] = 0;
   out_6523571130211706115[11] = 0;
   out_6523571130211706115[12] = 0;
   out_6523571130211706115[13] = 0;
   out_6523571130211706115[14] = 0;
   out_6523571130211706115[15] = 0;
   out_6523571130211706115[16] = 0;
   out_6523571130211706115[17] = 0;
   out_6523571130211706115[18] = 0;
   out_6523571130211706115[19] = 0;
   out_6523571130211706115[20] = 0;
   out_6523571130211706115[21] = 0;
   out_6523571130211706115[22] = 0;
   out_6523571130211706115[23] = 0;
   out_6523571130211706115[24] = 0;
   out_6523571130211706115[25] = 1;
   out_6523571130211706115[26] = 0;
   out_6523571130211706115[27] = 0;
   out_6523571130211706115[28] = 1;
   out_6523571130211706115[29] = 0;
   out_6523571130211706115[30] = 0;
   out_6523571130211706115[31] = 0;
   out_6523571130211706115[32] = 0;
   out_6523571130211706115[33] = 0;
   out_6523571130211706115[34] = 0;
   out_6523571130211706115[35] = 0;
   out_6523571130211706115[36] = 0;
   out_6523571130211706115[37] = 0;
   out_6523571130211706115[38] = 0;
   out_6523571130211706115[39] = 0;
   out_6523571130211706115[40] = 0;
   out_6523571130211706115[41] = 0;
   out_6523571130211706115[42] = 0;
   out_6523571130211706115[43] = 0;
   out_6523571130211706115[44] = 1;
   out_6523571130211706115[45] = 0;
   out_6523571130211706115[46] = 0;
   out_6523571130211706115[47] = 1;
   out_6523571130211706115[48] = 0;
   out_6523571130211706115[49] = 0;
   out_6523571130211706115[50] = 0;
   out_6523571130211706115[51] = 0;
   out_6523571130211706115[52] = 0;
   out_6523571130211706115[53] = 0;
}
void h_10(double *state, double *unused, double *out_635550838215594982) {
   out_635550838215594982[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_635550838215594982[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_635550838215594982[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_9209540089341204390) {
   out_9209540089341204390[0] = 0;
   out_9209540089341204390[1] = 9.8100000000000005*cos(state[1]);
   out_9209540089341204390[2] = 0;
   out_9209540089341204390[3] = 0;
   out_9209540089341204390[4] = -state[8];
   out_9209540089341204390[5] = state[7];
   out_9209540089341204390[6] = 0;
   out_9209540089341204390[7] = state[5];
   out_9209540089341204390[8] = -state[4];
   out_9209540089341204390[9] = 0;
   out_9209540089341204390[10] = 0;
   out_9209540089341204390[11] = 0;
   out_9209540089341204390[12] = 1;
   out_9209540089341204390[13] = 0;
   out_9209540089341204390[14] = 0;
   out_9209540089341204390[15] = 1;
   out_9209540089341204390[16] = 0;
   out_9209540089341204390[17] = 0;
   out_9209540089341204390[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_9209540089341204390[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_9209540089341204390[20] = 0;
   out_9209540089341204390[21] = state[8];
   out_9209540089341204390[22] = 0;
   out_9209540089341204390[23] = -state[6];
   out_9209540089341204390[24] = -state[5];
   out_9209540089341204390[25] = 0;
   out_9209540089341204390[26] = state[3];
   out_9209540089341204390[27] = 0;
   out_9209540089341204390[28] = 0;
   out_9209540089341204390[29] = 0;
   out_9209540089341204390[30] = 0;
   out_9209540089341204390[31] = 1;
   out_9209540089341204390[32] = 0;
   out_9209540089341204390[33] = 0;
   out_9209540089341204390[34] = 1;
   out_9209540089341204390[35] = 0;
   out_9209540089341204390[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_9209540089341204390[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_9209540089341204390[38] = 0;
   out_9209540089341204390[39] = -state[7];
   out_9209540089341204390[40] = state[6];
   out_9209540089341204390[41] = 0;
   out_9209540089341204390[42] = state[4];
   out_9209540089341204390[43] = -state[3];
   out_9209540089341204390[44] = 0;
   out_9209540089341204390[45] = 0;
   out_9209540089341204390[46] = 0;
   out_9209540089341204390[47] = 0;
   out_9209540089341204390[48] = 0;
   out_9209540089341204390[49] = 0;
   out_9209540089341204390[50] = 1;
   out_9209540089341204390[51] = 0;
   out_9209540089341204390[52] = 0;
   out_9209540089341204390[53] = 1;
}
void h_13(double *state, double *unused, double *out_400150804030781628) {
   out_400150804030781628[0] = state[3];
   out_400150804030781628[1] = state[4];
   out_400150804030781628[2] = state[5];
}
void H_13(double *state, double *unused, double *out_1087060078104994814) {
   out_1087060078104994814[0] = 0;
   out_1087060078104994814[1] = 0;
   out_1087060078104994814[2] = 0;
   out_1087060078104994814[3] = 1;
   out_1087060078104994814[4] = 0;
   out_1087060078104994814[5] = 0;
   out_1087060078104994814[6] = 0;
   out_1087060078104994814[7] = 0;
   out_1087060078104994814[8] = 0;
   out_1087060078104994814[9] = 0;
   out_1087060078104994814[10] = 0;
   out_1087060078104994814[11] = 0;
   out_1087060078104994814[12] = 0;
   out_1087060078104994814[13] = 0;
   out_1087060078104994814[14] = 0;
   out_1087060078104994814[15] = 0;
   out_1087060078104994814[16] = 0;
   out_1087060078104994814[17] = 0;
   out_1087060078104994814[18] = 0;
   out_1087060078104994814[19] = 0;
   out_1087060078104994814[20] = 0;
   out_1087060078104994814[21] = 0;
   out_1087060078104994814[22] = 1;
   out_1087060078104994814[23] = 0;
   out_1087060078104994814[24] = 0;
   out_1087060078104994814[25] = 0;
   out_1087060078104994814[26] = 0;
   out_1087060078104994814[27] = 0;
   out_1087060078104994814[28] = 0;
   out_1087060078104994814[29] = 0;
   out_1087060078104994814[30] = 0;
   out_1087060078104994814[31] = 0;
   out_1087060078104994814[32] = 0;
   out_1087060078104994814[33] = 0;
   out_1087060078104994814[34] = 0;
   out_1087060078104994814[35] = 0;
   out_1087060078104994814[36] = 0;
   out_1087060078104994814[37] = 0;
   out_1087060078104994814[38] = 0;
   out_1087060078104994814[39] = 0;
   out_1087060078104994814[40] = 0;
   out_1087060078104994814[41] = 1;
   out_1087060078104994814[42] = 0;
   out_1087060078104994814[43] = 0;
   out_1087060078104994814[44] = 0;
   out_1087060078104994814[45] = 0;
   out_1087060078104994814[46] = 0;
   out_1087060078104994814[47] = 0;
   out_1087060078104994814[48] = 0;
   out_1087060078104994814[49] = 0;
   out_1087060078104994814[50] = 0;
   out_1087060078104994814[51] = 0;
   out_1087060078104994814[52] = 0;
   out_1087060078104994814[53] = 0;
}
void h_14(double *state, double *unused, double *out_4238769098804087488) {
   out_4238769098804087488[0] = state[6];
   out_4238769098804087488[1] = state[7];
   out_4238769098804087488[2] = state[8];
}
void H_14(double *state, double *unused, double *out_2560330273872221586) {
   out_2560330273872221586[0] = 0;
   out_2560330273872221586[1] = 0;
   out_2560330273872221586[2] = 0;
   out_2560330273872221586[3] = 0;
   out_2560330273872221586[4] = 0;
   out_2560330273872221586[5] = 0;
   out_2560330273872221586[6] = 1;
   out_2560330273872221586[7] = 0;
   out_2560330273872221586[8] = 0;
   out_2560330273872221586[9] = 0;
   out_2560330273872221586[10] = 0;
   out_2560330273872221586[11] = 0;
   out_2560330273872221586[12] = 0;
   out_2560330273872221586[13] = 0;
   out_2560330273872221586[14] = 0;
   out_2560330273872221586[15] = 0;
   out_2560330273872221586[16] = 0;
   out_2560330273872221586[17] = 0;
   out_2560330273872221586[18] = 0;
   out_2560330273872221586[19] = 0;
   out_2560330273872221586[20] = 0;
   out_2560330273872221586[21] = 0;
   out_2560330273872221586[22] = 0;
   out_2560330273872221586[23] = 0;
   out_2560330273872221586[24] = 0;
   out_2560330273872221586[25] = 1;
   out_2560330273872221586[26] = 0;
   out_2560330273872221586[27] = 0;
   out_2560330273872221586[28] = 0;
   out_2560330273872221586[29] = 0;
   out_2560330273872221586[30] = 0;
   out_2560330273872221586[31] = 0;
   out_2560330273872221586[32] = 0;
   out_2560330273872221586[33] = 0;
   out_2560330273872221586[34] = 0;
   out_2560330273872221586[35] = 0;
   out_2560330273872221586[36] = 0;
   out_2560330273872221586[37] = 0;
   out_2560330273872221586[38] = 0;
   out_2560330273872221586[39] = 0;
   out_2560330273872221586[40] = 0;
   out_2560330273872221586[41] = 0;
   out_2560330273872221586[42] = 0;
   out_2560330273872221586[43] = 0;
   out_2560330273872221586[44] = 1;
   out_2560330273872221586[45] = 0;
   out_2560330273872221586[46] = 0;
   out_2560330273872221586[47] = 0;
   out_2560330273872221586[48] = 0;
   out_2560330273872221586[49] = 0;
   out_2560330273872221586[50] = 0;
   out_2560330273872221586[51] = 0;
   out_2560330273872221586[52] = 0;
   out_2560330273872221586[53] = 0;
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
void pose_err_fun(double *nom_x, double *delta_x, double *out_908254512132799916) {
  err_fun(nom_x, delta_x, out_908254512132799916);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1478078535588975513) {
  inv_err_fun(nom_x, true_x, out_1478078535588975513);
}
void pose_H_mod_fun(double *state, double *out_3249349051420756862) {
  H_mod_fun(state, out_3249349051420756862);
}
void pose_f_fun(double *state, double dt, double *out_5432931765517539191) {
  f_fun(state,  dt, out_5432931765517539191);
}
void pose_F_fun(double *state, double dt, double *out_2727849687671059041) {
  F_fun(state,  dt, out_2727849687671059041);
}
void pose_h_4(double *state, double *unused, double *out_7232734351538059647) {
  h_4(state, unused, out_7232734351538059647);
}
void pose_H_4(double *state, double *unused, double *out_6523571130211706115) {
  H_4(state, unused, out_6523571130211706115);
}
void pose_h_10(double *state, double *unused, double *out_635550838215594982) {
  h_10(state, unused, out_635550838215594982);
}
void pose_H_10(double *state, double *unused, double *out_9209540089341204390) {
  H_10(state, unused, out_9209540089341204390);
}
void pose_h_13(double *state, double *unused, double *out_400150804030781628) {
  h_13(state, unused, out_400150804030781628);
}
void pose_H_13(double *state, double *unused, double *out_1087060078104994814) {
  H_13(state, unused, out_1087060078104994814);
}
void pose_h_14(double *state, double *unused, double *out_4238769098804087488) {
  h_14(state, unused, out_4238769098804087488);
}
void pose_H_14(double *state, double *unused, double *out_2560330273872221586) {
  H_14(state, unused, out_2560330273872221586);
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
