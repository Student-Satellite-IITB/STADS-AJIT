#include "fe_region_growth.h"

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
{
	for(int i = 0; i < BREADTH + 2; i++)
		for(int j = 0; j < LENGTH + 2; j++)
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
	for(unsigned short j = 1; j < BREADTH + 1; j += SKIP_PIXELS)
		for(unsigned short i = 1; i < LENGTH + 1; i += SKIP_PIXELS)
			if(arr_out_img[j][i] > THRESHOLD)
			{
				getData(arr_out_img, i, j, star_num, x_sum, y_sum, pixel_sum, num_pixels);
				star_num++;
			}
	ofstream out;
	sprintf(datafile, "Results/centroid data %i.csv", img_num);
	out.open(datafile);
	out<<"x_sum, y_sum, pixel_sum, num_pixels\n";
	for(unsigned short i = 0; i < MAX_STARS; i++)
	{
		out<<x_sum[i]<<","<<y_sum[i]<<","<<pixel_sum[i]<<","<<num_pixels[i]<<"\n";
	}
	out.close();
	unsigned short valid_stars = 0;
	
	ofstream cen;
	sprintf(cenfile, "Results/centroids %i.csv", img_num);
	cen.open(cenfile);
	cen<<"ID, x_cen, y_cen\n";
	for(unsigned short k = 0; k < star_num; k++)
	{
		if((num_pixels[k] <= STAR_MAX_PIXEL) & (num_pixels[k] > STAR_MIN_PIXEL))
		{
			valid_stars++;
			centroids_st[k][0] = valid_stars;
			centroids_st[k][1] = (double)x_sum[k]/(double)pixel_sum[k] - ((double)(LENGTH/2) + 0.5);
			centroids_st[k][2] = -1*((double)y_sum[k]/(double)pixel_sum[k] - ((double)(BREADTH/2) + 0.5));
			cen<<centroids_st[k][0]<<","<<centroids_st[k][1]<<","<<centroids_st[k][2]<<"\n";
		}
	}
	cen.close();
	return;
}

int main()
{
    double centroids_st[MAX_STARS][3];
	for(unsigned short img_num = 1; img_num < 16; img_num++)
	{
		// making the appropriate filename
		ifstream file;
		char filename[25];
        sprintf(filename, "Test Images/image %i.txt", img_num);
		file.open(filename);
		//reading the array
		for(unsigned short i = 0; i < BREADTH; i++)
			for(unsigned short j = 0; j < LENGTH; j++)
				file >> arr_in_img[i][j];
		auto start = high_resolution_clock::now();

		regionGrowth(arr_in_img, arr_out_img, centroids_st, img_num);

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<milliseconds>(stop - start);
		cout<<"Time taken: " <<duration.count()<<" ms"<<endl;
	}
}
