#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_5357651433809492562);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5422870240418798336);
void car_H_mod_fun(double *state, double *out_8069224043506716698);
void car_f_fun(double *state, double dt, double *out_5560648741818025428);
void car_F_fun(double *state, double dt, double *out_266263411109112485);
void car_h_25(double *state, double *unused, double *out_4735018420632240230);
void car_H_25(double *state, double *unused, double *out_6764884933314745078);
void car_h_24(double *state, double *unused, double *out_1673618182050648597);
void car_H_24(double *state, double *unused, double *out_3296613781411020105);
void car_h_30(double *state, double *unused, double *out_1097568892378217880);
void car_H_30(double *state, double *unused, double *out_6635545986171505008);
void car_h_26(double *state, double *unused, double *out_4468532291682291985);
void car_H_26(double *state, double *unused, double *out_3023381614440688854);
void car_h_27(double *state, double *unused, double *out_8381175882220820224);
void car_H_27(double *state, double *unused, double *out_4460782674371080097);
void car_h_29(double *state, double *unused, double *out_7496610409792067026);
void car_H_29(double *state, double *unused, double *out_7145777330485897192);
void car_h_28(double *state, double *unused, double *out_8984491766897297741);
void car_H_28(double *state, double *unused, double *out_2063378313416366618);
void car_h_31(double *state, double *unused, double *out_7123897726601016223);
void car_H_31(double *state, double *unused, double *out_6795530895191705506);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}