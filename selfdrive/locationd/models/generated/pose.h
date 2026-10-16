#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8800160146285448971);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_3072673840862845580);
void pose_H_mod_fun(double *state, double *out_6930602079968694147);
void pose_f_fun(double *state, double dt, double *out_406523832625579260);
void pose_F_fun(double *state, double dt, double *out_848753936125427471);
void pose_h_4(double *state, double *unused, double *out_8157496129265217886);
void pose_H_4(double *state, double *unused, double *out_1170939759003718403);
void pose_h_10(double *state, double *unused, double *out_2237221901333140328);
void pose_H_10(double *state, double *unused, double *out_9147651789234380968);
void pose_h_13(double *state, double *unused, double *out_5159652440714071710);
void pose_H_13(double *state, double *unused, double *out_2041334066328614398);
void pose_h_14(double *state, double *unused, double *out_4170635472713662169);
void pose_H_14(double *state, double *unused, double *out_2792301097335766126);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}