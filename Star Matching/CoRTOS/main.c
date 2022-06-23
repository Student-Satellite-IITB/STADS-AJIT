//#include <stdio.h>
#include "cortos.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "sm_gnrt_3D_vecs.h"
#include "sm_4_star_main.h"
#include "sm_4_star_circulate.h"
#include "bubblesort.h"
#include "sm_constants.h"

#include "sm_K_vec_arr.h"
#include "sm_GC.h"

#include "UIS_0.h"
#include "UIS_1.h"
#include "UIS_2.h"
#include "UIS_3.h"
#include "UIS_4.h"
#include "UIS_5.h"
#include "UIS_6.h"
#include "UIS_7.h"
#include "UIS_8.h"
#include "UIS_9.h"

//int sm_K_vec_arr[224792][3]; Will be declared in header file
// int sm_K_vec_arr[188807][3]; // declared here because array of such sizes can't be declared inside main() in C

void sm(long double UIS[][3], int N_i)
{
    uint64_t t1 = cortos_get_clock_time();
    int i, countt, j, k; //Declaring counter variables
    // inputs/constants---------------------------------------

    //int N_i, N_uis, N_max, N_th, N_gc, N_kvec_pairs, N_circ = 0, N_is = 0;
    int N_uis, N_max, N_th, N_gc, N_kvec_pairs, N_circ = 0, N_is = 0;
    long double epsilon, q, m, foc, y_max, y_min, delta;

    // -------------------------------------------------------
    // Value of hyperparameters

    epsilon = EPSILON;
    foc = FOCAL_LENGTH;
    delta = DELTA;
    
    // Some other constants
    // y_max = 0.999999999992621;
    y_max = 0.9999999999926209;
    y_min = 0.990026120824787;
    // y_min = 0.973988966620749;
    N_kvec_pairs = 224792;
    // N_kvec_pairs = 188807;
    N_gc = 8876;
    // N_gc = 5060;

    // Inputs - will come from FE block. 
    //printf("Enter the number of stars in input test file :- ");
    //scanf("%d", &N_i);
    N_i = 26;
    N_uis = N_i;
    //printf("Enter the maximum number of iterations (< no. of input stars) you want the algorithm to run :- ");
    //scanf("%d", &N_max);
    N_max = 25;
    //printf("Enter the maximum number of matched stars you want :- ");
    //scanf("%d", &N_th);
    N_th = 8;

    //--------------------------------------------------------
    // taking input of the K vector catalogue
    /*FILE *file;
    file = fopen("sm_Reference_Star_Catalogue_4SM_6.5.txt", "r");
    // file = fopen("kvec.txt", "r");
    for (int i = 0; i < N_kvec_pairs; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int temp;
            fscanf(file, "%d", &temp);
            sm_K_vec_arr[i][j] = temp;
        }
    }
    fclose(file);

    // taking input of test file
    long double UIS[N_i][3];     // 2D array for storing (x,y) coordinates and star IDs of unidentified stars
    FILE *file2;
    file2 = fopen("sm_test_case_dummy2.txt", "r");
    // file2 = fopen("sm_test_case_2.txt", "r"); // type the name of your input test file here
    // file2 = fopen("sample_input.txt", "r");
    for (int i = 0; i < N_i; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            long double temp;
            fscanf(file2, "%Lf", &temp);
            UIS[i][j] = temp;
        }
    }
    fclose(file2);

    // taking input of Guide star catalogue
    double sm_GC[8876][4];
    // double sm_GC[5060][4];
    FILE *file3;
    file3 = fopen("sm_Guide_Star_Catalogue_6.5.txt", "r");
    // file3 = fopen("gsc.txt", "r"); 
    for (int i = 0; i < N_gc; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            long double temp;
            fscanf(file3, "%Lf", &temp);
            sm_GC[i][j] = temp;
        }
    }
    fclose(file3);
    */
    //--------------------------------------------------------
    // constants for using the k vector table (to be used in the 4 star matching)

    m = (y_max - y_min + 2 * epsilon) / (N_kvec_pairs - 1);
    q = y_min - m - epsilon;

    // printf("M is %0.15Lf\n", m);
    // printf("Q is %0.15Lf\n", q);
    
    // -------------------------------------------------------------------------------------------------------
    int sm_IS[N_gc][2]; // array for storing the matched stars
    memset(sm_IS, -1, N_gc * sizeof(sm_IS[0]));

    // sorting the UIS table according to Euclidean distance
    // bubbleSort(UIS, N_i);

    // for (int i = 0; i < N_i; i++)
    // {
    //     for (int j = 0; j < 3; j++)
    //     {
    //         printf("%Lf", UIS[i][j]);
    //     }
    //     printf("\n");
    // }


    long double sm_3D_vecs[N_i][4]; // this stores the 3D vectors generated from the UIS table
    // generating 3D vectors from the sorted UIS table
    sm_gnrt_3D_vec(sm_3D_vecs, UIS, foc, N_i);

    // for (int i = 0; i < N_i; i++)
    // {
    //     for (int j = 0; j < 4; j++)
    //     {
    //         printf("%Lf ", sm_3D_vecs[i][j]);
    //     }
    //     printf("\n");
    // }

    // main algo starts here
    int circ_flag = 1; // flag which stores the number of times the sm_3D_vecs table has been circulated
    //for (int i = 1; i <= N_max; i++) // N_max is the maximum number of times we want to run the code
    uint64_t t2 = cortos_get_clock_time(); //Constant declarations
    for (i = 1; i <= N_max; i++)
    {
       
        if (N_uis >= 4 && N_is < N_th) // N_uis >= 4 for running 4 star algo & N_is(identified stars) < N_th(threshold number of matched stars)
        {
            int N_match = 0; // variable for storing the number of stars matched in a particular iteration
            double four_stars[4][4]; // this will store the extracted 4 stars from the sm_3D_vecs table
            //for (int countt = 0, j = 0; j < N_i && countt < 4; j++) // here the variable countt is used just to count whether 4 stars have been extracted
            for (countt = 0, j = 0; j < N_i && countt < 4; j++)
            {
                if ((int)sm_3D_vecs[j][0] != -1)
                {

                    //for (int k = 0; k < 4; k++)
                    for (k = 0; k < 4; k++)
                    {
                        four_stars[countt][k] = sm_3D_vecs[j][k];
                    }
                    countt++;
                }
            }
            sm_4_star(four_stars, sm_3D_vecs, sm_IS, sm_K_vec_arr, &N_match, N_i, N_gc, delta, q, m);
            N_uis -= N_match;
            N_is += N_match;

            // printf("%d\n", N_match); // DEBUG line

            if (N_match == 0 && N_circ <= 2 * N_i) // if no stars are matched then we must circulate the sm_3D_vecs table
            {
                sm_4_star_circulate(sm_3D_vecs, &N_circ, N_i);
                if (N_circ >= 2 * N_i)
                {
                    break;  // end the loop after checking this condition, as mentioned in the flowchart
                }
            }
        }
        else
        {
            // end the loop if the conditions "N_uis >= 4 && N_is < N_th" are not satisfied
            break;
        }
    }
    uint64_t t3 = cortos_get_clock_time();
    cortos_printf(" \nTotal matched stars :- %d\n\n", N_is);
    cortos_printf("  Input_ID  Desired_star_ID  X             Y             Z\n");
    cortos_printf("-------------------------------------------------------------------\n");
    //for (int i = 0; i < N_gc; i++)
    //for (i = 0; i < N_gc; i++)
    for (i = 0; i < N_i; i++)
    {
        if (sm_IS[i][0]!=-1)
        {
            cortos_printf("%d     %d      %d         ", i, sm_IS[i][0], sm_IS[i][1]);
            //for (int j = 1; j < 4; j++)
            for (j = 1; j < 4; j++)
            {
                cortos_printf("%lf    ", sm_GC[sm_IS[i][1]][j]);
            }
            cortos_printf("\n");
        }
    }
    uint32_t t11 = t1&(0xffffffff);
    uint32_t t12 = t2&(0xffffffff);
    uint32_t t23 = t3&(0xffffffff);
    cortos_printf("\ntime required for constant declaration is %u \n", t12-t11);
    cortos_printf("\ntime required is %u \n", t23-t12);
}
int main(){
    cortos_printf("TEST CASE 1:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_0, CORTOS_N_i_0);
    cortos_printf("TEST CASE 2:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_1, CORTOS_N_i_1);
    cortos_printf("TEST CASE 3:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_2, CORTOS_N_i_2);
    cortos_printf("TEST CASE 4:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_3, CORTOS_N_i_3);
    cortos_printf("TEST CASE 5:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_4, CORTOS_N_i_4);
    cortos_printf("TEST CASE 6:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_5, CORTOS_N_i_5);
    cortos_printf("TEST CASE 7:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_6, CORTOS_N_i_6);
    cortos_printf("TEST CASE 8:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_7, CORTOS_N_i_7);
    cortos_printf("TEST CASE 9:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_8, CORTOS_N_i_8);
    cortos_printf("TEST CASE 10:-\n");
    cortos_printf("-------------------------------------------------------------------\n");
    sm(UIS_9, CORTOS_N_i_9);
    cortos_exit(0);
}
