#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7151556355931759320);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_659960172465309786);
void pose_H_mod_fun(double *state, double *out_3449117321369348042);
void pose_f_fun(double *state, double dt, double *out_5011277720700882846);
void pose_F_fun(double *state, double dt, double *out_8549798686069518373);
void pose_h_4(double *state, double *unused, double *out_6117192379534719749);
void pose_H_4(double *state, double *unused, double *out_1703401063669732693);
void pose_h_10(double *state, double *unused, double *out_2733554222400647132);
void pose_H_10(double *state, double *unused, double *out_1998743020988853441);
void pose_h_13(double *state, double *unused, double *out_6711610153155625838);
void pose_H_13(double *state, double *unused, double *out_4915674889002065494);
void pose_h_14(double *state, double *unused, double *out_6016470627401781103);
void pose_H_14(double *state, double *unused, double *out_1379387368625639603);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}