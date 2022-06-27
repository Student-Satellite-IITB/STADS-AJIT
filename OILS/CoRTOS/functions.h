#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "constants.h"
#include "cortos.h"
#include "sm_K_vec_arr.h"
#include "sm_GC.h"

//RGA functions

void getData(unsigned short p_i, unsigned short p_j, unsigned short* star_num, unsigned long x_sum[], unsigned long y_sum[], unsigned long pixel_sum[], unsigned short num_pixels[], short arr_out_img[BREADTH + 2][LENGTH + 2]){
    // base case
    if (arr_out_img[p_j][p_i] <= THRESHOLD)
        return;

    // keeping track of the sums
    x_sum[*star_num] += (unsigned long)arr_out_img[p_j][p_i] * p_i;
    y_sum[*star_num] += (unsigned long)arr_out_img[p_j][p_i] * p_j;
    pixel_sum[*star_num] += (unsigned long)arr_out_img[p_j][p_i];
    num_pixels[*star_num] += 1;
    arr_out_img[p_j][p_i] = 0;

    // recursive calls
    getData(p_i - 1, p_j, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
    getData(p_i + 1, p_j, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
    getData(p_i, p_j - 1, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
    getData(p_i, p_j + 1, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);

    return;
}



void regionGrowth(short arr_out_img[BREADTH + 2][LENGTH + 2], double centroids_st[MAX_STARS][3], int* tot_stars)
{
    int valid_stars = 0;
    // clear out all arrays
    //unsigned short stars = 0;
    //for (stars = 0; stars < MAX_STARS; stars++)
    //{
        //x_sum[stars] = {0};
        //y_sum[stars] = {0};
        //pixel_sum[stars] = {0};
        //num_pixels[stars] = {0};
    //}

    //star_num = 0;
    //valid_stars = 0;
    //tot_stars = 0;

    
    unsigned short star_num = 0;
    unsigned long x_sum[MAX_STARS] = {0};
    unsigned long y_sum[MAX_STARS] = {0};
    unsigned long pixel_sum[MAX_STARS] = {0};
    unsigned short num_pixels[MAX_STARS] = {0};

    int i = 0;
    int j = 0;
    int k = 0;

    for (j = 1; j < BREADTH + 1; j += SKIP_PIXELS)
        for (i = 1; i < LENGTH + 1; i += SKIP_PIXELS)
            if (arr_out_img[j][i] > THRESHOLD)
            {
                getData(i, j, &star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
                star_num++;
            }
    
    for (k = 0; k < star_num; k++)
    {   
        
        if ((num_pixels[k] <= STAR_MAX_PIXEL) & (num_pixels[k] > STAR_MIN_PIXEL))
        {
            valid_stars++;
            centroids_st[valid_stars-1][0] = valid_stars;
            centroids_st[valid_stars-1][1] = ((double)x_sum[k] / (double)pixel_sum[k] - ((double)(LENGTH / 2) + 0.5)) * PIXEL_WIDTH;
            centroids_st[valid_stars-1][2] = (-1 * ((double)y_sum[k] / (double)pixel_sum[k] - ((double)(BREADTH / 2) + 0.5))) * PIXEL_WIDTH;
        }
    }

    *tot_stars += valid_stars;
    return;
}

//SM functions
void sm_4_star_circulate(double sm_3D_vecs[][4], int *N_circ, int N_i)
{   
    int v;
    int j;
    int k; 

    int last = 0;
    for (j = N_i - 1; j >= 0; j--)
    {
        if (sm_3D_vecs[j][0] != -1)
        {
            last = j;
            break;
        }
    }
    double curr[4] = {sm_3D_vecs[last][0], sm_3D_vecs[last][1], sm_3D_vecs[last][2], sm_3D_vecs[last][3]};
    double var;
    for (k = 0; k < N_i; k++)
    {
        if (sm_3D_vecs[k][0] != -1)
        {
            for (v = 0; v < 4; v++)
            {
                var = sm_3D_vecs[k][v];
                sm_3D_vecs[k][v] = curr[v];
                curr[v] = var;
            }
        }
    }
    *N_circ++;
}

int already_matched(int sm_IS[][2], int indx)
{   
    int i;
    for (i = 0; i < N_GC; i++)
    {
        if (sm_IS[i][0] == indx)
        {
            return 1;
        }
    }
    return 0;
}

void sm_4_star(double four_stars[][4], double sm_3D_vecs[][4], int sm_IS[][2], int sm_K_vec_arr[][3], int *N_match, int N_i, double q, double m)
{   
    int i=0;
    int j=0;
    int k=0;

    int SIM[N_GC][6];
    memset(SIM, 0, N_GC * sizeof(SIM[0]));
    
    double p[6];
    int ct = 0;
    for (i = 0; i < 4; i++)
    {
        for (j = i + 1; j < 4; j++)
        {
             double norm1 = sqrt(four_stars[i][1] * four_stars[i][1] + four_stars[i][2] * four_stars[i][2] + four_stars[i][3] * four_stars[i][3]);
             double norm2 = sqrt(four_stars[j][1] * four_stars[j][1] + four_stars[j][2] * four_stars[j][2] + four_stars[j][3] * four_stars[j][3]);
            p[ct] = fabs(four_stars[i][1] * four_stars[j][1] + four_stars[i][2] * four_stars[j][2] + four_stars[i][3] * four_stars[j][3]) / (norm1 * norm2);
            ct++;
        }
    }

    int checks[4][6] = {{1, 1, 1, 0, 0, 0},
                        {1, 0, 0, 1, 1, 0},
                        {0, 1, 0, 1, 0, 1},
                        {0, 0, 1, 0, 1, 1}};

    for (j = 0; j < 6; j++)
    {
        double sin_j = sqrt(1 - (p[j] * p[j]));
        int k_top = ceil((cos(DELTA) * p[j] + sin_j * sin(DELTA) - q) / m);
        int k_bot = floor((cos(DELTA) * p[j] - sin_j * sin(DELTA) - q) / m);
        if (k_top <= 0 || k_bot >= 224792)
        {
            cortos_printf("bad values : k_bot = %d, k_top = %d\n", k_bot, k_top);
            continue;
        }
        else
        {
            if (k_top > 224792)
            {
                k_top = 224792;
            }
            if (k_bot < 0)
            {
                k_bot = 1;
            }
            int k_start = sm_K_vec_arr[k_bot - 1][2] + 1;
            int k_end = sm_K_vec_arr[k_top - 1][2];
            if (k_start == k_end)
            {
                SIM[sm_K_vec_arr[k_end - 1][0]][j] = 1;
            }
            else
            {
                for (i = k_start; i <= k_end; i++)
                {
                    SIM[sm_K_vec_arr[i - 1][0]][j] = 1; 
                    SIM[sm_K_vec_arr[i - 1][1]][j] = 1;
                }
            }
        }
    }

    for (j = 0; j < 4; j++)
    {
        int matched_rows = 0;
        int temp = 0;         
        for (k = 0; k < N_GC; k++)
        {
            if (SIM[k][0] == checks[j][0] && SIM[k][1] == checks[j][1] && SIM[k][2] == checks[j][2] && SIM[k][3] == checks[j][3] && SIM[k][4] == checks[j][4] && SIM[k][5] == checks[j][5])
            {
                matched_rows++;
                temp = k;
            }
        }
        if (matched_rows == 1)
        {
            int flag = already_matched(sm_IS, (int)four_stars[j][0]);
            if (flag == 0)
            {
                (*N_match)++;
                for (k = 0; k < N_i; k++)
                {
                    if ((int)sm_3D_vecs[k][0] == (int)four_stars[j][0])
                    {
                        sm_3D_vecs[k][0] = -1;
                        break;
                    }
                }
                for (k = 0; k < N_GC; k++)
                {
                    if (sm_IS[k][0] == -1)
                    {
                        sm_IS[k][0] = (int)four_stars[j][0];
                        sm_IS[k][1] = temp;
                        break;
                    }
                }
            }
        }
    }
    
}

void sm_gnrt_3D_vec(double sm_3D_vecs[][4], double sm_sorted_UIS[][3], int N_i)
{   int i;
    for (i = 0; i < N_i; i++)
    {
        double local = sqrt((sm_sorted_UIS[i][1] / FOCAL_LENGTH) * (sm_sorted_UIS[i][1] / FOCAL_LENGTH) + (sm_sorted_UIS[i][2] / FOCAL_LENGTH) * (sm_sorted_UIS[i][2] / FOCAL_LENGTH) + 1);
        sm_3D_vecs[i][0] = sm_sorted_UIS[i][0];
        sm_3D_vecs[i][1] = (sm_sorted_UIS[i][1] / (FOCAL_LENGTH * local));
        sm_3D_vecs[i][2] = (sm_sorted_UIS[i][2] / (FOCAL_LENGTH * local));
        sm_3D_vecs[i][3] = 1 / local;
        //cortos_printf("%.16f %.16f %.16f\n", sm_3D_vecs[i][3], sm_3D_vecs[i][1], sm_3D_vecs[i][2]);

    }
}

void sm_validate(double sm_3D_vecs[][4], int sm_IS[][2], double sm_GC[][4], int *N_is, int N_i, double tol, double p_1, double p_2){
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
                double d_ij = fabs(sm_3D_vecs[i][1]*sm_3D_vecs[j][1] + sm_3D_vecs[i][2]*sm_3D_vecs[j][2] + sm_3D_vecs[i][3]*sm_3D_vecs[j][3]);
                // printf("i: %d, j: %d, norm1: %Lf, norm2: %Lf, d_ij: %Lf\n", i, j, norm1, norm2, d_ij);
                double d_ij_gc = fabs(sm_GC[sm_IS[i][1] - 1][1]*sm_GC[sm_IS[j][1] - 1][1] + sm_GC[sm_IS[i][1] - 1][2]*sm_GC[sm_IS[j][1] - 1][2] + sm_GC[sm_IS[i][1] - 1][3]*sm_GC[sm_IS[j][1] - 1][3]);
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
            // printf("%d discarded, %d votes \n\n\n", i, votes[i]);
            N_new--;
        }
    }
    *N_is = N_new;
}

void starMatching(double centroids_st[MAX_STARS][3], int tot_stars, double data[3][MAX_STARS], int input_ids[50], int star_ids[50], int* matched_stars){
    // Maximum number of iterations
    int N_max = tot_stars - 1;

    // N_i is specially used to pass onto other functions(remains unchanged throughout the code)
    int N_i = tot_stars;

    // N_uis is a SM variable for the total number of stars detected from the FE block(changes value in main)
    int N_uis = tot_stars;

    // Required maximum number of matched stars
    int N_th = 8;

    // Number of times control goes to sm_4_star_circulate
    int N_circ = 0;

    // Number of identified stars
    int N_is = 0;

    double tol = 0.5;
    double p_1 = 35;
    double p_2 = 80;

    // Constants for using the k vector table (to be used in the 4 star matching)
    double m = (Y_MAX - Y_MIN + 2 * EPSILON) / (N_KVEC_PAIRS - 1);
    double q = Y_MIN - m - EPSILON;

    // Array for storing the Identified Stars
    int sm_IS[N_GC][2];

    // Initialize a block of memory to -1
    memset(sm_IS, -1, N_GC * sizeof(sm_IS[0]));

    // Array to store body frame vectors of extracted stars from FE block
    double sm_3D_vecs[N_i][4];

    // Generate body frame vectors for extracted stars
    sm_gnrt_3D_vec(sm_3D_vecs, centroids_st, N_i);

    int i = 1;
    for (i = 1; i <= N_max; i++){
        
            if (N_uis >= 4 && N_is < N_th){
            // Variable for storing the number of stars matched in a particular iteration    
            int N_match = 0;

            // This will store the 4 stars used from the sm_3D_vecs table
            double four_stars[4][4];

            // Here the variable countt is used just to count whether 4 stars have been extracted
            int countt = 0, j = 0;

            // Pick body vectors of 4 stars from sm_3D_vecs
            for (countt = 0, j = 0; j < N_i && countt < 4; j++){
                if ((int)sm_3D_vecs[j][0] != -1){
                    int k = 0;
                    for (k = 0; k < 4; k++){
                        four_stars[countt][k] = sm_3D_vecs[j][k];
                    }
                    countt++;
                }
            }

            // Perform 4 star N star algorithm
            sm_4_star(four_stars, sm_3D_vecs, sm_IS, sm_K_vec_arr, &N_match, N_i, q, m);

            // Decrement matched stars from those detected from FE block for next iteration
            N_uis -= N_match;

            // Increment identified stars with matched stars
            N_is += N_match;

            // If no star is detected or we have not circulated the sm_3D_vecs exhaustively
            if (N_match == 0 && N_circ <= 2 * N_i){

                sm_4_star_circulate(sm_3D_vecs, &N_circ, N_i);
            
                if (N_circ >= 2 * N_i){
                    break;
                }
            }
        }

        // End the loop if the conditions "N_uis >= 4 && N_is < N_th" are not satisfied
        else{
            break;
        }
    }

    sm_validate(sm_3D_vecs, sm_IS, sm_GC, &N_is, N_i, tol, p_1, p_2);

    // Index variable for organising SM output
    int data_index = 0;

    double x_inertial[N_is], y_inertial[N_is], z_inertial[N_is];

    // Arrays to store body frame components (sm_3D_vec)
    double x_body[N_is], y_body[N_is], z_body[N_is];

    // If "some" stars match
    if (N_is != 0){
        *matched_stars = N_is;
    
        i = 0;
        for (i = 0; i < N_GC; i++){
            if (sm_IS[i][0] != -1){

                // Storing input ids and SSP ids in respective arrays
                input_ids[data_index] = sm_IS[i][0];
                star_ids[data_index] = sm_IS[i][1];

                // Storing body frame components of matched stars in respective arrays
                x_body[data_index] = sm_3D_vecs[sm_IS[i][0] - 1][3];
                y_body[data_index] = sm_3D_vecs[sm_IS[i][0] - 1][1];
                z_body[data_index] = sm_3D_vecs[sm_IS[i][0] - 1][2];

                // Storinng intertial frame components of matched stars in respective arrays
                x_inertial[data_index] = sm_GC[sm_IS[i][1] - 1][1];
                y_inertial[data_index] = sm_GC[sm_IS[i][1] - 1][2];
                z_inertial[data_index] = sm_GC[sm_IS[i][1] - 1][3];

                // Increment data_index for next matched star
                data_index++;
            }
        }

        // Arranging SM output vectors compatible with Estimation block
        int j = 0;
        for (j = 0; j < N_is; j++){
            data[0][j] = x_inertial[j];
            data[0][j + N_is] = x_body[j];
            data[1][j] = y_inertial[j];
            data[1][j + N_is] = y_body[j];
            data[2][j] = z_inertial[j];
            data[2][j + N_is] = z_body[j];

        }
    }

    // If no star is matched
    else{
        cortos_printf("\nCOULD NOT MATCH STARS\n");
        
    }
}

// Estimation structures
typedef struct Vec Vec; 
struct Vec{
    double x, y, z;
};

typedef struct Matrix_3 Matrix_3;
struct Matrix_3{
    double elements[3][3];
};

//Estimation functions
double absoluteValue(double x){
    if (x < 0){
        x = -x;
    }
    return x;
}

double square_root(double x){
    double guess = 1;
    while (absoluteValue((guess * guess) / x - 1.0) >= 0.00001)
    {
        guess = ((x / guess) + guess) / 2;
    }
    return guess;
}

void Vec_construct(Vec *temp, double x, double y, double z){
    temp->x = x;
    temp->y = y;
    temp->z = z;
}

void cross(Vec *temp, Vec *vec1, Vec *vec2){
    temp->x = vec1->y * vec2->z - vec1->z * vec2->y;
    temp->y = vec1->z * vec2->x - vec1->x * vec2->z;
    temp->z = vec1->x * vec2->y - vec1->y * vec2->x;
}

double dot(Vec *vec1, Vec *vec2){
    return (vec1->x * vec2->x + vec1->y * vec2->y + vec1->z * vec2->z);
}

void scale_vec(Vec *temp, double k){
    temp->x *= k;
    temp->y *= k;
    temp->z *= k;
}

void add_vec(Vec *temp, Vec *vec1, Vec *vec2){
    temp->x = vec1->x + vec2->x;
    temp->y = vec1->y + vec2->y;
    temp->z = vec1->z + vec2->z;
}

void matrix_construct(Matrix_3 *temp, unsigned char x){
    if (x == 0)
    { // Null Matrix
        unsigned char i = 0;
        unsigned char j = 0;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                (temp->elements)[i][j] = 0;
            }
        }
    }
    if (x == 1)
    {
        unsigned char i = 0;
        unsigned char j = 0;
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                if (i == j)
                    (temp->elements)[i][j] = 1;
                else
                    (temp->elements)[i][j] = 0;
            }
        }
    }
}

