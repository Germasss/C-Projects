#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <time.h>
#define n 1000

int main()
{
    srand(time(NULL));
    int i, j, k;
    int** X = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        X[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            X[i][j] = rand() % 10;
        }
    int** Y = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        Y[i] = (int*)malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            Y[i][j] = rand() % 10;
        }
    int** Z = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++)
    {
        Z[i] = (int*)malloc(n * sizeof(int));
    }
    double start = omp_get_wtime();
    #pragma omp parallel for private(j,k)
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            Z[i][j] = 0;
            for (k = 0; k < n; k++)
            {
                Z[i][j] += X[i][k] * Y[k][j];
            }
        }
    }
    double end = omp_get_wtime();
    printf("Time taken: %lf", end - start);
    for (int i = 0; i < n; i++)
    {
        free(X[i]);
        free(Y[i]);
        free(Z[i]);
    }
    free(X);
    free(Y);
    free(Z);
}