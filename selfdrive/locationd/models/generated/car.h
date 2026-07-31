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
void car_err_fun(double *nom_x, double *delta_x, double *out_7605142866991004783);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_1440652675888281930);
void car_H_mod_fun(double *state, double *out_178616141825887590);
void car_f_fun(double *state, double dt, double *out_1588077771682777159);
void car_F_fun(double *state, double dt, double *out_2804806635348514472);
void car_h_25(double *state, double *unused, double *out_7143928669701088849);
void car_H_25(double *state, double *unused, double *out_9074939705971426789);
void car_h_24(double *state, double *unused, double *out_5462970336184341809);
void car_H_24(double *state, double *unused, double *out_6902290106965927223);
void car_h_30(double *state, double *unused, double *out_6986742001349959704);
void car_H_30(double *state, double *unused, double *out_4547243375843818591);
void car_h_26(double *state, double *unused, double *out_2478032900352751147);
void car_H_26(double *state, double *unused, double *out_5333436387097370565);
void car_h_27(double *state, double *unused, double *out_7747244554377566366);
void car_H_27(double *state, double *unused, double *out_6770837447027761808);
void car_h_29(double *state, double *unused, double *out_16020702443106075);
void car_H_29(double *state, double *unused, double *out_5057474720158210775);
void car_h_28(double *state, double *unused, double *out_1377941413084076291);
void car_H_28(double *state, double *unused, double *out_7021104991723537026);
void car_h_31(double *state, double *unused, double *out_7204512105729090903);
void car_H_31(double *state, double *unused, double *out_9105585667848387217);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}