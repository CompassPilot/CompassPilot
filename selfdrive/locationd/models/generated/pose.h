#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_7283166407761929442);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_546984208695000774);
void pose_H_mod_fun(double *state, double *out_3827791306191189093);
void pose_f_fun(double *state, double dt, double *out_6733983040945921210);
void pose_F_fun(double *state, double dt, double *out_6995611375067508290);
void pose_h_4(double *state, double *unused, double *out_3714895458843600451);
void pose_H_4(double *state, double *unused, double *out_2008092580284892232);
void pose_h_10(double *state, double *unused, double *out_144058714348640715);
void pose_H_10(double *state, double *unused, double *out_6768538146622882928);
void pose_h_13(double *state, double *unused, double *out_6588557550924599957);
void pose_H_13(double *state, double *unused, double *out_5220366405617225033);
void pose_h_14(double *state, double *unused, double *out_8672702186703207605);
void pose_H_14(double *state, double *unused, double *out_5971333436624376761);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}