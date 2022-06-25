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

int tot_stars=0;
unsigned short star_num = 0;
unsigned long x_sum[MAX_STARS] = {0};
unsigned long y_sum[MAX_STARS] = {0};
unsigned long pixel_sum[MAX_STARS] = {0};
unsigned short num_pixels[MAX_STARS] = {0};
unsigned short i,j;

unsigned short k;
unsigned short valid_stars = 0;
double centroids_st[MAX_STARS][3];
//Number of test cases
unsigned short n=1;
	
void getData(unsigned short i, unsigned short j, unsigned short star_num, unsigned long x_sum[], unsigned long y_sum[], unsigned long pixel_sum[], unsigned short num_pixels[], short arr_out_img[BREADTH + 2][LENGTH + 2])

{
	// base case
	if(arr_out_img[j][i] <= THRESHOLD)
		return;
	
	// keeping track of the sums
	x_sum[star_num] += (unsigned long)arr_out_img[j][i]*i;
	y_sum[star_num] += (unsigned long)arr_out_img[j][i]*j;
	pixel_sum[star_num] += (unsigned long)arr_out_img[j][i];
	num_pixels[star_num] += 1;
	arr_out_img[j][i] = 0;

	// recursive calls
	getData(i - 1, j, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
	getData(i + 1, j, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
	getData(i, j - 1, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
	getData(i, j + 1, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);

	return;
}


void regionGrowth(short arr_out_img[BREADTH + 2][LENGTH + 2], double centroids_st[MAX_STARS][3])
{
	
	// clear out all arrays
	unsigned short stars = 0;
	for(stars = 0; stars < MAX_STARS; stars++){
		x_sum[stars] = 0;
		y_sum[stars] = 0;
		pixel_sum[stars] = 0;
		num_pixels[stars] = 0;
	}

	//*uint64_t t1 = cortos_get_clock_time();
	star_num = 0;
	valid_stars = 0;
	tot_stars = 0;
	i = 0;
	j = 0;
	k = 0;
	// cortos_printf("RGA output starts here\n");

	for(j = 1; j < BREADTH + 1; j += SKIP_PIXELS)
		for( i = 1; i < LENGTH + 1; i += SKIP_PIXELS)
			if(arr_out_img[j][i] > THRESHOLD)
			{
				getData(i, j, star_num, x_sum, y_sum, pixel_sum, num_pixels, arr_out_img);
				star_num++;
			}


	// cortos_printf("SSP_ID,Sensor_y_Pixels,Sensor_z_Pixels\n");
	
	for(k = 0; k < star_num; k++)
	{
		if((num_pixels[k] <= STAR_MAX_PIXEL) & (num_pixels[k] > STAR_MIN_PIXEL))
		{
			valid_stars++;
			centroids_st[valid_stars-1][0] = valid_stars;
			centroids_st[valid_stars-1][1] = (double)x_sum[k]/(double)pixel_sum[k] - ((double)(LENGTH/2) + 0.5);
			centroids_st[valid_stars-1][2] = -1*((double)y_sum[k]/(double)pixel_sum[k] - ((double)(BREADTH/2) + 0.5));
			
			// To print Star ID, x coordinate, y coordinate
			// cortos_printf("%.6f,%.6f,%.6f\n",centroids_st[k][0],centroids_st[k][1],centroids_st[k][2]);		
		}
	}
	tot_stars += valid_stars;

	/*uint64_t t2 = cortos_get_clock_time();
	uint32_t t11 = t1& (0xffffffff);
	uint32_t t12 = t2& (0xffffffff);
	cortos_printf("RGA output ends here\n");
	cortos_printf("time = %u \n",t12-t11);*/
    printf("Total Stars: %d\n\n", tot_stars);
	return;
}

void main()
{
    printf("Image 1 output\n");
	regionGrowth(arr_out_img, centroids_st);
	
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
