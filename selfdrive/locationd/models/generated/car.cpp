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
void err_fun(double *nom_x, double *delta_x, double *out_49285200847488255) {
   out_49285200847488255[0] = delta_x[0] + nom_x[0];
   out_49285200847488255[1] = delta_x[1] + nom_x[1];
   out_49285200847488255[2] = delta_x[2] + nom_x[2];
   out_49285200847488255[3] = delta_x[3] + nom_x[3];
   out_49285200847488255[4] = delta_x[4] + nom_x[4];
   out_49285200847488255[5] = delta_x[5] + nom_x[5];
   out_49285200847488255[6] = delta_x[6] + nom_x[6];
   out_49285200847488255[7] = delta_x[7] + nom_x[7];
   out_49285200847488255[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_9123250913705597883) {
   out_9123250913705597883[0] = -nom_x[0] + true_x[0];
   out_9123250913705597883[1] = -nom_x[1] + true_x[1];
   out_9123250913705597883[2] = -nom_x[2] + true_x[2];
   out_9123250913705597883[3] = -nom_x[3] + true_x[3];
   out_9123250913705597883[4] = -nom_x[4] + true_x[4];
   out_9123250913705597883[5] = -nom_x[5] + true_x[5];
   out_9123250913705597883[6] = -nom_x[6] + true_x[6];
   out_9123250913705597883[7] = -nom_x[7] + true_x[7];
   out_9123250913705597883[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2017524134906365961) {
   out_2017524134906365961[0] = 1.0;
   out_2017524134906365961[1] = 0.0;
   out_2017524134906365961[2] = 0.0;
   out_2017524134906365961[3] = 0.0;
   out_2017524134906365961[4] = 0.0;
   out_2017524134906365961[5] = 0.0;
   out_2017524134906365961[6] = 0.0;
   out_2017524134906365961[7] = 0.0;
   out_2017524134906365961[8] = 0.0;
   out_2017524134906365961[9] = 0.0;
   out_2017524134906365961[10] = 1.0;
   out_2017524134906365961[11] = 0.0;
   out_2017524134906365961[12] = 0.0;
   out_2017524134906365961[13] = 0.0;
   out_2017524134906365961[14] = 0.0;
   out_2017524134906365961[15] = 0.0;
   out_2017524134906365961[16] = 0.0;
   out_2017524134906365961[17] = 0.0;
   out_2017524134906365961[18] = 0.0;
   out_2017524134906365961[19] = 0.0;
   out_2017524134906365961[20] = 1.0;
   out_2017524134906365961[21] = 0.0;
   out_2017524134906365961[22] = 0.0;
   out_2017524134906365961[23] = 0.0;
   out_2017524134906365961[24] = 0.0;
   out_2017524134906365961[25] = 0.0;
   out_2017524134906365961[26] = 0.0;
   out_2017524134906365961[27] = 0.0;
   out_2017524134906365961[28] = 0.0;
   out_2017524134906365961[29] = 0.0;
   out_2017524134906365961[30] = 1.0;
   out_2017524134906365961[31] = 0.0;
   out_2017524134906365961[32] = 0.0;
   out_2017524134906365961[33] = 0.0;
   out_2017524134906365961[34] = 0.0;
   out_2017524134906365961[35] = 0.0;
   out_2017524134906365961[36] = 0.0;
   out_2017524134906365961[37] = 0.0;
   out_2017524134906365961[38] = 0.0;
   out_2017524134906365961[39] = 0.0;
   out_2017524134906365961[40] = 1.0;
   out_2017524134906365961[41] = 0.0;
   out_2017524134906365961[42] = 0.0;
   out_2017524134906365961[43] = 0.0;
   out_2017524134906365961[44] = 0.0;
   out_2017524134906365961[45] = 0.0;
   out_2017524134906365961[46] = 0.0;
   out_2017524134906365961[47] = 0.0;
   out_2017524134906365961[48] = 0.0;
   out_2017524134906365961[49] = 0.0;
   out_2017524134906365961[50] = 1.0;
   out_2017524134906365961[51] = 0.0;
   out_2017524134906365961[52] = 0.0;
   out_2017524134906365961[53] = 0.0;
   out_2017524134906365961[54] = 0.0;
   out_2017524134906365961[55] = 0.0;
   out_2017524134906365961[56] = 0.0;
   out_2017524134906365961[57] = 0.0;
   out_2017524134906365961[58] = 0.0;
   out_2017524134906365961[59] = 0.0;
   out_2017524134906365961[60] = 1.0;
   out_2017524134906365961[61] = 0.0;
   out_2017524134906365961[62] = 0.0;
   out_2017524134906365961[63] = 0.0;
   out_2017524134906365961[64] = 0.0;
   out_2017524134906365961[65] = 0.0;
   out_2017524134906365961[66] = 0.0;
   out_2017524134906365961[67] = 0.0;
   out_2017524134906365961[68] = 0.0;
   out_2017524134906365961[69] = 0.0;
   out_2017524134906365961[70] = 1.0;
   out_2017524134906365961[71] = 0.0;
   out_2017524134906365961[72] = 0.0;
   out_2017524134906365961[73] = 0.0;
   out_2017524134906365961[74] = 0.0;
   out_2017524134906365961[75] = 0.0;
   out_2017524134906365961[76] = 0.0;
   out_2017524134906365961[77] = 0.0;
   out_2017524134906365961[78] = 0.0;
   out_2017524134906365961[79] = 0.0;
   out_2017524134906365961[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_6622563940226238714) {
   out_6622563940226238714[0] = state[0];
   out_6622563940226238714[1] = state[1];
   out_6622563940226238714[2] = state[2];
   out_6622563940226238714[3] = state[3];
   out_6622563940226238714[4] = state[4];
   out_6622563940226238714[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_6622563940226238714[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_6622563940226238714[7] = state[7];
   out_6622563940226238714[8] = state[8];
}
void F_fun(double *state, double dt, double *out_5356412997324511205) {
   out_5356412997324511205[0] = 1;
   out_5356412997324511205[1] = 0;
   out_5356412997324511205[2] = 0;
   out_5356412997324511205[3] = 0;
   out_5356412997324511205[4] = 0;
   out_5356412997324511205[5] = 0;
   out_5356412997324511205[6] = 0;
   out_5356412997324511205[7] = 0;
   out_5356412997324511205[8] = 0;
   out_5356412997324511205[9] = 0;
   out_5356412997324511205[10] = 1;
   out_5356412997324511205[11] = 0;
   out_5356412997324511205[12] = 0;
   out_5356412997324511205[13] = 0;
   out_5356412997324511205[14] = 0;
   out_5356412997324511205[15] = 0;
   out_5356412997324511205[16] = 0;
   out_5356412997324511205[17] = 0;
   out_5356412997324511205[18] = 0;
   out_5356412997324511205[19] = 0;
   out_5356412997324511205[20] = 1;
   out_5356412997324511205[21] = 0;
   out_5356412997324511205[22] = 0;
   out_5356412997324511205[23] = 0;
   out_5356412997324511205[24] = 0;
   out_5356412997324511205[25] = 0;
   out_5356412997324511205[26] = 0;
   out_5356412997324511205[27] = 0;
   out_5356412997324511205[28] = 0;
   out_5356412997324511205[29] = 0;
   out_5356412997324511205[30] = 1;
   out_5356412997324511205[31] = 0;
   out_5356412997324511205[32] = 0;
   out_5356412997324511205[33] = 0;
   out_5356412997324511205[34] = 0;
   out_5356412997324511205[35] = 0;
   out_5356412997324511205[36] = 0;
   out_5356412997324511205[37] = 0;
   out_5356412997324511205[38] = 0;
   out_5356412997324511205[39] = 0;
   out_5356412997324511205[40] = 1;
   out_5356412997324511205[41] = 0;
   out_5356412997324511205[42] = 0;
   out_5356412997324511205[43] = 0;
   out_5356412997324511205[44] = 0;
   out_5356412997324511205[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_5356412997324511205[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_5356412997324511205[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5356412997324511205[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_5356412997324511205[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_5356412997324511205[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_5356412997324511205[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_5356412997324511205[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_5356412997324511205[53] = -9.8100000000000005*dt;
   out_5356412997324511205[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_5356412997324511205[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_5356412997324511205[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5356412997324511205[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5356412997324511205[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_5356412997324511205[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_5356412997324511205[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_5356412997324511205[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_5356412997324511205[62] = 0;
   out_5356412997324511205[63] = 0;
   out_5356412997324511205[64] = 0;
   out_5356412997324511205[65] = 0;
   out_5356412997324511205[66] = 0;
   out_5356412997324511205[67] = 0;
   out_5356412997324511205[68] = 0;
   out_5356412997324511205[69] = 0;
   out_5356412997324511205[70] = 1;
   out_5356412997324511205[71] = 0;
   out_5356412997324511205[72] = 0;
   out_5356412997324511205[73] = 0;
   out_5356412997324511205[74] = 0;
   out_5356412997324511205[75] = 0;
   out_5356412997324511205[76] = 0;
   out_5356412997324511205[77] = 0;
   out_5356412997324511205[78] = 0;
   out_5356412997324511205[79] = 0;
   out_5356412997324511205[80] = 1;
}
void h_25(double *state, double *unused, double *out_1918977838287128218) {
   out_1918977838287128218[0] = state[6];
}
void H_25(double *state, double *unused, double *out_7175664091005871276) {
   out_7175664091005871276[0] = 0;
   out_7175664091005871276[1] = 0;
   out_7175664091005871276[2] = 0;
   out_7175664091005871276[3] = 0;
   out_7175664091005871276[4] = 0;
   out_7175664091005871276[5] = 0;
   out_7175664091005871276[6] = 1;
   out_7175664091005871276[7] = 0;
   out_7175664091005871276[8] = 0;
}
void h_24(double *state, double *unused, double *out_6247253825258833787) {
   out_6247253825258833787[0] = state[4];
   out_6247253825258833787[1] = state[5];
}
void H_24(double *state, double *unused, double *out_9098430383698180774) {
   out_9098430383698180774[0] = 0;
   out_9098430383698180774[1] = 0;
   out_9098430383698180774[2] = 0;
   out_9098430383698180774[3] = 0;
   out_9098430383698180774[4] = 1;
   out_9098430383698180774[5] = 0;
   out_9098430383698180774[6] = 0;
   out_9098430383698180774[7] = 0;
   out_9098430383698180774[8] = 0;
   out_9098430383698180774[9] = 0;
   out_9098430383698180774[10] = 0;
   out_9098430383698180774[11] = 0;
   out_9098430383698180774[12] = 0;
   out_9098430383698180774[13] = 0;
   out_9098430383698180774[14] = 1;
   out_9098430383698180774[15] = 0;
   out_9098430383698180774[16] = 0;
   out_9098430383698180774[17] = 0;
}
void h_30(double *state, double *unused, double *out_8646493584668374213) {
   out_8646493584668374213[0] = state[4];
}
void H_30(double *state, double *unused, double *out_4657331132498622649) {
   out_4657331132498622649[0] = 0;
   out_4657331132498622649[1] = 0;
   out_4657331132498622649[2] = 0;
   out_4657331132498622649[3] = 0;
   out_4657331132498622649[4] = 1;
   out_4657331132498622649[5] = 0;
   out_4657331132498622649[6] = 0;
   out_4657331132498622649[7] = 0;
   out_4657331132498622649[8] = 0;
}
void h_26(double *state, double *unused, double *out_4798577221380331758) {
   out_4798577221380331758[0] = state[7];
}
void H_26(double *state, double *unused, double *out_7529576663829624116) {
   out_7529576663829624116[0] = 0;
   out_7529576663829624116[1] = 0;
   out_7529576663829624116[2] = 0;
   out_7529576663829624116[3] = 0;
   out_7529576663829624116[4] = 0;
   out_7529576663829624116[5] = 0;
   out_7529576663829624116[6] = 0;
   out_7529576663829624116[7] = 1;
   out_7529576663829624116[8] = 0;
}
void h_27(double *state, double *unused, double *out_2522293722963605735) {
   out_2522293722963605735[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6832094444299047560) {
   out_6832094444299047560[0] = 0;
   out_6832094444299047560[1] = 0;
   out_6832094444299047560[2] = 0;
   out_6832094444299047560[3] = 1;
   out_6832094444299047560[4] = 0;
   out_6832094444299047560[5] = 0;
   out_6832094444299047560[6] = 0;
   out_6832094444299047560[7] = 0;
   out_6832094444299047560[8] = 0;
}
void h_29(double *state, double *unused, double *out_6383977199392107387) {
   out_6383977199392107387[0] = state[1];
}
void H_29(double *state, double *unused, double *out_4147099788184230465) {
   out_4147099788184230465[0] = 0;
   out_4147099788184230465[1] = 1;
   out_4147099788184230465[2] = 0;
   out_4147099788184230465[3] = 0;
   out_4147099788184230465[4] = 0;
   out_4147099788184230465[5] = 0;
   out_4147099788184230465[6] = 0;
   out_4147099788184230465[7] = 0;
   out_4147099788184230465[8] = 0;
}
void h_28(double *state, double *unused, double *out_1578783870061943300) {
   out_1578783870061943300[0] = state[0];
}
void H_28(double *state, double *unused, double *out_9217245268455790577) {
   out_9217245268455790577[0] = 1;
   out_9217245268455790577[1] = 0;
   out_9217245268455790577[2] = 0;
   out_9217245268455790577[3] = 0;
   out_9217245268455790577[4] = 0;
   out_9217245268455790577[5] = 0;
   out_9217245268455790577[6] = 0;
   out_9217245268455790577[7] = 0;
   out_9217245268455790577[8] = 0;
}
void h_31(double *state, double *unused, double *out_8764500978601750957) {
   out_8764500978601750957[0] = state[8];
}
void H_31(double *state, double *unused, double *out_6903368561596272640) {
   out_6903368561596272640[0] = 0;
   out_6903368561596272640[1] = 0;
   out_6903368561596272640[2] = 0;
   out_6903368561596272640[3] = 0;
   out_6903368561596272640[4] = 0;
   out_6903368561596272640[5] = 0;
   out_6903368561596272640[6] = 0;
   out_6903368561596272640[7] = 0;
   out_6903368561596272640[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_49285200847488255) {
  err_fun(nom_x, delta_x, out_49285200847488255);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9123250913705597883) {
  inv_err_fun(nom_x, true_x, out_9123250913705597883);
}
void car_H_mod_fun(double *state, double *out_2017524134906365961) {
  H_mod_fun(state, out_2017524134906365961);
}
void car_f_fun(double *state, double dt, double *out_6622563940226238714) {
  f_fun(state,  dt, out_6622563940226238714);
}
void car_F_fun(double *state, double dt, double *out_5356412997324511205) {
  F_fun(state,  dt, out_5356412997324511205);
}
void car_h_25(double *state, double *unused, double *out_1918977838287128218) {
  h_25(state, unused, out_1918977838287128218);
}
void car_H_25(double *state, double *unused, double *out_7175664091005871276) {
  H_25(state, unused, out_7175664091005871276);
}
void car_h_24(double *state, double *unused, double *out_6247253825258833787) {
  h_24(state, unused, out_6247253825258833787);
}
void car_H_24(double *state, double *unused, double *out_9098430383698180774) {
  H_24(state, unused, out_9098430383698180774);
}
void car_h_30(double *state, double *unused, double *out_8646493584668374213) {
  h_30(state, unused, out_8646493584668374213);
}
void car_H_30(double *state, double *unused, double *out_4657331132498622649) {
  H_30(state, unused, out_4657331132498622649);
}
void car_h_26(double *state, double *unused, double *out_4798577221380331758) {
  h_26(state, unused, out_4798577221380331758);
}
void car_H_26(double *state, double *unused, double *out_7529576663829624116) {
  H_26(state, unused, out_7529576663829624116);
}
void car_h_27(double *state, double *unused, double *out_2522293722963605735) {
  h_27(state, unused, out_2522293722963605735);
}
void car_H_27(double *state, double *unused, double *out_6832094444299047560) {
  H_27(state, unused, out_6832094444299047560);
}
void car_h_29(double *state, double *unused, double *out_6383977199392107387) {
  h_29(state, unused, out_6383977199392107387);
}
void car_H_29(double *state, double *unused, double *out_4147099788184230465) {
  H_29(state, unused, out_4147099788184230465);
}
void car_h_28(double *state, double *unused, double *out_1578783870061943300) {
  h_28(state, unused, out_1578783870061943300);
}
void car_H_28(double *state, double *unused, double *out_9217245268455790577) {
  H_28(state, unused, out_9217245268455790577);
}
void car_h_31(double *state, double *unused, double *out_8764500978601750957) {
  h_31(state, unused, out_8764500978601750957);
}
void car_H_31(double *state, double *unused, double *out_6903368561596272640) {
  H_31(state, unused, out_6903368561596272640);
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