void add_matrix(Matrix_3 *temp, Matrix_3 *m1, Matrix_3 *m2){
    unsigned char i = 0;
    unsigned char j = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            (temp->elements)[i][j] = (m1->elements)[i][j] + (m2->elements)[i][j];
        }
    }
}

void scale_matrix(Matrix_3 *temp, Matrix_3 *M, double k){
    unsigned char i = 0;
    unsigned char j = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            temp->elements[i][j] = (M->elements[i][j]) * k;
        }
    }
}

double det(Matrix_3 *temp){
    double x;
    x = temp->elements[0][0] * (temp->elements[1][1] * temp->elements[2][2] - temp->elements[1][2] * temp->elements[2][1]) - temp->elements[0][1] * (temp->elements[1][0] * temp->elements[2][2] - temp->elements[1][2] * temp->elements[2][0]) + temp->elements[0][2] * (temp->elements[1][0] * temp->elements[2][1] - temp->elements[1][1] * temp->elements[2][0]);
    return x;
}

double trace(Matrix_3 *temp){
    return (temp->elements[0][0] + temp->elements[1][1] + temp->elements[2][2]);
}

void T(Matrix_3 *temp, Matrix_3 *m1){
    unsigned char i = 0;
    unsigned char j = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            temp->elements[i][j] = m1->elements[j][i];
        }
    }
}

