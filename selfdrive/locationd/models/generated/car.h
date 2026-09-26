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
void car_err_fun(double *nom_x, double *delta_x, double *out_5810473909973717283);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1485605860133782086);
void car_H_mod_fun(double *state, double *out_917914942448985378);
void car_f_fun(double *state, double dt, double *out_6878888581283024476);
void car_F_fun(double *state, double dt, double *out_4073774113492927594);
void car_h_25(double *state, double *unused, double *out_7877812312184269483);
void car_H_25(double *state, double *unused, double *out_8275273283463251859);
void car_h_24(double *state, double *unused, double *out_7633665227894349500);
void car_H_24(double *state, double *unused, double *out_7998821191240800191);
void car_h_30(double *state, double *unused, double *out_8750849625267117772);
void car_H_30(double *state, double *unused, double *out_1358582941971635104);
void car_h_26(double *state, double *unused, double *out_2260751014013733031);
void car_H_26(double *state, double *unused, double *out_6429967471372243533);
void car_h_27(double *state, double *unused, double *out_7532145710080949448);
void car_H_27(double *state, double *unused, double *out_3533346253772060015);
void car_h_29(double *state, double *unused, double *out_7807339772365455337);
void car_H_29(double *state, double *unused, double *out_5246708980641611048);
void car_h_28(double *state, double *unused, double *out_1133104192667100302);
void car_H_28(double *state, double *unused, double *out_8117636075998409994);
void car_h_31(double *state, double *unused, double *out_7419610950025707821);
void car_H_31(double *state, double *unused, double *out_8244627321586291431);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}