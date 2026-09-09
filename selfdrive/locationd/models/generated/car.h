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
void car_err_fun(double *nom_x, double *delta_x, double *out_49285200847488255);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_9123250913705597883);
void car_H_mod_fun(double *state, double *out_2017524134906365961);
void car_f_fun(double *state, double dt, double *out_6622563940226238714);
void car_F_fun(double *state, double dt, double *out_5356412997324511205);
void car_h_25(double *state, double *unused, double *out_1918977838287128218);
void car_H_25(double *state, double *unused, double *out_7175664091005871276);
void car_h_24(double *state, double *unused, double *out_6247253825258833787);
void car_H_24(double *state, double *unused, double *out_9098430383698180774);
void car_h_30(double *state, double *unused, double *out_8646493584668374213);
void car_H_30(double *state, double *unused, double *out_4657331132498622649);
void car_h_26(double *state, double *unused, double *out_4798577221380331758);
void car_H_26(double *state, double *unused, double *out_7529576663829624116);
void car_h_27(double *state, double *unused, double *out_2522293722963605735);
void car_H_27(double *state, double *unused, double *out_6832094444299047560);
void car_h_29(double *state, double *unused, double *out_6383977199392107387);
void car_H_29(double *state, double *unused, double *out_4147099788184230465);
void car_h_28(double *state, double *unused, double *out_1578783870061943300);
void car_H_28(double *state, double *unused, double *out_9217245268455790577);
void car_h_31(double *state, double *unused, double *out_8764500978601750957);
void car_H_31(double *state, double *unused, double *out_6903368561596272640);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}