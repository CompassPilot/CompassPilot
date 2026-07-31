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
void err_fun(double *nom_x, double *delta_x, double *out_7605142866991004783) {
   out_7605142866991004783[0] = delta_x[0] + nom_x[0];
   out_7605142866991004783[1] = delta_x[1] + nom_x[1];
   out_7605142866991004783[2] = delta_x[2] + nom_x[2];
   out_7605142866991004783[3] = delta_x[3] + nom_x[3];
   out_7605142866991004783[4] = delta_x[4] + nom_x[4];
   out_7605142866991004783[5] = delta_x[5] + nom_x[5];
   out_7605142866991004783[6] = delta_x[6] + nom_x[6];
   out_7605142866991004783[7] = delta_x[7] + nom_x[7];
   out_7605142866991004783[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1440652675888281930) {
   out_1440652675888281930[0] = -nom_x[0] + true_x[0];
   out_1440652675888281930[1] = -nom_x[1] + true_x[1];
   out_1440652675888281930[2] = -nom_x[2] + true_x[2];
   out_1440652675888281930[3] = -nom_x[3] + true_x[3];
   out_1440652675888281930[4] = -nom_x[4] + true_x[4];
   out_1440652675888281930[5] = -nom_x[5] + true_x[5];
   out_1440652675888281930[6] = -nom_x[6] + true_x[6];
   out_1440652675888281930[7] = -nom_x[7] + true_x[7];
   out_1440652675888281930[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_178616141825887590) {
   out_178616141825887590[0] = 1.0;
   out_178616141825887590[1] = 0.0;
   out_178616141825887590[2] = 0.0;
   out_178616141825887590[3] = 0.0;
   out_178616141825887590[4] = 0.0;
   out_178616141825887590[5] = 0.0;
   out_178616141825887590[6] = 0.0;
   out_178616141825887590[7] = 0.0;
   out_178616141825887590[8] = 0.0;
   out_178616141825887590[9] = 0.0;
   out_178616141825887590[10] = 1.0;
   out_178616141825887590[11] = 0.0;
   out_178616141825887590[12] = 0.0;
   out_178616141825887590[13] = 0.0;
   out_178616141825887590[14] = 0.0;
   out_178616141825887590[15] = 0.0;
   out_178616141825887590[16] = 0.0;
   out_178616141825887590[17] = 0.0;
   out_178616141825887590[18] = 0.0;
   out_178616141825887590[19] = 0.0;
   out_178616141825887590[20] = 1.0;
   out_178616141825887590[21] = 0.0;
   out_178616141825887590[22] = 0.0;
   out_178616141825887590[23] = 0.0;
   out_178616141825887590[24] = 0.0;
   out_178616141825887590[25] = 0.0;
   out_178616141825887590[26] = 0.0;
   out_178616141825887590[27] = 0.0;
   out_178616141825887590[28] = 0.0;
   out_178616141825887590[29] = 0.0;
   out_178616141825887590[30] = 1.0;
   out_178616141825887590[31] = 0.0;
   out_178616141825887590[32] = 0.0;
   out_178616141825887590[33] = 0.0;
   out_178616141825887590[34] = 0.0;
   out_178616141825887590[35] = 0.0;
   out_178616141825887590[36] = 0.0;
   out_178616141825887590[37] = 0.0;
   out_178616141825887590[38] = 0.0;
   out_178616141825887590[39] = 0.0;
   out_178616141825887590[40] = 1.0;
   out_178616141825887590[41] = 0.0;
   out_178616141825887590[42] = 0.0;
   out_178616141825887590[43] = 0.0;
   out_178616141825887590[44] = 0.0;
   out_178616141825887590[45] = 0.0;
   out_178616141825887590[46] = 0.0;
   out_178616141825887590[47] = 0.0;
   out_178616141825887590[48] = 0.0;
   out_178616141825887590[49] = 0.0;
   out_178616141825887590[50] = 1.0;
   out_178616141825887590[51] = 0.0;
   out_178616141825887590[52] = 0.0;
   out_178616141825887590[53] = 0.0;
   out_178616141825887590[54] = 0.0;
   out_178616141825887590[55] = 0.0;
   out_178616141825887590[56] = 0.0;
   out_178616141825887590[57] = 0.0;
   out_178616141825887590[58] = 0.0;
   out_178616141825887590[59] = 0.0;
   out_178616141825887590[60] = 1.0;
   out_178616141825887590[61] = 0.0;
   out_178616141825887590[62] = 0.0;
   out_178616141825887590[63] = 0.0;
   out_178616141825887590[64] = 0.0;
   out_178616141825887590[65] = 0.0;
   out_178616141825887590[66] = 0.0;
   out_178616141825887590[67] = 0.0;
   out_178616141825887590[68] = 0.0;
   out_178616141825887590[69] = 0.0;
   out_178616141825887590[70] = 1.0;
   out_178616141825887590[71] = 0.0;
   out_178616141825887590[72] = 0.0;
   out_178616141825887590[73] = 0.0;
   out_178616141825887590[74] = 0.0;
   out_178616141825887590[75] = 0.0;
   out_178616141825887590[76] = 0.0;
   out_178616141825887590[77] = 0.0;
   out_178616141825887590[78] = 0.0;
   out_178616141825887590[79] = 0.0;
   out_178616141825887590[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1588077771682777159) {
   out_1588077771682777159[0] = state[0];
   out_1588077771682777159[1] = state[1];
   out_1588077771682777159[2] = state[2];
   out_1588077771682777159[3] = state[3];
   out_1588077771682777159[4] = state[4];
   out_1588077771682777159[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1588077771682777159[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1588077771682777159[7] = state[7];
   out_1588077771682777159[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2804806635348514472) {
   out_2804806635348514472[0] = 1;
   out_2804806635348514472[1] = 0;
   out_2804806635348514472[2] = 0;
   out_2804806635348514472[3] = 0;
   out_2804806635348514472[4] = 0;
   out_2804806635348514472[5] = 0;
   out_2804806635348514472[6] = 0;
   out_2804806635348514472[7] = 0;
   out_2804806635348514472[8] = 0;
   out_2804806635348514472[9] = 0;
   out_2804806635348514472[10] = 1;
   out_2804806635348514472[11] = 0;
   out_2804806635348514472[12] = 0;
   out_2804806635348514472[13] = 0;
   out_2804806635348514472[14] = 0;
   out_2804806635348514472[15] = 0;
   out_2804806635348514472[16] = 0;
   out_2804806635348514472[17] = 0;
   out_2804806635348514472[18] = 0;
   out_2804806635348514472[19] = 0;
   out_2804806635348514472[20] = 1;
   out_2804806635348514472[21] = 0;
   out_2804806635348514472[22] = 0;
   out_2804806635348514472[23] = 0;
   out_2804806635348514472[24] = 0;
   out_2804806635348514472[25] = 0;
   out_2804806635348514472[26] = 0;
   out_2804806635348514472[27] = 0;
   out_2804806635348514472[28] = 0;
   out_2804806635348514472[29] = 0;
   out_2804806635348514472[30] = 1;
   out_2804806635348514472[31] = 0;
   out_2804806635348514472[32] = 0;
   out_2804806635348514472[33] = 0;
   out_2804806635348514472[34] = 0;
   out_2804806635348514472[35] = 0;
   out_2804806635348514472[36] = 0;
   out_2804806635348514472[37] = 0;
   out_2804806635348514472[38] = 0;
   out_2804806635348514472[39] = 0;
   out_2804806635348514472[40] = 1;
   out_2804806635348514472[41] = 0;
   out_2804806635348514472[42] = 0;
   out_2804806635348514472[43] = 0;
   out_2804806635348514472[44] = 0;
   out_2804806635348514472[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2804806635348514472[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2804806635348514472[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2804806635348514472[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2804806635348514472[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2804806635348514472[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2804806635348514472[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2804806635348514472[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2804806635348514472[53] = -9.8100000000000005*dt;
   out_2804806635348514472[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2804806635348514472[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2804806635348514472[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2804806635348514472[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2804806635348514472[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2804806635348514472[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2804806635348514472[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2804806635348514472[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2804806635348514472[62] = 0;
   out_2804806635348514472[63] = 0;
   out_2804806635348514472[64] = 0;
   out_2804806635348514472[65] = 0;
   out_2804806635348514472[66] = 0;
   out_2804806635348514472[67] = 0;
   out_2804806635348514472[68] = 0;
   out_2804806635348514472[69] = 0;
   out_2804806635348514472[70] = 1;
   out_2804806635348514472[71] = 0;
   out_2804806635348514472[72] = 0;
   out_2804806635348514472[73] = 0;
   out_2804806635348514472[74] = 0;
   out_2804806635348514472[75] = 0;
   out_2804806635348514472[76] = 0;
   out_2804806635348514472[77] = 0;
   out_2804806635348514472[78] = 0;
   out_2804806635348514472[79] = 0;
   out_2804806635348514472[80] = 1;
}
void h_25(double *state, double *unused, double *out_7143928669701088849) {
   out_7143928669701088849[0] = state[6];
}
void H_25(double *state, double *unused, double *out_9074939705971426789) {
   out_9074939705971426789[0] = 0;
   out_9074939705971426789[1] = 0;
   out_9074939705971426789[2] = 0;
   out_9074939705971426789[3] = 0;
   out_9074939705971426789[4] = 0;
   out_9074939705971426789[5] = 0;
   out_9074939705971426789[6] = 1;
   out_9074939705971426789[7] = 0;
   out_9074939705971426789[8] = 0;
}
void h_24(double *state, double *unused, double *out_5462970336184341809) {
   out_5462970336184341809[0] = state[4];
   out_5462970336184341809[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6902290106965927223) {
   out_6902290106965927223[0] = 0;
   out_6902290106965927223[1] = 0;
   out_6902290106965927223[2] = 0;
   out_6902290106965927223[3] = 0;
   out_6902290106965927223[4] = 1;
   out_6902290106965927223[5] = 0;
   out_6902290106965927223[6] = 0;
   out_6902290106965927223[7] = 0;
   out_6902290106965927223[8] = 0;
   out_6902290106965927223[9] = 0;
   out_6902290106965927223[10] = 0;
   out_6902290106965927223[11] = 0;
   out_6902290106965927223[12] = 0;
   out_6902290106965927223[13] = 0;
   out_6902290106965927223[14] = 1;
   out_6902290106965927223[15] = 0;
   out_6902290106965927223[16] = 0;
   out_6902290106965927223[17] = 0;
}
void h_30(double *state, double *unused, double *out_6986742001349959704) {
   out_6986742001349959704[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4547243375843818591) {
   out_4547243375843818591[0] = 0;
   out_4547243375843818591[1] = 0;
   out_4547243375843818591[2] = 0;
   out_4547243375843818591[3] = 0;
   out_4547243375843818591[4] = 1;
   out_4547243375843818591[5] = 0;
   out_4547243375843818591[6] = 0;
   out_4547243375843818591[7] = 0;
   out_4547243375843818591[8] = 0;
}
void h_26(double *state, double *unused, double *out_2478032900352751147) {
   out_2478032900352751147[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5333436387097370565) {
   out_5333436387097370565[0] = 0;
   out_5333436387097370565[1] = 0;
   out_5333436387097370565[2] = 0;
   out_5333436387097370565[3] = 0;
   out_5333436387097370565[4] = 0;
   out_5333436387097370565[5] = 0;
   out_5333436387097370565[6] = 0;
   out_5333436387097370565[7] = 1;
   out_5333436387097370565[8] = 0;
}
void h_27(double *state, double *unused, double *out_7747244554377566366) {
   out_7747244554377566366[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6770837447027761808) {
   out_6770837447027761808[0] = 0;
   out_6770837447027761808[1] = 0;
   out_6770837447027761808[2] = 0;
   out_6770837447027761808[3] = 1;
   out_6770837447027761808[4] = 0;
   out_6770837447027761808[5] = 0;
   out_6770837447027761808[6] = 0;
   out_6770837447027761808[7] = 0;
   out_6770837447027761808[8] = 0;
}
void h_29(double *state, double *unused, double *out_16020702443106075) {
   out_16020702443106075[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5057474720158210775) {
   out_5057474720158210775[0] = 0;
   out_5057474720158210775[1] = 1;
   out_5057474720158210775[2] = 0;
   out_5057474720158210775[3] = 0;
   out_5057474720158210775[4] = 0;
   out_5057474720158210775[5] = 0;
   out_5057474720158210775[6] = 0;
   out_5057474720158210775[7] = 0;
   out_5057474720158210775[8] = 0;
}
void h_28(double *state, double *unused, double *out_1377941413084076291) {
   out_1377941413084076291[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7021104991723537026) {
   out_7021104991723537026[0] = 1;
   out_7021104991723537026[1] = 0;
   out_7021104991723537026[2] = 0;
   out_7021104991723537026[3] = 0;
   out_7021104991723537026[4] = 0;
   out_7021104991723537026[5] = 0;
   out_7021104991723537026[6] = 0;
   out_7021104991723537026[7] = 0;
   out_7021104991723537026[8] = 0;
}
void h_31(double *state, double *unused, double *out_7204512105729090903) {
   out_7204512105729090903[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9105585667848387217) {
   out_9105585667848387217[0] = 0;
   out_9105585667848387217[1] = 0;
   out_9105585667848387217[2] = 0;
   out_9105585667848387217[3] = 0;
   out_9105585667848387217[4] = 0;
   out_9105585667848387217[5] = 0;
   out_9105585667848387217[6] = 0;
   out_9105585667848387217[7] = 0;
   out_9105585667848387217[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_7605142866991004783) {
  err_fun(nom_x, delta_x, out_7605142866991004783);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1440652675888281930) {
  inv_err_fun(nom_x, true_x, out_1440652675888281930);
}
void car_H_mod_fun(double *state, double *out_178616141825887590) {
  H_mod_fun(state, out_178616141825887590);
}
void car_f_fun(double *state, double dt, double *out_1588077771682777159) {
  f_fun(state,  dt, out_1588077771682777159);
}
void car_F_fun(double *state, double dt, double *out_2804806635348514472) {
  F_fun(state,  dt, out_2804806635348514472);
}
void car_h_25(double *state, double *unused, double *out_7143928669701088849) {
  h_25(state, unused, out_7143928669701088849);
}
void car_H_25(double *state, double *unused, double *out_9074939705971426789) {
  H_25(state, unused, out_9074939705971426789);
}
void car_h_24(double *state, double *unused, double *out_5462970336184341809) {
  h_24(state, unused, out_5462970336184341809);
}
void car_H_24(double *state, double *unused, double *out_6902290106965927223) {
  H_24(state, unused, out_6902290106965927223);
}
void car_h_30(double *state, double *unused, double *out_6986742001349959704) {
  h_30(state, unused, out_6986742001349959704);
}
void car_H_30(double *state, double *unused, double *out_4547243375843818591) {
  H_30(state, unused, out_4547243375843818591);
}
void car_h_26(double *state, double *unused, double *out_2478032900352751147) {
  h_26(state, unused, out_2478032900352751147);
}
void car_H_26(double *state, double *unused, double *out_5333436387097370565) {
  H_26(state, unused, out_5333436387097370565);
}
void car_h_27(double *state, double *unused, double *out_7747244554377566366) {
  h_27(state, unused, out_7747244554377566366);
}
void car_H_27(double *state, double *unused, double *out_6770837447027761808) {
  H_27(state, unused, out_6770837447027761808);
}
void car_h_29(double *state, double *unused, double *out_16020702443106075) {
  h_29(state, unused, out_16020702443106075);
}
void car_H_29(double *state, double *unused, double *out_5057474720158210775) {
  H_29(state, unused, out_5057474720158210775);
}
void car_h_28(double *state, double *unused, double *out_1377941413084076291) {
  h_28(state, unused, out_1377941413084076291);
}
void car_H_28(double *state, double *unused, double *out_7021104991723537026) {
  H_28(state, unused, out_7021104991723537026);
}
void car_h_31(double *state, double *unused, double *out_7204512105729090903) {
  h_31(state, unused, out_7204512105729090903);
}
void car_H_31(double *state, double *unused, double *out_9105585667848387217) {
  H_31(state, unused, out_9105585667848387217);
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
