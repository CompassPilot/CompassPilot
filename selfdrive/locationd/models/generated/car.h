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
void car_err_fun(double *nom_x, double *delta_x, double *out_6282336697139833031);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_8558060260879538587);
void car_H_mod_fun(double *state, double *out_277130384350880664);
void car_f_fun(double *state, double dt, double *out_22960078068874879);
void car_F_fun(double *state, double dt, double *out_1009521106343814741);
void car_h_25(double *state, double *unused, double *out_7939610759328423497);
void car_H_25(double *state, double *unused, double *out_7644207648622979141);
void car_h_24(double *state, double *unused, double *out_3718883584221296980);
void car_H_24(double *state, double *unused, double *out_7244610826284249339);
void car_h_30(double *state, double *unused, double *out_474455786682081705);
void car_H_30(double *state, double *unused, double *out_3116511318495370943);
void car_h_26(double *state, double *unused, double *out_5476129054342927350);
void car_H_26(double *state, double *unused, double *out_3902704329748922917);
void car_h_27(double *state, double *unused, double *out_4108091796967278973);
void car_H_27(double *state, double *unused, double *out_941748006694946032);
void car_h_29(double *state, double *unused, double *out_1417965639583744140);
void car_H_29(double *state, double *unused, double *out_3626742662809763127);
void car_h_28(double *state, double *unused, double *out_8695922405661315808);
void car_H_28(double *state, double *unused, double *out_1455656354259767447);
void car_h_31(double *state, double *unused, double *out_6869683786127105769);
void car_H_31(double *state, double *unused, double *out_3276496227515571441);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}