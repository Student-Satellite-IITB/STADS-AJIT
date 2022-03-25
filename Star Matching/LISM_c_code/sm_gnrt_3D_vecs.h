#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void sm_gnrt_3D_vec(double sm_3D_vecs[][4],double sm_sorted_UIS[][3], double foc, int N_i){
    // this function is pretty straight-forward; directly the formula for generating 3D vectors has been applied
    for (int i = 0; i < N_i; i++)
    {
        double local = sqrt((sm_sorted_UIS[i][1] / foc) * (sm_sorted_UIS[i][1] / foc) + (sm_sorted_UIS[i][2] / foc) * (sm_sorted_UIS[i][2] / foc) + 1);
        sm_3D_vecs[i][0] = sm_sorted_UIS[i][0];
        sm_3D_vecs[i][1] = (sm_sorted_UIS[i][1] / (foc*local));
        sm_3D_vecs[i][2] = (sm_sorted_UIS[i][2] / (foc*local));
        sm_3D_vecs[i][3] = 1/local;
    }
}