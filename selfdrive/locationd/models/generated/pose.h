#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7808017239736434491);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_476072578365709337);
void pose_H_mod_fun(double *state, double *out_8257603167809194144);
void pose_f_fun(double *state, double dt, double *out_7273446577418706581);
void pose_F_fun(double *state, double dt, double *out_330211950996632566);
void pose_h_4(double *state, double *unused, double *out_7679267299934609420);
void pose_H_4(double *state, double *unused, double *out_686758498248627198);
void pose_h_10(double *state, double *unused, double *out_5266209753521868204);
void pose_H_10(double *state, double *unused, double *out_7448573778899456695);
void pose_h_13(double *state, double *unused, double *out_4542250088899745943);
void pose_H_13(double *state, double *unused, double *out_2525515327083705603);
void pose_h_14(double *state, double *unused, double *out_8415149323118688858);
void pose_H_14(double *state, double *unused, double *out_3276482358090857331);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}