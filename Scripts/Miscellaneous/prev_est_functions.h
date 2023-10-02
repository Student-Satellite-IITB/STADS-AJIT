#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "constants.h"
// #include "sm_K_vec_arr.h"
// #include "sm_GC.h"
// #include "sm_TM_SNT.h"

// -------------------------------RGA functions------------------------------------

double absoluteValue(double x)
{
    if (x < 0) return -x;
    return x;
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
    double epsilon_seq_error = 0.1;
    int is_success = 1;
    double a[N];
    int c;
    for (c = 0; c < N; c++)
    {
        a[c] = 0;
        a[c] = 1.0 ;
    }
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
        matrix_construct(&B, 0);
        matrix_construct(&S, 0);
        Vec_construct(&z, 0, 0, 0);

        if (counter == 1)
        { // Perform rotation abt x --- {x,-y,-z}
            for (i = 0; i < N; i++)
            {
                r[i].y = -1 * r[i].y;
                r[i].z = -1 * r[i].z;
            }
        }
        else if (counter == 2)
        { // Perform rotation abt y --- {-x,y,-z}
            for (i = 0; i < N; i++)
            {
                r[i].x = -1 * r[i].x;
                r[i].y = -1 * r[i].y;
            }
        }
        else if (counter == 3)
        { // Perform rotation abt z --- {-x,-y,z}
            for (i = 0; i < N; i++)
            {
                r[i].y = -1 * r[i].y;
                r[i].z = -1 * r[i].z;
            }
        }
        else if(counter > 3)
        {
            is_success = 0;
            break;
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

        double rho = N; 
        double x1 = 0;
        double x2 = 0;
        while(x1 > epsilon_est)
        {
            x1 = f(rho);
            x2 = f_bar(rho);
            rho = rho - x1 / x2;
        }
        rho += trace_B;
        Matrix_3 I;
        matrix_construct(&I, 1);
        scale_matrix(&I, &I, rho);
        scale_matrix(&check, &S, -1);
        add_matrix(&check, &check, &I);

        counter++;
    } while ((det(&check)) < epsilon_seq_error);

     Vec q_3;
    double q_4;

    if(is_success == 1)
    {
        q_4 = det(&check);
        Matrix_3 adj_check;
        adjoint(&adj_check, &check);
        matmul(&q_3, &adj_check, &z);

        double norm_q = square_root(q_3.x *q_3.x + q_3.y *q_3.y + q_3.z*q_3.z + q_4*q_4);
        scale_vec(&q_3, 1/norm_q);
        q_4 = q_4/norm_q;

        if(q_4 < 0)
        {
            q_3.x = -q_3.x;
            q_3.y = -q_3.y;
            q_3.z = -q_3.z;
            q_4 = -q_4;
        }

        Vec e, cross_q;
        if (counter == 2)
        {       
            Vec_construct(&e, 1, 0, 0);
            double new_4 = -dot(&e, &q_3);
            cross(&cross_q, &e, &q_3);
            scale_vec(&e, q_4);
            add_vec(&q_3, &cross_q, &e);
            q_4 = new_4;
        }
        
        else if (counter == 3)
        {
            Vec_construct(&e, 0, 1, 0);
            double new_4 = -dot(&e, &q_3);
            cross(&cross_q, &e, &q_3);
            scale_vec(&e, q_4);
            add_vec(&q_3, &cross_q, &e);
            q_4 = new_4;
        }
        else if (counter == 4)
        {
            Vec_construct(&e, 0, 0, 1);
            double new_4 = -dot(&e, &q_3);
            cross(&cross_q, &e, &q_3);            
            scale_vec(&e, q_4);
            add_vec(&q_3, &cross_q, &e);
            q_4 = new_4;
        }
        if(q_4 < 0)
        {
            q_3.x = -q_3.x;
            q_3.y = -q_3.y;
            q_3.z = -q_3.z;
            q_4 = -q_4;
        }
    }
    else
    {
        Vec_construct(&q_3, -1, 1, 1);
        q_4 = 1;
    }

    Q[0] = q_3.x;
    Q[1] = q_3.y;
    Q[2] = q_3.z;
    Q[3] = q_4;
    return;
}
