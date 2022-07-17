#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sm_TM_calc_angdist.h"

void sm_TM_SNT_match(double sm_TM_RBM_matchmat[][5],
                     int L,
                     double fe_output[][2],
                     int N,
                     int sm_TM_SNT[5060][11],
                     double sm_GD_SC[5060][4],
                     double sm_TM_CP_F,
                     double pixel_size,
                     int Nth,
                     int sm_TM_SNT_output[])
{
double fe_unmatched[N][2];
int num_unmatched = 0;

for (int j=0; j < N; j++)
{
    bool already_matched = false;

    for (int i=0; i < L; i++)
    {
        if ((sm_TM_RBM_matchmat[i][2] == fe_output[j][0]) and (sm_TM_RBM_matchmat[i][3] == fe_output[j][1]))
        {
            already_matched = true;
            break;
        }
    }
    if (not already_matched)
    {
        fe_unmatched[num_unmatched][0] = fe_output[j][0];
        fe_unmatched[num_unmatched][1] = fe_output[j][1];
        num_unmatched++;
    }
}


int new_matched = 0;

while (new_matched < Nth - L)
{
    for (int i = 0; i < L; i++)
    {
        int curr_ref_star = sm_TM_RBM_matchmat[i][5];
        int j = 1;
        while (sm_TM_SNT[curr_ref_star-1][j] != 0)
        {
            double x1 = sm_TM_RBM_matchmat[i][2];
            double y1 = sm_TM_RBM_matchmat[i][3];
            double x2 = fe_unmatched[new_matched][0];
            double y2 = fe_unmatched[new_matched][1];

            if (sm_TM_id_angdist(curr_ref_star, sm_TM_SNT[curr_ref_star][j], sm_GD_SC) == sm_TM_centroid_angdist(x1, y1, x2, y2, sm_TM_CP_F, pixel_size))
            {
                sm_TM_SNT_output[new_matched] = sm_TM_SNT[curr_ref_star][j];
                new_matched++;
            }

        }

    }
}

}
