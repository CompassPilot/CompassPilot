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
void car_err_fun(double *nom_x, double *delta_x, double *out_8412839542249066946);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1100572460195897381);
void car_H_mod_fun(double *state, double *out_1136722566492535070);
void car_f_fun(double *state, double dt, double *out_211467565025137174);
void car_F_fun(double *state, double dt, double *out_4884760099425242162);
void car_h_25(double *state, double *unused, double *out_939942926882322239);
void car_H_25(double *state, double *unused, double *out_1499834358522891124);
void car_h_24(double *state, double *unused, double *out_2762672389005360303);
void car_H_24(double *state, double *unused, double *out_4311551272499885841);
void car_h_30(double *state, double *unused, double *out_794423102661667268);
void car_H_30(double *state, double *unused, double *out_1629173305666131194);
void car_h_26(double *state, double *unused, double *out_6543034352156531438);
void car_H_26(double *state, double *unused, double *out_5241337677396947348);
void car_h_27(double *state, double *unused, double *out_4285964288953002708);
void car_H_27(double *state, double *unused, double *out_3803936617466556105);
void car_h_29(double *state, double *unused, double *out_7797185806454733047);
void car_H_29(double *state, double *unused, double *out_5517299344336107138);
void car_h_28(double *state, double *unused, double *out_9159106517095703263);
void car_H_28(double *state, double *unused, double *out_3553669072770780887);
void car_h_31(double *state, double *unused, double *out_6823322329938350202);
void car_H_31(double *state, double *unused, double *out_1469188396645930696);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}