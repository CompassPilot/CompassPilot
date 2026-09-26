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
void err_fun(double *nom_x, double *delta_x, double *out_5810473909973717283) {
   out_5810473909973717283[0] = delta_x[0] + nom_x[0];
   out_5810473909973717283[1] = delta_x[1] + nom_x[1];
   out_5810473909973717283[2] = delta_x[2] + nom_x[2];
   out_5810473909973717283[3] = delta_x[3] + nom_x[3];
   out_5810473909973717283[4] = delta_x[4] + nom_x[4];
   out_5810473909973717283[5] = delta_x[5] + nom_x[5];
   out_5810473909973717283[6] = delta_x[6] + nom_x[6];
   out_5810473909973717283[7] = delta_x[7] + nom_x[7];
   out_5810473909973717283[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_1485605860133782086) {
   out_1485605860133782086[0] = -nom_x[0] + true_x[0];
   out_1485605860133782086[1] = -nom_x[1] + true_x[1];
   out_1485605860133782086[2] = -nom_x[2] + true_x[2];
   out_1485605860133782086[3] = -nom_x[3] + true_x[3];
   out_1485605860133782086[4] = -nom_x[4] + true_x[4];
   out_1485605860133782086[5] = -nom_x[5] + true_x[5];
   out_1485605860133782086[6] = -nom_x[6] + true_x[6];
   out_1485605860133782086[7] = -nom_x[7] + true_x[7];
   out_1485605860133782086[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_917914942448985378) {
   out_917914942448985378[0] = 1.0;
   out_917914942448985378[1] = 0.0;
   out_917914942448985378[2] = 0.0;
   out_917914942448985378[3] = 0.0;
   out_917914942448985378[4] = 0.0;
   out_917914942448985378[5] = 0.0;
   out_917914942448985378[6] = 0.0;
   out_917914942448985378[7] = 0.0;
   out_917914942448985378[8] = 0.0;
   out_917914942448985378[9] = 0.0;
   out_917914942448985378[10] = 1.0;
   out_917914942448985378[11] = 0.0;
   out_917914942448985378[12] = 0.0;
   out_917914942448985378[13] = 0.0;
   out_917914942448985378[14] = 0.0;
   out_917914942448985378[15] = 0.0;
   out_917914942448985378[16] = 0.0;
   out_917914942448985378[17] = 0.0;
   out_917914942448985378[18] = 0.0;
   out_917914942448985378[19] = 0.0;
   out_917914942448985378[20] = 1.0;
   out_917914942448985378[21] = 0.0;
   out_917914942448985378[22] = 0.0;
   out_917914942448985378[23] = 0.0;
   out_917914942448985378[24] = 0.0;
   out_917914942448985378[25] = 0.0;
   out_917914942448985378[26] = 0.0;
   out_917914942448985378[27] = 0.0;
   out_917914942448985378[28] = 0.0;
   out_917914942448985378[29] = 0.0;
   out_917914942448985378[30] = 1.0;
   out_917914942448985378[31] = 0.0;
   out_917914942448985378[32] = 0.0;
   out_917914942448985378[33] = 0.0;
   out_917914942448985378[34] = 0.0;
   out_917914942448985378[35] = 0.0;
   out_917914942448985378[36] = 0.0;
   out_917914942448985378[37] = 0.0;
   out_917914942448985378[38] = 0.0;
   out_917914942448985378[39] = 0.0;
   out_917914942448985378[40] = 1.0;
   out_917914942448985378[41] = 0.0;
   out_917914942448985378[42] = 0.0;
   out_917914942448985378[43] = 0.0;
   out_917914942448985378[44] = 0.0;
   out_917914942448985378[45] = 0.0;
   out_917914942448985378[46] = 0.0;
   out_917914942448985378[47] = 0.0;
   out_917914942448985378[48] = 0.0;
   out_917914942448985378[49] = 0.0;
   out_917914942448985378[50] = 1.0;
   out_917914942448985378[51] = 0.0;
   out_917914942448985378[52] = 0.0;
   out_917914942448985378[53] = 0.0;
   out_917914942448985378[54] = 0.0;
   out_917914942448985378[55] = 0.0;
   out_917914942448985378[56] = 0.0;
   out_917914942448985378[57] = 0.0;
   out_917914942448985378[58] = 0.0;
   out_917914942448985378[59] = 0.0;
   out_917914942448985378[60] = 1.0;
   out_917914942448985378[61] = 0.0;
   out_917914942448985378[62] = 0.0;
   out_917914942448985378[63] = 0.0;
   out_917914942448985378[64] = 0.0;
   out_917914942448985378[65] = 0.0;
   out_917914942448985378[66] = 0.0;
   out_917914942448985378[67] = 0.0;
   out_917914942448985378[68] = 0.0;
   out_917914942448985378[69] = 0.0;
   out_917914942448985378[70] = 1.0;
   out_917914942448985378[71] = 0.0;
   out_917914942448985378[72] = 0.0;
   out_917914942448985378[73] = 0.0;
   out_917914942448985378[74] = 0.0;
   out_917914942448985378[75] = 0.0;
   out_917914942448985378[76] = 0.0;
   out_917914942448985378[77] = 0.0;
   out_917914942448985378[78] = 0.0;
   out_917914942448985378[79] = 0.0;
   out_917914942448985378[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6878888581283024476) {
   out_6878888581283024476[0] = state[0];
   out_6878888581283024476[1] = state[1];
   out_6878888581283024476[2] = state[2];
   out_6878888581283024476[3] = state[3];
   out_6878888581283024476[4] = state[4];
   out_6878888581283024476[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6878888581283024476[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6878888581283024476[7] = state[7];
   out_6878888581283024476[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4073774113492927594) {
   out_4073774113492927594[0] = 1;
   out_4073774113492927594[1] = 0;
   out_4073774113492927594[2] = 0;
   out_4073774113492927594[3] = 0;
   out_4073774113492927594[4] = 0;
   out_4073774113492927594[5] = 0;
   out_4073774113492927594[6] = 0;
   out_4073774113492927594[7] = 0;
   out_4073774113492927594[8] = 0;
   out_4073774113492927594[9] = 0;
   out_4073774113492927594[10] = 1;
   out_4073774113492927594[11] = 0;
   out_4073774113492927594[12] = 0;
   out_4073774113492927594[13] = 0;
   out_4073774113492927594[14] = 0;
   out_4073774113492927594[15] = 0;
   out_4073774113492927594[16] = 0;
   out_4073774113492927594[17] = 0;
   out_4073774113492927594[18] = 0;
   out_4073774113492927594[19] = 0;
   out_4073774113492927594[20] = 1;
   out_4073774113492927594[21] = 0;
   out_4073774113492927594[22] = 0;
   out_4073774113492927594[23] = 0;
   out_4073774113492927594[24] = 0;
   out_4073774113492927594[25] = 0;
   out_4073774113492927594[26] = 0;
   out_4073774113492927594[27] = 0;
   out_4073774113492927594[28] = 0;
   out_4073774113492927594[29] = 0;
   out_4073774113492927594[30] = 1;
   out_4073774113492927594[31] = 0;
   out_4073774113492927594[32] = 0;
   out_4073774113492927594[33] = 0;
   out_4073774113492927594[34] = 0;
   out_4073774113492927594[35] = 0;
   out_4073774113492927594[36] = 0;
   out_4073774113492927594[37] = 0;
   out_4073774113492927594[38] = 0;
   out_4073774113492927594[39] = 0;
   out_4073774113492927594[40] = 1;
   out_4073774113492927594[41] = 0;
   out_4073774113492927594[42] = 0;
   out_4073774113492927594[43] = 0;
   out_4073774113492927594[44] = 0;
   out_4073774113492927594[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4073774113492927594[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4073774113492927594[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4073774113492927594[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4073774113492927594[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4073774113492927594[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4073774113492927594[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4073774113492927594[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4073774113492927594[53] = -9.8100000000000005*dt;
   out_4073774113492927594[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4073774113492927594[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4073774113492927594[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4073774113492927594[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4073774113492927594[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4073774113492927594[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4073774113492927594[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4073774113492927594[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4073774113492927594[62] = 0;
   out_4073774113492927594[63] = 0;
   out_4073774113492927594[64] = 0;
   out_4073774113492927594[65] = 0;
   out_4073774113492927594[66] = 0;
   out_4073774113492927594[67] = 0;
   out_4073774113492927594[68] = 0;
   out_4073774113492927594[69] = 0;
   out_4073774113492927594[70] = 1;
   out_4073774113492927594[71] = 0;
   out_4073774113492927594[72] = 0;
   out_4073774113492927594[73] = 0;
   out_4073774113492927594[74] = 0;
   out_4073774113492927594[75] = 0;
   out_4073774113492927594[76] = 0;
   out_4073774113492927594[77] = 0;
   out_4073774113492927594[78] = 0;
   out_4073774113492927594[79] = 0;
   out_4073774113492927594[80] = 1;
}
void h_25(double *state, double *unused, double *out_7877812312184269483) {
   out_7877812312184269483[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8275273283463251859) {
   out_8275273283463251859[0] = 0;
   out_8275273283463251859[1] = 0;
   out_8275273283463251859[2] = 0;
   out_8275273283463251859[3] = 0;
   out_8275273283463251859[4] = 0;
   out_8275273283463251859[5] = 0;
   out_8275273283463251859[6] = 1;
   out_8275273283463251859[7] = 0;
   out_8275273283463251859[8] = 0;
}
void h_24(double *state, double *unused, double *out_7633665227894349500) {
   out_7633665227894349500[0] = state[4];
   out_7633665227894349500[1] = state[5];
}
void H_24(double *state, double *unused, double *out_7998821191240800191) {
   out_7998821191240800191[0] = 0;
   out_7998821191240800191[1] = 0;
   out_7998821191240800191[2] = 0;
   out_7998821191240800191[3] = 0;
   out_7998821191240800191[4] = 1;
   out_7998821191240800191[5] = 0;
   out_7998821191240800191[6] = 0;
   out_7998821191240800191[7] = 0;
   out_7998821191240800191[8] = 0;
   out_7998821191240800191[9] = 0;
   out_7998821191240800191[10] = 0;
   out_7998821191240800191[11] = 0;
   out_7998821191240800191[12] = 0;
   out_7998821191240800191[13] = 0;
   out_7998821191240800191[14] = 1;
   out_7998821191240800191[15] = 0;
   out_7998821191240800191[16] = 0;
   out_7998821191240800191[17] = 0;
}
void h_30(double *state, double *unused, double *out_8750849625267117772) {
   out_8750849625267117772[0] = state[4];
}
void H_30(double *state, double *unused, double *out_1358582941971635104) {
   out_1358582941971635104[0] = 0;
   out_1358582941971635104[1] = 0;
   out_1358582941971635104[2] = 0;
   out_1358582941971635104[3] = 0;
   out_1358582941971635104[4] = 1;
   out_1358582941971635104[5] = 0;
   out_1358582941971635104[6] = 0;
   out_1358582941971635104[7] = 0;
   out_1358582941971635104[8] = 0;
}
void h_26(double *state, double *unused, double *out_2260751014013733031) {
   out_2260751014013733031[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6429967471372243533) {
   out_6429967471372243533[0] = 0;
   out_6429967471372243533[1] = 0;
   out_6429967471372243533[2] = 0;
   out_6429967471372243533[3] = 0;
   out_6429967471372243533[4] = 0;
   out_6429967471372243533[5] = 0;
   out_6429967471372243533[6] = 0;
   out_6429967471372243533[7] = 1;
   out_6429967471372243533[8] = 0;
}
void h_27(double *state, double *unused, double *out_7532145710080949448) {
   out_7532145710080949448[0] = state[3];
}
void H_27(double *state, double *unused, double *out_3533346253772060015) {
   out_3533346253772060015[0] = 0;
   out_3533346253772060015[1] = 0;
   out_3533346253772060015[2] = 0;
   out_3533346253772060015[3] = 1;
   out_3533346253772060015[4] = 0;
   out_3533346253772060015[5] = 0;
   out_3533346253772060015[6] = 0;
   out_3533346253772060015[7] = 0;
   out_3533346253772060015[8] = 0;
}
void h_29(double *state, double *unused, double *out_7807339772365455337) {
   out_7807339772365455337[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5246708980641611048) {
   out_5246708980641611048[0] = 0;
   out_5246708980641611048[1] = 1;
   out_5246708980641611048[2] = 0;
   out_5246708980641611048[3] = 0;
   out_5246708980641611048[4] = 0;
   out_5246708980641611048[5] = 0;
   out_5246708980641611048[6] = 0;
   out_5246708980641611048[7] = 0;
   out_5246708980641611048[8] = 0;
}
void h_28(double *state, double *unused, double *out_1133104192667100302) {
   out_1133104192667100302[0] = state[0];
}
void H_28(double *state, double *unused, double *out_8117636075998409994) {
   out_8117636075998409994[0] = 1;
   out_8117636075998409994[1] = 0;
   out_8117636075998409994[2] = 0;
   out_8117636075998409994[3] = 0;
   out_8117636075998409994[4] = 0;
   out_8117636075998409994[5] = 0;
   out_8117636075998409994[6] = 0;
   out_8117636075998409994[7] = 0;
   out_8117636075998409994[8] = 0;
}
void h_31(double *state, double *unused, double *out_7419610950025707821) {
   out_7419610950025707821[0] = state[8];
}
void H_31(double *state, double *unused, double *out_8244627321586291431) {
   out_8244627321586291431[0] = 0;
   out_8244627321586291431[1] = 0;
   out_8244627321586291431[2] = 0;
   out_8244627321586291431[3] = 0;
   out_8244627321586291431[4] = 0;
   out_8244627321586291431[5] = 0;
   out_8244627321586291431[6] = 0;
   out_8244627321586291431[7] = 0;
   out_8244627321586291431[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_5810473909973717283) {
  err_fun(nom_x, delta_x, out_5810473909973717283);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1485605860133782086) {
  inv_err_fun(nom_x, true_x, out_1485605860133782086);
}
void car_H_mod_fun(double *state, double *out_917914942448985378) {
  H_mod_fun(state, out_917914942448985378);
}
void car_f_fun(double *state, double dt, double *out_6878888581283024476) {
  f_fun(state,  dt, out_6878888581283024476);
}
void car_F_fun(double *state, double dt, double *out_4073774113492927594) {
  F_fun(state,  dt, out_4073774113492927594);
}
void car_h_25(double *state, double *unused, double *out_7877812312184269483) {
  h_25(state, unused, out_7877812312184269483);
}
void car_H_25(double *state, double *unused, double *out_8275273283463251859) {
  H_25(state, unused, out_8275273283463251859);
}
void car_h_24(double *state, double *unused, double *out_7633665227894349500) {
  h_24(state, unused, out_7633665227894349500);
}
void car_H_24(double *state, double *unused, double *out_7998821191240800191) {
  H_24(state, unused, out_7998821191240800191);
}
void car_h_30(double *state, double *unused, double *out_8750849625267117772) {
  h_30(state, unused, out_8750849625267117772);
}
void car_H_30(double *state, double *unused, double *out_1358582941971635104) {
  H_30(state, unused, out_1358582941971635104);
}
void car_h_26(double *state, double *unused, double *out_2260751014013733031) {
  h_26(state, unused, out_2260751014013733031);
}
void car_H_26(double *state, double *unused, double *out_6429967471372243533) {
  H_26(state, unused, out_6429967471372243533);
}
void car_h_27(double *state, double *unused, double *out_7532145710080949448) {
  h_27(state, unused, out_7532145710080949448);
}
void car_H_27(double *state, double *unused, double *out_3533346253772060015) {
  H_27(state, unused, out_3533346253772060015);
}
void car_h_29(double *state, double *unused, double *out_7807339772365455337) {
  h_29(state, unused, out_7807339772365455337);
}
void car_H_29(double *state, double *unused, double *out_5246708980641611048) {
  H_29(state, unused, out_5246708980641611048);
}
void car_h_28(double *state, double *unused, double *out_1133104192667100302) {
  h_28(state, unused, out_1133104192667100302);
}
void car_H_28(double *state, double *unused, double *out_8117636075998409994) {
  H_28(state, unused, out_8117636075998409994);
}
void car_h_31(double *state, double *unused, double *out_7419610950025707821) {
  h_31(state, unused, out_7419610950025707821);
}
void car_H_31(double *state, double *unused, double *out_8244627321586291431) {
  H_31(state, unused, out_8244627321586291431);
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
