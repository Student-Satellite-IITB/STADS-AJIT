#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;

//sm_TM_CP_F = focal length in cm
//pixel size = in cm
void sm_TM_CP (double sm_TM_CP_prevmat_1[][3],
               double sm_TM_CP_prevmat_2[][3],
               double sm_TM_CP_F,
               double sm_TM_CP_predmat[][3],
               int N,
               double pixel_size)
{
double phi = 0, theta = 0, psi = 0;
double u, v, f = sm_TM_CP_F;
double dun, dvn;
double m[2*N][3];

for (int k=0; k<N; k++)
{
    u = sm_TM_CP_prevmat_2[k][0] * pixel_size;
    v = sm_TM_CP_prevmat_2[k][1] * pixel_size;
    m[2*k][0] = u*v/f;
    m[2*k][1] = -f - u*u/f;
    m[2*k][2] = v;
    m[2*k+1][0] = f + v*v/f;
    m[2*k+1][1] = -u*v/f;
    m[2*k+1][2] = -u;
}

/*for (int k=0; k<2*N; k++)
cout<<m[k][0]/f<<' '<<m[k][1]/f<<' '<<m[k][2]/f<<endl;*/


double m2[3][3] = {0,0,0,0,0,0,0,0,0};

for (int k=0; k<2*N; k++)
{
   m2[0][0] += m[k][0]*m[k][0];
   m2[1][0] += m[k][1]*m[k][0];
   m2[2][0] += m[k][2]*m[k][0];
   m2[0][1] += m[k][0]*m[k][1];
   m2[1][1] += m[k][1]*m[k][1];
   m2[2][1] += m[k][2]*m[k][1];
   m2[0][2] += m[k][0]*m[k][2];
   m2[1][2] += m[k][1]*m[k][2];
   m2[2][2] += m[k][2]*m[k][2];
}

/*for (int k=0; k<3; k++)
cout<<m2[k][0]/f/f<<' '<<m2[k][1]/f/f<<' '<<m2[k][2]/f/f<<endl;
cout<<endl<<endl;*/

double determinant = 0;
double minv[3][3];

for(int i=0;i<3;i++)
    determinant = determinant + (m2[0][i]*(m2[1][(i+1)%3]*m2[2][(i+2)%3] - m2[1][(i+2)%3]*m2[2][(i+1)%3]));

for(int i=0;i<3;i++)
{
    for(int j=0;j<3;j++)
        minv[i][j] = ((m2[(i+1)%3][(j+1)%3] * m2[(i+2)%3][(j+2)%3]) - (m2[(i+1)%3][(j+2)%3]*m2[(i+2)%3][(j+1)%3]))/ determinant;
}

/*for (int k=0; k<3; k++)
cout<<minv[k][0]*f*f<<' '<<minv[k][1]*f*f<<' '<<minv[k][2]*f*f<<endl;

cout<<endl<<endl;

for (int k=0; k<2*N; k++)
cout<<m[k][0]/f<<' '<<m[k][1]/f<<' '<<m[k][2]/f<<endl;

cout<<endl<<endl;*/

double m3[3][2*N];
for (int k=0; k<2*N; k++)
{
    m3[0][k] = minv[0][0]*m[k][0] + minv[0][1]*m[k][1] + minv[0][2]*m[k][2];
    m3[1][k] = minv[1][0]*m[k][0] + minv[1][1]*m[k][1] + minv[1][2]*m[k][2];
    m3[2][k] = minv[2][0]*m[k][0] + minv[2][1]*m[k][1] + minv[2][2]*m[k][2];
}

/*for (int k=0; k<2*N; k++)
cout<<m3[0][k]*f<<' '<<m3[1][k]*f<<' '<<m3[2][k]*f<<endl;

cout<<endl<<endl;*/

double col[2*N];
for (int k=0; k<N; k++)
{
    col[2*k] = (sm_TM_CP_prevmat_2[k][0] - sm_TM_CP_prevmat_1[k][0]) * pixel_size;
    col[2*k+1] = (sm_TM_CP_prevmat_2[k][1] - sm_TM_CP_prevmat_1[k][1]) * pixel_size;
}

/*for (int k=0; k<2*N; k++)
cout<<col[k]<<endl;

cout<<endl<<endl;*/

for (int k=0; k<2*N; k++)
{
    phi += m3[0][k]*col[k];
    theta += m3[1][k]*col[k];
    psi += m3[2][k]*col[k];
}

for (int k=0; k<N; k++)
{
    u = sm_TM_CP_prevmat_2[k][0] * pixel_size;
    v = sm_TM_CP_prevmat_2[k][1] * pixel_size;

    dun = (u*v/f)*phi + (-f - u*u/f)*theta + v*psi;
    dvn = (f + v*v/f)*phi + (-u*v/f)*theta + (-u)*psi;

    sm_TM_CP_predmat[k][0] = round(sm_TM_CP_prevmat_2[k][0] + dun/pixel_size);
    sm_TM_CP_predmat[k][1] = round(sm_TM_CP_prevmat_2[k][1] + dvn/pixel_size);
    //sm_TM_CP_predmat[k][0] = dun/pixel_size;
    //sm_TM_CP_predmat[k][1] = dvn/pixel_size;

    sm_TM_CP_predmat[k][2] = sm_TM_CP_prevmat_1[k][2];
}


}


