#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#define size 1000000

int main()
{
	printf("Function: sinh(2x) \n \n");
	double sum, secondLast, last;
	double h = 0.8/size;
	double x = 0.1;
	double difference;
	double array[size];
	int n;
	for (int i = 0; i < size; i++)
	{
		array[i] = 0;
	}
	double start = omp_get_wtime();
	#pragma omp parallel for firstprivate (x) private(difference,secondLast,last) reduction(+:sum)
	for (int i = 0; i < size; i++)
	{
		double stepx = x + i*h;
		difference = -1;
		sum = 2*stepx;
		secondLast = 0;
		last = 2*stepx;
		for (n = 1;; n++)
		{
			secondLast = last;
			double r = ((2*stepx) * (2*stepx)) / (2*n*(2*n+1));
			last *= r;
			sum += last;
			double difference = last - secondLast;
			if (difference == 0)
				break;
		}
		array[i] = sum;		
	}
	double end = omp_get_wtime();
	x = 0.1;
	for (int i = 0; i < 3; i++)
	{
		printf("%e ", array[i]);
		printf("%e ", sinh(2*x));
		printf("%e ", sinh(2*x) - array[i]);
		printf("\n");
		x += h;
	}
	x = 0.1 + (size*h-3*h);
	for (int i = size - 3; i < size; i++)
	{
		printf("%e ", array[i]);
		printf("%e ", sinh(2*x));
		printf("%e ", sinh(2*x) - array[i]);
		printf("\n");
		x += h;
	}
	printf("work time: %lf", end-start);
}