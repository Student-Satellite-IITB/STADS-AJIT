#include "cortos.h"
// Store the image as a short int array (with 10 bit resolution) under the variable name "arr_in_img"
#include "Image_1.h"

#define THRESHOLD 10
#define STAR_MIN_PIXEL 3
#define STAR_MAX_PIXEL 150
#define MAX_STARS 100
#define SKIP_PIXELS 1
#define LENGTH 100 //1024
#define BREADTH 100 //1280

//Initialising variables in the global scope
short arr_out_img[BREADTH + 2][LENGTH + 2];
char datafile[35], cenfile[35];
int tot_stars = 0;


	//void regionGrowth()
	unsigned short star_num = 0;
	unsigned short x_sum[MAX_STARS] = {0};
	unsigned short y_sum[MAX_STARS] = {0};
	unsigned short pixel_sum[MAX_STARS] = {0};
	unsigned short num_pixels[MAX_STARS] = {0};
	unsigned short i,j;

	//void regionGrowth()
	unsigned short k;	
	unsigned short valid_stars = 0;

	//int main()
	double centroids_st[MAX_STARS][3];
    int img_num;
    int n = 1;

void getData(short arr_out_img[BREADTH + 2][LENGTH + 2], unsigned short i, unsigned short j, unsigned short star_num, unsigned short x_sum[], unsigned short y_sum[], unsigned short pixel_sum[], unsigned short num_pixels[])
{
	// base case
	if(arr_out_img[j][i] <= THRESHOLD)
		return;
	
	// keeping track of the sums
	x_sum[star_num] += (unsigned short)arr_out_img[j][i]*i;
	y_sum[star_num] += (unsigned short)arr_out_img[j][i]*j;
	pixel_sum[star_num] += (unsigned short)arr_out_img[j][i];
	num_pixels[star_num] += 1;
	arr_out_img[j][i] = 0;

	// recursive calls
	getData(arr_out_img, i - 1, j, star_num, x_sum, y_sum, pixel_sum, num_pixels);
	getData(arr_out_img, i + 1, j, star_num, x_sum, y_sum, pixel_sum, num_pixels);
	getData(arr_out_img, i, j - 1, star_num, x_sum, y_sum, pixel_sum, num_pixels);
	getData(arr_out_img, i, j + 1, star_num, x_sum, y_sum, pixel_sum, num_pixels);

	return;
}

void padZeroes()
{   
	for(i = 0; i < BREADTH + 2; i++)
		for(j = 0; j < LENGTH + 2; j++)
			if((i == 0) | (j==0) | (i == (BREADTH + 1)) | (j == (LENGTH + 1)))
				arr_out_img[i][j] = 0;
			else
				arr_out_img[i][j] = arr_in_img[i-1][j-1];
}

void regionGrowth(double centroids_st[MAX_STARS][3], unsigned short img_num)
{
	padZeroes();
	for(j = 1; j < BREADTH + 1; j += SKIP_PIXELS)
		for( i = 1; i < LENGTH + 1; i += SKIP_PIXELS)
			if(arr_out_img[j][i] > THRESHOLD)
			{
				getData(arr_out_img, i, j, star_num, x_sum, y_sum, pixel_sum, num_pixels);
				star_num++;
			}

	CORTOS_INFO("Star ID, X Coordinate, Y Coordinate");
	
	for(k = 0; k < star_num; k++)
	{
		if((num_pixels[k] <= STAR_MAX_PIXEL) & (num_pixels[k] > STAR_MIN_PIXEL))
		{
			valid_stars++;
			centroids_st[k][0] = valid_stars;
			centroids_st[k][1] = ((double)x_sum[k]/(double)pixel_sum[k] - ((double)(LENGTH/2) + 0.5));
			centroids_st[k][2] = -1*((double)y_sum[k]/(double)pixel_sum[k] - ((double)(BREADTH/2) + 0.5));

			// To print Star ID, x coordinate, y coordinate
			CORTOS_INFO("%.6f,%.6f,%.6f\n",centroids_st[k][0],centroids_st[k][1],centroids_st[k][2]);			
		}
	}
	tot_stars += valid_stars;

	return;
}

void main()
{
	// Initialising scalar variables to prevent incremental errors over multiple runs
	star_num = 0;
	valid_stars = 0;
	tot_stars = 0;
	i = 0;
	j = 0;
	k = 0;
    
    //Number of test cases n
	for(img_num = 1; img_num <= n; img_num++)
	{
		// Master function call
		regionGrowth(centroids_st, img_num);
	}
	
	CORTOS_INFO("\nTotal Stars: %d", tot_stars);
	cortos_exit(0);
}
