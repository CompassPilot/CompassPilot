#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2944995704786546086) {
   out_2944995704786546086[0] = delta_x[0] + nom_x[0];
   out_2944995704786546086[1] = delta_x[1] + nom_x[1];
   out_2944995704786546086[2] = delta_x[2] + nom_x[2];
   out_2944995704786546086[3] = delta_x[3] + nom_x[3];
   out_2944995704786546086[4] = delta_x[4] + nom_x[4];
   out_2944995704786546086[5] = delta_x[5] + nom_x[5];
   out_2944995704786546086[6] = delta_x[6] + nom_x[6];
   out_2944995704786546086[7] = delta_x[7] + nom_x[7];
   out_2944995704786546086[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5103335814858408194) {
   out_5103335814858408194[0] = -nom_x[0] + true_x[0];
   out_5103335814858408194[1] = -nom_x[1] + true_x[1];
   out_5103335814858408194[2] = -nom_x[2] + true_x[2];
   out_5103335814858408194[3] = -nom_x[3] + true_x[3];
   out_5103335814858408194[4] = -nom_x[4] + true_x[4];
   out_5103335814858408194[5] = -nom_x[5] + true_x[5];
   out_5103335814858408194[6] = -nom_x[6] + true_x[6];
   out_5103335814858408194[7] = -nom_x[7] + true_x[7];
   out_5103335814858408194[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_3080422690750513034) {
   out_3080422690750513034[0] = 1.0;
   out_3080422690750513034[1] = 0.0;
   out_3080422690750513034[2] = 0.0;
   out_3080422690750513034[3] = 0.0;
   out_3080422690750513034[4] = 0.0;
   out_3080422690750513034[5] = 0.0;
   out_3080422690750513034[6] = 0.0;
   out_3080422690750513034[7] = 0.0;
   out_3080422690750513034[8] = 0.0;
   out_3080422690750513034[9] = 0.0;
   out_3080422690750513034[10] = 1.0;
   out_3080422690750513034[11] = 0.0;
   out_3080422690750513034[12] = 0.0;
   out_3080422690750513034[13] = 0.0;
   out_3080422690750513034[14] = 0.0;
   out_3080422690750513034[15] = 0.0;
   out_3080422690750513034[16] = 0.0;
   out_3080422690750513034[17] = 0.0;
   out_3080422690750513034[18] = 0.0;
   out_3080422690750513034[19] = 0.0;
   out_3080422690750513034[20] = 1.0;
   out_3080422690750513034[21] = 0.0;
   out_3080422690750513034[22] = 0.0;
   out_3080422690750513034[23] = 0.0;
   out_3080422690750513034[24] = 0.0;
   out_3080422690750513034[25] = 0.0;
   out_3080422690750513034[26] = 0.0;
   out_3080422690750513034[27] = 0.0;
   out_3080422690750513034[28] = 0.0;
   out_3080422690750513034[29] = 0.0;
   out_3080422690750513034[30] = 1.0;
   out_3080422690750513034[31] = 0.0;
   out_3080422690750513034[32] = 0.0;
   out_3080422690750513034[33] = 0.0;
   out_3080422690750513034[34] = 0.0;
   out_3080422690750513034[35] = 0.0;
   out_3080422690750513034[36] = 0.0;
   out_3080422690750513034[37] = 0.0;
   out_3080422690750513034[38] = 0.0;
   out_3080422690750513034[39] = 0.0;
   out_3080422690750513034[40] = 1.0;
   out_3080422690750513034[41] = 0.0;
   out_3080422690750513034[42] = 0.0;
   out_3080422690750513034[43] = 0.0;
   out_3080422690750513034[44] = 0.0;
   out_3080422690750513034[45] = 0.0;
   out_3080422690750513034[46] = 0.0;
   out_3080422690750513034[47] = 0.0;
   out_3080422690750513034[48] = 0.0;
   out_3080422690750513034[49] = 0.0;
   out_3080422690750513034[50] = 1.0;
   out_3080422690750513034[51] = 0.0;
   out_3080422690750513034[52] = 0.0;
   out_3080422690750513034[53] = 0.0;
   out_3080422690750513034[54] = 0.0;
   out_3080422690750513034[55] = 0.0;
   out_3080422690750513034[56] = 0.0;
   out_3080422690750513034[57] = 0.0;
   out_3080422690750513034[58] = 0.0;
   out_3080422690750513034[59] = 0.0;
   out_3080422690750513034[60] = 1.0;
   out_3080422690750513034[61] = 0.0;
   out_3080422690750513034[62] = 0.0;
   out_3080422690750513034[63] = 0.0;
   out_3080422690750513034[64] = 0.0;
   out_3080422690750513034[65] = 0.0;
   out_3080422690750513034[66] = 0.0;
   out_3080422690750513034[67] = 0.0;
   out_3080422690750513034[68] = 0.0;
   out_3080422690750513034[69] = 0.0;
   out_3080422690750513034[70] = 1.0;
   out_3080422690750513034[71] = 0.0;
   out_3080422690750513034[72] = 0.0;
   out_3080422690750513034[73] = 0.0;
   out_3080422690750513034[74] = 0.0;
   out_3080422690750513034[75] = 0.0;
   out_3080422690750513034[76] = 0.0;
   out_3080422690750513034[77] = 0.0;
   out_3080422690750513034[78] = 0.0;
   out_3080422690750513034[79] = 0.0;
   out_3080422690750513034[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4878075406049581454) {
   out_4878075406049581454[0] = state[0];
   out_4878075406049581454[1] = state[1];
   out_4878075406049581454[2] = state[2];
   out_4878075406049581454[3] = state[3];
   out_4878075406049581454[4] = state[4];
   out_4878075406049581454[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4878075406049581454[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4878075406049581454[7] = state[7];
   out_4878075406049581454[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4214148513384381455) {
   out_4214148513384381455[0] = 1;
   out_4214148513384381455[1] = 0;
   out_4214148513384381455[2] = 0;
   out_4214148513384381455[3] = 0;
   out_4214148513384381455[4] = 0;
   out_4214148513384381455[5] = 0;
   out_4214148513384381455[6] = 0;
   out_4214148513384381455[7] = 0;
   out_4214148513384381455[8] = 0;
   out_4214148513384381455[9] = 0;
   out_4214148513384381455[10] = 1;
   out_4214148513384381455[11] = 0;
   out_4214148513384381455[12] = 0;
   out_4214148513384381455[13] = 0;
   out_4214148513384381455[14] = 0;
   out_4214148513384381455[15] = 0;
   out_4214148513384381455[16] = 0;
   out_4214148513384381455[17] = 0;
   out_4214148513384381455[18] = 0;
   out_4214148513384381455[19] = 0;
   out_4214148513384381455[20] = 1;
   out_4214148513384381455[21] = 0;
   out_4214148513384381455[22] = 0;
   out_4214148513384381455[23] = 0;
   out_4214148513384381455[24] = 0;
   out_4214148513384381455[25] = 0;
   out_4214148513384381455[26] = 0;
   out_4214148513384381455[27] = 0;
   out_4214148513384381455[28] = 0;
   out_4214148513384381455[29] = 0;
   out_4214148513384381455[30] = 1;
   out_4214148513384381455[31] = 0;
   out_4214148513384381455[32] = 0;
   out_4214148513384381455[33] = 0;
   out_4214148513384381455[34] = 0;
   out_4214148513384381455[35] = 0;
   out_4214148513384381455[36] = 0;
   out_4214148513384381455[37] = 0;
   out_4214148513384381455[38] = 0;
   out_4214148513384381455[39] = 0;
   out_4214148513384381455[40] = 1;
   out_4214148513384381455[41] = 0;
   out_4214148513384381455[42] = 0;
   out_4214148513384381455[43] = 0;
   out_4214148513384381455[44] = 0;
   out_4214148513384381455[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4214148513384381455[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4214148513384381455[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4214148513384381455[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4214148513384381455[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4214148513384381455[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4214148513384381455[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4214148513384381455[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4214148513384381455[53] = -9.8100000000000005*dt;
   out_4214148513384381455[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4214148513384381455[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4214148513384381455[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4214148513384381455[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4214148513384381455[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4214148513384381455[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4214148513384381455[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4214148513384381455[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4214148513384381455[62] = 0;
   out_4214148513384381455[63] = 0;
   out_4214148513384381455[64] = 0;
   out_4214148513384381455[65] = 0;
   out_4214148513384381455[66] = 0;
   out_4214148513384381455[67] = 0;
   out_4214148513384381455[68] = 0;
   out_4214148513384381455[69] = 0;
   out_4214148513384381455[70] = 1;
   out_4214148513384381455[71] = 0;
   out_4214148513384381455[72] = 0;
   out_4214148513384381455[73] = 0;
   out_4214148513384381455[74] = 0;
   out_4214148513384381455[75] = 0;
   out_4214148513384381455[76] = 0;
   out_4214148513384381455[77] = 0;
   out_4214148513384381455[78] = 0;
   out_4214148513384381455[79] = 0;
   out_4214148513384381455[80] = 1;
}
void h_25(double *state, double *unused, double *out_1916755864117606233) {
   out_1916755864117606233[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6173133157046801345) {
   out_6173133157046801345[0] = 0;
   out_6173133157046801345[1] = 0;
   out_6173133157046801345[2] = 0;
   out_6173133157046801345[3] = 0;
   out_6173133157046801345[4] = 0;
   out_6173133157046801345[5] = 0;
   out_6173133157046801345[6] = 1;
   out_6173133157046801345[7] = 0;
   out_6173133157046801345[8] = 0;
}
void h_24(double *state, double *unused, double *out_7274133001747769888) {
   out_7274133001747769888[0] = state[4];
   out_7274133001747769888[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8398840941025669907) {
   out_8398840941025669907[0] = 0;
   out_8398840941025669907[1] = 0;
   out_8398840941025669907[2] = 0;
   out_8398840941025669907[3] = 0;
   out_8398840941025669907[4] = 1;
   out_8398840941025669907[5] = 0;
   out_8398840941025669907[6] = 0;
   out_8398840941025669907[7] = 0;
   out_8398840941025669907[8] = 0;
   out_8398840941025669907[9] = 0;
   out_8398840941025669907[10] = 0;
   out_8398840941025669907[11] = 0;
   out_8398840941025669907[12] = 0;
   out_8398840941025669907[13] = 0;
   out_8398840941025669907[14] = 1;
   out_8398840941025669907[15] = 0;
   out_8398840941025669907[16] = 0;
   out_8398840941025669907[17] = 0;
}
void h_30(double *state, double *unused, double *out_8766722952771272942) {
   out_8766722952771272942[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5356920575171133516) {
   out_5356920575171133516[0] = 0;
   out_5356920575171133516[1] = 0;
   out_5356920575171133516[2] = 0;
   out_5356920575171133516[3] = 0;
   out_5356920575171133516[4] = 1;
   out_5356920575171133516[5] = 0;
   out_5356920575171133516[6] = 0;
   out_5356920575171133516[7] = 0;
   out_5356920575171133516[8] = 0;
}
void h_26(double *state, double *unused, double *out_698051948931437909) {
   out_698051948931437909[0] = state[7];
}
void H_26(double *state, double *unused, double *out_2431629838172745121) {
   out_2431629838172745121[0] = 0;
   out_2431629838172745121[1] = 0;
   out_2431629838172745121[2] = 0;
   out_2431629838172745121[3] = 0;
   out_2431629838172745121[4] = 0;
   out_2431629838172745121[5] = 0;
   out_2431629838172745121[6] = 0;
   out_2431629838172745121[7] = 1;
   out_2431629838172745121[8] = 0;
}
void h_27(double *state, double *unused, double *out_3084917403543239412) {
   out_3084917403543239412[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3869030898103136364) {
   out_3869030898103136364[0] = 0;
   out_3869030898103136364[1] = 0;
   out_3869030898103136364[2] = 0;
   out_3869030898103136364[3] = 1;
   out_3869030898103136364[4] = 0;
   out_3869030898103136364[5] = 0;
   out_3869030898103136364[6] = 0;
   out_3869030898103136364[7] = 0;
   out_3869030898103136364[8] = 0;
}
void h_29(double *state, double *unused, double *out_4678347853277433029) {
   out_4678347853277433029[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4846689230856741332) {
   out_4846689230856741332[0] = 0;
   out_4846689230856741332[1] = 1;
   out_4846689230856741332[2] = 0;
   out_4846689230856741332[3] = 0;
   out_4846689230856741332[4] = 0;
   out_4846689230856741332[5] = 0;
   out_4846689230856741332[6] = 0;
   out_4846689230856741332[7] = 0;
   out_4846689230856741332[8] = 0;
}
void h_28(double *state, double *unused, double *out_48131352098906727) {
   out_48131352098906727[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4119298442798911582) {
   out_4119298442798911582[0] = 1;
   out_4119298442798911582[1] = 0;
   out_4119298442798911582[2] = 0;
   out_4119298442798911582[3] = 0;
   out_4119298442798911582[4] = 0;
   out_4119298442798911582[5] = 0;
   out_4119298442798911582[6] = 0;
   out_4119298442798911582[7] = 0;
   out_4119298442798911582[8] = 0;
}
void h_31(double *state, double *unused, double *out_4854079362232744703) {
   out_4854079362232744703[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6203779118923761773) {
   out_6203779118923761773[0] = 0;
   out_6203779118923761773[1] = 0;
   out_6203779118923761773[2] = 0;
   out_6203779118923761773[3] = 0;
   out_6203779118923761773[4] = 0;
   out_6203779118923761773[5] = 0;
   out_6203779118923761773[6] = 0;
   out_6203779118923761773[7] = 0;
   out_6203779118923761773[8] = 1;
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

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_2944995704786546086) {
  err_fun(nom_x, delta_x, out_2944995704786546086);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5103335814858408194) {
  inv_err_fun(nom_x, true_x, out_5103335814858408194);
}
void car_H_mod_fun(double *state, double *out_3080422690750513034) {
  H_mod_fun(state, out_3080422690750513034);
}
void car_f_fun(double *state, double dt, double *out_4878075406049581454) {
  f_fun(state,  dt, out_4878075406049581454);
}
void car_F_fun(double *state, double dt, double *out_4214148513384381455) {
  F_fun(state,  dt, out_4214148513384381455);
}
void car_h_25(double *state, double *unused, double *out_1916755864117606233) {
  h_25(state, unused, out_1916755864117606233);
}
void car_H_25(double *state, double *unused, double *out_6173133157046801345) {
  H_25(state, unused, out_6173133157046801345);
}
void car_h_24(double *state, double *unused, double *out_7274133001747769888) {
  h_24(state, unused, out_7274133001747769888);
}
void car_H_24(double *state, double *unused, double *out_8398840941025669907) {
  H_24(state, unused, out_8398840941025669907);
}
void car_h_30(double *state, double *unused, double *out_8766722952771272942) {
  h_30(state, unused, out_8766722952771272942);
}
void car_H_30(double *state, double *unused, double *out_5356920575171133516) {
  H_30(state, unused, out_5356920575171133516);
}
void car_h_26(double *state, double *unused, double *out_698051948931437909) {
  h_26(state, unused, out_698051948931437909);
}
void car_H_26(double *state, double *unused, double *out_2431629838172745121) {
  H_26(state, unused, out_2431629838172745121);
}
void car_h_27(double *state, double *unused, double *out_3084917403543239412) {
  h_27(state, unused, out_3084917403543239412);
}
void car_H_27(double *state, double *unused, double *out_3869030898103136364) {
  H_27(state, unused, out_3869030898103136364);
}
void car_h_29(double *state, double *unused, double *out_4678347853277433029) {
  h_29(state, unused, out_4678347853277433029);
}
void car_H_29(double *state, double *unused, double *out_4846689230856741332) {
  H_29(state, unused, out_4846689230856741332);
}
void car_h_28(double *state, double *unused, double *out_48131352098906727) {
  h_28(state, unused, out_48131352098906727);
}
void car_H_28(double *state, double *unused, double *out_4119298442798911582) {
  H_28(state, unused, out_4119298442798911582);
}
void car_h_31(double *state, double *unused, double *out_4854079362232744703) {
  h_31(state, unused, out_4854079362232744703);
}
void car_H_31(double *state, double *unused, double *out_6203779118923761773) {
  H_31(state, unused, out_6203779118923761773);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
