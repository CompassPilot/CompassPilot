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
void err_fun(double *nom_x, double *delta_x, double *out_5357651433809492562) {
   out_5357651433809492562[0] = delta_x[0] + nom_x[0];
   out_5357651433809492562[1] = delta_x[1] + nom_x[1];
   out_5357651433809492562[2] = delta_x[2] + nom_x[2];
   out_5357651433809492562[3] = delta_x[3] + nom_x[3];
   out_5357651433809492562[4] = delta_x[4] + nom_x[4];
   out_5357651433809492562[5] = delta_x[5] + nom_x[5];
   out_5357651433809492562[6] = delta_x[6] + nom_x[6];
   out_5357651433809492562[7] = delta_x[7] + nom_x[7];
   out_5357651433809492562[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_5422870240418798336) {
   out_5422870240418798336[0] = -nom_x[0] + true_x[0];
   out_5422870240418798336[1] = -nom_x[1] + true_x[1];
   out_5422870240418798336[2] = -nom_x[2] + true_x[2];
   out_5422870240418798336[3] = -nom_x[3] + true_x[3];
   out_5422870240418798336[4] = -nom_x[4] + true_x[4];
   out_5422870240418798336[5] = -nom_x[5] + true_x[5];
   out_5422870240418798336[6] = -nom_x[6] + true_x[6];
   out_5422870240418798336[7] = -nom_x[7] + true_x[7];
   out_5422870240418798336[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_8069224043506716698) {
   out_8069224043506716698[0] = 1.0;
   out_8069224043506716698[1] = 0.0;
   out_8069224043506716698[2] = 0.0;
   out_8069224043506716698[3] = 0.0;
   out_8069224043506716698[4] = 0.0;
   out_8069224043506716698[5] = 0.0;
   out_8069224043506716698[6] = 0.0;
   out_8069224043506716698[7] = 0.0;
   out_8069224043506716698[8] = 0.0;
   out_8069224043506716698[9] = 0.0;
   out_8069224043506716698[10] = 1.0;
   out_8069224043506716698[11] = 0.0;
   out_8069224043506716698[12] = 0.0;
   out_8069224043506716698[13] = 0.0;
   out_8069224043506716698[14] = 0.0;
   out_8069224043506716698[15] = 0.0;
   out_8069224043506716698[16] = 0.0;
   out_8069224043506716698[17] = 0.0;
   out_8069224043506716698[18] = 0.0;
   out_8069224043506716698[19] = 0.0;
   out_8069224043506716698[20] = 1.0;
   out_8069224043506716698[21] = 0.0;
   out_8069224043506716698[22] = 0.0;
   out_8069224043506716698[23] = 0.0;
   out_8069224043506716698[24] = 0.0;
   out_8069224043506716698[25] = 0.0;
   out_8069224043506716698[26] = 0.0;
   out_8069224043506716698[27] = 0.0;
   out_8069224043506716698[28] = 0.0;
   out_8069224043506716698[29] = 0.0;
   out_8069224043506716698[30] = 1.0;
   out_8069224043506716698[31] = 0.0;
   out_8069224043506716698[32] = 0.0;
   out_8069224043506716698[33] = 0.0;
   out_8069224043506716698[34] = 0.0;
   out_8069224043506716698[35] = 0.0;
   out_8069224043506716698[36] = 0.0;
   out_8069224043506716698[37] = 0.0;
   out_8069224043506716698[38] = 0.0;
   out_8069224043506716698[39] = 0.0;
   out_8069224043506716698[40] = 1.0;
   out_8069224043506716698[41] = 0.0;
   out_8069224043506716698[42] = 0.0;
   out_8069224043506716698[43] = 0.0;
   out_8069224043506716698[44] = 0.0;
   out_8069224043506716698[45] = 0.0;
   out_8069224043506716698[46] = 0.0;
   out_8069224043506716698[47] = 0.0;
   out_8069224043506716698[48] = 0.0;
   out_8069224043506716698[49] = 0.0;
   out_8069224043506716698[50] = 1.0;
   out_8069224043506716698[51] = 0.0;
   out_8069224043506716698[52] = 0.0;
   out_8069224043506716698[53] = 0.0;
   out_8069224043506716698[54] = 0.0;
   out_8069224043506716698[55] = 0.0;
   out_8069224043506716698[56] = 0.0;
   out_8069224043506716698[57] = 0.0;
   out_8069224043506716698[58] = 0.0;
   out_8069224043506716698[59] = 0.0;
   out_8069224043506716698[60] = 1.0;
   out_8069224043506716698[61] = 0.0;
   out_8069224043506716698[62] = 0.0;
   out_8069224043506716698[63] = 0.0;
   out_8069224043506716698[64] = 0.0;
   out_8069224043506716698[65] = 0.0;
   out_8069224043506716698[66] = 0.0;
   out_8069224043506716698[67] = 0.0;
   out_8069224043506716698[68] = 0.0;
   out_8069224043506716698[69] = 0.0;
   out_8069224043506716698[70] = 1.0;
   out_8069224043506716698[71] = 0.0;
   out_8069224043506716698[72] = 0.0;
   out_8069224043506716698[73] = 0.0;
   out_8069224043506716698[74] = 0.0;
   out_8069224043506716698[75] = 0.0;
   out_8069224043506716698[76] = 0.0;
   out_8069224043506716698[77] = 0.0;
   out_8069224043506716698[78] = 0.0;
   out_8069224043506716698[79] = 0.0;
   out_8069224043506716698[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_5560648741818025428) {
   out_5560648741818025428[0] = state[0];
   out_5560648741818025428[1] = state[1];
   out_5560648741818025428[2] = state[2];
   out_5560648741818025428[3] = state[3];
   out_5560648741818025428[4] = state[4];
   out_5560648741818025428[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_5560648741818025428[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_5560648741818025428[7] = state[7];
   out_5560648741818025428[8] = state[8];
}
void F_fun(double *state, double dt, double *out_266263411109112485) {
   out_266263411109112485[0] = 1;
   out_266263411109112485[1] = 0;
   out_266263411109112485[2] = 0;
   out_266263411109112485[3] = 0;
   out_266263411109112485[4] = 0;
   out_266263411109112485[5] = 0;
   out_266263411109112485[6] = 0;
   out_266263411109112485[7] = 0;
   out_266263411109112485[8] = 0;
   out_266263411109112485[9] = 0;
   out_266263411109112485[10] = 1;
   out_266263411109112485[11] = 0;
   out_266263411109112485[12] = 0;
   out_266263411109112485[13] = 0;
   out_266263411109112485[14] = 0;
   out_266263411109112485[15] = 0;
   out_266263411109112485[16] = 0;
   out_266263411109112485[17] = 0;
   out_266263411109112485[18] = 0;
   out_266263411109112485[19] = 0;
   out_266263411109112485[20] = 1;
   out_266263411109112485[21] = 0;
   out_266263411109112485[22] = 0;
   out_266263411109112485[23] = 0;
   out_266263411109112485[24] = 0;
   out_266263411109112485[25] = 0;
   out_266263411109112485[26] = 0;
   out_266263411109112485[27] = 0;
   out_266263411109112485[28] = 0;
   out_266263411109112485[29] = 0;
   out_266263411109112485[30] = 1;
   out_266263411109112485[31] = 0;
   out_266263411109112485[32] = 0;
   out_266263411109112485[33] = 0;
   out_266263411109112485[34] = 0;
   out_266263411109112485[35] = 0;
   out_266263411109112485[36] = 0;
   out_266263411109112485[37] = 0;
   out_266263411109112485[38] = 0;
   out_266263411109112485[39] = 0;
   out_266263411109112485[40] = 1;
   out_266263411109112485[41] = 0;
   out_266263411109112485[42] = 0;
   out_266263411109112485[43] = 0;
   out_266263411109112485[44] = 0;
   out_266263411109112485[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_266263411109112485[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_266263411109112485[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_266263411109112485[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_266263411109112485[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_266263411109112485[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_266263411109112485[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_266263411109112485[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_266263411109112485[53] = -9.8100000000000005*dt;
   out_266263411109112485[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_266263411109112485[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_266263411109112485[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_266263411109112485[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_266263411109112485[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_266263411109112485[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_266263411109112485[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_266263411109112485[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_266263411109112485[62] = 0;
   out_266263411109112485[63] = 0;
   out_266263411109112485[64] = 0;
   out_266263411109112485[65] = 0;
   out_266263411109112485[66] = 0;
   out_266263411109112485[67] = 0;
   out_266263411109112485[68] = 0;
   out_266263411109112485[69] = 0;
   out_266263411109112485[70] = 1;
   out_266263411109112485[71] = 0;
   out_266263411109112485[72] = 0;
   out_266263411109112485[73] = 0;
   out_266263411109112485[74] = 0;
   out_266263411109112485[75] = 0;
   out_266263411109112485[76] = 0;
   out_266263411109112485[77] = 0;
   out_266263411109112485[78] = 0;
   out_266263411109112485[79] = 0;
   out_266263411109112485[80] = 1;
}
void h_25(double *state, double *unused, double *out_4735018420632240230) {
   out_4735018420632240230[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6764884933314745078) {
   out_6764884933314745078[0] = 0;
   out_6764884933314745078[1] = 0;
   out_6764884933314745078[2] = 0;
   out_6764884933314745078[3] = 0;
   out_6764884933314745078[4] = 0;
   out_6764884933314745078[5] = 0;
   out_6764884933314745078[6] = 1;
   out_6764884933314745078[7] = 0;
   out_6764884933314745078[8] = 0;
}
void h_24(double *state, double *unused, double *out_1673618182050648597) {
   out_1673618182050648597[0] = state[4];
   out_1673618182050648597[1] = state[5];
}
void H_24(double *state, double *unused, double *out_3296613781411020105) {
   out_3296613781411020105[0] = 0;
   out_3296613781411020105[1] = 0;
   out_3296613781411020105[2] = 0;
   out_3296613781411020105[3] = 0;
   out_3296613781411020105[4] = 1;
   out_3296613781411020105[5] = 0;
   out_3296613781411020105[6] = 0;
   out_3296613781411020105[7] = 0;
   out_3296613781411020105[8] = 0;
   out_3296613781411020105[9] = 0;
   out_3296613781411020105[10] = 0;
   out_3296613781411020105[11] = 0;
   out_3296613781411020105[12] = 0;
   out_3296613781411020105[13] = 0;
   out_3296613781411020105[14] = 1;
   out_3296613781411020105[15] = 0;
   out_3296613781411020105[16] = 0;
   out_3296613781411020105[17] = 0;
}
void h_30(double *state, double *unused, double *out_1097568892378217880) {
   out_1097568892378217880[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6635545986171505008) {
   out_6635545986171505008[0] = 0;
   out_6635545986171505008[1] = 0;
   out_6635545986171505008[2] = 0;
   out_6635545986171505008[3] = 0;
   out_6635545986171505008[4] = 1;
   out_6635545986171505008[5] = 0;
   out_6635545986171505008[6] = 0;
   out_6635545986171505008[7] = 0;
   out_6635545986171505008[8] = 0;
}
void h_26(double *state, double *unused, double *out_4468532291682291985) {
   out_4468532291682291985[0] = state[7];
}
void H_26(double *state, double *unused, double *out_3023381614440688854) {
   out_3023381614440688854[0] = 0;
   out_3023381614440688854[1] = 0;
   out_3023381614440688854[2] = 0;
   out_3023381614440688854[3] = 0;
   out_3023381614440688854[4] = 0;
   out_3023381614440688854[5] = 0;
   out_3023381614440688854[6] = 0;
   out_3023381614440688854[7] = 1;
   out_3023381614440688854[8] = 0;
}
void h_27(double *state, double *unused, double *out_8381175882220820224) {
   out_8381175882220820224[0] = state[3];
}
void H_27(double *state, double *unused, double *out_4460782674371080097) {
   out_4460782674371080097[0] = 0;
   out_4460782674371080097[1] = 0;
   out_4460782674371080097[2] = 0;
   out_4460782674371080097[3] = 1;
   out_4460782674371080097[4] = 0;
   out_4460782674371080097[5] = 0;
   out_4460782674371080097[6] = 0;
   out_4460782674371080097[7] = 0;
   out_4460782674371080097[8] = 0;
}
void h_29(double *state, double *unused, double *out_7496610409792067026) {
   out_7496610409792067026[0] = state[1];
}
void H_29(double *state, double *unused, double *out_7145777330485897192) {
   out_7145777330485897192[0] = 0;
   out_7145777330485897192[1] = 1;
   out_7145777330485897192[2] = 0;
   out_7145777330485897192[3] = 0;
   out_7145777330485897192[4] = 0;
   out_7145777330485897192[5] = 0;
   out_7145777330485897192[6] = 0;
   out_7145777330485897192[7] = 0;
   out_7145777330485897192[8] = 0;
}
void h_28(double *state, double *unused, double *out_8984491766897297741) {
   out_8984491766897297741[0] = state[0];
}
void H_28(double *state, double *unused, double *out_2063378313416366618) {
   out_2063378313416366618[0] = 1;
   out_2063378313416366618[1] = 0;
   out_2063378313416366618[2] = 0;
   out_2063378313416366618[3] = 0;
   out_2063378313416366618[4] = 0;
   out_2063378313416366618[5] = 0;
   out_2063378313416366618[6] = 0;
   out_2063378313416366618[7] = 0;
   out_2063378313416366618[8] = 0;
}
void h_31(double *state, double *unused, double *out_7123897726601016223) {
   out_7123897726601016223[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6795530895191705506) {
   out_6795530895191705506[0] = 0;
   out_6795530895191705506[1] = 0;
   out_6795530895191705506[2] = 0;
   out_6795530895191705506[3] = 0;
   out_6795530895191705506[4] = 0;
   out_6795530895191705506[5] = 0;
   out_6795530895191705506[6] = 0;
   out_6795530895191705506[7] = 0;
   out_6795530895191705506[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5357651433809492562) {
  err_fun(nom_x, delta_x, out_5357651433809492562);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5422870240418798336) {
  inv_err_fun(nom_x, true_x, out_5422870240418798336);
}
void car_H_mod_fun(double *state, double *out_8069224043506716698) {
  H_mod_fun(state, out_8069224043506716698);
}
void car_f_fun(double *state, double dt, double *out_5560648741818025428) {
  f_fun(state,  dt, out_5560648741818025428);
}
void car_F_fun(double *state, double dt, double *out_266263411109112485) {
  F_fun(state,  dt, out_266263411109112485);
}
void car_h_25(double *state, double *unused, double *out_4735018420632240230) {
  h_25(state, unused, out_4735018420632240230);
}
void car_H_25(double *state, double *unused, double *out_6764884933314745078) {
  H_25(state, unused, out_6764884933314745078);
}
void car_h_24(double *state, double *unused, double *out_1673618182050648597) {
  h_24(state, unused, out_1673618182050648597);
}
void car_H_24(double *state, double *unused, double *out_3296613781411020105) {
  H_24(state, unused, out_3296613781411020105);
}
void car_h_30(double *state, double *unused, double *out_1097568892378217880) {
  h_30(state, unused, out_1097568892378217880);
}
void car_H_30(double *state, double *unused, double *out_6635545986171505008) {
  H_30(state, unused, out_6635545986171505008);
}
void car_h_26(double *state, double *unused, double *out_4468532291682291985) {
  h_26(state, unused, out_4468532291682291985);
}
void car_H_26(double *state, double *unused, double *out_3023381614440688854) {
  H_26(state, unused, out_3023381614440688854);
}
void car_h_27(double *state, double *unused, double *out_8381175882220820224) {
  h_27(state, unused, out_8381175882220820224);
}
void car_H_27(double *state, double *unused, double *out_4460782674371080097) {
  H_27(state, unused, out_4460782674371080097);
}
void car_h_29(double *state, double *unused, double *out_7496610409792067026) {
  h_29(state, unused, out_7496610409792067026);
}
void car_H_29(double *state, double *unused, double *out_7145777330485897192) {
  H_29(state, unused, out_7145777330485897192);
}
void car_h_28(double *state, double *unused, double *out_8984491766897297741) {
  h_28(state, unused, out_8984491766897297741);
}
void car_H_28(double *state, double *unused, double *out_2063378313416366618) {
  H_28(state, unused, out_2063378313416366618);
}
void car_h_31(double *state, double *unused, double *out_7123897726601016223) {
  h_31(state, unused, out_7123897726601016223);
}
void car_H_31(double *state, double *unused, double *out_6795530895191705506) {
  H_31(state, unused, out_6795530895191705506);
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
