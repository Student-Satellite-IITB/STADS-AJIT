#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void bubbleSort2(double arr[][2], int n, int ind)
{
    int i, j;
    long double temp[2];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j][ind] > arr[j + 1][ind])
            {
                // swap the elements
                temp[0] = arr[j][0];
                temp[1] = arr[j][1];

                arr[j][0] = arr[j + 1][0];
                arr[j][1] = arr[j + 1][1];

                arr[j + 1][0] = temp[0];
                arr[j + 1][1] = temp[1];
            }
        }
    }
}

void bubbleSort3(double arr[][3], int n, int ind)
{
    int i, j;
    long double temp[3];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j][ind] > arr[j + 1][ind])
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
}