void adjoint(Matrix_3 *temp, Matrix_3 *m){
    temp->elements[0][0] = m->elements[1][1] * m->elements[2][2] - m->elements[1][2] * m->elements[2][1];
    temp->elements[1][0] = m->elements[1][2] * m->elements[2][0] - m->elements[1][0] * m->elements[2][2];
    temp->elements[2][0] = m->elements[1][0] * m->elements[2][1] - m->elements[2][0] * m->elements[1][1];
    temp->elements[0][1] = m->elements[2][1] * m->elements[0][2] - m->elements[0][1] * m->elements[2][2];
    temp->elements[1][1] = m->elements[0][0] * m->elements[2][2] - m->elements[2][0] * m->elements[0][2];
    temp->elements[2][1] = m->elements[2][0] * m->elements[0][1] - m->elements[0][0] * m->elements[2][1];
    temp->elements[0][2] = m->elements[0][1] * m->elements[1][2] - m->elements[1][1] * m->elements[0][2];
    temp->elements[1][2] = m->elements[1][0] * m->elements[0][2] - m->elements[0][0] * m->elements[1][2];
    temp->elements[2][2] = m->elements[0][0] * m->elements[1][1] - m->elements[1][0] * m->elements[0][1];
}

void outer_product(Matrix_3 *temp, Vec *v1, Vec *v2){
    temp->elements[0][0] = v1->x * v2->x;
    temp->elements[0][1] = v1->x * v2->y;
    temp->elements[0][2] = v1->x * v2->z;
    temp->elements[1][0] = v1->y * v2->x;
    temp->elements[1][1] = v1->y * v2->y;
    temp->elements[1][2] = v1->y * v2->z;
    temp->elements[2][0] = v1->z * v2->x;
    temp->elements[2][1] = v1->z * v2->y;
    temp->elements[2][2] = v1->z * v2->z;
}

