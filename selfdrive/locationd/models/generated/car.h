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
void car_err_fun(double *nom_x, double *delta_x, double *out_2944995704786546086);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_5103335814858408194);
void car_H_mod_fun(double *state, double *out_3080422690750513034);
void car_f_fun(double *state, double dt, double *out_4878075406049581454);
void car_F_fun(double *state, double dt, double *out_4214148513384381455);
void car_h_25(double *state, double *unused, double *out_1916755864117606233);
void car_H_25(double *state, double *unused, double *out_6173133157046801345);
void car_h_24(double *state, double *unused, double *out_7274133001747769888);
void car_H_24(double *state, double *unused, double *out_8398840941025669907);
void car_h_30(double *state, double *unused, double *out_8766722952771272942);
void car_H_30(double *state, double *unused, double *out_5356920575171133516);
void car_h_26(double *state, double *unused, double *out_698051948931437909);
void car_H_26(double *state, double *unused, double *out_2431629838172745121);
void car_h_27(double *state, double *unused, double *out_3084917403543239412);
void car_H_27(double *state, double *unused, double *out_3869030898103136364);
void car_h_29(double *state, double *unused, double *out_4678347853277433029);
void car_H_29(double *state, double *unused, double *out_4846689230856741332);
void car_h_28(double *state, double *unused, double *out_48131352098906727);
void car_H_28(double *state, double *unused, double *out_4119298442798911582);
void car_h_31(double *state, double *unused, double *out_4854079362232744703);
void car_H_31(double *state, double *unused, double *out_6203779118923761773);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}