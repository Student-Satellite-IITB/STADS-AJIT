#include<stdio.h>
#include<string.h>



#define THRESHOLD 10
#define STAR_MIN_PIXEL 3
#define STAR_MAX_PIXEL 150
#define MAX_STARS 100
#define SKIP_PIXELS 2
#define LENGTH 1280
#define BREADTH 1024

short arr_in_img[BREADTH][LENGTH] = {{0}};
short arr_out_img[BREADTH + 2][LENGTH + 2];
char datafile[25], cenfile[25];

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

void padZeroes(short arr_in_img[BREADTH][LENGTH], short arr_out_img[BREADTH + 2][LENGTH + 2])
{   int i,j;
	for(i = 0; i < BREADTH + 2; i++)
		for(j = 0; j < LENGTH + 2; j++)
			if((i == 0) | (j==0) | (i == (BREADTH + 1)) | (j == (LENGTH + 1)))
				arr_out_img[i][j] = 0;
			else
				arr_out_img[i][j] = arr_in_img[i-1][j-1];
}

void regionGrowth(short arr_in_img[BREADTH][LENGTH], short arr_out_img[BREADTH + 2][LENGTH + 2], double centroids_st[MAX_STARS][3], unsigned short img_num)
{
	unsigned short star_num = 0;
	padZeroes(arr_in_img, arr_out_img);
	unsigned short x_sum[MAX_STARS] = {0};
	unsigned short y_sum[MAX_STARS] = {0};
	unsigned short pixel_sum[MAX_STARS] = {0};
	unsigned short num_pixels[MAX_STARS] = {0};
	unsigned short i,j;
	for(j = 1; j < BREADTH + 1; j += SKIP_PIXELS)
		for( i = 1; i < LENGTH + 1; i += SKIP_PIXELS)
			if(arr_out_img[j][i] > THRESHOLD)
			{
				getData(arr_out_img, i, j, star_num, x_sum, y_sum, pixel_sum, num_pixels);
				star_num++;
			}
	FILE *out;
	sprintf(datafile, "fe_rg_centroid_data_%i.csv", img_num);
	out=fopen(datafile,"w");
	fprintf(out,"x_sum, y_sum, pixel_sum, num_pixels\n");
	
	for(i = 0; i < MAX_STARS; i++)
	{
		fprintf(out,"%d, %d, %d, %d\n",x_sum[i],y_sum[i],pixel_sum[i],num_pixels);
		
	}
	fclose(out);
	unsigned short valid_stars = 0;
	
	FILE *cen;
	sprintf(cenfile, "fe_rg_centroids_%i.csv", img_num);
	cen=fopen(cenfile,"w");
	fprintf(cen,"ID, x_cen, y_cen\n");
	unsigned short k;
	for(k = 0; k < star_num; k++)
	{
		if((num_pixels[k] <= STAR_MAX_PIXEL) & (num_pixels[k] > STAR_MIN_PIXEL))
		{
			valid_stars++;
			centroids_st[k][0] = valid_stars;
			centroids_st[k][1] = (double)x_sum[k]/(double)pixel_sum[k] - ((double)(LENGTH/2) + 0.5);
			centroids_st[k][2] = -1*((double)y_sum[k]/(double)pixel_sum[k] - ((double)(BREADTH/2) + 0.5));
			fprintf(cen, "%2.0f,%11.7f,%11.7f\n",centroids_st[k][0],centroids_st[k][1],centroids_st[k][2]);
			
		}
	}
	fclose(cen);
	return;
}

int main()
{
    double centroids_st[MAX_STARS][3];
    unsigned short img_num;
  //Number of test cases
    unsigned short int n=15;
	for(img_num = 1; img_num <= n; img_num++)
	{
		// making the appropriate filename
		FILE *file;
		char filename[25];
        sprintf(filename, "image_%i.txt", img_num);
		file=fopen(filename,"r");
		//reading the array
		unsigned short i,j;
		for( i= 0; i < BREADTH; i++)
			for(j = 0; j < LENGTH; j++)
				fscanf(file,"%d",& arr_in_img[i][j]);

		regionGrowth(arr_in_img, arr_out_img, centroids_st, img_num);

		
	}
	printf("Centroids data can be found in fe_rg_centroids_i.txt for image_i");
}
