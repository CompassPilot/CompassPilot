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
void err_fun(double *nom_x, double *delta_x, double *out_3085762064690293463) {
   out_3085762064690293463[0] = delta_x[0] + nom_x[0];
   out_3085762064690293463[1] = delta_x[1] + nom_x[1];
   out_3085762064690293463[2] = delta_x[2] + nom_x[2];
   out_3085762064690293463[3] = delta_x[3] + nom_x[3];
   out_3085762064690293463[4] = delta_x[4] + nom_x[4];
   out_3085762064690293463[5] = delta_x[5] + nom_x[5];
   out_3085762064690293463[6] = delta_x[6] + nom_x[6];
   out_3085762064690293463[7] = delta_x[7] + nom_x[7];
   out_3085762064690293463[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_8869691075625684096) {
   out_8869691075625684096[0] = -nom_x[0] + true_x[0];
   out_8869691075625684096[1] = -nom_x[1] + true_x[1];
   out_8869691075625684096[2] = -nom_x[2] + true_x[2];
   out_8869691075625684096[3] = -nom_x[3] + true_x[3];
   out_8869691075625684096[4] = -nom_x[4] + true_x[4];
   out_8869691075625684096[5] = -nom_x[5] + true_x[5];
   out_8869691075625684096[6] = -nom_x[6] + true_x[6];
   out_8869691075625684096[7] = -nom_x[7] + true_x[7];
   out_8869691075625684096[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_4304656995766687822) {
   out_4304656995766687822[0] = 1.0;
   out_4304656995766687822[1] = 0.0;
   out_4304656995766687822[2] = 0.0;
   out_4304656995766687822[3] = 0.0;
   out_4304656995766687822[4] = 0.0;
   out_4304656995766687822[5] = 0.0;
   out_4304656995766687822[6] = 0.0;
   out_4304656995766687822[7] = 0.0;
   out_4304656995766687822[8] = 0.0;
   out_4304656995766687822[9] = 0.0;
   out_4304656995766687822[10] = 1.0;
   out_4304656995766687822[11] = 0.0;
   out_4304656995766687822[12] = 0.0;
   out_4304656995766687822[13] = 0.0;
   out_4304656995766687822[14] = 0.0;
   out_4304656995766687822[15] = 0.0;
   out_4304656995766687822[16] = 0.0;
   out_4304656995766687822[17] = 0.0;
   out_4304656995766687822[18] = 0.0;
   out_4304656995766687822[19] = 0.0;
   out_4304656995766687822[20] = 1.0;
   out_4304656995766687822[21] = 0.0;
   out_4304656995766687822[22] = 0.0;
   out_4304656995766687822[23] = 0.0;
   out_4304656995766687822[24] = 0.0;
   out_4304656995766687822[25] = 0.0;
   out_4304656995766687822[26] = 0.0;
   out_4304656995766687822[27] = 0.0;
   out_4304656995766687822[28] = 0.0;
   out_4304656995766687822[29] = 0.0;
   out_4304656995766687822[30] = 1.0;
   out_4304656995766687822[31] = 0.0;
   out_4304656995766687822[32] = 0.0;
   out_4304656995766687822[33] = 0.0;
   out_4304656995766687822[34] = 0.0;
   out_4304656995766687822[35] = 0.0;
   out_4304656995766687822[36] = 0.0;
   out_4304656995766687822[37] = 0.0;
   out_4304656995766687822[38] = 0.0;
   out_4304656995766687822[39] = 0.0;
   out_4304656995766687822[40] = 1.0;
   out_4304656995766687822[41] = 0.0;
   out_4304656995766687822[42] = 0.0;
   out_4304656995766687822[43] = 0.0;
   out_4304656995766687822[44] = 0.0;
   out_4304656995766687822[45] = 0.0;
   out_4304656995766687822[46] = 0.0;
   out_4304656995766687822[47] = 0.0;
   out_4304656995766687822[48] = 0.0;
   out_4304656995766687822[49] = 0.0;
   out_4304656995766687822[50] = 1.0;
   out_4304656995766687822[51] = 0.0;
   out_4304656995766687822[52] = 0.0;
   out_4304656995766687822[53] = 0.0;
   out_4304656995766687822[54] = 0.0;
   out_4304656995766687822[55] = 0.0;
   out_4304656995766687822[56] = 0.0;
   out_4304656995766687822[57] = 0.0;
   out_4304656995766687822[58] = 0.0;
   out_4304656995766687822[59] = 0.0;
   out_4304656995766687822[60] = 1.0;
   out_4304656995766687822[61] = 0.0;
   out_4304656995766687822[62] = 0.0;
   out_4304656995766687822[63] = 0.0;
   out_4304656995766687822[64] = 0.0;
   out_4304656995766687822[65] = 0.0;
   out_4304656995766687822[66] = 0.0;
   out_4304656995766687822[67] = 0.0;
   out_4304656995766687822[68] = 0.0;
   out_4304656995766687822[69] = 0.0;
   out_4304656995766687822[70] = 1.0;
   out_4304656995766687822[71] = 0.0;
   out_4304656995766687822[72] = 0.0;
   out_4304656995766687822[73] = 0.0;
   out_4304656995766687822[74] = 0.0;
   out_4304656995766687822[75] = 0.0;
   out_4304656995766687822[76] = 0.0;
   out_4304656995766687822[77] = 0.0;
   out_4304656995766687822[78] = 0.0;
   out_4304656995766687822[79] = 0.0;
   out_4304656995766687822[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_4290705075249888359) {
   out_4290705075249888359[0] = state[0];
   out_4290705075249888359[1] = state[1];
   out_4290705075249888359[2] = state[2];
   out_4290705075249888359[3] = state[3];
   out_4290705075249888359[4] = state[4];
   out_4290705075249888359[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_4290705075249888359[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_4290705075249888359[7] = state[7];
   out_4290705075249888359[8] = state[8];
}
void F_fun(double *state, double dt, double *out_2044662117251408537) {
   out_2044662117251408537[0] = 1;
   out_2044662117251408537[1] = 0;
   out_2044662117251408537[2] = 0;
   out_2044662117251408537[3] = 0;
   out_2044662117251408537[4] = 0;
   out_2044662117251408537[5] = 0;
   out_2044662117251408537[6] = 0;
   out_2044662117251408537[7] = 0;
   out_2044662117251408537[8] = 0;
   out_2044662117251408537[9] = 0;
   out_2044662117251408537[10] = 1;
   out_2044662117251408537[11] = 0;
   out_2044662117251408537[12] = 0;
   out_2044662117251408537[13] = 0;
   out_2044662117251408537[14] = 0;
   out_2044662117251408537[15] = 0;
   out_2044662117251408537[16] = 0;
   out_2044662117251408537[17] = 0;
   out_2044662117251408537[18] = 0;
   out_2044662117251408537[19] = 0;
   out_2044662117251408537[20] = 1;
   out_2044662117251408537[21] = 0;
   out_2044662117251408537[22] = 0;
   out_2044662117251408537[23] = 0;
   out_2044662117251408537[24] = 0;
   out_2044662117251408537[25] = 0;
   out_2044662117251408537[26] = 0;
   out_2044662117251408537[27] = 0;
   out_2044662117251408537[28] = 0;
   out_2044662117251408537[29] = 0;
   out_2044662117251408537[30] = 1;
   out_2044662117251408537[31] = 0;
   out_2044662117251408537[32] = 0;
   out_2044662117251408537[33] = 0;
   out_2044662117251408537[34] = 0;
   out_2044662117251408537[35] = 0;
   out_2044662117251408537[36] = 0;
   out_2044662117251408537[37] = 0;
   out_2044662117251408537[38] = 0;
   out_2044662117251408537[39] = 0;
   out_2044662117251408537[40] = 1;
   out_2044662117251408537[41] = 0;
   out_2044662117251408537[42] = 0;
   out_2044662117251408537[43] = 0;
   out_2044662117251408537[44] = 0;
   out_2044662117251408537[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_2044662117251408537[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_2044662117251408537[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2044662117251408537[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_2044662117251408537[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_2044662117251408537[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_2044662117251408537[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_2044662117251408537[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_2044662117251408537[53] = -9.8100000000000005*dt;
   out_2044662117251408537[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_2044662117251408537[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_2044662117251408537[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2044662117251408537[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2044662117251408537[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_2044662117251408537[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_2044662117251408537[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_2044662117251408537[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_2044662117251408537[62] = 0;
   out_2044662117251408537[63] = 0;
   out_2044662117251408537[64] = 0;
   out_2044662117251408537[65] = 0;
   out_2044662117251408537[66] = 0;
   out_2044662117251408537[67] = 0;
   out_2044662117251408537[68] = 0;
   out_2044662117251408537[69] = 0;
   out_2044662117251408537[70] = 1;
   out_2044662117251408537[71] = 0;
   out_2044662117251408537[72] = 0;
   out_2044662117251408537[73] = 0;
   out_2044662117251408537[74] = 0;
   out_2044662117251408537[75] = 0;
   out_2044662117251408537[76] = 0;
   out_2044662117251408537[77] = 0;
   out_2044662117251408537[78] = 0;
   out_2044662117251408537[79] = 0;
   out_2044662117251408537[80] = 1;
}
void h_25(double *state, double *unused, double *out_5185932570181153644) {
   out_5185932570181153644[0] = state[6];
}
void H_25(double *state, double *unused, double *out_3000317885574716202) {
   out_3000317885574716202[0] = 0;
   out_3000317885574716202[1] = 0;
   out_3000317885574716202[2] = 0;
   out_3000317885574716202[3] = 0;
   out_3000317885574716202[4] = 0;
   out_3000317885574716202[5] = 0;
   out_3000317885574716202[6] = 1;
   out_3000317885574716202[7] = 0;
   out_3000317885574716202[8] = 0;
}
void h_24(double *state, double *unused, double *out_2382549089680422133) {
   out_2382549089680422133[0] = state[4];
   out_2382549089680422133[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7061180829151048981) {
   out_7061180829151048981[0] = 0;
   out_7061180829151048981[1] = 0;
   out_7061180829151048981[2] = 0;
   out_7061180829151048981[3] = 0;
   out_7061180829151048981[4] = 1;
   out_7061180829151048981[5] = 0;
   out_7061180829151048981[6] = 0;
   out_7061180829151048981[7] = 0;
   out_7061180829151048981[8] = 0;
   out_7061180829151048981[9] = 0;
   out_7061180829151048981[10] = 0;
   out_7061180829151048981[11] = 0;
   out_7061180829151048981[12] = 0;
   out_7061180829151048981[13] = 0;
   out_7061180829151048981[14] = 1;
   out_7061180829151048981[15] = 0;
   out_7061180829151048981[16] = 0;
   out_7061180829151048981[17] = 0;
}
void h_30(double *state, double *unused, double *out_6672983577052102809) {
   out_6672983577052102809[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1527378444552891996) {
   out_1527378444552891996[0] = 0;
   out_1527378444552891996[1] = 0;
   out_1527378444552891996[2] = 0;
   out_1527378444552891996[3] = 0;
   out_1527378444552891996[4] = 1;
   out_1527378444552891996[5] = 0;
   out_1527378444552891996[6] = 0;
   out_1527378444552891996[7] = 0;
   out_1527378444552891996[8] = 0;
}
void h_26(double *state, double *unused, double *out_6772087228996603162) {
   out_6772087228996603162[0] = state[7];
}
void H_26(double *state, double *unused, double *out_741185433299340022) {
   out_741185433299340022[0] = 0;
   out_741185433299340022[1] = 0;
   out_741185433299340022[2] = 0;
   out_741185433299340022[3] = 0;
   out_741185433299340022[4] = 0;
   out_741185433299340022[5] = 0;
   out_741185433299340022[6] = 0;
   out_741185433299340022[7] = 1;
   out_741185433299340022[8] = 0;
}
void h_27(double *state, double *unused, double *out_1592596185437432833) {
   out_1592596185437432833[0] = state[3];
}
void H_27(double *state, double *unused, double *out_696215626631051221) {
   out_696215626631051221[0] = 0;
   out_696215626631051221[1] = 0;
   out_696215626631051221[2] = 0;
   out_696215626631051221[3] = 1;
   out_696215626631051221[4] = 0;
   out_696215626631051221[5] = 0;
   out_696215626631051221[6] = 0;
   out_696215626631051221[7] = 0;
   out_696215626631051221[8] = 0;
}
void h_29(double *state, double *unused, double *out_2648574529195806150) {
   out_2648574529195806150[0] = state[1];
}
void H_29(double *state, double *unused, double *out_1017147100238499812) {
   out_1017147100238499812[0] = 0;
   out_1017147100238499812[1] = 1;
   out_1017147100238499812[2] = 0;
   out_1017147100238499812[3] = 0;
   out_1017147100238499812[4] = 0;
   out_1017147100238499812[5] = 0;
   out_1017147100238499812[6] = 0;
   out_1017147100238499812[7] = 0;
   out_1017147100238499812[8] = 0;
}
void h_28(double *state, double *unused, double *out_5127222044847074816) {
   out_5127222044847074816[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6099546117308030386) {
   out_6099546117308030386[0] = 1;
   out_6099546117308030386[1] = 0;
   out_6099546117308030386[2] = 0;
   out_6099546117308030386[3] = 0;
   out_6099546117308030386[4] = 0;
   out_6099546117308030386[5] = 0;
   out_6099546117308030386[6] = 0;
   out_6099546117308030386[7] = 0;
   out_6099546117308030386[8] = 0;
}
void h_31(double *state, double *unused, double *out_6057595546542412002) {
   out_6057595546542412002[0] = state[8];
}
void H_31(double *state, double *unused, double *out_3030963847451676630) {
   out_3030963847451676630[0] = 0;
   out_3030963847451676630[1] = 0;
   out_3030963847451676630[2] = 0;
   out_3030963847451676630[3] = 0;
   out_3030963847451676630[4] = 0;
   out_3030963847451676630[5] = 0;
   out_3030963847451676630[6] = 0;
   out_3030963847451676630[7] = 0;
   out_3030963847451676630[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_3085762064690293463) {
  err_fun(nom_x, delta_x, out_3085762064690293463);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8869691075625684096) {
  inv_err_fun(nom_x, true_x, out_8869691075625684096);
}
void car_H_mod_fun(double *state, double *out_4304656995766687822) {
  H_mod_fun(state, out_4304656995766687822);
}
void car_f_fun(double *state, double dt, double *out_4290705075249888359) {
  f_fun(state,  dt, out_4290705075249888359);
}
void car_F_fun(double *state, double dt, double *out_2044662117251408537) {
  F_fun(state,  dt, out_2044662117251408537);
}
void car_h_25(double *state, double *unused, double *out_5185932570181153644) {
  h_25(state, unused, out_5185932570181153644);
}
void car_H_25(double *state, double *unused, double *out_3000317885574716202) {
  H_25(state, unused, out_3000317885574716202);
}
void car_h_24(double *state, double *unused, double *out_2382549089680422133) {
  h_24(state, unused, out_2382549089680422133);
}
void car_H_24(double *state, double *unused, double *out_7061180829151048981) {
  H_24(state, unused, out_7061180829151048981);
}
void car_h_30(double *state, double *unused, double *out_6672983577052102809) {
  h_30(state, unused, out_6672983577052102809);
}
void car_H_30(double *state, double *unused, double *out_1527378444552891996) {
  H_30(state, unused, out_1527378444552891996);
}
void car_h_26(double *state, double *unused, double *out_6772087228996603162) {
  h_26(state, unused, out_6772087228996603162);
}
void car_H_26(double *state, double *unused, double *out_741185433299340022) {
  H_26(state, unused, out_741185433299340022);
}
void car_h_27(double *state, double *unused, double *out_1592596185437432833) {
  h_27(state, unused, out_1592596185437432833);
}
void car_H_27(double *state, double *unused, double *out_696215626631051221) {
  H_27(state, unused, out_696215626631051221);
}
void car_h_29(double *state, double *unused, double *out_2648574529195806150) {
  h_29(state, unused, out_2648574529195806150);
}
void car_H_29(double *state, double *unused, double *out_1017147100238499812) {
  H_29(state, unused, out_1017147100238499812);
}
void car_h_28(double *state, double *unused, double *out_5127222044847074816) {
  h_28(state, unused, out_5127222044847074816);
}
void car_H_28(double *state, double *unused, double *out_6099546117308030386) {
  H_28(state, unused, out_6099546117308030386);
}
void car_h_31(double *state, double *unused, double *out_6057595546542412002) {
  h_31(state, unused, out_6057595546542412002);
}
void car_H_31(double *state, double *unused, double *out_3030963847451676630) {
  H_31(state, unused, out_3030963847451676630);
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
