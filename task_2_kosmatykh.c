#include <stdio.h>
#include <time.h>
#define razmer 3


void Print(int A[razmer][razmer])
{
	int i, j;
	for (i = 0; i < razmer; i++)
	{
		for (j = 0; j < razmer; j++)
			printf("%d \t", A[i][j]);
			printf("\n");
	}
}

int main()
{
	//Matrix X can be multiplied by matrix Y only if the number of columns of matrix X equals the number of rows of matrix Y.
	//Matrices for which this condition is not met cannot be multiplied
	//We need: determine the size of the matrices; if the number of columns of the first matrix matches the number of rows of the second matrix, then perform multiplication.
	srand(time(NULL));

	// matrix X
	int X[razmer][razmer];
	//matrix Y
	int Y[razmer][razmer];

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			X[i][j] = 0;
			Y[i][j] = 0;
		}
	}

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			X[i][j] = rand() % 5;
			Y[i][j] = rand() % 5;
		}
	}

	//Fill the matrix with zeros so that garbage is not stored in it

	// matrix Z
	int Z[razmer][razmer];

	//Matrix multiplication is performed by multiplying a row by a column. 
	//The products of the first row element and the first column element, the second row element and the second column element, etc. are found. 
	//Then the resulting products are summed up

	for (int i = 0; i < razmer; i++)
	{
		for (int j = 0; j < razmer; j++)
		{
			Z[i][j] = 0;
			for (int g = 0; g < razmer; g++)
			{
				Z[i][j] += X[i][g] * Y[g][j];
			}
		}
	}

	//We output the matrices	

	printf("Matrix X ");
	printf("\n");
	Print(X);

	printf("Matrix Y ");
	printf("\n");
	Print(Y);

	printf("Matrix Z ");
	printf("\n");
	Print(Z);

}