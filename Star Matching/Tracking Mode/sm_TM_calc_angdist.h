#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double sm_TM_id_angdist(int id_1,
                        int id_2,
                        double sm_GD_SC[5060][4])
{
double dot, norm1, norm2, dist;
dot = sm_GD_SC[id_1][0]*sm_GD_SC[id_2][0] + sm_GD_SC[id_1][1]*sm_GD_SC[id_2][1] + sm_GD_SC[id_1][2]*sm_GD_SC[id_2][2];
norm1 = sqrt(sm_GD_SC[id_1][0]*sm_GD_SC[id_1][0] + sm_GD_SC[id_1][1]*sm_GD_SC[id_1][1] + sm_GD_SC[id_1][2]*sm_GD_SC[id_1][2]);
norm2 = sqrt(sm_GD_SC[id_2][0]*sm_GD_SC[id_2][0] + sm_GD_SC[id_2][1]*sm_GD_SC[id_2][1] + sm_GD_SC[id_2][2]*sm_GD_SC[id_2][2]);

dist = dot/(norm1*norm2);
return dist;

}


double sm_TM_centroid_angdist(double x_1, double y_1,
                              double x_2, double y_2,
                              double sm_TM_F,
                              double pixel_size)
{
double dot, norm1, norm2, dist;
dot = (x_1*pixel_size)*(x_2*pixel_size) + (y_1*pixel_size)*(y_2*pixel_size) + (sm_TM_F)*(sm_TM_F);
norm1 = sqrt((x_1*pixel_size)*(x_1*pixel_size) + (y_1*pixel_size)*(y_1*pixel_size) + (sm_TM_F)*(sm_TM_F));
norm2 = sqrt((x_2*pixel_size)*(x_2*pixel_size) + (y_2*pixel_size)*(y_2*pixel_size) + (sm_TM_F)*(sm_TM_F));

dist = dot/(norm1*norm2);
return dist;
}
