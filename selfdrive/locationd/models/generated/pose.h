#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_5353336122144560205);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4798572186740292528);
void pose_H_mod_fun(double *state, double *out_7952152851251730240);
void pose_f_fun(double *state, double dt, double *out_7552017383192428802);
void pose_F_fun(double *state, double dt, double *out_6783292645299155505);
void pose_h_4(double *state, double *unused, double *out_3201313637048019244);
void pose_H_4(double *state, double *unused, double *out_7197991849197017633);
void pose_h_10(double *state, double *unused, double *out_7841290235876673145);
void pose_H_10(double *state, double *unused, double *out_4457773099460457900);
void pose_h_13(double *state, double *unused, double *out_6486454295362862882);
void pose_H_13(double *state, double *unused, double *out_3985718023864684832);
void pose_h_14(double *state, double *unused, double *out_6937527919275139740);
void pose_H_14(double *state, double *unused, double *out_3234750992857533104);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}