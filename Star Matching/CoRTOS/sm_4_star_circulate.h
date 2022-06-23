//#include <stdio.h>
#include "cortos.h"
#include <stdlib.h>
#include <math.h>

void sm_4_star_circulate(long double sm_3D_vecs[][4], int *N_circ, int N_i){
    uint64_t t1 = cortos_get_clock_time();
    int j, k, v; //Declaring counter variables
    int last = 0;
    //for (int j = N_i - 1; j >= 0; j--)
    for (j = N_i - 1; j >= 0; j--)
    {
        if (sm_3D_vecs[j][0] != -1)
        {
            last = j;
            break;
        }
    }
    double curr[4] = {sm_3D_vecs[last][0], sm_3D_vecs[last][1], sm_3D_vecs[last][2], sm_3D_vecs[last][3]};
    double var; //an auxiliary variable
    //for (int k = 0; k < N_i; k++)
    for (k = 0; k < N_i; k++)
    {
        if (sm_3D_vecs[k][0] != -1)
        {
            //for (int v = 0; v < 4; v++)
            for (v = 0; v < 4; v++)
            {
                var = sm_3D_vecs[k][v];
                sm_3D_vecs[k][v] = curr[v];
                curr[v] = var;
            }
        }
    }
    *N_circ++;
    uint64_t t2 = cortos_get_clock_time();
    uint32_t t11 = t1&(0xffffffff);
    uint32_t t12 = t2&(0xffffffff);
    cortos_printf("\ntime required for circulation is %u \n", t12-t11);


}