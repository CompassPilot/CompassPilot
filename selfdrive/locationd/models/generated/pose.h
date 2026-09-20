#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2139705222199814366);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_5823649811361463428);
void pose_H_mod_fun(double *state, double *out_7742649709516102044);
void pose_f_fun(double *state, double dt, double *out_3760212722055020200);
void pose_F_fun(double *state, double dt, double *out_8097536246104009244);
void pose_h_4(double *state, double *unused, double *out_3390290786106786870);
void pose_H_4(double *state, double *unused, double *out_4468427630725152791);
void pose_h_10(double *state, double *unused, double *out_3462457376472911907);
void pose_H_10(double *state, double *unused, double *out_6419953993889457901);
void pose_h_13(double *state, double *unused, double *out_4244633994094952731);
void pose_H_13(double *state, double *unused, double *out_7680701456057485592);
void pose_h_14(double *state, double *unused, double *out_4959751181186855862);
void pose_H_14(double *state, double *unused, double *out_8431668487064637320);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}