#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_908254512132799916);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_1478078535588975513);
void pose_H_mod_fun(double *state, double *out_3249349051420756862);
void pose_f_fun(double *state, double dt, double *out_5432931765517539191);
void pose_F_fun(double *state, double dt, double *out_2727849687671059041);
void pose_h_4(double *state, double *unused, double *out_7232734351538059647);
void pose_H_4(double *state, double *unused, double *out_6523571130211706115);
void pose_h_10(double *state, double *unused, double *out_635550838215594982);
void pose_H_10(double *state, double *unused, double *out_9209540089341204390);
void pose_h_13(double *state, double *unused, double *out_400150804030781628);
void pose_H_13(double *state, double *unused, double *out_1087060078104994814);
void pose_h_14(double *state, double *unused, double *out_4238769098804087488);
void pose_H_14(double *state, double *unused, double *out_2560330273872221586);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}