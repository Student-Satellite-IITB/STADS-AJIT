#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sm_TM_CP.h"
#include "sm_TM_RBM.h"
#include "sm_TM_SNT_matched.h"
#include "sm_TM_consts.h"

void sm_TM_main(double fe_output[][2],
                int N,
                double sm_output_curr[][3],
                int M,
                double sm_output_prev[][3],
                int O,
                int sm_TM_SNT[5060][11],
                double sm_GD_SC[5060][4],
                bool sort_before_match,
                bool sort_dx,
                double final_output[Nth][4])

{
double sm_TM_CP_prevmat[O][3];
double sm_TM_CP_currmat[M][3];
int n_common = 0;

for (int i = 0; i<M; i++)
    for (int j = 0; j<O; j++)
        if (sm_output_curr[i][2] == sm_output_prev[j][2])
        {
            sm_TM_CP_prevmat[n_common][0] = sm_output_prev[j][0];
            sm_TM_CP_prevmat[n_common][1] = sm_output_prev[j][1];
            sm_TM_CP_prevmat[n_common][2] = sm_output_prev[j][2];

            sm_TM_CP_currmat[n_common][0] = sm_output_curr[i][0];
            sm_TM_CP_currmat[n_common][1] = sm_output_curr[i][1];
            sm_TM_CP_currmat[n_common][2] = sm_output_curr[i][2];

            n_common++;
        }

if (n_common < 2) return;

double sm_TM_CP_predmat[n_common][3];
sm_TM_CP(sm_TM_CP_prevmat, sm_TM_CP_currmat, FOCAL_LENGTH, sm_TM_CP_predmat, n_common, pixel_size);

double sm_TM_RBM_matchmat[n_common][5];
int RBM_matched = sm_TM_RBM(sm_TM_CP_predmat, n_common, fe_output, N, RBM_radius, sort_dx, sort_before_match, sm_TM_RBM_matchmat);

if (RBM_matched >= Nth) return;

int sm_TM_SNT_newmatched[Nth];
sm_TM_SNT_match(sm_TM_RBM_matchmat, n_common, fe_output, N, sm_TM_SNT, sm_GD_SC, FOCAL_LENGTH, pixel_size, Nth, sm_TM_SNT_newmatched);



}
