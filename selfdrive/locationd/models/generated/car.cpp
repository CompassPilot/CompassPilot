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
void err_fun(double *nom_x, double *delta_x, double *out_7908204057599693162) {
   out_7908204057599693162[0] = delta_x[0] + nom_x[0];
   out_7908204057599693162[1] = delta_x[1] + nom_x[1];
   out_7908204057599693162[2] = delta_x[2] + nom_x[2];
   out_7908204057599693162[3] = delta_x[3] + nom_x[3];
   out_7908204057599693162[4] = delta_x[4] + nom_x[4];
   out_7908204057599693162[5] = delta_x[5] + nom_x[5];
   out_7908204057599693162[6] = delta_x[6] + nom_x[6];
   out_7908204057599693162[7] = delta_x[7] + nom_x[7];
   out_7908204057599693162[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_3591353112255890273) {
   out_3591353112255890273[0] = -nom_x[0] + true_x[0];
   out_3591353112255890273[1] = -nom_x[1] + true_x[1];
   out_3591353112255890273[2] = -nom_x[2] + true_x[2];
   out_3591353112255890273[3] = -nom_x[3] + true_x[3];
   out_3591353112255890273[4] = -nom_x[4] + true_x[4];
   out_3591353112255890273[5] = -nom_x[5] + true_x[5];
   out_3591353112255890273[6] = -nom_x[6] + true_x[6];
   out_3591353112255890273[7] = -nom_x[7] + true_x[7];
   out_3591353112255890273[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7960573159970110864) {
   out_7960573159970110864[0] = 1.0;
   out_7960573159970110864[1] = 0.0;
   out_7960573159970110864[2] = 0.0;
   out_7960573159970110864[3] = 0.0;
   out_7960573159970110864[4] = 0.0;
   out_7960573159970110864[5] = 0.0;
   out_7960573159970110864[6] = 0.0;
   out_7960573159970110864[7] = 0.0;
   out_7960573159970110864[8] = 0.0;
   out_7960573159970110864[9] = 0.0;
   out_7960573159970110864[10] = 1.0;
   out_7960573159970110864[11] = 0.0;
   out_7960573159970110864[12] = 0.0;
   out_7960573159970110864[13] = 0.0;
   out_7960573159970110864[14] = 0.0;
   out_7960573159970110864[15] = 0.0;
   out_7960573159970110864[16] = 0.0;
   out_7960573159970110864[17] = 0.0;
   out_7960573159970110864[18] = 0.0;
   out_7960573159970110864[19] = 0.0;
   out_7960573159970110864[20] = 1.0;
   out_7960573159970110864[21] = 0.0;
   out_7960573159970110864[22] = 0.0;
   out_7960573159970110864[23] = 0.0;
   out_7960573159970110864[24] = 0.0;
   out_7960573159970110864[25] = 0.0;
   out_7960573159970110864[26] = 0.0;
   out_7960573159970110864[27] = 0.0;
   out_7960573159970110864[28] = 0.0;
   out_7960573159970110864[29] = 0.0;
   out_7960573159970110864[30] = 1.0;
   out_7960573159970110864[31] = 0.0;
   out_7960573159970110864[32] = 0.0;
   out_7960573159970110864[33] = 0.0;
   out_7960573159970110864[34] = 0.0;
   out_7960573159970110864[35] = 0.0;
   out_7960573159970110864[36] = 0.0;
   out_7960573159970110864[37] = 0.0;
   out_7960573159970110864[38] = 0.0;
   out_7960573159970110864[39] = 0.0;
   out_7960573159970110864[40] = 1.0;
   out_7960573159970110864[41] = 0.0;
   out_7960573159970110864[42] = 0.0;
   out_7960573159970110864[43] = 0.0;
   out_7960573159970110864[44] = 0.0;
   out_7960573159970110864[45] = 0.0;
   out_7960573159970110864[46] = 0.0;
   out_7960573159970110864[47] = 0.0;
   out_7960573159970110864[48] = 0.0;
   out_7960573159970110864[49] = 0.0;
   out_7960573159970110864[50] = 1.0;
   out_7960573159970110864[51] = 0.0;
   out_7960573159970110864[52] = 0.0;
   out_7960573159970110864[53] = 0.0;
   out_7960573159970110864[54] = 0.0;
   out_7960573159970110864[55] = 0.0;
   out_7960573159970110864[56] = 0.0;
   out_7960573159970110864[57] = 0.0;
   out_7960573159970110864[58] = 0.0;
   out_7960573159970110864[59] = 0.0;
   out_7960573159970110864[60] = 1.0;
   out_7960573159970110864[61] = 0.0;
   out_7960573159970110864[62] = 0.0;
   out_7960573159970110864[63] = 0.0;
   out_7960573159970110864[64] = 0.0;
   out_7960573159970110864[65] = 0.0;
   out_7960573159970110864[66] = 0.0;
   out_7960573159970110864[67] = 0.0;
   out_7960573159970110864[68] = 0.0;
   out_7960573159970110864[69] = 0.0;
   out_7960573159970110864[70] = 1.0;
   out_7960573159970110864[71] = 0.0;
   out_7960573159970110864[72] = 0.0;
   out_7960573159970110864[73] = 0.0;
   out_7960573159970110864[74] = 0.0;
   out_7960573159970110864[75] = 0.0;
   out_7960573159970110864[76] = 0.0;
   out_7960573159970110864[77] = 0.0;
   out_7960573159970110864[78] = 0.0;
   out_7960573159970110864[79] = 0.0;
   out_7960573159970110864[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_3939178357234727692) {
   out_3939178357234727692[0] = state[0];
   out_3939178357234727692[1] = state[1];
   out_3939178357234727692[2] = state[2];
   out_3939178357234727692[3] = state[3];
   out_3939178357234727692[4] = state[4];
   out_3939178357234727692[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_3939178357234727692[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_3939178357234727692[7] = state[7];
   out_3939178357234727692[8] = state[8];
}
void F_fun(double *state, double dt, double *out_7601566188878897936) {
   out_7601566188878897936[0] = 1;
   out_7601566188878897936[1] = 0;
   out_7601566188878897936[2] = 0;
   out_7601566188878897936[3] = 0;
   out_7601566188878897936[4] = 0;
   out_7601566188878897936[5] = 0;
   out_7601566188878897936[6] = 0;
   out_7601566188878897936[7] = 0;
   out_7601566188878897936[8] = 0;
   out_7601566188878897936[9] = 0;
   out_7601566188878897936[10] = 1;
   out_7601566188878897936[11] = 0;
   out_7601566188878897936[12] = 0;
   out_7601566188878897936[13] = 0;
   out_7601566188878897936[14] = 0;
   out_7601566188878897936[15] = 0;
   out_7601566188878897936[16] = 0;
   out_7601566188878897936[17] = 0;
   out_7601566188878897936[18] = 0;
   out_7601566188878897936[19] = 0;
   out_7601566188878897936[20] = 1;
   out_7601566188878897936[21] = 0;
   out_7601566188878897936[22] = 0;
   out_7601566188878897936[23] = 0;
   out_7601566188878897936[24] = 0;
   out_7601566188878897936[25] = 0;
   out_7601566188878897936[26] = 0;
   out_7601566188878897936[27] = 0;
   out_7601566188878897936[28] = 0;
   out_7601566188878897936[29] = 0;
   out_7601566188878897936[30] = 1;
   out_7601566188878897936[31] = 0;
   out_7601566188878897936[32] = 0;
   out_7601566188878897936[33] = 0;
   out_7601566188878897936[34] = 0;
   out_7601566188878897936[35] = 0;
   out_7601566188878897936[36] = 0;
   out_7601566188878897936[37] = 0;
   out_7601566188878897936[38] = 0;
   out_7601566188878897936[39] = 0;
   out_7601566188878897936[40] = 1;
   out_7601566188878897936[41] = 0;
   out_7601566188878897936[42] = 0;
   out_7601566188878897936[43] = 0;
   out_7601566188878897936[44] = 0;
   out_7601566188878897936[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_7601566188878897936[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_7601566188878897936[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7601566188878897936[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_7601566188878897936[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_7601566188878897936[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_7601566188878897936[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_7601566188878897936[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_7601566188878897936[53] = -9.8100000000000005*dt;
   out_7601566188878897936[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_7601566188878897936[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_7601566188878897936[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7601566188878897936[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7601566188878897936[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_7601566188878897936[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_7601566188878897936[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_7601566188878897936[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_7601566188878897936[62] = 0;
   out_7601566188878897936[63] = 0;
   out_7601566188878897936[64] = 0;
   out_7601566188878897936[65] = 0;
   out_7601566188878897936[66] = 0;
   out_7601566188878897936[67] = 0;
   out_7601566188878897936[68] = 0;
   out_7601566188878897936[69] = 0;
   out_7601566188878897936[70] = 1;
   out_7601566188878897936[71] = 0;
   out_7601566188878897936[72] = 0;
   out_7601566188878897936[73] = 0;
   out_7601566188878897936[74] = 0;
   out_7601566188878897936[75] = 0;
   out_7601566188878897936[76] = 0;
   out_7601566188878897936[77] = 0;
   out_7601566188878897936[78] = 0;
   out_7601566188878897936[79] = 0;
   out_7601566188878897936[80] = 1;
}
void h_25(double *state, double *unused, double *out_1655895321249480568) {
   out_1655895321249480568[0] = state[6];
}
void H_25(double *state, double *unused, double *out_5813414222692730452) {
   out_5813414222692730452[0] = 0;
   out_5813414222692730452[1] = 0;
   out_5813414222692730452[2] = 0;
   out_5813414222692730452[3] = 0;
   out_5813414222692730452[4] = 0;
   out_5813414222692730452[5] = 0;
   out_5813414222692730452[6] = 1;
   out_5813414222692730452[7] = 0;
   out_5813414222692730452[8] = 0;
}
void h_24(double *state, double *unused, double *out_8277837610060872399) {
   out_8277837610060872399[0] = state[4];
   out_8277837610060872399[1] = state[5];
}
void H_24(double *state, double *unused, double *out_5342956740649391728) {
   out_5342956740649391728[0] = 0;
   out_5342956740649391728[1] = 0;
   out_5342956740649391728[2] = 0;
   out_5342956740649391728[3] = 0;
   out_5342956740649391728[4] = 1;
   out_5342956740649391728[5] = 0;
   out_5342956740649391728[6] = 0;
   out_5342956740649391728[7] = 0;
   out_5342956740649391728[8] = 0;
   out_5342956740649391728[9] = 0;
   out_5342956740649391728[10] = 0;
   out_5342956740649391728[11] = 0;
   out_5342956740649391728[12] = 0;
   out_5342956740649391728[13] = 0;
   out_5342956740649391728[14] = 1;
   out_5342956740649391728[15] = 0;
   out_5342956740649391728[16] = 0;
   out_5342956740649391728[17] = 0;
}
void h_30(double *state, double *unused, double *out_5804663442999407757) {
   out_5804663442999407757[0] = state[4];
}
void H_30(double *state, double *unused, double *out_5684075275549490382) {
   out_5684075275549490382[0] = 0;
   out_5684075275549490382[1] = 0;
   out_5684075275549490382[2] = 0;
   out_5684075275549490382[3] = 0;
   out_5684075275549490382[4] = 1;
   out_5684075275549490382[5] = 0;
   out_5684075275549490382[6] = 0;
   out_5684075275549490382[7] = 0;
   out_5684075275549490382[8] = 0;
}
void h_26(double *state, double *unused, double *out_4861153590097745322) {
   out_4861153590097745322[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6470268286803042356) {
   out_6470268286803042356[0] = 0;
   out_6470268286803042356[1] = 0;
   out_6470268286803042356[2] = 0;
   out_6470268286803042356[3] = 0;
   out_6470268286803042356[4] = 0;
   out_6470268286803042356[5] = 0;
   out_6470268286803042356[6] = 0;
   out_6470268286803042356[7] = 1;
   out_6470268286803042356[8] = 0;
}
void h_27(double *state, double *unused, double *out_948509999559217083) {
   out_948509999559217083[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3509311963749065471) {
   out_3509311963749065471[0] = 0;
   out_3509311963749065471[1] = 0;
   out_3509311963749065471[2] = 0;
   out_3509311963749065471[3] = 1;
   out_3509311963749065471[4] = 0;
   out_3509311963749065471[5] = 0;
   out_3509311963749065471[6] = 0;
   out_3509311963749065471[7] = 0;
   out_3509311963749065471[8] = 0;
}
void h_29(double *state, double *unused, double *out_802990175338562112) {
   out_802990175338562112[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6194306619863882566) {
   out_6194306619863882566[0] = 0;
   out_6194306619863882566[1] = 1;
   out_6194306619863882566[2] = 0;
   out_6194306619863882566[3] = 0;
   out_6194306619863882566[4] = 0;
   out_6194306619863882566[5] = 0;
   out_6194306619863882566[6] = 0;
   out_6194306619863882566[7] = 0;
   out_6194306619863882566[8] = 0;
}
void h_28(double *state, double *unused, double *out_4053163268101628562) {
   out_4053163268101628562[0] = state[0];
}
void H_28(double *state, double *unused, double *out_1111907602794351992) {
   out_1111907602794351992[0] = 1;
   out_1111907602794351992[1] = 0;
   out_1111907602794351992[2] = 0;
   out_1111907602794351992[3] = 0;
   out_1111907602794351992[4] = 0;
   out_1111907602794351992[5] = 0;
   out_1111907602794351992[6] = 0;
   out_1111907602794351992[7] = 0;
   out_1111907602794351992[8] = 0;
}
void h_31(double *state, double *unused, double *out_1813081989600609713) {
   out_1813081989600609713[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5844060184569690880) {
   out_5844060184569690880[0] = 0;
   out_5844060184569690880[1] = 0;
   out_5844060184569690880[2] = 0;
   out_5844060184569690880[3] = 0;
   out_5844060184569690880[4] = 0;
   out_5844060184569690880[5] = 0;
   out_5844060184569690880[6] = 0;
   out_5844060184569690880[7] = 0;
   out_5844060184569690880[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7908204057599693162) {
  err_fun(nom_x, delta_x, out_7908204057599693162);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3591353112255890273) {
  inv_err_fun(nom_x, true_x, out_3591353112255890273);
}
void car_H_mod_fun(double *state, double *out_7960573159970110864) {
  H_mod_fun(state, out_7960573159970110864);
}
void car_f_fun(double *state, double dt, double *out_3939178357234727692) {
  f_fun(state,  dt, out_3939178357234727692);
}
void car_F_fun(double *state, double dt, double *out_7601566188878897936) {
  F_fun(state,  dt, out_7601566188878897936);
}
void car_h_25(double *state, double *unused, double *out_1655895321249480568) {
  h_25(state, unused, out_1655895321249480568);
}
void car_H_25(double *state, double *unused, double *out_5813414222692730452) {
  H_25(state, unused, out_5813414222692730452);
}
void car_h_24(double *state, double *unused, double *out_8277837610060872399) {
  h_24(state, unused, out_8277837610060872399);
}
void car_H_24(double *state, double *unused, double *out_5342956740649391728) {
  H_24(state, unused, out_5342956740649391728);
}
void car_h_30(double *state, double *unused, double *out_5804663442999407757) {
  h_30(state, unused, out_5804663442999407757);
}
void car_H_30(double *state, double *unused, double *out_5684075275549490382) {
  H_30(state, unused, out_5684075275549490382);
}
void car_h_26(double *state, double *unused, double *out_4861153590097745322) {
  h_26(state, unused, out_4861153590097745322);
}
void car_H_26(double *state, double *unused, double *out_6470268286803042356) {
  H_26(state, unused, out_6470268286803042356);
}
void car_h_27(double *state, double *unused, double *out_948509999559217083) {
  h_27(state, unused, out_948509999559217083);
}
void car_H_27(double *state, double *unused, double *out_3509311963749065471) {
  H_27(state, unused, out_3509311963749065471);
}
void car_h_29(double *state, double *unused, double *out_802990175338562112) {
  h_29(state, unused, out_802990175338562112);
}
void car_H_29(double *state, double *unused, double *out_6194306619863882566) {
  H_29(state, unused, out_6194306619863882566);
}
void car_h_28(double *state, double *unused, double *out_4053163268101628562) {
  h_28(state, unused, out_4053163268101628562);
}
void car_H_28(double *state, double *unused, double *out_1111907602794351992) {
  H_28(state, unused, out_1111907602794351992);
}
void car_h_31(double *state, double *unused, double *out_1813081989600609713) {
  h_31(state, unused, out_1813081989600609713);
}
void car_H_31(double *state, double *unused, double *out_5844060184569690880) {
  H_31(state, unused, out_5844060184569690880);
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
