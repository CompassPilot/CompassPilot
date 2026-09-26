#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2547418662005312230);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_7399773008628044860);
void pose_H_mod_fun(double *state, double *out_5714773270956696752);
void pose_f_fun(double *state, double dt, double *out_2896016994829875537);
void pose_F_fun(double *state, double dt, double *out_4605913986885817776);
void pose_h_4(double *state, double *unused, double *out_5842182755326302952);
void pose_H_4(double *state, double *unused, double *out_3229588395101124590);
void pose_h_10(double *state, double *unused, double *out_3449867082812412812);
void pose_H_10(double *state, double *unused, double *out_7178221840794629758);
void pose_h_13(double *state, double *unused, double *out_2961129492765088647);
void pose_H_13(double *state, double *unused, double *out_17314569768791789);
void pose_h_14(double *state, double *unused, double *out_5769522878399662028);
void pose_H_14(double *state, double *unused, double *out_733652461238359939);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}