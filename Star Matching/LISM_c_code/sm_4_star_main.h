#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int already_matched(int sm_IS[][2],int indx,int N_gc){
    for (int i = 0; i < N_gc; i++)
    {
        if (sm_IS[i][0]==indx)
        {
            return 1;
        }
    }
    return 0;
}

void sm_4_star (double four_stars[][4], double sm_3D_vecs[][4], int sm_IS[][2], int sm_K_vec_arr[][3], int *N_match, int N_i, int N_gc, double delta, double q, double m)
{
    double SIM[N_gc][6]; // SIM implies star identification matrix which is basically the table in which we set those values as 1 
                         // which are corresponding to the star ids obtained from the kvec catalogue
    for (int i = 0; i < N_gc; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            SIM[i][j] = 0;
        }
    }
    
    double p[6]; // this stores the angular distances between each of the 4 pairs in the four_stars array
    int ct = 0;
    // below loop calculates angular distances between each pairs and stores them in the array p
    for (int i = 0; i < 4; i++)
    {
        for (int j = i+1; j < 4; j++)
        {
            p[ct] = four_stars[i][1] * four_stars[j][1] + four_stars[i][2] * four_stars[j][2] + four_stars[i][3] * four_stars[j][3];
            ct++;
        }    
    }
    // below is the array used for checking the matching of a particular star
    // those who know the 4 star algo will be knowing about this
    int checks[4][6] = {{1, 1, 1, 0, 0, 0},
                        {1, 0, 0, 1, 1, 0},
                        {0, 1, 0, 1, 0, 1},
                        {0, 0, 1, 0, 1, 1}};

    for (int j = 0; j < 6; j++)
    {
        // the below computations have been directly adopted from the Dong-Xing 4 star document

        int k_top = ceil((cos(acos(p[j]) - delta) - q) / m);
        int k_bot = floor((cos(acos(p[j]) + delta) - q) / m);

        if (k_top < 0 || k_bot >= 188807)
        {
            printf("bad values : k_bot = %d, k_top = %d\n", k_bot, k_top);
            continue;
        }
        else
        {
            if (k_top > 188807)
            {
                k_top = 188806;
            }
            if (k_bot < 0)
            {
                k_bot = 0;
            }
            int k_start = sm_K_vec_arr[k_bot][0] + 1;
            int k_end = sm_K_vec_arr[k_top][0];
            for (int i = k_start; i <= k_end; i++)
            {
                SIM[sm_K_vec_arr[i][1]][j] = 1; // sm_K_vec_arr[i][1 (or 2)] gives you the star ids which CAN be the unidentified stars
                SIM[sm_K_vec_arr[i][2]][j] = 1;
            }
        }
    }
    for (int j = 0; j < 4; j++)
    {
        int matched_rows = 0; // this stores the number of rows matched
        int temp = 0; // this variable stores the row number of the matched row
        for (int k = 0; k < N_gc; k++)
        {
            if (SIM[k][0] == checks[j][0]
             && SIM[k][1] == checks[j][1]
             && SIM[k][2] == checks[j][2]
             && SIM[k][3] == checks[j][3] 
             && SIM[k][4] == checks[j][4] 
             && SIM[k][5] == checks[j][5])
            {
                matched_rows++;
                temp = k;
            }
        }
        if (matched_rows == 1)
        {
            int flag = already_matched(sm_IS, (int)four_stars[j][0], N_gc);
            if (flag == 0) // checking if that star has earlier been matched
            {
                (*N_match)++;
                for (int k = 0; k < N_i; k++)
                {
                    // below is the substitute for removing the identified star from the 3D vector array
                    if ((int)sm_3D_vecs[k][0] == (int)four_stars[j][0]) 
                    {
                        sm_3D_vecs[k][0] = -1;
                        break;
                    }
                }
                for (int k = 0; k < N_gc; k++)
                {
                    if (sm_IS[k][0]==-1)
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