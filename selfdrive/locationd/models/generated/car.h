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
void car_err_fun(double *nom_x, double *delta_x, double *out_7908204057599693162);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3591353112255890273);
void car_H_mod_fun(double *state, double *out_7960573159970110864);
void car_f_fun(double *state, double dt, double *out_3939178357234727692);
void car_F_fun(double *state, double dt, double *out_7601566188878897936);
void car_h_25(double *state, double *unused, double *out_1655895321249480568);
void car_H_25(double *state, double *unused, double *out_5813414222692730452);
void car_h_24(double *state, double *unused, double *out_8277837610060872399);
void car_H_24(double *state, double *unused, double *out_5342956740649391728);
void car_h_30(double *state, double *unused, double *out_5804663442999407757);
void car_H_30(double *state, double *unused, double *out_5684075275549490382);
void car_h_26(double *state, double *unused, double *out_4861153590097745322);
void car_H_26(double *state, double *unused, double *out_6470268286803042356);
void car_h_27(double *state, double *unused, double *out_948509999559217083);
void car_H_27(double *state, double *unused, double *out_3509311963749065471);
void car_h_29(double *state, double *unused, double *out_802990175338562112);
void car_H_29(double *state, double *unused, double *out_6194306619863882566);
void car_h_28(double *state, double *unused, double *out_4053163268101628562);
void car_H_28(double *state, double *unused, double *out_1111907602794351992);
void car_h_31(double *state, double *unused, double *out_1813081989600609713);
void car_H_31(double *state, double *unused, double *out_5844060184569690880);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}