void matmul(Vec *temp, Matrix_3 *M, Vec *v){
    temp->x = M->elements[0][0] * v->x + M->elements[0][1] * v->y + M->elements[0][2] * v->z;
    temp->y = M->elements[1][0] * v->x + M->elements[1][1] * v->y + M->elements[1][2] * v->z;
    temp->z = M->elements[2][0] * v->x + M->elements[2][1] * v->y + M->elements[2][2] * v->z;
}

void quest(double Q[4], double data[3][MAX_STARS], int N){
    Vec b[N];
    Vec r[N];

    double epsilon_est = 0.001;
    double a[N];
    int c;
    for (c = 0; c < N; c++)
    {
        a[c] = 0;
        a[c] = 1.0 / N;
    }
    double guess = 1;
    Matrix_3 B, S;
    matrix_construct(&B, 0);
    matrix_construct(&S, 0);
    Vec z;
    Vec_construct(&z, 0, 0, 0);
    unsigned char counter = 0;
    double K;
    double norm_2_z;
    double det_S;
    double trace_B;
    double zTSz;
    double zTSSz;
    Matrix_3 adj_S;
    Matrix_3 check;
    int i = 0;
    for (i = 0; i < N * 2; i++)
    { 
        if (i < N)
        {
            // Construct r vectors according to the data read
            Vec_construct(&r[i], data[0][i], data[1][i], data[2][i]);
        }
        else
        {
             // Construct b vectors according to the data read
            Vec_construct(&b[i - N], data[0][i], data[1][i], data[2][i]);
        }
    }

    // Perform Quest
    double f(double x)
    { // This is the function whose roots are found using Newton Rapshon
        double first = (x * x - trace_B * trace_B + K) * (x * x - trace_B * trace_B - norm_2_z);
        double second = (x - trace_B) * (zTSz + det_S);
        return (first - second - zTSSz);
    }
    double f_bar(double x)
    { // This is the derivative of the function whose roots are found using Newton Rapshon
        double temp = 2 * x * (2 * x * x - 2 * trace_B * trace_B + K - norm_2_z);
        return (temp - zTSz - det_S);
    }

    do
    {
        if (counter == 1)
        { // Perform rotation abt x --- {x,-y,-z}
            for (i = 0; i < N; i++)
            {
                r[i].y = -1 * r[i].y;
                r[i].z = -1 * r[i].z;
            }
        }
        if (counter == 2)
        { // Perform rotation abt y --- {-x,y,-z}
            for (i = 0; i < N; i++)
            {
                r[i].x = -1 * r[i].x;
                r[i].z = -1 * r[i].z;
            }
        }
        if (counter == 3)
        { // Perform rotation abt z --- {-x,-y,z}
            for (i = 0; i < N; i++)
            {
                r[i].y = -1 * r[i].y;
                r[i].x = -1 * r[i].x;
            }
        }
        for (i = 0; i < N; i++)
        {
            Matrix_3 temp;
            outer_product(&temp, &(b[i]), &(r[i]));
            scale_matrix(&temp, &temp, a[i]);
            add_matrix(&B, &B, &temp);
        }
        for (i = 0; i < N; i++)
        {
            Vec temp;
            cross(&temp, &(b[i]), &(r[i]));
            scale_vec(&temp, a[i]);
            add_vec(&z, &z, &temp);
        }

        trace_B = trace(&B);
        T(&S, &B);              
        add_matrix(&S, &S, &B); 
        adjoint(&adj_S, &S);    
        K = trace(&adj_S);
        norm_2_z = z.x * z.x + z.y * z.y + z.z * z.z;
        det_S = det(&S);  
        Vec temp1, temp2; 
        matmul(&temp1, &S, &z);
        zTSz = dot(&z, &temp1);
        matmul(&temp2, &S, &temp1);
        zTSSz = dot(&z, &temp2);

        double rho = guess; 
        for (i = 0; i < 10; i++)
        {
            double x1 = f(rho);
            double x2 = f_bar(rho);
            rho = rho - x1 / x2;
        }
        rho += trace_B;
        Matrix_3 I;
        matrix_construct(&I, 1);
        scale_matrix(&I, &I, rho);
        scale_matrix(&check, &S, -1);
        add_matrix(&check, &check, &I);

        counter++;
    } while ((det(&check)) < epsilon_est);

    Vec q_3;
    double q_4 = det(&check);
    Matrix_3 adj_check;
    adjoint(&adj_check, &check);
    matmul(&q_3, &adj_check, &z);

    if (counter == 2)
    {
        Vec e;
        Vec_construct(&e, 1, 0, 0);
        double new_4 = -dot(&e, &q_3);
        cross(&q_3, &e, &q_3);
        scale_vec(&e, q_4);
        add_vec(&q_3, &q_3, &e);
        q_4 = new_4;
    }
    else if (counter == 3)
    {
        Vec e;
        Vec_construct(&e, 0, 1, 0);
        double new_4 = -dot(&e, &q_3);
        cross(&q_3, &e, &q_3);
        scale_vec(&e, q_4);
        add_vec(&q_3, &q_3, &e);
        q_4 = new_4;
    }
    else if (counter == 4)
    {
        Vec e;
        Vec_construct(&e, 0, 0, 1);
        double new_4 = -dot(&e, &q_3);
        cross(&q_3, &e, &q_3);
        scale_vec(&e, q_4);
        add_vec(&q_3, &q_3, &e);
        q_4 = new_4;
    }
    double alpha;
    double x1 = (q_3.x);
    double x2 = (q_3.y);
    double x3 = (q_3.z);
    double x4 = (q_4);
    alpha = square_root(x1 * x1 + x2 * x2 + x3 * x3 + x4 * x4);
    Q[0] = x1 / alpha;
    Q[1] = x2 / alpha;
    Q[2] = x3 / alpha;
    Q[3] = x4 / alpha;
    return;
}

