//#include <stdio.h>
#include "cortos.h"
#include <stdlib.h>
#include <math.h>

void bubbleSort(long double arr[][3], int n)
{
    uint64_t t1 = cortos_get_clock_time();
    int i, j;
    long double temp[3];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j][1] * arr[j][1] + arr[j][2] * arr[j][2] > arr[j + 1][1] * arr[j + 1][1] + arr[j + 1][2] * arr[j + 1][2])
            {
                // swap the elements
                temp[0] = arr[j][0];
                temp[1] = arr[j][1];
                temp[2] = arr[j][2];
                arr[j][0] = arr[j + 1][0];
                arr[j][1] = arr[j + 1][1];
                arr[j][2] = arr[j + 1][2];
                arr[j + 1][0] = temp[0];
                arr[j + 1][1] = temp[1];
                arr[j + 1][2] = temp[2];
            }
        }
    }
    uint64_t t2 = cortos_get_clock_time();
    uint32_t t11 = t1&(0xffffffff);
    uint32_t t12 = t2&(0xffffffff);
    cortos_printf("\ntime required for bubblesort is %u \n", t12-t11);

}