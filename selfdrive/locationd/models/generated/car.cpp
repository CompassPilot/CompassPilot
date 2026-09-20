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
void err_fun(double *nom_x, double *delta_x, double *out_8412839542249066946) {
   out_8412839542249066946[0] = delta_x[0] + nom_x[0];
   out_8412839542249066946[1] = delta_x[1] + nom_x[1];
   out_8412839542249066946[2] = delta_x[2] + nom_x[2];
   out_8412839542249066946[3] = delta_x[3] + nom_x[3];
   out_8412839542249066946[4] = delta_x[4] + nom_x[4];
   out_8412839542249066946[5] = delta_x[5] + nom_x[5];
   out_8412839542249066946[6] = delta_x[6] + nom_x[6];
   out_8412839542249066946[7] = delta_x[7] + nom_x[7];
   out_8412839542249066946[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1100572460195897381) {
   out_1100572460195897381[0] = -nom_x[0] + true_x[0];
   out_1100572460195897381[1] = -nom_x[1] + true_x[1];
   out_1100572460195897381[2] = -nom_x[2] + true_x[2];
   out_1100572460195897381[3] = -nom_x[3] + true_x[3];
   out_1100572460195897381[4] = -nom_x[4] + true_x[4];
   out_1100572460195897381[5] = -nom_x[5] + true_x[5];
   out_1100572460195897381[6] = -nom_x[6] + true_x[6];
   out_1100572460195897381[7] = -nom_x[7] + true_x[7];
   out_1100572460195897381[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_1136722566492535070) {
   out_1136722566492535070[0] = 1.0;
   out_1136722566492535070[1] = 0.0;
   out_1136722566492535070[2] = 0.0;
   out_1136722566492535070[3] = 0.0;
   out_1136722566492535070[4] = 0.0;
   out_1136722566492535070[5] = 0.0;
   out_1136722566492535070[6] = 0.0;
   out_1136722566492535070[7] = 0.0;
   out_1136722566492535070[8] = 0.0;
   out_1136722566492535070[9] = 0.0;
   out_1136722566492535070[10] = 1.0;
   out_1136722566492535070[11] = 0.0;
   out_1136722566492535070[12] = 0.0;
   out_1136722566492535070[13] = 0.0;
   out_1136722566492535070[14] = 0.0;
   out_1136722566492535070[15] = 0.0;
   out_1136722566492535070[16] = 0.0;
   out_1136722566492535070[17] = 0.0;
   out_1136722566492535070[18] = 0.0;
   out_1136722566492535070[19] = 0.0;
   out_1136722566492535070[20] = 1.0;
   out_1136722566492535070[21] = 0.0;
   out_1136722566492535070[22] = 0.0;
   out_1136722566492535070[23] = 0.0;
   out_1136722566492535070[24] = 0.0;
   out_1136722566492535070[25] = 0.0;
   out_1136722566492535070[26] = 0.0;
   out_1136722566492535070[27] = 0.0;
   out_1136722566492535070[28] = 0.0;
   out_1136722566492535070[29] = 0.0;
   out_1136722566492535070[30] = 1.0;
   out_1136722566492535070[31] = 0.0;
   out_1136722566492535070[32] = 0.0;
   out_1136722566492535070[33] = 0.0;
   out_1136722566492535070[34] = 0.0;
   out_1136722566492535070[35] = 0.0;
   out_1136722566492535070[36] = 0.0;
   out_1136722566492535070[37] = 0.0;
   out_1136722566492535070[38] = 0.0;
   out_1136722566492535070[39] = 0.0;
   out_1136722566492535070[40] = 1.0;
   out_1136722566492535070[41] = 0.0;
   out_1136722566492535070[42] = 0.0;
   out_1136722566492535070[43] = 0.0;
   out_1136722566492535070[44] = 0.0;
   out_1136722566492535070[45] = 0.0;
   out_1136722566492535070[46] = 0.0;
   out_1136722566492535070[47] = 0.0;
   out_1136722566492535070[48] = 0.0;
   out_1136722566492535070[49] = 0.0;
   out_1136722566492535070[50] = 1.0;
   out_1136722566492535070[51] = 0.0;
   out_1136722566492535070[52] = 0.0;
   out_1136722566492535070[53] = 0.0;
   out_1136722566492535070[54] = 0.0;
   out_1136722566492535070[55] = 0.0;
   out_1136722566492535070[56] = 0.0;
   out_1136722566492535070[57] = 0.0;
   out_1136722566492535070[58] = 0.0;
   out_1136722566492535070[59] = 0.0;
   out_1136722566492535070[60] = 1.0;
   out_1136722566492535070[61] = 0.0;
   out_1136722566492535070[62] = 0.0;
   out_1136722566492535070[63] = 0.0;
   out_1136722566492535070[64] = 0.0;
   out_1136722566492535070[65] = 0.0;
   out_1136722566492535070[66] = 0.0;
   out_1136722566492535070[67] = 0.0;
   out_1136722566492535070[68] = 0.0;
   out_1136722566492535070[69] = 0.0;
   out_1136722566492535070[70] = 1.0;
   out_1136722566492535070[71] = 0.0;
   out_1136722566492535070[72] = 0.0;
   out_1136722566492535070[73] = 0.0;
   out_1136722566492535070[74] = 0.0;
   out_1136722566492535070[75] = 0.0;
   out_1136722566492535070[76] = 0.0;
   out_1136722566492535070[77] = 0.0;
   out_1136722566492535070[78] = 0.0;
   out_1136722566492535070[79] = 0.0;
   out_1136722566492535070[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_211467565025137174) {
   out_211467565025137174[0] = state[0];
   out_211467565025137174[1] = state[1];
   out_211467565025137174[2] = state[2];
   out_211467565025137174[3] = state[3];
   out_211467565025137174[4] = state[4];
   out_211467565025137174[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_211467565025137174[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_211467565025137174[7] = state[7];
   out_211467565025137174[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4884760099425242162) {
   out_4884760099425242162[0] = 1;
   out_4884760099425242162[1] = 0;
   out_4884760099425242162[2] = 0;
   out_4884760099425242162[3] = 0;
   out_4884760099425242162[4] = 0;
   out_4884760099425242162[5] = 0;
   out_4884760099425242162[6] = 0;
   out_4884760099425242162[7] = 0;
   out_4884760099425242162[8] = 0;
   out_4884760099425242162[9] = 0;
   out_4884760099425242162[10] = 1;
   out_4884760099425242162[11] = 0;
   out_4884760099425242162[12] = 0;
   out_4884760099425242162[13] = 0;
   out_4884760099425242162[14] = 0;
   out_4884760099425242162[15] = 0;
   out_4884760099425242162[16] = 0;
   out_4884760099425242162[17] = 0;
   out_4884760099425242162[18] = 0;
   out_4884760099425242162[19] = 0;
   out_4884760099425242162[20] = 1;
   out_4884760099425242162[21] = 0;
   out_4884760099425242162[22] = 0;
   out_4884760099425242162[23] = 0;
   out_4884760099425242162[24] = 0;
   out_4884760099425242162[25] = 0;
   out_4884760099425242162[26] = 0;
   out_4884760099425242162[27] = 0;
   out_4884760099425242162[28] = 0;
   out_4884760099425242162[29] = 0;
   out_4884760099425242162[30] = 1;
   out_4884760099425242162[31] = 0;
   out_4884760099425242162[32] = 0;
   out_4884760099425242162[33] = 0;
   out_4884760099425242162[34] = 0;
   out_4884760099425242162[35] = 0;
   out_4884760099425242162[36] = 0;
   out_4884760099425242162[37] = 0;
   out_4884760099425242162[38] = 0;
   out_4884760099425242162[39] = 0;
   out_4884760099425242162[40] = 1;
   out_4884760099425242162[41] = 0;
   out_4884760099425242162[42] = 0;
   out_4884760099425242162[43] = 0;
   out_4884760099425242162[44] = 0;
   out_4884760099425242162[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4884760099425242162[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4884760099425242162[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4884760099425242162[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4884760099425242162[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4884760099425242162[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4884760099425242162[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4884760099425242162[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4884760099425242162[53] = -9.8100000000000005*dt;
   out_4884760099425242162[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4884760099425242162[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4884760099425242162[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4884760099425242162[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4884760099425242162[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4884760099425242162[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4884760099425242162[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4884760099425242162[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4884760099425242162[62] = 0;
   out_4884760099425242162[63] = 0;
   out_4884760099425242162[64] = 0;
   out_4884760099425242162[65] = 0;
   out_4884760099425242162[66] = 0;
   out_4884760099425242162[67] = 0;
   out_4884760099425242162[68] = 0;
   out_4884760099425242162[69] = 0;
   out_4884760099425242162[70] = 1;
   out_4884760099425242162[71] = 0;
   out_4884760099425242162[72] = 0;
   out_4884760099425242162[73] = 0;
   out_4884760099425242162[74] = 0;
   out_4884760099425242162[75] = 0;
   out_4884760099425242162[76] = 0;
   out_4884760099425242162[77] = 0;
   out_4884760099425242162[78] = 0;
   out_4884760099425242162[79] = 0;
   out_4884760099425242162[80] = 1;
}
void h_25(double *state, double *unused, double *out_939942926882322239) {
   out_939942926882322239[0] = state[6];
}
void H_25(double *state, double *unused, double *out_1499834358522891124) {
   out_1499834358522891124[0] = 0;
   out_1499834358522891124[1] = 0;
   out_1499834358522891124[2] = 0;
   out_1499834358522891124[3] = 0;
   out_1499834358522891124[4] = 0;
   out_1499834358522891124[5] = 0;
   out_1499834358522891124[6] = 1;
   out_1499834358522891124[7] = 0;
   out_1499834358522891124[8] = 0;
}
void h_24(double *state, double *unused, double *out_2762672389005360303) {
   out_2762672389005360303[0] = state[4];
   out_2762672389005360303[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4311551272499885841) {
   out_4311551272499885841[0] = 0;
   out_4311551272499885841[1] = 0;
   out_4311551272499885841[2] = 0;
   out_4311551272499885841[3] = 0;
   out_4311551272499885841[4] = 1;
   out_4311551272499885841[5] = 0;
   out_4311551272499885841[6] = 0;
   out_4311551272499885841[7] = 0;
   out_4311551272499885841[8] = 0;
   out_4311551272499885841[9] = 0;
   out_4311551272499885841[10] = 0;
   out_4311551272499885841[11] = 0;
   out_4311551272499885841[12] = 0;
   out_4311551272499885841[13] = 0;
   out_4311551272499885841[14] = 1;
   out_4311551272499885841[15] = 0;
   out_4311551272499885841[16] = 0;
   out_4311551272499885841[17] = 0;
}
void h_30(double *state, double *unused, double *out_794423102661667268) {
   out_794423102661667268[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1629173305666131194) {
   out_1629173305666131194[0] = 0;
   out_1629173305666131194[1] = 0;
   out_1629173305666131194[2] = 0;
   out_1629173305666131194[3] = 0;
   out_1629173305666131194[4] = 1;
   out_1629173305666131194[5] = 0;
   out_1629173305666131194[6] = 0;
   out_1629173305666131194[7] = 0;
   out_1629173305666131194[8] = 0;
}
void h_26(double *state, double *unused, double *out_6543034352156531438) {
   out_6543034352156531438[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5241337677396947348) {
   out_5241337677396947348[0] = 0;
   out_5241337677396947348[1] = 0;
   out_5241337677396947348[2] = 0;
   out_5241337677396947348[3] = 0;
   out_5241337677396947348[4] = 0;
   out_5241337677396947348[5] = 0;
   out_5241337677396947348[6] = 0;
   out_5241337677396947348[7] = 1;
   out_5241337677396947348[8] = 0;
}
void h_27(double *state, double *unused, double *out_4285964288953002708) {
   out_4285964288953002708[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3803936617466556105) {
   out_3803936617466556105[0] = 0;
   out_3803936617466556105[1] = 0;
   out_3803936617466556105[2] = 0;
   out_3803936617466556105[3] = 1;
   out_3803936617466556105[4] = 0;
   out_3803936617466556105[5] = 0;
   out_3803936617466556105[6] = 0;
   out_3803936617466556105[7] = 0;
   out_3803936617466556105[8] = 0;
}
void h_29(double *state, double *unused, double *out_7797185806454733047) {
   out_7797185806454733047[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5517299344336107138) {
   out_5517299344336107138[0] = 0;
   out_5517299344336107138[1] = 1;
   out_5517299344336107138[2] = 0;
   out_5517299344336107138[3] = 0;
   out_5517299344336107138[4] = 0;
   out_5517299344336107138[5] = 0;
   out_5517299344336107138[6] = 0;
   out_5517299344336107138[7] = 0;
   out_5517299344336107138[8] = 0;
}
void h_28(double *state, double *unused, double *out_9159106517095703263) {
   out_9159106517095703263[0] = state[0];
}
void H_28(double *state, double *unused, double *out_3553669072770780887) {
   out_3553669072770780887[0] = 1;
   out_3553669072770780887[1] = 0;
   out_3553669072770780887[2] = 0;
   out_3553669072770780887[3] = 0;
   out_3553669072770780887[4] = 0;
   out_3553669072770780887[5] = 0;
   out_3553669072770780887[6] = 0;
   out_3553669072770780887[7] = 0;
   out_3553669072770780887[8] = 0;
}
void h_31(double *state, double *unused, double *out_6823322329938350202) {
   out_6823322329938350202[0] = state[8];
}
void H_31(double *state, double *unused, double *out_1469188396645930696) {
   out_1469188396645930696[0] = 0;
   out_1469188396645930696[1] = 0;
   out_1469188396645930696[2] = 0;
   out_1469188396645930696[3] = 0;
   out_1469188396645930696[4] = 0;
   out_1469188396645930696[5] = 0;
   out_1469188396645930696[6] = 0;
   out_1469188396645930696[7] = 0;
   out_1469188396645930696[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_8412839542249066946) {
  err_fun(nom_x, delta_x, out_8412839542249066946);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1100572460195897381) {
  inv_err_fun(nom_x, true_x, out_1100572460195897381);
}
void car_H_mod_fun(double *state, double *out_1136722566492535070) {
  H_mod_fun(state, out_1136722566492535070);
}
void car_f_fun(double *state, double dt, double *out_211467565025137174) {
  f_fun(state,  dt, out_211467565025137174);
}
void car_F_fun(double *state, double dt, double *out_4884760099425242162) {
  F_fun(state,  dt, out_4884760099425242162);
}
void car_h_25(double *state, double *unused, double *out_939942926882322239) {
  h_25(state, unused, out_939942926882322239);
}
void car_H_25(double *state, double *unused, double *out_1499834358522891124) {
  H_25(state, unused, out_1499834358522891124);
}
void car_h_24(double *state, double *unused, double *out_2762672389005360303) {
  h_24(state, unused, out_2762672389005360303);
}
void car_H_24(double *state, double *unused, double *out_4311551272499885841) {
  H_24(state, unused, out_4311551272499885841);
}
void car_h_30(double *state, double *unused, double *out_794423102661667268) {
  h_30(state, unused, out_794423102661667268);
}
void car_H_30(double *state, double *unused, double *out_1629173305666131194) {
  H_30(state, unused, out_1629173305666131194);
}
void car_h_26(double *state, double *unused, double *out_6543034352156531438) {
  h_26(state, unused, out_6543034352156531438);
}
void car_H_26(double *state, double *unused, double *out_5241337677396947348) {
  H_26(state, unused, out_5241337677396947348);
}
void car_h_27(double *state, double *unused, double *out_4285964288953002708) {
  h_27(state, unused, out_4285964288953002708);
}
void car_H_27(double *state, double *unused, double *out_3803936617466556105) {
  H_27(state, unused, out_3803936617466556105);
}
void car_h_29(double *state, double *unused, double *out_7797185806454733047) {
  h_29(state, unused, out_7797185806454733047);
}
void car_H_29(double *state, double *unused, double *out_5517299344336107138) {
  H_29(state, unused, out_5517299344336107138);
}
void car_h_28(double *state, double *unused, double *out_9159106517095703263) {
  h_28(state, unused, out_9159106517095703263);
}
void car_H_28(double *state, double *unused, double *out_3553669072770780887) {
  H_28(state, unused, out_3553669072770780887);
}
void car_h_31(double *state, double *unused, double *out_6823322329938350202) {
  h_31(state, unused, out_6823322329938350202);
}
void car_H_31(double *state, double *unused, double *out_1469188396645930696) {
  H_31(state, unused, out_1469188396645930696);
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
