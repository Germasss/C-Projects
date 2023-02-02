#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>


#define N 1000


void print_array(int* arr)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%ld", *(arr + i * N + j));
			printf(" ");
		}
		printf("\n");
	
       }
 

	printf("\n");
}

int main(int argc, char *argv[])
{

	srand(time(NULL));

	int i, j, k, step, remains, rank, size;
	double start, end;


	int* A = (int*)malloc(N * N * sizeof(int));
	int* B = (int*)malloc(N * N * sizeof(int));
	int* C = (int*)malloc(N * N * sizeof(int));
	
	

	
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Comm_rank(comm, &rank);
	MPI_Comm_size(comm, &size);

	step = N / size; remains = N % size;

	int* local_A = (int*)malloc(step * N * sizeof(int));
	int* res = (int*)malloc(step * N * sizeof(int));


	if (rank == 0)
	{
		start = MPI_Wtime();

		for (i = 0; i < N; i++)
		{
			for (j = 0; j < N; j++)
			{
				*(A + i * N + j) = rand() % 10;
				*(B + i * N + j) = rand() % 10;
			}
		}
	}

	MPI_Bcast(B, N * N, MPI_INT, 0, comm);
	MPI_Scatter(A, step * N, MPI_INT, local_A, step * N, MPI_INT, 0, comm);

	
	
	for (i = 0; i < step; i++)
	{
		for (j = 0; j < N; j++)
		{
			*(res + i * N + j) = 0;
			for (k = 0; k < N; k++)
			{
				*(res + i * N + j) += *(local_A + i * N + k) * *(B + k * N + j);
			}
		}
	}

	
	MPI_Gather(res, N * step, MPI_INT, C, N * step, MPI_INT, 0, comm);

	
	if (rank == 0)
	{
		
		if (remains != 0)
		
		{
			
		for (i = N - remains - 1; i < N; i++)
			{
				for (j = 0; j < N; j++)
				{
					*(C + i * N + j) = 0;
					for (k = 0; k < N; k++)
					{
						*(C + i * N + j) += *(A + i * N + k) * *(B + k * N + j);
					}
				}
			}
			
		}

	}
	end = MPI_Wtime();



	if (rank == 0)
	
	{
		
		printf("Elapsed time : %lf \n", end - start);

	}

	MPI_Finalize();
				
			
}