void OILS(short arr_out_img[BREADTH + 2][LENGTH + 2]){
    // Store start time of FE and OILS
    uint64_t FE_START = cortos_get_clock_time();

    int tot_stars = 0;
    double centroids_st[MAX_STARS][3];

    // Perform Feature Extraction
    regionGrowth(arr_out_img, centroids_st, &tot_stars);
    // Store stop time of FE
    uint64_t FE_END = cortos_get_clock_time();

    // Print FE output on the terminal
    int i = 0;
    int j = 0;
    for(i = 0; i < tot_stars; i++){
        cortos_printf("%d %.16Lf %.16Lf\n", (int)centroids_st[i][0], centroids_st[i][1], centroids_st[i][2]);
    }

    // Variable passed by reference to starMatcing function to get number of mathched stars
    int matched_stars = 0;
    // Array to store input ids of matched stars
    int input_ids[MAX_STARS] = {0};
    // Array to store SSP ids of matched stars
    int star_ids[MAX_STARS] = {0};
   
    // Array to store the input of Estimation block
    double data[3][MAX_STARS];

    

    // Store start time of SM
    uint64_t SM_START = cortos_get_clock_time();

    // Perform Star Matching
    starMatching(centroids_st, tot_stars, data, input_ids, star_ids, &matched_stars);

    // Store stop time of SM
    uint64_t SM_END = cortos_get_clock_time();

    // Prints the number of stars matched by the SM block on the terminal
    cortos_printf("\nTotal matched stars = %d\n\n", matched_stars);

    // Prints the inertial frame vectors and body frame vectors of matched stars on the terminal
    if(matched_stars != 0){
        for (j = 0; j < matched_stars; j++){
            cortos_printf("%d %d ", input_ids[j], star_ids[j]);
            cortos_printf("%.16f %.16f %.16f ", data[0][j], data[1][j], data[2][j]);
            cortos_printf("%.16f %.16f %.16f\n",data[0][j + matched_stars], data[1][j + matched_stars], data[2][j + matched_stars]);
        }

        // Store start time of Estimation
        uint64_t EST_START = cortos_get_clock_time();
        
        // Array to store the quaternion output of Estimation block
        double out[4];

        // Perform QUEST
        quest(out, data, matched_stars);

        // Printing the quaternion values on the terminal
        cortos_printf("\n");
        cortos_printf("quat_3.x = %.15f\n", out[0]);
        cortos_printf("quat_3.y = %.15f\n", out[1]);
        cortos_printf("quat_3.z = %.15f\n", out[2]);
        cortos_printf("quat_4   = %.15f\n", out[3]);
    


        //Store stop time of Estimation and OILS
        uint64_t EST_END = cortos_get_clock_time();

        // CoRTOS operation
        uint32_t t_FEs = FE_START & (0xffffffff);
        uint32_t t_FEe = FE_END & (0xffffffff);
        uint32_t t_SMs = SM_START & (0xffffffff);
        uint32_t t_SMe = SM_END & (0xffffffff);
        uint32_t t_ESTs = EST_START & (0xffffffff);
        uint32_t t_ESTe = EST_END & (0xffffffff);
        
        // Print run times
        cortos_printf("\n");
        cortos_printf("FE__run_time =  %u\n", t_FEe - t_FEs);
        cortos_printf("SM__run_time =  %u\n", t_SMe - t_SMs);
        cortos_printf("EST_run_time =  %u\n", t_ESTe - t_ESTs);
        cortos_printf("Net_run_time =  %u\n", t_ESTe - t_FEs);
    }
}

