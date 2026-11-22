#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_3291478583356534624);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_8622738967567708549);
void pose_H_mod_fun(double *state, double *out_4432635606321955062);
void pose_f_fun(double *state, double dt, double *out_872598189031658011);
void pose_F_fun(double *state, double dt, double *out_2142823975635459713);
void pose_h_4(double *state, double *unused, double *out_1527567868933253243);
void pose_H_4(double *state, double *unused, double *out_6820365971482965361);
void pose_h_10(double *state, double *unused, double *out_4124637140898740964);
void pose_H_10(double *state, double *unused, double *out_7216042770550817325);
void pose_h_13(double *state, double *unused, double *out_5617317736233702869);
void pose_H_13(double *state, double *unused, double *out_3608092146150632560);
void pose_h_14(double *state, double *unused, double *out_2577074895762232854);
void pose_H_14(double *state, double *unused, double *out_4145232286946845831);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}