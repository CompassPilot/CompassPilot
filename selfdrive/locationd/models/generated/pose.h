#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2988555708200788841);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_2701064156642240678);
void pose_H_mod_fun(double *state, double *out_5968360833876018355);
void pose_f_fun(double *state, double dt, double *out_1848968576771995423);
void pose_F_fun(double *state, double dt, double *out_3155877724521984150);
void pose_h_4(double *state, double *unused, double *out_2502869184113054181);
void pose_H_4(double *state, double *unused, double *out_5214199831821305748);
void pose_h_10(double *state, double *unused, double *out_3666588124569296206);
void pose_H_10(double *state, double *unused, double *out_5786440187132908313);
void pose_h_13(double *state, double *unused, double *out_3939295682978216666);
void pose_H_13(double *state, double *unused, double *out_2396431376495395181);
void pose_h_14(double *state, double *unused, double *out_6847784443772444789);
void pose_H_14(double *state, double *unused, double *out_8296988264116678044);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}