#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bubblesort.h"

int sm_TM_RBM (double sm_TM_RBM_predmat[][3],
                int N,
                double sm_TM_RBM_truemat[][2],
                int M,
                double sm_TM_RBM_radius,
                bool sort_dx,
                bool sort_before_match,
                double sm_TM_RBM_matchmat[][5])

{

if (sort_before_match and sort_dx)
    {
    bubbleSort3(sm_TM_RBM_predmat, N, 0);
    bubbleSort2(sm_TM_RBM_truemat, M, 0);
    }

else if (sort_before_match and (not sort_dx))
    {
    bubbleSort3(sm_TM_RBM_predmat, N, 1);
    bubbleSort2(sm_TM_RBM_truemat, M, 1);
    }

if (sort_before_match)
{

int start_ind = 0;
int stars_in_range = 0;
int sole_matched = -1;
double r = sm_TM_RBM_radius;
int matched = -1;

for (int i=0; i<N; i++)
{
    stars_in_range = 0;
    for (int j = start_ind; j<N; j++)
    {
        double dx = abs(sm_TM_RBM_truemat[j][0] - sm_TM_RBM_predmat[i][0]);
        if (dx<r)
        {
            start_ind = j;
            double dy = abs(sm_TM_RBM_truemat[j][1] - sm_TM_RBM_predmat[i][1]);
            if (dy<r)
            {
                stars_in_range++;
                if (stars_in_range > 1) break;
                sole_matched = j;
            }
        }
    }
    if (stars_in_range == 1)
    {
        matched++;
        sm_TM_RBM_matchmat[matched][0] = sm_TM_RBM_predmat[i][0];
        sm_TM_RBM_matchmat[matched][1] = sm_TM_RBM_predmat[i][1];
        sm_TM_RBM_matchmat[matched][2] = sm_TM_RBM_truemat[sole_matched][0];
        sm_TM_RBM_matchmat[matched][3] = sm_TM_RBM_truemat[sole_matched][1];
        sm_TM_RBM_matchmat[matched][4] = sm_TM_RBM_predmat[i][2];
    }
}

return matched + 1;
}

}



