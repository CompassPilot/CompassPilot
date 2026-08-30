#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_6512097809109486594);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6429931426526857200);
void pose_H_mod_fun(double *state, double *out_797770248136307860);
void pose_f_fun(double *state, double dt, double *out_8790483116213543922);
void pose_F_fun(double *state, double dt, double *out_9177730108629592028);
void pose_h_4(double *state, double *unused, double *out_7984495719087756063);
void pose_H_4(double *state, double *unused, double *out_6645852054888266581);
void pose_h_10(double *state, double *unused, double *out_7217217585169764441);
void pose_H_10(double *state, double *unused, double *out_2486700685078595702);
void pose_h_13(double *state, double *unused, double *out_4227448484818960513);
void pose_H_13(double *state, double *unused, double *out_3433578229555933780);
void pose_h_14(double *state, double *unused, double *out_4160763402509463502);
void pose_H_14(double *state, double *unused, double *out_2682611198548782052);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}