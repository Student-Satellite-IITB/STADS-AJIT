#include <stdio.h>
#include <stdlib.h>
#include <math.h> 

void sm_validate(long double sm_3D_vecs[][4], int sm_IS[][2], long double body_vecs_IS[][4], double sm_GC[][4], int *N_is, int N_i, int N_gc, double tol, double p_1, double p_2){
    int i, j;
    int N_new = *N_is;
    int votes[N_i];
    memset(votes, 0, N_i * sizeof(votes[0]));
    // for (i = 0; i<N_i; i++){
    //     for (j = 0; j<4; j++){
    //         printf("%Lf         ", sm_3D_vecs[i][j]);
    //     }
    //     printf("\n");
    // }

    for (i = 0; i < N_i; i++){
        if (sm_IS[i][0] == -1)
            continue;
        for (j = i+1; j< N_i-1; j++){
            if (sm_IS[j][0] != -1){
                long double d_ij = fabs(body_vecs_IS[i][1]*body_vecs_IS[j][1] + body_vecs_IS[i][2]*body_vecs_IS[j][2] + body_vecs_IS[i][3]*body_vecs_IS[j][3]);
                // printf("i: %d, j: %d, norm1: %Lf, norm2: %Lf, d_ij: %Lf\n", i, j, norm1, norm2, d_ij);
                long double d_ij_gc = fabs(sm_GC[(int)sm_IS[i][1] - 1][1]*sm_GC[(int)sm_IS[j][1] - 1][1] + sm_GC[(int)sm_IS[i][1] - 1][2]*sm_GC[(int)sm_IS[j][1] - 1][2] + sm_GC[(int)sm_IS[i][1] - 1][3]*sm_GC[(int)sm_IS[j][1] - 1][3]);
                // printf("i: %d, j: %d, norm_gc_1: %Lf, norm_gc_2: %Lf, d_ij_gc: %Lf\n", i, j, norm_gc_1, norm_gc_2, d_ij_gc);
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
    // printf("\nN_LB: %d \n", N_LB);
    for (i = 0; i < N_i; i++){
        if (sm_IS[i][0] == -1)
            continue;
        if (votes[i] < N_LB){
            sm_IS[i][0] = -1;
            body_vecs_IS[i][0] = -1;
            // printf("%d discarded, %d votes \n", i, votes[i]);
            N_new--;
        }
    }
    int N_UB = p_2*(N_new)/100;
    // printf("N_UB: %d \n", N_UB);
    for (i = 0; i < N_i; i++){
        if (sm_IS[i][0] == -1)
            continue;
        if (votes[i] < N_UB){
            sm_IS[i][0] = -1;
            body_vecs_IS[i][0] = -1;
            // printf("%d discarded, %d votes \n\n\n", i, votes[i]);
            N_new--;
        }
    }
    *N_is = N_new;
}