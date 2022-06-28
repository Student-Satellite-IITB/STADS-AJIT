#include<stdio.h>
#include<string.h>

#include "image_1_padded_rga.h"
//#include "image_2.h"
//#include "image_3.h"
//#include "image_4.h"
//#include "image_5.h"
//#include "image_96.h"
//#include "image_97.h"
//#include "image_98.h"
//#include "image_99.h"
//#include "image_101.h"

#define THRESHOLD 5 
#define STAR_MIN_PIXEL 3
#define STAR_MAX_PIXEL 150
#define MAX_STARS 100
#define SKIP_PIXELS 2
#define LENGTH 808
#define BREADTH 608
#define PIXEL_WIDTH 4.8e-6
#define NUM_MAX_STARS 10

int tot_stars=0;
// unsigned short star_num = 0;
// unsigned long x_sum[MAX_STARS] = {0};
// unsigned long y_sum[MAX_STARS] = {0};
// unsigned long pixel_sum[MAX_STARS] = {0};
// unsigned short num_pixels[MAX_STARS] = {0};
unsigned long pixel_track[MAX_STARS] = {0};
unsigned short i,j;

unsigned short k;
unsigned short valid_stars = 0;
double centroids_st[MAX_STARS][3];
//Number of test cases
unsigned short n=1;

void sort(double centroids_st[][3], unsigned long pixel_track[MAX_STARS], int tot_stars){
	double temp_st[3];
	unsigned long temp_pt;
	for (int i = 0; i < tot_stars; i++){
		for (int j = 0; j < tot_stars-i-1; j++){
			if(pixel_track[j] < pixel_track[j + 1]){
				temp_pt = pixel_track[j];
				pixel_track[j] = pixel_track[j + 1];
				pixel_track[j + 1] = temp_pt;
				for (int k = 0; k < 3; k++){
					temp_st[k] = centroids_st[j][k];
					centroids_st[j][k] = centroids_st[j + 1][k];
					centroids_st[j + 1][k] = temp_st[k];
				}
			}
		}
	}
}
	
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
			pixel_track[valid_stars-1] = pixel_sum[k];
        }
    }

    *tot_stars += valid_stars;
	sort(centroids_st, pixel_track, *tot_stars);
	if (*tot_stars > NUM_MAX_STARS)
		*tot_stars = NUM_MAX_STARS;
    return;
}


void main()
{
    printf("Image 1 output\n");
	regionGrowth(arr_out_img, centroids_st, &tot_stars);
	printf("Total Stars: %d\n", tot_stars);
	for(int i = 0; i < tot_stars; i++){
		for(int j = 0; j < 3; j++){
			printf("%Lf     ", centroids_st[i][j]);
		}
		printf("%d     \n", pixel_track[i]);
	}
	
	/*cortos_printf("Image 2 output\n");
	regionGrowth(arr_out_img_2, centroids_st);
	
	cortos_printf("Image 3 output\n");
	regionGrowth(arr_out_img_3, centroids_st);
	
	cortos_printf("Image 4 output\n");
	regionGrowth(arr_out_img_4, centroids_st);
	
	cortos_printf("Image 5 output\n");
	regionGrowth(arr_out_img_5, centroids_st);
	
	cortos_printf("Image 96 output\n");
	regionGrowth(arr_out_img_96, centroids_st);
	
	cortos_printf("Image 97 output\n");
	regionGrowth(arr_out_img_97, centroids_st);
	
	cortos_printf("Image 98 output\n");
	regionGrowth(arr_out_img_98, centroids_st);
	
	cortos_printf("Image 99 output\n");
	regionGrowth(arr_out_img_99, centroids_st);
	
	cortos_printf("Image 100 output\n");
	regionGrowth(arr_out_img_100, centroids_st);*/
}
