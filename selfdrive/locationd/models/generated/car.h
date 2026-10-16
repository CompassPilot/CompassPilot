#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_8233216615330642720);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_3323267851210774788);
void car_H_mod_fun(double *state, double *out_2657081693941184082);
void car_f_fun(double *state, double dt, double *out_2500309925286397946);
void car_F_fun(double *state, double dt, double *out_5520992529212024714);
void car_h_25(double *state, double *unused, double *out_6765546080961273843);
void car_H_25(double *state, double *unused, double *out_2246610131243480758);
void car_h_24(double *state, double *unused, double *out_8544466045127711145);
void car_H_24(double *state, double *unused, double *out_4423824554850630731);
void car_h_30(double *state, double *unused, double *out_5317604014446461912);
void car_H_30(double *state, double *unused, double *out_4764943089750729385);
void car_h_26(double *state, double *unused, double *out_2713198693637764261);
void car_H_26(double *state, double *unused, double *out_1494893187630575466);
void car_h_27(double *state, double *unused, double *out_7368861965637751360);
void car_H_27(double *state, double *unused, double *out_6988537160934672602);
void car_h_29(double *state, double *unused, double *out_598026739287400424);
void car_H_29(double *state, double *unused, double *out_5275174434065121569);
void car_h_28(double *state, double *unused, double *out_6201118164561609623);
void car_H_28(double *state, double *unused, double *out_192775416995590995);
void car_h_31(double *state, double *unused, double *out_2903862604532772191);
void car_H_31(double *state, double *unused, double *out_2277256093120441186);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}