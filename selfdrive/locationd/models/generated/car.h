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
void car_err_fun(double *nom_x, double *delta_x, double *out_2775274116566591905);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_4862922527033836182);
void car_H_mod_fun(double *state, double *out_288162873960322100);
void car_f_fun(double *state, double dt, double *out_4209339073044526153);
void car_F_fun(double *state, double dt, double *out_8268644401583620946);
void car_h_25(double *state, double *unused, double *out_1237672683194303606);
void car_H_25(double *state, double *unused, double *out_8965392973836992279);
void car_h_24(double *state, double *unused, double *out_6600116073729833171);
void car_H_24(double *state, double *unused, double *out_6792743374831492713);
void car_h_30(double *state, double *unused, double *out_2063324788982146462);
void car_H_30(double *state, double *unused, double *out_6963018141365310710);
void car_h_26(double *state, double *unused, double *out_6461276870263775474);
void car_H_26(double *state, double *unused, double *out_5223889654962936055);
void car_h_27(double *state, double *unused, double *out_3764000584466542039);
void car_H_27(double *state, double *unused, double *out_4739424070181367493);
void car_h_29(double *state, double *unused, double *out_334302713812829825);
void car_H_29(double *state, double *unused, double *out_6452786797050918526);
void car_h_28(double *state, double *unused, double *out_8765673852127387684);
void car_H_28(double *state, double *unused, double *out_6911558259589102516);
void car_h_31(double *state, double *unused, double *out_6525592573626368835);
void car_H_31(double *state, double *unused, double *out_8996038935713952707);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}