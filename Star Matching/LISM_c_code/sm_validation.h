#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

void sm_validate(long double sm_3D_vecs[][4], int sm_IS[][2], double sm_GC[][4], int *N_is, int N_i, int N_gc, double tol, double p_1, double p_2){
    int i, j;
    int N_new = *N_is;
    int votes[N_i];
    memset(votes, 0, N_i * sizeof(votes[0]));
    for (i = 0; i < N_i; i++){
        if (sm_IS[i][0] == -1)
            continue;
        for (j = i+1; j< N_i-1; j++){
            if (sm_IS[j][0] != -1){
                long double norm1 = sqrt(sm_3D_vecs[i][1]*sm_3D_vecs[i][1] + sm_3D_vecs[i][2]*sm_3D_vecs[i][2] + sm_3D_vecs[i][3]*sm_3D_vecs[i][3]);
                long double norm2 = sqrt(sm_3D_vecs[j][1]*sm_3D_vecs[j][1] + sm_3D_vecs[j][2]*sm_3D_vecs[j][2] + sm_3D_vecs[j][3]*sm_3D_vecs[j][3]);
                long double norm_gc_1 = sqrt(sm_GC[sm_IS[i][1]][1]*sm_GC[sm_IS[i][1]][1] + sm_GC[sm_IS[i][1]][2]*sm_GC[sm_IS[i][1]][2] + sm_GC[sm_IS[i][1]][3]*sm_GC[sm_IS[i][1]][3]);
                long double norm_gc_2 = sqrt(sm_GC[sm_IS[j][1]][1]*sm_GC[sm_IS[j][1]][1] + sm_GC[sm_IS[j][1]][2]*sm_GC[sm_IS[j][1]][2] + sm_GC[sm_IS[j][1]][3]*sm_GC[sm_IS[j][1]][3]);
                long double d_ij = fabs(sm_3D_vecs[i][1]*sm_3D_vecs[j][1] + sm_3D_vecs[i][2]*sm_3D_vecs[j][2] + sm_3D_vecs[i][3]*sm_3D_vecs[j][3])/(norm1*norm2);
                long double d_ij_gc = fabs(sm_GC[sm_IS[i][1]][1]*sm_GC[sm_IS[j][1]][1] + sm_GC[sm_IS[i][1]][2]*sm_GC[sm_IS[j][1]][2] + sm_GC[sm_IS[i][1]][3]*sm_GC[sm_IS[j][1]][3])/(norm_gc_1*norm_gc_2);
                if (fabs(d_ij/d_ij_gc - 1) < tol/100){
                    votes[i]++;
                    votes[j]++;
                }
                if((votes[i] < 0) || (votes[j] < 0))
                    printf("Idx i: %d, j: %d\n", i, j);
            }
        }
    }
    int N_LB = p_1*(N_new)/100;
    printf("\nN_LB: %d \n", N_LB);
    for (i = 0; i < N_i; i++){
        if (sm_IS[i][0] == -1)
            continue;
        if (votes[i] < N_LB){
            sm_IS[i][0] = -1;
            printf("%d discarded, %d votes \n", i, votes[i]);
            N_new--;
        }
    }
    int N_UB = p_2*(N_new)/100;
    printf("N_UB: %d \n", N_UB);
    for (i = 0; i < N_i; i++){
        if (sm_IS[i][0] == -1)
            continue;
        if (votes[i] < N_UB){
            sm_IS[i][0] = -1;
            printf("%d discarded, %d votes \n\n\n", i, votes[i]);
            N_new--;
        }
    }
    *N_is = N_new;
}